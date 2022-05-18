```
/**************************************
-----------------card.h---------------------
product name：card
module name：card
date：2022.03.02
auther：none
file describe: none
***************************************/

#ifndef _CARD_H_
#define _CARD_H_

#ifdef __cplusplus // c++ include
extern "C"
#endif // include c++ file
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
    using namespace sf;
#define WIDTH 1920
#define HEIGHT 1114
sf::RenderWindow window(VideoMode(WIDTH, HEIGHT), "Legends of Diana");
sf::Event event;
//编写strcpy函数
void strcpy(char *a, char *b)
{
    int i = 0;
    while (b[i] != '\0')
    {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}
//编写strlen函数
int strlen(char *a)
{
    int i = 0;
    while (a[i] != '\0')
    {
        i++;
    }
    return i;
}
void safe_strncpy(char *dest, char *source, int N)
{

    int strlen_source = strlen(source);
    int i = 0, j = 0;
    int flag = 0; /*添加一个标志，用来标志所加的中文的位数 */
    unsigned char *p;
    /*N取目标串和N的最小值*/
    if (strlen_source < N)
        N = strlen_source;

    p = (unsigned char *)source;

    for (i = 0; i < N; i++) /*N-1用来腾出一位存 '\0 '，字符串数组需要 */
    {
        if (p[i] >= 0x81 && p[i] <= 0xFE) /*中文字符[0x81-0xFE] */
        {
            if ((i + 1) == N)
            {
                /* 前面一半是中文，后面是结束符，舍弃半个汉字*/
                dest[j++] = '\0';
            }
            else
            {
                if (p[i + 1] >= 0x40 && p[i + 1] <= 0xFE)
                {
                    if (p[i + 1] == 0x7C && ((p[i] < 0x81 && p[i] > 0xFE) || (p[i] > 0xA0 && p[i] < 0xA8)))
                    {
                        /* 如果是以|为分隔符的，要满足前面一半是中文，字节范围必须在【0X81-0XA0，0XA8-0XFE】之间。如果不在舍弃前面一个 */
                        i++;
                        dest[j++] = p[i];
                    }
                    else
                    {
                        /* 前面一半是中文，后面一半也是中文，说明是一个汉字*/
                        dest[j++] = p[i];
                        i++;
                        dest[j++] = p[i];
                        i++;
                        dest[j++] = p[i];
                    }
                }
                else
                {
                    /* 前面一半是中文，后面一半非中文，舍弃前面一个 */
                    i++;
                    dest[j++] = p[i];
                    i++;
                    dest[j++] = p[i];
                }
            }
        }
        else
        {
            /* 普通的非中文字符 */
            dest[j++] = p[i];
        }
    }
    dest[j] = '\0'; /*字符串最后赋值结束符*/

    return;
}
//绝对值函数
double fabs(double a)
{
    if (a <= 0)
        return -a;
    else
        return a;
}
//这个函数是将字符串改为数字
//例如“156”->156
char *itoa(int num, char *str, int radix)
{ /*索引表*/
    char index[] = "0123456789ABCDEF";
    unsigned unum; /*中间变量*/
    int i = 0, j, k;
    /*确定unum的值*/
    if (radix == 10 && num < 0) /*十进制负数*/
    {
        unum = (unsigned)-num;
        str[i++] = '-';
    }
    else
        unum = (unsigned)num; /*其他情况*/
    /*转换*/
    do
    {
        str[i++] = index[unum % (unsigned)radix];
        unum /= radix;
    } while (unum);
    str[i] = '\0';
    /*逆序*/
    if (str[0] == '-')
        k = 1; /*十进制负数*/
    else
        k = 0;

    for (j = k; j <= (i - 1) / 2; j++)
    {
        char temp;
        temp = str[j];
        str[j] = str[i - 1 + k - j];
        str[i - 1 + k - j] = temp;
    }
    return str;
}
//宏定义的字体类型，可以重复使用
sf::Font font;
//宏定义的文字类型，可以重复使用
sf::Text text;

//卡牌的类
struct Card
{
    //卡牌初始化的空函数
    Card() {}
    Card(int, int, int, char *s = "chu传说");

    int HP;
    int ATK;
    int Cost;
    //战吼：当你使用时的效果
    int Battlecry;
    //嘲讽：必须现攻击具有嘲讽的卡牌
    int Taunt;
    //亡语：卡牌死亡后的效果
    int Deathrattle;
    //圣盾：免疫一次伤害
    int Divien_Shield;

    sf::Texture Texture;
    sf::Sprite Sprite;

    double Width, Height;
    // Hold是个0/1变量，用于标识卡牌是否被抓住
    int Hold;
    int isInclude();
    void setCardFollowMouse();
    void changeHold();
    // moveFlag是个0/1变量，用于标识卡牌是否正在移动
    // moveTo()函数中会使用此变量来判断移动的结束与否
    int moveFlag;
    void moveTo(double x, double y, double speed = 40);
    // state是一个 卡牌 的状态变量
    // 0 在你的《卡牌库》中
    // 1 在你的《手牌》中
    // 2 在你的《选中》中
    // 3 在你的《战斗》中
    // 4 在你的《死亡》牌库中
    int state;
    char *name;
    void txtFollow();
};
//这个函数是用来让你的文字
//跟随！你的卡牌
//包括卡牌的名字，血量，简介，消耗值，攻击力
void Card::txtFollow()
{
    Width = Texture.getSize().x;
    Height = Texture.getSize().y;

    font.loadFromFile("wryh.ttf");
    text.setFont(font);

    char s[99];
    //消耗值
    text.setString(itoa(Cost, s, 10));
    text.setPosition(Sprite.getPosition());
    window.draw(text);
    //攻击力
    text.setString(itoa(ATK, s, 10));
    text.setPosition(Sprite.getPosition().x, Sprite.getPosition().y + Height);
    window.draw(text);
    //血量
    text.setString(itoa(HP, s, 10));
    text.setPosition(Sprite.getPosition().x + Width, Sprite.getPosition().y + Height);
    window.draw(text);
    //名字
    text.setString(name);
    text.setCharacterSize(20);
    text.setPosition(Sprite.getPosition().x + Width / 2 - 25, Sprite.getPosition().y + Height / 2);
    window.draw(text);
}
//这个是移动函数
//其中speed是移动速度，默认为40.数值越大越快
// x是目标坐标X，y是目标坐标Y
//**但是*，该函数依然有不完善的地方
//当合法误差为1，而speed作产生的位移大于1时，就有距离目标的较大误差的结果
//需要完善！！！
void Card::moveTo(double x, double y, double speed)
{
    double originalX, originalY;
    originalX = Sprite.getPosition().x;
    originalY = Sprite.getPosition().y;
    double speedX, speedY;
    speedX = (x - originalX);
    speedY = (y - originalY);
    double k = speedY / speedX;
    //当函数执行时，卡牌速度太快可能跳过判定区间从而无限往复运动
    //为了解决这个问题，用两个为坐标的flag，判定只要有一次正负变化，就停止运动
    int flagX, flagY;
    if (x > originalX)
        flagX = 1;
    else
        flagX = 0;
    if (y > originalY)
        flagY = 1;
    else
        flagY = 0;
    if (fabs(x - originalX) > 0.1)
    {
        Sprite.setPosition(originalX + speed * fabs(speedX) / (speedX), originalY + speed * fabs(speedX) / (speedX)*k);
        if (flagX && x < Sprite.getPosition().x)
            moveFlag = 0;
        if (flagY && y < Sprite.getPosition().y)
            moveFlag = 0;
        if (!flagX && x > Sprite.getPosition().x)
            moveFlag = 0;
        if (!flagY && y > Sprite.getPosition().y)
            moveFlag = 0;
    }
    else
    {
        moveFlag = 0;
    }
}
// 这个函数返回的是0/1，判断鼠标的点击是否在卡牌的范围之内
// 当你使用它之后，记得要改变你的
//**Hold*
//值
int Card::isInclude()
{
    Width = Texture.getSize().x;
    Height = Texture.getSize().y;
    double x, y;
    x = sf::Mouse::getPosition(window).x;
    y = sf::Mouse::getPosition(window).y;
    if (x - Sprite.getPosition().x < Width && x - Sprite.getPosition().x > 0 && y - Sprite.getPosition().y < Height && y - Sprite.getPosition().y > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// 初始化你的卡牌，参数的顺序是
//费用，攻击力，血量，名字(默认为test)
//注意！名字不能有中文！
Card::Card(int cost, int atk, int hp, char *namee)
{
    Cost = cost;
    HP = hp;
    ATK = atk;
    Battlecry = 0;
    Taunt = 0;
    Deathrattle = 0;
    Divien_Shield = 0;
    Hold = 0;
    moveFlag = 0;
    state = 0;
    //将名字赋值给name
    name = new char[strlen(namee) + 1];
    safe_strncpy(name, namee, strlen(namee) + 1);
}
// 让你的卡牌跟随你的鼠标
// 但是鼠标会在卡牌的*正中间*
void Card::setCardFollowMouse()
{
    Card::Sprite.setPosition(sf::Mouse::getPosition(window).x - Width / 2, sf::Mouse::getPosition(window).y - Height / 2);
}
// 只是改变你的Hold值罢了
//从0到1，从1到0
void Card::changeHold()
{
    if (Hold == 1)
        Hold = 0;
    else
        Hold = 1;
}
//一个图片的结构体
struct Img
{
    sf::Texture Texture;
    sf::Sprite Sprite;
};
#ifdef __cpluscplus
#endif
#endif // end _LIST_H

```

