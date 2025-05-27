#pragma once
#ifdef TETRIS
#include "../../brick_game/tetris/s21_tetris.h"
#endif
#ifdef SNAKE
#include "../../brick_game/snake/s21_snake.h"
#endif
// #include "../../brick_game/s21_brick_game.h"
namespace s21{
    template<typename T>
class ConsoleView{
    private:
        T *controller;
    public:
        ConsoleView(T *c):controller(c){};
        ~ConsoleView(){};

        void print_start() {
            clear();
            mvprintw(9, 7, "Start game");
            mvprintw(10, 4, "Click different key");
            refresh();
        }
        void print_end() {
            clear();
            mvprintw(9, 7, "End game");
            mvprintw(10, 4, "Clcik different key");
            refresh();
        }
        void print_field() {
            mvprintw(1, 25, "Record:");
            mvaddch(0, 0, ACS_ULCORNER);
            mvaddch(0, WIDTH + 1, ACS_URCORNER);
            mvaddch(HEIGHT + 1, 0, ACS_LLCORNER);
            mvaddch(HEIGHT + 1, WIDTH + 1, ACS_LRCORNER);
            for (int i = 1; i < WIDTH + 1; i++) {
                mvaddch(0, i, ACS_HLINE);
                mvaddch(HEIGHT + 1, i, ACS_HLINE);
            }
            for (int i = 1; i < HEIGHT + 1; i++) {
                mvaddch(i, 0, ACS_VLINE);
                mvaddch(i, WIDTH + 1, ACS_VLINE);
            }
        }
        void print_board(GameInfo_t game) {
            clear();
            print_field();
            mvprintw(1, 20, "High score: %d", game.high_score);
            mvprintw(4, 20, "Score: %d", game.score);
            mvprintw(7, 20, "Level: %d", game.level);
            mvprintw(10, 20, "Speed: %d", game.speed);
            #ifdef TETRIS
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                mvprintw(13 + i, 20 + j, game.next[i][j] ? "#" : " ");
                }
            }
            for (int i = 1; i < HEIGHT + 1; i++)
                for (int j = 1; j < WIDTH + 1; j++)
                mvprintw(i, j, game.field[i - 1][j - 1] ? "#" : ".");
            #endif
            #ifdef SNAKE
            for (int i = 1; i < HEIGHT + 1 ; i++)
                for (int j = 1; j < WIDTH + 1; j++){
                    if(game.field[i - 1][j - 1] == 1)
                        mvprintw(i, j, "-");
                    else if(game.field[i-1][j-1] == 2)
                        mvprintw(i, j, "+");
                    else if(game.field[i-1][j-1] == 3)
                        mvprintw(i, j, "#");
                    else
                        mvprintw(i, j,".");
                }
            #endif
            refresh();
        }
};
}