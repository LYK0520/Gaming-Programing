#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <sstream>
#include "Tetris.h"
using namespace sf;
#define B_START_CORNER_X 621
#define B_START_CORNER_Y 743
#define B_HOLD_CORNER_X 621
#define B_HOLD_CORNER_Y 802
#define B_LEFT_CORNER_X 70
#define B_LEFT_CORNER_Y 440
#define B_RIGHT_CORNER_X 1295
#define B_RIGHT_CORNER_Y 440
#define P1_STAGE_CORNER_X 156
#define P1_STAGE_CORNER_Y 154
#define P2_STAGE_CORNER_X 844
#define P2_STAGE_CORNER_Y 154
#define P1_NEXT_CORNER_X 587
#define P1_NEXT_CORNER_Y 105
#define P2_NEXT_CORNER_X 702
#define P2_NEXT_CORNER_Y 105
#define P1_SCORE_CORNER_X 160
#define P1_SCORE_CORNER_Y 860
#define P2_SCORE_CORNER_X 850
#define P2_SCORE_CORNER_Y 860
#define INFO_CORNER_X 585
#define INFO_CORNER_Y 430
typedef enum ButtonState
{
    Continue_Dark, // 继续
    Continue_Light,
    Hold_Dark, // 暂停
    Hold_Light,
    Close_Dark, // 结束
    Close_Light,
    Start_Dark, // 开始
    Start_Light,
};
class Game
{
public:
    Game();
    ~Game();
    RenderWindow window;
    Tetris player1, player2;
    bool gameOver, gameQuit;
    Clock clock;
    int Window_width, Window_height, stageWidth, stageHeight;
    bool isGameBegin, isGameHold; //游戏是否开始
    int isGameOverState;          //游戏结束的状态
    Vector2i mCornPoint;          //游戏区域位置
    int gridSize;                 //块的大小
    int imgSetNo = 1;
    int imgBGNo, imgSkinNo = 1;
    Texture tBackground, tTiles, tButtons, tSwitcher, tFrame, tCover, tScore, tGameOver; //创建纹理对象
    Sprite sBackground, sTiles, sButtons, sSwitcher, sFrame, sCover, sScore, sGameOver;  //创建精灵对象
    IntRect ButtonRectStart, ButtonRectHold, ButtonRectLeft, ButtonRectRight;
    int ButtonState_Start, ButtonState_Hold;
    SoundBuffer sbWin, sbBoom;
    Sound soundWin, soundBoom;
    Music bkMusic;
    Clock gameClock, mouseClickTimer;
    void gameInitial();
    void LoadMediaData();

    Font font;
    Text text;
    void gameInput();
    void gameLogic();
    void gameDraw();
    void gameRun();
    void DrawButton();
    void DrawResults();
    void TextOut();
};