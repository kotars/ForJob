#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>


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


namespace s21{
    class SnakeModel
    {
    private:     
        GameInfo_t game_info;
        clock_t start_move_timer;
        clock_t end_move_timer;
    public:
        SnakeModel(){
            init_snake();
            start_move_timer = 0;
            end_move_timer = 0;
        }
        void init_snake() {
            game_info.field = (int**)malloc(sizeof(int*) * HEIGHT);
            for (int i = 0; i < HEIGHT; i++)
                game_info.field[i] = (int*)calloc(WIDTH, sizeof(int));
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
        void init_game(Game_t * game, GameState_t* game_state){
            game->field = (int**)malloc(HEIGHT * sizeof(int*));
            for (int i = 0; i < HEIGHT; i++) game->field[i] = (int*)calloc(WIDTH, sizeof(int));
            clear_game(game);
            *game_state = StartGame;
            update_field(game);
        }
        void clear_game(Game_t* game) {
            for (int i = 0; i < HEIGHT; ++i) {
                for (int j = 0; j < WIDTH; ++j) {
                    game->field[i][j] = 0;
                }
            }
            game->snake.curr = R;
            game->snake.head_x = 2;
            game->snake.head_y = 0;
            (game->snake.coords).clear();
            (game->snake.coords).push_back(std::make_pair(0,2)); 
            (game->snake.coords).push_back(std::make_pair(0,1)); 
            (game->snake.coords).push_back(std::make_pair(0,0)); 
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
        
        void update_field(Game_t* game){
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    game_info.field[i][j] = 0;
                }
            }
            game_info.field[game->apple.y][game->apple.x] = 3;
            game_info.field[game->snake.head_y][game->snake.head_x] = 2;
            for(size_t i = 1; i < game->snake.coords.size(); i++){
                game_info.field[game->snake.coords[i].second][game->snake.coords[i].first] = 1;
            }
        }

        int proverka(Game_t* game, int x, int y) {
            int flag = 1;
            for(size_t i = 0; i < game->snake.coords.size() && flag; i++){
                flag = game->snake.head_x + x == game->snake.coords[i].first && game->snake.head_y + y == game->snake.coords[i].second ? 0 : 1;
            }
            return flag && game->snake.head_x + x > -1 && game->snake.head_x + x < WIDTH && game->snake.head_y + y > -1 && game->snake.head_y + y < HEIGHT;
        }

        void spawn_state(Game_t* game, GameState_t* state) {
            if ((game->snake.coords).size() == 200)
                *state = GameOver;
            else {
                int x = rand() % WIDTH, y = rand() % HEIGHT;
                while(game->field[y][x] != 0){
                    x = rand() % WIDTH;
                    y = rand() % HEIGHT;
                }
                game->apple.x = x;
                game->apple.y = y;
                update_field(game);
                *state = MoveFigure;
            }

        }

        bool direction_snake(Game_t* game, GameState_t *state, int x, int y){
            bool check = true;
            int h = game->snake.head_x, w = game->snake.head_y;
            game->snake.head_x += x;
            game->snake.head_y += y;
            if (game->apple.x == game->snake.head_x && game->apple.y == game->snake.head_y) {
                game_info.score++;
                *state = AttachFigure;
            }
            bool flag = true;
            for(size_t i = 0; i < game->snake.coords.size() && flag; i++){
                flag = (game->snake.head_x == game->snake.coords[i].first && game->snake.head_y == game->snake.coords[i].second ) ? false : true;
            }
            if(!flag) *state = GameOver;
            for(size_t i = 1; i < game->snake.coords.size() && check; i++){
                int temp_h, temp_w;
                temp_h = game->snake.coords[i].first;
                temp_w = game->snake.coords[i].second;
                game->snake.coords[i].first = h;
                game->snake.coords[i].second = w;
                h = temp_h;
                w = temp_w;
                if (i == game->snake.coords.size() - 1 && (game->apple.x == game->snake.head_x && game->apple.y == game->snake.head_y)) {
                    check = false;
                    game->snake.coords.push_back(std::make_pair(h, w));
                    game_info.score++;
                    *state = AttachFigure;
                }
            }
            return check && flag;
        } //перемещаем уже
        
        void move_state(Game_t* game, GameState_t* state, UserAction_t action){
            double elapsed = (double)(end_move_timer - start_move_timer) / 10000;
            if (elapsed >= (0.25 - (double)game_info.speed / 500)) {
                int x = 0, y = 0;
                if(game->snake.curr == U) y--;
                else if(game->snake.curr == D) y++;
                else if(game->snake.curr == L) x--;
                else if(game->snake.curr == R) x++;
                if(game->snake.head_x + x > -1 && game->snake.head_x + x < WIDTH && game->snake.head_y + y > -1 && game->snake.head_y + y < HEIGHT){
                    if(direction_snake(game, state, x, y)){ 
                        *state = ShiftFigure;
                    }
                    update_field(game);
                }else{
                    *state = GameOver;
                }
                start_move_timer = end_move_timer;

            } else{
                *state = ShiftFigure;
            }
        }

        void shift_state(Game_t* game, GameState_t* state, UserAction_t action){
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
                }
                else if (action == Right && game->snake.curr != L) {
                    game->snake.curr = R;
                }
                else if (action == Left && game->snake.curr != R) {
                    game->snake.curr = L;
                }
                else if (action == Down && game->snake.curr != U) {
                    game->snake.curr = D;
                }
                
                
                *state = MoveFigure;
                update_field(game);
                break;
            }
        }

        void attach_state(GameState_t* state, Game_t* game) {
            *state = SpawnFigure;
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

        void exit_game_state(GameState_t* state, Game_t* game) {
            free(game->field);
            FILE* file = fopen("./stats", "w");
            fprintf(file, "%d", game_info.high_score);
            fclose(file);
            *state = DestroyGame;
        }

        GameInfo_t updateCurrentState() { return game_info; }

        void updateClock(clock_t time) { end_move_timer = time; }

        ~SnakeModel(){}
    };
};