#include "bin/knight.h"
#include "bin/backpack.h"
#include "bin/monster.h"
"ddan"

void gotoxy(short x, short y){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y}; SetConsoleCursorPosition(h, a);
}
void TextColor(int x){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x); 
}
void setcursor(bool visible, DWORD size){
	
    if(size == 0)
		size = 20;	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(h,&lpCursor);
}

/* * * BEGIN OF ITEM CLASS * * */

Item::Item(string name, unsigned int quantity) : name(name), quantity(quantity){};

Potion::Potion(string name, unsigned int quantity) : Item(name, quantity){};

Potion* Potion::createPotion(string name, unsigned int qua){
    Potion* potion = new Potion(name, qua);
    
    return potion;
}

/* * * END OF ITEM CLASS * * */

Item* ItemManager::findItem(Item* item_to_find){
    for(auto x : items)
        if(x->name == item_to_find->name) 
            return x;
}
void ItemManager::addItem(Item* item_to_add){
    for(auto x : items){
        if(x->name == item_to_add->name){
            x->quantity += 1;
            return;
        } 
    }
    this->items.push_back(item_to_add);
}
void ItemManager::removeItem(Item* item_to_remove){
    if(!item_to_remove || !(backpack->findItem(item_to_remove)))
        return;

    for(auto x = items.begin(); x != items.end(); ++x){
        if((*x)->name == item_to_remove->name){
            items.erase(x); return;
        }
    }
}
void ItemManager::showItems(){
    if(items.empty()) return;
    int nth = 0, num_page, count = 0;

    for(auto x : this->items) count++; 
    num_page = count/6 + 1; int item_per_page[num_page];

    if(num_page > 1){
        for(int i = 0; i < num_page - 1; i++)
            item_per_page[i] = 6;
        item_per_page[num_page - 1] = count%6;
    } else{
        item_per_page[num_page-1] = count%6;
    }

    vector<vector<string>> page(num_page, vector<string>(6, ""));

    for(int i = 0; i < num_page; ++i){
        for(int j = 0; j < item_per_page[i]; j++){
            page[i][j] = "*" + items[nth]->name + " X" + to_string(items[nth]->quantity);
            nth++;
        }
    }
// 37 <  38 ^  39 >  40 v    
    int _x[]= {8, 35};
    int _y[] = {11, 13, 15};
    int i = 0, j = 0;
    for(auto x : page[0]){
        gotoxy(_x[i], _y[j]); cout << x;
            if(i){
                if(j == 2){
                    j = 0;
                }
                else{ j++; i = 0;
                }   
            } else i++;
    }

}
/* * * BEGIN OF ATTRIBUTE CLASS * * */

Attribute::Attribute(string name,int MaxHP, int HP, float Atk, int level, bool turn, string infor) :
name(name), MaxHP(MaxHP), HP(HP), level(level), Atk(Atk), turn(turn), infor(infor){};


Knight* Knight::create(){
    
    Knight* knight = new Knight();
    string s("knight.txt"); fstream inp(s); 
    
    inp >> knight->name >> knight->MaxHP >> knight->HP >> knight->Atk >> knight->level >> knight->turn;
    
    return knight;
}

bool Knight::isPoisoned(){
    
    if(!poisoned){          
        
        poisoned = 3; frog = 0; tiny = 0;
        currentStatus = "poisoned";

        return 1;
    }
    return 0;
}
bool Knight::isFrogged(){
    
    if(!frog){

        poisoned = 0; frog = 3; tiny = 0;
        tempValue = level; level = 1;
        hasDebuff = true; currentStatus = "Frog";

        return 1;
    } 
    return 0;
}
bool Knight::getSmallen(){
    
    if(!tiny){
        
        poisoned = 0; frog = 0; tiny = 3;
        tempValue = HP; 
        hasDebuff = true;  currentStatus = "Tiny";

        if(HP <= 5) HP = 1;  else HP /= 5;

        return 1;  
    } 
    return 0;
}
string Knight::getStatus() const {
    
    return currentStatus;
}
void Knight::Status(Item* item){
    
    if(poisoned > 1) poisoned--;
    else {
            frog--;
            hasDebuff = false;  
            currentStatus = "Normal";
        }
       
    if(frog > 1) frog--;
    else {
            frog--;
            level = tempValue;
            hasDebuff = false; 
            currentStatus = "Normal"; 
    } 
    if(tiny > 1) tiny--;
    else {
            tiny--;
            HP *= 5; 
            hasDebuff = false;   
            currentStatus = "Normal";
        }               
}
void Knight::useItem(Item* item_to_use, ItemManager* balo){
    if(!item_to_use || balo->items.empty()) return;
        
    string s = item_to_use->name; Item* temp = balo->findItem(item_to_use);

    if(s == "Antidote"){
        poisoned = 0;  hasDebuff = false;
        currentStatus = "normal";
    } else if(s == "Maidenkiss"){
        level = tempValue;
            hasDebuff = false; 
            currentStatus = "Normal"; 
    } else if(s == "MushMario"){
            HP *= 5; 
            hasDebuff = false;   
            currentStatus = "Normal";
    }
    
    if(temp->quantity < 2) balo->removeItem(temp);
    else temp->quantity--;
}


