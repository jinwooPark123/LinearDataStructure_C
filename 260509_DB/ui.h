#pragma once

typedef enum MY_MENE { EXIT, NEW, SEARCH, PRINT, REMOVE } my_menu;

my_menu PrintMenu(void);
void EventLoop(void);
void PrintList(void);
void Search(void);
void NewNode(void);