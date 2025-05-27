#include "s21_snake.h"
namespace s21 {
SnakeModel::SnakeModel() {
  init_snake();
  start_move_timer = 0;
  end_move_timer = 0;
}
void SnakeModel::init_snake() {
  game_info.field = (int**)malloc(sizeof(int*) * HEIGHT);
  for (int i = 0; i < HEIGHT; i++)
    game_info.field[i] = (int*)calloc(WIDTH, sizeof(int));
  game_info.level = 1;
  game_info.score = 0;
  FILE* f = fopen("stats_snake", "r");
  if (f != NULL) {
    fscanf(f, "%d", &game_info.high_score);
    fclose(f);
  } else
    game_info.high_score = 0;
  game_info.speed = 1;
  game_info.pause = 0;
}
void SnakeModel::init_game(GameSnake_t* game, GameState_t* game_state) {
  game->field = (int**)malloc(HEIGHT * sizeof(int*));
  for (int i = 0; i < HEIGHT; i++)
    game->field[i] = (int*)calloc(WIDTH, sizeof(int));
  clear_game(game);
  *game_state = StartGame;
  update_field(game);
}
void SnakeModel::clear_game(GameSnake_t* game) {
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      game->field[i][j] = 0;
    }
  }
  game->snake.curr = R;
  game->snake.head_x = 2;
  game->snake.head_y = 0;
  (game->snake.coords).clear();
  (game->snake.coords).push_back(std::make_pair(2, 0));
  (game->snake.coords).push_back(std::make_pair(1, 0));
  (game->snake.coords).push_back(std::make_pair(0, 0));
  game_info.level = 1;
  game_info.speed = 1;
  game_info.score = 0;
  game_info.pause = 0;
}
void SnakeModel::start_game(GameSnake_t* game, GameState_t* state,
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
void SnakeModel::update_field(GameSnake_t* game) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      game_info.field[i][j] = 0;
    }
  }
  game_info.field[game->apple.y][game->apple.x] = 3;
  game_info.field[game->snake.head_y][game->snake.head_x] = 2;
  for (size_t i = 1; i < game->snake.coords.size(); i++) {
    game_info.field[game->snake.coords[i].second][game->snake.coords[i].first] =
        1;
  }
}
int SnakeModel::proverka(GameSnake_t* game, int x, int y) {
  int flag = 1;
  for (size_t i = 0; i < game->snake.coords.size() && flag; i++) {
    flag = game->snake.head_x + x == game->snake.coords[i].first &&
                   game->snake.head_y + y == game->snake.coords[i].second
               ? 0
               : 1;
  }
  return flag && game->snake.head_x + x > -1 &&
         game->snake.head_x + x < WIDTH && game->snake.head_y + y > -1 &&
         game->snake.head_y + y < HEIGHT;
}
void SnakeModel::spawn_state(GameSnake_t* game, GameState_t* state) {
  if ((game->snake.coords).size() == 200)
    *state = GameOver;
  else {
    int x = rand() % WIDTH, y = rand() % HEIGHT;
    while (game->field[y][x] != 0) {
      x = rand() % WIDTH;
      y = rand() % HEIGHT;
    }
    game->apple.x = x;
    game->apple.y = y;
    update_field(game);
    *state = MoveFigure;
  }
}
bool SnakeModel::direction_snake(GameSnake_t* game, GameState_t* state, int x,
                                 int y) {
  bool check = true;
  int h = game->snake.head_x, w = game->snake.head_y;
  game->snake.head_x += x;
  game->snake.head_y += y;
  if (game->apple.x == game->snake.head_x &&
      game->apple.y == game->snake.head_y) {
    *state = AttachFigure;
  }
  bool flag = true;
  for (size_t i = 0; i < game->snake.coords.size() && flag; i++) {
    flag = (game->snake.head_x == game->snake.coords[i].first &&
            game->snake.head_y == game->snake.coords[i].second)
               ? false
               : true;
  }
  if (!flag) *state = GameOver;
  for (size_t i = 1; i < game->snake.coords.size() && check; i++) {
    int temp_h, temp_w;
    temp_h = game->snake.coords[i].first;
    temp_w = game->snake.coords[i].second;
    game->snake.coords[i].first = h;
    game->snake.coords[i].second = w;
    h = temp_h;
    w = temp_w;
    if (i == game->snake.coords.size() - 1 &&
        (game->apple.x == game->snake.head_x &&
         game->apple.y == game->snake.head_y)) {
      check = false;
      game->snake.coords.push_back(std::make_pair(h, w));
      game_info.score++;
      *state = AttachFigure;
    }
  }
  return check && flag;
}  // перемещаем уже
void SnakeModel::move_state(GameSnake_t* game, GameState_t* state) {
#ifdef CLI
  double elapsed = (double)(end_move_timer - start_move_timer) / 10000;
  if (elapsed >= (0.25 - (double)game_info.speed / 500)) {
#endif
    int x = 0, y = 0;
    if (game->snake.curr == U)
      y--;
    else if (game->snake.curr == D)
      y++;
    else if (game->snake.curr == L)
      x--;
    else if (game->snake.curr == R)
      x++;
    if (game->snake.head_x + x > -1 && game->snake.head_x + x < WIDTH &&
        game->snake.head_y + y > -1 && game->snake.head_y + y < HEIGHT) {
      if (direction_snake(game, state, x, y)) {
        *state = ShiftFigure;
      }
      update_field(game);
    } else {
      *state = GameOver;
    }
#ifdef CLI
    start_move_timer = end_move_timer;
  } else {
    *state = ShiftFigure;
  }
#endif
}
void SnakeModel::shift_state(GameSnake_t* game, GameState_t* state,
                             UserAction_t action) {
  switch (action) {
    case Pause:
      *state = PauseGame;
      break;
    case Terminate:
      *state = ExitGame;
      break;
    default:
      if (action == Up && game->snake.curr != D) {
        game->snake.curr = U;
      } else if (action == Right && game->snake.curr != L) {
        game->snake.curr = R;
      } else if (action == Left && game->snake.curr != R) {
        game->snake.curr = L;
      } else if (action == Down && game->snake.curr != U) {
        game->snake.curr = D;
      }

      *state = MoveFigure;
      update_field(game);
      break;
  }
}
void SnakeModel::attach_state(GameState_t* state) { *state = SpawnFigure; }
void SnakeModel::pause_state(GameState_t* state, UserAction_t action) {
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
void SnakeModel::gameover_state(GameState_t* state, UserAction_t action) {
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
void SnakeModel::exit_game_state(GameState_t* state, GameSnake_t* game) {
  free(game->field);
  FILE* file = fopen("./stats_snake", "w");
  fprintf(file, "%d", game_info.high_score);
  fclose(file);
  *state = DestroyGame;
}
GameInfo_t SnakeModel::updateCurrentState() { return game_info; }
void SnakeModel::updateClock(clock_t time) { end_move_timer = time; }
SnakeModel::~SnakeModel() {}

SnakeControle::SnakeControle(SnakeModel* m) : model(m){};
#ifdef CLI
UserAction_t SnakeControle::get_signal(int key) {
  if (key != -1) {
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
        break;
    }
  }
  return action;
}
#endif
#ifdef DESKTOP
UserAction_t SnakeControle::qt_get_signal(QKeyEvent* event) {
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
GameState_t SnakeControle::updateState() { return game_state; }
void SnakeControle::userInput(UserAction_t action, bool hold) {
  static GameSnake_t game;
  hold = 1 - hold;
  switch (game_state) {
    case InitGame:
      model->init_game(&game, &game_state);
      break;
    case StartGame:
      model->start_game(&game, &game_state, action);
      break;
    case SpawnFigure:
      model->spawn_state(&game, &game_state);
      break;
    case MoveFigure:
      model->move_state(&game, &game_state);
      break;
    case ShiftFigure:
      model->shift_state(&game, &game_state, action);
      break;
    case AttachFigure:
      model->attach_state(&game_state);
      break;
    case GameOver:
      model->gameover_state(&game_state, action);
      break;
    case PauseGame:
      model->pause_state(&game_state, action);
      break;
    case ExitGame:
      model->exit_game_state(&game_state, &game);
      break;
    default:
      break;
  }
}
GameInfo_t SnakeControle::updateInfo() { return model->updateCurrentState(); }
SnakeControle::~SnakeControle() {}
}  // namespace s21
