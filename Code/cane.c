/*
=========================================
* "Cane Pofuente" command for Linux Shell. 
* inspired by sl command of  mtoyoda / sl. 
* All right reserved to mtoyoda.
*
* Alteration by Rombo
=========================================
*/

#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "cane.h"

int add_cane(int x);
void option(char *str);
int my_mvaddstr(int y, int x, char *str);

int FLY       = 0;

int my_mvaddstr(int y, int x, char *str)
{
    for ( ; x < 0; ++x, ++str)
        if (*str == '\0')  return ERR;
    for ( ; *str != '\0'; ++str, ++x)
        if (mvaddch(y, x, *str) == ERR)  return ERR;
    return OK;
}

void option(char *str)
{
    extern int FLY;

    while (*str != '\0') {
        switch (*str++) {
            case 'F': FLY      = 1; break;
            default:                break;
        }
    }
}

int main(int argc, char *argv[])
{
    int x, i;

    for (i = 1; i < argc; ++i) {
        if (*argv[i] == '-') {
            option(argv[i] + 1);
        }
    }
    initscr();
    signal(SIGINT, SIG_IGN);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    for (x = COLS - 1; ; --x) {
        if (add_cane(x) == ERR) break;
        getch();
        refresh();
        usleep(60000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();

    return 0;
}

int add_cane(int x)
{
    static char *cane[PATTERNS][HEIGHT + 1]
        = {{BODY01, BODY02, BODY03, BODY04, BODY05, BODY06, BODY07, BODY08, BODY09, BODY10, BODY11, BODY12, BODY13, BODY14, BODY15, 
            END101, END102, END103, END104, END105, END106, END107, END108, END109, END110, END111, END112, END113, END114}, /*First Frame*/
           {BODY01, BODY02, BODY03, BODY04, BODY05, BODY06, BODY07, BODY08, BODY09, BODY10, BODY11, BODY12, BODY13, BODY14, BODY15,
            END201, END202, END203, END204, END205, END206, END207, END208, END209, END210, END211, END212, END213, END214},/*Second Frame*/
           {BODY01, BODY02, BODY03, BODY04, BODY05, BODY06, BODY07, BODY08, BODY09, BODY10, BODY11, BODY12, BODY13, BODY14, BODY15,
            END301, END302, END303, END304, END305, END306, END307, END308, END309, END310, END311, END312, END313, END314},/*Third Frame*/
           {BODY01, BODY02, BODY03, BODY04, BODY05, BODY06, BODY07, BODY08, BODY09, BODY10, BODY11, BODY12, BODY13, BODY14, BODY15,
            END201, END202, END203, END204, END205, END206, END207, END208, END209, END210, END211, END212, END213, END214},/*Fourth Frame*/
           };

    int y, i;

    if (x < - LENGTH)  return ERR;
    y = LINES / 2 - 5;

    if (FLY == 1) {
        y = (x / 7) + LINES - (COLS / 7) - HEIGHT;
    }
    for (i = 0; i <= HEIGHT; ++i) {
        my_mvaddstr(y + i, x, cane[(LENGTH + x) % PATTERNS][i]);
    }
    return OK;
}



