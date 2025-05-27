#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/tetris.h"

#define loop(n)                 \
  for (int i = 0; i < n; ++i) { \
    userInput(action, false);   \
    userInput(action, false);   \
  }

START_TEST(_TETRIS_) {
  init_tetris();
  GameInfo_t game_info;
  GameState_t game_state;
  UserAction_t action;
  action = Start;
  userInput(action, false);
  game_state = updateState();
  game_info = updateCurrentState();
  ck_assert_int_eq(game_state, StartGame);
  userInput(action, false);
  ck_assert_int_eq(game_info.score, 0);
  ck_assert_int_eq(game_info.speed, 1);
  ck_assert_int_eq(game_info.level, 1);
  ck_assert_int_eq(game_info.pause, 0);
  userInput(action, false);
  game_state = updateState();
  ck_assert_int_eq(game_state, MoveFigure);
  userInput(action, false);
  game_state = updateState();
  ck_assert_int_eq(game_state, ShiftFigure);
  action = Left;
  loop(4) action = Down;
  ck_assert_int_eq(game_state, 5);
  loop(19) action = Down;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) printf("%d", game_info.field[i][j]);
    printf("\n");
  }
  game_state = updateState();
  ck_assert_int_eq(game_state, 3);

  loop(3) action = Down;
  loop(1) action = Action;
  game_state = updateState();
  printf("%d\n", game_state);
  loop(1) action = Pause;
  ck_assert_int_eq(get_signal(27), Terminate);
  ck_assert_int_eq(get_signal('\t'), Pause);
  ck_assert_int_eq(get_signal('\n'), Start);
  ck_assert_int_eq(get_signal(KEY_UP), Up);
  ck_assert_int_eq(get_signal(KEY_DOWN), Down);
  ck_assert_int_eq(get_signal(KEY_RIGHT), Right);
  ck_assert_int_eq(get_signal(KEY_LEFT), Left);
  ck_assert_int_eq(get_signal(32), Action);

  gameover_state(&game_state, -1);
  ck_assert_int_eq(game_state, 7);

  gameover_state(&game_state, 2);
  ck_assert_int_eq(game_state, 8);
  gameover_state(&game_state, 0);
  ck_assert_int_eq(game_state, 1);
  action = Terminate;
  loop(2) free(game_info.field);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, _TETRIS_);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
