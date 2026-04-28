#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];

	struct USERDATA* pNext;
}UD;

UD* g_h = NULL;

// Head 바로 뒤, 맨 앞 노드로 삽입.
void AddNewNode(int age, const char* pName, const char* pPhone) {
	UD* pNewNode = malloc(sizeof(UD));
	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pPhone);
	pNewNode->pNext = NULL;

	if (g_h == NULL) {
		g_h = pNewNode;
	}
	else {
		pNewNode->pNext = g_h;
		g_h = pNewNode;
	}
}

void ReleaseList(void) {
	UD* pTmp = g_h;
	UD* pDelete;
	while (pTmp != NULL) {
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		printf("Delete: [%p], %d, %s, %s, [next: %p]\n",
			pDelete, pDelete->age, pDelete->name, pDelete->phone, pDelete->pNext);

		free(pDelete);
	}
	g_h = NULL;
}

void InitDummyData(void) {
	//테스트 코드
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(7, "chul", "010-2222-2222");
	AddNewNode(12, "jjang", "010-3333-3333");
}

void printResult(void){
	UD* pTmp = g_h;
	// 다른 포인터(pTmp)를 사용하는 이유
	// g_h(Head) : '고정된 표지판' 역할. 시작 위치를 잃어버리면 안 되므로 절대 직접 움직이지 않습니다.
	// pTmp(Current) : 표지판 대신 칸을 하나씩 이동하며 확인하는 '심부름꾼'입니다.
	// 이유 : 시작점(g_h)을 이동시켜 버리면, 나중에 다시 처음부터 찾고 싶을 때 돌아갈 길을 잃어버리기 때문입니다.
	 
	 
	//1.전체적인 출력구조 구현하기.
	while (pTmp != NULL) {
		printf("New: [%p], %d, %s, %s, [next: %p]\n",
			pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);
		pTmp = pTmp->pNext;
	}
}

int main(void) {
	InitDummyData();

	printResult();
	
	ReleaseList();
	
	return 0;
}