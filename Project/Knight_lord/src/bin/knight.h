#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "main.h"

class Item{

    public:
        string name;
        unsigned int quantity;
        

        Item(){};
        ~Item(){};

        Item(string name, unsigned int quantity);
        friend class ItemManager;

};
class Potion : public Item {
    public:
        Potion(string name, unsigned int quantity);
        static Potion* createPotion(string name, unsigned int quantity);
       

};
class ItemManager{
    public: 
        vector<Item*> items;

        ItemManager(){};
        ~ItemManager(){};

        Item* findItem(Item* item);
        void addItem(Item* item);   
        void removeItem(Item* item);
        void showItems(Knight* knight);
};

class Attribute{
    public:   
        int MaxHP;
        int HP;
        int level;
        float Atk;
        bool turn;
        string name;
        string infor;

        Attribute(){};
        ~Attribute(){};

        Attribute(string name,int MaxHP, int HP, float Atk, int level, bool turn, string infor);
    
};
class Knight : public Attribute{
    protected:      
        int tiny = 0;
        int poisoned = 0;
        int frog = 0;
        int tempValue;
        
        

    
    public: 
        bool hasDebuff;
        char currentStatus;

        static Knight * init();

        void isPoisoned();
        void isFrogged();
        void getSmallen();
        void Status(); 
        void useItem(Item* item_to_use, ItemManager* balo); 
        void revieve(ItemManager* balo);  
        
        friend class Game;
        
};
class Monster : public Attribute{
    public:
        vector<Monster*> type;
        int skill_cooldown;

    public:
        Monster(){};
        Monster(string name,int MaxHP, int HP, float Atk, int level, bool turn, string infor); 
        
        static Monster* init();
        
        void skill(int event, Knight* knight);
        
        friend class Game;
};
class NPC : public Attribute{

};
class Object {
    public:   
        int x;
        int y;

        Object(){};
        ~Object(){};

        virtual void draw() const{};
        virtual void erase() const{};
};
class MainCharacter : public Object {
    private:
        char (*model_c)[Model_c_X_Length];
    
    public:
        
        MainCharacter(){};
        ~MainCharacter(){};

        static MainCharacter* init();
    
        void draw() const;
        void erase() const;
        friend class Game;
};
class Bullet : public Object {
   private:
        char (*model_b)[Model_b_X_Length];
        int damage;
        bool isReady;

   public:
        
        Bullet(){};
        ~Bullet(){};

        static Bullet* init();   
        
        void draw() const;
        void erase() const;
        void generate();
        void reset();
        void collision(int i, Bullet* bullet, MainCharacter* mc, Knight* knight);

        friend class Game;
};
class Game{
    public:
       static void dialogue(short x ,short y, string s);
       static void interact(int event, Knight* knight,Monster* monster, Bullet* bullet, MainCharacter* char_, Item* item, int rescue);
       static void cleanBoard(int x, int y, int _x, int _y);
       static void init(string name, Attribute* Object);
       static void analyse(Monster* monster, int event);
       static void drawBorder(Knight* knight, int type_enemy ,char type_combat);
       static void fight(Bullet* bullet, MainCharacter* char_, Knight* knight, Monster* monster);
       static void animationAttack(Knight* knight);
       static int choices_box();
       static void drawModel(char type);
       static void intro(Knight* knight);
       static void delete_model(char type);
};

void setcursor(bool visible, DWORD size);
void TextColor(int x);
void gotoxy(short x, short y);

Knight* knight = Knight::init();
#endif