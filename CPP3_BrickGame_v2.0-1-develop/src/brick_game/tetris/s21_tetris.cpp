#include "s21_tetris.h"

Figure_t figures[7] = {
    {.square_fig = {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     .x = 3,
     .y = -1},
    {.square_fig = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     .x = 3,
     .y = -1},
    {.square_fig = {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
     .x = 3,
     .y = -1},
    {.square_fig = {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
     .x = 3,
     .y = -1},
    {.square_fig = {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
     .x = 3,
     .y = -1},
    {.square_fig = {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     .x = 3,
     .y = -1},
    {.square_fig = {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
     .x = 3,
     .y = -1}};

namespace s21 {
TetrisModel::TetrisModel() {
  init_tetris();
  start_move_timer = 0;
  end_move_timer = 0;
}
TetrisModel::~TetrisModel() {}
void TetrisModel::init_tetris() {
  game_info.field = (int**)malloc(sizeof(int*) * HEIGHT);
  for (int i = 0; i < HEIGHT; i++)
    game_info.field[i] = (int*)calloc(WIDTH, sizeof(int));
  game_info.next = (int**)malloc(sizeof(int*) * 4);
  for (int i = 0; i < 4; i++) game_info.next[i] = (int*)calloc(4, sizeof(int));

  game_info.level = 1;
  game_info.score = 0;
  FILE* f = fopen("stats_tetris", "r");
  if (f != NULL) {
    fscanf(f, "%d", &game_info.high_score);
    fclose(f);
  } else
    game_info.high_score = 0;
  game_info.speed = 1;
  game_info.pause = 0;
}
void TetrisModel::init_game(Game_t* game, GameState_t* game_state) {
  game->field = (int**)malloc(HEIGHT * sizeof(int*));
  for (int i = 0; i < HEIGHT; i++)
    game->field[i] = (int*)calloc(WIDTH, sizeof(int));
  copy_figure(&game->next, &figures[rand() % 7]);
  *game_state = StartGame;
}
void TetrisModel::clear_game(Game_t* game) {
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      game->field[i][j] = 0;
    }
  }
  game_info.level = 1;
  game_info.speed = 1;
  game_info.score = 0;
  game_info.pause = 0;
}
void TetrisModel::start_game(Game_t* game, GameState_t* state,
                             UserAction_t action) {
  switch (action) {
    case Start:
      clear_game(game);
      *state = SpawnFigure;
      break;
    case Terminate:
      *state = ExitGame;
      break;
    default:
      *state = StartGame;
      break;
  }
}
void TetrisModel::copy_figure(Figure_t* curr, const Figure_t* fig) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) curr->square_fig[i][j] = fig->square_fig[i][j];
  curr->x = fig->x;
  curr->y = fig->y;
}
void TetrisModel::copy_field(Game_t* game) {
  for (int i = 0; i < HEIGHT; i++)
    for (int j = 0; j < WIDTH; j++) game_info.field[i][j] = game->field[i][j];
  copy_figure_to_field(game_info.field, &game->curr);
}
void TetrisModel::copy_figure_to_field(int** field, Figure_t* fig) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (fig->square_fig[i][j])
        field[fig->y + i][fig->x + j] = fig->square_fig[i][j];
    }
  }
}
int TetrisModel::proverka(Game_t* game, int x, int y) {
  int res = 1;
  for (int i = 0; i < 4 && res != 0; i++) {
    for (int j = 0; j < 4 && res != 0; j++) {
      if (game->curr.square_fig[i][j]) {
        if ((game->curr.x + j + x) < 0 || (game->curr.x + j + x) >= 10 ||
            (game->curr.y + i + y) < 0 || (game->curr.y + i + y) >= 20) {
          res = 0;
        } else if (game->field[game->curr.y + i + y][game->curr.x + j + x])
          res = 0;
      }
    }
  }
  return res;
}
void TetrisModel::spawn_state(Game_t* game, GameState_t* state) {
  copy_figure(&game->curr, &game->next);
  copy_figure(&game->next, &figures[rand() % 7]);
  if (!proverka(game, 0, 0))
    *state = GameOver;
  else {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        game_info.next[i][j] = game->next.square_fig[i][j];
    copy_field(game);
    *state = MoveFigure;
  }
}
// проверка на соприкосновение с фигурами, проверять заполненность поля +++
int TetrisModel::issquare_line(Game_t* game) {
  return (game->curr.square_fig[1][1] && game->curr.square_fig[1][2] &&
          game->curr.square_fig[2][1] && game->curr.square_fig[2][2]) ||
                 (game->curr.square_fig[1][0] && game->curr.square_fig[1][1] &&
                  game->curr.square_fig[1][2] && game->curr.square_fig[1][3])
             ? 4
             : 3;
}
int TetrisModel::dvig(UserAction_t action, GameState_t* state, Game_t* game) {
  int res = 1;
  if (action == Left)
    game->curr.x = proverka(game, -1, 0) ? game->curr.x - 1 : game->curr.x;
  else if (action == Right)
    game->curr.x = proverka(game, 1, 0) ? game->curr.x + 1 : game->curr.x;
  else if (action == Down) {
    if (proverka(game, 0, 1))
      game->curr.y += 1;
    else
      res = 0;

  } else if (action == Action) {
    Game_t temp = *game;
    int n = issquare_line(game);
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) temp.curr.square_fig[i][j] = 0;

    // поворот фигуры +++

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        temp.curr.square_fig[j][n - i - 1] = game->curr.square_fig[i][j];
      }
    }

    if (proverka(&temp, 0, 0)) {
      copy_figure(&game->curr, &temp.curr);
    }
  }
  *state = !res ? AttachFigure : MoveFigure;
  copy_field(game);
  return res;
}
void TetrisModel::remove_lines(int** field, int y) {
  for (int i = y - 1; i >= 0; i--)
    for (int j = 0; j < WIDTH; j++) field[i + 1][j] = field[i][j];
}
void TetrisModel::attach_state(GameState_t* state, Game_t* game) {
  copy_figure_to_field(game->field, &game->curr);
  int scores[5] = {0, 100, 300, 700, 1500};
  int score = 0;
  for (int i = 0; i < HEIGHT; i++) {
    int temp = 0;
    for (int j = 0; j < WIDTH && game->field[i][j] != 0; j++) {
      temp += 1;
    }
    if (temp == 10) {
      score++;
      // удаление строки и смещение основного поля на 1 вниз
      remove_lines(game->field, i);
    }
  }
  game_info.score += scores[score];
  if (game_info.high_score < game_info.score) {
    game_info.high_score = game_info.score;
  }
  int temp = game_info.score / 600;
  game_info.speed = temp < 10 ? temp + 1 : 10;
  game_info.level = game_info.speed;
  *state = SpawnFigure;
}
void TetrisModel::gameover_state(GameState_t* state, UserAction_t action) {
  switch (action) {
    case Up:
    case Down:
    case Left:
    case Right:
    case Action:
    case Pause:
    case Start:
      *state = StartGame;
      break;
    case Terminate:
      *state = ExitGame;
      break;
    default:
      *state = GameOver;
      break;
  }
}
void TetrisModel::pause_state(GameState_t* state, UserAction_t action) {
  switch (action) {
    case Up:
    case Down:
    case Left:
    case Right:
    case Action:
    case Pause:
    case Start:
      game_info.pause = 0;
      *state = MoveFigure;
      break;
    case Terminate:
      *state = ExitGame;
      break;
    default:
      game_info.pause = 1;
      *state = PauseGame;
      break;
  }
}
void TetrisModel::move_state(Game_t* game, GameState_t* state) {
#ifdef CLI
  double elapsed = (double)(end_move_timer - start_move_timer) / 10000;
  if (elapsed >= (0.25 - (double)game_info.speed / 500)) {
#endif
    if (proverka(game, 0, 1)) {
      game->curr.y += 1;
      copy_field(game);
      *state = ShiftFigure;
    } else {
      *state = AttachFigure;
    }
#ifdef CLI
    start_move_timer = end_move_timer;
  } else {
    *state = ShiftFigure;
  }
#endif
}
void TetrisModel::shift_state(Game_t* game, GameState_t* state,
                              UserAction_t action) {
  switch (action) {
    case Pause:
      *state = PauseGame;
      break;
    case Terminate:
      *state = ExitGame;
      break;
    default:
      if (dvig(action, state, game)) {
        *state = MoveFigure;
      } else {
        *state = AttachFigure;
      }
      copy_field(game);
      break;
  }
}
void TetrisModel::exit_game_state(GameState_t* state, Game_t* game) {
  free(game->field);
  FILE* file = fopen("./stats_tetris", "w");
  fprintf(file, "%d", game_info.high_score);
  fclose(file);
  *state = DestroyGame;
}
GameInfo_t TetrisModel::updateCurrentState() { return game_info; }
void TetrisModel::updateClock(clock_t time) { end_move_timer = time; }

