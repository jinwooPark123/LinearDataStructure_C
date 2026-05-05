# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];

	struct USERDATA* pNext;
}user;

user* g_h = NULL;

//노드 추가
void AddNode(int age, char* pName, char* pPhone) {
	user* pNewNode = malloc(sizeof(user));

	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pPhone);

	pNewNode->pNext = NULL;

	if (g_h == NULL)
		g_h = pNewNode;
	else {
		// 맨 앞에 노드 추가
		/*pNewNode->pNext = g_h;
		g_h = pNewNode;*/
		
		// 맨 뒤에 노드 추가
		user* pT = g_h;

		while (pT->pNext != NULL) {
			pT = pT->pNext;
		}

		pT->pNext = pNewNode;
	}
}

void ReleaseNode(void) {
	user* pCur = g_h;
	user* pRel;

	while (pCur != NULL) {
		pRel = pCur;
		pCur = pCur->pNext;
		
		printf("Release: %p, %d, %s, %s, [pNext: %p]\n",
			pRel, pRel->age, pRel->name, pRel->phone, pRel->pNext);
		free(pRel);
	}
	g_h = NULL; // 아주 중요 잊지않도록 주의.
}

// key 개념 등장, 검색 노드(예제에서는 이름으로 검색한다.) 중요: 키는 중복을 허락하지 않는다.
user* SearchByName(const char* pName) {
	user* searching = g_h;

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

// 삭제할 노드와 함께 그 이전 노드를 찾아줘야 한다.
user* SearchRemoveNode(user** ppPrev, const char* pName) {
	user* pCur = g_h;
	user* pPrev = NULL;
	
	while (pCur != NULL) {
		if (strcmp(pCur->name, pName) == 0) {
			*ppPrev = pPrev;
			return pCur;
		}
		pPrev = pCur;
		pCur = pCur->pNext;
	}
	return;
}

void RemoveNode(user* pPrev) {
	user* pRem = NULL;

	if (pPrev == NULL) {
		if (g_h == 0)
			return; // 일종의 방어코드이며, 여기서는 크게 의미가 없음.

		else {
			pRem = g_h;
			g_h = pRem->pNext;
			printf("Rem: %s\n", pRem->name);
			free(pRem);
			return;
		}
	}
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
	user* pTmp = g_h;

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

	user* pPrev = NULL;
	if (SearchRemoveNode(&pPrev, "hoon") != NULL)
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

	user* pPrev = NULL;
	if (SearchRemoveNode(&pPrev, "sung") != NULL)
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

	user* pPrev = NULL;
	if (SearchRemoveNode(&pPrev, "jin") != NULL)
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