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

// [목적] 
// 삭제할 타겟 노드를 찾지만, 타겟 노드 자체가 아니라 
// 단방향 리스트의 삭제(연결 고리 재구성)를 위해 "타겟의 바로 앞 노드" 주소를 반환하는 함수

user* SearchRemoveNode(const char* pName) {
	// 1. 시작점 설정
	// 더미 노드의 시작 주소값을 pPrev 포인터 변수에 담고 시작.
	// 더미 노드 역시 물리적 메모리 공간이 존재하므로 첫 '이전 노드' 역할을 완벽히 수행함.
	user* pPrev = &g_h;

	// 2. 루프 진입 조건: "현재 노드에 저장된 다음 방의 주소값(pNext)이 0(NULL)이 아닌가?"
	// 순회(Print)와 달리 삭제 검색은 타겟 노드에 직접 진입하면 안 됨.
	// 타겟 방에 들어가 버리면 이전 방의 주소를 잊어버려 리스트를 이어 붙일 수 없기 때문.
	// 따라서 타겟 노드의 '앞방'에 멈춰 서기 위해 내 다음 방이 존재하는지만 확인함.
	while (pPrev->pNext != NULL) {

		// 3. 앞방 데이터 확인 (창문 너머로 보기)
		// 현재 내가 서 있는 방(pPrev)에서, 다음 방(pPrev->pNext)의 실제 데이터(name)를 비교함.
		if (strcmp(pPrev->pNext->name, pName) == 0) {

			// 4. 핵심 반환 로직: 타겟을 찾았다면 타겟 노드가 아닌 '현재 위치(pPrev)'를 반환.
			// 다음 방이 삭제할 타겟이므로, 현재 서 있는 방(타겟의 앞방)의 주소를 반환해야
			// 이 함수를 호출한 곳에서 앞방의 pNext 값을 조작하여 타겟을 리스트에서 잘라낼 수 있음.
			return pPrev;
		}

		// 5. 다음 노드로 이동 (주소값 덮어쓰기)
		// 다음 방이 타겟이 아니라면, 현재 노드에 적혀있던 다음 주소값을
		// pPrev 변수에 덮어써서 관찰자의 위치를 한 칸 전진시킴.
		pPrev = pPrev->pNext;
	}

	// 6. 검색 실패
	// 마지막 노드에 도착하여 다음 방의 주소값이 NULL이 될 때까지 루프를 돌았음에도 
	// if문에 걸리지 않았다면, 지우려는 데이터가 리스트에 존재하지 않는다는 뜻임.
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