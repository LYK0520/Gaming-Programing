#include<SFML/Graphics.hpp>
#include"8-4-Animation.cpp"
#include"8-4-AnimatedSprite.cpp"
#include<bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
const int SKIP_TICKS=1000/6;
DWORD next_Game_Tick=GetTickCount();
int sleep_Time=0;
int main(int argc,char* argv[])
{
    //创建窗口
    sf::RenderWindow window(sf::VideoMode(600,800),"Example animation");
    //加载纹理图像
    sf::Texture textures;
    textures.loadFromFile("../data/images/eye.png");
    //创建两个动画序列容器
    Animation walkLeft(&textures);
    walkLeft.addFramesLine(4,2,0);
    Animation walkRight(&textures);
    walkRight.addFramesLine(4,2,1);
    //创建精灵动画对象
    AnimatedSprite sprite(&walkLeft,AnimatedSprite::Playing,sf::seconds(0.1));

    //游戏循环
    sf::Clock clock;
    while(window.isOpen())
    {
        sf::Time delta=clock.restart();
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
            }
        }
        float speed =50;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            sprite.setAnimation(&walkLeft);
            sprite.play();
            sprite.move(-speed*delta.asSeconds(),0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            sprite.setAnimation(&walkRight);
            sprite.play();
            sprite.move(speed*delta.asSeconds(),0);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            sprite.play();
            sprite.move(0,-speed*delta.asSeconds());
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            sprite.setAnimation(&walkRight);
            sprite.play();
            sprite.move(0,speed*delta.asSeconds());
        }
        window.clear();
        sprite.setFrameTime(sf::seconds(1/6.f));
        sprite.update(delta);
        next_Game_Tick+=SKIP_TICKS;
        sleep_Time=next_Game_Tick-GetTickCount();
        if(sleep_Time>0)
        {
            Sleep(sleep_Time);
        }
        window.draw(sprite);
        window.display();
        cout<<1<<endl;
    }
    return 0;
}