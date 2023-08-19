#include "bin/knight.h"
#include "bin/backpack.h"
#include "bin/monster.h"

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
void ItemManager::showItems(Knight* knight){
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

    vector<vector<string>> page(num_page - 1, vector<string>(6, ""));
    page.push_back(vector<string>(item_per_page[num_page-1], ""));

    Game::cleanBoard(4, 10, 68, 15);

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
//show first page
    bool isfirstItem = true;
    for(auto x : page[0]){
        
        if(isfirstItem){
             isfirstItem = false;  TextColor(224);  
        }
        gotoxy(_x[i], _y[j]); cout << x; TextColor(14);

        if(i){ if(j == 2) j = 0; else{ j++; i = 0;} } else i++;
    }
// show all page
    int choice = 0, currentPage = 0, previousPage = currentPage;
    int pos_x = 0, pos_y = 0, max_pos_x[num_page], max_pos_y[num_page];

    for(int i = 0; i< num_page; i++){

        switch(item_per_page[i]){
            case 1:
                max_pos_x[i] = 0; max_pos_y[i] = 0;
            break;

            case 2:
                max_pos_x[i] = 1; max_pos_y[i] = 0;
            break;

            case 3:
                max_pos_x[i] = 0; max_pos_y[i] = 1;
            break;

            case 4:
                max_pos_x[i] = 1; max_pos_y[i] = 1;
            break;

            case 5:
                max_pos_x[i] = 0; max_pos_y[i] = 2;
            break;

            case 6:
                max_pos_x[i] = 1; max_pos_y[i] = 2;
            break; 
            
        }
    } 

    while(1){
        char c = getch(); i = 0; j = 0;
    // click right
        if(c == 'd' || c == 'D' || c == 77){ 
            if(pos_x + 1 > max_pos_x[currentPage]){
                if(currentPage + 1 >= num_page) currentPage = 0;
                    else currentPage++;
                pos_x = 0;
                if(max_pos_y[currentPage] < 1) pos_y = max_pos_y[currentPage];
            } else pos_x++;
        }
    // click left
        if(c == 'a' || c == 'A' || c == 75){ 
            if(pos_x - 1 < 0){
                if(currentPage - 1 < 0) currentPage = num_page-1;
                    else currentPage--;
                pos_x = max_pos_x[currentPage];
                pos_y = 0;
            } else pos_x--;
        }
    // click up
        if(c == 'w' || c == 'W' || c == 72){ 
            if(pos_y - 1 < 0){
                pos_y = max_pos_y[currentPage]; 
            } else pos_y--;
        }
    // click down
        if(c == 's' || c == 'S' || c == 80){ 
            if(pos_y + 1 > max_pos_y[currentPage]){
                pos_y = 0;
            } else pos_y++;
        }
        if(c == 13) break;
        if(c == 27){
            knight->turn = 1; return;
        }
       
        if(previousPage != currentPage) Game::cleanBoard(4, 10, 68, 15);

        for(int x = 0; x < page[currentPage].size(); x++){
            
            if(page[currentPage][x] != ""){

                if(pos_x == i && pos_y == j){ TextColor(224); choice = (currentPage)*6 + x;}
                gotoxy(_x[i] , _y[j]); cout << page[currentPage][x]; TextColor(14);
                if(i){ if(j == 2) j = 0; else{ j++; i = 0;} } else i++;
            }
        
        }

        previousPage = currentPage;
 
    }
    
    knight->useItem(this->items[choice], backpack);
    
}
/* * * BEGIN OF ATTRIBUTE CLASS * * */

Attribute::Attribute(string name,int MaxHP, int HP, float Atk, int level, bool turn, string infor) :
name(name), MaxHP(MaxHP), HP(HP), level(level), Atk(Atk), turn(turn), infor(infor){};


Knight* Knight::init(){
    
    Knight* knight = new Knight();
    string s("lib/knight.txt"); fstream inp(s); 
    
    inp >> knight->name >> knight->MaxHP >> knight->HP >> knight->Atk >> knight->level >> knight->turn;
    
    return knight;
}

