
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;


void Run();

void Initial();

void IniData(); 
void LoadMediaData();
void MineSet(int Py,int Px);

void Input();
void RButtonDown(Vector2i mPoint);
void LButtonDown(Vector2i mPoint);
void LButtonDblClk(Vector2i mPoint);

void Logic();
void isWin();
void unCover();

void Draw();
void DrawBG();
void DrawGrid();
void DrawButton();
void DrawScore();
void DrawTimer();
void DrawGameEnd();