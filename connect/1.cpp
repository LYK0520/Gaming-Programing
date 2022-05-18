#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#define TILE_SIZE 40.f
using namespace std;
int main()
{
    // 建立连接↓
    sf::TcpSocket socket;
    std::string consoleInput;
    std::cin >> consoleInput;
    if (consoleInput == "host")
    {
        sf::TcpListener listener;
        listener.listen(45000);
        cout << "Waiting for connection..." << endl;
        if (listener.accept(socket) != sf::Socket::Done)
        {
            return -1;
        }
    }
    else
    {
        cout << "Try to connect to..." << endl;
        if (socket.connect(consoleInput, 45000, sf::seconds(10)) != sf::Socket::Done)
        {
            return -1;
        }
    }
    //建立连接↑
    // 建立一个简单的联网测试游戏 需要注意的是需要有两个窗口的显示一个是local端一个是remote端
    sf::RenderWindow window(sf::VideoMode(640, 480), "Networking");
    socket.setBlocking(false);
    sf::Vector2f shapeSize(TILE_SIZE, TILE_SIZE);
    //注意！！！就是这两个窗口的显示
    sf::RectangleShape localShape(shapeSize);
    sf::RectangleShape remoteShape(shapeSize);

    while (window.isOpen())
    {
        // Handle Input
        //这个很简单，主要就是方块的移动，看两边是否协同
        sf::Vector2i moveDir;
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::W)
                {
                    moveDir.y += -1;
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    moveDir.x += -1;
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    moveDir.y += 1;
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    moveDir.x += 1;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        //检查是否有新的数据传递 
        //更新remote端的显示和local端的显示
        sf::Packet packet;
        if(socket.receive(packet)==sf::Socket::Done)
        {
            sf::Vector2f pos;
            packet>>pos.x>>pos.y;
            remoteShape.setPosition(pos);    
        }
        //update frame
        if(moveDir.x!=0||moveDir.y!=0)
        {
            localShape.move(moveDir.x*TILE_SIZE,moveDir.y*TILE_SIZE);
            sf::Packet packet;
            packet<<localShape.getPosition().x<<localShape.getPosition().y;
            //如果断开连接或者是其他的错误，退出程序
            if(socket.send(packet)!=sf::Socket::Done)
            {
                cout<<"Failed to send packet"<<endl;
                return -1;
            }
        }
        //draw frame
        window.clear();
        window.draw(localShape);
        window.draw(remoteShape);
        window.display();
    }
}
