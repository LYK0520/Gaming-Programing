void HideCursor(){//终于没有光标了 
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cci;
GetConsoleCursorInfo(hOut, &cci);
cci.bVisible = FALSE;
SetConsoleCursorInfo(hOut, &cci);
} 
void gotoxy(int x,int y){//清屏函数
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}