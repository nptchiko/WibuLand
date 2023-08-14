#include <windows.h>
#include <iostream>
#include <direct.h>
#include <time.h>
#include <conio.h>
#include <fstream>

using namespace std;

#define X 4
#define Y 2
#define SCREEN_W 72
#define SCREEN_H 24

#define NUM 4

#define Model_X_Length 1
#define Model_Y_Length 1

char Model_Bullet[Model_Y_Length][Model_X_Length] = {{'v'}};

const char *Event_Name[] = {"", "MadBear", "Bandit", "LordLupin", "Elf", "Troll",
                             "Shaman", "Siren_Vajsh", "MushMario", "MushFibo", "MushGhost",
                             "Remedy", "MaidenKiss", "PhoenixDown", "Asclepius", "Merlin", "Bowser"};

void gotoxy(short x, short y){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y}; SetConsoleCursorPosition(h, a);
}
void TextColor(int x){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x); 
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(h,&lpCursor);
}
class Attribute{
    public:
        string name;
        int MaxHP;
        int HP;
        float Atk;
        int level;
        bool turn;
        string infor;
    
    Attribute(){};
    Attribute(string name,int MaxHP, int HP, float Atk, int level, bool turn){
        this->MaxHP = HP;
        this->name = name;
        this->HP = HP;
        this->Atk = Atk;
        this->level = level;
        this->turn = turn;
    }
};
class Knight : public Attribute{
    private:      
        int Thu_Nho;
        int Trung_Doc;
        int Thanh_Frog;
        int Temp_value;
        string status;
    public: 
        bool have_debuff;

        Knight(){}
        Knight(string name,int MaxHP, int HP, float Atk, int level, bool turn) : Attribute(name, MaxHP, HP, Atk, level, turn){
            this->Trung_Doc = 0;
            this->Thanh_Frog = 0;
            this->Thu_Nho = 0;
            this->Temp_value = 0;
            this->have_debuff = false;
            this->status = "Bình thường";
        }
        void Poisened(){
            if(this->Trung_Doc == 0){
                
                this->Trung_Doc = 3;
                this->Thanh_Frog = 0;
                this->Thu_Nho = 0;
                this->have_debuff = true;  
                this->status = "Trúng độc";
            }
        }
        void Frog(){
            if(this->Thanh_Frog == 0){
                
                this->Trung_Doc = 0;
                this->Thanh_Frog = 3;
                this->Thu_Nho = 0;

                this->Temp_value = this->level;
                this->level = 1;
                this->have_debuff = true;  
                this->status = "Ếch";
            } 
        }
        void Smallen(){
            if(this->Thu_Nho == 0){
                
                this->Trung_Doc = 0;
                this->Thanh_Frog = 0;
                this->Thu_Nho = 3;

                this->Temp_value = this->HP;
                if(this->HP <= 5) this->HP = 1;
                else this->HP /= 5;  
                this->have_debuff = true;  
                this->status = "Tí hon";
            } 
        }
        string getStatus(){
            return status;
        }
        void Status(int &remedy, int& maidenkiss, int &phoenixdown){
            if(this->Trung_Doc > 0 ){
                if(phoenixdown){
                    phoenixdown--;  
                    this->Trung_Doc = 0;
                    this->have_debuff = false;                  
                } 
                if(this->Trung_Doc > 1) this->Trung_Doc--;
                else {
                    this->Thanh_Frog--;
                    this->have_debuff = false;  
                    this->status = "Bình thường";
                }
            }    
            
         else  if(this->Thanh_Frog > 0){
                if(maidenkiss){
                      maidenkiss--;
                    this->Thanh_Frog = 0;
                    this->level = this->Temp_value;   
                    this->have_debuff = false;                        

                }
                if(this->Thanh_Frog > 1) this->Thanh_Frog--;
                else {
                    this->Thanh_Frog--;
                    this->level = this->Temp_value;
                    this->have_debuff = false; 
                    this->status = "Bình thường"; 
                }
                
            }

          else  if(this->Thu_Nho > 0){
                if(remedy){
                      remedy--;
                    this->Thu_Nho = 0;  
                    this->HP *= 5; 
                    this->have_debuff = false;                           
                }
                if(this->Thu_Nho > 1) this->Thu_Nho--;
                else {
                    this->Thu_Nho--;
                    this->HP *= 5; 
                    this->have_debuff = false;  
                    this->status = "Bình thường";
                }               
            }
        }
};

