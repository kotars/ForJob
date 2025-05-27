#include "view.h"

int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(50);
  TetrisModel model;
  TetrisController controller(&model);
  ConsoleView view(&controller);
  GameInfo_t game_info;  // выделить сюда память
  GameState_t game_state;
  bool break_game = true;
  int signal = -1;
  while (break_game) {
    controller.userInput(controller.get_signal(signal), false);
    model.updateClock(clock());
    game_info = model.updateCurrentState();
    game_state = controller.updateState();
    if (game_state == DestroyGame) {
      break_game = 1 - break_game;
    }
    if (game_state == MoveFigure || game_state == PauseGame ||
        game_state == StartGame || game_state == GameOver) {
      signal = getch();
    }
    switch (game_state) {
      case StartGame:
        view.print_start();
        break;
      case GameOver:
        view.print_end();
        break;
      default:
        view.print_board(game_info);
        break;
    }
  }
  free(game_info.field);
  endwin();
  return 0;
}