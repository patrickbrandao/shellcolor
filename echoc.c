/*
setcolor:

core para colorir prompt

sintax:
    setcolor cor_texto cor_fundo

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// texto e opcoes
char *_output_string;

// quebrar linha apos exibir texto
int _do_break = 1;

// resetar cores do terminal apos terminar
int _do_reset = 1;

static char* argv0;

#define set_color(b)		if(cl) bgcolor = b; else txtcolor = b


static void usage( void ) {
	fprintf( stderr, "Autor: Marcio Araujo <contato@mysab.com.br>\nUsage:  %s -c (color) -b (bgcolor) [-n] [-l] [-B] [-s] [-p] [-k] TEXT\n", argv0 );
	fprintf( stderr, "\t-B = bold text\n");
	fprintf( stderr, "\t-s = sublinhed text\n");
	fprintf( stderr, "\t-l = light text\n");
	fprintf( stderr, "\t-n = don't break line after\n");
	fprintf( stderr, "\t-k = keep colors after print text\n");
	fprintf( stderr, "\t-p = blink text\n");
	exit( 1 );
}

static void parse_args( int argc, char** argv ){
	int argn = 1;
	int cl = 0;
	while( argn < argc){

		// recebe argumentos
		cl = 0;
		if(!strcmp(argv[argn],"-c") || !strcmp(argv[argn],"-b")){
			if(!strcmp(argv[argn],"-b")) cl=1;

			if(argn < argc) argn++; else continue;
		
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
			argn++;
			continue;
		}

		if(!strcmp(argv[argn],"-h") || !strcmp(argv[argn],"--help")){ usage(); }
		if(!strcmp(argv[argn],"-B")){ _text_effect = 1; ++argn; continue; }
		if(!strcmp(argv[argn],"-s")){ _text_effect = 2; ++argn; continue; }
		if(!strcmp(argv[argn],"-p")){ _text_effect = 3; ++argn; continue; }
		if(!strcmp(argv[argn],"-l")){ _light = 1; ++argn; continue; }

		if(!strcmp(argv[argn],"-n")){ _do_break = 2; ++argn; continue; }
		if(!strcmp(argv[argn],"-k")){ _do_reset = 0; ++argn; continue; }


		// texto
		if(strlen(argv[argn])) _output_string = (char *)argv[argn];

		++argn;
	}
    if ( argn != argc ) usage();
}

// principal
int main(int argc, char *argv[]){
	argv0 = argv[0];
	_output_string = (char) 0;

	parse_args( argc, argv );
	
	if(txtcolor <= 9 && _light) txtcolor+= 9;
	// printf("txtcolor=[%d] bgcolor=[%bgcolor]\n", txtcolor, bgcolor);
	
	printf("%s%s%s",background_colors[bgcolor], effects[_text_effect], text_colors[txtcolor]);

	if(_output_string && strlen(_output_string)) printf("%s", _output_string);

	// printf("%s%s",background_colors[bgcolor],text_colors[txtcolor]);
	
	// resetar cor
	if(_do_reset) printf("%s%s",background_colors[0],text_colors[0]);

	// quebra final de linha
	if(1==_do_break) printf("\n");

	return(0);
}
