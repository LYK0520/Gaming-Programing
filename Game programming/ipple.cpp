#include<iostream>
#include<windows.h>
using namespace std;

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int textColor = 0x02;
	cout << R"(

)" << '\n';
	SetConsoleTextAttribute(h, textColor);
	cout << R"(
                                                                                      
                                                                                      
                                                                                      
                                                                                      
                                                        `.                            
                                                  .:!!!!!'                            
                                               `;!!!!!!!!'                            
                                             `;!!!!!!!!!;.                            
                                           .;!!!!!!!!!!!'                             
                                          `;!!!!!!!!!!!'                              
                                         `;!!!!!!!!!!!'                               
                                        .;!!!!!!!!!!;.                                
                                        `!!!!!!!!!;.                                  
                                        '!!!!!!;`   
                                             )" << '\n'; 
    textColor = 0x03;
    SetConsoleTextAttribute(h, textColor);
  	cout << R"(                            
                      .`::;;;:'.        .:'`          `':;;;;:'.                      
                  ';!!!!!!!!!!!!!!!!:`          `:!!!!!!!!!!!!!!!!!:.                 
               :!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;.              
            .;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;`            
           :!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:.          
         `;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;'             
        `:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::.  )";
        textColor = 0x04;
    SetConsoleTextAttribute(h, textColor);
  	cout << R"(          
       .::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::`                 
       ':::::::::::::::::::::::::::::::::::::::::::::::::::::::::::`                  
      `:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::`                   
      '::::::::::::::::::::::::::::::::::::::::::::::::::::::::::'.                   
     .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;' )";   
        textColor = 0x05;
    SetConsoleTextAttribute(h, textColor);
  	cout << R"(                    
     .;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'                    
     .;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'                    
     .:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:.                   
      :;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'                   
      :|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||!'                  
      `!||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||:  )";   
        textColor = 0x06;
    SetConsoleTextAttribute(h, textColor);
  	cout << R"(                 
      .;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||;.               
       `!||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||;.             
        :||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||!:           
        .;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||'        
         .;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'         
          `;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'          
           `;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'  )" ;   
        textColor = 0x07;
    SetConsoleTextAttribute(h, textColor);
  	cout << R"(          
            .;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`            
              :!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;.             
               ';!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;'               
                .:!!!;;;;;;;;;;!!!!;!!!!!;;;;;;;;;;;;;;;;;;;;;;;;;!!;`                
                  `;!;;;;;;;;;;!!!!;!!!!!;;;;;;;;;;;;;;;;;;;;;;;;!;'         ..       
                    `;!!;;;;;;;;;!!!!!!;;;:::;;!!!!!;;;;;;;;;;!!;'           ..       
                      .:;!!!!!!!;;;`              .:;!!!!!!!!;:.                      
                            ..                          ...                  ..       
                                                                                      


)";




	system("pause");

	return 0;
}