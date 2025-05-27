#include <ncurses.h>

#include <cstddef>
#include <iostream>
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
  if (xzz == 122)
    std::system("make snake_cli");
  else if (xzz == 120)
    std::system("make tetris_cli");
  else if (xzz == 99)
    std::system("make tetris_desktop");
  else
    std::system("make snake_desktop");
}