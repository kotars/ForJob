#ifndef S21_SNAKE_H
#define S21_SNAKE_H
#include <iostream>
#ifdef CLI
#include <ncurses.h>
#include <time.h>
#endif
#ifdef DESKTOP
#include <QKeyEvent>
#endif
#include "../s21_brick_game.h"

#define HEIGHT 20
#define WIDTH 10



namespace s21{
class SnakeModel
{
private:
    GameInfo_t game_info;
    clock_t start_move_timer;
    clock_t end_move_timer;
public:
    SnakeModel();
    void init_snake() ;
    void init_game(GameSnake_t * game, GameState_t* game_state);
    void clear_game(GameSnake_t* game) ;
    void start_game(GameSnake_t* game, GameState_t* state, UserAction_t action) ;
    void update_field(GameSnake_t* game);
    int proverka(GameSnake_t* game, int x, int y);
    void spawn_state(GameSnake_t* game, GameState_t* state);
    bool direction_snake(GameSnake_t* game, GameState_t *state, int x, int y);
    void move_state(GameSnake_t* game, GameState_t* state);
    void shift_state(GameSnake_t* game, GameState_t* state, UserAction_t action);

    void attach_state(GameState_t* state) ;
    void pause_state(GameState_t* state, UserAction_t action) ;
    void gameover_state(GameState_t* state, UserAction_t action) ;
    void exit_game_state(GameState_t* state, GameSnake_t* game) ;
    GameInfo_t updateCurrentState() ;
    void updateClock(clock_t time) ;
    ~SnakeModel();
};

class SnakeControle
{
private:
    SnakeModel *model;
    UserAction_t action = Action;
    GameState_t game_state = InitGame;
public:
    SnakeControle(SnakeModel *m);

// #ifdef CLI
    UserAction_t get_signal(int key);
// #endif
#ifdef DESKTOP
    UserAction_t qt_get_signal(QKeyEvent* event);
#endif
    GameState_t updateState();
    void userInput(UserAction_t action, bool hold);
    GameInfo_t updateInfo();
    ~SnakeControle();
};

};

#endif // SNAKE_H

