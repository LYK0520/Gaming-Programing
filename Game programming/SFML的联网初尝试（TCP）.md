啧啧啧，好久没更新了。今天小编为大家带来的是SFML的联网初尝试（TCP）

这是一个简单的联网小程序，用于两端的交互和显示。

值得注意的是，小编提供的是完整可以执行的代码，夸我~

不过仅仅是最简单的联网程序，大家可以在此基础上进行更改，如果作业里想做联网的同志们可以相互交流以下哈哈哈。一些需要注意的地方，我都写在代码的注释里面了~

```c++
#include <SFML/Network.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

#define TILE_SIZE 40.f

using namespace std;

int main()

{

​    // 建立连接↓

​    sf::TcpSocket socket;

​    std::string consoleInput;

​    std::cin >> consoleInput;

​    if (consoleInput == "host")

​    {

​        sf::TcpListener listener;

​        listener.listen(45000);

​        cout << "Waiting for connection..." << endl;

​        if (listener.accept(socket) != sf::Socket::Done)

​        {

​            return -1;

​        }

​    }

​    else

​    {

​        cout << "Try to connect to..." << endl;

​        if (socket.connect(consoleInput, 45000, sf::seconds(10)) != sf::Socket::Done)

​        {

​            return -1;

​        }

​    }

​    //建立连接↑

​    // 建立一个简单的联网测试游戏 需要注意的是需要有两个窗口的显示一个是local端一个是remote端

​    sf::RenderWindow window(sf::VideoMode(640, 480), "Networking");

​    socket.setBlocking(false);

​    sf::Vector2f shapeSize(TILE_SIZE, TILE_SIZE);

​    //注意！！！就是这两个窗口的显示

​    sf::RectangleShape localShape(shapeSize);

​    sf::RectangleShape remoteShape(shapeSize);



​    while (window.isOpen())

​    {

​        // Handle Input

​        //这个很简单，主要就是方块的移动，看两边是否协同

​        sf::Vector2i moveDir;

​        sf::Event event;

​        while (window.pollEvent(event))

​        {

​            switch (event.type)

​            {

​            case sf::Event::KeyPressed:

​                if (event.key.code == sf::Keyboard::W)

​                {

​                    moveDir.y += -1;

​                }

​                else if (event.key.code == sf::Keyboard::A)

​                {

​                    moveDir.x += -1;

​                }

​                else if (event.key.code == sf::Keyboard::S)

​                {

​                    moveDir.y += 1;

​                }

​                else if (event.key.code == sf::Keyboard::D)

​                {

​                    moveDir.x += 1;

​                }

​                break;

​            case sf::Event::Closed:

​                window.close();

​                break;

​            default:

​                break;

​            }

​        }

​        //检查是否有新的数据传递

​        //更新remote端的显示和local端的显示

​        sf::Packet packet;

​        if(socket.receive(packet)==sf::Socket::Done)

​        {

​            sf::Vector2f pos;

​            packet>>pos.x>>pos.y;

​            remoteShape.setPosition(pos);    

​        }

​        //update frame

​        if(moveDir.x!=0||moveDir.y!=0)

​        {

​            localShape.move(moveDir.x*TILE_SIZE,moveDir.y*TILE_SIZE);

​            sf::Packet packet;

​            packet<<localShape.getPosition().x<<localShape.getPosition().y;

​            //如果断开连接或者是其他的错误，退出程序

​            if(socket.send(packet)!=sf::Socket::Done)

​            {

​                cout<<"Failed to send packet"<<endl;

​                return -1;

​            }

​        }

​        //draw frame

​        window.clear();

​        window.draw(localShape);

​        window.draw(remoteShape);

​        window.display();

​    }

}


```

好的，需要注意的是如果想要在自己的电脑上同时运行两个程序，也是可以执行的。

要求：打开两个相同的程序，一个输入host 一个输入127.0.0.1就可以构建相互的联系。

还有如果大家在运行的时候，如果出现了类似于 undefined reference to `__imp__ZN2sf11TcpListener6listenEtRKNS_9IpAddressE'的提示，但也不是报错，不用慌张。

解决方案如下：

​    在task.json当中，加入“-lsfml-network"，再次运行就可以解决问题啦~

![img](https://p.ananas.chaoxing.com/star3/origin/d4811e7b36ccc8a8a8590ec58d448ffd.png?rw=676&rh=185&_fileSize=16051&_orientation=1)

如果还有其他的想法欢迎在评论区里面留言，或者QQcall我哈~


  