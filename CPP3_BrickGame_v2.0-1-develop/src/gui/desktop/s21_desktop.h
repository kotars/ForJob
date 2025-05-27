#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define SQUARE_SIZE 40
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QLabel>
#include <QString>
#include <QMessageBox>
#ifdef TETRIS
#include "../../brick_game/tetris/s21_tetris.h"
#endif
#ifdef SNAKE
#include "../../brick_game/snake/s21_snake.h"
#endif
namespace s21{
template<typename T>
class MainWindow : public QWidget
{
public:
    MainWindow(T *c) : cont(c){
        init_game();
    }
    void init_game(){
        this->setWindowTitle("BrickGame");
        this->setFixedWidth(600);
        this->setFixedHeight(800);
        cont->userInput(Action,false);
        game_info = cont->updateInfo();
        game_state = cont->updateState();
        labelScore = new QLabel(this);
        labelHighScore = new QLabel(this);
        labelSpeed = new QLabel(this);
        labelLvl = new QLabel(this);
        start = new QLabel(this);
        timer = startTimer(250);
    }
    void timerEvent(QTimerEvent* event){
        Q_UNUSED(event);
        this->killTimer(timer);
        timer = startTimer(250);
        cont->userInput(act, false);
        game_info = cont->updateInfo();
        game_state = cont->updateState();
        this->repaint();

    }
    void paintEvent(QPaintEvent* event){
        Q_UNUSED(event);
        switch(game_state){
        case StartGame:
            print_start();
            break;
        case GameOver:
            print_end();
            break;
        default:
            print_board();
            break;
        }
    }
    void keyPressEvent(QKeyEvent* event){
        Q_UNUSED(event);
        #ifdef SNAKE
            act = cont->qt_get_signal(event);
            cont->userInput(act, false);
        #endif
        #ifdef TETRIS 
            UserAction_t act1 = cont->qt_get_signal(event);
            cont->userInput(act1, false);
        #endif
        game_info = cont->updateInfo();
        game_state = cont->updateState();
    }

    void print_start(){
        start->setText("Start Game, Please press Enter");
        start->move(300, 400);
        start->setFixedSize(200, 50);
        start->show();
    }
    void print_end(){
        labelSpeed->close();
        labelHighScore->close();
        labelScore->close();
        labelLvl->close();
        QMessageBox msgt;
        if (game_info.score == HEIGHT * WIDTH) {
            msgt.setText("You win!");
        } else {
            msgt.setText("Game over!");
        }
        msgt.exec();
    }
    void LabelSet(QLabel* lable, int x, int y, QString str){
        lable->setText(str);
        lable->move(x,y);
        lable->setFixedSize(200, 50);
        lable->show();
    }
    void print_board(){
        start->close();
        QPainter qp(this);
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (game_info.field[i][j] == 0) {
                    qp.setBrush((QBrush(Qt::white, Qt::SolidPattern)));
                    qp.drawRect(40 * j, 40 * i, SQUARE_SIZE, SQUARE_SIZE);
                } else if (game_info.field[i][j] == 1) {
                    qp.setBrush((QBrush(Qt::green, Qt::SolidPattern)));
                    qp.drawRect(40 * j, 40 * i, SQUARE_SIZE, SQUARE_SIZE);
                } else if (game_info.field[i][j] == 3) {
                    qp.setBrush((QBrush(Qt::red, Qt::SolidPattern)));
                    qp.drawRect(40 * j, 40 * i, SQUARE_SIZE, SQUARE_SIZE);
                } else {
                    qp.setBrush((QBrush(Qt::darkGreen, Qt::SolidPattern)));
                    qp.drawRect(40 * j, 40 * i, SQUARE_SIZE, SQUARE_SIZE);
                }
            }
        }
        LabelSet(labelScore, 450, 40, QString::number(game_info.score ));
        LabelSet(labelHighScore, 450, 80, QString::number(game_info.high_score));
        LabelSet(labelSpeed, 450, 120, QString::number(game_info.speed));
        LabelSet(labelLvl, 450, 160, QString::number(game_info.level));
    }
    ~MainWindow(){}

private:
    QLabel* labelScore,* labelHighScore,* labelSpeed,* labelLvl, * start;
    int timer;
    UserAction_t act;
    GameInfo_t game_info;
    GameState_t game_state;
    T* cont;
};
};
#endif // MAINWINDOW_H
