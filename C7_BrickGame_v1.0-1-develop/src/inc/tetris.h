#ifndef TETRIS_H
#define TETRIS_H
#include <stdio.h>
#include <stdlib.h>
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
    Action
} UserAction_t; 

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;
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
  int x, y; // координты фигуры
  int square_fig[4][4];
} Figure_t; 
 
static const Figure_t figures[7] = {
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

void init_tetris();

UserAction_t get_signal(int key);
void userInput(UserAction_t action, bool hold);
void print_board(GameInfo_t game);
void clear_tetris(GameInfo_t* game);

void init_game(Game_t* game, GameState_t* game_state);
void start_game(Game_t* game, GameState_t* state, UserAction_t action);
void copy_figure(Figure_t* curr, const Figure_t* fig);
void copy_field(Game_t* game);
void copy_figure_to_field(int** field, Figure_t* fig);
void spawn_state(Game_t* game, GameState_t* state);
int move_state(UserAction_t action, GameState_t* state, Game_t* game);
int issquare_line(Game_t* game);
void gameover_state(GameState_t* state, UserAction_t action);
//для получения состояния в game_loop()
GameInfo_t updateCurrentState();
GameState_t updateState();
void updateClock(clock_t time);
#endif