#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

void func_titulo() {
	printf("\tJOGO DA VELHA!\n\n");
}

void clearScreen() {
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void func_tabuleiro(char LETRAS[3][3]) {
	printf("\t  A   B   C\n");
	for(int i=0; i < 3; i++) {
		printf("\t%d ", i+1);
		for(int j=0; j < 3; j++) {
			printf("%c", LETRAS[i][j]);
			while (j<2) {
				printf(" | ");
				break;
			}
		}
		while (i<2) {
				printf("\n\t  ---------\n");
				break;
		}
	}
	printf("\n");
}

void func_inicializa_valores(char LETRAS[3][3]) {
	for(int i=0; i < 3; i++) {
		for(int j=0; j < 3; j++) {
			LETRAS[i][j] = '\0';		
		}    
	}
}

void func_entrada(char *COORD_LTR, int *COORD_NUM) {
	printf("\nDigite a jogada: ");
	scanf("%c%d", &(*COORD_LTR), &(*COORD_NUM));
	fflush(stdin);
	*COORD_LTR=toupper((*COORD_LTR));
	if (*COORD_LTR != 'A' && *COORD_LTR != 'B' && *COORD_LTR != 'C') {
		printf("Letra invalida, tente novamente: ");
		func_entrada(COORD_LTR, COORD_NUM);
	}
	if (*COORD_NUM < 1 || *COORD_NUM > 3) {
		printf("Numero invalido, tente novamente: ");
		func_entrada(COORD_LTR, COORD_NUM);
	}
}

void func_marcador(char LETRAS[3][3], int *CONTADOR, char *MARCADOR, char COORD_LTR, int COORD_NUM) {
	if (*CONTADOR%2==0) {
		*MARCADOR='O';
	} else {
		*MARCADOR='X';
	}
	if (LETRAS[COORD_NUM-1][COORD_LTR-65]=='\0') {
		LETRAS[COORD_NUM-1][COORD_LTR-65]=*MARCADOR;
	} else {
		do {
			printf("Ja marcado, tente novamente...\n\n");
			func_tabuleiro(LETRAS);
			func_entrada(&COORD_LTR, &COORD_NUM);
			clearScreen();
		} while (LETRAS[COORD_NUM-1][COORD_LTR-65]!='\0');
		func_marcador(LETRAS, CONTADOR, MARCADOR, COORD_LTR, COORD_NUM);
		(*CONTADOR)--;
	}
	(*CONTADOR)++;
}

bool func_ganhou(char LETRAS[3][3]) {
	int A=0, B=1, C=2;
	int N1=0, N2=1, N3=2;
	if (LETRAS[N2][B]!='\0') {
		if (LETRAS[N2][B] == LETRAS[N1][A] && LETRAS[N2][B] == LETRAS[N3][C]) {
			return true;
		}
		if (LETRAS[N2][B] == LETRAS[2][A] && LETRAS[N2][B] == LETRAS[N1][C]) {
			return true;
		}
		if (LETRAS[N2][B] == LETRAS[N2][C] && LETRAS[N2][B] == LETRAS[N2][A]) {
			return true;
		}
		if (LETRAS[N2][B] == LETRAS[N1][B] && LETRAS[N2][B] == LETRAS[N3][B]) {
			return true;
		}
	}
	if (LETRAS[N3][A]!='\0') {
		if (LETRAS[N3][A] == LETRAS[N3][B] && LETRAS[N3][A]  == LETRAS[N3][C]) {
			return true;
		}
		if (LETRAS[N3][A] == LETRAS[N2][A] && LETRAS[N3][A]  == LETRAS[N1][A]) {
			return true;
		}
	}
	if (LETRAS[N1][C]!='\0') {
		if (LETRAS[N1][C] == LETRAS[N2][C] && LETRAS[N1][C]  == LETRAS[N3][C]) {
			return true;
		}
		if (LETRAS[N1][C] == LETRAS[N1][A] && LETRAS[N1][C]  == LETRAS[N1][B]) {
			return true;
		}
	}
	return false;
}

void func_resultado(bool GANHADOR, char MARCADOR) {
	if (GANHADOR==true) {
		switch (MARCADOR) {
			case 'O': {
				printf("\nO ganhador foi a bolinha!\n\n");
				break;			
			}
			case 'X': {
				printf("\nO ganhador foi a cruz!\n\n");
				break;
			}
		}	
	} else {
		printf("\nDeu velha!\n\n");
	}	
	system("pause");
}

void func_imprime_jogada(int CONTADOR, char COORD_LTR, int COORD_NUM) {
	char MARCADOR_1[10], MARCADOR_2[10];
	if (CONTADOR%2==0) {
		strcpy(MARCADOR_1, "CRUZ");
		strcpy(MARCADOR_2, "BOLINHA");
	} else {
		strcpy(MARCADOR_1, "BOLINHA");
		strcpy(MARCADOR_2, "CRUZ");
	}
	printf("%d | %s JOGOU %c%d, QUEM JOGA AGORA E: %s\n\n", CONTADOR, MARCADOR_1, COORD_LTR, COORD_NUM, MARCADOR_2);
}

main () {
	char LETRAS[3][3]; char COORD_LTR; int COORD_NUM;
	int CONTADOR=0; char MARCADOR; bool GANHADOR;
	
	func_titulo();
	func_inicializa_valores(LETRAS);
	func_tabuleiro(LETRAS);
	do {
		func_entrada(&COORD_LTR, &COORD_NUM);
		clearScreen();
		func_marcador(LETRAS, &CONTADOR, &MARCADOR, COORD_LTR, COORD_NUM);
		func_imprime_jogada(CONTADOR, COORD_LTR, COORD_NUM);		
		func_tabuleiro(LETRAS);
		GANHADOR = func_ganhou(LETRAS);
	} while (CONTADOR<9 && GANHADOR==false);
	func_resultado(GANHADOR, MARCADOR);
}