TetrisController::TetrisController(TetrisModel* m) : model(m){};
TetrisController::~TetrisController() {}
GameState_t TetrisController::updateState() { return game_state; }
GameInfo_t TetrisController::updateInfo() {
  return model->updateCurrentState();
}
void TetrisController::userInput(UserAction_t act, bool hold) {
  static Game_t game;
  hold = 1 - hold;
  switch (game_state) {
    case InitGame:
      model->init_game(&game, &game_state);
      break;
    case StartGame:
      model->start_game(&game, &game_state, act);
      break;
    case SpawnFigure:
      model->spawn_state(&game, &game_state);
      break;
    case MoveFigure:
      model->move_state(&game, &game_state);
      break;
    case ShiftFigure:
      model->shift_state(&game, &game_state, act);
      break;
    case AttachFigure:
      model->attach_state(&game_state, &game);
      break;
    case GameOver:
      model->gameover_state(&game_state, act);
      break;
    case PauseGame:
      model->pause_state(&game_state, act);
      break;
    case ExitGame:
      model->exit_game_state(&game_state, &game);
      break;
    default:
      break;
  }
}
#ifdef DESKTOP
UserAction_t TetrisController::qt_get_signal(QKeyEvent* event) {
  UserAction_t action = MEM;
  switch (event->key()) {
    case Qt::Key_Up:
      action = Up;
      break;
    case Qt::Key_Down:
      action = Down;
      break;
    case Qt::Key_Right:
      action = Right;
      break;
    case Qt::Key_Left:
      action = Left;
      break;
    case Qt::Key_Escape:
      action = Terminate;
      break;  // Выход
    case Qt::Key_Tab:
      action = Pause;
      break;  // Пауза
    case Qt::Key_Space:
      action = Action;
      break;
    case Qt::Key_Return:
      action = Start;
      break;
    default:
      break;
  }
  return action;
}
#endif

#ifdef CLI
UserAction_t TetrisController::get_signal(int key) {
  UserAction_t action = MEM;
  if (key != 0) {
    switch (key) {
      case '\t':
        action = Pause;
        break;
      case 27:
        action = Terminate;
        break;
      case '\n':
        action = Start;
        break;
      case KEY_UP:
        action = Up;
        break;
      case KEY_LEFT:
        action = Left;
        break;
      case KEY_RIGHT:
        action = Right;
        break;
      case KEY_DOWN:
        action = Down;
        break;
      case 32:
        action = Action;
        break;
      default:
        action = Up;
        break;
    }
  }
  return action;
}
#endif

}  // namespace s21
