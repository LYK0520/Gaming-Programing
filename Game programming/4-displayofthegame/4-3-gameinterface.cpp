#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
////////////////////////////////////
//????????????????????????????
HANDLE hOutPut, hOutBuf;
COORD coord = {0, 0};
DWORD bytes = 0;
bool BufferSwapFlag = false;
///////////////////////////////////
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
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
int nTail=1;
void Initial()
{
////////////////////////////////////
//????????????
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
//???????????????��?????????????????????????

    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = 0;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hOutPut, &cci);
    SetConsoleCursorInfo(hOutBuf, &cci);
///////////////////////////////////   
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() //????
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
    int tailflag=false;
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
                tailflag=false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                         cout << "o";
                        tailflag=!tailflag;
                    }
                }
                if(!tailflag)
                {
                    cout<<" ";
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
void Draw2() //????
{
    int i, j;
    int currentLine = 0;
    for (j = 0; j < width + 2; j++)
    {
        ScreenData[currentLine][j] = '#';
    }
    currentLine++;

    for ( i = 0; i < height; i++)
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
    sprintf(ScreenData[currentLine + i], "????��??%d", score);
    
}
void Show_DoubleBuffer()//????
{
    HANDLE hBuf;
    WORD textColor;
    int i,j;
    Draw2();
    if(BufferSwapFlag==false)
    {
        BufferSwapFlag=true;
        hBuf=hOutBuf;
    }else{
        BufferSwapFlag=false;
       hBuf=hOutPut;
    }
    for(i=0;i<height+5;i++)
    {
        coord.Y=i;
        for(j=0;j<width+5;j++)
        {
            coord.X=j;
            if(ScreenData[i][j]=='O')
            {
                textColor=0x03;
            }else if(ScreenData[i][j]=='F')
            {
                textColor=0x04;
            }else if(ScreenData[i][j]=='o')
            {
                textColor=0x0a;
            }else{
                textColor=0x06;
            }
            WriteConsoleOutputAttribute(hBuf,&textColor,1,coord,&bytes);
        }
        coord.X=0;
        WriteConsoleOutputCharacterA(hBuf,ScreenData[i],width,coord,&bytes);
    }
    SetConsoleActiveScreenBuffer(hBuf);
/////////////////////////////////////////////////////////////////////////////////////
//???????????
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
void Input() //????
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
        default:

            break;
        }
    }
}
void Logic() //???
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

    //?��???��???????
     if(x>width-2||x<=0||y>height-1||y<0)
    {
        gameOver=true;
    }
    //?��????????????????????
    for(int i=1;i<nTail;i++)
    {
        if(tailX[i]==x&&tailY[i]==y)
        {
            gameOver=true;
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
    Sleep(100);
}
int main()
{

    Initial();
    while (!gameOver)
    {
         //Draw(); 
        Show_DoubleBuffer();
        Input();
        Logic();   
    }
    _getch();
    system("pause");
    return 0;
}