void Knight::isPoisoned(){
    
    if(!this->poisoned){          
        
        this->poisoned = 3; this->frog = 0; tiny = 0;
        currentStatus = 'p'; hasDebuff = true;
        gotoxy(8, 4); cout << "@v@";
        
    }
    
}
void Knight::isFrogged(){
    
    if(!this->frog){

        this->poisoned = 0; this->frog = 3; tiny = 0;
        tempValue = level; level = 1;
        hasDebuff = true; currentStatus = 'f';
    } 

}
void Knight::getSmallen(){
    
    if(!tiny){
        
        this->poisoned = 0; this->frog = 0; tiny = 3;
        tempValue = HP; 
        hasDebuff = true;  currentStatus = 't';

        if(HP <= 5) HP = 1;  else HP /= 5;
  
    } 

}
void Knight::Status(){
  
    switch(currentStatus){
        case 'p':
            
            if(this->poisoned > 1){
                this->poisoned--; HP -= 5;
            } else {
                this->poisoned = 0;
                hasDebuff = false;  
                currentStatus = 'n';
            }
        break;

        case 'f':

            if(this->frog > 1)
                this->frog--;
            else {
                level = tempValue;
                hasDebuff = false; 
                currentStatus = 'n';
                this->frog = 0;
            } 
        break;

        case 't':
      
            if(this->tiny > 1)
                tiny--;
            else {
                    HP *= 5; 
                    hasDebuff = false;   
                    currentStatus = 'n';
                    this->tiny = 0;
            }
        break;             
    }
}
void Knight::useItem(Item* item_to_use, ItemManager* balo){
    if(!item_to_use || balo->items.empty()) return;
        
    string s = item_to_use->name; Item* temp = balo->findItem(item_to_use);

    Game::cleanBoard(4, 10, 68, 15); gotoxy(6, 11) ; cout << "*You used " << s; getch();
    if(hasDebuff){
        if(s == "Antidote"){
            this->poisoned = 0;  hasDebuff = false;
            currentStatus = 'n'; gotoxy(8,4); cout << "'v'";
        } else if(s == "Maidenkiss"){
                level = tempValue;
                hasDebuff = false; 
                currentStatus = 'n'; 
        } else if(s == "MushMario"){
                HP *= 5; 
                hasDebuff = false;   
                currentStatus = 'n';
        }
    }
    
    if(temp->quantity < 2) balo->removeItem(temp);
    else temp->quantity--;

    
}

Monster::Monster(string name,int MaxHP, int HP, float Atk, int level, bool turn, string infor) : Attribute(name, MaxHP, HP, Atk, level, turn, infor){};

