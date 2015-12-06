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

// espacamento
int _left_space = 0;
int _right_space = 0;

// conversao de strings
int _convert_case = 0; 	// 0 = nao alterar case, 1=upper, 2=lower

// conversao para formato numerico
int _to_number_format = 0;		// 0=nao interpretar numero, 2=converter para formato numerico, exemplo: 123456 para 123.456

static char* argv0;

#define set_color(b)		if(cl) bgcolor = b; else txtcolor = b


static void usage( void ) {
	fprintf( stderr, "Autor: Marcio Araujo <contato@mysab.com.br>\nUsage:  %s -c (color) -b (bgcolor) [-n] [-l] [-B] [-s] [-p] [-k] [-N] TEXT\n", argv0 );
	fprintf( stderr, "\t-B				bold text\n");
	fprintf( stderr, "\t-s				sublinhed text\n");
	fprintf( stderr, "\t-l				light text\n");
	fprintf( stderr, "\t-n 				don't break line after\n");
	fprintf( stderr, "\t-k				keep colors after print text\n");
	fprintf( stderr, "\t-p				blink text\n");
	fprintf( stderr, "\t-L (number)		padding left spaces\n");
	fprintf( stderr, "\t-R (number)		padding right spaces\n");
	fprintf( stderr, "\t-N				number format\n");
	fprintf( stderr, "\t-Y				convert to uppercase\n");
	fprintf( stderr, "\t-W				convert to lowercase\n");
	fprintf( stderr, "\t-c (color)		text color\n");
	fprintf( stderr, "\t-b (color)		background color\n");
	fprintf( stderr, "Colors list:\n");
	fprintf( stderr, "\tblue, red, green, magenta, cyan, pink, yellow, white, light, black, gray\n");
	exit( 1 );
}

/*
blue
red
green
magenta
cyan
cian
pink
yellow
white
light
black


*/

#define TEST_COLOR(TEXT, VALUE)			if(0==strcmp(argv[argn],TEXT)){ argn++; set_color(VALUE); continue; }
static void parse_args( int argc, char** argv ){
	int argn = 1;
	int cl = 0;
	while( argn < argc){

		// recebe argumentos
		cl = 0;

		// opcoes multi-parametros
		if(0==strcmp(argv[argn],"-c") || 0==strcmp(argv[argn],"-b")){
			if(0==strcmp(argv[argn],"-b")) cl=1;

			if(argn < argc) argn++; else continue;

			TEST_COLOR("blue", 5);
			TEST_COLOR("azul", 5);

			TEST_COLOR("red", 2);
			TEST_COLOR("vermelho", 2);

			TEST_COLOR("green", 3);
			TEST_COLOR("verde", 3);

			TEST_COLOR("magenta", 7);
			TEST_COLOR("celeste", 7);
			TEST_COLOR("cyan", 7);
			TEST_COLOR("cian", 7);

			TEST_COLOR("pink", 6);
			TEST_COLOR("rosa", 6);

			TEST_COLOR("yellow", 4);
			TEST_COLOR("amarelo", 4);

			TEST_COLOR("white", 8);
			TEST_COLOR("light", 9);
			TEST_COLOR("black", 1);

			TEST_COLOR("gray", 10);
			TEST_COLOR("cinza", 10);

			argn++;
		}

		// definicao de espacamento
		// ESQUERDA
		if(strcmp(argv[argn],"-L") ==0 ){
			if(argn < argc) argn++; else continue;	
			// tamanho do espaco para alinhar a esquerda
			_left_space = atoi(argv[argn++]);
			if(_left_space < 0) _left_space = 0;
			continue;
		}
		// DIREITA
		if(strcmp(argv[argn],"-R") ==0 ){
			if(argn < argc) argn++; else continue;	
			// tamanho do espaco para alinhar a esquerda
			_right_space = atoi(argv[argn++]);
			if(_right_space < 0) _right_space = 0;
			continue;
		}

		// opcoes singulares
		if(0==strcmp(argv[argn],"-h") || 0==strcmp(argv[argn],"--help")){ usage(); }
		if(0==strcmp(argv[argn],"-B")){ _text_effect = 1; ++argn; continue; }
		if(0==strcmp(argv[argn],"-s")){ _text_effect = 2; ++argn; continue; }
		if(0==strcmp(argv[argn],"-p")){ _text_effect = 3; ++argn; continue; }
		if(0==strcmp(argv[argn],"-l")){ _light = 1; ++argn; continue; }

		if(0==strcmp(argv[argn],"-n")){ _do_break = 2; ++argn; continue; }
		if(0==strcmp(argv[argn],"-k")){ _do_reset = 0; ++argn; continue; }

		// number
		if(0==strcmp(argv[argn],"-N")){ _to_number_format = 1; ++argn; continue; }

		// upper
		if(0==strcmp(argv[argn],"-Y")){ _convert_case = 1; ++argn; continue; }

		// lower
		if(0==strcmp(argv[argn],"-W")){ _convert_case = 2; ++argn; continue; }

		// texto
		if(strlen(argv[argn])) _output_string = (char *)argv[argn];

		++argn;
	}
    if ( argn != argc ) usage();
}

