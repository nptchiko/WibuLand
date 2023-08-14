#include <iostream>
#include <windows.h>
#include <conio.h>
#include <windows.h>
#include <direct.h>

using namespace std;
#define X 4
#define Y 2
#define SCREEN_W 72
#define SCREEN_H 24
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD a;
void gotoxy(short x,short y)//x,y là tọa điểm x,y trên màn hình
{    
    a = {x, y};    SetConsoleCursorPosition(h, a);
}
void TextColor(int x)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

void HoiThoai(int x, int y, string s){
    for(int i = 0;i < s.length(); i++){
        gotoxy(x + i, y); cout << s[i];
        Sleep(100);
    }
}
void vekhung(){
    system("cls");
    for(int i = 1; i <= 71; i++){
        gotoxy(i, 0); cout << "_";
    }
    for(int i = 1; i <= 23; i++){
        gotoxy(0, i); cout << "|";
        gotoxy(72, i); cout << "|";
        cout << endl;
    }
    for(int i = 1; i <= 71; i++){
        gotoxy(i, 23); cout << "_";
    }
    
    for(int i = 4; i <= 68; i++){
        gotoxy(i, 9); cout << "_";
    }
    for(int i = 10; i <= 16; i++){
        gotoxy(3, i); cout << "|";
        gotoxy(69, i); cout << "|";
        cout << endl;
    }
    for(int i = 4; i <= 68; i++){
        gotoxy(i, 16); cout << "_";
    }
    
    gotoxy(3, 19); cout << "Name";
    gotoxy(4+10, 19); cout << "LEVEL 3";
    gotoxy(4+ 10 + 10 + 10, 19); cout << "HP:100/100" ;
    for(int i = 1; i <= 71; i++){
            gotoxy(i, 20); cout << "_";
        }
            gotoxy(0, 21);  cout << "|                 ";
            gotoxy(0, 22);  cout << "|      FIGHT      ";
            gotoxy(0, 23);  cout << "|_________________";
            
            
            gotoxy(18, 21); cout << "|                 ";
            gotoxy(18, 22); cout << "|      CHECK      ";
            gotoxy(18, 23); cout << "|_________________";
              
            
            gotoxy(36, 21); cout << "|                 ";
            gotoxy(36, 22); cout << "|      ITEM       ";
            gotoxy(36, 23); cout << "|_________________";
            

            gotoxy(54, 21); cout << "|                 |";
            gotoxy(54, 22); cout << "|      FLEE       |";
            gotoxy(54, 23); cout << "|_________________|";
    TextColor(14);
    gotoxy(4, 2); cout << "   ~~O      /|" << endl;
    gotoxy(4, 3); cout << "    _|_    // " << endl;
    gotoxy(4, 4); cout << "   |'_'| _//_ " << endl;
    gotoxy(4, 5); cout << "===|||===//   " << endl;
    gotoxy(4, 6); cout << "   |||        " << endl;
    gotoxy(4, 7); cout << "  // \\\\       " << endl;
    
  
    gotoxy(50, 2); cout << "        ,\\        " << endl;
    gotoxy(50, 3); cout << "      __/_\\__     " << endl;
    gotoxy(50, 4); cout << "     , ((\")\\//  " << endl;
    gotoxy(50, 5); cout << "      \\_/ \\_|     " << endl;
    gotoxy(50, 6); cout << "       /___\\|     " << endl;
    gotoxy(50, 7); cout << "       _/ |_|     " << endl;
    
    TextColor(7);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(h,&lpCursor);
}
void k(){
    system("cls");
    //Hiệp sĩ 6x14      Quái 5x18  0,4 - 14,
    for(int i = 4; i <= 36; i++){
        gotoxy(i, 2); cout << "   ~~O      /|" << endl;
        gotoxy(i, 3); cout << "    _|_    // " << endl;
        gotoxy(i, 4); cout << "   |'_'| _//_ " << endl;
        gotoxy(i, 5); cout << "===|||===//   " << endl;
        gotoxy(i, 6); cout << "   |||        " << endl;
        gotoxy(i, 7); cout << "  // \\\\       " << endl;        
        
        gotoxy(50, 3); cout << " oo`'._..---.___.." << endl;
        gotoxy(50, 4); cout << "(_,-.        ,..'`" << endl;
        gotoxy(50, 5); cout << "   `'.      ;     " << endl;
        gotoxy(50, 6); cout << "       :--:`     " << endl;
        gotoxy(50, 7); cout << "      _; _;      " << endl;
        
        Sleep(13);
        system("cls");
        
        if(i == 36){
            for(int j = 36; j >= 4;  j--){
                    if(j >= 26){
                        gotoxy(48, 6); cout << 12;
                    }
                    gotoxy(j, 2); cout << "   ~~O      /|" << endl;
                    gotoxy(j, 3); cout << "    _|_    // " << endl;
                    gotoxy(j, 4); cout << "   |'_'| _//_ " << endl;
                    gotoxy(j, 5); cout << "===|||===//   " << endl;
                    gotoxy(j, 6); cout << "   |||        " << endl;
                    gotoxy(j, 7); cout << "  // \\\\       " << endl;        
                    
                    gotoxy(50, 3); cout << " oo`'._..---.___.." << endl;
                    gotoxy(50, 4); cout << "(_,-.        ,..'`" << endl;
                    gotoxy(50, 5); cout << "   `'.      ;     " << endl;
                    gotoxy(50, 6); cout << "       :--:`     " << endl;
                    gotoxy(50, 7); cout << "      _; _;      " << endl;
                    
                    Sleep(13);
                    system("cls");
            }
        }
    }
    for(int i = 1; i < 72; i++){
        gotoxy(i, 0); cout << "_";
    }
    for(int i = 1; i <= 23; i++){
        gotoxy(0, i); cout << "|";
        gotoxy(72, i); cout << "|";
        cout << endl;
    }
    for(int i = 1; i <= 71; i++){
        gotoxy(i, 23); cout << "_";
    }
    
    gotoxy(4, 2); cout << "   ~~O      /|" << endl;
    gotoxy(4, 3); cout << "    _|_    // " << endl;
    gotoxy(4, 4); cout << "   |'_'| _//_ " << endl;
    gotoxy(4, 5); cout << "===|||===//   " << endl;
    gotoxy(4, 6); cout << "   |||        " << endl;
    gotoxy(4, 7); cout << "  // \\\\       " << endl;
    
    gotoxy(50, 3); cout << " oo`'._..---.___.." << endl;
    gotoxy(50, 4); cout << "(_,-.        ,..'`" << endl;
    gotoxy(50, 5); cout << "   `'.      ;     " << endl;
    gotoxy(50, 6); cout << "       :--:`     " << endl;
    gotoxy(50, 7); cout << "      _; _;      " << endl;

     
}
void k2(){
    for(int i = 50; i >= 18; i--){
        gotoxy(4, 2); cout << "   ~~O      /|" << endl;
        gotoxy(4, 3); cout << "    _|_    // " << endl;
        gotoxy(4, 4); cout << "   |'_'| _//_ " << endl;
        gotoxy(4, 5); cout << "===|||===//   " << endl;
        gotoxy(4, 6); cout << "   |||        " << endl;
        gotoxy(4, 7); cout << "  // \\\\       " << endl;

        gotoxy(i, 3); cout << " oo`'._..---.___.." << endl;
        gotoxy(i, 4); cout << "(_,-.        ,..'`" << endl;
        gotoxy(i, 5); cout << "   `'.      ;     " << endl;
        gotoxy(i, 6); cout << "       :--:`     " << endl;
        gotoxy(i, 7); cout << "      _; _;      " << endl;

        Sleep(15);
        system("cls");
        
        if(i == 18){
            for(int j = 18; j <= 50; j++){
                if(j <= 30){
                    gotoxy(19, 5); cout << 12;
                }
                gotoxy(4, 2); cout << "   ~~O      /|" << endl;
                gotoxy(4, 3); cout << "    _|_    // " << endl;
                gotoxy(4, 4); cout << "   |'_'| _//_ " << endl;
                gotoxy(4, 5); cout << "===|||===//   " << endl;
                gotoxy(4, 6); cout << "   |||        " << endl;
                gotoxy(4, 7); cout << "  // \\\\       " << endl;

                gotoxy(j, 3); cout << " oo`'._..---.___.." << endl;
                gotoxy(j, 4); cout << "(_,-.        ,..'`" << endl;
                gotoxy(j, 5); cout << "   `'.      ;     " << endl;
                gotoxy(j, 6); cout << "       :--:`      " << endl;
                gotoxy(j, 7); cout << "      _; _;       " << endl;

                Sleep(15);
                system("cls");
            }
        }
    }
}
void inthongtin(){
    string ten = "*MADBEAR      ATK 10        LEVEL 1";
    gotoxy(5,11); cout << ten;
    string str = "*Lmao Lmao Lmao";
    gotoxy(5,13); cout << str;
}
void item(){
    int Maidenkiss = 4;
    int Phoenixdown = 4;
    int Remedy = 3;
    int vitriy = 12, vitrix = 8;
    int Toado = 11, Chon = 0;   
   
    while(Maidenkiss > 0){
    gotoxy(6,11); cout << "                               ";
    gotoxy(8,11); cout << "*Maidenkiss: " << Maidenkiss;
    gotoxy(5,11); cout << "-->";
    gotoxy(8,13); cout << "*Phoenixdown: " << Phoenixdown;
    gotoxy(8,15); cout << "*Remedy: " << Remedy;    
    do{        
        char c = getch();
        if(c == 'w' || c == 72 || c == 'W') Chon = 1;
                else if(c == 's' || c == 'S' || c == 80) Chon = 2;
                    else if(c == 13) Chon = 3;
                        else Chon = 0;
        
        if(Toado > 11 && Toado <= 15 && Chon == 1) Toado -= 2;
            else if(Toado >= 11 && Toado < 15 && Chon == 2) Toado += 2;

        switch(Toado)
        {
            case 11:
                gotoxy(8,11); cout << "*Maidenkiss: " << Maidenkiss;
                gotoxy(5,11); cout << "-->";
                gotoxy(5,13); cout << "   ";
                gotoxy(8,13); cout << "*Phoenixdown: " << Phoenixdown;
                gotoxy(5,15); cout << "   ";
                gotoxy(8,15); cout << "*Remedy: " << Remedy;
            
            
            break;

            case 13:
                gotoxy(5,11); cout << "   ";
                gotoxy(8,11); cout << "*Maidenkiss: " << Maidenkiss;                
                gotoxy(8,13); cout << "*Phoenixdown: " << Phoenixdown;
                gotoxy(5,13); cout << "-->";
                gotoxy(5,15); cout << "   ";
                gotoxy(8,15); cout << "*Remedy: " << Remedy;
            break;

            case 15:
                gotoxy(5,11); cout << "   ";
                gotoxy(8,11); cout << "*Maidenkiss: " << Maidenkiss;
                gotoxy(5,13); cout << "   ";
                gotoxy(8,13); cout << "*Phoenixdown: " << Phoenixdown;
                gotoxy(5,15); cout << "-->";
                gotoxy(8,15); cout << "*Remedy: " << Remedy;
            break;
        }     
    } while(Chon != 3);
    switch (Toado){
        case 11:
            vekhung();
            Maidenkiss--;
            gotoxy(6, 11); cout << "Bạn vừa dùng Maidenkiss";
        break;

        case 13:
            vekhung();
            Phoenixdown--;
            gotoxy(6, 11); cout << "Bạn vừa dùng Phoenixdown";
        break;

        case 15:
            vekhung();
            Remedy--;
            gotoxy(6, 11); cout << "Bạn vừa dùng Remedy";
        break;

    }
    
    cin.ignore();
    }   
}
void Model(string type){
    if(type == "HiepSi"){
        gotoxy(X, 2 + Y); cout << "   ~~O      /|" << endl;
        gotoxy(X, 3 + Y); cout << "    _|_    // " << endl;
        gotoxy(X, 4 + Y); cout << "   |'_'| _//_ " << endl;
        gotoxy(X, 5 + Y); cout << "===|||===//   " << endl;
        gotoxy(X, 6 + Y); cout << "   |||        " << endl;
        gotoxy(X, 7 + Y); cout << "  // \\\\       " << endl;
    }
    if(type == "QuaiVat"){
        gotoxy(50, 3); cout << " oo`'._..---.___.." << endl;
        gotoxy(50, 4); cout << "(_,-.        ,..'`" << endl;
        gotoxy(50, 5); cout << "   `'.      ;     " << endl;
        gotoxy(50, 6); cout << "       :--:`     " << endl;
        gotoxy(50, 7); cout << "      _; _;      " << endl;
    }
    if(type == "NPC"){
        gotoxy(50, 2); cout << "        ,\\        " << endl;
        gotoxy(50, 3); cout << "      __/_\\__     " << endl;
        gotoxy(50, 4); cout << "     , ((\")\\//  " << endl;
        gotoxy(50, 5); cout << "      \\_/ \\_|     " << endl;
        gotoxy(50, 6); cout << "       /___\\|     " << endl;
        gotoxy(50, 7); cout << "       _/ |_|     " << endl;
    }
    if(type == "Ech"){
        gotoxy(X, 2); cout << "   (o)--(o) " << endl;
        gotoxy(X, 3); cout << "  /.______.\\" << endl;
        gotoxy(X, 4); cout << "  \\________/" << endl;
        gotoxy(X, 5); cout << " ./        \\." << endl;
        gotoxy(X, 6); cout << "( .        , )" << endl;
        gotoxy(X, 7); cout << " \\ \\_\\//_/ /" << endl;
        gotoxy(X, 8); cout << "  ~~  ~~  ~~ " << endl;
    }
    if(type == "TiHon"){
        gotoxy(X, 2); cout << "              " << endl;
        gotoxy(X, 3); cout << "              " << endl;
        gotoxy(X, 4); cout << "              " << endl;
        gotoxy(X, 5); cout << "              " << endl;
        gotoxy(X, 6); cout << "              " << endl;
        gotoxy(X, 7); cout << "              " << endl;
        gotoxy(X, 5); cout << "    O" << endl;
        gotoxy(X, 6); cout << " --[|]--" << endl;
        gotoxy(X, 7); cout << "   / \\ " << endl;
    }
}
void intro(string &name){
    system("cls");        
    for(int i = 0; i <= 47; i++){
        gotoxy(i,2);  cout << ",--.   ,--.,------.,--.    ,-----. ,-----. ,--.   ,--.,------.    ";    
        gotoxy(i,3);  cout << "|  |   |  ||  .---'|  |   '  .--./'  .-.  '|   `.'   ||  .---'    " ;  
        gotoxy(i,4);  cout << "|  |.'.|  ||  `--, |  |   |  |    |  | |  ||  |'.'|  ||  `--,     " ;  
        gotoxy(i,5);  cout << "|   ,'.   ||  `---.|  '--.'  '--' '  '-'  '|  |   |  ||  `---.,--." ;  
        gotoxy(i,6);  cout << "'--'   '--'`------'`-----' `-----' `-----' `--'   `--'`------''-,/" ;  
    
                                                                           
              
        Sleep(15);
            if( i == 47) continue;    
                system("cls");
    }
        for(int j = 94; j >= 47; j--){
            gotoxy(47,2);  cout << ",--.   ,--.,------.,--.    ,-----. ,-----. ,--.   ,--.,------.    ";    
            gotoxy(47,3);  cout << "|  |   |  ||  .---'|  |   '  .--./'  .-.  '|   `.'   ||  .---'    " ;  
            gotoxy(47,4);  cout << "|  |.'.|  ||  `--, |  |   |  |    |  | |  ||  |'.'|  ||  `--,     " ;  
            gotoxy(47,5);  cout << "|   ,'.   ||  `---.|  '--.'  '--' '  '-'  '|  |   |  ||  `---.,--." ;  
            gotoxy(47,6);  cout << "'--'   '--'`------'`-----' `-----' `-----' `--'   `--'`------''-,/" ;  
            
            gotoxy(j,8);   cout << "                                                         ,---.   ";     
            gotoxy(j,9);   cout << "    ,--. ,--.,--.  ,--.,--. ,----.   ,--.  ,--.,--------.|   |   ";
            gotoxy(j,10);  cout << "    |  .'   /|  ,'.|  ||  |'  .-./   |  '--'  |'--.  .--'|  .'   ";
            gotoxy(j,11);  cout << "    |  .   ' |  |' '  ||  ||  | .---.|  .--.  |   |  |   |  |    ";
            gotoxy(j,12);  cout << "    |  |\\   \\|  | `   ||  |'  '--'  ||  |  |  |   |  |   `--'  ";
            gotoxy(j,13);  cout << "    `--' '--'`--'  `--'`--' `------' `--'  `--'   `--'   .--.    ";   
            gotoxy(j,14);  cout << "                                                         '--'    "; 
             Sleep(15);
        if(j == 47) continue;    


            system("cls");

        };
        gotoxy(65, 16); cout << "Press any key to continue!";
            getch();
        
        system("cls");
        cout << "NAME OF THE FAILURE: ";
        getline(cin, name);
        system("cls");  cout << "Please wait..."; Sleep(2000); system("cls");
        HoiThoai(3, 1, "This is you");
        Model("HiepSi"); gotoxy(6, 9+ Y); cout << name;;  Sleep(500); 
        getch();
        HoiThoai(20, 5, "<----- a failure");
        Sleep(1000); system("cls");
        Model("HiepSi"); 
        HoiThoai(7, 9+Y, name); 
        HoiThoai(20, 5, "<---- The princess was kidnapped by Bowser.");
        HoiThoai(20, 7, "<---- and your duty is defeat Bowser and save the princess, that's all.");
        HoiThoai(20, 9, "<---- Got it?");
    TextColor(224);
    gotoxy(SCREEN_W/2 - 4 - 3, 11); cout << "YES";
    TextColor(14);
    gotoxy(SCREEN_W/2 + 4 + 3, 11); cout << "NO";
    int choice = 0;int toado = 0;
    do{
        
        char c = getch();
        if(c == 'a' || c == 'A') choice = 1;
        else if(c == 'd' || c == 'D') choice = 2;
        else if(c == 13) choice = 3;
        else choice = 0;
        if(choice == 1 && toado > 0) toado -= 14;
        else if(choice == 2 && toado < 14) toado += 14;
    
        switch(toado){
            case 0:
                TextColor(224);
                gotoxy(SCREEN_W/2 - 4 - 3, 11); cout << "YES";
                TextColor(14);
                gotoxy(SCREEN_W/2 + 4 + 3, 11); cout << "NO";
                break;

            case 14:
                TextColor(14);
                gotoxy(SCREEN_W/2 - 4 - 3, 11); cout << "YES";
                TextColor(224);
                gotoxy(SCREEN_W/2 + 4 + 3, 11); cout << "NO";
                TextColor(14);
                break;

            default:    
                break;
        }
    } while(choice != 3);
    switch(toado){
        case 0:
            system("cls");
            cout << "KO biet lam gi";
            break;

        case 14:
            system("cls");
            cout << "het game:)";
            break;
    }
}
/*
int main(){
    string name;
    intro(name);
    
    
     
}   
 
  _(    )
 (___(__)
       ___
     

  __
 |:3|
  \/      
      /__\__  //
    //_____\///
   _| /-_-\)|/_
  (___\ _ //___\
  (  |\\_/// * \\
   \_| \_((*   *))
  // ( |__|_\\  */
 //  (o/  _  \_*_/
   //\__|__/\
  // |  | |  |
 //  _\ | |___)
 /*cout << "//  (___|        ";
         ___..._
    _,--'       "`-.
  ,'.  .            \
,/:. .     .       .'
|;..  .      _..--'
`--:...-,-'""\
        |:.  `.
        l;.   l
        `|:.   |
        vvv |:.   `.,
        .l;.    j, ,
     `. \`;:.   //,/
      .\\)`;,|\'/(
       ` `itz `(,
}       
        ____,
       /.---|
       `    |     ___
           (=\.  /-. \
            |\/\_|"|  |
            |_\ |;-|  ;
            | / \| |_/ \
            | )/\/      \
            | ( '|  \   |
            |    \_ /   \
            |    /  \_.--\
            \    |    (|\`
             |   |     \
             |   |      '.
             |  /         \
       jgs   \  \.__.__.-._)
          .--.
         /..  \     
         \ O  /    
         /    \    
        /      \
       (/      \)      
        |      \        
         \      '._     
          '._      '-.   
             `'- ,~- _.`  
   jgs                 
*/    
/*            _,._      
  .||,       /_ _\\     
 \.`',/      |'L'| |    
 = ,. =      | -,| L    
 / || \    ,-'\"/,'`.   
   ||     ,'   `,,. `.  
   ,|____,' , ,;' \| |  
  (3|\    _/|/'   _| |  
   ||/,-''  | >-'' _,\\ 
   ||'      ==\ ,-'  ,' 
   ||       |  V \ ,|   
   ||       |    |` |   
   ||       |    |   \  
   ||       |    \    \ 
   ||       |     |    \
   ||       |      \_,-'
   ||       |___,,--")_\
   ||         |_|   ccc/
   ||        ccc/       
   ||                hjm*/
