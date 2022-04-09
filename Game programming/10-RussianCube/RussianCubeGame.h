#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<windows.h>
#include<iostream>
#include<sstream>
#include"10-1-3Tetris.h"
using namespace sf;

class Game
{
    public:
        Game();
        ~Game();
        RenderWindow window;
        Tetris player1,player2;
        bool gameOver,gameQuit;
        Clock clock;
        int Window_width,Window_height,stageWidth,stageHeight;
        bool isGameBegin;//游戏是否开始
        int isGameOverState;//游戏结束的状态
        Vector2i mCornPoint;//游戏区域位置
        int gridSize;//块的大小
        int imgBGNo,imgSkinNo=1;
        Texture tBackground,tTiles,tButtons,tSwitcher,tFrame,tCover,tScore,tGameOver;//创建纹理对象
        Sprite sBackground,sTiles,sButtons,sSwitcher,sFrame,sCover,sScore,sGameOver;//创建精灵对象
        IntRect ButtonRectStart,ButtonRectHolt,ButtonRectLeft,ButtonRectRight;
        int ButtonState_Start,ButtonState_Hold;
        SoundBuffer sbWin,sbBoom;
        Sound soundWin,soundBoom;
        Music bkMusic;
        Clock gameClock,mouseClickTimer;
        void gameInitial();
        void LoadMediaData();

        void gameInput();
        void gameLogic();
        void gameDraw();
        void gameRun();
};
