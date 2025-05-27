#ifndef S21_BRICK_GAME_H
#define S21_BRICK_GAME_H
#include <vector>

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
    int x,y;
    bool apple_in_field;
} AppleInfo_t;

typedef enum { L, R, U, D } Snake_direction;

typedef struct{
    int head_x, head_y;
    Snake_direction curr;
    std::vector<std::pair<int,int>> coords;
} SnakeInfo_t;

typedef struct {
    int** field;
    AppleInfo_t apple;
    SnakeInfo_t snake;
} GameSnake_t;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;


typedef struct{
    int square_fig[4][4];
    int x, y; // координты фигуры
} Figure_t;

typedef struct {
    int** field;
    Figure_t curr;
    Figure_t next;
} Game_t;

#endif