// principal
#define BIGINT unsigned long long int
int main(int argc, char *argv[]){
	register int outlen = 0;
	register int k, m, n;
	register int total;
	char *workmem = NULL, *newoutput = NULL;
	int needfree = 0;
	int alocsize = 0;

	argv0 = argv[0];
	_output_string = (char) 0;

	// processar argumentos do usuario
	parse_args( argc, argv );

	if(txtcolor <= 9 && _light) txtcolor+= 9;
	// printf("txtcolor=[%d] bgcolor=[%bgcolor]\n", txtcolor, bgcolor);

	// Definir coloracao
	printf("%s%s%s",background_colors[bgcolor], effects[_text_effect], text_colors[txtcolor]);

	// tamanho do texto de saida
	if(_output_string) outlen = strlen(_output_string);

	// temos conteudo para mostrar?
	if(outlen){

		// formatar case?
		if(_convert_case == 1){
			// upper
			for(k=0; k < outlen; k++) _output_string[k] = toupper(_output_string[k]);
		}else if(_convert_case == 2){
			// lower
			for(k=0; k < outlen; k++) _output_string[k] = tolower(_output_string[k]);
		}

		// temos que alinhar ou formatar? precisamos copiar
		if(_right_space || _left_space || _to_number_format){

			// tamanho total do buffer, exagerar um pouco
			// - espaco para a string
			// - espaco para padding left e right
			// - espaco para formatacao de numeros
			// - um pouquinho mais
			total = outlen + _left_space + _right_space + (outlen > 3 ? outlen / 3 + 1 : 1) + 2;
			alocsize = total * sizeof(char);

			// alocar copia
			newoutput = malloc(alocsize); bzero(newoutput, alocsize);
			if(_to_number_format) workmem = malloc(alocsize); bzero(workmem, alocsize);
			needfree = 1;

			//strncpy(newoutput, _output_string, total);

		}

		// formatar numero?
		if(_to_number_format && outlen){
			int newlen = 0;
			int rest = outlen;

			// copiar apenas numeros, invertendo
			n = 0;
			for(m=outlen-1; m >= 0; m--){
				char x = _output_string[m];
				if(isdigit(x)) newoutput[newlen++] = x;
			}

			// nenhum numero?
			if(!newlen) newoutput[newlen++] = '0';

			// limpar output-string
			bzero(_output_string, outlen);

			// copiar de volta para output-string invertida
			for(m=0; m <= newlen; m++) _output_string[m] = newoutput[m];

			// limpar nova output
			bzero(newoutput, newlen);

			// temos apenas os numeros invertidos, escreve-los com pontos
			k = 0;
			n = 1;
			for(m = 0; m < newlen; m++){
				workmem[k++] = _output_string[m];
				if(n == 3){
					n = 0;
					if(m + 1 < newlen) workmem[k++] = '.';
				}
				n++;
			}
			newlen = k;

			// inverter novamente
			k = 0;
			for(m = newlen-1; m >=0; m--) newoutput[k++] = workmem[m];

			// pronto
			_output_string = newoutput;
			outlen = newlen;

		}else if(_to_number_format){

			// nao informou nada no parametro, mas quer numero, toma um ZERO
			printf("0");

		}

		// temos que alinhar?
		if(outlen && (_right_space || _left_space)) {

			// tamanho total do buffer, exagerar um pouco
			register int total = outlen+_left_space+_right_space;

			// criar buffer para alocacao do texto, +2 para evitar problemas
			register int buflen = total + 2;
			char *_output;

			// alocar com preenchimento zero
			bzero(workmem, alocsize);
			_output = calloc(buflen, sizeof(char) * buflen);

			if(workmem!=NULL){
				register int offset = _left_space;	// bytes saltar
				register int maxwrites = outlen;

				// Preencher buffer com espacos
				for(k=0; k < buflen; k++)
					workmem[k] = ' ';
				//-

				// Direita ou esquerda?
				if(_right_space){
					// DIREITA

					// buffer termina no limite
					workmem[_right_space] = 0;

					// tamanho do texto nao pode ser maior que o espacamento
					maxwrites = _right_space;

					// copiar texto
					for(k=0, m=0; m < maxwrites && m < outlen; k++) workmem[k] = _output_string[m++];

				}else{
					// ESQUERDA

					// buffer termina no limite
					workmem[_left_space] = 0;

					// espacos a esquerda
					offset = _left_space - outlen;
					// caso o texto senha maior, teremos que pica-lo
					if(offset < 0){ offset = 0; maxwrites = _left_space; }

					for(k=offset, m=0; m < maxwrites && m < outlen; k++) workmem[k] = _output_string[m++];

				}

				// imprimir buffer na saida
				printf("%s", workmem);

			}
			// else{ PROBLEMA NA PORCARIA DA MEMORIA }

		}else{

			// nenhuma formatacao exigida, apenas jogar na tela
			printf("%s", _output_string);

		}
	}

	// resetar cor
	if(_do_reset)
		printf("%s%s",background_colors[0],text_colors[0]);
	//-

	// quebra final de linha
	if(1==_do_break)
		printf("\n");
	//-

	// liberar memoria alocada nas formatacoes
	if(needfree){
		if(workmem != NULL) free(workmem);
		if(newoutput != NULL) free(newoutput);
	}

	return 0;

}
































