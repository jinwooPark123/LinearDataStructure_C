#include <stdio.h>
#include <stdlib.h>

void AddNewData(void);

typedef enum MY_MENE { EXIT, NEW, SEARCH, PRINT, REMOVE } my_menu; 

my_menu PrintMenu(void) {
	my_menu input = 0;

	system("cls");
	printf("[1]New\t[2]Search\t[3]Print\t[4]Remove\t[0]Exit\n");
	scanf_s("%d%*c", &input);
	return input;
}

int main(void) {
	my_menu menu = 0;

	while ((menu = PrintMenu()) != 0) {
		switch (menu) {
			case NEW:
				AddNewData();
				break;

			case SEARCH:
				break;

			case PRINT:
				break;

			case REMOVE:
				break;

			default:
				break;
		}
	}
	puts("Bye~!");

	return 0;
}