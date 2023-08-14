#include "test4.cpp"

#define SCREEN_W_CONSOLE 110
#define SCREEN_H_CONSOLE 3
void act1(){
    system("cls");
    TextColor(14);
    Sleep(1000); 

    gotoxy(SCREEN_W_CONSOLE/2 - 21, SCREEN_H_CONSOLE);   cout << "   .---.     ,------. ,--------.     .---."; Sleep(50);
    gotoxy(SCREEN_W_CONSOLE/2 - 21, SCREEN_H_CONSOLE+1); cout << "  /  _  \\   '  .---./ '--.  .--'    /_   |"; Sleep(50);
    gotoxy(SCREEN_W_CONSOLE/2 - 21, SCREEN_H_CONSOLE+2); cout << " /  /_\\  \\  |  |         |  |         |  |"; Sleep(50);
    gotoxy(SCREEN_W_CONSOLE/2 - 21, SCREEN_H_CONSOLE+3); cout << "/  /   \\  \\ |  '---'\\    |  |         |  |"; Sleep(50);
    gotoxy(SCREEN_W_CONSOLE/2 - 21, SCREEN_H_CONSOLE+4); cout << "'-'     '-'  `------'    `--'         |__|";

    HoiThoai(SCREEN_W_CONSOLE/2 - 12, SCREEN_H_CONSOLE+7,"THE WHISPERING FOREST"); Sleep(1000);

    system("cls");

    Model("HiepSi"); HoiThoai(20, 5,  "<---- To reach the Bowser's Castle, you have to explore the Whispering Forest"); Sleep(50);
    HoiThoai(20, 7, "<--- This place is filled with dangerous, also countless treasures");  Sleep(50);
    HoiThoai(20, 9
    , "<--- Good luck!");





}


int main(){
    string s;
    setcursor(0,0);
    act1();
    getch();
}
/*
   .---.     ,------. ,--------.     .---.
  /  _  \   '  .---./ '--.  .--'    /_   |
 /  /_\  \  |  |         |  |         |  |
/  /   \  \ |  '---'\    |  |         |  |
'-'     '-'  `------'    `--'         |__|

*/