#include"RussianCubeGame.h"
#include<iostream>
#include "10-1-3Tetris.h"
using namespace std;
using namespace sf;
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
Game::Game()
{
    Window_width=1350;
    Window_height=1000;

    imgBGNo=1;
    imgSkinNo=1;
    window.create(VideoMode(Window_width,Window_height),"Russian Cube");
}
Game::~Game()
{

}
void Game::LoadMediaData()
{
    std::stringstream ss;
    ss<<"data/images/bg"<<imgSetNo<<".jpg";

    if(!tBackground.loadFromFile(ss.str()))
    {
        std::cout<<"Error: Cannot load background image!"<<std::endl;
       // exit(0);
    }
    ss.str("");//清空字符串
    ss<<"data/images/tiles"<<imgSetNo<<".jpg";
    if(!tTiles.loadFromFile(ss.str()))
    {
        std::cout<<"Error: Cannot load tiles image!"<<std::endl;
        //exit(0);
    }
    if(!tButtons.loadFromFile("data/images/button.png"))
    {
        std::cout<<"Error: Cannot load buttons image!"<<std::endl;
        //exit(0);
    }
    if(!tSwitcher.loadFromFile("data/images/bgSwitch.png"))
    {
        std::cout<<"Error: Cannot load switcher image!"<<std::endl;
        //exit(0);
    }
    if(!tFrame.loadFromFile("data/images/frame.png"))
    {
        std::cout<<"Error: Cannot load frame image!"<<std::endl;
        ///exit(0);
    }
    if(!tCover.loadFromFile("data/images/cover.png"))
    {
        std::cout<<"Error: Cannot load cover image!"<<std::endl;
        //exit(0);
    }
    if(!tGameOver.loadFromFile("data/images/end.png"))
    {
        std::cout<<"Error: Cannot load end image!"<<std::endl;
        //exit(0);
    }
    sBackground.setTexture(tBackground);
    //sTiles.setTexture(tTiles);
    sFrame.setTexture(tFrame);
    sCover.setTexture(tCover);
    sGameOver.setTexture(tGameOver);
    sButtons.setTexture(tButtons);
    sSwitcher.setTexture(tSwitcher);
    sSwitcher.setOrigin(sSwitcher.getGlobalBounds().width/2,sSwitcher.getGlobalBounds().height/2);

    // if(!font.loadFromFile("data/fonts/simsun.ttc"))
    // {
    //     std::cout<<"Error: Cannot load font!"<<std::endl;
    //     //exit(0);
    // }
    // text.setFont(font);
}

void Game::gameInitial()
{
    window.setFramerateLimit(15);
    LoadMediaData();
    isGameBegin=false;
    isGameHold=false;
    gameOver=false;
    ButtonState_Start=Start_Dark;
    ButtonState_Hold=Hold_Dark;
    player1.role=rolePLAYER1;
    player2.role=rolePLAYER2;
    player1.Initial(&tTiles);
    player2.Initial(&tTiles);
}
//p288
void Game::gameInput()
{
    Event event;
    window.setKeyRepeatEnabled(false);
    //cout<<"01"<<endl;
    while(window.pollEvent(event))
    {
        if(event.type==Event::Closed)
        {
            window.close();
            gameQuit=true;
        }
        if(event.type==Event::EventType::KeyReleased&& event.key.code==Keyboard::Escape)
        {
            window.close();
            gameQuit=true;
        }
        //cout<<"02"<<endl;
        if(event.type==Event::MouseButtonReleased&& event.mouseButton.button==Mouse::Left)
        {
            cout<<3<<endl;
           if(ButtonRectStart.contains(Mouse::getPosition(window)))
           {
               if(isGameBegin==false)
               {
                   isGameBegin=true;
                   player1.animationFlag=false;
                   player2.animationFlag=false;
                   ButtonState_Start=Close_Light;
                   cout<<2<<endl;
               }
               else{
                   isGameBegin=false;
                   ButtonState_Start=Start_Light;
               }
           }
              if(ButtonRectHold.contains(Mouse::getPosition(window)))
              {
                if(isGameHold==false)
                {
                     isGameHold=true;
                     ButtonState_Hold=Continue_Light;
                }
                else{
                     isGameHold=false;
                     ButtonState_Hold=Hold_Light;
                }
              }
              if(ButtonRectLeft.contains(Mouse::getPosition(window)))
              {
                  imgSetNo--;
                  if(imgSetNo<1)
                  {
                      imgSetNo=4;
                  }
                  LoadMediaData();
              }
              if(ButtonRectRight.contains(Mouse::getPosition(window)))
              {
                  imgSetNo++;
                  if(imgSetNo>4)
                  {
                      imgSetNo=1;
                  }
                  LoadMediaData();
              }
        }
        if(event.type==Event::MouseMoved)
        {
            if(ButtonRectStart.contains(Mouse::getPosition(window)))
            {
                if(isGameBegin==false)
                {
                    ButtonState_Start=Start_Light;
                }else{
                    ButtonState_Start=Close_Light;
                }
            }
            else{
                if(isGameBegin==false)
                {
                    ButtonState_Start=Start_Dark;
                }else{
                    ButtonState_Start=Close_Dark;
                }
            }
            if(ButtonRectHold.contains(Mouse::getPosition(window)))
            {
                if(isGameHold==false)
                {
                    ButtonState_Hold=Hold_Light;
                }else{
                    ButtonState_Hold=Continue_Light;
                }
            }
            else{
                if(isGameHold==false)
                {
                    ButtonState_Hold=Hold_Dark;
                }else{
                    ButtonState_Hold=Continue_Dark;
                }
            }
            
        }
        player1.Input(event);
        player2.Input(event);
    }
}
void Game::gameLogic()
{
    if(isGameHold==true)
    {
        return;
    }
    float time=clock.getElapsedTime().asSeconds();
    clock.restart();
    player1.timer+=time;
    player2.timer+=time;
    cout<<player2.gameOver<<endl;
    cout<<"101"<<endl;
    player1.Logic();
    cout<<"102"<<endl;
    player2.Logic();
    cout<<gameOver<<endl;
    cout<<player1.gameOver<<" "<<player2.gameOver<<endl;
    gameOver=(player1.gameOver||player2.gameOver);
}

