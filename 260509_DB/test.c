#include <string.h>   // strcpy_s (AddNode 내부에서 씀)
#include "list.h"     // AddNode
#include "test.h"

void Dummy(void) {
	AddNode(11, "Dong", "010-0000-0001");
	AddNode(9, "Chung", "010-0000-0002");
	AddNode(14, "Choi", "010-0000-0003");
}