Monster::Monster(string name,int MaxHP, int HP, float Atk, int level, bool turn, string infor) : Attribute(name, MaxHP, HP, Atk, level, turn, infor){};

Monster* Monster::init(){

    Monster* ms = new Monster(); fstream input("Monster.txt"); string temp;
        while(input >> temp){
            Monster* m = new Monster();
                m->name = temp; temp += "txt";
                fstream output(temp);
                output >> m->HP >> m->Atk >> m->level; output.ignore();
                output >> m->infor; 

            ms->type.push_back(m);            
        }


    return ms;
}
void Monster::skill(int event, Knight* knight){
    
    if(skill_cooldown == 0){
        
        skill_cooldown = 3;
        
        switch (event){
            case 6:
                
                knight->isFrogged();
                
            break;

            case 7:
                knight->getSmallen();
                

            break;
        }
    } else this->skill_cooldown--;

}
void Knight::revieve(ItemManager* balo){
    
    gotoxy(6, 11); cout << "YOU DIED! ";
    gotoxy(6, 13); cout << "You have Phoenixdown potion in your backpack.";
    gotoxy(6, 15);  cout << "Press \"Enter\" to revive.";
    
    while(1){
        char c = getch();

        switch(c){
            case 13:
                this->useItem(PhoenixDown, balo);
                return;
            break;
        }
    }
}

/* * * END OF KNIGHT CLASS * * */

/* * * BEGIN OF OBJECT CLASS * * */
  
MainCharacter* MainCharacter::create(){

    MainCharacter* c = new MainCharacter();
        c->model_c = modelMC;
        c->x = SCREEN_W/2; c->y = SCREEN_H/2;

    return c;
}
void MainCharacter::draw() const {

    for(int i = 0; i < Model_c_Y_Length; i++){
        for(int j = 0; j < Model_c_X_Length; j++){
        
            gotoxy(x + j, y + i); cout << model_c[i][j];      
        }
        cout << endl;
    }
}

void MainCharacter::erase() const {

    for(int i = 0; i < Model_c_Y_Length; i++){
        for(int j = 0; j < Model_c_X_Length; j++){
        
            gotoxy(x + j, y + i); cout << " ";      
        }
        cout << endl;
    }
}


Bullet* Bullet:: create(){
    
    Bullet* bullet = new Bullet();
        bullet->model_b = modelBl;
        bullet->y = SCREEN_H/2 - 7;

    return bullet;
}
void Bullet::draw() const {

    if(isReady){
        for(int i = 0; i < Model_b_Y_Length; i++){
            for(int j = 0; j < Model_b_X_Length; j++){
                gotoxy(this->x+j, this->y+i); cout << model_b[i][j];
            }
        }    
    }
}

void Bullet::erase() const{
    
    if(isReady){
        for(int i = 0; i < Model_b_Y_Length; i++){
            for(int j = 0; j < Model_b_X_Length; j++){
                gotoxy(x+j, y+i); cout << " ";
            }
        }    
    }
}

void Bullet::generate(){
    x = SCREEN_W/2 - 15 + rand()%31;
}

