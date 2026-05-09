#include <stdio.h>    // printf, puts
#include <stdlib.h>   // system("cls")
#include <conio.h>    // _getch
#include "list.h"     // user, g_h
#include "ui.h"

my_menu PrintMenu(void) {
	my_menu input = 0;

	system("cls");
	printf("[1]New\t[2]Search\t[3]Print\t[4]Remove\t[0]Exit\n");
	scanf_s("%d%*c", &input);
	return input;
}

void EventLoop(void) {
	my_menu menu = 0;

	while ((menu = PrintMenu()) != 0) {
		switch (menu) {
		case NEW:
			NewNode();
			break;

		case SEARCH:
			Search();
			break;

		case PRINT:
			PrintList(); // error, 위에 원형 선언!
			break;

		case REMOVE:
			break;

		default:
			break;
		}
	}
	puts("Bye~!");
}

void PrintList(void) {
	user* pTmp = &g_h;

	while (pTmp != NULL) {
		printf("New: [%p], %d, %s, %s, [pNext: %p]\n",
			pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);

		pTmp = pTmp->pNext;
	}
	puts("End of List");
	_getch();
}

void Search(void) {
	char name[32] = { 0 };
	gets_s(name, sizeof(name));

	user* pResult = SearchByName(name);

	if (pResult != NULL) {
		printf("%d, %s, %s\n",
			pResult->age, pResult->name, pResult->phone);
	}
	else
		puts("Not found\n");

	_getch();
}

void NewNode(void) {
	int age = 0;
	char name[32] = { 0 };
	char phone[32] = { 0 };

	printf("나이: ");
	scanf_s("%d%*c", &age);

	printf("이름: ");
	scanf_s("%s%*c", name, sizeof(name));

	printf("전화번호: ");
	scanf_s("%s%*c", phone, sizeof(phone));

	AddNode(age, name, phone);  // 그대로 넘김
	_getch();
}