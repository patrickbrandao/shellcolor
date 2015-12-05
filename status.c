#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "version.h"

#define _GNU_SOURCE
#include <string.h>
#include <libgen.h>

int _y_position = 63;
int _y_start = 100;
char *progname;

int usage() {
	fprintf( stderr, "%s by %s\n", progname, author);
	fprintf( stderr, "\tVersion: %d.%d\n", version, subversion);
	fprintf( stderr, "\tUsage:\n\techo_danger\n\techo_done\n\techo_failure\n\techo_started\n\techo_stopped\n\techo_success\n\techo_skip\n\techo_warnning\n");
}

int getprogcode(){
	int pc = 0;
	char *progbase;

	// tratar caminho completo
	progbase = basename (progname);

	if(!strcmp(progbase,"echo_danger")) pc = 1;
	if(!strcmp(progbase,"echo_done")) pc = 2;
	if(!strcmp(progbase,"echo_failure")) pc = 3;
	if(!strcmp(progbase,"echo_started")) pc = 4;
	if(!strcmp(progbase,"echo_stopped")) pc = 5;	
	if(!strcmp(progbase,"echo_success")) pc = 6;
	if(!strcmp(progbase,"echo_skip")) pc = 7;
	if(!strcmp(progbase,"echo_warning")) pc = 8;
	return pc;
}

int main(int argc, char *argv[]){
	progname=(char*)argv[0];

	if(argc>1){
		if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")){
			usage();
			exit(1);
		}else{
			progname = argv[1];
		}
	}
	int prog = getprogcode();

	switch(prog){
		case 1:
			printf("\033[%dD\033[%dC%s%s%s %sDANGER %s\n",_y_start,_y_position ,BPRETO, AMARELOL,BLINK, BOLD,RESET );
			break;
		case 2:
			printf("\033[%dD\033[%dC[ %s%sDONE%s ]\n",_y_start,_y_position , VERDE, BOLD,RESET );
			break;
		case 3:
			printf("\033[%dD\033[%dC%s%s%s %sFAILED %s\n",_y_start,_y_position ,BVERMELHO, BRANCO,BLINK, BOLD,RESET );
			break;
		case 4:
			printf("\033[%dD\033[%dC%s%s%s START  %s\n",_y_start,_y_position ,BVERDE, BRANCOL, BOLD,RESET );
			break;
		case 5:
			printf("\033[%dD\033[%dC%s%s  %sSTOP  %s\n",_y_start,_y_position ,BVERMELHO, BRANCOL, BOLD,RESET );
			break;
		case 6:
			printf("\033[%dD\033[%dC[ %s %sOK %s ]\n",_y_start,_y_position , VERDE, BOLD,RESET );
			break;
		case 7:
			printf("\033[%dD\033[%dC[ %s%sSKIP %s]\n",_y_start,_y_position , AZULL, BOLD,RESET );
			break;
		case 8:
			printf("\033[%dD\033[%dC%s%s%s%s  %sWARN %s\n",_y_start,_y_position ,BPRETO, AMARELOL,AMARELO,BLINK, BOLD,RESET );
			break;
		default:
			usage();
	}
	return 0;
}
