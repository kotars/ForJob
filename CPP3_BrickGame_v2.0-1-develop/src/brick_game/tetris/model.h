#pragma once
#include <iostream>
#include <ncurses.h>
#include <time.h>
#include <stddef.h>
#define _BSD_SOURCE
#define HEIGHT 20
#define WIDTH 10

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action,
    MEM
} UserAction_t; 


typedef enum {
  InitGame,
  StartGame,
  PauseGame,
  SpawnFigure,
  MoveFigure,
  ShiftFigure,
  AttachFigure,
  GameOver,
  ExitGame,
  DestroyGame,
} GameState_t;


typedef struct{
  int square_fig[4][4];
  int x, y; // координты фигуры
} Figure_t; 
 
Figure_t figures[7] = {
  { .square_fig = {
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}
    },
    .x = 3,
    .y = -1
  },
  { .square_fig = {
    {0,0,0,0},
    {1,1,1,1},
    {0,0,0,0},
    {0,0,0,0}
    },
    .x = 3,
    .y = -1
  },
  { .square_fig = {
    {0,0,0,0},
    {1,0,0,0},
    {1,1,1,0},
    {0,0,0,0}
    },
    .x = 3,
    .y = -1
  },
  { .square_fig = {
    {0,0,0,0},
    {0,0,1,0},
    {1,1,1,0},
    {0,0,0,0}
    },
    .x = 3,
    .y = -1
  },
  { .square_fig = {
    {0,0,0,0},
    {0,1,1,0},
    {1,1,0,0},
    {0,0,0,0}
    },
    .x = 3,
    .y = -1
  }, 
  { .square_fig = {
    {0,0,0,0},
    {1,1,0,0},
    {0,1,1,0},
    {0,0,0,0}
    },
    .x = 3,
    .y = -1
  },
  { .square_fig = {
    {0,0,0,0},
    {0,1,0,0},
    {1,1,1,0},
    {0,0,0,0}
    },
    .x = 3,
    .y = -1
  }
};

typedef struct {
  int** field;
  Figure_t curr;
  Figure_t next;
} Game_t;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

class TetrisModel{
    private: 
        GameInfo_t game_info;
        clock_t start_move_timer;
        clock_t end_move_timer;
    public:
        TetrisModel(){
            init_tetris();
            start_move_timer = 0;
            end_move_timer = 0;
        }
        ~TetrisModel(){}
        void init_tetris() {
            game_info.field = (int**)malloc(sizeof(int*) * HEIGHT);
            for (int i = 0; i < HEIGHT; i++)
                game_info.field[i] = (int*)calloc(WIDTH, sizeof(int));
            game_info.next = (int**)malloc(sizeof(int*) * 4);
            for (int i = 0; i < 4; i++) game_info.next[i] = (int*)calloc(4, sizeof(int));

            game_info.level = 1;
            game_info.score = 0;
            FILE* f = fopen("./stats", "r");
            if (f != NULL)
                fscanf(f, "%d", &game_info.high_score);
            else
                game_info.high_score = 0;
            game_info.speed = 1;
            game_info.pause = 0;
            fclose(f);
        }
        
        void init_game(Game_t* game, GameState_t* game_state) {
            game->field = (int**)malloc(HEIGHT * sizeof(int*));
            for (int i = 0; i < HEIGHT; i++) game->field[i] = (int*)calloc(WIDTH, sizeof(int));
            copy_figure(&game->next, &figures[rand() % 7]);
            *game_state = StartGame;
        }

        void clear_game(Game_t* game) {
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

        void start_game(Game_t* game, GameState_t* state, UserAction_t action) {
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
        void copy_figure(Figure_t* curr, const Figure_t* fig) {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++) curr->square_fig[i][j] = fig->square_fig[i][j];
            curr->x = fig->x;
            curr->y = fig->y;
        }
        void copy_field(Game_t* game) {
            for (int i = 0; i < HEIGHT; i++)
                for (int j = 0; j < WIDTH; j++) game_info.field[i][j] = game->field[i][j];
            copy_figure_to_field(game_info.field, &game->curr);
        }

        void copy_figure_to_field(int** field, Figure_t* fig) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                if (fig->square_fig[i][j])
                    field[fig->y + i][fig->x + j] = fig->square_fig[i][j];
                }
            }
        }

        int proverka(Game_t* game, int x, int y) {
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

        void spawn_state(Game_t* game, GameState_t* state) {
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

        //проверка на соприкосновение с фигурами, проверять заполненность поля +++
        int issquare_line(Game_t* game) {
        return (game->curr.square_fig[1][1] && game->curr.square_fig[1][2] &&
                game->curr.square_fig[2][1] && game->curr.square_fig[2][2]) ||
                        (game->curr.square_fig[1][0] && game->curr.square_fig[1][1] &&
                        game->curr.square_fig[1][2] && game->curr.square_fig[1][3])
                    ? 4
                    : 3;
        }

        int move_state(UserAction_t action, GameState_t* state, Game_t* game) {
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

        void remove_lines(int** field, int y) {
            for (int i = y - 1; i >= 0; i--)
                for (int j = 0; j < WIDTH; j++) field[i + 1][j] = field[i][j];
        }
        void attach_state(GameState_t* state, Game_t* game) {
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
        void gameover_state(GameState_t* state, UserAction_t action) {
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
        void pause_state(GameState_t* state, UserAction_t action) {
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

        void dvigenie_state(Game_t* game, GameState_t* state) {
            double elapsed = (double)(end_move_timer - start_move_timer) / 10000;
            if (elapsed >= (0.25 - (double)game_info.speed / 500)) {
                if (proverka(game, 0, 1)) {
                    game->curr.y += 1;
                    copy_field(game);
                    *state = ShiftFigure;
                } else {
                    *state = AttachFigure;
                }
                start_move_timer = end_move_timer;
            } else {
                *state = ShiftFigure;
            }
        }

        void dop(Game_t* game, GameState_t* state, UserAction_t action) {
            switch (action) {
                case Pause:
                    *state = PauseGame;
                break;
                case Terminate:
                    *state = ExitGame;
                break;
                default:
                if (move_state(action, state, game)) {
                    *state = MoveFigure;
                } else {
                    *state = AttachFigure;
                }
                copy_field(game);
                break;
            }
        }

        void exit_game_state(GameState_t* state, Game_t* game) {
            free(game->field);
            FILE* file = fopen("./stats", "w");
            fprintf(file, "%d", game_info.high_score);
            fclose(file);
            *state = DestroyGame;
        }

       
        GameInfo_t updateCurrentState() { return game_info; }
        void updateClock(clock_t time) { end_move_timer = time; }
};
