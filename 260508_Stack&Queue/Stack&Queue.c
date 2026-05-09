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

	while (pTmp != NULL) {
		printf("New: [%p], %d, %s, %s, [pNext: %p]\n",
			pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);

		pTmp = pTmp->pNext;
	}
	putchar('\n');
}

void InitList(void) {
	g_h.pNext = &g_t;
	g_t.pPrev = &g_h;
}
// 기능적으로 이미 queue 구현
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


int IsEmpty(void) {
	if (g_h.pNext == &g_t)
		return 1;

	return 0;
}

void Push(user* pUser) {
	user* pNewNode = malloc(sizeof(user));
	memcpy_s(pNewNode,sizeof(user), pUser, sizeof(user));
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	user* pNextNode = g_h.pNext;

	pNewNode->pNext = g_h.pNext;
	pNewNode->pPrev = &g_h;
	g_h.pNext->pPrev = pNewNode;
	g_h.pNext = pNewNode;
}

user* Pop(void) {
	if (IsEmpty()) {
		puts("Error: Stack underflow.");
		return NULL;
	}
	
	user* pPop = g_h.pNext; 
	g_h.pNext = pPop->pNext;
	
	pPop->pNext->pPrev = &g_h;
	
	return pPop;
}

user* Dequeue(void) {
	return Pop();
}

void Enqueue(user* pUser) {
	AddNode(pUser->age, pUser->name, pUser->phone);
}

// stack
//int main(void) { 
//	InitList();
//	
//	user Tester = { 10, "park" };
//	Push(&Tester);
//
//	Tester.age = 15;
//	strcpy_s(Tester.name, sizeof(Tester.name), "lee");
//	Push(&Tester);
//
//	Tester.age = 17;
//	strcpy_s(Tester.name, sizeof(Tester.name), "choi");
//	Push(&Tester);
//
//	PrintList();
//
//	for (int i = 0; i < 3; i++) {
//		user* pUser = Pop();
//		printf("Pop: %d, %s\n\n", pUser->age, pUser->name);
//		free(pUser);
//	}
//
//	PrintList();
//	
//	return 0;
//}

// queue
int main(void) {
	InitList();
	user Tester = { 10, "park" };
	Enqueue(&Tester);
	
	Tester.age = 15;
	strcpy_s(Tester.name, sizeof(Tester.name), "lee");
	Enqueue(&Tester);
	
	Tester.age = 17;
	strcpy_s(Tester.name, sizeof(Tester.name), "choi");
	Enqueue(&Tester);
	
	PrintList();
	
	for (int i = 0; i < 3; i++) {
		user* pUser = Dequeue();
		printf("Pop: %d, %s\n\n", pUser->age, pUser->name);
		free(pUser);
	}
	
	PrintList();
		
	return 0;
}