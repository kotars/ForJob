#include "../gui/cli/cli.h"

int main() {
  initscr();
  keypad(stdscr, 1);
  noecho();
  curs_set(0);
  mvprintw(0, 0, "Enter Z to start Terminal snake\n");
  mvprintw(2, 0, "Enter X to start Terminal tetris\n");
  mvprintw(4, 0, "Enter C to start Desktop tetris\n");
  mvprintw(6, 0, "Enter other key to start Desktop snake\n");
  int xzz = getch();
  clear();
  refresh();
  endwin();
  return 0;
}