#include "Game.h"
#include <iostream>
using namespace std;
Game::Game()
{
    Window_width = 860;
    Window_height = 600;

    gamelvl = 2;
    window.create(sf::VideoMode(Window_width, Window_height), L"Mine-Sweeper by LYK");
}
Game::~Game()
{
}
void Game::NullClick(int j, int i)
{
    cout<<"wuyu"<<endl;
    int k, l;
    for (k = j - 1; k < j + 2; k++)
    {
        for (l = i - 1; l < i + 2; l++)
        {
            if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
            {
                if (mGameData[k][l].isPress == false)
                {
                    if(mGameData[k][l].mState!=ncMINE)
                    {
                        mGameData[k][l].isPress = true;
                        cout<<8<<endl;
                    }

                    if (mGameData[k][l].mState == ncNULL)
                    {
                        NullClick(k, l);
                    }
                }
            }
        }
    }
}
void Game::unCover()
{
    int i, j;
    for (j = 0; j < stageHeight; j++)
    {
        for (i = 0; i < stageWidth; i++)
        {
            if (mGameData[j][i].isPress == false)
            {
                if (mGameData[j][i].mState == ncMINE)
                {
                    mGameData[j][i].isPress = true;
                    mGameData[j][i].mState = ncUNFOUND;
                }
            }
        }
    }
}
void Game::isWin()
{
    //p215 p216
    int i, j, c = 0;
    // if(mFlagCalc==mMineNum)
    // {
    //     for(i=0;i<stageWidth;i++)
    //     {
    //         for(j=0;j<stageHeight;j++)
    //         {
    //             if(mGameData[j][i].mState==ncFLAG)
    //             {
    //                 if(mGameData[j][i].mStateBackUp==ncMINE)
    //                 {
    //                     c++;
    //                 }
    //             }
    //         }
    //     }
    // }else{
    //     if(isGameOverState!=ncLOSE)
    //     {
    //         for(i=0;i<stageWidth;i++)
    //         {
    //             for(j=0;j<stageHeight;j++)
    //             {
    //                 if(mGameData[j][i].isPress==false||mGameData[j][i].mState==ncFLAG)
    //                 {
    //                     c++;
    //                 }
    //             }
    //         }
    //     }
    // }
    if (isGameOverState != ncLOSE)
    {
        for (i = 0; i < stageWidth; i++)
        {
            for (j = 0; j < stageHeight; j++)
            {
                if (mGameData[j][i].isPress == false || mGameData[j][i].mState == ncFLAG)
                {
                    c++;
                }
            }
        }
    }
    if (c == mMineNum)
    {
        isGameBegin = false;
        mFlagCalc=mMineNum;
        undownOpen();
        isGameOverState = ncWIN;
    }
}
void Game::undownOpen()
{
    int i,j;
    for(j=0;j<stageHeight;j++)
    {
        for(i=0;i<stageWidth;i++)
        {
            if(mGameData[j][i].isPress==false)
            {
                mGameData[j][i].isPress=true;
                if(mGameData[j][i].mState=ncMINE)
                {
                    mGameData[j][i].mState=ncFLAG;
                }
            }
        }
    }
}
void Game::LoadMediaData()
{
    std::stringstream ss;
    // ss<<"data/images/BK0"<<imgBGNo<<".jpg";
    ss.fill('0');
    ss << "data/images/BK";
    ss.width(2);
    ss << imgBGNo << ".jpg";
    if (!tBackground.loadFromFile(ss.str()))
    {
        std::cout << "BK image 没有找到" << std::endl;
    }
    ss.str(""); //清空字符串
    ss << "data/images/Game" << imgSkinNo << ".jpg";
    if (!tTiles.loadFromFile(ss.str()))
    {
        cout << "Game Skin Image 没有找到" << endl;
    }
    if (!tNum.loadFromFile("data/images/num.jpg"))
    {
        cout << "Num.jpg 没有找到" << endl;
    }
    if (!tTimer.loadFromFile("data/images/jishiqi.jpg"))
    {
        cout << "jishiqi.jpg 没有找到" << endl;
    }
    if (!tCounter.loadFromFile("data/images/jishuqi.jpg"))
    {
        cout << "jishuqi.jpg 没有找到" << endl;
    }
    if (!tButtons.loadFromFile("data/images/button.jpg"))
    {
        cout << "button.jpg 没有找到" << endl;
    }
    if (!tGameOver.loadFromFile("data/images/gameover.jpg"))
    {
        cout << "gameover.jpg 没有找到" << endl;
    }

    sBackground.setTexture(tBackground);
    sTiles.setTexture(tTiles);
    if(gamelvl==1)
    {
        float scale=1.0*LVL2_WIDTH/LVL1_WIDTH;
        sTiles.setScale(scale,scale);
        gridSize=GRIDSIZE*scale;
    }else{
        gridSize=GRIDSIZE;
         sTiles.setScale(1.0,1.0);
    }
    sButtons.setTexture(tButtons);
    sNum.setTexture(tNum);
    sTimer.setTexture(tTimer);
    sCounter.setTexture(tCounter);
    sGameOver.setTexture(tGameOver);
}
void Game::IniData()
{
    int i, j;
    for (j = 0; j < stageHeight; j++)
    {
        for (i = 0; i < stageWidth; i++)
        {
            mGameData[j][i].mState = ncUNDOWN;
            mGameData[j][i].isPress = false;
        }
    }
}
void Game::Initial()
{
    window.setFramerateLimit(10);
    
    gridSize = GRIDSIZE; //点击的位置的块的大小

    switch (gamelvl)
    {
    case 1:
        stageWidth = LVL1_WIDTH;
        stageHeight = LVL1_HEIGHT;
        mMineNum = LVL1_NUM;
        break;
    case 2:
        stageWidth = LVL2_WIDTH;
        stageHeight = LVL2_HEIGHT;
        mMineNum = LVL2_NUM;
        break;
    case 3:
        stageWidth = LVL3_WIDTH;
        stageHeight = LVL3_HEIGHT;
        mMineNum = LVL3_NUM;
        break;
    default:
        break;
    }
    gameOver = false;
    gameQuit = false;
    isGameOverState = ncNo; //初始化游戏的结束状态
    mFlagCalc = 0;          //初始化棋子的数量
    isGameBegin = false;    //初始化游戏是否开始
    mTime = 0;              //初始化游戏进行的时间
    mCornPoint.x = (Window_width - stageWidth * gridSize) / 2;
    mCornPoint.y = (Window_height - stageHeight * gridSize) / 2;
    IniData();       //初始化数据
    LoadMediaData(); //加载素材
}
void Game::MineSet(int Py, int Px)
{
    int mCount, i, j, k, l;
    mCount = 0;
    srand(time(NULL));
    do
    {
        bool flag = true;
        k = rand() % stageHeight;
        l = rand() % stageWidth;
        // if(k==Py && l==Px)
        // {
        //     continue;
        // }
        for (i = Py - 1; i < Py + 2; i++)
        {
            for (j = Px - 1; j < Px + 2; j++)
            {
                if (i >= 0 && i < stageHeight && j >= 0 && j < stageWidth)
                {
                    if (k == i && l == j)
                    {
                        flag = false;
                    }
                }
            }
        }
        if (mGameData[k][l].mState == ncUNDOWN)
        {
            mGameData[k][l].mState = ncMINE;
            mGameData[k][l].mStateBackUp = ncMINE;
            mCount++;
        }
    } while (mCount != mMineNum);

    for (i = 0; i < stageHeight; i++)
    {
        for (j = 0; j < stageWidth; j++)
        {
            if (mGameData[i][j].mState != ncMINE)
            {
                mCount = 0;
                for (k = i - 1; k < i + 2; k++)
                {
                    for (l = j - 1; l < j + 2; l++)
                    {
                        if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
                        {
                            if (mGameData[k][l].mState == ncMINE)
                            {
                                mCount++;
                            }
                        }
                    }
                }
                switch (mCount)
                {
                case 0:
                    mGameData[i][j].mState = ncNULL;
                    break;
                case 1:
                    mGameData[i][j].mState = ncONE;
                    break;
                case 2:
                    mGameData[i][j].mState = ncTWO;
                    break;
                case 3:
                    mGameData[i][j].mState = ncTHREE;
                    break;
                case 4:
                    mGameData[i][j].mState = ncFOUR;
                    break;
                case 5:
                    mGameData[i][j].mState = ncFIVE;
                    break;
                case 6:
                    mGameData[i][j].mState = ncSIX;
                    break;
                case 7:
                    mGameData[i][j].mState = ncSEVEN;
                    break;
                case 8:
                    mGameData[i][j].mState = ncEIGHT;
                    break;
                }
            }
        }
    }
}
void Game::RL_ButtonDown(Vector2i mPoint)
{
    int i,j,k,l;
    i=(mPoint.x-mCornPoint.x)/gridSize;
    j=(mPoint.y-mCornPoint.y)/gridSize;

    if(i>=0&& i<stageWidth&& j>=0 && j<stageHeight)
    {
        if(mGameData[j][i].isPress==true)
        {
            if(mGameData[j][i].mState!=ncFLAG && mGameData[j][i].mState!=ncQ)
            {
                for(k=j-1;k<j+2;k++)
                {
                    for(l=i-1;l<i+2;l++)
                    {
                        if(k>=0 && k<stageHeight&& l>=0 && l<stageWidth)
                        {
                            if(mGameData[k][l].isPress==false)
                            {
                                mGameData[k][l].isPress=true;
                                mGameData[k][l].mState=ncX;
                            }
                        }
                    }
                }
            }else{
                for(k=j-1;k<j+2;k++)
                {
                    for(l=i-1;l<i+2;l++)
                    {
                        if(k>=0 && k<stageHeight&& l>=0 && l<stageWidth)
                        {
                            if(mGameData[k][l].isPress==false)
                            {
                                mGameData[k][l].isPress=true;
                                mGameData[k][l].mState=ncX;
                            }
                        }
                    }
                }
                mGameData[j][i].isPress=false;
            }
        }
    }
    RL_Point=mPoint;
    RL_ClkJudge_flag=true;
}
void Game::Input()
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            gameQuit = true;
        }
        if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::Escape)
        {
            window.close();
            gameQuit = true;
        }
        // p219
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            mouse_RL_ClkReady=0;
            cout<<1<<endl;
           P2 = Mouse::getPosition(window);
            if (isGameOverState == ncNo)
            {
                if(mouseClickTimer.getElapsedTime().asMilliseconds()>500)
                {
                    mouseClickTimer.restart();
                    P2=Mouse::getPosition(window);

                    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        RL_ButtonDown(P2);
                        cout<<2<<endl;
                    }
                    else{
                        cout<<3<<endl;
                        LButtonDown(P2);
                        mouseDlbClkReady=true;
                    }
                }
                mouse_RL_ClkReady++;
                // if (mouseClickTimer.getElapsedTime().asMilliseconds() < 500 && P2.x - P1.x < gridSize / 4 && P2.y - P1.y < gridSize / 4 && mouseDlbClkReady)
                // {
                //     LButtonDblClk(P2);
                //     mouseDlbClkReady = false;
                // }
                // else
                // {
                //     LButtonDown(P2);
                //     mouseDlbClkReady = true;
                //     mouse_RL_ClkReady = true;
                //     mouse_RL_ClkReady++;
                //     if (mouse_RL_ClkReady == 2)
                //     {
                //         RL_ButtonDown(Mouse::getPosition(window));
                //     }
                // }
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            if (isGameOverState == ncNo)
            {
                mouse_RL_ClkReady++;

                if (mouse_RL_ClkReady == 2)
                {
                    RL_ButtonDown(Mouse::getPosition(window));
                }
                else
                {
                    RButtonDown(Mouse::getPosition(window));
                }
            }
        }
        // if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        // {
        //     if (isGameOverState == ncNo)
        //     {
        //         if (mouseClickTimer.getElapsedTime().asMilliseconds() > 300)
        //         {
        //             LButtonDown(Mouse::getPosition(window));
        //         }
        //         else
        //         {
        //              cout<<12<<endl;
        //             LButtonDblClk(Mouse::getPosition(window));
        //         }
        //     }
        // }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            if (isGameOverState == ncNo)
            {
                mouseClickTimer.restart();
                if(mouseDlbClkReady)
                {
                    mouseDlbClkReady=false;
                }else{
                    P1=Mouse::getPosition(window);
                   if (mouseClickTimer.getElapsedTime().asMilliseconds() < 500 && P2.x - P1.x < gridSize / 4 && P2.y - P1.y < gridSize / 4 && mouseDlbClkReady)
                    {
                        cout<<11<<endl;
                    LButtonDblClk(P2);
                    }
                }
                mouse_RL_ClkReady=0;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            if (isGameOverState == ncNo)
            {
                RButtonDown(Mouse::getPosition(window));
            }
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            if (isGameOverState == ncNo)
            {
                mouseClickTimer.restart();
                mouseAction = RButtonDownFunc;
                mousePoint = Mouse::getPosition(window);
                P1 = Mouse::getPosition(window);
                if (isGameBegin == false)
                {
                    if (ButtonRectEasy.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        gamelvl = 1;
                    }
                    if (ButtonRectNormal.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        gamelvl = 2;
                    }
                    if (ButtonRectHard.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        gamelvl = 3;
                    }
                    Initial();
                }
            }
            if (ButtonRectBG.contains(event.mouseButton.x, event.mouseButton.y))
            {
                imgBGNo++;
                if (imgBGNo > 7)
                {
                    imgBGNo = 1;
                }
                LoadMediaData();
            }
            if (ButtonRectSkin.contains(event.mouseButton.x, event.mouseButton.y))
            {
                imgSkinNo++;
                if (imgSkinNo > 6)
                {
                    imgSkinNo = 1;
                }
                LoadMediaData();
            }
            if (ButtonRectRestart.contains(event.mouseButton.x, event.mouseButton.y))
            {
                Initial();
            }
            if (ButtonRectQuit.contains(event.mouseButton.x, event.mouseButton.y))
            {
                window.close();
                gameQuit = true;
            }
        }
    }
}
void Game::RButtonDown(Vector2i mPoint)
{
    int i, j;
    i = (mPoint.x - mCornPoint.x) / gridSize;
    j = (mPoint.y - mCornPoint.y) / gridSize;

    if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)
    {
        if(isGameBegin==false)//重新开始
        {
            isGameBegin=true;
            gameClock.restart();
        }
        if (mGameData[j][i].isPress == false)//如果是未揭开状态，设立flag并且备份
        {
            mGameData[j][i].isPress = true;
            mGameData[j][i].mStateBackUp = mGameData[j][i].mState;
            mGameData[j][i].mState = ncFLAG;
            cout<<4<<endl;
            mFlagCalc++;
        }
        else
        {
            cout<<i<<" "<<j<<endl;
            cout<<5<<endl;
            if (mGameData[j][i].mState == ncFLAG)//flag变成问号
            {
                mGameData[j][i].isPress = true;
                mGameData[j][i].mState = ncQ;
                mFlagCalc--;
                cout<<6<<endl;
            }
            else if (mGameData[j][i].mState == ncQ)//问号变回未揭开状态
            {
                mGameData[j][i].isPress = false;
                mGameData[j][i].mState = mGameData[j][i].mStateBackUp;
            }
        }
    }
}
void Game::LButtonDown(Vector2i mPoint)
{
    int i, j;
    i = (mPoint.x - mCornPoint.x) / gridSize;
    j = (mPoint.y - mCornPoint.y) / gridSize;

    if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)
    {
        //可能出现点击重来之后无法点击的情况
        // if(isGameBegin==false)
        // {
        //     isGameBegin=true;
        //     gameClock.restart();
        // }
        // if(isMineSetBegin==false)
        // {
        //     isMineSetBegin=true;
        //     MineSet(j,i);
        // }
        if (isGameBegin == false)
        {
            isGameBegin = true;
            gameClock.restart();
            MineSet(j, i);
        }
        cout<<"test1"<<endl;
        if (mGameData[j][i].mState != ncFLAG)
        {
            if (mGameData[j][i].isPress == false)
            {
                cout<<"test4"<<endl;
                mGameData[j][i].isPress = true;
                if (mGameData[j][i].mState == ncMINE)
                {
                    cout<<"test2"<<endl;
                    isGameBegin = false;
                    isGameOverState = ncLOSE;
                    mGameData[j][i].mState = ncBOMBING;
                    unCover();
                }
                cout<<"test5"<<endl<<endl;
                cout<<mGameData[j][i].mState<<endl;
                if (mGameData[j][i].mState !=ncMINE)
                {
                    cout<<"test"<<endl;
                    cout<<"test7"<<endl;
                    NullClick(j, i);
                }
                cout<<"test6"<<endl;
            }
        }
    }
}
void Game::LButtonDblClk(Vector2i mpoint)
{
    int i, j, k, l, lvl;
    i = (mpoint.x - mCornPoint.x) / gridSize;
    j = (mpoint.y - mCornPoint.y) / gridSize;

    if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)
    {
        if (mGameData[j][i].isPress == true)
        {
            if (mGameData[j][i].mState != ncFLAG)
            {
                for (k = j - 1; k < j + 2; k++)
                {
                    for (l = i - 1; l < i + 2; l++)
                    {
                        if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
                        {
                            if (mGameData[k][l].mState == ncFLAG)//如果是旗子
                            {
                                if (mGameData[k][l].mStateBackUp != ncMINE)
                                {
                                    isGameOverState = ncLOSE;
                                    isGameBegin = false;
                                    unCover();
                                }
                            }
                            else
                            {
                                if (mGameData[k][l].isPress == false)
                                {
                                    mGameData[k][l].isPress = true;
                                    if (mGameData[k][l].mState == ncMINE)
                                    {
                                        isGameOverState = ncLOSE;
                                        isGameBegin = false;
                                        mGameData[k][l].mState = ncBOMBING;
                                        unCover();
                                    }
                                    if (mGameData[k][l].mState == ncNULL)
                                    {
                                        cout<<10<<endl;
                                        NullClick(k, l);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void Game::RL_ClkJudge()
{
    int i,j,k,l,mineNum=0,flagNum=0;
    i=(RL_Point.x-mCornPoint.x)/gridSize;
    j=(RL_Point.y-mCornPoint.y)/gridSize;
    if(i>=0&& i<stageWidth && j>=0 && j<stageHeight)
    {
        if(mGameData[j][i].isPress==true)
        {
            if(mGameData[j][i].mState!=ncFLAG)
            {
                for(k=j-1;k<j+2;k++)
                {
                    for(l=i-1;l<i+2;l++)
                    {
                        if(k>=0&& k<stageHeight&& l>=0&& l<stageWidth)
                        {
                            if(mGameData[k][l].mState==ncFLAG)
                            {
                                flagNum++;
                            }
                            if(mGameData[k][l].mState==ncX)
                            {
                                mGameData[k][l].isPress=false;
                                mGameData[k][l].mState=mGameData[k][l].mStateBackUp;
                            }
                        }
                    }
                }
            }
        }
        if(mGameData[j][i].mState==flagNum+2)
        {
            LButtonDblClk(RL_Point);
        }
    }
    RL_ClkJudge_flag=false;
}
void Game::Logic()
{
    // if(mouse_RL_ClkReady==0 && RL_ClkJudge_flag==true)
    // {
    //     RL_ClkJudge();
    // }
    switch (mouseAction)
    {
    case RButtonDownFunc:
        cout<<"this is RButtonDownFunc"<<endl;
        RButtonDown(mousePoint);
        break;
    case LButtonDownFunc:
        cout<<"this is LButtonDownFunc"<<endl;
        LButtonDown(mousePoint);
        break;
    case LButtonDblClkFunc:
        cout<<"this is RButtonDblClkFunc"<<endl;
        LButtonDblClk(mousePoint);
        break;
    }
    isWin();
}
void Game::DrawGrid()
{
    mCornPoint.x = (Window_width - stageWidth * gridSize) / 2;
    mCornPoint.y = (Window_height - stageHeight * gridSize) / 2;
    for (int j = 0; j < stageHeight; j++)
    {
        for (int i = 0; i < stageWidth; i++)
        {
            if (mGameData[j][i].isPress == true)
            {
                sTiles.setTextureRect(IntRect(mGameData[j][i].mState * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
                sTiles.setPosition(mCornPoint.x + i * gridSize, mCornPoint.y + j * gridSize);
            }
            else
            {
                sTiles.setTextureRect(IntRect(ncUNDOWN * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
                sTiles.setPosition(mCornPoint.x + i * gridSize, mCornPoint.y + j * gridSize);
            }
            window.draw(sTiles);
        }
    }
}
void Game::DrawButton()
{
    Vector2i LeftCorner;
    int ButtonWidth = 60;
    int ButtonHeight = 36;
    int detaX;
    detaX = (Window_width - ButtonWidth * 7) / 8; //七个按钮在界面上等分
    LeftCorner.y = Window_height - GRIDSIZE * 3;

    // ButtonRectEasy
    LeftCorner.x = detaX;
    sButtons.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
    sButtons.setPosition(LeftCorner.x, LeftCorner.y);
    ButtonRectEasy.left = LeftCorner.x;
    ButtonRectEasy.top = LeftCorner.y;
    ButtonRectEasy.width = ButtonWidth;
    ButtonRectEasy.height = ButtonHeight;
    window.draw(sButtons);

    // ButtonRectNormal
    LeftCorner.x = detaX * 2 + ButtonWidth;
    sButtons.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
    sButtons.setPosition(LeftCorner.x, LeftCorner.y);
    ButtonRectNormal.left = LeftCorner.x;
    ButtonRectNormal.top = LeftCorner.y;
    ButtonRectNormal.width = ButtonWidth;
    ButtonRectNormal.height = ButtonHeight;
    window.draw(sButtons);

    // ButtonRectEasy
    LeftCorner.x = detaX * 3 + ButtonWidth * 2;
    sButtons.setTextureRect(IntRect(2 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
    sButtons.setPosition(LeftCorner.x, LeftCorner.y);
    ButtonRectHard.left = LeftCorner.x;
    ButtonRectHard.top = LeftCorner.y;
    ButtonRectHard.width = ButtonWidth;
    ButtonRectHard.height = ButtonHeight;
    window.draw(sButtons);

    // ButtonRectBG
    LeftCorner.x = detaX * 4 + ButtonWidth * 3;
    sButtons.setTextureRect(IntRect(3 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
    sButtons.setPosition(LeftCorner.x, LeftCorner.y);
    ButtonRectBG.left = LeftCorner.x;
    ButtonRectBG.top = LeftCorner.y;
    ButtonRectBG.width = ButtonWidth;
    ButtonRectBG.height = ButtonHeight;
    window.draw(sButtons);

    // ButtonRectSkin
    LeftCorner.x = detaX * 5 + ButtonWidth * 4;
    sButtons.setTextureRect(IntRect(4 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
    sButtons.setPosition(LeftCorner.x, LeftCorner.y);
    ButtonRectSkin.left = LeftCorner.x;
    ButtonRectSkin.top = LeftCorner.y;
    ButtonRectSkin.width = ButtonWidth;
    ButtonRectSkin.height = ButtonHeight;
    window.draw(sButtons);

    // ButtonRectRestart
    LeftCorner.x = detaX * 6 + ButtonWidth * 5;
    sButtons.setTextureRect(IntRect(5 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
    sButtons.setPosition(LeftCorner.x, LeftCorner.y);
    ButtonRectRestart.left = LeftCorner.x;
    ButtonRectRestart.top = LeftCorner.y;
    ButtonRectRestart.width = ButtonWidth;
    ButtonRectRestart.height = ButtonHeight;
    window.draw(sButtons);

    // ButtonRectQuit
    LeftCorner.x = detaX * 7 + ButtonWidth * 6;
    sButtons.setTextureRect(IntRect(6 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
    sButtons.setPosition(LeftCorner.x, LeftCorner.y);
    ButtonRectQuit.left = LeftCorner.x;
    ButtonRectQuit.top = LeftCorner.y;
    ButtonRectQuit.width = ButtonWidth;
    ButtonRectQuit.height = ButtonHeight;
    window.draw(sButtons);
}
void Game::DrawScore()
{
    Vector2i LeftCorner;
    LeftCorner.x = Window_width - sCounter.getLocalBounds().width * 1.25;
    LeftCorner.y = sCounter.getLocalBounds().height * 0.5;
    sCounter.setPosition(LeftCorner.x, LeftCorner.y);
    window.draw(sCounter);

    int NumSize = sNum.getLocalBounds().height;
    LeftCorner.x = LeftCorner.x + sCounter.getLocalBounds().width - NumSize;
    LeftCorner.y = LeftCorner.y + sCounter.getLocalBounds().height * 0.5 - NumSize * 0.5;

    int mScore = mMineNum - mFlagCalc;
    //绘制个位数的数字
    int a = mScore % 10;
    sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
    //在贴图上取对应数字字符的纹理贴图
    sNum.setPosition(LeftCorner.x, LeftCorner.y);
    window.draw(sNum);

    //绘制十位数的数字
    mScore = mScore / 10;
    a = mScore % 10;
    LeftCorner.x = LeftCorner.x - NumSize;
    sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
    //在贴图上取对应数字字符的纹理贴图
    sNum.setPosition(LeftCorner.x, LeftCorner.y);
    window.draw(sNum);

    //绘制百位数的数字

    mScore = mScore / 10;
    a = mScore % 10;
    LeftCorner.x = LeftCorner.x - NumSize;
    sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
    //在贴图上取对应数字字符的纹理贴图
    sNum.setPosition(LeftCorner.x, LeftCorner.y);
    window.draw(sNum);
}
void Game::DrawTimer()
{
    Vector2i LeftCorner;
    LeftCorner.x = sTimer.getLocalBounds().width * 0.25;
    LeftCorner.y = sTimer.getLocalBounds().height * 0.5;
    sTimer.setPosition(LeftCorner.x, LeftCorner.y);
    window.draw(sTimer);
    if (isGameBegin)
    {
        mTime = gameClock.getElapsedTime().asSeconds();
    }
    int mScore = mTime;
    if (mScore > 999)
    {
        mScore = 999;
    }
    int NumSize = sNum.getLocalBounds().height;
    LeftCorner.x = LeftCorner.x + sTimer.getLocalBounds().width - NumSize * 1.5;
    LeftCorner.y = LeftCorner.y + sTimer.getLocalBounds().height * 0.5 - NumSize * 0.5;

    //绘制个位数的数字
    int a = mScore % 10;
    sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
    //在贴图上取对应数字字符的纹理贴图
    sNum.setPosition(LeftCorner.x, LeftCorner.y);
    window.draw(sNum);

    //绘制十位数的数字
    mScore = mScore / 10;
    a = mScore % 10;
    LeftCorner.x = LeftCorner.x - NumSize;
    sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
    //在贴图上取对应数字字符的纹理贴图
    sNum.setPosition(LeftCorner.x, LeftCorner.y);
    window.draw(sNum);

    //绘制百位数的数字

    mScore = mScore / 10;
    a = mScore % 10;
    LeftCorner.x = LeftCorner.x - NumSize;
    sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
    //在贴图上取对应数字字符的纹理贴图
    sNum.setPosition(LeftCorner.x, LeftCorner.y);
    window.draw(sNum);
}
void Game::DrawGameEnd()
{
    Vector2i LeftCorner;
    int ButtonWidth = 200;
    int ButtonHeight = sGameOver.getLocalBounds().height;
    LeftCorner.x = (Window_width - ButtonWidth) / 2;
    LeftCorner.y = (Window_height - ButtonHeight) / 2;

    sGameOver.setPosition(LeftCorner.x, LeftCorner.y);

    if (isGameOverState == ncWIN)
    {
        sGameOver.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
    }
    if (isGameOverState == ncLOSE)
    {
        sGameOver.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
    }
    window.draw(sGameOver);
}
void Game::Draw()
{
    window.clear();
    //绘制背景
    sBackground.setPosition(0, 0);
    window.draw(sBackground);
    //绘制舞台
    DrawGrid();
    DrawButton();
    DrawTimer();
    DrawScore();
    if (isGameOverState)
    {
        DrawGameEnd();
    }
    window.display();
}
void Game::Run()
{
    do
    {
        Initial();
        while (window.isOpen() && gameOver == false)
        {
            Input();

            Logic();

            Draw();
        }
    } while (window.isOpen() && !gameQuit);
}