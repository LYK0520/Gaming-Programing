#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include<iostream>
#include<sstream>
#define GRIDSIZE  35
#define STAGE_WIDTH 10
#define STAGE_HEIGHT 20
#define P1_STAGE_CORNER_X 156
#define P1_STAGE_CORNER_Y 174
#define P2_STAGE_CORNER_X 844
#define P2_STAGE_CORNER_Y 174
#define P1_NEXT_CORNER_X 587
#define P1_NEXT_CORNER_Y 125
#define P2_NEXT_CORNER_X 702
#define P2_NEXT_CORNER_Y 125
#define HOLD_CORNER_X 660
#define HOLD_CORNER_Y 275

using namespace sf;
class Tetris
{
    public:
        Tetris();
        ~Tetris();
        Vector2i mCornPoint,nextSquareCornPoint,holdSquareCornPoint;//游戏区域位置
        
        int gridSize;//块大小
        int imgBGNo,imgSkinNo;
        int role;
        Texture *tTiles;
        Texture tBackground,tButtons,tNum,tTimer,tCounter,tGameOver;//创建纹理对象
        Sprite  sBackground,sTiles,sButtons,sNum,sTimer,sCounter,sGameOver;//创建精灵对象

        int Field[STAGE_HEIGHT][STAGE_WIDTH]={0};
        Vector2i currentSquare[4],nextSquare[4],holdSquare[4],tempSquare[4];
        int Figures[7][4]=
        {
            1,3,5,7, //I
            2,4,5,6, //S
            3,4,5,6, //Z
            3,4,5,7, //T
            2,3,5,7, //L
            3,5,6,7, //J
            2,3,4,5, //O
        };

        int dx;
        bool rotate,hold;
        int colorNum;
        float timer,delay;

        int colorNum,nextColorNum,tempcolorNum;
        int currentShapeNum,nextShapeNum,tempShapeNum;

        static int holdcolorNum,holdShapeNum;
        static Vector2i holdSquare[4];
        int b7array[7]={0},b7Int;
        int Bag7();
        void Initial(Texture *tex);
        void Input(sf::Event event);
        void Logic();
        void Draw(sf::RenderWindow* window);
        bool hitTest();
        void Rotate();
        //void TickDrop();
        void CheckLine();
        void yMove();
};
Tetris::Tetris()
{
    dx=0;//X方向偏移量
    rotate=false;//是否旋转
    colorNum=1;//色块的颜色
    timer=0;
    delay=0.3; //下落的速度
}
Tetris::~Tetris()
{
}
void Tetris::Logic()
{
    yMove();
    ///<-水平Move->///
    for(int i=0;i<4;i++)
    {
        tempSquare[i]=currentSquare[i];
        currentSquare[i].x+=dx;
    }
    if(!hitTest())
    {
        for(int i=0;i<4;i++)
        {
            currentSquare[i]=tempSquare[i];//到左右的边界，不能移出边界
        }
    }
}

bool Tetris::hitTest()
{
    for(int i=0;i<4;i++)
    {
        if(currentSquare[i].x<0 || currentSquare[i].x>=STAGE_WIDTH||currentSquare[i].y>=STAGE_HEIGHT)
        {
            return false;
        }else if(Field[currentSquare[i].y][currentSquare[i].x])
        {
            return false;
        }
    }
    return true;
}
////////////
//Rotate
void Tetris::Rotate()
{
    if(rotate)
    {
        Vector2i p=currentSquare[1];//设置旋转中心点
        for(int i=0;i<4;i++)
        {
            //顺时针旋转90
            int x=currentSquare[i].y-p.y;//原Y方向距离中心点的差值，作为新的差值，传递给X方向
            int y=currentSquare[i].x-p.x;//原X方向距离中心点的差值，作为新的差值，传递给Y方向
            currentSquare[i].x=p.x-x;//新坐标X=中心点坐标-新的X方向差值
            currentSquare[i].y=p.y+y;//新坐标Y=中心点坐标+新的Y方向差值
        }
        if(!hitTest())
        {
            for(int i=0;i<4;i++)
            {
                currentSquare[i]=tempSquare[i];
            }
        }
    }
}

