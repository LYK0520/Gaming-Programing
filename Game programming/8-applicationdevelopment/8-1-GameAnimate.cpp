#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 25
#define STAGE_WIDTH 20
#define STAGE_HEIGHT 20
#define GRIDSIZE 25
#define MAXLENGTH 100
#define SCALE 0.5
#define INFO_WIDTH 400
////////////////////////////////
// 8-1
#define STEP 0.1
int GameMode;
float stepX, stepY;
//////////////////////////////////////
bool gameOver;
const int width = STAGE_WIDTH;
const int height = STAGE_HEIGHT;
int x, y, fruitX, fruitY, score;
int tailX[MAXLENGTH], tailY[MAXLENGTH];
int nTail;
int headRotation;
int delay;
bool gameQuit;
Font font;
Text text;

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir, dir_ing;
bool updateFlag;
RenderWindow window(VideoMode(width *GRIDSIZE + INFO_WIDTH, height *GRIDSIZE + GRIDSIZE), L"SFML Works");
// Texture tBackGround,tSnack,tFruit;
// Sprite spBackGround,spSnack,spFruit;
Texture tBackGround, tSnackHead, tSnackBody, tFruit;
Sprite spBackGround, spSnackHead, spSnackBody, spFruit;
void Initial()
{
    window.setFramerateLimit(60);

    if (!font.loadFromFile("../data/Fonts/simsun.ttc"))
    {
        cout << "字体没有找到" << endl;
    }
    else
    {
        cout << 1 << endl;
    }
    text.setFont(font);
    if (!tBackGround.loadFromFile("../data/images/BK.png"))
    {
        cout << "BK Load Error" << endl;
    }
    if (!tSnackHead.loadFromFile("../data/images/sh01.png"))
    {
        cout << "sh01 Load Error" << endl;
    }
    if (!tSnackBody.loadFromFile("../data/images/sb0102.png"))
    {
        cout << "sb0102 Load Error" << endl;
    }
    if (!tFruit.loadFromFile("../data/images/sb0202.png"))
    {
        cout << "sb0202 Load Error" << endl;
    }

    spBackGround.setTexture(tBackGround);
    spSnackHead.setTexture(tSnackHead);
    spSnackBody.setTexture(tSnackBody);
    spFruit.setTexture(tFruit);

    spBackGround.setScale(SCALE, SCALE);
    spSnackHead.setScale(SCALE, SCALE);
    spSnackBody.setScale(SCALE, SCALE);
    spFruit.setScale(SCALE, SCALE);

    spBackGround.setOrigin(GRIDSIZE / SCALE / 2, GRIDSIZE / SCALE / 2);
    spSnackHead.setOrigin(GRIDSIZE / SCALE / 2, GRIDSIZE / SCALE / 2);
    spSnackBody.setOrigin(GRIDSIZE / SCALE / 2, GRIDSIZE / SCALE / 2);
    spFruit.setOrigin(GRIDSIZE / SCALE / 2, GRIDSIZE / SCALE / 2);

    headRotation = 0;
    gameOver = false;
    dir = STOP;
    dir_ing = STOP;
    updateFlag = false;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 1;
    delay = 0;
    for (int i = 0; i < MAXLENGTH; i++)
    {
        tailX[i] = 0;
        tailY[i] = 0;
    }
    tailX[0] = x;
    tailY[0] = y;
    //////////////////////////////////
    // 8-1
    GameMode = 1;
    stepX = 0.0;
    stepY = 0.0;
}
void gameOver_info(int _x, int _y);
void Prompt_info(int _x, int _y)
{
    // gameOver_info(0, 0);
    int initialX = 20, initialY = 0;
    int CharacterSize = 24;
    text.setCharacterSize(CharacterSize);
    text.setFillColor(Color(255, 255, 255, 255));
    text.setStyle(Text::Bold);
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"■ 游戏说明:");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"  A.蛇身自撞，游戏结束");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"  B.蛇可穿墙");
    window.draw(text);
    initialY += CharacterSize;
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"■ 操作说明:");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"   向左移动:←A");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"   向右移动:→D");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"   向下移动:↓S");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"   向上移动:↑W");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"   开始游戏：任意方向键");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"   退出游戏:x键退出");
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"   ■动画模式切换：空格键");
    window.draw(text);
    initialY += CharacterSize * 1.5;
    text.setPosition(_x + initialX, _y + initialY);
    if (GameMode == 1)
    {
        text.setFillColor(Color(0, 0, 255, 255));
        text.setString(L"        步进移动");
    }
    else
    {
        text.setFillColor(Color(255, 0, 0, 255));
        text.setString(L"        连续移动");
    }
    window.draw(text);
    initialY += CharacterSize * 1.5;
    text.setFillColor(Color(255, 255, 255, 255));
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"■ 当前得分：");
    window.draw(text);
    text.setFillColor(Color(255, 0, 0, 255));
    text.setPosition(_x + initialX + CharacterSize * 7, _y + initialY);
    CharacterSize = 48;
    text.setCharacterSize(CharacterSize);
    stringstream ss;
    ss << score;
    text.setString(ss.str());
    window.draw(text);
    text.setFillColor(Color(255, 255, 255, 255));
    CharacterSize = 24;
    text.setCharacterSize(CharacterSize);
    initialY += CharacterSize;
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"■ 作者:L——Y——K");
    window.draw(text);
}
void Input()
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
        }
        if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::Space)
        {
            if (GameMode == 1)
            {
                GameMode = 2;
            }
            else
            {
                GameMode = 1;
            }
        }
    }
    // int unicode = event.text.unicode;
    // if (unicode < 128)
    //     cout << (char)unicode << endl;
    // switch (unicode)
    // {

    // // case 37:
    // case 'a':
    // case 'A':
    //     if (dir != RIGHT)
    //         dir = LEFT;
    //     break;
    // // case 39:
    // case 'd':
    // case 'D':

    //     if (dir != LEFT)
    //         dir = RIGHT;
    //     break;
    //     // case 38:
    // case 'w':
    // case 'W':
    //     if (dir != DOWN)
    //         dir = UP;
    //     break;
    // // case 40:
    // case 's':
    // case 'S':

    //     if (dir != UP)
    //         dir = DOWN;
    //     break;

    // case 72:
    //     if (dir != DOWN)
    //     {
    //         dir = UP;
    //     }
    //     break;
    // case 80:
    //     if (dir != UP)
    //     {
    //         dir = DOWN;
    //     }
    //     break;
    // case 75:
    //     if (dir != RIGHT)
    //     {
    //         dir = LEFT;
    //     }
    //     break;
    // case 77:
    //     if (dir != LEFT)
    //     {
    //         dir = RIGHT;
    //     }
    //     break;
    // default:
    //     break;
    // }

    // if (Event::EventType::KeyPressed)
    // {
    //     switch (event.key.code)
    //     {
    //     case Keyboard::Left:
    //     case Keyboard::A:
    //         if (dir != RIGHT)
    //             dir = LEFT;
    //         break;
    //     case Keyboard::Right:
    //     case Keyboard::D:
    //         if (dir != LEFT)
    //             dir = RIGHT;
    //         break;
    //     case Keyboard::Up:
    //     case Keyboard::W:
    //         if (dir != DOWN)
    //             dir = UP;
    //         break;
    //     case Keyboard::Down:
    //     case Keyboard::S:
    //         if (dir != UP)
    //             dir = DOWN;
    //         break;

    //     default:
    //         break;
    //     }
    // }

    if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
    {
        if (dir != RIGHT)
            dir = LEFT;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
    {
        if (dir != LEFT)
            dir = RIGHT;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
    {
        if (dir != DOWN)
            dir = UP;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
    {
        if (dir != UP)
            dir = DOWN;
    }
}
void LogicStep()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    updateFlag = false;
    dir_ing = dir;
    switch (dir_ing)
    {
    case LEFT:
        stepX -= STEP;
        if (stepX < -0.9999 || stepX >= 0.9999)
        {
            x--;
            stepX = 0;
            stepY = 0;
            headRotation = -90;
            updateFlag = true;
        }
        break;
    case RIGHT:
        stepX += STEP;
        if (stepX < -0.9999 || stepX >= 0.9999)
        {
            x++;
            stepX = 0;
            stepY = 0;
            headRotation = 90;
            updateFlag = true;
        }
        break;
    case UP:
        stepY -= STEP;
        if (stepY < -0.9999 || stepY >= 0.9999)
        {
            y--;
            stepX = 0;
            stepY = 0;
            headRotation = 0;
            updateFlag = true;
        }
        break;
    case DOWN:
        stepY += STEP;
        if (stepY < -0.9999 || stepY >= 0.9999)
        {
            y++;
            stepX = 0;
            stepY = 0;
            headRotation = 180;
            updateFlag = true;
        }
        break;
    }
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
    tailX[0] = x;
    tailY[0] = y;
    if (updateFlag == true)
    {
        if (x == fruitX && y == fruitY)
        {
            score += 10;
            fruitX = rand() % width;
            fruitY = rand() % height;
            nTail++;
        }
        for (int i = 1; i < nTail; i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        for (int i = 1; i < nTail; i++)
        {
            if (tailX[i] == x && tailY[i] == y)
            {
                gameOver = true;
            }
        }
    }
}
void Logic()
{
    switch (dir)
    {
    case LEFT:
        x--;
        headRotation = -90;
        break;
    case RIGHT:
        x++;
        headRotation = 90;
        break;
    case UP:
        y--;
        headRotation = 0;
        break;
    case DOWN:
        y++;
        headRotation = 180;
        break;
    default:
        break;
    }
    if (x == fruitX && y == fruitY)
    {
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
        score += 10;
    }

    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
    // //判断出界，游戏结束
    // if (x > width - 2 || x <= 0 || y > height - 1 || y < 0)
    // {
    //     gameOver = true;
    // }
    //判断身体与头相撞，游戏结束
    for (int i = 1; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
}
void gameOver_info(int _x, int _y)
{
    // Prompt_info(width * GRIDSIZE + GRIDSIZE, GRIDSIZE);
    int initialX = 20, initialY = 0;
    int CharacterSize = 48;
    text.setCharacterSize(CharacterSize);
    text.setFillColor(Color(255, 0, 0, 255));
    text.setStyle(Text::Bold);
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L"  游戏结束！！");
    cout << 3 << endl;
    window.draw(text);
    initialY += CharacterSize;
    text.setPosition(_x + initialX, _y + initialY);
    text.setString(L" Y重新开始/N退出");
    window.draw(text);
}
void DrawStep()
{
    window.clear(Color(0, 0, 0, 255));
    Prompt_info(width * GRIDSIZE + GRIDSIZE, GRIDSIZE);

    int detaX = GRIDSIZE / SCALE / 2;
    int detaY = GRIDSIZE / SCALE / 2;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            spBackGround.setPosition(i * GRIDSIZE + detaX, j * GRIDSIZE + detaY);
            window.draw(spBackGround);
        }
    }
    float stepLength;
    stepLength = stepX + stepY;
    if (stepLength < 0)
    {
        stepLength = -stepLength;
    }

    spSnackHead.setPosition((tailX[0] + stepX) * GRIDSIZE + detaX, (tailY[0] + stepY) * GRIDSIZE + detaY);
    spSnackHead.setRotation(headRotation);
    window.draw(spSnackHead);
    // for (int i = 1; i < nTail; i++)
    // {
    //     if (tailY[i] == tailY[i - 1] && tailX[i] != tailX[i - 1])
    //     {

    //         spSnackBody.setPosition((tailX[i] + (tailX[i - 1] - tailX[i]) * stepLength) * GRIDSIZE + detaX, tailY[i] * GRIDSIZE + detaY);
    //     }
    //     if (tailY[i] != tailY[i - 1] && tailX[i] == tailX[i - 1])
    //     {
    //         spSnackBody.setPosition(tailX[i] * GRIDSIZE + detaX, (tailY[i] + (tailY[i - 1] - tailY[i]) * stepLength) * GRIDSIZE + detaY);
    //     }
    //     if (tailX[i] != tailX[i - 1] && tailY[i] != tailY[i - 1])
    //     {
    //         spSnackBody.setPosition((tailX[i] + (tailX[i - 1] - tailX[i]) * stepLength) * GRIDSIZE + detaX, (tailY[i] + (tailY[i - 1] - tailY[i]) * stepLength) * GRIDSIZE + detaY);
    //     }
    //     window.draw(spSnackBody);
    // }
    for (int i = 1; i < nTail; i++)
    {
        if (tailY[i] == tailY[i - 1] && tailX[i] != tailX[i - 1] && abs(tailX[i] - tailX[i - 1]) <= 2)
        {

            spSnackBody.setPosition((tailX[i] + (tailX[i - 1] - tailX[i]) * stepLength) * GRIDSIZE + detaX, tailY[i] * GRIDSIZE + detaY);
        }
        if (tailY[i] != tailY[i - 1] && tailX[i] == tailX[i - 1] && abs(tailY[i] - tailY[i - 1]) <= 2)
        {
            spSnackBody.setPosition(tailX[i] * GRIDSIZE + detaX, (tailY[i] + (tailY[i - 1] - tailY[i]) * stepLength) * GRIDSIZE + detaY);
        }
        if (tailX[i] != tailX[i - 1] && tailY[i] != tailY[i - 1] && abs(tailX[i] - tailX[i - 1]) <= 2 && abs(tailY[i] - tailY[i - 1]) <= 2)
        {
            spSnackBody.setPosition((tailX[i] + (tailX[i - 1] - tailX[i]) * stepLength) * GRIDSIZE + detaX, (tailY[i] + (tailY[i - 1] - tailY[i]) * stepLength) * GRIDSIZE + detaY);
        }
        window.draw(spSnackBody);
    }
    spFruit.setPosition(fruitX * GRIDSIZE + detaX, fruitY * GRIDSIZE + detaY);
    window.draw(spFruit);
    // gameOver_info(width/8*GRIDSIZE, height/4*GRIDSIZE);

    if (gameOver)
    {
        gameOver_info(width / 8 * GRIDSIZE, height / 4 * GRIDSIZE);
    }
    window.display();
}
void Draw()
{
    window.clear(Color(0, 0, 0, 255));
    Prompt_info(width * GRIDSIZE + GRIDSIZE, GRIDSIZE);
    int detaX = GRIDSIZE / SCALE / 2;
    int detaY = GRIDSIZE / SCALE / 2;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            spBackGround.setPosition(i * GRIDSIZE + detaX, j * GRIDSIZE + detaY);
            window.draw(spBackGround);
        }
    }
    spSnackHead.setPosition(tailX[0] * GRIDSIZE + detaX, tailY[0] * GRIDSIZE + detaY);
    spSnackHead.setRotation(headRotation);
    window.draw(spSnackHead);
    for (int i = 1; i < nTail; i++)
    {
        spSnackBody.setPosition(tailX[i] * GRIDSIZE + detaX, tailY[i] * GRIDSIZE + detaY);
        window.draw(spSnackBody);
    }

    spFruit.setPosition(fruitX * GRIDSIZE + detaX, fruitY * GRIDSIZE + detaY);
    window.draw(spFruit);

    if (gameOver)
    {
        gameOver_info(width / 8 * GRIDSIZE, height / 4 * GRIDSIZE);
    }
    window.display();
}

int main()
{
    do
    {
        Initial();
        while (window.isOpen() && gameOver == false)
        {
            Input();
            switch (GameMode)
            {
            case 1:
                delay++;
                if (delay % 10 == 0)
                {
                    Logic();
                }
                Draw();
                break;
            case 2:
                LogicStep();
                DrawStep();
                break;
            }
        }
        while (gameOver)
        {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                {
                    window.close();
                    gameOver = false;
                    gameQuit = true;
                }
                if (e.type == Event::EventType::KeyReleased && e.key.code == Keyboard::Y)
                {
                    gameOver = false;
                }
                if (e.type == Event::EventType::KeyReleased && e.key.code == Keyboard::N)
                {
                    gameOver = false;
                    gameQuit = true;
                }
            }
        }
    } while (!gameQuit);

    return 0;
}