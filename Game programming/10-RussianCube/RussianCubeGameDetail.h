#include"RussianCubeGame.h"
using namespace sf;
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
    ss<<"data/images/bg"<<imgBGNo<<".jpg";

    if(!tBackground.loadFromFile(ss.str()))
    {
        std::cout<<"Error: Cannot load background image!"<<std::endl;
       // exit(0);
    }
    ss.str("");//清空字符串
    ss<<"data/images/tiles"<<imgSkinNo<<".jpg";
    if(!tTiles.loadFromFile(ss.str()))
    {
        std::cout<<"Error: Cannot load tiles image!"<<std::endl;
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
}

void Game::gameInitial()
{
    window.setFramerateLimit(15);
    LoadMediaData();
    player1.role=rolePLAYER1;
    player2.role=rolePLAYER2;
    player1.Initial(&tTiles);
    player2.Initial(&tTiles);
}

void Game::gameInput()
{
    Event event;
    window.setKeyRepeatEnabled(false);
    while(window.pollEvent(event))
    {
        if(event.type==Event::Closed)
        {
            window.close();
            gameQuit=true;
        }
        player1.Input(event);
        player2.Input(event);
    }
}
void Game::gameLogic()
{
    float time=clock.getElapsedTime().asSeconds();
    clock.restart();
    player1.timer+=time;
    player2.timer+=time;

    player1.Logic();
    player2.Logic();
}

void Game::gameDraw()
{
    window.clear();
    sBackground.setPosition(0,0);
    window.draw(sBackground);
    window.draw(sFrame);
    player1.Draw(&window);
    player2.Draw(&window);

    window.display();
}
void Game::gameRun()
{
    do{
        gameInitial();

        while(window.isOpen()&& gameOver==false)
        {
            gameInput();
            gameLogic();
            gameDraw();
        }
    }while(!gameQuit);
}