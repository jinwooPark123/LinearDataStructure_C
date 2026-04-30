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
    user* newNode = malloc(sizeof(user));
    newNode->age = age;
    strcpy_s(newNode->name, sizeof(newNode->name), pName);
    strcpy_s(newNode->phone, sizeof(newNode->phone), pPhone);
    newNode->pNext = NULL;

    if (g_h == NULL) {
        // 리스트가 비어있을 때 처음 추가되면, 전역변수 g_h가 이 첫 노드를 가리키게 됨
        g_h = newNode;
    }
    else {
        user* pT = g_h;

        while (pT->pNext != NULL)
            pT = pT->pNext;

        pT->pNext = newNode;
    }
}

void ReleaseNode(void) {
    // 1. 원본 훼손(시작 위치 소실)을 막기 위해 순회용 임시 포인터(cur) 생성
    user* cur = g_h;
    user* Rel; // 2. 삭제할 노드를 잠시 맡아둘 백업용 포인터

    while (cur != NULL) {
        Rel = cur;          // 3. 현재 지울 방을 del에 찜(백업)해둠
        cur = cur->pNext;   // 4. 내 몸(cur)은 다음 방으로 안전하게 이동해둠

        printf("Rel : [%p], %d, %s, %s, [next: %p]\n",
            Rel, Rel->age, Rel->name, Rel->phone, Rel->pNext);

        free(Rel);          // 5. 다음 방으로 피신했으니, 안심하고 예전 방(del)을 파괴
    }

    // 6. 건물 철거가 끝났으니, g_h가 들고 있던 옛날 주소표를 떼어냄(댕글링 포인터 방지)
    g_h = NULL;
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

    PrintList();

    // 메모리 해제
    ReleaseNode();

    return 0;
}