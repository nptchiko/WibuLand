#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

void TextColor(int x){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}
void gotoxy(short x, short y){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y}; SetConsoleCursorPosition(h, a);
}

void animation1(){
    system("cls");
    TextColor(4);
    for(int i = 0; i < 26; i++){
        gotoxy(i, 0);        cout <<"    ~~O      /|" << endl;            
        gotoxy(i, 1);        cout <<"     _|_    // "<< endl;       
        gotoxy(i, 2);        cout <<"    |'_'| _//_ "<< endl;            
        gotoxy(i, 3);        cout <<" ===|||===//   "<< endl;         
        gotoxy(i, 4);        cout <<"    |||        "<< endl;          
        gotoxy(i, 5);        cout <<"   // \\\\     "<< endl;        
        
        gotoxy(40, 0);cout << " oo`'._..---.___.." << endl;
        gotoxy(40, 1);cout << "(_,-.        ,..'`" << endl;
        gotoxy(40, 2);cout << "   `'.      ;     " << endl;
        gotoxy(40, 3);cout << "       :--:`      " << endl;
        gotoxy(40, 4);cout << "      _; _;       " << endl;
        gotoxy(40, 5);cout << "                  " << endl;
    
        Sleep(15);
        system("cls");
    
        if(i == 25){
        
            for(int j = 25; j >=0 ; j--){
                if(j >= 15){
                    gotoxy(35, 6); cout << 50;
                }    
                gotoxy(j, 0);        cout <<"    ~~O      /|" << endl;            
                gotoxy(j, 1);        cout <<"     _|_    // "<< endl;       
                gotoxy(j, 2);        cout <<"    |'_'| _//_ "<< endl;            
                gotoxy(j, 3);        cout <<" ===|||===//   "<< endl;         
                gotoxy(j, 4);        cout <<"    |||        "<< endl;          
                gotoxy(j, 5);        cout <<"   // \\\\     "<< endl;        
                
                gotoxy(40, 0);cout << " oo`'._..---.___.." << endl;
                gotoxy(40, 1);cout << "(_,-.        ,..'`" << endl;
                gotoxy(40, 2);cout << "   `'.      ;     " << endl;
                gotoxy(40, 3);cout << "       :--:`      " << endl;
                gotoxy(40, 4);cout << "      _; _;       " << endl;
                gotoxy(40, 5);cout << "                  " << endl;
        
                Sleep(15);
                system("cls");
            }
        }
    }
}    
void animation2(){    
    for(int i = 40; i > 15 ; i--){
        gotoxy(0, 0);        cout <<"    ~~O      /|" << endl;            
        gotoxy(0, 1);        cout <<"     _|_    // "<< endl;       
        gotoxy(0, 2);        cout <<"    |'_'| _//_ "<< endl;            
        gotoxy(0, 3);        cout <<" ===|||===//   "<< endl;         
        gotoxy(0, 4);        cout <<"    |||        "<< endl;          
        gotoxy(0, 5);        cout <<"   // \\\\     "<< endl;        
        
        gotoxy(i, 0);cout << " oo`'._..---.___.." << endl;
        gotoxy(i, 1);cout << "(_,-.        ,..'`" << endl;
        gotoxy(i, 2);cout << "   `'.      ;     " << endl;
        gotoxy(i, 3);cout << "       :--:`      " << endl;
        gotoxy(i, 4);cout << "      _; _;       " << endl;
        gotoxy(i, 5);cout << "                  " << endl;
        
        Sleep(15);
        system("cls");
    
        if(i == 16){
            for(int j = 16; j <= 40 ; j++){
                if(j <= 26){
                    gotoxy(15, 6); cout << 50;
                }
                gotoxy(0, 0);        cout <<"    ~~O      /|" << endl;            
                gotoxy(0, 1);        cout <<"     _|_    // "<< endl;       
                gotoxy(0, 2);        cout <<"    |'_'| _//_ "<< endl;            
                gotoxy(0, 3);        cout <<" ===|||===//   "<< endl;         
                gotoxy(0, 4);        cout <<"    |||        "<< endl;          
                gotoxy(0, 5);        cout <<"   // \\\\     "<< endl;        
                
                gotoxy(j, 0);cout << " oo`'._..---.___.." << endl;
                gotoxy(j, 1);cout << "(_,-.        ,..'`" << endl;
                gotoxy(j, 2);cout << "   `'.      ;     " << endl;
                gotoxy(j, 3);cout << "       :--:`      " << endl;
                gotoxy(j, 4);cout << "      _; _;       " << endl;
                gotoxy(j, 5);cout << "                  " << endl;
                Sleep(15);
                system("cls");
            }
        
        }
    
    }       
    
}         
      

int main(){
    animation1();
    animation2();
    return 0;
}