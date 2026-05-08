# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];

	struct USERDATA* pNext;
}user;

user g_h = { 0, "_Dummy_" };

void PrintList(void) {
	user* node = &g_h;

	while (node != NULL) {
		printf("[%p], %d, %s, %s, [pNext: %p]\n",
			node, node->age, node->name, node->phone, node->pNext);

		node = node->pNext;
	}
}

void AddNode(int age, char* pName, char* pPhone) {
	user* pNewNode = malloc(sizeof(user));

	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pPhone);

	pNewNode->pNext = NULL;

	//user* pT = g_h.pNext; // 실질적인 첫번째 데이터 노드
	//					    // 아직 아무 데이터가 없는 상황에서는 에러 발생

	user* pT = &g_h;

	while (pT->pNext != NULL) {
		pT = pT->pNext;
	}
	pT->pNext = pNewNode;
}

void ReleaseNode(void) {
	user* pCur = g_h.pNext;
	user* pRel = NULL;

	while (pCur = NULL) {
		pRel = pCur;
		pCur = pCur->pNext;
		printf("Release: [%p], %d, %s, %s, [pNext: %p]\n",
			pCur, pCur->age, pCur->name, pCur->phone, pCur->pNext);
		
		free(pRel);
	}
	g_h.pNext = NULL;
}

user* SearchByName(char* pName) {
	user* searching = &g_h;

	while (searching != NULL) {
		if (strcmp(searching->name, pName) == 0) {
			printf("\"%s\": Found\n", pName);
			return searching;
		}
		searching = searching->pNext;
	}
	printf("\"%s\": Not found\n", pName);
	return NULL;
}

user* SearchRemoveNode(char* pName) {
	user* pPrev = &g_h;

	while (pPrev->pNext != NULL) {
		if (strcmp(pPrev->pNext->name, pName) == 0) {
			printf("\"%s\": Found\n", pName);
			return pPrev;
		}
		pPrev = pPrev->pNext;
	}
	printf("\"%s\": Not found\n", pName);
	return NULL;
}

void RemoveNode(user* pPrev) {
	user* pDel = NULL;

	pDel = pPrev->pNext;
	pPrev->pNext = pDel->pNext;
	printf("Del: \"%s\"\n", pDel->name);
	free(pDel);
}

void Dummy(void) {
	AddNode(10, "kim", "010-0000-0001");
	AddNode(18, "lee", "010-0000-0002");
	AddNode(9, "park", "010-0000-0003");
}

void Test1(void) {
	puts("Test01-------------------------------------------------");
	AddNode(10, "kim", "010-0000-0001");
	AddNode(18, "lee", "010-0000-0002");
	AddNode(9, "park", "010-0000-0003");
	PrintList();

	user* pPrev = SearchRemoveNode("kim");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	ReleaseNode();
	putchar('\n');
}

void Test2(void) {
	puts("Test02-------------------------------------------------");
	AddNode(10, "kim", "010-0000-0001");
	AddNode(18, "lee", "010-0000-0002");
	AddNode(9, "park", "010-0000-0003");
	PrintList();

	user* pPrev = SearchRemoveNode("lee");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	ReleaseNode();
	putchar('\n');
}

void Test3(void) {
	puts("Test03-------------------------------------------------");
	AddNode(10, "kim", "010-0000-0001");
	AddNode(18, "lee", "010-0000-0002");
	AddNode(9, "park", "010-0000-0003");
	PrintList();

	user* pPrev = SearchRemoveNode("park");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	ReleaseNode();
	putchar('\n');
}

int main() {
	Test1();
	Test2();
	Test3();

	return 0;
}