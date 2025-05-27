#include <gtest/gtest.h>

#include "../brick_game/snake/s21_snake.h"
#include "../brick_game/tetris/s21_tetris.h"

TEST(back, back_1) {
  s21::SnakeModel model;
  s21::SnakeControle controller(&model);
  GameInfo_t game_info;
  GameState_t game_state;
  int signal = -1;

  UserAction_t act = controller.get_signal(signal);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == StartGame);

  act = controller.get_signal('\n');
  ASSERT_TRUE(act == Start);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == SpawnFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Start);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Start);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);
  model.updateClock(clock());

  act = controller.get_signal('\t');
  ASSERT_TRUE(act == Pause);
  controller.userInput(Pause, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == PauseGame);

  act = controller.get_signal(27);
  ASSERT_TRUE(act == Terminate);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ExitGame);
  free(game_info.field);
}

TEST(back, back_2) {
  s21::SnakeModel model;
  s21::SnakeControle controller(&model);
  GameInfo_t game_info;
  GameState_t game_state;
  int signal = -1;

  UserAction_t act = controller.get_signal(signal);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == StartGame);

  model.attach_state(&game_state);
  act = controller.get_signal(27);
  ASSERT_TRUE(act == Terminate);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();

  ASSERT_TRUE(game_state == ExitGame);
  // free(game_info.field);

  GameSnake_t s;
  s.field = (int**)malloc(HEIGHT * sizeof(int*));
  for (int i = 0; i < HEIGHT; i++)
    s.field[i] = (int*)calloc(WIDTH, sizeof(int));
  model.proverka(&s, 0, 0);
  (s.snake.coords).push_back(std::make_pair(2, 0));
  (s.snake.coords).push_back(std::make_pair(1, 0));
  (s.snake.coords).push_back(std::make_pair(0, 0));
  model.direction_snake(&s, &game_state, 0, 0);
  model.gameover_state(&game_state, Start);
  model.gameover_state(&game_state, Up);
  model.gameover_state(&game_state, Pause);
  model.gameover_state(&game_state, Terminate);
  model.pause_state(&game_state, Start);
  model.pause_state(&game_state, Up);
  model.pause_state(&game_state, Pause);
  model.pause_state(&game_state, Terminate);
  model.exit_game_state(&game_state, &s);
}

TEST(back, back_3) {
  s21::SnakeModel model;
  s21::SnakeControle controller(&model);
  GameInfo_t game_info;
  GameState_t game_state;
  int signal = -1;

  UserAction_t act = controller.get_signal(signal);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == StartGame);
  act = controller.get_signal('\n');
  ASSERT_TRUE(act == Start);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == SpawnFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Start);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Start);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);

  act = controller.get_signal(0403);
  ASSERT_TRUE(act == Up);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Up);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);

  act = controller.get_signal(0404);
  ASSERT_TRUE(act == Left);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Left);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);

  act = controller.get_signal(0402);
  ASSERT_TRUE(act == Down);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Down);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);

  act = controller.get_signal(0405);
  ASSERT_TRUE(act == Right);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Right);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);

  act = controller.get_signal(27);
  ASSERT_TRUE(act == Terminate);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();

  ASSERT_TRUE(game_state == ExitGame);
  free(game_info.field);
}

TEST(back, Back_1) {
  s21::TetrisModel model;
  s21::TetrisController controller(&model);
  GameInfo_t game_info;
  GameState_t game_state;
  int signal = -1;

  UserAction_t act = controller.get_signal(signal);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == StartGame);

  act = controller.get_signal('\n');
  ASSERT_TRUE(act == Start);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == SpawnFigure);

  act = controller.get_signal(-1);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Up);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);
  model.updateClock(clock());

  act = controller.get_signal('\t');
  ASSERT_TRUE(act == Pause);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == PauseGame);

  act = controller.get_signal(27);
  ASSERT_TRUE(act == Terminate);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ExitGame);
  free(game_info.field);
}

TEST(back, Back_2) {
  s21::TetrisModel model;
  s21::TetrisController controller(&model);
  GameInfo_t game_info;
  GameState_t game_state;
  Game_t g;
  int signal = -1;

  UserAction_t act = controller.get_signal(signal);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == StartGame);

  act = controller.get_signal('\n');
  ASSERT_TRUE(act == Start);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == SpawnFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Up);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Up);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);

  act = controller.get_signal(0403);
  ASSERT_TRUE(act == Up);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Up);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);

  act = controller.get_signal(0404);
  ASSERT_TRUE(act == Left);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Up);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);

  act = controller.get_signal(0402);
  ASSERT_TRUE(act == Down);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Up);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);

  act = controller.get_signal(0405);
  ASSERT_TRUE(act == Right);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == MoveFigure);

  act = controller.get_signal(-1);
  ASSERT_TRUE(act == Up);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();
  ASSERT_TRUE(game_state == ShiftFigure);

  act = controller.get_signal(27);
  ASSERT_TRUE(act == Terminate);
  controller.userInput(act, false);
  game_info = model.updateCurrentState();
  game_state = controller.updateState();

  ASSERT_TRUE(game_state == ExitGame);

  controller.updateInfo();
  controller.get_signal(32);

  g.field = (int**)malloc(HEIGHT * sizeof(int*));
  for (int i = 0; i < HEIGHT; i++)
    g.field[i] = (int*)calloc(WIDTH, sizeof(int));
  model.remove_lines(g.field, 19);
  // model.attach_state(&game_state,&g);
  model.gameover_state(&game_state, Start);
  model.gameover_state(&game_state, Up);
  model.gameover_state(&game_state, Pause);
  model.gameover_state(&game_state, Terminate);
  model.gameover_state(&game_state, MEM);
  model.pause_state(&game_state, Start);
  model.pause_state(&game_state, Up);
  model.pause_state(&game_state, Pause);
  model.pause_state(&game_state, Terminate);
  model.exit_game_state(&game_state, &g);
  model.start_game(&g, &game_state, Up);
  model.start_game(&g, &game_state, Terminate);
  model.issquare_line(&g);
  controller.userInput(Action, false);
  free(game_info.field);
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}