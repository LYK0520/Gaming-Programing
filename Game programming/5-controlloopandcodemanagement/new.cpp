#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
/////////////////////////////////////////
// 5-3-code maintenance and management
////////////////////////////////////////
#define STAGE_WIDTH 20
#define STAGE_HEIGHT 20
#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 25
#define CORNER_X 1
#define CORNER_Y 1
#define THICKNESS 1
#define MAXLENGTH 100
#define COLOR_WALL 0x06
#define COLOR_TEXT 0x0f
#define COLOR_TEXT2 0xec
#define COLOR_SCORE 0x0c
#define COLOR_FRUIT 0x04
#define COLOR_SNAKE_HEAD 0x09
#define COLOR_SNAKE_BODY 0x0a
using namespace std;
////////////////////////////////////
//˫�����������Լ���������������
HANDLE hOutPut, hOutBuf;
COORD coord = {0, 0};
DWORD bytes = 0;
bool BufferSwapFlag = false;
///////////////////////////////////
bool gameOver;
const int width = STAGE_WIDTH;
const int height = STAGE_HEIGHT;
int x, y, fruitX, fruitY, score;
//////////////////////////////////////
// 4-partial-renewal
/////////////////////////////////////
#define DETA_X 1;
#define DETA_Y 1;
#define EDGE_THICKNESS 1;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
bool fruitFlash = true;
bool isFullWidth;
bool change = 0;
//����ڼ�����ĸ�ıȶ�
int nowwordnumber=0;
//next һ������ͨ�ر�־
int nextwordflag;
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
int tailX[MAXLENGTH], tailY[MAXLENGTH];
int nTail = 1;
////////////////////////////////////////
// 5-1-gameloopcontrol
bool isPause = false;

struct flagxy
{
    int FruitX, FruitY;
    bool flag=0;
    int number;
    string ch;
}flagXY[width][height];
////////////////////////////////////////
/////////////////////////////////////////
// 5-2-Gameframeratemanagement
////////////////////////////////////////
const int FRAMES_PER_SECOND = 25;
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
DWORD next_Game_Tick = GetTickCount();
int sleep_Time = 0;
#define DIFFICULTY_FACTOR 50
string word[100];
int nowword=1,totalword;

std::string ToFull(std::string str)
{
 std::string result = "";  
 unsigned char tmp; unsigned char tmp1;  
 for (unsigned int i = 0; i < str.length(); i++)
 {  
  tmp = str[i];  
  tmp1 = str[i + 1];  
  //cout << "uchar:" << (int) tmp << endl;  
  if (tmp>32 && tmp<128)
  {//�ǰ���ַ�
   result += 163;//��һ���ֽ�����Ϊ163
   result += (unsigned char)str[i]+128;//�ڶ����ֽ�+128;  
  }
  else if (tmp >= 163)
  {//��ȫ���ַ�  
   result += str.substr(i, 2);  
   i++;  
   continue;  
  }
  else if (tmp == 32)
  {//�����ǿո�  
   result += 161; 
   result += 161; 
  }
  else
  {  
   result += str.substr(i, 2);  
   i++;
  }
 }
 return result;  
}



string ToHalf(string str) {   
    string result = "";   
    unsigned char tmp; unsigned char tmp1;   
    for (unsigned int i = 0; i < str.length(); i++) {   
        tmp = str[i];   
        tmp1 = str[i + 1];   
        cout << "uchar:" << (int) tmp << endl;   
        if (tmp == 163) {///��һ���ֽ���163����־����ȫ���ַ�   
            result += (unsigned char) str[i + 1] - 128;   
            i++;   
            continue;   
        } else if (tmp > 163) {//����   
            result += str.substr(i, 2);   
            i++;   
            continue;   
        } else if (tmp == 161 && tmp1 == 161) {///����ȫ�ǿո�   
            result += "";   
            i++;   
        } else {   
            result += str.substr(i, 1); } } return result;   
} 

//���ļ����뵽string��
void readFileIntoString(char *filename, string *inword)
{

    ifstream f(filename, ios::in);
    int i = 1;
    while (!f.eof())
    {
        f >> inword[i];
        i++;
    }
    totalword=i-1;
}
//

//
//��ĸ��λ�ü�¼
// struct wordPosition
// {
    
