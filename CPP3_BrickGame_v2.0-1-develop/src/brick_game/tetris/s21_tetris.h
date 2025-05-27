#ifndef TETRIS_H
#define TETRIS_H
#include <iostream>
#include <stddef.h>
#define _BSD_SOURCE
#define HEIGHT 20
#define WIDTH 10
#ifdef CLI
#include <ncurses.h>
#include <time.h>
#endif
#ifdef DESKTOP
#include <QKeyEvent>
#endif
#include "../s21_brick_game.h"



namespace s21{


class TetrisModel{
private:
    GameInfo_t game_info;
    clock_t start_move_timer;
    clock_t end_move_timer;
public:
    TetrisModel();
    ~TetrisModel();
    void init_tetris();
    void init_game(Game_t* game, GameState_t* game_state);
    void clear_game(Game_t* game);
    void start_game(Game_t* game, GameState_t* state, UserAction_t action);
    void copy_figure(Figure_t* curr, const Figure_t* fig);
    void copy_field(Game_t* game);
    void copy_figure_to_field(int** field, Figure_t* fig);
    int proverka(Game_t* game, int x, int y);
    void spawn_state(Game_t* game, GameState_t* state);
    int issquare_line(Game_t* game);
    int dvig(UserAction_t action, GameState_t* state, Game_t* game);
    void remove_lines(int** field, int y) ;
    void attach_state(GameState_t* state, Game_t* game);
    void gameover_state(GameState_t* state, UserAction_t action);
    void pause_state(GameState_t* state, UserAction_t action);
    void move_state(Game_t* game, GameState_t* state) ;
    void qt_move_state(Game_t* game, GameState_t* state);
    void shift_state(Game_t* game, GameState_t* state, UserAction_t action);
    void exit_game_state(GameState_t* state, Game_t* game);
    GameInfo_t updateCurrentState();
    void updateClock(clock_t time);
};

class TetrisController{
private:
    TetrisModel* model;
    GameState_t game_state = InitGame;
public:
    TetrisController(TetrisModel* m);
    ~TetrisController();
    GameState_t updateState();
    GameInfo_t updateInfo();
    void userInput(UserAction_t act, bool hold) ;
#ifdef DESKTOP
    UserAction_t qt_get_signal(QKeyEvent* event);
#endif

// #ifdef CLI
    UserAction_t get_signal(int key);
// #endif
};
}
#endif // TETRIS_H
