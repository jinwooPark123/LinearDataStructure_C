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

void AddNode(int age, char* pName, char* pPhone) {
	user* pNewNode = malloc(sizeof(user));

	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pPhone);

	pNewNode->pNext = NULL;

	if (g_h == NULL)
		g_h = pNewNode;
	else{
		// 맨 앞노드 위치에 추가(stack)
		/*pNewNode->pNext = g_h;
		g_h = pNewNode;*/

		//맨 뒷노드 위치에 추가(queue)
		user* pT = g_h;

		while (pT->pNext != NULL) {
			pT = pT->pNext;
		}
		pT->pNext = pNewNode;
	}
}

void ReleaseNode(void) {
	user* pCur = g_h;
	user* pRel = NULL;

	while (pCur != NULL) {
		pRel = pCur;
		pCur = pCur->pNext;
		printf("Release: [% p], % d, % s, % s, [pNext:% p]\n",
			pRel, pRel->age, pRel->name, pRel->phone, pRel->pNext);

		free(pRel);
	}
	g_h = NULL;
}

user* SearchByName(char* pName) {
	user* searching = g_h;

	while (searching != NULL) {
		if (strcmp(searching->name, pName) == 0) {
			printf("\"%s\": Found!\n", pName);
			return searching;
		}
		searching = searching->pNext;
	}
	printf("\"%s\": Not found!\n", pName);
	return NULL;
}

// 삭제 이전 노드를 같이 찾아줘야 한다.
user* searchRemoveNode(user** ppPrev, char* pName) {
	user* pCur = g_h;
	user* pPrev = NULL;

	while (pCur != NULL) {
		if (strcmp(pCur->name, pName) == 0) {
			*ppPrev = pPrev;
			printf("삭제할 노드는 \"%s\" 입니다.\n", pCur->name);
			return pCur;
		}
		pPrev = pCur;
		pCur = pCur->pNext;
	}
	return NULL;
}

void RemoveNode(user* pPrev) {
	user* Rem = NULL;

	if (pPrev == NULL) {
		//삭제할 노드가 첫번째 노드일 때,
		Rem = g_h;
		g_h = Rem->pNext;
		printf("Remove: \"%s\"\n", Rem->name);
		free(Rem);
		return;
	}
	Rem = pPrev->pNext;
	pPrev->pNext = Rem->pNext;
	printf("Remove: \"%s\"\n", Rem->name);
	free(Rem);
}

void Dummy(void) {
	AddNode(10, "kim", "010-0000-0001");
	AddNode(18, "lee", "010-0000-0002");
	AddNode(9, "park", "010-0000-0003");
}

void PrintList(void) {
	user* node = g_h;

	while (node != NULL) {
		printf("[%p], %d, %s, %s, [pNext: %p]\n",
			node, node->age, node->name, node->phone, node->pNext);

		node = node->pNext;
	}
	putchar('\n');
}

void Test1(void) {
	puts("Test01-------------------------------------------------");
	AddNode(10, "kim", "010-0000-0001");
	AddNode(18, "lee", "010-0000-0002");
	AddNode(9, "park", "010-0000-0003");
	PrintList();

	user* pPrev = NULL;
	if (searchRemoveNode(&pPrev, "kim") != NULL)
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

	user* pPrev = NULL;
	if (searchRemoveNode(&pPrev, "lee") != NULL)
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

	user* pPrev = NULL;
	if (searchRemoveNode(&pPrev, "park") != NULL)
		RemoveNode(pPrev);
	ReleaseNode();
	putchar('\n');
}

int main(void) {
	Test1();
	Test2();
	Test3();
}