#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>

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

bool gameOver;
const int width=STAGE_WIDTH;
const int height=STAGE_HEIGHT;
int x,y,fruitX,fruitY,score;
int tailX[MAXLENGTH],tailY[MAXLENGTH];
int nTail;
int headLocation;
int delay;

Font font;
Text text;
enum eDirection{ STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
RenderWindow window(VideoMode(width*GRIDSIZE+INFO_WIDTH,height*GRIDSIZE+GRIDSIZE),L"SFML Works");
// Texture tBackGround,tSnack,tFruit;
// Sprite spBackGround,spSnack,spFruit;
Texture tBackGround,tSnackHead,tSnackBody,tFruit;
Sprite spBackGround,spSnackHead,spSnackBody,spFruit;
void Initial()
{
    window.setFramerateLimit(60);

    if(!font.loadFromFile("../data/Fonts/simsunb.ttf"))
    {
        cout<<"字体没有找到"<<endl;
    }else{
        cout<<1<<endl;
    }
    text.setFont(font);
    if(!tBackGround.loadFromFile("../data/images/BK.png"))
    {
        cout<<"BK Load Error"<<endl;
    }
    if(!tSnackHead.loadFromFile("../data/images/sh01.png"))
    {
        cout<<"sh01 Load Error"<<endl;
    }
    if(!tSnackBody.loadFromFile("../data/images/sb0102.png"))
    {
        cout<<"sb0102 Load Error"<<endl;
    }
    if(!tFruit.loadFromFile("../data/images/sb0202.png"))
    {
        cout<<"sb0202 Load Error"<<endl;
    }

    spBackGround.setTexture(tBackGround);
    spSnackHead.setTexture(tSnackHead);
    spSnackBody.setTexture(tSnackBody);
    spFruit.setTexture(tFruit);

    spBackGround.setScale(SCALE,SCALE);
    spSnackHead.setScale(SCALE,SCALE);
    spSnackBody.setScale(SCALE,SCALE);
    spFruit.setScale(SCALE,SCALE);

    spBackGround.setOrigin(GRIDSIZE/SCALE/2,GRIDSIZE/SCALE/2);
    spSnackHead.setOrigin(GRIDSIZE/SCALE/2,GRIDSIZE/SCALE/2);
    spSnackBody.setOrigin(GRIDSIZE/SCALE/2,GRIDSIZE/SCALE/2);
    spFruit.setOrigin(GRIDSIZE/SCALE/2,GRIDSIZE/SCALE/2);

    
    headLocation=0;
    gameOver=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    fruitX=rand()%width;
    fruitY=rand()%height;
    score=0;
    nTail=1;
    delay=0;
    for(int i=0;i<MAXLENGTH;i++)
    {
        tailX[i]=0;
        tailY[i]=0;
    }  
    tailX[0] = x;
    tailY[0] = y;  
}

void Prompt_info(int _x, int _y)
{
    int initialX = 20, initialY = 0;
    int CharacterSize=24;
    text.setCharacterSize(CharacterSize);
    text.setFillColor(Color(255,255,255,255));
    text.setStyle(Text::Bold);
    text.setPosition(_x+initialX,_y+initialY);
    text.setString("■ 游戏说明:");window.draw(text);
    initialY+=CharacterSize;
    text.setPosition(_x+initialX,_y+initialY);
    text.setString("  A.蛇身自撞，游戏结束");window.draw(text);
    initialY+=CharacterSize;
    text.setPosition(_x+initialX,_y+initialY);
    text.setString("    B.蛇可穿墙");window.draw(text);
    initialY+=CharacterSize;
    initialY+=CharacterSize;
    text.setPosition(_x+initialX,_y+initialY);
    text.setString("■ 操作说明:");window.draw(text);
    initialY+=CharacterSize;
    text.setPosition(_x+initialX,_y+initialY);
    text.setString("   向左移动:←A");window.draw(text);
    initialY+=CharacterSize;
    text.setPosition(_x+initialX,_y+initialY);
    text.setString("   向右移动:→D");window.draw(text);
    initialY+=CharacterSize;
    text.setPosition(_x+initialX,_y+initialY);
    text.setString("   向下移动:↓S");window.draw(text);
    initialY+=CharacterSize;
    text.setPosition(_x+initialX,_y+initialY);
    text.setString("   向上移动:↑W");window.draw(text);
    initialY+=CharacterSize;
    text.setPosition(_x+initialX,_y+initialY);
    text.setString("   开始游戏：任意方向键");window.draw(text);
    initialY+=CharacterSize;
    text.setPosition(_x+initialX,_y+initialY);
    text.setString("   退出游戏:x键退出");window.draw(text);
    initialY+=CharacterSize;
    initialY+=CharacterSize;
    text.setPosition(_x+initialX,_y+initialY);
    text.setString("■ 作者:L——Y——K");window.draw(text);
}
void Input()
{
    Event event;
    while(window.pollEvent(event))
    {
        if(event.type==Event::Closed)
        {
            window.close();
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        if(dir!=RIGHT)
            dir=LEFT;
    }
    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        if(dir!=LEFT)
            dir=RIGHT;
    }
    if(Keyboard::isKeyPressed(Keyboard::Up))
    {
        if(dir!=DOWN)
            dir=UP;
    }
    if(Keyboard::isKeyPressed(Keyboard::Down))
    {
        if(dir!=UP)
            dir=DOWN;
    }
}
void Logic()
{
 switch (dir)
    {
    case LEFT:
        x--;
        headLocation=-90;
        break;
    case RIGHT:
        x++;
         headLocation=90;
        break;
    case UP:
        y--;
         headLocation=0;
        break;
    case DOWN:
        y++;
         headLocation=180;
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

    if(x>=width) x=0;else if(x<0) x=width-1;
    if(y>=height) y=0;else if(y<0) y=height-1;
    // //判断出界，游戏结束
    // if (x > width - 2 || x <= 0 || y > height - 1 || y < 0)
    // {
    //     gameOver = true;
    // }
    // //判断身体与头相撞，游戏结束
    // for (int i = 1; i < nTail; i++)
    // {
    //     if (tailX[i] == x && tailY[i] == y)
    //     {
    //         gameOver = true;
    //     }
    // }

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
void Draw()
{
    window.clear(Color(0,0,0,255));
    Prompt_info(width*GRIDSIZE+GRIDSIZE,GRIDSIZE);
    int detaX=GRIDSIZE/SCALE/2;
    int detaY=GRIDSIZE/SCALE/2;
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            spBackGround.setPosition(i*GRIDSIZE+detaX,j*GRIDSIZE+detaY);
            window.draw(spBackGround);
        }
    }
    spSnackHead.setPosition(tailX[0]*GRIDSIZE+detaX,tailY[0]*GRIDSIZE+detaY);
    spSnackHead.setRotation(headLocation);
    window.draw(spSnackHead);
    for(int i=1;i<nTail;i++)
    {
        spSnackBody.setPosition(tailX[i]*GRIDSIZE+detaX,tailY[i]*GRIDSIZE+detaY);
        window.draw(spSnackBody);
    }

    spFruit.setPosition(fruitX*GRIDSIZE+detaX,fruitY*GRIDSIZE+detaY);
    window.draw(spFruit);
    window.display();
}
int main()
{
    Initial();
    while(window.isOpen()&& gameOver==false)
    {
        Input();
        delay++;
        if(delay%10==0)
        {
            Logic();
        }
        
        Draw();
    }
    
    return 0;
}