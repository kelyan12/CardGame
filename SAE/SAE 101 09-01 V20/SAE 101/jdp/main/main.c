#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main()
{
    initscr();
    printw("Hello world!");
    newwin(1,1,1,1);

    return 0;
}