/*
   ,\
 __/_\__ 
, ((")\\//
 \_/ \_|
  /___\|
  _/ |_|

*/
  /*                                                                  
,--.   ,--.,------.,--.    ,-----. ,-----. ,--.   ,--.,------.    
|  |   |  ||  .---'|  |   '  .--./'  .-.  '|   `.'   ||  .---'    
|  |.'.|  ||  `--, |  |   |  |    |  | |  ||  |'.'|  ||  `--,     
|   ,'.   ||  `---.|  '--.'  '--'\'  '-'  '|  |   |  ||  `---.,--. 
'--'   '--'`------'`-----' `-----' `-----' `--'   `--'`------''-,/
                                                                      
                                                         ,---.        
    ,--. ,--.,--.  ,--.,--. ,----.   ,--.  ,--.,--------.|   |    
    |  .'   /|  ,'.|  ||  |'  .-./   |  '--'  |'--.  .--'|  .'    
    |  .   ' |  |' '  ||  ||  | .---.|  .--.  |   |  |   |  |     
    |  |\   \|  | `   ||  |'  '--'  ||  |  |  |   |  |   `--'     
    `--' '--'`--'  `--'`--' `------' `--'  `--'   `--'   .--.         
                                                         '--'     
                                            ⢀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠖⠋⠉⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢸⣿⠛⠲⠦⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⢋⣤⣂⣀⢸⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣰⠃⠀⢀⣀⡀⠈⠛⠦⣀⠀⠀⢀⣀⡤⠤⠀⠀⠐⠈⠛⠛⠛⠒⠺⠧⢾⣉⠉⠶⣏⠈⢻⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⡿⠀⢀⣴⡋⠉⠓⣄⠀⠈⠓⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⠪⣝⡛⢥⡀⣸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢰⡇⠀⢀⣼⣛⣠⠴⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠢⠉⠳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢸⡇⠀⠈⣹⠋⠁⢠⡇⠂⠀⠀⠀⠀⠰⣤⡀⠀⠀⠀⠀⠀⠀⠀⣀⡄⠀⠀⠀⠀⠀⠈⠂⠀⠈⠳⣄⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣧⢀⡞⠁⠲⠚⠁⠀⠀⠀⣰⢿⠈⣇⢿⠱⣄⠠⠔⡒⠀⠉⠁⠀⠱⡀⠀⠀⠀⢀⠄⠀⠑⢦⡹⡙⣆⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠹⡾⠀⠀⠀⠀⠀⠀⣠⠞⢁⡟⠀⡿⡞⡆⠘⢦⠀⢸⡀⠀⠀⠀⠀⢷⣆⢀⡴⣿⡀⠀⠀⠀⠁⢳⡘⣆⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣸⠃⠀⠀⠀⠀⢀⠴⠁⠀⣸⠧⣰⡇⣇⡇⠀⠘⣇⠈⣇⠀⠀⠀⠀⣿⣿⡇⠀⡿⣧⢢⠀⠀⠀⠈⢧⢹⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⡿⠀⠀⠀⠀⢰⠇⠀⠀⣠⠏⠀⡼⢳⣿⡀⠀⠀⠸⣾⢿⡄⣀⣀⣴⢏⣽⣧⣴⣃⢸⡞⠀⠀⠀⠀⢸⣼⠃⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢀⡇⠀⠀⠀⠀⣼⠀⠀⣰⠏⣠⣞⣥⡿⠷⠮⣇⠀⠀⠟⠀⠛⠁⠈⢿⢟⢵⡶⢮⡙⢿⣷⠀⠀⠀⠀⣼⡿⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠐⡇⠀⠀⠀⣰⠃⢀⡼⡿⢛⣿⠟⣱⢶⡟⠙⣶⡀⠀⠀⠀⠀⠀⠀⠀⣿⢼⡇⠈⢳⠀⢻⡄⠀⠀⣰⠇⠁⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢸⡇⠀⠀⣰⣣⢶⠋⢸⠁⣿⠃⢠⡷⠊⠀⢀⠘⢿⠀⠀⠀⠀⠀⠀⠀⣿⡈⠳⠃⢸⠃⠀⣧⠀⠈⠓⠦⡀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢸⠃⠀⠀⠉⠀⢸⡀⠿⠛⣏⠀⠈⣷⠀⠙⠉⢀⡾⠀⠀⠀⠀⠀⠀⠀⠈⠳⠤⠴⠋⣀⣀⡈⢳⡀⠀⠀⢹⡄⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⣸⠆⠀⠀⠀⠀⠈⣇⠀⠀⠈⢧⠀⣈⡛⡒⡚⡋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⢣⣿⣿⣹⠀⢳⠀⠀⢸⡇⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢰⠇⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⢸⣞⡟⡴⡿⡽⠁⣲⣤⡤⠤⠖⠚⠛⠓⠒⢾⢿⡇⠃⠉⠑⠃⠀⣼⠃⠀⢸⡀⠀⢰⡀⠀⠀
⠀⠀⠀⢀⡇⠀⠀⠀⠀⠀⠀⠀⡼⠀⠀⠀⢸⠋⠘⠀⠁⠀⢠⡇⠈⠀⠀⠀⠀⠀⠀⠀⠉⣾⠀⠀⠀⠀⠀⣰⠃⠀⣀⠈⠓⣶⡿⠀⠀⠀
⠀⠀⠀⡼⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠠⡄⠸⣆⣀⣠⠄⠀⠀⣇⠀⠀⠀⠀⠀⠀⠀⠀⣰⠇⠀⠀⢀⣠⠞⠁⠀⠀⠉⢋⡿⠉⠀⠀⠀⠀
⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⢳⡀⠀⡉⠒⣮⣽⣋⠀⠀⠀⠘⢦⣀⡀⠀⢀⣀⣤⠞⢁⣀⣤⠔⠋⠁⠀⢀⣀⣠⠶⡏⠀⠀⠀⠀⠀⠀
⠀⠀⠀⢷⠀⠀⣀⠀⠀⠀⠀⠀⠀⠳⢤⣈⣙⣫⣭⣿⣽⠶⣦⣀⢀⣈⢉⣿⠿⣷⢶⣯⣍⠀⠀⠀⠀⠀⠀⡸⠃⠁⢸⠇⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠈⠀⠀⠈⠲⠤⢄⡀⡀⠀⠀⠀⠀⣴⠏⠁⠀⢷⠀⢿⢿⣿⣾⣿⣧⠀⠈⢳⡀⠙⣧⣀⣀⣠⠴⠋⠀⠀⠀⣸⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠓⠉⠙⢒⡾⣏⣀⠀⠀⠘⡆⢼⣿⢋⠹⣿⣿⠀⠀⠀⣷⣠⠼⠙⢇⠀⠀⠀⠀⠀⢠⡇⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠈⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠈⠉⠉⠉⠁⠈⠈⠈⠈⠈⠈⠀⠀⠀⠉⠀⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀*/
/* (o)--(o)
  /.______.\
  \________/
 ./        \.
( .        , )
 \ \_\\//_/ /
  ~~  ~~  ~~ */
  /*
   .---.     ,------. ,--------.     .---.
  /  _  \   '  .---./ '--.  .--'    /_   |
 /  /_\  \  |  |         |  |         |  |
/  /   \  \ |  '---'\    |  |         |  |
'-'     '-'  `------'    `--'         |__|
,--.   ,--.,------.,--.    ,-----. ,-----. ,--.   ,--.,------.    
|  |   |  ||  .---'|  |   '  .--./'  .-.  '|   `.'   ||  .---'    
|  |.'.|  ||  `--, |  |   |  |    |  | |  ||  |'.'|  ||  `--,     
|   ,'.   ||  `---.|  '--.'  '--'\'  '-'  '|  |   |  ||  `---.,--. 
'--'   '--'`------'`-----' `-----' `-----' `--'   `--'`------'
  */