/*
setcolor:

core para colorir prompt

sintax:
    setcolor cor_texto cor_fundo

*/


#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
static void parse_args( int argc, char** argv );

//varivel para cor da fonte
int  txtcolor = 0;

// variavel para cor de fundo
int bgcolor = 0;

// flags especiais de cores de letra
// -b = negrito
// -s = sublinhado
// -p = piscante
int _text_effect = 0;
int _light = 0;

static char* argv0;

#define set_color(b)		if(cl++) bgcolor = b; else txtcolor = b


static void usage( void ) {
	(void) fprintf( stderr, "Autor: Marcio Araujo <contato@mysab.com.br>\nUsage: %s (color) (bgcolor)\n", argv0 );
	exit( 1 );
}

static void parse_args( int argc, char** argv ){
	int argn = 1;
	int cl = 0;
	while( argn < argc){

		// recebe argumentos
		if(!strcmp(argv[argn],"blue")) set_color(5);
		if(!strcmp(argv[argn],"red")) set_color(2);
		if(!strcmp(argv[argn],"green")) set_color(3);
		if(!strcmp(argv[argn],"magenta")) set_color(7);

		if(!strcmp(argv[argn],"cyan")) set_color(7);
		if(!strcmp(argv[argn],"cian")) set_color(7);

		if(!strcmp(argv[argn],"pink")) set_color(6);
		if(!strcmp(argv[argn],"yellow")) set_color(4);
		if(!strcmp(argv[argn],"white")) set_color(8);
		if(!strcmp(argv[argn],"light")) set_color(9);
		if(!strcmp(argv[argn],"black")) set_color(1);

		if(!strcmp(argv[argn],"-h") || !strcmp(argv[argn],"--help")){ usage(); }

		if(!strcmp(argv[argn],"-b")) _text_effect = 1;
		if(!strcmp(argv[argn],"-s")) _text_effect = 2;
		if(!strcmp(argv[argn],"-p")) _text_effect = 3;
		if(!strcmp(argv[argn],"-l")) _light = 1;

		++argn;
	}
    if ( argn != argc ) usage();
}

// principal
int main(int argc, char *argv[]){
	argv0 = argv[0];
	parse_args( argc, argv );
	
	if(txtcolor <= 9 && _light) txtcolor+= 9;
	// printf("txtcolor=[%d] bgcolor=[%bgcolor]\n", txtcolor, bgcolor);
	
	printf("%s%s%s",background_colors[bgcolor], effects[_text_effect], text_colors[txtcolor]);

	return(0);
}



