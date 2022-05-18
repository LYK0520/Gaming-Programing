// #include <iostream>
// #include <string>
// using namespace std;
// #define MAX_CHAR_LENGH (50)
// int strlen(char *a)
// {
//     int i = 0;
//     while (a[i] != '\0')
//     {
//         i++;
//     }
//     return i;
// }
// void safe_strncpy(char *dest, char *source, int N)
// {

//     int strlen_source = strlen(source);
//     int i = 0, j = 0;
//     int flag = 0; /*添加一�?标志，用来标志所加的�?文的位数 */
//     unsigned char *p;
//     /*N取目标串和N的最小�?*/
//     if (strlen_source < N)
//         N = strlen_source;

//     p = (unsigned char *)source;

//     for (i = 0; i < N; i++) /*N-1用来腾出一位存 '\0 '，字符串数组需�? */
//     {
//         if (p[i] >= 0x81 && p[i] <= 0xFE) /*�?文字�?[0x81-0xFE] */
//         {
//             if ((i + 1) == N)
//             {
//                 /* 前面一半是�?文，后面�?结束符，舍弃半个汉字*/
//                 dest[j++] = '\0';
//             }
//             else
//             {
//                 if (p[i + 1] >= 0x40 && p[i + 1] <= 0xFE)
//                 {
//                     if (p[i + 1] == 0x7C && ((p[i] < 0x81 && p[i] > 0xFE) || (p[i] > 0xA0 && p[i] < 0xA8)))
//                     {
//                         /* 如果�?�?|为分隔�?�的，�?�满足前�?一半是�?文，字节范围必须在�?0X81-0XA0�?0XA8-0XFE】之间。�?�果不在舍弃前面一�? */
//                         i++;
//                         dest[j++] = p[i];
//                     }
//                     else
//                     {
//                         /* 前面一半是�?文，后面一半也�?�?文，说明�?一�?汉字*/
//                         dest[j++] = p[i];
//                         i++;
//                         dest[j++] = p[i];
//                         i++;
//                         dest[j++] = p[i];
//                     }
//                 }
//                 else
//                 {
//                     /* 前面一半是�?文，后面一半非�?文，舍弃前面一�? */
//                     i++;
//                     dest[j++] = p[i];
//                     i++;
//                     dest[j++] = p[i];
//                 }
//             }
//         }
//         else
//         {
//             /* �?通的非中文字�? */
//             dest[j++] = p[i];
//         }
//     }
//     dest[j] = '\0'; /*字�?�串最后赋值结束�??*/

//     return;
// }

// int main()
// {
//     char *str = "123451234512345我";
//     char *Intercept;
//     Intercept = (char *)malloc(MAX_CHAR_LENGH);
//     string s;
//     safe_strncpy(Intercept, str, strlen(str));
//     cout << Intercept << endl;
//     getchar();
//     return 0;
// }
// #include <fcntl.h>
// #include <io.h>
// #include <iostream>

// int main(void) {
//     _setmode(_fileno(stdout), _O_U16TEXT);
//     std::wcout << L"中文\n";
//     getchar();
//     return 0;
// }
// #include<iostream>
// #include<string>
// using namespace std;
// #define MAX_CHAR_LENGH (50)
// int main()
// {	
// 	string	str="123451234512345一二三";
// 	string Intercept;
// 	int CharCount = 0;
// 	for (int i = 0; i < str.size(); i++) {
//  		if (CharCount <= MAX_CHAR_LENGH) {
//     			if (str[i] & 0x80) {
//     	 			CharCount += 3;			
//      				if (CharCount > MAX_CHAR_LENGH ) {//对下一个中文是否超出截取范围做判断，超出即不能继续拼接字符串
//       					break;
//      				}
//      			Intercept += str[i];
//      			Intercept += str[++i];
//                  Intercept += str[++i];
//     		} else {
//      			CharCount += 1;
//      			Intercept += str[i];
//     		}
//    	}
// }
// cout<<Intercept<<endl;
// getchar();
// }

// #include <SFML/Graphics.hpp>
// #include <bits/stdc++.h>
// using namespace sf;
// int mouseStatus = 0;
// int x, y;          // x,y是按钮的位置
// int height, width; // height,weight是按钮的宽高
// sf::RenderWindow window(VideoMode(800, 600), "Legends of Diana");
// void mouseFunc()
// {
//     mouseStatus = 0;
//     Vector2i position = Mouse::getPosition(window); //window是游戏窗口
//     if (position.x >= x && position.x <= x + width || position.y >= y && position.y <= y + height)
//     {
//         if (Mouse::isButtonPressed(Mouse::Left))
//         {
//             mouseStatus = 1;
//         }
//         else
//         {
//             mouseStatus = 2;
//         }
//     }
//     switch (mouseStatus)
//     {
//     case 0:
//         //按钮处于普通状态
//         break;
//     case 1:
//         //按钮处于点击状态
//         break;
//     case 2:
//         //按钮处于鼠标滑过状态
//         break;
//     default:
//         break;
//     }
// }
//二进制加法
// int add(int a, int b)
// {
//     int sum = 0;
//     int carry = 0;
//     while (b != 0)
//     {
//         sum = a ^ b;
//         carry = (a & b) << 1;
//         a = sum;
//         b = carry;
//     }
//     return a;
// }
