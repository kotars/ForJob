#pragma once
#include "Snake.h"

namespace s21
{
    class SnakeControle
    {
    private:
        SnakeModel *model;
        UserAction_t action = Action;
        GameState_t game_state = InitGame;    
    public:
        SnakeControle(SnakeModel *m) : model(m){};

        UserAction_t get_signal(int key) {
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
        GameState_t updateState() { return game_state; }
        void userInput(UserAction_t action, bool hold){
            static Game_t game;
            mvprintw(10, 30, "%d %d", game_state, action);
            refresh();
            switch(game_state){
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
                    model->move_state(&game, &game_state, action);
                    break;
                case ShiftFigure:
                    model->shift_state(&game, &game_state, action);
                    break;
                case AttachFigure:
                    model->attach_state(&game_state, &game);
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
        ~SnakeControle(){}
    };
    
} // namespace s21
