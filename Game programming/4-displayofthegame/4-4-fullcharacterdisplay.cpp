////////////////////////////////////////
//��ע������Ŀ��ܲ��ǳ����ַ����±�����ʱ�����ȥ����Ѱ��ȫ���ַ�
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
bool change = 0;
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
    SetConsoleTitleA("console_̰���� Full character display");
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
            cout << "��";
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
                    cout << "��";
                else
                {
                    cout << "#";
                }
            }
            else if (j == width + 1)
            {
                SetConsoleTextAttribute(h, textColor);
                if (isFullWidth)
                    cout << "��";
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
        if (isFullWidth)
            cout << "��";
        else
        {
            cout << "#";
        }
    }
    cout << endl;
    cout << "��Ϸ�÷֣�" << score << endl;
}
void eraseSnake()
{
    for (int i = 0; i < nTail; i++)
    {
        setPos(tailX[i], tailY[i]);
        if (isFullWidth)
            cout << "   ";
        else
        {
            cout << " ";
        }
    }
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
void DrawLocally()
{
    if (isFullWidth == false && change == 0)
    {
        DrawMap();
        Prompt_info(3, 1);
        change = 1;
    }
    if (isFullWidth == true && change == 1)
    {
        DrawMap();
        Prompt_info(3, 1);
        change = 0;
    }
    if (!fruitFlash)
    {
        setPos(fruitX, fruitY);
        SetConsoleTextAttribute(h, 0x04);
        if (isFullWidth)
            cout << "��";
        else
        {
            cout << "F";
        }
        fruitFlash = true;
    }
    else
    {
        setPos(fruitX, fruitY);
        SetConsoleTextAttribute(h, 0x04);
        if (isFullWidth)
            cout << "  ";
        else
        {
            cout << " ";
        }
        fruitFlash = false;
    }

    for (int i = 0; i < nTail; i++)
    {
        setPos(tailX[i], tailY[i]);
        if (i == 0)
        {
            SetConsoleTextAttribute(h, 0x09);
            if (isFullWidth)
                cout << "��";
            else
            {
                cout << "O";
            }
        }
        else
        {
            SetConsoleTextAttribute(h, 0x0a);
            if (isFullWidth)
                cout << "��";
            else
            {
                cout << "o";
            }
        }
    }
    setPos(0, height + 1);
    SetConsoleTextAttribute(h, 0x06);
    cout << "��Ϸ�÷�" << score;
}

void showScore(int _x, int _y)
{
    setPos(_x + 20, _y + 17);
    SetConsoleTextAttribute(h, 0x0f);
    cout << "����ǰ���֣�";
    SetConsoleTextAttribute(h, 0x0c);
    cout << score;
}

void gameOver_info()
{
    setPos(5, 8);
    SetConsoleTextAttribute(h, 0xec);
    cout << "��Ϸ��������";
    setPos(3, 9);
    cout << "Y���¿�ʼ/N�˳�";
}
void Input() //����
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
            isFullWidth = !isFullWidth;

            break;
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
    if(x>=width) x=0;else if(x<0) x=width-1;
    if(y>=height) y=0;else if(y<0) y=height-1;
    //�жϳ��磬��Ϸ����
    // if (x > width - 2 || x <= 0 || y > height - 1 || y < 0)
    // {
    //     gameOver = true;
    // }
    // //�ж�������ͷ��ײ����Ϸ����
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