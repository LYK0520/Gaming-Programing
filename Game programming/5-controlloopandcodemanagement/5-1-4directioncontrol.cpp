#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
////////////////////////////////////
//˫�����������Լ���������������
HANDLE hOutPut, hOutBuf;
COORD coord = {0, 0};
DWORD bytes = 0;
bool BufferSwapFlag = false;
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
int nTail = 1;
////////////////////////////////////////
// 5-1-gameloopcontrol
bool isPause = false;
////////////////////////////////////////
void Initial()
{
    ////////////////////////////////////
    //�����µĻ�����
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
    //���������������г�ʼ��������������������Ĺ��

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
    SetConsoleTitleA("console_̰����");
    COORD dSize = {80, 25};
    SetConsoleScreenBufferSize(h, dSize);
    CONSOLE_CURSOR_INFO _cursor = {1, false};
    SetConsoleCursorInfo(h, &_cursor);
    //////////////////////////////////////////
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() //����
{
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int textColor = 0X06;
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
                textColor = 0x0a;
                SetConsoleTextAttribute(h, textColor);
                cout << "O";
                int textColor = 0X06;
                SetConsoleTextAttribute(h, textColor);
            }
            else if (i == fruitY && j == fruitX)
            {
                textColor = 0x04;
                SetConsoleTextAttribute(h, textColor);
                cout << "F";
                int textColor = 0X06;
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
void Draw2() //����
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
    sprintf(ScreenData[currentLine + i], "��Ϸ�÷֣�%d", score);
}
//////////////////////////////////////
// 4-partial-renewal
/////////////////////////////////////
void setPos(int X, int Y)
{
    COORD pos;
    pos.X = X + DETA_X;
    pos.Y = Y + DETA_Y;
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
        cout << "#";
    }
    for (int i = 0; i < height; i++)
    {
        setPos(-1, i);
        for (int j = 0; j < width + 2; j++)
        {
            if (j == 0)
            {
                SetConsoleTextAttribute(h, textColor);
                cout << "#";
            }
            else if (j == width + 1)
            {
                SetConsoleTextAttribute(h, textColor);
                cout << "#";
            }
            else
            {
                SetConsoleTextAttribute(h, 0x04);
                cout << " ";
            }
        }
        cout << endl;
    }
    setPos(-1, height);
    for (int i = 0; i < width + 2; i++)
    {
        SetConsoleTextAttribute(h, textColor);
        cout << "#";
    }
    cout << endl;
    cout << "��Ϸ�÷֣�" << score << endl;
}
void eraseSnake()
{
    for (int i = 0; i < nTail; i++)
    {
        setPos(tailX[i], tailY[i]);
        cout << " ";
    }
}
void DrawLocally()
{
    if (!fruitFlash)
    {
        setPos(fruitX, fruitY);
        SetConsoleTextAttribute(h, 0x04);
        cout << "F";
        fruitFlash = true;
    }
    else
    {
        setPos(fruitX, fruitY);
        SetConsoleTextAttribute(h, 0x04);
        cout << " ";
        fruitFlash = false;
    }

    for (int i = 0; i < nTail; i++)
    {
        setPos(tailX[i], tailY[i]);
        if (i == 0)
        {
            SetConsoleTextAttribute(h, 0x09);
            cout << "O";
        }
        else
        {
            SetConsoleTextAttribute(h, 0x0a);
            cout << "o";
        }
    }
    setPos(0, height + 1);
    SetConsoleTextAttribute(h, 0x06);
    cout << "��Ϸ�÷�" << score;
}
//////////////////////////////////////////
void Show_DoubleBuffer() //����
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
    //��ɫ��ʾ˫����
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
    cout << "����ǰ���֣�";
    SetConsoleTextAttribute(h, 0x0c);
    cout << score;
}

void Prompt_info(int _x, int _y)
{
    int initialX = 20, initialY = 0;

    SetConsoleTextAttribute(h, 0x0f);
    setPos(_x + initialX, _y + initialY);
    cout << "��Ϸ˵����";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "  A.������ײ����Ϸ����";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "  B.�߿ɴ�ǽ";
    initialY++;
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "����˵����";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   �����ƶ�����A";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   �����ƶ�����D";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   �����ƶ�����S";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   �����ƶ�����W";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   ��ʼ��Ϸ�����ⷽ���";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   �˳���Ϸ��x���˳�";
}
void gameOver_info()
{
    setPos(5, 8);
    SetConsoleTextAttribute(h, 0x0c);
    cout << "��Ϸ��������";
    setPos(3, 9);
    cout << "Y���¿�ʼ/N�˳�";
}
void Input() //����
{
    isPause = false;
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
            isPause = true;
            break;
        case 224:
            switch(_getch())
            {
                case 72:
                    if(dir!= DOWN)
                    {
                        dir=UP;
                    }
                    break;
                case 80:
                    if(dir!= UP)
                    {
                        dir=DOWN;
                    }
                    break;
                case 75:
                    if(dir!= RIGHT)
                    {
                        dir=LEFT;
                    }
                    break;
                case 77:
                    if(dir!= LEFT)
                    {
                        dir=RIGHT;
                    }
                    break;
                default:
                    break;
            }
        default:

            break;
        }
    }
}
void Logic() //�߼�
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

    //�жϳ��磬��Ϸ����
    if (x > width - 2 || x <= 0 || y > height - 1 || y < 0)
    {
        gameOver = true;
    }
    //�ж�������ͷ��ײ����Ϸ����
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
int main()
{
    //////////////////////////////////////////////////
    // 5-1-gameloopcontrol
    ////////////////////////////////////////////////
    bool gameQuit = false;
    do
    {
        Initial();
        DrawMap();
        Prompt_info(5, 1);
        while (!gameOver)
        {
            // Draw();
            // Show_DoubleBuffer();
            Input();
            eraseSnake();
            Logic();
            DrawLocally();
            showScore(5, 1);
            Sleep(100);
        }
        nTail=1;
        gameOver_info();
        while (gameOver)
        {
            if (_kbhit())
            {
                switch (_getch())
                {
                case 'y':
                case 'Y':
                    gameOver = false;
                    system("cls");
                    break;
                case 'n':
                case 'N':
                    gameOver = false;
                    gameQuit = true;
                    break;
                default:
                    break;
                }
            }
            Sleep(50);
        }
    } while (!gameQuit);

    setPos(0, 23);
    system("pause");
    return 0;
}