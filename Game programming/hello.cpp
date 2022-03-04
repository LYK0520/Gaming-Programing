#include <iostream>
#include<conio.h>

using namespace std;
bool isPause=false;
void input()
{
    if(_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            isPause=!isPause;
            break;
        
        default:
            break;
        }
    }
}
void Logic()
{
    cout<<"1"<<endl;
}
int main()
{

    while(1)
    {
        input();
        if(!isPause)
        {
            Logic();
        }
    }
    system("pause");
    return 0;
}