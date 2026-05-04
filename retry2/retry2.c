#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];

	struct USERDATA* pNext;
}user;

user g_h = { 0, "_Dummy_" };


void PrintList(void) {
	user* pTmp = &g_h;

	while (pTmp != NULL) {
		printf("New: [%p], %d, %s, %s, [pNext: %p]\n",
			pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);

		pTmp = pTmp->pNext;
	}
}


void AddNode(int age, char* pName, char* pPhone) {
	user* pNewNode = malloc(sizeof(user));

	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pPhone);

	pNewNode->pNext = NULL;

	// 맨 앞에 노드 추가(stack)
	/*pNewNode->pNext = g_h.pNext;
	g_h.pNext = pNewNode;*/

	// 맨 뒤에 노드 추가(queue)
	user* pT = &g_h;

	while (pT->pNext != NULL) {
		pT = pT->pNext;
	}
	pT->pNext = pNewNode;
}


void ReleaseNode(void) {
	user* pCur = g_h.pNext;
	user* pRel = NULL;

	while (pCur != NULL) {
		pRel = pCur;
		pCur = pCur->pNext;
		printf("Rel: [%p], %d, %s, %s, [pNext: %p]\n",
			pRel, pRel->age, pRel->name, pRel->phone, pRel->pNext);

		free(pRel);
	}
	g_h.pNext = NULL;
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


user* SearchRemoveNode(char* pName) {
	user* pPrev = &g_h;

	while (pPrev->pNext != NULL) {
		if (strcmp(pPrev->pNext->name, pName) == 0) {
			return pPrev;
		}
		pPrev = pPrev->pNext;
	}
	return NULL;
}


user* RemoveNode(user* pPrev) {
	user* pDel = NULL;

	pDel = pPrev->pNext;
	pPrev->pNext = pDel->pNext;
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

	user* pPrev = SearchRemoveNode("Dong");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	ReleaseNode();
	putchar('\n');
}

void TestStep02(void) {
	puts("TestStep02()------------------------------------------");
	AddNode(11, "Dong", "010-0000-0001");
	AddNode(9, "Chung", "010-0000-0002");
	AddNode(14, "Choi", "010-0000-0003");
	PrintList();

	user* pPrev = SearchRemoveNode("Chung");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	ReleaseNode();
	putchar('\n');
}

void TestStep03(void) {
	puts("TestStep03()------------------------------------------");
	AddNode(11, "Dong", "010-0000-0001");
	AddNode(9, "Chung", "010-0000-0002");
	AddNode(14, "Choi", "010-0000-0003");
	PrintList();

	user* pPrev = SearchRemoveNode("Choi");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	ReleaseNode();
	putchar('\n');
}


int main(void){
	TestStep01();
	TestStep02();
	TestStep03();

	
	return 0;
}