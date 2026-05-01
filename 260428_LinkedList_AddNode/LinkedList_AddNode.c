#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조체 정의
typedef struct USERDATA {
    int age;
    char name[32];
    char phone[32];
    struct USERDATA* pNext;
} user;

// 리스트의 기준점(닻) 역할을 하는 전역 변수. 초기엔 비어있음(NULL).
user* g_h = NULL;

void AddNode(int age, char* pName, char* pPhone) {
    user* pNewNode = malloc(sizeof(user));
    pNewNode->age = age;
    strcpy_s(pNewNode->name, sizeof(pNewNode->name), pName);
    strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pPhone);
    pNewNode->pNext = NULL;

    if (g_h == NULL) {
        // 리스트가 비어있을 때 처음 추가되면, 전역변수 g_h가 이 첫 노드를 가리키게 됨
        g_h = pNewNode;
    }
    else {
        //맨 앞 노드 삽입
        /*pNewNode->pNext = g_h;
        g_h = pNewNode;*/

        //맨 뒤 노드 삽입
        user* pT = g_h;

        while (pT->pNext != NULL) {
            pT = pT->pNext;
        }
        pT->pNext = pNewNode;
    }
}
 
void ReleaseNode(void) {
    // 1. 원본 훼손(시작 위치 소실)을 막기 위해 순회용 임시 포인터(cur) 생성
    user* cur = g_h;
    user* Rel; // 2. 해제할 노드를 잠시 맡아둘 백업용 포인터

    while (cur != NULL) {
        Rel = cur;          // 3. 현재 해제할 방을 del에 찜(백업)해둠
        cur = cur->pNext;   // 4. 내 몸(cur)은 다음 방으로 안전하게 이동해둠

        printf("Rel : [%p], %d, %s, %s, [next: %p]\n",
            Rel, Rel->age, Rel->name, Rel->phone, Rel->pNext);

        free(Rel);          // 5. 다음 방으로 피신했으니, 안심하고 예전 방(del)을 파괴
    }

    // 6. 건물 철거가 끝났으니, g_h가 들고 있던 옛날 주소표를 떼어냄(댕글링 포인터 방지)
    g_h = NULL;
}

user* SearchByName(user** ppPrev, const char* pName) {
    user* searching = g_h;

    while (searching != NULL) {
        if (strcmp(searching->name, pName) == 0) {
            printf("\"%s\": Found\n", pName);
            return searching;
        }

        searching = searching->pNext;
    }

    printf("\"%s\": Not found\n", pName);
    return 0;
}



// 삭제할 노드와 그 앞 노드를 같이 찾아줘야 한다.
// 삭제할 노드는 다음 노드 위치값을 포함하고 있으며, 이 노드를 먼저 삭제할 경우, 데이터가 유실된다.
// 그러므로 앞 전 노드를 찾아서 삭제할 노드가 가리치는 값을 가리키도록 선조치 후, 삭제할 수 있도록 한다.

user* SearchToRemove(user** ppPrev, const char* pName) {
    // [기준점 설정] g_h는 리스트의 시작점을 쥐고 있는 부동의 지표다.
    // 지표가 변질되지 않도록 순회 전용 포인터 pCur를 생성하여 탐색을 위임한다.
    user* pCur = g_h;

    // [단방향성 보완] 단일 연결 리스트는 역방향 추적이 불가능한 외길이다.
    // 따라서 다음 노드로 전진하기 전, 현재 위치를 pPrev에 상시 백업하여 '직전 경로'를 확보한다.[cite: 1]
    user* pPrev = NULL;

    while (pCur != NULL) {
        // [검색 성공 시 처리] 삭제 대상(pCur)을 발견한 결정적 순간[cite: 1]
        if (strcmp(pCur->name, pName) == 0) {

            // [상위 차원 간섭] ppPrev는 함수 외부(main) 포인터 변수의 '실체 주소'다.[cite: 1]
            // 간접 참조 연산자(*)를 통해 차원을 뚫고 들어가, 밖의 변수에 백업된 이전 주소를 강제 주입한다.[cite: 1]
            // 이로써 함수가 종료되어도 외부의 pPrev는 삭제 노드의 앞 노드를 정확히 가리키게 된다.[cite: 1]
            *ppPrev = pPrev;

            // 삭제를 실행할 주체(대상 노드)를 반환하며 로직을 마친다.[cite: 1]
            return pCur;
        }

        // [이동 로직] 
        // 현재 노드(pCur)의 위치를 pPrev에 백업하여 '과거'로 만들고,[cite: 1]
        pPrev = pCur;

        // pCur을 다음 노드(pNext)로 갱신하여 '미래'로 한 칸 전진한다.[cite: 1]
        pCur = pCur->pNext;
    }

    // 리스트 끝(NULL)까지 탐색했으나 대상을 찾지 못한 경우 실 실패를 반환한다.[cite: 1]
    return NULL;
}


void Tester(void) {
    //테스트 코드
    AddNode(10, "Hoon", "010-0000-0001");
    AddNode(11, "chul", "010-0000-0002");
    AddNode(8, "jjang", "010-0000-0003");
}

void PrintList(void) {
    // 출력 시에도 g_h 원본이 움직이지 않게 순회용 포인터(pTmp) 사용
    user* pTmp = g_h;
    // 다른 포인터(pTmp)를 사용하는 이유
    // g_h(Head) : '고정된 표지판' 역할. 시작 위치를 잃어버리면 안 되므로 절대 직접 움직이지 않습니다.
    // pTmp(Current) : 표지판 대신 칸을 하나씩 이동하며 확인하는 '심부름꾼'입니다.
    // 이유 : 시작점(g_h)을 이동시켜 버리면, 나중에 다시 처음부터 찾고 싶을 때 돌아갈 길을 잃어버리기 때문입니다.


    //1.전체적인 출력구조 구현하기.
    while (pTmp != NULL) {
        printf("New : [%p], %d, %s, %s, [next: %p]\n",
            pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);
        pTmp = pTmp->pNext;
    }
}

int main(void) {

    Tester();

    user* pPrev = NULL;
    user* Del = SearchToRemove(&pPrev, "Hoon");

    // 메모리 해제
    ReleaseNode();

    return 0;
}