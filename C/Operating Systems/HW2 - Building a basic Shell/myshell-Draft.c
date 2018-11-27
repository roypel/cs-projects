 #include <sys/types.h>
 #include <sys/wait.h>
 #include <unistd.h>
#include <stdio.h>
#include <signal.h>


int prepare(void){
	struct sigaction no_zombies = {//Do not transform children into zombies - used for background process
		.sa_handler = SIG_DFL,
		.sa_flags   = SA_NOCLDWAIT
		};
	sigaction(SIGCHLD, &no_zombies, NULL);
	struct sigaction no_interrupt = {//Ignore SIGINT, will be changed for foreground processes
		.sa_handler = SIG_IGN,
		.sa_flags = 0;
		};
	sigaction(SIGINT, &no_interrupt, NULL);
	}
		
int process_arglist(int count, char** arglist){
	int piped = 0, background = 0;//Flags for indication of the running method
	//char *first_cmd = arglist[0], *second_cmd;
	char *first_exec_args, second_exec_args;
	int i, j = 0;
	int pid, cid[2], pipfds[2], readerfd, writerfd, curr_child;
	first_exec_args = (char *) malloc((count + 1) * sizeof(char));
	if (first_exec_args == NULL){
		fprintf(stderr, "Error allocating memory");
		return 0;
	}
	for (i = 0; i <= count; i++){//Parsing the arglist 
		if (arglist[i] == '|'){;// i now indicates the beginning of the second command 
			if (pipe(pipefds) == -1) {
				fprintf(stderr, "Error creating pipe");
				return 0;
			}
			readerfd = pipefds[0];
			writerfd = pipefds[1];
			piped = 1;
			first_exec_args = (char *) realloc(first_exec_args, i+1);
			second_exec_args = (char *) malloc(count - i);
			if ((first_exec_args == NULL) || (second_exec_args == NULL)){
				fprintf(stderr, "Error allocating memory");
				free(first_exec_args);
				close(readerfd);
				close(writerfd);
				return 0;
			}
			first_exec_args[i] = NULL;
		}
		else if (arglist[i] == '&'){
			background = 1;
			first_exec_args = (char *) realloc(first_exec_args, i+1);// '&' Shouldn't be passed to execvp, and we assume we don't have a pipe with background
			if (first_exec_args == NULL){
				fprintf(stderr, "Error allocating memory");
				free(first_exec_args);
				close(readerfd);
				close(writerfd);
				return 0;
			}
			first_exec_args[i] = NULL;
			break;// '&' Is last argument, we can continue freely
		}
		else if (piped == 0)
			first_exec_args[i] = arglist[i];
		else
			second_exec_args[j++] = arglist[i];
	}
	struct sigaction return_interrupt = {//Restore default SIGINT behaviour for foreground process
		.sa_handler = SIG_DEF,
		.sa_flags = 0;
		};
	pid = fork();
	if (pid == -1) {
        fprintf(stderr, "Error in forking");
        close(readerfd);
        close(writerfd);
        return 0;;
    }
	if (pid == 0){//We're in child process
		sigaction(SIGINT, &return_interrupt, NULL);
		if (piped){
			close(readerfd);
		}
		execvp(first_exec_args[0], first_exec_args);
	}
	else{//We're in parent process
		cid[0] = pid;
		if (piped){//We have a pipe, need to fork to another child
			pid = fork();
			if (pid == -1) {
				fprintf(stderr, "Error in forking");
				close(readerfd);
				close(writerfd);
				return 0;;
			}
			if (pid == 0){//We're in second child process
				sigaction(SIGINT, &return_interrupt, NULL);
				close(writerfd);
				execvp(second_exec_args[0], second_exec_args);
			}
			else{
				cid[1] = pid;
				while ((cid[0] != 0) || (cid[1] != 0)){//As long one of the childs are running, wait
					if ((curr_child = wait(NULL)) != -1){
						if (curr_child == cid[0])
							cid[0] = 0;
						if (curr_child == cid[1])
							cid[1] = 0;
					}
				}
			}
		}
		else{
			if (background == 0)
				while ((curr_child = wait(NULL)) != pid);//Wait until child stop running
			//Else, we can continue run without stopping for background process
		}
	}
	return 1;
}


int finalize(void){
}
