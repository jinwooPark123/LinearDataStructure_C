#pragma once

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];

	struct USERDATA* pPrev;
	struct USERDATA* pNext;
}user;

extern user g_h;
extern user g_t;

void InitList(void);
void AddNode(int age, char* pName, char* pPhone);
void ReleaseNode(void);
int IsEmpty(void);
void Push(user* pUser);
user* Pop(void);
user* Dequeue(void);
void Enqueue(user* pUser);
user* SearchByName(char* pName);
void RemoveNode(user* pDel);