#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];

	struct USERDATA* pPrev;
	struct USERDATA* pNext;
}user;

user g_h = { 0, "_Head_" };
user g_t = { 0, "_Tail_" };


void PrintList(void) {
	user* pTmp = &g_h;

	while (pTmp != &g_t) {
		printf("New: [%p], %d, %s, %s, [pNext: %p]\n",
			pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);

		pTmp = pTmp->pNext;
	}
}


void InitList(void) {
	g_h.pNext = &g_t;
	g_t.pPrev = &g_h;
}


void AddNode(int age, char* pName, char* pPhone) {
	user* pNewNode = malloc(sizeof(user));

	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pPhone);

	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;
	
	user* pPrevNode = g_t.pPrev;

	pNewNode->pNext = &g_t;
	pNewNode->pPrev = g_t.pPrev;
	g_t.pPrev->pNext = pNewNode;
	g_t.pPrev = pNewNode;
}


void ReleaseNode(void) {
	user* pCur = g_h.pNext;
	user* pRel = NULL;

	while (pCur != &g_t) {
		pRel = pCur;
		pCur = pCur->pNext;
		printf("Rel: [%p], %d, %s, %s, [pNext: %p]\n",
			pRel, pRel->age, pRel->name, pRel->phone, pRel->pNext);

		free(pRel);
	}
	InitList();
}


user* SearchByName(char* pName) {
	user* pCur = g_h.pNext;

	while (pCur != NULL) {
		if (strcmp(pCur->name, pName) == 0) {
			printf("\"%s\": Found\n", pName);
			return pCur;
		}
		pCur = pCur->pNext;
	}
	printf("\"%s\": Not found\n", pName);
	return NULL;
}


void RemoveNode(user* pDel) {
	user* pPrev = pDel->pPrev;
	user* pNext = pDel->pNext;

	pPrev->pNext = pDel->pNext;
	pNext->pPrev = pDel->pPrev;

	printf("Del: %s\n", pDel->name);
	free(pDel);
}


void Dummy(void) {
	AddNode(11, "Dong", "010-0000-0001");
	AddNode(9, "Chung", "010-0000-0002");
	AddNode(14, "Choi", "010-0000-0003");
}


void TestStep01(void) {
	puts("TestStep01()------------------------------------------");
	AddNode(11, "Dong", "010-0000-0001");
	AddNode(9, "Chung", "010-0000-0002");
	AddNode(14, "Choi", "010-0000-0003");
	PrintList();

	user* pRemove = SearchByName("Dong");
	if (pRemove != NULL)
		RemoveNode(pRemove);
	ReleaseNode();
	putchar('\n');
}

void TestStep02(void) {
	puts("TestStep02()------------------------------------------");
	AddNode(11, "Dong", "010-0000-0001");
	AddNode(9, "Chung", "010-0000-0002");
	AddNode(14, "Choi", "010-0000-0003");
	PrintList();

	user* pRemove = SearchByName("Chung");
	if (pRemove != NULL)
		RemoveNode(pRemove);
	ReleaseNode();
	putchar('\n');
}

void TestStep03(void) {
	puts("TestStep03()------------------------------------------");
	AddNode(11, "Dong", "010-0000-0001");
	AddNode(9, "Chung", "010-0000-0002");
	AddNode(14, "Choi", "010-0000-0003");
	PrintList();

	user* pRemove = SearchByName("Choi");
	if (pRemove != NULL)
		RemoveNode(pRemove);
	ReleaseNode();
	putchar('\n');
}


int main(void) {
	InitList();
	TestStep01();
	TestStep02();
	TestStep03();


	return 0;
}