class Monster : public Attribute{
    private:
        int skill_cooldown;
    public:
        Monster(){};
        ~Monster(){};
        Monster(string name,int MaxHP, int HP, float Atk, int level, bool turn, string infor) : Attribute(name, MaxHP, HP, Atk, level, turn){
            this->infor = infor;
            this->skill_cooldown = 0;
        }
        Monster* monster(string name,int MaxHP, int HP, float Atk, int level){
            Monster* mons = new Monster();
                mons->name = name;
                mons->MaxHP = MaxHP;
                mons->HP = HP;
                mons->Atk = Atk;
                mons->level = level;

            return mons;
        }
        void Skill(int event, Knight &knight){
            if(this->skill_cooldown == 0){
                this->skill_cooldown = 3;
                switch (event){
                    case 6:
                        
                        knight.Frog();
                        
                    break;

                    case 7:
                        knight.Smallen();
                        

                    break;
                }
            } else this->skill_cooldown--;
        }

};
class Object {
     public:   
        int x = 0;
        int y = 0;
    virtual void draw(){};
    virtual void erase(){};
    virtual void gen(){};
};
class Character : public Object {
    private:
        char model1[2][4] = {{' ','_','_',' '},
                             {'|',':','3','|'}};
    
    public:
        Character(){
            this->x = SCREEN_W/2;
            this->y = SCREEN_H/2 + 4;
        };

        void draw(){
            for(int i = 0; i < 2; i++){
               for(int j = 0; j < 4; j++){
                
                    gotoxy(this->x + j, this->y + i); cout << model1[i][j];
                
                }
               
                cout << endl;
           }
        }

        void erase(){
            for(int i = 0; i < 2; i++){
                for(int j = 0; j < 4; j++){
                     gotoxy(this->x + j, this->y + i); cout << " ";
                }
                cout << endl;
            }
        }

};
class Bullet : public Object {
   private:
        char (*model)[Model_X_Length];
   public:
        
        bool ready = 0;
        int damage = 0;
        
        void Modify(char (*c)[Model_X_Length]){
            this->model = c;
        }

        void draw(){
            if(this->ready == 1){
                for(int i = 0; i < Model_Y_Length; i++){
                    for(int j = 0; j < Model_X_Length; j++){
                        gotoxy(this->x+j, this->y+i); cout << model[i][j];
                    }
                }    
            }
        }

        void erase(){
                for(int i = 0; i < Model_Y_Length; i++){    
                    for(int j = 0; j < Model_X_Length; j++){
                        gotoxy(this->x+j, this->y+i); cout << " ";
                    }
                }
        }

        void gen(){
            this->x = SCREEN_W/2 - 15 + rand()%31;
        }

        void reset(){
            this->erase();
            this->ready = 0;
            this->y = SCREEN_H/2 - 7;
            this->gen();
        }

};


