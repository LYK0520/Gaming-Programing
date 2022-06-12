#include "RussianCubeGame.h"
#include <iostream>
#include "Tetris.h"
using namespace std;
using namespace sf;
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
Game::Game()
{
    Window_width = 1350;
    Window_height = 1000;

    imgBGNo = 1;
    imgSkinNo = 1;
    window.create(sf::VideoMode(Window_width, Window_height), "Russian Cube", Style::Close);
}
Game::~Game()
{
}
void Game::LoadMediaData()
{
    std::stringstream ss;
    ss << "data/images/bg" << imgSetNo << ".jpg";

    if (!tBackground.loadFromFile(ss.str()))
        std::cout << "Error: Cannot load background image!" << std::endl;

    ss.str(""); // 清空字符串
    ss << "data/images/tiles" << imgSetNo << ".jpg";
    if (!tTiles.loadFromFile(ss.str()))
        std::cout << "Error: Cannot load tiles image!" << std::endl;
    if (!tButtons.loadFromFile("data/images/button.png"))
        std::cout << "Error: Cannot load buttons image!" << std::endl;
    if (!tSwitcher.loadFromFile("data/images/bgSwitch.png"))
        std::cout << "Error: Cannot load switcher image!" << std::endl;
    if (!tFrame.loadFromFile("data/images/frame.png"))
        std::cout << "Error: Cannot load frame image!" << std::endl;
    if (!tCover.loadFromFile("data/images/cover.png"))
        std::cout << "Error: Cannot load cover image!" << std::endl;
    if (!tGameOver.loadFromFile("data/images/end.png"))
        std::cout << "Error: Cannot load end image!" << std::endl;
    if (!font.loadFromFile("./data/Fonts/Mi/MiSans-Medium.ttf"))
        std::cout << "字体没有找到" << std::endl;
    text.setFont(font); //加载指定字体

    sBackground.setTexture(tBackground);
    // sTiles.setTexture(tTiles);
    sFrame.setTexture(tFrame);
    sCover.setTexture(tCover);
    sGameOver.setTexture(tGameOver);

    sButtons.setTexture(tButtons);
    sSwitcher.setTexture(tSwitcher);
    sSwitcher.setOrigin(sSwitcher.getGlobalBounds().width / 2, sSwitcher.getGlobalBounds().height / 2);

    // if(!font.loadFromFile("data/fonts/simsun.ttc"))
    // {
    //     std::cout<<"Error: Cannot load font!"<<std::endl;
    //     //exit(0);
    // }
    // text.setFont(font);
}

void Game::gameInitial()
{
    window.setFramerateLimit(15); // 每秒设置目标帧数
    LoadMediaData();

    isGameBegin = false;
    isGameHold = false;
    gameOver = false;
    ButtonState_Start = Start_Dark;
    ButtonState_Hold = Hold_Dark;
    player1.role = rolePLAYER1;
    player2.role = rolePLAYER2;
    player1.Initial(&tTiles); // 将方块儿的素材传给 Tetris 对象，由 Trtris 对象控制方块儿
    player2.Initial(&tTiles); // 将方块儿的素材传给 Tetris 对象，由 Trtris 对象控制方块儿
}
// p288
void Game::gameInput()
{
    Event event;
    window.setKeyRepeatEnabled(false); // 按键按下只响应一次
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
            gameQuit = true;
        }
        if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::Escape)
        {
            window.close();
            gameQuit = true;
        }
        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
        {
            if (ButtonRectStart.contains(Mouse::getPosition(window)))
            {
                if (isGameBegin == false)
                {
                    isGameBegin = true;
                    player1.animationFlag = false;
                    player2.animationFlag = false;
                    ButtonState_Start = Close_Light;
                }
                else
                {
                    isGameBegin = false;
                    ButtonState_Start = Start_Light;
                }
            }
            if (ButtonRectHold.contains(Mouse::getPosition(window)))
            {
                if (isGameHold == false)
                {
                    isGameHold = true;
                    ButtonState_Hold = Continue_Light;
                }
                else
                {
                    isGameHold = false;
                    ButtonState_Hold = Hold_Light;
                }
            }
            if (ButtonRectLeft.contains(Mouse::getPosition(window)))
            {
                imgSetNo--;
                if (imgSetNo < 1)
                    imgSetNo = 4;
                LoadMediaData();
            }
            if (ButtonRectRight.contains(Mouse::getPosition(window)))
            {
                imgSetNo++;
                if (imgSetNo > 4)
                    imgSetNo = 1;
                LoadMediaData();
            }
        }
        if (event.type == Event::MouseMoved)
        {
            if (ButtonRectStart.contains(Mouse::getPosition(window)))
            {
                if (isGameBegin == false)
                    ButtonState_Start = Start_Light;
                else
                    ButtonState_Start = Close_Light;
            }
            else
            {
                if (isGameBegin == false)
                    ButtonState_Start = Start_Dark;
                else
                    ButtonState_Start = Close_Dark;
            }
            if (ButtonRectHold.contains(Mouse::getPosition(window)))
            {
                if (isGameHold == false)
                    ButtonState_Hold = Hold_Light;
                else
                    ButtonState_Hold = Continue_Light;
            }
            else
            {
                if (isGameHold == false)
                    ButtonState_Hold = Hold_Dark;
                else
                    ButtonState_Hold = Continue_Dark;
            }
        }
        player1.Input(event);
        player2.Input(event);
    }
}
void Game::gameLogic()
{
    if (isGameHold == true)
        return;
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    player1.timer += time;
    player2.timer += time;

    player1.Logic();
    player2.Logic();
}

