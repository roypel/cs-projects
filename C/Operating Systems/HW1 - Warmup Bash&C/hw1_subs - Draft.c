//TODO: Check file size, make appropiate buffer, read to buffer all input file, change strings in buffer, write buffer to stdout
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void changeStrings (char *buf, char *from, char *to){
	char *pos = buf;
	while ((pos = strstr(pos, from)) != NULL){
		while (buf != pos){// Print from last point to current point
			printf("%c", *buf);
			buf++;
		}
		printf("%s", to);
		pos+= strlen(from);
		buf = pos;
	}
	printf("%s", buf); // Print rest of string untill the end
}


int main (int argc, char* argv[]){
	assert(argc == 2 || argc == 3);
	const char *dir = getenv("HW1DIR");
	if (dir == NULL){
		printf("HW1DIR Not defined!");
		return 1;
	}
	const char *tf = getenv("HW1TF");
	if (tf == NULL){
	        printf("HW1TF Not defined!");
	        return 1;
	}
	int pathLength = strlen(dir) + strlen(tf) + 2;// Add +1 for '/' and +1 for '\0' at the end
	//const char *path = malloc(pathLength * sizeof(char));
	//if (path == NULL){
	//	printf("Error allocating memory!");
	//	return 1;
	//}
	char *buf = (char *) malloc(pathLength * sizeof(char));
    if (buf == NULL){
        printf("Error allocating memory!");
	    free(buf);
        return 1;
    }
	strcpy(buf, dir);
	strcat(buf, "/");
	strcat(buf, tf);
	//buf[pathLength - 1] = '\0';
	/*if (buf == NULL){
		printf("Error combining path!");
		free(buf);
		return 1;
	}*/
	//const char* path = buf;
	int pos = open(buf, O_RDONLY);
	if (pos < 0){
		printf("Error opening file!");
		free(buf);
		return 1;
	}
	struct stat fileInfo;
	if (fstat(pos, &fileInfo) == -1){
		printf("Error using fstat on file");
		free(buf);
		return 1;
	}
	free(buf);
	int fileSize = fileInfo.st_size + 1;// Add 1 for closing '\0'
	buf = (char *) malloc(fileSize * sizeof(char));
	if (buf == NULL){
		printf("malloc has failed");
		free(buf);
		return 1;
	}
	
	/*int move = strlen(argv[1]);
	buf = (char *) malloc(fileSize * sizeof(char));
	if (buf == NULL){
		printf("malloc has failed");
		return 1;
	}*/
	ssize_t numRead;
/*	while ((numRead = read(pos, buf, move)) > 0){
		if (!strcmp
	}
	*/
	while ((numRead = read(pos, buf, fileSize)) > 0);// Read whole file to buffer
	if (numRead == -1){
		printf("Error reading from file");
		free(buf);
		close(pos);
		return 1;
	}
	buf[fileSize - 1] = '\0';
	if (argc == 3)
		changeStrings(buf, argv[1], argv[2]);
	else
		changeStrings(buf, argv[1], "");
	free(buf);	
		//while ((numWrite = numWrite - fwrite(buf, sizeof(char), numWrite, stdout)) < 0){
		//printf(buf);
		
	if (close(pos) < 0){
		printf("Error closing file!");
		return 1;
	}
	return 0;
}

