#include <windows.h>
#include <iostream>
#include <direct.h>
#include <time.h>
#include <conio.h>
#include <fstream>

using namespace std;

#define SCREEN_W 72
#define SCREEN_H 24

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
        char* model;
   public:
        bool ready;
        
        Bullet(){};
        
        void Modify_Bullet(char c[]){
            this->model = c;
        }

        void draw(){
            if(this->ready){
                for(int j = 0; j < Model_Length; j++){
                    gotoxy(this->x+j, this->y); cout << *(this->model+j);
                }
            }
        }

        void erase(){
            if(this->ready){
                for(int j = 0; j < Model_Length; j++){
                    gotoxy(this->x+j, this->y); cout << " ";
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


bool collision(int i, Bullet* bullet, Character* Char){
    if((bullet+i)->y + 1 >= Char->y){
        if((bullet+i)->x - Char->x >= 0 && (bullet+i)->x - Char->x <= 4){
            return 1;
        }

    }
    return 0;
}
void play(Bullet* bullet, Character* Char){
    
    int count = 15;
    
    (bullet)->ready = 1;

    Char->x = SCREEN_W/2;
    Char->y = SCREEN_H/2 + 4;

    for(int i = 1; i < NUM; i++)
        (bullet+i)->ready = 0;

    for(int i = 0; i < NUM; i++){
        (bullet+i)->y = SCREEN_H/2 - 7;
        (bullet+i)->gen();
        (bullet+i)->Modify_Bullet(Model_Bullet);
    }

    Char->draw();

	bool start = false;
	
    gotoxy(SCREEN_W/2, SCREEN_H/2); cout << "READY?";
    Sleep(2000); 
    gotoxy(SCREEN_W/2, SCREEN_H/2); cout << "      ";

    gotoxy(SCREEN_W/2, SCREEN_H/2); cout << "FIGHT";
    Sleep(2000);
    gotoxy(SCREEN_W/2, SCREEN_H/2); cout << "       ";


    while(1){
        
		
		if( kbhit()){ 
          	
            char c = getch();
            if(Char->y > SCREEN_H/2 + 3){
                Char->erase();
                gotoxy(Char->x, Char->y + 1); cout << "_";
                
                if(Char->x + 3 <= SCREEN_W/2 + 16)
                    gotoxy(Char->x + 3, Char->y+1); cout << "_";

                if( c == 'w' || 'W'){
                    gotoxy(Char->x, Char->y + 1); cout << "___";
                }
            }
            else if( Char->y < SCREEN_H/2 - 7){
                Char->erase();
                gotoxy(Char->x, Char->y ); cout << "____";

                if( c == 's' || c == 'S'){
                    gotoxy(Char->x, Char->y); cout << "__";
                }
            }        
            else Char->erase();

        if( c == 'a' || c == 'A'){
                if(Char->x > SCREEN_W/2 - 14)
                    Char->x -= 2;
            }        
            else if( c == 'd' || c == 'D'){
                if(Char->x < SCREEN_W/2 + 12)
                    Char->x += 2;
            }
            else if( c == 'w' || c == 'W'){
                if(Char->y > SCREEN_H/2 - 8)
                    Char->y--;
            }
            else if( c == 's' || c == 'S'){
                if(Char->y < SCREEN_H/2 + 4)
                    Char->y++;
            }
            else break;  
            
            
        }

        (bullet)->ready = 1;

        Char->draw();
        for(int i = 0; i < NUM; i++)
            (bullet+i)->draw();

        
       Sleep(75);

        for(int i = 0; i < NUM; i++)
            (bullet+i)->erase();

        for(int i = 0; i < NUM; i++){
            if(collision(i, bullet, Char))
                return;
        }

        for(int i = 0; i < NUM - 1; i++){
            if( (bullet+i)->y == SCREEN_H/2 - 4)
                if( (bullet+i+1)->ready == 0)
                    (bullet+i+1)->ready = 1;
        }

        for(int i = 0; i < NUM; i++)
            if((bullet+i+1)->ready)
               (bullet+i)->y++;
        

        for(int i = 0; i < NUM; i++)
            if((bullet+i)->y >= SCREEN_H/2 + 4){
                count--;
                
                if(!count) return; (bullet+i)->reset();
            }
       }
}
void vekhung()
{
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
    

    for (int i = SCREEN_W / 2 - 15; i <= SCREEN_W / 2 + 15; i++)
    {
        gotoxy(i, SCREEN_H / 2 - 8);
        cout << "_";
    }
    //hitbox SCREEN_W/2 - 15, SCREEN_H /2 - 7;
    //hitbox SCREEN_W/2 + 15, SCREEN_H /2 + 4
    for (int i = SCREEN_H / 2 - 7; i < SCREEN_H / 2 + 6; i++)
    {
        gotoxy(SCREEN_W / 2 - 16, i);
        cout << "|";
        gotoxy(SCREEN_W / 2 + 16, i);
        cout << "|";
        cout << endl;
    }
    for (int i = SCREEN_W / 2 - 15; i <= SCREEN_W / 2 + 15; i++)
    {
        gotoxy(i, SCREEN_H / 2 + 5);
        cout << "_";
    }
}

int main()
{
    srand(time(NULL));
    setcursor(0, 0);
    
    Character* Char = new Character();
    Bullet* bullet = new Bullet[NUM];

    vekhung();

    play(bullet, Char);

    return 0;
}
*/
