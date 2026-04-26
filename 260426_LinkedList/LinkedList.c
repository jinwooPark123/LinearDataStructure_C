#include <stdio.h>

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
}USER;

int main(void) {
	USER tester[4] = {
		{20, "tester1", "010-0000-0001", NULL},
		{21, "tester2", "010-0000-0002", NULL},
		{22, "tester3", "010-0000-0003", NULL},
		{23, "tester4", "010-0000-0004", NULL}
	};

	tester[0].pNext = &tester[1];
	tester[1].pNext = &tester[2];
	tester[2].pNext = &tester[3];
	tester[3].pNext = NULL;

	//개발 팁
	//전체 구조를 알 수 있는 출력 코드를 먼저 개발하는 것이 유리하다
	USER* pUser = &tester[0];

	while (pUser != NULL) {
		printf("%p, %d, %s, %s, [pNext: %p]\n",
			pUser, pUser->age, pUser->name, pUser->phone, pUser->pNext);
		
		pUser = pUser->pNext;
	}

	return 0;
}