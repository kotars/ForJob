#pragma once
#include "model.h"

class TetrisController{
    private:
        TetrisModel* model;
        GameState_t game_state = InitGame;
    public:
        TetrisController(TetrisModel* m) : model(m){};
        ~TetrisController(){}
        GameState_t updateState() { return game_state; }

        void userInput(UserAction_t act, bool hold) {
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
                    model->dvigenie_state(&game, &game_state);
                break;
                case ShiftFigure:
                    model->dop(&game, &game_state, act);
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
        
        UserAction_t get_signal(int key) {      
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
                    break;
                }
            }
            return action;
        }
};