Monster* Monster::init(){

    Monster* ms = new Monster(); 
    fstream input("lib/Monster.txt"); string temp;
        while(input >> temp){
            Monster* m = new Monster();
                m->name = temp; temp = "lib/" + temp + ".txt";
                fstream output(temp);
                output >> m->HP >> m->Atk >> m->level >> m->turn; output.ignore();
                getline(output, m->infor); 

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

/* * * END OF ATTRIBUTE CLASS * * */

/* * * BEGIN OF OBJECT CLASS * * */
  
MainCharacter* MainCharacter::init(){

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


Bullet* Bullet::init(){
    
    Bullet* bullet = new Bullet[NUM];
      for(int i = 0; i < NUM; i++){ 
        (bullet+i)->model_b = modelBl;
        (bullet+i)->y = SCREEN_H/2 - 7;
      }

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
    
    this->erase(); this->generate();
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

        dialogue(3, 1, "This is you"); drawModel('k'); gotoxy(6, 11); cout << knight->name;;  Sleep(500); 
        getch(); dialogue(20, 5, "<----- a failure"); Sleep(1000); system("cls");
        
        drawModel('k'); dialogue(7, 11, knight->name); 
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

void Game::drawModel(char type){
    vector<string> model; bool isEnemy = false;

    if(type == 'k') model = frame2_0;
    else if(type == 'f') model = sprite_frog;
    else if(type == 't') model = sprite_tiny;

     if(type == 'm'){ model = sprite_monster; isEnemy = 1;}
     else if(type == 'n'){ model = sprite_NPC; isEnemy = 1;}

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
void Game::delete_model(char type){
    vector<string> model; bool isEnemy = false;

    if(type == 'k') model = frame4;
    else if(type == 'f') model = sprite_frog;
    else if(type == 't') model = sprite_tiny; 

     if(type == 'm'){ model = sprite_monster; isEnemy = 1;}
     else if(type == 'n'){ model = sprite_NPC; isEnemy = 1;}

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
            case 13:
                out = true;
            break;

           case 'a':
           case 'A':
           case 75:
                if(choice > 1) choice--;
           break;

           case 'd':
           case 'D':
           case 77:
                if(choice < 4) choice++;
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

    drawBorder(knight, 1, 'a'); drawModel('m');

    for(auto x : sprite){
        for(auto y : x){
            gotoxy(4, i++); cout << y;
        }

        Sleep(50); delete_model('k'); i=2; 
    }

    sprite.clear();
    sprite.push_back(frame10);
    sprite.push_back(frame11);
    sprite.push_back(frame13);
    sprite.push_back(frame14);
    sprite.push_back(frame15);
    
    drawModel('k');

    for(auto x : sprite){

        for(auto y : x){
             gotoxy(48, i++); cout << y;  
        }
            Sleep(50); cleanBoard(SCREEN_W/2, 1, SCREEN_W - 1, SCREEN_H/2 - 4); i= 1; 
            drawModel('m');
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
        
		if(kbhit()){ 
          	
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

            gotoxy(SCREEN_W/2 - 2, SCREEN_H/2 + 7); cout << "HP: " << knight->HP << "/" << knight->MaxHP << "  ";
        }

        for(int i = 0; i < NUM - 1; i++){
            if( (bullet+i)->y == SCREEN_H/2 - 4)
                if((bullet+i+1)->isReady == 0)
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
void Game::drawBorder(Knight* knight, int type_enemy, char type_combat){
    
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

    if( type_combat == 'a'){
    
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
            drawModel('k');

        switch(type_enemy){
            case 0:
                drawModel('n');
                break;

            case 1:
                drawModel('m');
                break;
        }

    } else if(type_combat == 'd'){
        
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
    
    TextColor(14); cleanBoard(4, 10, 68, 15);
    gotoxy(5, 11); cout << "* " << Event_Name[event];
    gotoxy(19, 11); cout << "ATK " << monster->Atk;
    gotoxy(27, 11); cout << "LEVEL " << monster->level;
    gotoxy(5, 13); cout << "* " << monster->infor;
}
void Game::cleanBoard(int x1, int y1, int x2, int y2){
    for(int i = y1; i <= y2; i++){
        for(int j = x1; j <= x2; j++){
            gotoxy(j, i); cout << " ";
        }
    }
}
void Game::interact(int event, Knight* knight, Monster* monster, Bullet* bullet, MainCharacter* char_, Item* item, int rescue){

    bool enemyDefeated = false; 
   
    if(event > 10){
        
        switch(event){
            case 11:
            case 12:
            case 13: {

                drawBorder(knight,2, 'a'); 
                gotoxy(55,7); cout << "🍄";
                gotoxy(6, 11); cout << "You have picked a SUS Mushrom!";
                
                TextColor(224); gotoxy(SCREEN_W/2 - 17,SCREEN_H/2 + 3); cout << "|  Eat |";
                TextColor(14);  gotoxy(SCREEN_W/2 + 6,SCREEN_H/2 + 3) ;cout << "| Throw |";
                
                int choice = 1; char c = getch();  
                
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
                            
                            cleanBoard(4 ,10, 68, 15);
                                gotoxy(6, 11); cout << "Your Atk got x2 damage";
                                gotoxy(6, 13); cout << "Attack: " << knight->Atk << " --> " << knight->Atk*2;   
                                knight->Atk *= 2;
                        cin.ignore();

                        break;
                        case 12:
                            cleanBoard(4, 10, 68, 15);
                                dialogue(6, 11, "You recovered 100 HP");

                                    if(knight->HP + 100 > knight->MaxHP) knight->HP = knight->MaxHP;
                                    else knight->HP += 100;

                                gotoxy(6, 13); cout << "HP: " << knight->HP - 100 << " --> " << knight->HP;

                            cin.ignore();
                        break;

                        case 13:
                            cleanBoard(4, 10, 68, 15);

                                gotoxy(6, 11); cout << "You're this->poisoned :D";
                                gotoxy(8, 4); cout << "@_@";
                                knight->isPoisoned();

                                cin.ignore();
                        break;    

                    }
                }
            }
            break;
        
            case 14:
                gotoxy(4, 10); cout << "*You have picked the Aspirin potion"; backpack->addItem(Aspirin);    
            
            break;

            case 15:
                gotoxy(4, 10); cout << "*You have picked the Maidenkiss potion"; backpack->addItem(Maidenkiss);    
            
            break;
        
            case 16:
                gotoxy(4, 10); cout << "*You have picked the PhoenixDowm potion"; backpack->addItem(PhoenixDown);    
            
            break;

            case 17:
                gotoxy(4, 10); cout << "*You have picked the Antidote potion"; backpack->addItem(Antidote);    
            
            break;
        }
        knight->Status();

    } else {
        
        while(!enemyDefeated){
                //player turn
                    while(knight->turn){  

                            drawBorder(knight, true, 'a');

                            switch(knight->currentStatus){
                                case 'p':
                                    gotoxy(6, 11); cout << "*You are in poisoned status effect";
                                    gotoxy(6, 13); cout << "*Use the Antidote potion to remove poison";
                                break;

                                case 'f':
                                    gotoxy(6, 11); cout << "*You are in frog status effect";
                                    gotoxy(6, 13); cout << "*Use the Maidenkiss potion to remove effect";
                                break;

                                case 't':
                                    gotoxy(6, 11); cout << "*You are in tiny status effect";
                                    gotoxy(6, 13); cout << "*Use the MushMario to remove effect";
                                break;

                                default:
                                    gotoxy(6, 11); cout << "*The " << monster->type[event-1]->name << " is blocking your way";
                                break;                                  
                            }

                            if(knight->hasDebuff){
                                if(knight->currentStatus == 'f') drawModel('f');
                                else if(knight->currentStatus == 't') drawModel('t');
                            }
                            
                            switch(choices_box()){
                                
                                case 1: 
                                    
                                    if(knight->currentStatus == 'f'){
                                        gotoxy(6, 11); cout << "*You can not fight in froggy mode";
                                        getch(); knight->turn = 1; 
 
                                    } else {
                                        
                                        animationAttack(knight); gotoxy(SCREEN_W/2+13, 5); cout << knight->level*knight->Atk;
                                        Sleep(500); gotoxy(SCREEN_W/2+13, 5); cout << "    ";
                                        
                                        if(knight->Atk >= monster->type[event-1]->HP){
                                            delete_model('m'); gotoxy(6, 11); cout << "*The enemy is defeated";        
                                            getch(); return;
                                        } else{
                                            monster->type[event-1]->HP -= knight->Atk;
                                            knight->turn = 0;
                                        }

                                    }

                                    break;

                                case 2:

                                    analyse(monster->type[event-1], event); getch(); knight->turn = 1;
                                    break;

                                case 3:
                                    
                                   backpack->showItems(knight);                   
                                   

                                break;

                                case 4:

                                    cleanBoard(4, 10, 68, 15); 
                                    gotoxy(6, 11); cout << "Real hero never run!"; getch();
                                    knight->turn = 1;

                                break;
                            }  

                        if(!knight->turn) monster->type[event-1]-> turn = 1;
                         
                    }
                    
                     while(monster->type[event-1]->turn){

                            drawBorder(knight, true, 'd'); 
                                
                            fight(bullet, char_, knight, monster->type[event-1]);
                            
                            if(knight->HP <= 0){
                                
                                if(backpack->findItem(PhoenixDown)) knight->revieve(backpack);
                            
                                 else gotoxy(6, 11); dialogue(6, 11, "*You died"); getch(); return;
                            } 

                            monster->type[event-1]->turn = 0; knight->turn = 1;
                    }
            knight->Status();
        }
    }
}

int main()
{
   
   
    setcursor(0,0); srand(time(NULL)); 
    system("cls");
    backpack->addItem(Antidote);
    backpack->addItem(Antidote);
    backpack->addItem(Maidenkiss);
    MainCharacter* _main = MainCharacter::init();
    Bullet * _bullet = Bullet::init();
    Game::interact(2, knight, monster, _bullet, _main, nullptr, 0);
}
// 4 68
// 10 15