//     int number;
//     char ch;
// } wp[10][20];
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
    
    for (int j = 0; j < word[nowword].size(); j++)
    {
        while (1)
        {
            int x1, y1;
            x1 = rand() % width;
            y1 = rand() % height;
            if (flagXY[x1][y1].flag == 0)
            {
                flagXY[x1][y1].flag = 1;
                flagXY[x1][y1].ch=word[nowword].substr(j,1);
                flagXY[x1][y1].number=nowword;
                break;
            }
        }
    }
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
            if (tailX[i] == width - 1)
            {
                cout << "  ";
            }

            else
            {
                cout << "  ";
            }
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
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "***<<ÿ�ռǵ���>>***";
    initialY++;
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
    cout << "   �����ƶ�����A/a";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   �����ƶ�����D/d";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   �����ƶ�����S/s";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   �����ƶ�����W/w";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   �ı�ȫ��/���ģʽ��G/g";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   ��ʼ��Ϸ�����ⷽ���";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   �ո������ͣ����������ͣ";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   ���¿�ʼ��Y/y";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   ��Ϸ������X/x";

    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "   �˳���Ϸ�� N/n���˳�";
    initialY++;
    initialY++;
    initialY++;
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "  ����ɣ�";
    for(int i=1;i<=nowword-1;i++)
    {
        initialY++;
        setPos(_x + initialX, _y + initialY);
        cout << i<<" :"<<word[i];
    }
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
    // if (!fruitFlash)
    // {
    //     setPos(fruitX, fruitY);
    //     SetConsoleTextAttribute(h, 0x04);
    //     if (isFullWidth)
    //         cout << "��";
    //     else
    //     {
    //         cout << "F";
    //     }
    //     fruitFlash = true;
    // }
    // else
    // {
    //     setPos(fruitX, fruitY);
    //     SetConsoleTextAttribute(h, 0x04);
    //     if (isFullWidth)
    //         cout << "  ";
    //     else
    //     {
    //         cout << " ";
    //     }
    //     fruitFlash = false;
    // }
    if(nextwordflag==1)
    {
        Prompt_info(3,1);
        for (int j = 0; j < word[nowword].size(); j++)
        {
            while (1)
            {
                int x1, y1;
                x1 = rand() % width;
                y1 = rand() % height;
                if (flagXY[x1][y1].flag == 0)
                {
                    flagXY[x1][y1].flag = 1;
                    flagXY[x1][y1].ch=word[nowword].substr(j,1);
                    flagXY[x1][y1].number=nowword;
                    break;
                }
            }
        }
        nextwordflag=0;
    }
    
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            if(flagXY[i][j].flag==1 and flagXY[i][j].number==nowword)
            {
                setPos(i, j);
                SetConsoleTextAttribute(h, 0x04);
                if(isFullWidth)
                {
                    cout << ToFull(flagXY[i][j].ch);
                }else{
                    cout << flagXY[i][j].ch;
                }
                
            }
        }
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
                cout <<ToFull(word[nowword].substr(i-1,1));
            else
            {
                cout << word[nowword].substr(i-1,1);
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
    SetConsoleTextAttribute(h, 0x0c);
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
        case 'A':
            dir = LEFT;
            break;
        case 'd':
        case 'D':
            dir = RIGHT;
            break;
        case 'w':
        case 'W':
            dir = UP;
            break;
        case 's':
        case 'S':
            dir = DOWN;
            break;
        case 'x':
        case 'X':
            gameOver = true;
            break;
        case ' ':
            isPause = !isPause;
            break;
        case 'y':
        case 'Y':

            system("cls");
            
            nowword=1;
            for(int i=0;i<width;i++)
            {
                for(int j=0;j<height;j++)
                {
                    flagXY[i][j].flag=0;
                }
            }
            Initial();
            DrawMap();
            Prompt_info(3, 1);
            break;
        case 'n':
        case 'N':
            exit(0);
            break;
        case 'g':
        case 'G':
            isFullWidth = !isFullWidth;
            break;
        case 224:
            switch (_getch())
            {
            case 72:
                if (dir != DOWN)
                {
                    dir = UP;
                }
                break;
            case 80:
                if (dir != UP)
                {
                    dir = DOWN;
                }
                break;
            case 75:
                if (dir != RIGHT)
                {
                    dir = LEFT;
                }
                break;
            case 77:
                if (dir != LEFT)
                {
                    dir = RIGHT;
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
    for(int i=0;i<=word[nowword].size();i++)
    {
        if(flagXY[x][y].flag==1 && flagXY[x][y].ch==word[nowword].substr(nowwordnumber,1))
        {
            flagXY[x][y].flag=0;
            nowwordnumber++;
            nTail++;
            score+=10;
            if(nowwordnumber==word[nowword].size())
            {
                nowword++;
                nowwordnumber=0;
                nextwordflag=1;
                nTail=1;
            }
        }
    }
    // if (x == fruitX && y == fruitY)
    // {
    //     fruitX = rand() % width;
    //     fruitY = rand() % height;
    //     nTail++;
    //     score += 10;
    // }

    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
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
    //////////////////////////////////////////////

    //�ļ���
    char *fn = "a.txt";
    string str;
    readFileIntoString(fn, word);
    for (int i = 1; i <= 5; i++)
    {
        cout << i << " " << word[i] << endl;
    }

    system("pause");

    //////////////////////////////////////////////////
    // 5-1-gameloopcontrol
    ////////////////////////////////////////////////
    bool gameQuit = false;
    do
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
            if (!isPause)
            {
                Logic();
            }
            // Logic();
            //  if(GetAsyncKeyState(VK_SPACE)&&pauseKey==0)
            //  {
            //      system("pause");
            //      pauseKey++;
            //  }else if(pauseKey!=0){
            //      pauseKey=0;
            //  }
            if (score % DIFFICULTY_FACTOR == 0)
            {
                Prompt_info(3, 1);
            }
            DrawLocally();
            showScore(3, 1);
            ///////////////////////////////////
            // 5-2-Gameframeratemanagement
            /////////////////////////////////////
            // Sleep(100);
            //  next_Game_Tick+=SKIP_TICKS;
            //  sleep_Time=next_Game_Tick-GetTickCount();
            //  if(sleep_Time>=0)
            //  {
            //      Sleep(sleep_Time);
            //  }
            ////////////////////////////////////////
            // jiezouyunandu
            //////////////////////////////////////
            int sleep_Time = 200 / (score / DIFFICULTY_FACTOR + 1);
            Sleep(sleep_Time);
        }
        nTail = 1;nowword=1;
        for(int i=0;i<width;i++)
        {
            for(int j=0;j<height;j++)
            {
                flagXY[i][j].flag=0;
            }
        }
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
                    nowword=1;
                    for(int i=0;i<width;i++)
                    {
                        for(int j=0;j<height;j++)
                        {
                            flagXY[i][j].flag=0;
                        }
                    }
                    Initial();
                    DrawMap();
                    Prompt_info(3, 1);
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