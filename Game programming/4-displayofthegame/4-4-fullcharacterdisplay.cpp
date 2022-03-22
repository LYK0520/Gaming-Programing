////////////////////////////////////////
//备注：输出的可能不是常规字符导致报错暂时不清楚去哪里寻找全角字符
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
////////////////////////////////////
//双缓冲句柄变量以及缓冲区描述变量
HANDLE hOutPut, hOutBuf;
COORD coord = {0, 0};
DWORD bytes = 0;
bool BufferSwapFlag = false;
bool change=0;
///////////////////////////////////
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
//////////////////////////////////////
// 4-partial-renewal
/////////////////////////////////////
#define DETA_X 1;
#define DETA_Y 1;
#define EDGE_THICKNESS 1;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
bool fruitFlash = true;
/////////////////////////////////////////
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;
char ScreenData[width + 5][height + 5];
int tailX[100], tailY[100];
int nTail;
bool isFullWidth;
void Initial()
{
    ////////////////////////////////////
    //创建新的缓冲区
    hOutBuf = CreateConsoleScreenBuffer(
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL);
    hOutPut = CreateConsoleScreenBuffer(
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL);
    ///////////////////////////////////
    ///////////////////////////////////
    //对两个缓冲区进行初始化，隐藏两个缓冲区里的光标

    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = 0;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hOutPut, &cci);
    SetConsoleCursorInfo(hOutBuf, &cci);
    ///////////////////////////////////
    /////////////////////////////////////////
    // 4-3gameinterface
    /////////////////////////////////////////
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTitleA("console_贪吃蛇 Full character display");
    COORD dSize = {80, 25};
    SetConsoleScreenBufferSize(h, dSize);
    CONSOLE_CURSOR_INFO _cursor = {1, false};
    SetConsoleCursorInfo(h, &_cursor);
    //////////////////////////////////////////
    gameOver = false;
    fruitFlash = false;
    isFullWidth = true;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 1;
    tailX[0] = x;
    tailY[0] = y;
    memset(tailX, 0, sizeof(tailX));
    memset(tailY, 0, sizeof(tailY));
}

