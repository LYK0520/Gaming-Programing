#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;


#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 25
#define STAGE_WIDTH 20
#define STAGE_HEIGHT 20
#define GRIDSIZE 25
#define MAXLENGTH 100

bool gameOver;
const int width=STAGE_WIDTH;
const int height=STAGE_HEIGHT;
int x,y,fruitX,fruitY,score;
int tailX[MAXLENGTH],tailY[MAXLENGTH];
int nTail;
enum eDirection{ STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
RenderWindow window(VideoMode(width*GRIDSIZE,height*GRIDSIZE),"SFML Works");
Texture tBackGround,tSnack,tFruit;
Sprite spBackGround,spSnack,spFruit;
void Initial()
{
    window.setFramerateLimit(10);
    tBackGround.loadFromFile("../input/Color1.png");
    tSnack.loadFromFile("../input/Color2.png");
    tFruit.loadFromFile("../input/Color3.png");

    spBackGround.setTexture(tBackGround);
    spSnack.setTexture(tSnack);
    spFruit.setTexture(tFruit);

    gameOver=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    fruitX=rand()%width;
    fruitY=rand()%height;
    score=0;
    nTail=1;
    for(int i=0;i<MAXLENGTH;i++)
    {
        tailX[i]=0;
        tailY[i]=0;
    }    
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
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
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
    window.clear();
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            spBackGround.setPosition(i*GRIDSIZE,j*GRIDSIZE);
            window.draw(spBackGround);
        }
    }
    for(int i=0;i<nTail;i++)
    {
        spSnack.setPosition(tailX[i]*GRIDSIZE,tailY[i]*GRIDSIZE);
        window.draw(spSnack);
    }

    spFruit.setPosition(fruitX*GRIDSIZE,fruitY*GRIDSIZE);
    window.draw(spFruit);
    window.display();
}
int main()
{
    Initial();
    while(window.isOpen())
    {
        Input();
        Logic();
        Draw();
    }
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);
    return 0;
}