void collision(int i, Bullet* bullet, Character* Char, Knight &Knight){
    
    if((bullet+i)->y + 1 >= Char->y){
        if((bullet+i)->x - Char->x >= 0 && (bullet+i)->x - Char->x <= 4){
            Knight.HP -= (bullet+i)->damage;
            (bullet+i)->reset();
        }

    }
}
void intro(){
    string s;
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

        }
        gotoxy(65, 16); cout << "Press any key to continue!";
            cin.ignore();
                system("cls");
        cout << "NAME OF THE FAILURE: ";
        getline(cin, s);
        system("cls");
        cout << "Please wait..";
        Sleep(1000);
        
}
void Model(string type){
    if(type == "HiepSi"){
        gotoxy(4, 2); cout << "   ~~O      /|" << endl;
        gotoxy(4, 3); cout << "    _|_    // " << endl;
        gotoxy(4, 4); cout << "   |'_'| _//_ " << endl;
        gotoxy(4, 5); cout << "===|||===//   " << endl;
        gotoxy(4, 6); cout << "   |||        " << endl;
        gotoxy(4, 7); cout << "  // \\\\       " << endl;
    }
    if(type == "Monster"){
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
    if(type == "Frog"){
        gotoxy(4, 2); cout << "   (o)--(o) " << endl;
        gotoxy(4, 3); cout << "  /.______.\\" << endl;
        gotoxy(4, 4); cout << "  \\________/" << endl;
        gotoxy(4, 5); cout << " ./        \\." << endl;
        gotoxy(4, 6); cout << "( .        , )" << endl;
        gotoxy(4, 7); cout << " \\ \\_\\//_/ /" << endl;
        gotoxy(4, 8); cout << "  ~~  ~~  ~~ " << endl;
    }
    if(type == "Tiny"){
        gotoxy(4, 2); cout << "              " << endl;
        gotoxy(4, 3); cout << "              " << endl;
        gotoxy(4, 4); cout << "              " << endl;
        gotoxy(4, 5); cout << "              " << endl;
        gotoxy(4, 6); cout << "              " << endl;
        gotoxy(4, 7); cout << "              " << endl;
        gotoxy(4, 5); cout << "    O" << endl;
        gotoxy(4, 6); cout << " --[|]--" << endl;
        gotoxy(4, 7); cout << "   / \\ " << endl;
    }
};
void Xu_li(int &toa_do){
    for(int i = 1; i <= 71; i++){
            gotoxy(i, 20); cout << "_";
    }
    TextColor(224);
        
            gotoxy(0, 21);  cout << "|                 ";
            gotoxy(0, 22);  cout << "|      FIGHT      ";
            gotoxy(0, 23);  cout << "|_________________";
            
            TextColor(14);
            gotoxy(18, 21); cout << "|                 ";
            gotoxy(18, 22); cout << "|      CHECK      ";
            gotoxy(18, 23); cout << "|_________________";
            
            
            gotoxy(36, 21); cout << "|                 ";
            gotoxy(36, 22); cout << "|      ITEM       ";
            gotoxy(36, 23); cout << "|_________________";

            gotoxy(54, 21); cout << "|                 |";
            gotoxy(54, 22); cout << "|      FLEE       |";
            gotoxy(54, 23); cout << "|_________________|";
        
    
    int chon = 0;
    int toado = 0;
    do{
        char a = getch();
        if(a == 77 ||a == 'd'||a=='D'||a=='6') chon = 1;
        else if(a == 75 || a == 'a'||a=='A'||a =='4') chon = 2;
        else if(a == 13 || a== '5') chon = 3;
        else chon = 0;
        if(chon == 1 && toado < 45) toado += 15;
        else if(chon == 2 && toado >= 15) toado += 15;
      if(toado == 0)
        {
            
            TextColor(224);
            gotoxy(0, 21);  cout << "|                 ";
            gotoxy(0, 22);  cout << "|      FIGHT      ";
            gotoxy(0, 23);  cout << "|_________________";
            
            TextColor(14);
            gotoxy(18, 21); cout << "|                 ";
            gotoxy(18, 22); cout << "|      CHECK      ";
            gotoxy(18, 23); cout << "|_________________";
            
            
            gotoxy(36, 21); cout << "|                 ";
            gotoxy(36, 22); cout << "|      ITEM       ";
            gotoxy(36, 23); cout << "|_________________";

            gotoxy(54, 21); cout << "|                 |";
            gotoxy(54, 22); cout << "|      FLEE       |";
            gotoxy(54, 23); cout << "|_________________|";
            
            TextColor(7);
        }
      if(toado == 15)
        {
            
            TextColor(14);
            gotoxy(0, 21);  cout << "|                 ";
            gotoxy(0, 22);  cout << "|      FIGHT      ";
            gotoxy(0, 23);  cout << "|_________________";
            
            TextColor(224);
            gotoxy(18, 21); cout << "|                 ";
            gotoxy(18, 22); cout << "|      CHECK      ";
            gotoxy(18, 23); cout << "|_________________";
              
            TextColor(14);
            
            gotoxy(36, 21); cout << "|                 ";
            gotoxy(36, 22); cout << "|      ITEM       ";
            gotoxy(36, 23); cout << "|_________________";

            gotoxy(54, 21); cout << "|                 |";
            gotoxy(54, 22); cout << "|      FLEE       |";
            gotoxy(54, 23); cout << "|_________________|";
            
            TextColor(7);
        }
        if(toado == 30)
        {
            
            TextColor(14);
            gotoxy(0, 21);  cout << "|                 ";
            gotoxy(0, 22);  cout << "|      FIGHT      ";
            gotoxy(0, 23);  cout << "|_________________";
            
            
            gotoxy(18, 21); cout << "|                 ";
            gotoxy(18, 22); cout << "|      CHECK      ";
            gotoxy(18, 23); cout << "|_________________";
              
            
            TextColor(224);
            gotoxy(36, 21); cout << "|                 ";
            gotoxy(36, 22); cout << "|      ITEM       ";
            gotoxy(36, 23); cout << "|_________________";
            TextColor(14);

            gotoxy(54, 21); cout << "|                 |";
            gotoxy(54, 22); cout << "|      FLEE       |";
            gotoxy(54, 23); cout << "|_________________|";
            
            
            TextColor(7);
        }
        if(toado == 45)
        {
            
            TextColor(14);
            gotoxy(0, 21);  cout << "|                 ";
            gotoxy(0, 22);  cout << "|      FIGHT      ";
            gotoxy(0, 23);  cout << "|_________________";
            
           
            gotoxy(18, 21); cout << "|                 ";
            gotoxy(18, 22); cout << "|      CHECK      ";
            gotoxy(18, 23); cout << "|_________________";
              
            
            gotoxy(36, 21); cout << "|                 ";
            gotoxy(36, 22); cout << "|      ITEM       ";
            gotoxy(36, 23); cout << "|_________________";
            TextColor(224);
            gotoxy(54, 21); cout << "|                 |";
            gotoxy(54, 22); cout << "|      FLEE       |";
            gotoxy(54, 23); cout << "|_________________|";
            
            TextColor(7);
        }
            
        
} while(chon != 3);
    toa_do = toado;
    cout << endl;
}
void animation1(int dmg, int Case, bool Mons){
   
    switch (Case){
        case 1: 
            system("cls");
            TextColor(14);
            for(int i = 4; i <= 36; i++){
                gotoxy(i, 2); cout << "   ~~O      /|" << endl;
                gotoxy(i, 3); cout << "    _|_    // " << endl;
                gotoxy(i, 4); cout << "   |'_'| _//_ " << endl;
                gotoxy(i, 5); cout << "===|||===//   " << endl;
                gotoxy(i, 6); cout << "   |||        " << endl;
                gotoxy(i, 7); cout << "  // \\\\       " << endl;        
                
                Model("Monster");
                
                Sleep(18);
                system("cls");
                
                if(i == 36){
                    for(int j = 36; j >= 4;  j--){
                            if(j >= 26){
                                gotoxy(45, 6); cout << dmg;
                            }

                            gotoxy(j, 2); cout << "   ~~O      /|" << endl;
                            gotoxy(j, 3); cout << "    _|_    // " << endl;
                            gotoxy(j, 4); cout << "   |'_'| _//_ " << endl;
                            gotoxy(j, 5); cout << "===|||===//   " << endl;
                            gotoxy(j, 6); cout << "   |||        " << endl;
                            gotoxy(j, 7); cout << "  // \\\\       " << endl;        
                            
                            Model("Monster");
                            Sleep(18);
                            system("cls");
                    }
                }
            } 
        break;

        case 0:
            system("cls");
            TextColor(14);
            for(int i = 4; i >= 0; i--){
                gotoxy(i, 2); cout << "   ~~O      /|" << endl;
                gotoxy(i, 3); cout << "    _|_    // " << endl;
                gotoxy(i, 4); cout << "   |'_'| _//_ " << endl;
                gotoxy(i, 5); cout << "===|||===//   " << endl;
                gotoxy(i, 6); cout << "   |||        " << endl;
                gotoxy(i, 7); cout << "  // \\\\       " << endl;        
                if(Mons){
                      Model("Monster");
                } else {
                      Model("NPC");
                }
                Sleep(18);
                system("cls");
            }
        break;    
    }    
}
void animation2(int dmg){    
    system("cls");
    TextColor(14);
    for(int i = 50; i >= 18; i--){
        Model("HiepSi");

        gotoxy(i, 3); cout << " oo`'._..---.___.." << endl;
        gotoxy(i, 4); cout << "(_,-.        ,..'`" << endl;
        gotoxy(i, 5); cout << "   `'.      ;     " << endl;
        gotoxy(i, 6); cout << "       :--:`     " << endl;
        gotoxy(i, 7); cout << "      _; _;      " << endl;

        Sleep(18);
        system("cls");
        
      if(i == 18){
            for(int j = 18; j <= 50; j++){
               if(j <= 28){
                    gotoxy(19, 5); cout << dmg;
                }
                Model("HiepSi");

                gotoxy(j, 3); cout << " oo`'._..---.___.." << endl;
                gotoxy(j, 4); cout << "(_,-.        ,..'`" << endl;
                gotoxy(j, 5); cout << "   `'.      ;     " << endl;
                gotoxy(j, 6); cout << "       :--:`     " << endl;
                gotoxy(j, 7); cout << "      _; _;      " << endl;

                Sleep(18);
                system("cls");
            }
        }
    }
}         
void play(Bullet* bullet, Character* char_, Knight knight, Monster* monster){
    
    int count = 50;

    int damage = monster->level*monster->Atk;

    (bullet)->ready = 1;

    char_->x = SCREEN_W/2;
    char_->y = SCREEN_H/2 + 4;

    for(int i = 1; i < NUM; i++)
        (bullet+i)->ready = 0;

    for(int i = 0; i < NUM; i++){
        (bullet+i)->y = SCREEN_H/2 - 7;
        (bullet+i)->gen();
        (bullet+i)->Modify(Model_Bullet);
        (bullet+i)->damage = damage;

   }
    char_->draw();

	bool start = false;
	
    gotoxy(SCREEN_W/2, SCREEN_H/2); cout << "READY?";
    Sleep(2000); 
    gotoxy(SCREEN_W/2, SCREEN_H/2); cout << "      ";

    gotoxy(SCREEN_W/2, SCREEN_H/2); cout << "FIGHT";
    Sleep(1000);
    gotoxy(SCREEN_W/2, SCREEN_H/2); cout << "       ";


    while(1){
        
		
		if( kbhit()){ 
          	
            char c = getch();
            if(char_->y > SCREEN_H/2 + 3){
                char_->erase();
                gotoxy(char_->x, char_->y + 1); cout << "_";
                
                if(char_->x + 3 <= SCREEN_W/2 + 16)
                    gotoxy(char_->x + 3, char_->y+1); cout << "_";

                if( c == 'w' || 'W'){
                    gotoxy(char_->x, char_->y + 1); cout << "___";
                }
            }
            else if( char_->y < SCREEN_H/2 - 7){
                char_->erase();
                gotoxy(char_->x, char_->y ); cout << "____";

                if( c == 's' || c == 'S'){
                    gotoxy(char_->x, char_->y); cout << "__";
                }
            }        
            else char_->erase();

        if( c == 'a' || c == 'A'){
                if(char_->x > SCREEN_W/2 - 14)
                    char_->x -= 2;
            }        
            else if( c == 'd' || c == 'D'){
                if(char_->x < SCREEN_W/2 + 12)
                    char_->x += 2;
            }
            else if( c == 'w' || c == 'W'){
                if(char_->y > SCREEN_H/2 - 8)
                    char_->y--;
            }
            else if( c == 's' || c == 'S'){
                if(char_->y < SCREEN_H/2 + 4)
                    char_->y++;
            }
            
            
        }

        (bullet)->ready = 1;

        char_->draw();
        
        for(int i = 0; i < NUM; i++)
            (bullet+i)->draw();

        
       Sleep(15);

        for(int i = 0; i < NUM; i++)
            (bullet+i)->erase();

        for(int i = 0; i < NUM; i++){
            collision(i, bullet, char_, knight);
            if(knight.HP <= 0) return;

            gotoxy(SCREEN_W/2-2, SCREEN_H/2 + 7); cout << "HP: " << knight.HP << "/" << knight.MaxHP;
        }

        for(int i = 0; i < NUM - 1; i++){
            if( (bullet+i)->y == SCREEN_H/2 - 4)
                if( (bullet+i+1)->ready == 0)
                    (bullet+i+1)->ready = 1;
        }

        for(int i = 0; i < NUM; i++)
            if((bullet+i)->ready)
               (bullet+i)->y++;
        

        for(int i = 0; i < NUM; i++)
            if((bullet+i)->y >= SCREEN_H/2 + 4){
                count--;
                
                if(!count) return; 
                
                (bullet+i)->reset();
            }
       }
}
void drawBorder(Knight &knight, int type_enemy ,string type_combat){
    
    system("cls");
    TextColor(14);
    
    for (int i = 1; i < SCREEN_W ; i++)
    {
        gotoxy(i, 0);
        cout << "_";
    }
    for (int i = 1; i < SCREEN_H; i++)
    {
        gotoxy(0, i);
        cout << "|";
        gotoxy(SCREEN_W , i);
        cout << "|";
        cout << endl;
    }
    for (int i = 1; i < SCREEN_W ; i++)
    {
        gotoxy(i, SCREEN_H - 1);
        cout << "_";
    }

    gotoxy(SCREEN_W/2-33, SCREEN_H/2 + 7); cout << knight.name;
    gotoxy(SCREEN_W/2-22, SCREEN_H/2 + 7); cout << "LEVEL " << knight.level;
    gotoxy(SCREEN_W/2-2, SCREEN_H/2 + 7); cout << "HP: " << knight.HP << "/" << knight.MaxHP;

    for(int i = 1; i <= SCREEN_W - 1; i++){
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

    if( type_combat == "Player"){
    
        for(int i = 4; i <= SCREEN_W - 4; i++){
            gotoxy(i, 9); cout << "_";
        }

        for(int i = 10; i <= SCREEN_H - 8; i++){
            gotoxy(3, i); cout << "|";
            gotoxy(69, i); cout << "|";
            cout << endl;
        }

        for(int i = 4; i <= SCREEN_W - 4; i++){
            gotoxy(i, 16); cout << "_";
        }
    
        TextColor(14);
            Model("HiepSi");

        switch(type_enemy){
            case 0:
                Model("NPC");
                break;

            case 1:
                Model("Monster");
                break;
        }

    } else if(type_combat == "Monster"){
        
        for (int i = SCREEN_W / 2 - 15; i <= SCREEN_W / 2 + 15; i++){
            gotoxy(i, SCREEN_H / 2 - 8);
            cout << "_";
        }
        for (int i = SCREEN_H / 2 - 7; i < SCREEN_H / 2 + 6; i++){
            gotoxy(SCREEN_W / 2 - 16, i);
            cout << "|";
            gotoxy(SCREEN_W / 2 + 16, i);
            cout << "|";
            cout << endl;
        }
        for (int i = SCREEN_W / 2 - 15; i <= SCREEN_W / 2 + 15; i++){
            gotoxy(i, SCREEN_H / 2 + 5);
            cout << "_";
        }
    }
}
void Analyse(Attribute Monsvat, int event, const int HP){ 
    TextColor(14);
    gotoxy(5, 11); cout << "* " << Event_Name[event];
    gotoxy(19, 11); cout << "ATK " << Monsvat.Atk;
    gotoxy(27, 11); cout << "LEVEL " << Monsvat.level;
    gotoxy(5, 13); cout << "* " << Monsvat.infor;
}
void Init(string ten, Attribute &Monsvat)
{
    string s; 
    Monsvat.name = ten;
    ten += ".txt";
    fstream inp(ten);
    inp >> Monsvat.HP >> Monsvat.Atk >> Monsvat.level;
    inp.ignore();
    getline(inp, Monsvat.infor);
}    
void Revieve(int &phoenixdown, Knight &knight){
    gotoxy(6, 11); cout << "                                 ";
    gotoxy(6, 13); cout << "                                 ";
    gotoxy(6, 11); cout << "Hiệp sĩ đã hẹo, bạn có muốn hồi sinh?";
    
    TextColor(224);
    gotoxy(18, 15); cout << "|  Có   |";
    TextColor(14);
    gotoxy(46, 15); cout << "| Không |";
    int vi_tri = 0; int toado = 18;
    do{
         char c = getch();        
        if(c == 'd' || c == 'D' || c == 77) vi_tri = 1;
        else if(c == 'a' || c == 'A' || c == 75) vi_tri = 2;
        else if(c == 13) vi_tri = 3;
        else (vi_tri == 0);

        if(vi_tri == 1 && toado == 18) toado += 28;
        else if(vi_tri == 2 && toado == 46) toado -= 28;
        switch (toado){
            case 18:
                TextColor(224);
                gotoxy(18, 15); cout << "|  Có   |";
                TextColor(14);
                gotoxy(46, 15); cout << "| Không |";
            break;

            case 46:               
                gotoxy(18, 15); cout << "|  Có   |";
                TextColor(224);
                gotoxy(46, 15); cout << "| Không |"; 
                TextColor(14);   
            break;
                
        } 


    } while(vi_tri != 3);
    if(toado == 18){
        knight.HP = knight.MaxHP;
        phoenixdown--;
    }
    
}
void item(int &Phoenixdown, int &Remedy, int &Maidenkiss, Knight &knight, bool Mons){

    int vitriy = 12, vitrix = 8;
    int Toado = 11, Chon = 0;   
    TextColor(14);
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
        else if(c == 27) Chon = 4;
        else Chon = 0;
        
        if(Toado > 11 && Toado <= 15 && Chon == 1) Toado -= 2;
        else if(Toado >= 11 && Toado < 15 && Chon == 2) Toado += 2;
        else if(Chon == 4){
            knight.turn = false;
            Toado = 0;
            break;
        }
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
    if(Maidenkiss && Toado == 11){
            drawBorder(knight,2, "Player");
             Maidenkiss--;
             gotoxy(6, 11); cout << "Bạn vừa dùng Maidenkiss";
    } else if(Phoenixdown && Toado == 12){
        drawBorder(knight,2, "Player");
                    Phoenixdown--;
                    gotoxy(6, 11); cout << "Bạn vừa dùng Phoenixdown";
    } else if(Remedy && Toado == 15){
        drawBorder(knight,2, "Player");
                    Remedy--;
                    gotoxy(6, 11); cout << "Bạn vừa dùng Remedy";
    }  else {     
            knight.turn = false;
            Toado = 0;
    }    
    
}   
void CleanBoard(){
    for(int i = 10; i <= 15; i++){
        for(int j = 4; j <= 68; j++){
            gotoxy(j, i); cout << " ";
        }
    }
}
void Interact(string infor, int event, Knight &knight, Bullet* bullet, Character* char_ ,int &remedy, int &maidenkiss, int &phoenixdown, int rescue)
{
    infor += ".txt";
    Monster Mons("",0 ,0 ,0 ,0, true, "");
    Attribute NPC("",0 ,0 ,0 ,0, true);
    Attribute items("", 0, 0, 0, 0, true);
    fstream inp(infor);
    knight.turn = true;    
    string MadBear, Bandit, LordLupin, Elf, Troll, Shaman, Siren_Vajsh, Bowser;
    getline(inp, MadBear, ',');

    getline(inp, Bandit, ',');
    getline(inp, LordLupin, ',');
    getline(inp, Elf, ',');
    getline(inp, LordLupin, ',');
    getline(inp, Troll, ',');
    getline(inp, Shaman, ',');
    getline(inp, Siren_Vajsh, ',');
    getline(inp, Bowser, ',');
    bool win = false; int toa_do;
    switch (event){

                case 6:
                    Init(Event_Name[event], Mons);
                    break;
                case 7:
                    Init(Event_Name[event], Mons);
                    break;
                case 11:
                    Init(Event_Name[event], items);
                    break;
                case 12:
                    Init(Event_Name[event], items);   
                    break;
                case 13:
                    Init(Event_Name[event], items);   
                    break;    
                case 15:
                    Init(Event_Name[event], NPC);
                    break;
                case 14:
                    Init(Event_Name[event], NPC);
                    break;          
                case 17:
                    Init(Event_Name[event], Mons);
                    break;
                default:
                    Init(Event_Name[event], Mons);
                    break;
    }
   
    switch (event){
        case 8:
        case 9:
        case 10:{
            drawBorder(knight,2, "PLayer");
            
            gotoxy(55,7); cout << "🍄";
            gotoxy(6, 11); cout << "Bạn nhặt được cây nấm có vẻ SUS!";
            TextColor(224);
            gotoxy(18, 15); cout << "|  Ăn  |";
            TextColor(14);
            gotoxy(46, 15); cout << "| Quăng |";
            
            int vi_tri = 0; int toado1 = 18;
            
            do{
                char c = getch();        
                if(c == 'd' || c == 'D' || c == 77) vi_tri = 1;
                else if(c == 'a' || c == 'A' || c == 75) vi_tri = 2;
                else if(c == 13) vi_tri = 3;
                else (vi_tri == 0);

                if(vi_tri == 1 && toado1 == 18) toado1 += 28;
                else if(vi_tri == 2 && toado1 == 46) toado1 -= 28;
                switch (toado1){
                    case 18:
                        TextColor(224);
                        gotoxy(18, 15); cout << "|  Ăn   |";
                        TextColor(14);
                        gotoxy(46, 15); cout << "| Quăng |";
                    break;

                    case 46:               
                        gotoxy(18, 15); cout << "|  Ăn   |";
                        TextColor(224);
                        gotoxy(46, 15); cout << "| Quăng |"; 
                        TextColor(14);   
                    break;
                        
                } 


            } while(vi_tri != 3);
        
            if(toado1 == 18){
                
                switch(event){
                    case 8:              
                        CleanBoard();
                            gotoxy(6, 11); cout << "Attack được x2";
                            gotoxy(6, 13); cout << "Attack: " << knight.Atk << " --> " << knight.Atk*2;
                            knight.Atk *= 2;
                        cin.ignore();
                    break;

                    case 9:
                        CleanBoard();
                            gotoxy(6, 11); cout << "Bạn được hồi 100 HP";
                                if(knight.HP + 100 > knight.MaxHP) knight.HP = knight.MaxHP;
                                else knight.HP += 100;
                            gotoxy(6, 13); cout << "HP: " << knight.HP - 100 << " --> " << knight.HP;
                        cin.ignore();
                    break;

                    case 10:
                        CleanBoard();

                            gotoxy(6, 11); cout << "Bạn bị trúng độc :D";
                            gotoxy(8, 4); cout << "@_@";
                            knight.Poisened();
                            cin.ignore();
                        break;    

                }
            }
        
            knight.Status(remedy, maidenkiss, phoenixdown);
        }

        break;
        
        case 11:{
            remedy++;
            drawBorder(knight,2, "PLayer");
            gotoxy(6, 11); cout << "*Bạn vừa nhặt được " << items.name;
            
            cin.ignore();
        }    
        break;
        
        case 12:{
            maidenkiss++;
            drawBorder(knight,2, "PLayer");
            gotoxy(6, 11); cout << "*Bạn vừa nhặt được " << items.name;
            
            cin.ignore();
        }
        break;
        
        case 13:{
            phoenixdown++;
            drawBorder(knight,2, "PLayer");
            gotoxy(6, 11); cout << "*Bạn vừa nhặt được " << items.name;
            
            cin.ignore();
        }    
        break;

        case 14:
        case 15:                  
            while(win != 1){
                drawBorder(knight, false, "Monster");
                gotoxy(5, 11); cout << "*Có vẻ " << NPC.name << " đang muốn điều gì đó..";
                Xu_li(toa_do);
                CleanBoard();
                switch(toa_do){
            
                    case 0: 
                        gotoxy(6, 11); cout << "*" << "Bạn không thể tấn công " << NPC.name; 
                        cin.ignore();
                    break; 

                    case 15:      
                        Analyse(NPC, event, NPC.MaxHP);  
                        cin.ignore();
                    break;

                    case 30:
                        item(phoenixdown, remedy, maidenkiss, knight, false);   
                    break;
                    
                    case 45:
                        drawBorder(knight, true, "PLayer");
                        animation1(0, 0, 0);
                        win = 1;
                }
            
            }
            break;

        default:
        
            do{

                while(knight.turn && win != 1){                   
                        drawBorder(knight, true, "PLayer");
                        if(knight.have_debuff){
                            if(knight.getStatus() == "Ếch")
                                Model("Frog");
                            else if(knight.getStatus() == "Tí hon")
                                Model("Tiny");
                            else {
                                gotoxy(8,4); cout << "@_@";
                            }
                        }
                            
                       gotoxy(6, 11); cout << "*"<< Mons.name << " đang chặn đường bạn";
                    
                        Xu_li(toa_do);
                        CleanBoard();
                        
                        switch(toa_do){
                            case 0:{
                                if(knight.getStatus() == "Ếch"){
                                    gotoxy(6, 11); cout << "*" << "Bạn không thể tấn công trong trạng thái ếch";
                                    knight.turn = false; 
                                    cin.ignore();
                                } else {             

                                    int damage = knight.Atk*knight.level;
                                    
                                    animation1(damage, 1, 1);
                                    Mons.HP -= damage;
                                    drawBorder(knight, true, "PLayer");
                                    gotoxy(6,11); cout << "*Damage: ";
                                    TextColor(4);
                                    gotoxy(15, 11); cout << damage;
                                    TextColor(14);
                                    
                                    int HP = (Mons.HP < 0) ? 0 : Mons.HP;
                                    
                                    gotoxy(6, 13); cout << "*HP của địch: " << Mons.HP + damage << "-->" << HP;
                                    if(Mons.HP <= 0){
                                        gotoxy(51,3); cout << "xx";
                                    }
                                    cin.ignore();  
                                }
                            }
                              
                            break;       
                            
                            
                            case 15:{
                                switch (event)
                                    {

                                    case 6:
                                        Analyse(Mons, event, Mons.MaxHP);
                                        break;
                                    case 7:
                                        Analyse(Mons, event, Mons.MaxHP);
                                        break;
                                    case 15:
                                       Analyse(Mons, event, Mons.MaxHP);
                                        break;
                                    case 16:
                                        Analyse(Mons, event, Mons.MaxHP);
                                        break;
                                    case 17:
                                        Analyse(Mons, event, Mons.MaxHP);
                                        break;
                                    default:
                                        Analyse(Mons, event, Mons.MaxHP);
                                        break;
                                }
                                knight.turn = false; 
                                cin.ignore();
                            }
                                break;


                            case 30:
                                
                                item(phoenixdown, remedy, maidenkiss, knight, true);                   
                            
                            break;
                            
                            case 45:
                                
                                drawBorder(knight, true, "PLayer");
                                animation1(0, 0, 1);
                                win = 1;
                            
                            break;

                            default:
                            break;
                        }
                        
                        if(win) continue;
                        {    win = Mons.HP <= 0 ? 1 : 0;
                        }
                        
                        if(!knight.turn) knight.turn = true;
                        else {
                            
                            knight.turn = false; 
                            Mons.turn = true;

                        }
                }
                
                while(Mons.turn && win != 1){

                        int damage = Mons.level*Mons.Atk, recent_HP = knight.HP; 
                        
                        drawBorder(knight, true, "PLayer"); Sleep(500);
                            
                        //play(bullet, char_, knight, Mons);
                        
                        
                        if(knight.HP <= 0 && phoenixdown > 0){
                            
                            gotoxy(8, 4); cout << "x_x" << endl;
                            gotoxy(50,50);
                            
                            Revieve(phoenixdown, knight);
                        } 
                        

                        knight.Status(remedy, maidenkiss, phoenixdown);
                        win = knight.HP <= 0 ? 1 : 0;

                        Mons.turn = false; knight.turn = true;
            }


            } while (win != 1);

        break;    
    }

}
    int main()
    {
        setcursor(0,0);
        srand(time(NULL));
        string Thong_tin;
        Knight knight("Tiến", 5000, 5000,1000, 1, true);
        int remedy = 0, maidenkiss = 0, phoenixdown = 0;
        Monster* monster = new Monster();
        monster = monster->monster("", 1, 2, 3, 4);
        Character* Char = new Character();
        Bullet* bullet = new Bullet[NUM];
        drawBorder(knight, 2, "Monster");
        play(bullet,Char, knight, monster);
    }