void Bullet::reset(){
    
    erase(); generate();
    isReady = 0;
    y = SCREEN_H/2 - 7;
    
}
void Bullet::collision(int i, Bullet* bullet, MainCharacter* Char, Knight* Knight){
    
    if((bullet+i)->y + 1 >= Char->y){
        if((bullet+i)->x - Char->x >= 0 && (bullet+i)->x - Char->x <= 4){
            Knight->HP -= (bullet+i)->damage;
            (bullet+i)->reset();
        }
    }
}

/* * *  END OF OBJECT CLASS * * */

/* * * BEGIN OF GAME CLASS * * */

void Game::dialogue(short x, short y, string s){
    
    for(int i = 0;i < s.length(); i++){
        gotoxy(x + i, y); cout << s[i];
        Sleep(100);
    }
}
void Game::intro(Knight* knight){
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
        gotoxy(65, 16); cout << "Press any key to continue!"; getch(); system("cls");
        
        cout << "NAME OF THE FAILURE: "; getline(cin, knight->name);
        system("cls");  cout << "Please wait..."; Sleep(2000); system("cls");

        dialogue(3, 1, "This is you"); drawModel("Knight"); gotoxy(6, 11); cout << knight->name;;  Sleep(500); 
        getch(); dialogue(20, 5, "<----- a failure"); Sleep(1000); system("cls");
        
        drawModel("Knight"); dialogue(7, 11, knight->name); 
        dialogue(20, 5, "<---- The princess was kidnapped by Bowser.");
        dialogue(20, 7, "<---- and your duty is defeat Bowser and save the princess, that's all.");
        dialogue(20, 9, "<---- Got it?");
        
        TextColor(224); gotoxy(SCREEN_W/2 - 4 - 3, 11); cout << "YES";
        TextColor(14); gotoxy(SCREEN_W/2 + 4 + 3, 11); cout << "NO";
    
        char c = getch(); int choice = 1;

        switch(c){
            case 'a':
                
                TextColor(224);
                gotoxy(SCREEN_W/2 - 4 - 3, 11); cout << "YES";
                TextColor(14);
                gotoxy(SCREEN_W/2 + 4 + 3, 11); cout << "NO";
                choice = 1;
            
                break;
            
            case 'd':

                TextColor(14);
                gotoxy(SCREEN_W/2 - 4 - 3, 11); cout << "YES";
                TextColor(224);
                gotoxy(SCREEN_W/2 + 4 + 3, 11); cout << "NO";
                TextColor(14);
                choice = 2;
            
                break;

            default:    
                break;
        }
       switch(choice){
            case 1:
                cout << ""; //act1;

            break;

            case 2:
                cout << "kememay"; //act1

            break;
       }
}

void Game::drawModel(string type){
    vector<string> model; bool isEnemy = false;

    if(type == "Knight") model = frame2_0;
    else if(type == "Frog") model = sprite_frog;
    else if(type == "Tiny") model = sprite_tiny;

     if(type == "Monster"){ model = sprite_monster; isEnemy = 1;}
     else if(type == "NPC"){ model = sprite_NPC; isEnemy = 1;}

     if(isEnemy){
        int i = 2;
            for(auto x : model){
                gotoxy(SCREEN_W/2 + 18, i++); cout << x;
            }
    }
    else{
        for(int i = 0; i < model.size(); i++)
            for(int j = 0; j < model[i].size(); j++){
                gotoxy(SCREEN_W/2 - 32 + j, i + 2); cout << model[i][j];
        }
    }    
};
void Game::delete_model(string type){
    vector<string> model; bool isEnemy = false;

    if(type == "Knight") model = frame4;
    else if(type == "Frog") model = sprite_frog;
    else if(type == "Tiny") model = sprite_tiny;

     if(type == "Monster"){ model = sprite_monster; isEnemy = 1;}
     else if(type == "NPC"){ model = sprite_NPC; isEnemy = 1;}

     if(isEnemy){
        for(int i = 0; i < model.size(); i++){
                gotoxy(SCREEN_W/2 + 18, i + 2); cout << "             ";
            }
        }
    else{
        for(int i = 0; i < model.size(); i++)
            for(int j = 0; j < model[i].size(); j++){
                gotoxy(SCREEN_W/2 - 32 + j, i + 2); cout << " ";
        }
    }     
}
int Game::choices_box(){
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
        
    int choice = 1; bool out = false; char c;
    
    while(!out){
    
        c = getch();

       switch(c){
           case 'a':
           case 'A':
                if(choice > 1) choice--;
           break;

           case 'd':
           case 'D':
                if(choice < 4) choice++;
            break;

           case 13:
                out = true;
            break;

           default:
              break;

        }
        
        switch (choice){
            case 1:
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

                break;
            
            case 2:

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

            break;

            case 3:

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
            break;

            case 4:

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
            break;

            default:
                break;
        } 
    }
    return choice;
}
void Game::animationAttack(Knight* knight){
    
    int i = 2; vector<vector<string>> sprite;

    sprite.push_back(frame1);
    sprite.push_back(frame2_0);
    sprite.push_back(frame3);
    sprite.push_back(frame4);

    drawBorder(knight, 1, "Player"); drawModel("Monster");

    for(auto x : sprite){
        for(auto y : x){
            gotoxy(4, i++); cout << y;
        }

        Sleep(75); delete_model("Knight"); i=2; 
    }

    sprite.clear();
    sprite.push_back(frame10);
    sprite.push_back(frame11);
    sprite.push_back(frame13);
    sprite.push_back(frame14);
    sprite.push_back(frame15);
    
    drawModel("Knight");

    for(auto x : sprite){
        for(auto y : x){
             gotoxy(48, i++); cout << y;  
        }
            Sleep(50); cleanBoard(SCREEN_W/2, 1, SCREEN_W - 1, SCREEN_H/2 - 4); i= 1; 
            drawModel("Monster");
    }
}

