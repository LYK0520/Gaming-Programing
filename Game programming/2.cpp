#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;
int main()
{
    while(1)
    {
        cout<<"1"<<endl;
        if(_kbhit())
        {
            system("pause");
        }
    }
    return 0;
}