#include "../inc/cli.h"
#include "../inc/tetris.h"

void game_loop() {
  init_tetris();
  GameInfo_t game_info;  //выделить сюда память
  GameState_t game_state;
  bool break_game = true;
  int signal = -1;

  while (break_game) {
    userInput(get_signal(signal), false);
    updateClock(clock());

    game_info = updateCurrentState();
    game_state = updateState();
    if (game_state == DestroyGame) {
      break_game = 1 - break_game;
    }
    if (game_state == MoveFigure || game_state == PauseGame ||
        game_state == StartGame || game_state == GameOver) {
      signal = getch();
    }
    switch (game_state) {
      case StartGame:
        print_start();
        break;
      case GameOver:
        print_end();
        break;
      default:
        print_board(game_info);
        break;
    }
  }
  free(game_info.field);
}

int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(50);
  game_loop();
  endwin();
  return 0;
}