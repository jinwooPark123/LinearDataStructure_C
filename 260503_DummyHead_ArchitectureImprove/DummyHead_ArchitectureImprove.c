# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];

	struct USERDATA* pNext;
}user;


//user* g_h = NULL;
user g_h = { 0, "_Dummy_" };

//노드 추가
void AddNode(int age, char* pName, char* pPhone) {
	user* pNewNode = malloc(sizeof(user));

	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pPhone);

	pNewNode->pNext = NULL;

	// 맨 앞에 노드 추가
	/*pNewNode->pNext = g_h.pNext;
	g_h.pNext = pNewNode;*/

	// 맨 뒤에 노드 추가
	user* pT = &g_h;

	while (pT->pNext != NULL) {
		pT = pT->pNext;
	}

	pT->pNext = pNewNode;

}

void ReleaseNode(void) {
	user* pCur = g_h.pNext;
	user* pRel;

	while (pCur != NULL) {
		pRel = pCur;
		pCur = pCur->pNext;

		printf("Release: %p, %d, %s, %s, [pNext: %p]\n",
			pRel, pRel->age, pRel->name, pRel->phone, pRel->pNext);
		free(pRel);
	}
	g_h.pNext = NULL; // 아주 중요 잊지않도록 주의.
}

// key 개념 등장, 검색 노드(예제에서는 이름으로 검색한다.) 중요: 키는 중복을 허락하지 않는다.
user* SearchByName(const char* pName) {
	user* searching = g_h.pNext;

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

user* SearchRemoveNode(const char* pName) {
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
	user* pRem = NULL;

	pRem = pPrev->pNext;
	pPrev->pNext = pRem->pNext;
	printf("Rem: %s\n", pRem->name);
	free(pRem);
}

void DummyData(void) {
	AddNode(10, "hoon", "010-0000-0001");
	AddNode(9, "sung", "010-0000-0002");
	AddNode(15, "jin", "010-0000-0003");
}

void PrintList(void) {
	user* pTmp = &g_h;

	while (pTmp != NULL) {
		printf("%p, %d, %s, %s, [pNext: %p]\n",
			pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);

		pTmp = pTmp->pNext;
	}
}


void TestStep01(void) {
	puts("TestStep01()------------------------------------------");
	AddNode(10, "hoon", "010-0000-0001");
	AddNode(9, "sung", "010-0000-0002");
	AddNode(15, "jin", "010-0000-0003");
	PrintList();

	user* pPrev = SearchRemoveNode("hoon");
	if (pPrev !=NULL)
		RemoveNode(pPrev);
	ReleaseNode();
	putchar('\n');
}

void TestStep02(void) {
	puts("TestStep02()------------------------------------------");
	AddNode(10, "hoon", "010-0000-0001");
	AddNode(9, "sung", "010-0000-0002");
	AddNode(15, "jin", "010-0000-0003");
	PrintList();

	user* pPrev = SearchRemoveNode("sung");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	ReleaseNode();
	putchar('\n');
}

void TestStep03(void) {
	puts("TestStep03()------------------------------------------");
	AddNode(10, "hoon", "010-0000-0001");
	AddNode(9, "sung", "010-0000-0002");
	AddNode(15, "jin", "010-0000-0003");
	PrintList();

	user* pPrev = SearchRemoveNode("jin");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	ReleaseNode();
	putchar('\n');
}



int main(void) {
	TestStep01();
	TestStep02();
	TestStep03();

	return 0;
}