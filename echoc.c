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

#define MY_MALLOC(PTR, MEMSIZE)		PTR = malloc(MEMSIZE+1); if(PTR){ bzero(PTR, MEMSIZE+1); }else exit(1);
#define MY_STRDUP(PTR, STR)			MY_MALLOC(PTR, strlen(STR) * sizeof(char) + 1); strcpy(PTR, STR)

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
		if(strlen(argv[argn])) _output_string = strdup(argv[argn]);

		++argn;
	}
    if ( argn != argc ) usage();
}

#define STR_EXIST_OR_RETURN(STR)	if(!STR || !STR[0]) return

// inverter uma string
void str_reverse(char *str){
	char *buf = NULL;
	register int len, i;
	register int total;

	// nada a fazer
	STR_EXIST_OR_RETURN(str);

	// tamanho da string
	len = strlen(str);

	// nao da pra inverter 1 byte ne!
	if(len <= 2) return;

	// alocar
	total = (len+1) * (sizeof(char)) + 1;
	MY_MALLOC(buf, total);

	// inverter
	for(i=0; i < len; i++) buf[i] = str[len-i-1];

	// copiar de volta pro original
	for(i=0; i < len; i++) str[i] = buf[i];
}

// preencher ponteiro com espacos
void bspace(char *ptr, int size){
	register int i;
	for(i=0; i<size;i++) ptr[i] = ' ';
}

// retirar todos os caracteres nao-numericos
void str_only_numbers(char *str){
	register int len = 0, k = 0, i = 0;
	// nada a fazer
	STR_EXIST_OR_RETURN(str);
	len = strlen(str);
	for(i = 0; i < len; i++){
		if(isdigit(str[i]))
			str[k++] = str[i];
		//-
	}
	// apagar o resto
	for(i = k; i < len; i++) str[i] = 0;
}

// depurar espaco de memoria
void str_mem_debug(char *ptr, int size){
	register int i, j=0;
	printf("STRING DEBUG, LEN (%d) SIZE (%d):\n", strlen(ptr), size);
	for(i=0; i< size; i++){
		printf("[%c] %h", ptr[i] ? ptr[i] : '?', ptr[i]);
		if(j++==40){ printf("\n"); j = 0; }
	}
	printf("\n\n");
}

// formatar numero, entrada: 1234 saida 1.234
char *str_number_format(const char *input){
	register int alocsize = 0, inputlen = 0;
	register int newlen = 0, k, m, n;
	char *ret = NULL, *workspace = NULL;

	// nada a fazer
	if(!input || !input[0]) return ret;

	// tamanho da entrada
	inputlen = strlen(input);
	if(inputlen < 4){
		// nada a fazer, duplicar e retornar
		MY_STRDUP(ret, input);
		return ret;
	}

	// tamanho da string para trabalho
	alocsize = (inputlen * sizeof(char)) + (inputlen > 3 ? inputlen / 3 : inputlen) + 3;

	// alocar espaco para retorno e gerar copia local
	MY_MALLOC(ret, alocsize);
	MY_MALLOC(workspace, alocsize);
	strcpy(ret, input);

	// apenas numeros sao permitidos
	str_only_numbers(ret);

	newlen = strlen(ret);
	if(!newlen++) sprintf(ret, "0");

	// inverter ordem
	str_reverse(ret);

	// temos apenas os numeros invertidos, escreve-los com pontos
	k = 0;
	n = 1;
	for(m = 0; m < newlen; m++){
		workspace[k++] = ret[m];
		if(n++ == 3){ n = 0; if( m+2 < newlen) workspace[k++] = '.'; }
	}
	// inverter novamente
	str_reverse(workspace);
	return workspace;
}

// converter para maiusculas
void str_to_upper(char *str){
	char *_str;
	register int i, len;
	register int k;
	STR_EXIST_OR_RETURN(str);
	len = strlen(str);
	if(len)
		for(i=0; i < len; i++)
			str[i] = toupper(str[i]);
	//-
}

// converter para minusculas
void str_to_lower(char *str){
	char *_str;
	register int i, len;
	register int k;
	STR_EXIST_OR_RETURN(str);
	len = strlen(str);
	if(len)
		for(i=0; i < len; i++)
			str[i] = tolower(str[i]);
	//-
}

// colocar espacos a esquerda do texto
char *str_pad_left(const char *input, int space){
	char *ret = NULL;
	register int i, len, offset = 0, idx = 0;

	// espaco necessario (space + 1)
	MY_MALLOC(ret, space + 1);

	// preencher com espacos que vamos utilizar
	bspace(ret, space);

	// usuario nao passou nada
	// facil retornar apenas espacos
	if(!input || !input[0]) return ret;

	// tamanho do texto
	len = strlen(input);

	offset = space - len;
	if(offset < 0) offset = 0;

	// copiar por cima dos espacos, respeitando limites
	for(i=offset; i < space; i++) ret[i] = input[idx++];

	return ret;
}

// colocar espacos a direita do texto
char *str_pad_right(const char *input, int space){
	char *ret = NULL;
	register int i, len;

	// espaco necessario (space + 1)
	MY_MALLOC(ret, space + 1);

	// preencher com espacos que vamos utilizar
	bspace(ret, space);

	// usuario nao passou nada
	// facil retornar apenas espacos
	if(!input || !input[0]) return ret;

	// copiar texto dentro do limite
	len = strlen(input);
	if(len > space) len = space;
	for(i = 0; i < len; i++) ret[i] = input[i];

	// str_mem_debug(ret, space);
	return ret;
}

// principal
#define BIGINT unsigned long long int
int main(int argc, char *argv[]){
	// variaveis
	register int outlen = 0;

	// inits
	argv0 = argv[0];
	_output_string = (char) 0;

	// processar argumentos do usuario
	parse_args( argc, argv );


	// Definir coloracao
	if(txtcolor <= 9 && _light) txtcolor+= 9;
	printf("%s%s%s",background_colors[bgcolor], effects[_text_effect], text_colors[txtcolor]);

	// Processar texto de entrada
	if(_output_string) outlen = strlen(_output_string);

	// formatar case?
	if(outlen && _convert_case){
		if(_convert_case == 1) str_to_upper(_output_string);	// Maiusculas
		if(_convert_case == 2) str_to_lower(_output_string);	// Minusculas
	}

	// apenas numeros? formatar
	if(_to_number_format){
		_output_string = str_number_format(_output_string);		// de 1234 para 1.234
		outlen = strlen(_output_string);
	}

	// fazer padding?
	if(_left_space){
		_output_string = str_pad_left(_output_string, _left_space);
	}else if(_right_space){
		_output_string = str_pad_right(_output_string, _right_space);
	}

// FINALIZAR -------------------------------------------------------------------------

	// jogar saida
	printf("%s", _output_string);

	// resetar cor
	if(_do_reset)
		printf("%s%s",background_colors[0],text_colors[0]);
	//-

	// quebra final de linha
	if(1==_do_break)
		printf("\n");
	//-

	// liberar memoria alocada nas formatacoes
	// MY_FREE();

	return 0;




}
































