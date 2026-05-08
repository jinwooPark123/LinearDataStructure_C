# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];

	struct USERDATA* pPrev;
	struct USERDATA* pNext;
}user;

user g_h = { 0, "Dummy_h" };
user g_t = { 0, "Dummy_t" };

void PrintList(void) {
	user* node = &g_h;

	while (node != NULL) {
		printf("[%p], %d, %s, %s, [pNext: %p]\n",
			node, node->age, node->name, node->phone, node->pNext);

		node = node->pNext;
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
		pCur = pCur -> pNext;
		printf("Release: [%p], %d, %s, %s, [pNext: %p]\n",
			pRel, pRel->age, pRel->name, pRel->phone, pRel->pNext);

		free(pRel);
	}
	InitList();
}

user* SearchByName(char* pName) {
	user* pCur = g_h.pNext;

	while (pCur != &g_t) {
		if (strcmp(pCur->name, pName) == 0) {
			printf("\"%s\": Found!\n", pName);
			return pCur;
		}
		pCur = pCur->pNext;
	}
	printf("\"%s\": Not found!\n", pName);
	return NULL;
}

void RemoveNode(user* pDel) {
	pDel->pPrev->pNext = pDel->pNext;
	pDel->pNext->pPrev = pDel->pPrev;
	
	printf("Del: %s\n", pDel->name);
	free(pDel);
}

void Dummy(void) {
	AddNode(10, "kim", "010-0000-0001");
	AddNode(18, "lee", "010-0000-0002");
	AddNode(9, "park", "010-0000-0003");
}

void Test01(void) {
	puts("Test01()--------------------------------------");
	AddNode(10, "kim", "010-0000-0001");
	AddNode(18, "lee", "010-0000-0002");
	AddNode(9, "park", "010-0000-0003");
	PrintList();

	user* pRemove = SearchByName("kim");
	if (pRemove != NULL) {
		RemoveNode(pRemove);
	}
	ReleaseNode();
	putchar('\n');
}

void Test02(void) {
	puts("Test02()--------------------------------------");
	AddNode(10, "kim", "010-0000-0001");
	AddNode(18, "lee", "010-0000-0002");
	AddNode(9, "park", "010-0000-0003");
	PrintList();

	user* pRemove = SearchByName("lee");
	if (pRemove != NULL) {
		RemoveNode(pRemove);
	}
	ReleaseNode();
	putchar('\n');
}

void Test03(void) {
	puts("Test03()--------------------------------------");
	AddNode(10, "kim", "010-0000-0001");
	AddNode(18, "lee", "010-0000-0002");
	AddNode(9, "park", "010-0000-0003");
	PrintList();

	user* pRemove = SearchByName("park");
	if (pRemove != NULL) {
		RemoveNode(pRemove);
	}
	ReleaseNode();
	putchar('\n');
}

void TEST(void) {
	Test01();
	Test02();
	Test03();
}


int main(void) {
	InitList();
	TEST();
	
	return 0;
}