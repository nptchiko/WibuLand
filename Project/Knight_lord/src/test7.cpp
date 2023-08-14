#include "main.h"

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
};
class Monster : public Attribute{
    private:
        int skill_cooldown;
    public:
        static Monster* create(string name,int MaxHP, int HP, float Atk, int level){
            Monster* mons = new Monster();
                mons->name = name;
                mons->MaxHP = MaxHP;
                mons->HP = HP;
                mons->Atk = Atk;
                mons->level = level;

            return mons;
        }
};
void Init(string ten, Attribute* Monsvat)
{
    string s; 
    Monsvat->name = ten;
    ten += ".txt";
    fstream inp(ten);
    inp >> Monsvat->HP >> Monsvat->Atk >> Monsvat->level;
    inp.ignore();
    getline(inp, Monsvat->infor);
}  

int main(){
    Monster* monster = new Monster();
    Init("Troll", monster);
    cout << monster->name;
}