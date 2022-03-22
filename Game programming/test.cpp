#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
int a=1;
int abc()
{
    int a=2;
    cout<<a<<endl;
    return a;
}
int main()
{
    int a=1;
     a=abc();
     cout<<a<<endl;
     system("pause");
    return 0;
}



