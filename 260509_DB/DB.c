#include "list.h"
#include "ui.h"
#include "test.h"

int main(void) {
	InitList();
	Dummy();
	
	EventLoop();

	ReleaseNode();
	return 0;
}