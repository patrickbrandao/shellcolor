
/*
\033[x;yH     posiciona o cursor na linha x, coluna y
\033[xA       move o cursor x linhas para cima
\033[xB       move o cursor x linhas para baixo
\033[yC       move o cursor y colunas para a direita
\033[yD       move o cursor y colunas para a esquerda
*/


// ANSI-Cores
#define		 RESET		"\033[00m"	//0
#define		 VAZIO		""			// NULL

#define		CLRSCR		"\033c"		// limpar a tela

// FORMATACAO
#define		 BOLD		"\033[1m" 	// negrito
#define		 SUBT		"\033[4m" 	// sublinhado
#define		 BLINK		"\033[5m" 	// piscando


// TEXT COLOR
#define 	PRETO		"\033[30m"	//1
#define 	VERMELHO	"\033[31m"	//2
#define 	VERDE		"\033[32m"	//3
#define 	AMARELO		"\033[33m"	//4
#define 	AZUL		"\033[34m"	//5
#define 	ROSA		"\033[35m"	//6
#define 	CIANO		"\033[36m"	//7
#define 	BRANCO		"\033[39m"	//8
#define 	LIGHT		"\033[38m"	//9

// TEXT COLOR LIGHT
#define 	PRETOL		"\033[90m"	//10
#define 	VERMELHOL	"\033[91m"	//11
#define 	VERDEL		"\033[92m"	//12
#define 	AMARELOL	"\033[93m"	//13
#define 	AZULL		"\033[94m"	//14
#define 	ROSAL		"\033[95m"	//15
#define 	CIANOL		"\033[96m"	//16
#define 	BRANCOL		"\033[99m"	//17


// BACKGROUD
#define 	BPRETO		"\033[40m"	//1
#define 	BVERMELHO	"\033[41m"	//2
#define 	BVERDE		"\033[42m"	//3
#define 	BLARANJA	"\033[43m"	//4
#define 	BAZUL		"\033[44m"	//5
#define 	BROSA		"\033[45m"	//6
#define 	BCIANO		"\033[46m"	//7
#define 	BBRANCO		"\033[47m"	//8
#define 	BLIGHT		"\033[48m"	//9

// BACKGROUD
#define 	BPRETO		"\033[40m"	//1
#define 	BVERMELHO	"\033[41m"	//2
#define 	BVERDE		"\033[42m"	//3
#define 	BLARANJA	"\033[43m"	//4
#define 	BAZUL		"\033[44m"	//5
#define 	BROSA		"\033[45m"	//6
#define 	BCIANO		"\033[46m"	//7
#define 	BBRANCO		"\033[47m"	//8
#define 	BLIGHT		"\033[48m"	//9

char *text_colors[] = {
	RESET,
	PRETO,
	VERMELHO,
	VERDE,
	AMARELO,
	AZUL,
	ROSA,
	CIANO,
	BRANCO,
	LIGHT,
	PRETOL,
	VERMELHOL,
	VERDEL,
	AMARELOL,
	AZULL,
	ROSAL,
	CIANOL,
	BRANCOL
};

char *background_colors[] = {RESET,
	BPRETO,
	BVERMELHO,
	BVERDE,
	BLARANJA,
	BAZUL,
	BROSA,
	BCIANO,
	BBRANCO,
	BLIGHT
};

char *effects[] = {
	VAZIO,
	BOLD,
	SUBT,
	BLINK
};
