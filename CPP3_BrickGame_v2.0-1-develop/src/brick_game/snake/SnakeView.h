#pragma once
#include "SnakeControle.h"


namespace s21
{
    class SnakeView
    {
    private:
        SnakeControle* controller;
        
    public:
        SnakeView(SnakeControle* c) : controller(c) {};
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
        void print_board(GameInfo_t game){
            clear();
            print_field();
            mvprintw(1, 30, "High score: %d", game.high_score);
            mvprintw(4, 30, "Score: %d", game.score);
            mvprintw(7, 30, "Level: %d", game.level);
            mvprintw(10, 30, "Speed: %d", game.speed);
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
            refresh();
        }
        
        void qt_print(){
            
        }
        ~SnakeView(){}
    };
} // namespace s21
