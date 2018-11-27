#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>


int prepare(void){
	struct sigaction no_zombies;
	memset(&no_zombies, 0, sizeof(no_zombies));
	//Do not transform children into zombies - used for background process
	no_zombies.sa_handler = SIG_DFL;
	no_zombies.sa_flags   = SA_NOCLDWAIT | SA_RESTART;//Don't wait for children so zombies reaped automatically and restart if an interrupt happened
	if (sigaction(SIGCHLD, &no_zombies, NULL) != 0){
		fprintf(stderr, "Error registering signal handle");
		return 1;
	}
	struct sigaction ignore_interrupt;
	memset(&ignore_interrupt, 0, sizeof(ignore_interrupt));
	//Ignore SIGINT, will be changed for foreground processes
	ignore_interrupt.sa_handler = SIG_IGN;
	ignore_interrupt.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &ignore_interrupt, NULL) != 0){
		fprintf(stderr, "Error registering signal handle");
		return 1;
	}
	return 0;
}
		
int process_arglist(int count, char** arglist){
	int piped = 0, background = 0;//Flags for indication of the running method
	int i;
	int readerfd = -1, writerfd = -1, curr_child, pipefds[2];
	pid_t pid, cid[2];
	struct sigaction revert_interrupt;
	memset(&revert_interrupt, 0, sizeof(revert_interrupt));
	//Used to restore default SIGINT behaviour for foreground process
	revert_interrupt.sa_handler = SIG_DFL;
	revert_interrupt.sa_flags = 0;
	struct sigaction revert_SIGCHLD;
	memset(&revert_SIGCHLD, 0, sizeof(revert_SIGCHLD));
	//Used to restore default SIGCHLD behaviour to catch foreground process
	revert_SIGCHLD.sa_handler = SIG_DFL;
	revert_SIGCHLD.sa_flags = 0;
	for (i = 1; i < count; i++){//Parsing the arglist 
		if (strcmp(arglist[i], "|") == 0){// i now indicates the beginning of the second command 
			if (pipe(pipefds) == -1) {
				fprintf(stderr, "Error creating pipe");
				return 0;
			}
			arglist[i++] = NULL;
			readerfd = pipefds[0];
			writerfd = pipefds[1];
			piped = 1;
			break;
		}
		if (strcmp(arglist[i], "&") == 0){
			background = 1;
			arglist[i] = NULL;//Squash '&'
		}
	}
	if (background == 0){

	}
	pid = fork();
	if (pid == -1) {
        fprintf(stderr, "Error in forking");
		if (piped == 1){
       	 	close(readerfd);
        	close(writerfd);
		}
        return 0;
    }
	if (pid == 0){//We're in child process
		if (background == 0){//Not background, need to terminate on SIGINT
			if (sigaction(SIGINT, &revert_interrupt, NULL) != 0){
				fprintf(stderr, "Error registering signal handle");
				return 0;
			}
		}
		if (piped){
			close(readerfd);
			if (dup2(writerfd, 1) == -1){
				fprintf(stderr, "Error in duplicating file descriptor");
				close(writerfd);
				return 0;
			}
			close(writerfd);
		}
		execvp(arglist[0], arglist);
		fprintf(stderr, "Error in running first command");
		exit(1);
	}
	else{//We're in parent process
		if (background == 0){//We need to recieve SIGCHLD again and stop ignoring it
			if (sigaction(SIGCHLD, &revert_SIGCHLD, NULL) != 0){
				fprintf(stderr, "Error registering signal handle");
				return 0;
			}
		}
		if (piped){//We have a pipe, need to fork to another child
			cid[0] = pid;
			close(writerfd);
			pid = fork();
			if (pid == -1) {
				fprintf(stderr, "Error in forking");
				close(readerfd);
				return 0;;
			}
			if (pid == 0){//We're in second child process
				if (sigaction(SIGINT, &revert_interrupt, NULL) != 0){
					fprintf(stderr, "Error registering signal handle");
					return 0;
				}
				if (dup2(readerfd, 0) == -1){
					fprintf(stderr, "Error in duplicating file descriptor");
					close(readerfd);
					return 0;
				}
				close(readerfd);
				execvp(arglist[i], arglist+i);
				fprintf(stderr, "Error in running second command");
				exit(1);
			}
			else{//We're in parent process
				close(readerfd);
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
	return 0;
}