void Game::gameDraw()
{
    window.clear();
    sBackground.setPosition(0,0);
    window.draw(sBackground);
    window.draw(sFrame);
    player1.Draw(&window);
    player2.Draw(&window);

    //window.display();

    sCover.setPosition(P1_STAGE_CORNER_X,P1_STAGE_CORNER_Y);
    window.draw(sCover);
    sCover.setPosition(P2_STAGE_CORNER_X,P2_STAGE_CORNER_Y);
    window.draw(sCover);

    DrawButton();
    //TextOut1();
    DrawResults();
    window.display();
}
void Game::gameRun()
{
    do{
        gameInitial();

        while(window.isOpen()&& gameOver==false)
        {
            gameInput();
            if(isGameBegin==true)
            {
                cout<<02<<endl;
                gameLogic();
            }
            // }else{
            //     gameInitial();
            // }
            //cout<<1<<endl;
            gameDraw();
        }
         while (1)
        {
            if (KEY_DOWN(MOUSE_MOVED) || KEY_DOWN(MOUSE_EVENT) || KEY_DOWN(MOUSE_WHEELED))
            {
                break;
            }
        }
    }while(!gameQuit);
}
void Game::DrawButton()
{
    int ButtonWidth,ButtonHeight;
    ButtonWidth=110;
    ButtonHeight=sButtons.getLocalBounds().height;
    sButtons.setPosition(B_START_CORNER_X,B_START_CORNER_Y);
    sButtons.setTextureRect(IntRect(ButtonState_Start*ButtonWidth,0,ButtonWidth,ButtonHeight));
    ButtonRectStart.left=B_START_CORNER_X;
    ButtonRectStart.top=B_START_CORNER_Y;
    ButtonRectStart.width=ButtonWidth;
    ButtonRectStart.height=ButtonHeight;
    window.draw(sButtons);

    sButtons.setPosition(B_HOLD_CORNER_X,B_HOLD_CORNER_Y);
    sButtons.setTextureRect(IntRect(ButtonState_Hold*ButtonWidth,0,ButtonWidth,ButtonHeight));
    ButtonRectHold.left=B_HOLD_CORNER_X;
    ButtonRectHold.top=B_HOLD_CORNER_Y;
    ButtonRectHold.width=ButtonWidth;
    ButtonRectHold.height=ButtonHeight;
    window.draw(sButtons);

    ButtonWidth=sSwitcher.getLocalBounds().width;
    ButtonHeight=sSwitcher.getLocalBounds().height;


    sSwitcher.setPosition(B_LEFT_CORNER_X,B_LEFT_CORNER_Y);
    ButtonRectLeft.left=B_LEFT_CORNER_X-ButtonWidth/2;
    ButtonRectLeft.top=B_LEFT_CORNER_Y-ButtonHeight/2;
    ButtonRectLeft.width=ButtonWidth;
    ButtonRectLeft.height=ButtonHeight;
    window.draw(sSwitcher);

    sSwitcher.setPosition(B_RIGHT_CORNER_X,B_RIGHT_CORNER_Y);
    ButtonRectRight.left=B_RIGHT_CORNER_X-ButtonWidth/2;
    ButtonRectRight.top=B_RIGHT_CORNER_Y-ButtonHeight/2;
    ButtonRectRight.width=ButtonWidth;
    ButtonRectRight.height=ButtonHeight;
    sSwitcher.rotate(180);
    window.draw(sSwitcher);
    sSwitcher.rotate(180);
}
void Game::DrawResults()
{
    int ButtonWidth,ButtonHeight;
    ButtonWidth=250;
    ButtonHeight=sButtons.getLocalBounds().height;

    if(player1.gameOver||player2.gameOver)
    {
        sGameOver.setTextureRect(IntRect(player1.gameOver*ButtonWidth,0,ButtonWidth,ButtonHeight));
        sGameOver.setPosition(P1_STAGE_CORNER_X+GRIDSIZE*1.5,0);
        window.draw(sGameOver);

        sGameOver.setTextureRect(IntRect(player2.gameOver*ButtonWidth,0,ButtonWidth,ButtonHeight));
        sGameOver.setPosition(P2_STAGE_CORNER_X+GRIDSIZE*1.5,0);
        window.draw(sGameOver);
    }
}