void Draw() //绘制
{
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int textColor = 0X86;
    SetConsoleTextAttribute(h, textColor);
    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << endl;
    int tailflag = false;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "#";
            }

            if (i == y && j == x)
            {
                textColor = 0x8a;
                SetConsoleTextAttribute(h, textColor);
                cout << "O";
                int textColor = 0X86;
                SetConsoleTextAttribute(h, textColor);
            }
            else if (i == fruitY && j == fruitX)
            {
                textColor = 0x84;
                SetConsoleTextAttribute(h, textColor);
                cout << "F";
                int textColor = 0X86;
                SetConsoleTextAttribute(h, textColor);
            }
            else
            {
                tailflag = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        tailflag = !tailflag;
                    }
                }
                if (!tailflag)
                {
                    cout << " ";
                }
            }
            if (j == width - 1)
            {
                cout << "#";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << endl;
}
void Draw2() //绘制
{
    int i, j;
    int currentLine = 0;
    for (j = 0; j < width + 2; j++)
    {
        ScreenData[currentLine][j] = '#';
    }
    currentLine++;

    for (i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                ScreenData[currentLine + i][j] = '#';
            }
            else if (i == fruitY && j == fruitX)
            {
                ScreenData[currentLine + i][j] = 'F';
            }
            else if (i == y && j == x)
            {
                ScreenData[currentLine + i][j] = 'O';
            }
            else
            {
                bool flagPrint = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        ScreenData[currentLine + i][j] = 'o';
                        flagPrint = true;
                    }
                }
                if (!flagPrint)
                {
                    ScreenData[currentLine + i][j] = ' ';
                }
            }
            if (j == width - 1)
            {
                ScreenData[currentLine + i][j] = '#';
            }
        }
    }
    for (int j = 0; j < width + 2; j++)
    {
        ScreenData[currentLine + i][j] = '#';
    }
    currentLine++;
    sprintf(ScreenData[currentLine + i], "游戏得分：%d", score);
}
//////////////////////////////////////
// 4-partial-renewal
/////////////////////////////////////
void setPos(int X, int Y)
{
    COORD pos;
    if (isFullWidth)
    {
        pos.X = 2 * X + 2;
    }
    else
    {
        pos.X = X + 2;
    }
    pos.Y = Y + 2;

    // pos.X=X+DETA_X;
    // pos.Y=Y+DETA_Y;
    SetConsoleCursorPosition(h, pos);
}
void DrawMap()
{
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int textColor = 0x06;
    SetConsoleTextAttribute(h, textColor);

    setPos(-1, -1);
    for (int i = 0; i < width + 2; i++)
    {
        if (isFullWidth)
            cout << "□";
        else
        {
            cout << "#";
        }
    }
    for (int i = 0; i < height; i++)
    {
        setPos(-1, i);
        for (int j = 0; j < width + 2; j++)
        {
            if (j == 0)
            {
                SetConsoleTextAttribute(h, textColor);
                if (isFullWidth)
                    cout << "□";
                else
                {
                    cout << "#";
                }
            }
            else if (j == width + 1)
            {
                SetConsoleTextAttribute(h, textColor);
                if (isFullWidth)
                    cout << "□";
                else
                {
                    cout << "#";
                }
            }
            else
            {
                SetConsoleTextAttribute(h, 0x04);
                if (isFullWidth)
                    cout << "  ";
                else
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    setPos(-1, height);
    for (int i = 0; i < width + 2; i++)
    {
        SetConsoleTextAttribute(h, textColor);
        if(isFullWidth)
            cout<<"□";
        else{
            cout<<"#";
        }
    }
    cout << endl;
    cout << "游戏得分：" << score << endl;
}
void eraseSnake()
{
    for (int i = 0; i < nTail; i++)
    {
        setPos(tailX[i], tailY[i]);
        if(isFullWidth)
            cout<<"   ";
        else{
            cout<<" ";
        }
    }
}
void Prompt_info(int _x, int _y)
{
    int initialX = 20, initialY = 0;

    SetConsoleTextAttribute(h, 0x0f);
    setPos(_x + initialX, _y + initialY);
    cout << "游戏说明：";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "  A.蛇身自撞，游戏结束";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "  B.蛇可穿墙";
    initialY++;
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "操作说明：";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   向左移动：←A";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   向右移动：→D";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   向下移动：↓S";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   向上移动：↑W";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   开始游戏：任意方向键";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   退出游戏：x键退出";
}
void DrawLocally()
{
    if(isFullWidth==false&& change==0)
        {
            DrawMap();
            Prompt_info(3, 1);
            change=1;
        }
        if(isFullWidth==true&& change==1)
        {
            DrawMap();
            Prompt_info(3, 1);
            change=0;
        }
    if (!fruitFlash)
    {
        setPos(fruitX, fruitY);
        SetConsoleTextAttribute(h, 0x04);
        if(isFullWidth)
            cout<<"☆";
        else{
            cout<<"F";
        }
        fruitFlash = true;
    }
    else
    {
        setPos(fruitX, fruitY);
        SetConsoleTextAttribute(h, 0x04);
       if(isFullWidth)
            cout<<"  ";
        else{
            cout<<" ";
        }
        fruitFlash = false;
    }

    for (int i = 0; i < nTail; i++)
    {
        setPos(tailX[i], tailY[i]);
        if (i == 0)
        {
            SetConsoleTextAttribute(h, 0x09);
            if(isFullWidth)
            cout<<"Ｏ";
        else{
            cout<<"O";
        }
        }
        else
        {
            SetConsoleTextAttribute(h, 0x0a);
            if(isFullWidth)
            cout<<"ｏ";
        else{
            cout<<"o";
        }
        }
    }
    setPos(0, height + 1);
    SetConsoleTextAttribute(h, 0x06);
    cout << "游戏得分" << score;
}
//////////////////////////////////////////
void Show_DoubleBuffer() //缓冲
{
    HANDLE hBuf;
    WORD textColor;
    int i, j;
    Draw2();
    if (BufferSwapFlag == false)
    {
        BufferSwapFlag = true;
        hBuf = hOutBuf;
    }
    else
    {
        BufferSwapFlag = false;
        hBuf = hOutPut;
    }
    for (i = 0; i < height + 5; i++)
    {
        coord.Y = i;
        for (j = 0; j < width + 5; j++)
        {
            coord.X = j;
            if (ScreenData[i][j] == 'O')
            {
                textColor = 0x03;
            }
            else if (ScreenData[i][j] == 'F')
            {
                textColor = 0x04;
            }
            else if (ScreenData[i][j] == 'o')
            {
                textColor = 0x0a;
            }
            else
            {
                textColor = 0x06;
            }
            WriteConsoleOutputAttribute(hBuf, &textColor, 1, coord, &bytes);
        }
        coord.X = 0;
        WriteConsoleOutputCharacterA(hBuf, ScreenData[i], width, coord, &bytes);
    }
    SetConsoleActiveScreenBuffer(hBuf);
    /////////////////////////////////////////////////////////////////////////////////////
    //单色显示双缓冲
    // if(BufferSwapFlag==false)
    // {
    //     BufferSwapFlag=true;
    //     for(i=0;i<height+5;i++)
    //     {
    //         coord.Y=i;
    //         WriteConsoleOutputCharacterA(hOutBuf,ScreenData[i],width,coord,&bytes);
    //     }
    //     SetConsoleActiveScreenBuffer(hOutBuf);
    // }else{
    //     BufferSwapFlag=false;
    //     for(i=0;i<height+5;i++)
    //     {
    //         coord.Y=i;
    //         WriteConsoleOutputCharacterA(hOutPut,ScreenData[i],width,coord,&bytes);
    //     }
    //     SetConsoleActiveScreenBuffer(hOutPut);
    // }
}

void showScore(int _x, int _y)
{
    setPos(_x + 20, _y + 17);
    SetConsoleTextAttribute(h, 0x0f);
    cout << "·当前积分：";
    SetConsoleTextAttribute(h, 0x0c);
    cout << score;
}


void gameOver_info()
{
    setPos(5, 8);
    SetConsoleTextAttribute(h, 0xec);
    cout << "游戏结束！！";
    setPos(3, 9);
    cout << "Y重新开始/N退出";
}
void Input() //输入
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        case ' ':
            isFullWidth=!isFullWidth;
            
            break;
        default:

            break;
        }
    }
}
void Logic() //逻辑
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
    // if(x>=width) x=0;else if(x<0) x=width-1;
    // if(y>=height) y=0;else if(y<0) y=height-1;
    //判断出界，游戏结束
    if (x > width - 2 || x <= 0 || y > height - 1 || y < 0)
    {
        gameOver = true;
    }
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
int main()
{

    Initial();
    DrawMap();
    Prompt_info(3, 1);
    while (!gameOver)
    {
        // Draw();
        // Show_DoubleBuffer();
        Input();
        eraseSnake();
        Logic();
        
        DrawLocally();
        showScore(3, 1);
        Sleep(100);
    }
    gameOver_info();
    setPos(0, 23);
    system("pause");
    return 0;
}