```
#include <SFML/Graphics.hpp>
#include "list.h"
#include "card.h"
using namespace sf;
//***************************//
//完成上牌，抽牌，取消选取，牌死亡
//完成牌的攻击判定，动画
//卡牌的效果
//***************************//

//正在选取卡片
int isChooseCard = 0;
//战斗的背景
Img batter;
//手中牌链表
List *CardHand;
//场上的战斗牌链表
List *CardinFight;
//用来测试的无用链表
List *Head;
//测试例子1
Card l(2, 2, 3, "Diana");
//测试例子2
Card p(1, 2, 3);
//创建一个节点
List *creat(List *list)
{
    Card a(0, 0, 0);
    list = (List *)malloc(sizeof(List));
    list->next = NULL;
    list->prior = NULL;
    list->val = a;
    return list;
}
//开始初始化
void Start()
{
    window.setFramerateLimit(60);
    //战斗背景的初始化
    batter.Texture.loadFromFile("img/batter.jpg");
    batter.Sprite.setTexture(batter.Texture);
    batter.Sprite.setScale(2, 2);
    //卡牌测试1的初始化
    l.Texture.loadFromFile("img/base.png");
    l.Sprite.setTexture(l.Texture);
    //卡牌测试2的初始化
    p.Texture.loadFromFile("img/q.png");
    p.Sprite.setTexture(p.Texture);
    p.Sprite.setPosition(500, 500);
    //手牌的初始化
    CardHand = creat(CardHand);
    CardHand->Insert(l);
    CardHand->Insert(p);
    //战斗卡牌的初始化
    CardinFight = creat(CardinFight);
}
void Draw()
{
    window.draw(batter.Sprite);
    //绘画手牌
    Head = CardHand->next;
    while (Head)
    {
        Card Q(0, 0, 0);
        Q = Head->val;
        window.draw(Q.Sprite);
        Q.txtFollow();

        //下一个链表内容
        Head = Head->next;
    }
    //绘画战斗卡牌
    Head = CardinFight->next;
    while (Head)
    {
        Card Q(0, 0, 0);
        Q = Head->val;
        window.draw(Q.Sprite);
        Q.txtFollow();
        //下一个链表内容
        Head = Head->next;
    }
    //场景绘画线
    CircleShape c(10);
    for (int i = 0; i < 50; i++)
    {
        c.setPosition(i * WIDTH / 50, HEIGHT / 2);
        window.draw(c);
        c.setPosition(i * WIDTH / 50, HEIGHT * 2 / 3);
        window.draw(c);
    }
    c.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    window.draw(c);
    window.display();
}
int main()
{
    Start();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // printf("Left is press\n");
                //最后一个head
                printf("CardHand: ");
                CardHand->print();
                Head = CardHand;
                while (Head->next)
                {
                    Head = Head->next;
                }
                if (isChooseCard == 0) //鼠标上没有被抓手牌
                {
                    while (Head)
                    {
                        if (Head->val.isInclude())
                        {
                            Head->val.Hold = 1;
                            break;
                        }
                        Head = Head->prior;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                printf("Right is press\n");
                Head = CardHand->next;
                while (Head)
                {
                    if (Head->val.isInclude() && Head->val.Hold)
                    {
                        Head->val.changeHold();
                        Head->val.moveFlag = 1;
                    }
                    Head = Head->next;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                // printf("Left is release\n");
                //当鼠标抓着手牌的时候↓
                Head = CardHand->next;
                while (Head)
                {
                    Head->val.Hold = 0;
                    // if (sf::Mouse::getPosition().y >= HEIGHT / 2 && sf::Mouse::getPosition().y <= HEIGHT * 2 / 3)
                    if (Head->val.Sprite.getPosition().y >= HEIGHT / 2 && Head->val.Sprite.getPosition().y <= HEIGHT * 2 / 3)
                    {
                        CardinFight->Insert(Head->val);
                        printf("CardinFight:");
                        CardinFight->print();
                        if (Head->next == NULL)
                        {
                            Head->prior->next = NULL;
                        }
                        else if (Head->next->next == NULL)
                        {
                            Head->val = Head->next->val;
                            Head->next = Head->next->next;
                        }
                        else
                        {
                            Head->val = Head->next->val;
                            Head->next = Head->next->next;
                            Head->next->prior = Head;
                        }
                    }
                    Head = Head->next;
                }
                //当鼠标抓着手牌的时候↑
            }
        }
        window.clear();

        Head = CardHand->next;
        while (Head)
        {
            if (Head->val.Hold)
            {
                Head->val.setCardFollowMouse();
            }
            Head = Head->next;
        }
        Head = CardHand->next;
        while (Head)
        {
            if (Head->val.moveFlag)
                Head->val.moveTo(500, 300);
            Head = Head->next;
        }
        Draw();
    }
}

```

```c++
do{
	bool flag=true;
	k= rand() % stageHeight;
	l= rand() % stageWidth;
	for(i= Py-1;i< Py+2; i++)
	{
		for(j= Px-1;j< Px+2;j++)
		{
			if(i>=0 && i<stageHeight && j>=0 && j<stageWidth)
			{
				if(k==i && l==j)
				{
					flag=false;
				}
			}
		}
	}
	if(flag && mGameData[k][l].mState ==ncUNDOWN)
	{
		mGameData[k][l].mState =ncMINE;
		mGameData[k][l].mStateBackUp =ncMINE;
		mCount++;
	}
}while( mCount != mMineNum)
```

