#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
void gotoxy(short x,short y)//x,y là tọa điểm x,y trên màn hình
{    
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y};    SetConsoleCursorPosition(h, a);
}
void TextColor(int x)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}
void k(){
system("cls");
    TextColor(202);
            gotoxy(0, 15);  cout << "|             |";
            gotoxy(0, 16);  cout << "|    FIGHT    |";
            gotoxy(0, 17);  cout << "|_____________|";
            
            TextColor(14);
            gotoxy(15, 15); cout << "|             |";
            gotoxy(15, 16); cout << "|    CHECK    |";
            gotoxy(15, 17); cout << "|_____________|";
            
            
            gotoxy(30, 15); cout << "|             |";
            gotoxy(30, 16); cout << "|    ITEM     |";
            gotoxy(30, 17); cout << "|_____________|";

            gotoxy(45, 15);  cout << "|             |";
            gotoxy(45, 16); cout << "|    FLEE     |";
            gotoxy(45, 17); cout << "|_____________|";
        
    
    int chon = 0;
    int toado = 0;
    do{
        char a = getch();
        if(a == 77 ||a == 'd'||a=='D'||a=='6') chon = 1;
        else if(a == 75 || a == 'a'||a=='A'||a =='4') chon = 2;
        else if(a == 13 ||a=='5') chon = 3;
        else chon = 0;
        if(chon == 1 && toado < 45) toado += 15;
        else if(chon == 2 && toado >= 15) toado -= 15;
      if(toado == 0)
        {
            
            TextColor(202);
            gotoxy(0, 15);  cout << "|             |";
            gotoxy(0, 16);  cout << "|    FIGHT    |";
            gotoxy(0, 17);  cout << "|_____________|";
            
            TextColor(14);
            gotoxy(15, 15); cout << "|             |";
            gotoxy(15, 16); cout << "|    CHECK    |";
            gotoxy(15, 17); cout << "|_____________|";
            
            
            gotoxy(30, 15); cout << "|             |";
            gotoxy(30, 16); cout << "|    ITEM     |";
            gotoxy(30, 17); cout << "|_____________|";

            gotoxy(45, 15); cout << "|             |";
            gotoxy(45, 16); cout << "|    FLEE     |";
            gotoxy(45, 17); cout << "|_____________|";
            
            TextColor(0);
        }
      if(toado == 15)
        {
            
            TextColor(14);
            gotoxy(0, 15);   cout << "|             |";
            gotoxy(0, 16);  cout << "|    FIGHT    |";
            gotoxy(0, 17);  cout << "|_____________|";
            
            TextColor(202);
            gotoxy(15, 15);  cout << "|             |";
            gotoxy(15, 16); cout << "|    CHECK    |";
            gotoxy(15, 17); cout << "|_____________|";
            TextColor(14);
            
            gotoxy(30, 15);  cout << "|             |";
            gotoxy(30, 16); cout << "|    ITEM     |";
            gotoxy(30, 17); cout << "|_____________|";

            gotoxy(45, 15);  cout << "|             |";
            gotoxy(45, 16); cout << "|    FLEE     |";
            gotoxy(45, 17); cout << "|_____________|";
            
            TextColor(0);
        }
        if(toado == 30)
        {
            
            TextColor(14);
            gotoxy(0, 15);   cout << "|             |";
            gotoxy(0, 16);  cout << "|    FIGHT    |";
            gotoxy(0, 17);  cout << "|_____________|";
            
            
            gotoxy(15, 15);  cout << "|             |";
            gotoxy(15, 16); cout << "|    CHECK    |";
            gotoxy(15, 17); cout << "|_____________|";
            
            TextColor(202);
            gotoxy(30, 15);  cout << "|             |";
            gotoxy(30, 16); cout << "|    ITEM     |";
            gotoxy(30, 17); cout << "|_____________|";
            TextColor(14);

            gotoxy(45, 15);  cout << "|             |";
            gotoxy(45, 16); cout << "|    FLEE     |";
            gotoxy(45, 17); cout << "|_____________|";
            
            TextColor(0);
        }
        if(toado == 45)
        {
            
            TextColor(14);
            gotoxy(0, 15);   cout << "|             |";
            gotoxy(0, 16);  cout << "|    FIGHT    |";
            gotoxy(0, 17);  cout << "|_____________|";
            
           
            gotoxy(15, 15);  cout << "|             |";
            gotoxy(15, 16); cout << "|    CHECK    |";
            gotoxy(15, 17); cout << "|_____________|";
            
            
            gotoxy(30, 15);  cout << "|             |";
            gotoxy(30, 16); cout << "|    ITEM     |";
            gotoxy(30, 17); cout << "|_____________|";

            TextColor(202);
            gotoxy(45, 15);  cout <<"|             |";
            gotoxy(45, 16); cout << "|    FLEE     |";
            gotoxy(45, 17); cout << "|_____________|";
            
            TextColor(0);
        }
            
        
} while(chon != 3);
}
int main(){
    k();
    return 0;
}