//////////////
//Tick下落
void Tetris::yMove()
{
    if(timer>delay)
    {
        for(int i=0;i<4;i++)
        {
            tempSquare[i]=currentSquare[i];
            currentSquare[i].y+=1;
        }

        if(!hitTest())
        {
            for(int i=0;i<4;i++)
            {
                Field[tempSquare[i].y][tempSquare[i].x]=colorNum;
            }
            colorNum=nextColorNum;
            currentShapeNum=nextShapeNum;
            //更新下一个方块图形
            nextShapeNum=rand()%7;
            nextColorNum=rand()%7+1;
            for(int i=0;i<4;i++)
            {
                currentSquare[i]=nextSquare[i];
                currentSquare[i].x+=STAGE_WIDTH/2;
                nextSquare[i].x=Figures[nextShapeNum][i]%2;
                nextSquare[i].y=Figures[nextShapeNum][i]/2;
            }
        }
        timer=0;
    }
}

void Tetris::CheckLine()
{
    int k=STAGE_HEIGHT-1;
    for(int i=STAGE_HEIGHT-1;i>0;i--)
    {
        int count=0;
        for(int j=0;j<STAGE_WIDTH;j++)
        {
            if(Field[i][j])
            {
                count++;
            }
            Field[k][j]=Field[i][j];
        }
        if(count<STAGE_WIDTH) k--;
    }

}

typedef enum PLAYROLE{
    roleNONE,
    rolePLAYER1,
    rolePLAYER2,
};
void Tetris::Initial(Texture *tex)
{
    tTiles=tex;
    dx=0;
    rotate=false;
    hold=false;//是否有hold块图形
    colorNum=1;
    timer=0;
    delay=DALAYVALUE;
    holdSquareCornPoint={HOLD_CORNER_X,HOLD_CORNER_Y};
    sTiles.setTexture(*tTiles);
    b7Int=0;
   if(role==rolePLAYER1)
   {
       mCornPoint={P1_STAGE_CORNER_X,P1_STAGE_CORNER_Y};
         nextSquareCornPoint={P1_NEXT_CORNER_X,P1_NEXT_CORNER_Y};
   }
   if(role==rolePLAYER2)
   {
         mCornPoint={P2_STAGE_CORNER_X,P2_STAGE_CORNER_Y};
            nextSquareCornPoint={P2_NEXT_CORNER_X,P2_NEXT_CORNER_Y};
   }
   sTiles.setTexture(*tTiles);
   //初始化方块图形
    colorNum=1+rand()%7;
    currentShapeNum=rand()%7;
    //更新下一个方块图形
    nextColorNum=1+rand()%7;
    nextShapeNum=rand()%7;
    //int n=rand()%7;
    for(int i=0;i<4;i++)
    {
        currentSquare[i].x=Figures[currentShapeNum][i]%2+STAGE_WIDTH/2;
        currentSquare[i].y=Figures[currentShapeNum][i]/2;
        nextSquare[i].x=Figures[nextShapeNum][i]%2;
        nextSquare[i].y=Figures[nextShapeNum][i]/2;
    }
    holdShapeNum=-1;//在游戏开始，将hold区的图形设置为一个异常值
}

