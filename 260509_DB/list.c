#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free
#include <string.h>   // strcpy_s, memcpy_s
#include "list.h"

user g_h = { 0, "_Head_" };
user g_t = { 0, "_Tail_" };

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

		free(pRel);
	}
	InitList();
}

user* SearchByName(char* pName) {
	user* pCur = g_h.pNext;

	while (pCur != &g_t) {
		if (strcmp(pCur->name, pName) == 0) {
			return pCur;
		}
		pCur = pCur->pNext;
	}
	return NULL;
}

void RemoveNode(user* pDel) {
	user* pPrev = pDel->pPrev;
	user* pNext = pDel->pNext;

	pPrev->pNext = pDel->pNext;
	pNext->pPrev = pDel->pPrev;

	free(pDel);
}

int IsEmpty(void) {
	if (g_h.pNext == &g_t)
		return 1;

	return 0;
}

void Push(user* pUser) {
	user* pNewNode = malloc(sizeof(user));
	memcpy_s(pNewNode, sizeof(user), pUser, sizeof(user));
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