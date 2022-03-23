#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
const int FRAME_PRE_SECOND = 25; //ºã¶¨µÄÖ¡Êý
const int SKIP_TICKS = 1000 / FRAME_PRE_SECOND;
const int MAX_FRAMESKIP = 5;
DWORD next_Game_Tick = GetTickCount();

int sleep_Time = 0;
while (!gameOver)
{
    int Loop = 0;
    next_Game_Tick = +SKIP_TICKS;
    eraseSnake();
    while (next_Game_Tick - GetTickCount() > 0&& loops < MAX_FRAMESKIP)
    {
        Input();
        Logic();
        Loops += 200 / (scrore / DIFFICULTY_FACTOR + 1);
    }
    DrawLocally();

    sleep_Time = next_Game_Tick - GetTickCount();
    if (sleep_Time >= 0)
        Sleep(sleep_Time);
}