void Game::gameDraw()
{
    window.clear();

    sBackground.setPosition(0, 0);
    window.draw(sBackground);
    sFrame.setPosition(0, -20);
    window.draw(sFrame);
    player1.Draw(&window);
    player2.Draw(&window);

    sCover.setPosition(P1_STAGE_CORNER_X, P1_STAGE_CORNER_Y);
    window.draw(sCover);
    sCover.setPosition(P2_STAGE_CORNER_X, P2_STAGE_CORNER_Y);
    window.draw(sCover);

    DrawButton();
    DrawResults();
    TextOut();
    window.display();
}
void Game::DrawButton()
{
    int ButtonWidth, ButtonHeight;
    ButtonWidth = 110;
    ButtonHeight = sButtons.getLocalBounds().height;

    // ButtonRectStart
    sButtons.setPosition(B_START_CORNER_X, B_START_CORNER_Y);
    sButtons.setTextureRect(IntRect(ButtonState_Start * ButtonWidth, 0, ButtonWidth, ButtonHeight));
    ButtonRectStart.left = B_START_CORNER_X;
    ButtonRectStart.top = B_START_CORNER_Y;
    ButtonRectStart.width = ButtonWidth;
    ButtonRectStart.height = ButtonHeight;
    window.draw(sButtons);

    // ButtonRectHold
    sButtons.setPosition(B_HOLD_CORNER_X, B_HOLD_CORNER_Y);
    sButtons.setTextureRect(IntRect(ButtonState_Hold * ButtonWidth, 0, ButtonWidth, ButtonHeight));
    ButtonRectHold.left = B_HOLD_CORNER_X;
    ButtonRectHold.top = B_HOLD_CORNER_Y;
    ButtonRectHold.width = ButtonWidth;
    ButtonRectHold.height = ButtonHeight;
    window.draw(sButtons);

    // 背景素材切换
    ButtonWidth = sSwitcher.getLocalBounds().width;
    ButtonHeight = sSwitcher.getLocalBounds().height;

    // ButtonRectLeft
    sSwitcher.setPosition(B_LEFT_CORNER_X, B_LEFT_CORNER_Y);
    ButtonRectLeft.left = B_LEFT_CORNER_X - ButtonWidth / 2;
    ButtonRectLeft.top = B_LEFT_CORNER_Y - ButtonHeight / 2;
    ButtonRectLeft.width = ButtonWidth;
    ButtonRectLeft.height = ButtonHeight;
    window.draw(sSwitcher);

    // ButtonRectRight
    sSwitcher.setPosition(B_RIGHT_CORNER_X, B_RIGHT_CORNER_Y);
    ButtonRectRight.left = B_RIGHT_CORNER_X - ButtonWidth / 2;
    ButtonRectRight.top = B_RIGHT_CORNER_Y - ButtonHeight / 2;
    ButtonRectRight.width = ButtonWidth;
    ButtonRectRight.height = ButtonHeight;
    sSwitcher.rotate(180);
    window.draw(sSwitcher);
    sSwitcher.rotate(180); // 还原
}
void Game::DrawResults()
{
    int ButtonWidth, ButtonHeight;
    ButtonWidth = 250;
    ButtonHeight = sGameOver.getLocalBounds().height;

    if (player1.gameOver || player2.gameOver)
    {
        sGameOver.setTextureRect(IntRect(player1.gameOver * ButtonWidth, 0, ButtonWidth, ButtonHeight));
        sGameOver.setPosition(P1_STAGE_CORNER_X + GRIDSIZE * 1.5, 400);
        window.draw(sGameOver);

        sGameOver.setTextureRect(IntRect(player2.gameOver * ButtonWidth, 0, ButtonWidth, ButtonHeight));
        sGameOver.setPosition(P2_STAGE_CORNER_X + GRIDSIZE * 1.5, 400);
        window.draw(sGameOver);
    }
}
void Game::TextOut()
{
    int initialX, initialY;
    int CharacterSize = 36;
    text.setCharacterSize(CharacterSize);
    text.setFillColor(Color(255, 0, 0, 255));
    text.setStyle(Text::Bold);
    text.setOutlineColor(Color(255, 255, 255, 255));
    text.setOutlineThickness(5);
    text.setPosition(P1_SCORE_CORNER_X, P1_SCORE_CORNER_Y);
    std::stringstream ss;

    ss << "score: " << player1.score;
    text.setString(ss.str());
    window.draw(text);

    text.setPosition(P2_SCORE_CORNER_X, P2_SCORE_CORNER_Y);
    ss.str("");
    ss << "score: " << player2.score;
    text.setString(ss.str());
    window.draw(text);

    text.setOutlineThickness(0);
    CharacterSize = 24;
    text.setCharacterSize(CharacterSize);
    text.setFillColor(Color(255, 255, 255, 255));
    text.setStyle(Text::Bold);
    initialY = INFO_CORNER_Y;
    text.setPosition(INFO_CORNER_X, initialY);
    text.setString(L"玩家1：");
    window.draw(text);
    CharacterSize = 21;
    text.setCharacterSize(CharacterSize);
    initialY += CharacterSize * 1.2;
    text.setPosition(INFO_CORNER_X, initialY);
    text.setString(L"方向： WASD");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(INFO_CORNER_X, initialY);
    text.setString(L"速降： SPACE");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(INFO_CORNER_X, initialY);
    text.setString(L"交换： 左 CTRL");
    window.draw(text);
    CharacterSize = 24;
    text.setCharacterSize(CharacterSize);
    initialY += CharacterSize * 2;
    text.setPosition(INFO_CORNER_X, initialY);
    text.setString(L"玩家2：");
    window.draw(text);
    CharacterSize = 21;
    text.setCharacterSize(CharacterSize);
    initialY += CharacterSize * 1.2;
    text.setPosition(INFO_CORNER_X, initialY);
    text.setString(L"方向： ↑↓←→");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(INFO_CORNER_X, initialY);
    text.setString(L"速降： ENTER");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(INFO_CORNER_X, initialY);
    text.setString(L"交换： 右 CTRL");
    window.draw(text);
    initialY += CharacterSize * 2;
    text.setPosition(INFO_CORNER_X, initialY);
    text.setString(L"自带底部缓冲功能");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(INFO_CORNER_X, initialY);
    text.setString(L"退出：ESC");
    window.draw(text);
}
void Game::gameRun()
{
    do
    {
        gameInitial();

        while (window.isOpen() && gameOver == false)
        {
            gameInput();
            if (isGameBegin == true)
            {
                gameLogic();
            }
            // }else{
            //     gameInitial();
            // }
            gameDraw();
            gameOver = (player1.gameOver || player2.gameOver);
        }
        while (1)
        {
            if (KEY_DOWN(MOUSE_MOVED) || KEY_DOWN(MOUSE_EVENT) || KEY_DOWN(MOUSE_WHEELED))
            {
                break;
            }
        }
    } while (!gameQuit);
}