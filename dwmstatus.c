#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <X11/Xlib.h>
#include "config.h"

#define REFRESHRATE 1000 /* Refreshrate in miliseconds */
/* Although the refreshrate is adjustable the variable time_1000ms is still named like that
 * and the comment in the config file is not automatically adjusted */


static Window root;
static Display *dpy;
static int screen;

int init_x(){
	dpy = XOpenDisplay(NULL);
	if(!dpy){
		printf("dwmstatus: Failed to open Display! Aborting...\n");
		return -1;
	}
	screen = DefaultScreen(dpy);
	root = RootWindow(dpy, screen);
	return 1;
}

void *execute_block(void *arg){
	struct block *block = (struct block*)arg;
	FILE *pipe;

	pipe = popen(block->command, "r");
	/* check if it worked */
	if (pipe == NULL){
		perror("pipe");
		exit(1);
	}

	fgets(block->result, block->result_l, pipe);
	block->result[strlen(block->result)-1] = '\0';

	pclose(pipe);
	return NULL;
}

void execute_scripts(int time_1000ms){
	pthread_t tid;
	int i = 0;
	for(i = 0; i < sizeof(blocks)/sizeof(struct block); i++){
		if(time_1000ms % blocks[i].repitition == 0)
			pthread_create(&tid, NULL, execute_block, (void *)&blocks[i]);
	}
}

int main(){
	char *output = malloc(1000);
	char *output_pr = malloc(1000);
	output_pr[0] = '\0';
	int i;
	long long time_1000ms = 0;
	struct timespec ts;

	if(!init_x())
		return -1;

	ts.tv_sec = REFRESHRATE / 1000;
	ts.tv_nsec = (REFRESHRATE % 1000) * 1000000;
 
	for(i = 0; i < sizeof(blocks)/sizeof(struct block); i++){
		blocks[i].result = malloc(1000);
		blocks[i].result_l = 1000;
	}

	while(1){
		execute_scripts(time_1000ms);
		sleep(1);
	//	if(nanosleep(&ts, &ts)){
	//		printf("Sleep Function failed... Aborting! (nanosleep, main, dwmstatus.c)");
	//		return false;
	//	}
	//	strcpy(output, "xsetroot -name \"");

		for(i = 0; i < sizeof(blocks)/sizeof(struct block); i++){
			if(delim_empty || blocks[i].result[0]!= '\0')
				strcat(output, blocks[i].delim);
			if(delim_global_empty || blocks[i].result[0]!= '\0')
				strcat(output, delim_global);
			strcat(output, blocks[i].result);
		}

		if(strcmp(output_pr, output)){
			XStoreName(dpy, root, output);
			XFlush(dpy);
			strcpy(output_pr, output);
		}
	//	strcat(output, "\"");
		printf("%s\n", output);
	//	system(output);
		strcpy(output_pr, output);
		strcpy(output, "\0");
		time_1000ms++;
	}
}