void Game::fight(Bullet* bullet, MainCharacter* char_, Knight* knight, Monster* monster){
    
    int count = 50;

    int damage = monster->level*monster->Atk;

    (bullet)->isReady = 1;

    char_->x = SCREEN_W/2;
    char_->y = SCREEN_H/2 + 4;

    for(int i = 1; i < NUM; i++)
        (bullet+i)->isReady = 0;

    for(int i = 0; i < NUM; i++){
        (bullet+i)->y = SCREEN_H/2 - 7;
        (bullet+i)->generate();
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

        (bullet)->isReady = 1;

        char_->draw();
        
        for(int i = 0; i < NUM; i++)
            (bullet+i)->draw();

        
       Sleep(15);

        for(int i = 0; i < NUM; i++)
            (bullet+i)->erase();

        for(int i = 0; i < NUM; i++){
            bullet->collision(i, bullet, char_, knight);
            
            if(knight->HP <= 0) return;

            gotoxy(SCREEN_W/2-2, SCREEN_H/2 + 7); cout << "HP: " << knight->HP << "/" << knight->MaxHP;
        }

        for(int i = 0; i < NUM - 1; i++){
            if( (bullet+i)->y == SCREEN_H/2 - 4)
                if( (bullet+i+1)->isReady == 0)
                    (bullet+i+1)->isReady = 1;
        }

        for(int i = 0; i < NUM; i++)
            if((bullet+i)->isReady)
               (bullet+i)->y++;
        

        for(int i = 0; i < NUM; i++)
            if((bullet+i)->y >= SCREEN_H/2 + 4){
                count--;
                
                if(!count) return; 
                
                (bullet+i)->reset();
            }
       }
}
void Game::drawBorder(Knight* knight, int type_enemy, string type_combat){
    
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

    gotoxy(SCREEN_W/2-33, SCREEN_H/2 + 7); cout << knight->name;
    gotoxy(SCREEN_W/2-22, SCREEN_H/2 + 7); cout << "LEVEL " << knight->level;
    gotoxy(SCREEN_W/2-2, SCREEN_H/2 + 7); cout << "HP: " << knight->HP << "/" << knight->MaxHP;

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
            drawModel("Knight");

        switch(type_enemy){
            case 0:
                drawModel("NPC");
                break;

            case 1:
                drawModel("Monster");
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
void Game::analyse(Monster* monster, int event){ 
    
    TextColor(14);
    gotoxy(5, 11); cout << "* " << Event_Name[event];
    gotoxy(19, 11); cout << "ATK " << monster->Atk;
    gotoxy(27, 11); cout << "LEVEL " << monster->level;
    gotoxy(5, 13); cout << "* " << monster->infor;
}
    

/*
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
*/
void Game::cleanBoard(int x1, int y1, int x2, int y2){
    for(int i = y1; i <= y2; i++){
        for(int j = x1; j <= x2; j++){
            gotoxy(j, i); cout << " ";
        }
    }
}
/*
void Game::interact(int event, Knight* knight, Bullet* bullet, MainCharacter* char_, Item* item, int rescue){
    
    bool defeat = false; 
   
    if(event > 10){
        
            drawBorder(knight,2, "Player"); 
            gotoxy(55,7); cout << "🍄";
            gotoxy(6, 11); cout << "You have picked a SUS Mushromm!";
            
            TextColor(224); gotoxy(SCREEN_W/2 - 17,SCREEN_H/2 + 3); cout << "|  Eat |";
            TextColor(14);  gotoxy(SCREEN_W/2 + 6,SCREEN_H/2 + 3) ;cout << "| Throw |";
            
            short choice = 1; char c = getch();  
            
            do{
              
                if(c == 'a' || c == 'A'){

                    choice = 0;                  
                    TextColor(224); gotoxy(SCREEN_W/2 - 17,SCREEN_H/2 + 3); cout << "|  Eat |";
                    TextColor(14); gotoxy(SCREEN_W/2 + 6,SCREEN_H/2 + 3) ;cout << "| Throw |";
            

                } else if(c == 'd' || c == 'D'){    

                    choice = 1;
                    gotoxy(SCREEN_W/2 - 17,SCREEN_H/2 + 3); cout << "|  Eat |"; TextColor(224);
                    gotoxy(SCREEN_W/2 + 6,SCREEN_H/2 + 3) ;cout << "| Throw |"; TextColor(14);

                } else break;

          } while(c = getch());
        
            if(!choice){
                
                switch(event){
                    
                    case 11:              
                        
                        cleanBoard();
                            gotoxy(6, 11); cout << "Your Atk got x2 damage";
                            gotoxy(6, 13); cout << "Attack: " << knight->Atk << " --> " << knight->Atk*2;
                            
                            knight->Atk *= 2;
                        cin.ignore();
                    break;

                    case 12:
                        cleanBoard();
                            dialogue(6, 11, "You recovered 100 HP");

                                if(knight->HP + 100 > knight->MaxHP) knight->HP = knight->MaxHP;
                                else knight->HP += 100;

                            gotoxy(6, 13); cout << "HP: " << knight->HP - 100 << " --> " << knight->HP;

                        cin.ignore();
                    break;

                    case 13:
                        cleanBoard();

                            gotoxy(6, 11); cout << "You're poisoned :D";
                            gotoxy(8, 4); cout << "@_@";
                            knight->isPoisoned();

                            cin.ignore();
                        break;    

                }
            }
        
            knight->Status(item);
    }
}
        
        }
        case 11:{
            remedy++;
            drawBorder(knight,2, "PLayer");
            gotoxy(6, 11); cout << "*Bạn vừa nhặt được " << items.knight->name;
            
            cin.ignore();
        }    
        break;
        
        case 12:{
            maidenkiss++;
            drawBorder(knight,2, "PLayer");
            gotoxy(6, 11); cout << "*Bạn vừa nhặt được " << items.knight->name;
            
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
                cleanBoard();
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
                        if(knight.hasDebuff){
                            if(knight.getStatus() == "Ếch")
                                drawModel("Frog");
                            else if(knight.getStatus() == "Tiny")
                                drawModel("Tiny");
                            else {
                                gotoxy(8,4); cout << "@_@";
                            }
                        }
                            
                       gotoxy(6, 11); cout << "*"<< Mons.name << " đang chặn đường bạn";
                    
                        Xu_li(toa_do);
                        cleanBoard();
                        
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
*/
int main()
{
        setcursor(0,0); srand(time(NULL)); Game::drawBorder(knight, true, "Player");
        backpack->addItem(PhoenixDown);
        backpack->addItem(Maidenkiss);
        backpack->addItem(Antidote);
        backpack->addItem(Aspirin);
        backpack->addItem(MushMario);
        backpack->showItems();
}
// 4 68
// 10 15