void Tetris::Input(sf::Event event)
{
   if(role==rolePLAYER1)
   {
       if(event.type==sf::Event::KeyPressed)
       {
           if(event.key.code==sf::Keyboard::A)
           {
               dx=-1;
              // rotate=false;
           }
           if(event.key.code==sf::Keyboard::D)
           {
               dx=1;
               //rotate=false;
           }
           if(event.key.code==sf::Keyboard::W)
           {
               rotate=true;
           }
           if(event.key.code==sf::Keyboard::S)
           {
               delay=DALAYVALUE/10;
           }
       }
       if(event.type==Event::KeyReleased)
       {
           if(event.key.code==Keyboard::LControl)
           {
               hold=true;
           }
              if(event.key.code==sf::Keyboard::A)
              {
                dx=0;
              }
              if(event.key.code==sf::Keyboard::D)
              {
                dx=0;
              }
            //   if(event.key.code==sf::Keyboard::W)
            //   {
            //     rotate=false;
            //   }
              if(event.key.code==sf::Keyboard::S)
              {
                delay=0.3;
              }
       }
   }
   if(role==rolePLAYER2)
   {
       if(event.type==sf::Event::KeyPressed)
       {
           if(event.key.code==sf::Keyboard::Left)
           {
               dx=-1;
              // rotate=false;
           }
           if(event.key.code==sf::Keyboard::Right)
           {
               dx=1;
               //rotate=false;
           }
           if(event.key.code==sf::Keyboard::Up)
           {
               rotate=true;
           }
           if(event.key.code==sf::Keyboard::Down)
           {
               delay=0.05;
           }
       }
       if(event.type==Event::KeyReleased)
       {
              if(event.key.code==sf::Keyboard::Left)
              {
                dx=0;
              }
              if(event.key.code==sf::Keyboard::Right)
              {
                dx=0;
              }
            //   if(event.key.code==sf::Keyboard::Up)
            //   {
            //     rotate=false;
            //   }
              if(event.key.code==sf::Keyboard::Down)
              {
                delay=0.3;
              }
       }
   }
}

void Tetris::Draw(sf::RenderWindow* window)
{
    for(int i=0;i<STAGE_HEIGHT;i++)
    {
        for(int j=0;j<STAGE_WIDTH;j++)
        {
            if(Field[i][j])
            {
                sTiles.setTextureRect(IntRect(Field[i][j]*GRIDSIZE,0,GRIDSIZE,GRIDSIZE));
                sTiles.setPosition(j*GRIDSIZE,i*GRIDSIZE);
                sTiles.move(mCornPoint.x,mCornPoint.y);
                window->draw(sTiles);
            }
        }
    }
    for(int i=0;i<4;i++)
    {
        sTiles.setPosition(currentSquare[i].x*GRIDSIZE,currentSquare[i].y*GRIDSIZE);
        sTiles.setTextureRect(sf::IntRect(colorNum*GRIDSIZE,0,GRIDSIZE,GRIDSIZE));
        sTiles.move(mCornPoint.x,mCornPoint.y);
        window->draw(sTiles);
    }
    //绘制Next区的方块
    for(int i=0;i<4;i++)
    {
        sTiles.setPosition(nextSquare[i].x*GRIDSIZE,nextSquare[i].y*GRIDSIZE);
        sTiles.setTextureRect(sf::IntRect(nextColorNum*GRIDSIZE,0,GRIDSIZE,GRIDSIZE));
        sTiles.move(nextSquareCornPoint.x,nextSquareCornPoint.y);
        window->draw(sTiles);
    }
    //绘制Hold区的方块
    if(holdShapeNum>-1)
    {
        for(int i=0;i<4;i++)
        {
            sTiles.setPosition(holdSquare[i].x*GRIDSIZE,holdSquare[i].y*GRIDSIZE);
            sTiles.setTextureRect(sf::IntRect(holdShapeNum*GRIDSIZE,0,GRIDSIZE,GRIDSIZE));
            sTiles.move(holdSquareCornPoint.x,holdSquareCornPoint.y);
            window->draw(sTiles);
        }
    }
}

int Tetris::Bag7()
{
    int num;
    srand(time(NULL));
    num=rand()%7;
    for(int i=0;i<b7Int;i++)
    {
        if(b7array[i]==num)
        {
            i=-1;
            num=rand()%7;
        }
    }
    b7array[b7Int]=num;
    b7Int++;
    if(b7Int==7)
    {
        b7Int=0;
        for(int i=0;i<7;i++)
        {
            b7array[i]=0;
        }
    }
    return num;
}

int Tetris::holdcolorNum=0,Tetris::holdShapeNum=0;
Vector2i Tetris::holdSquare[4]={{0,0},{0,0},{0,0},{0,0}};