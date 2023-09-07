#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

#define width 920
#define height 680


//green_point 320

class Animation {
    public:
        sf::Texture texture;
        float time = 0.0f;
        float holdTime = 0.3f;
        int currentFrame = 0;  

        void Update(float dt){};
        void Draw(sf::RenderTarget &rt){};
        void ApplyToSprite(sf::Sprite& sprite){};
};
class CharacterSprite : public Animation{

    private:

        static constexpr int nFrames = 4;
        sf::IntRect frames[nFrames];
        sf::Sprite _charSprite;
        sf::Vector2f position; // {width / 2 - 400, 230};

    public:
        CharacterSprite(){};
        CharacterSprite(sf::Vector2f position) : position(position){
            _charSprite.setPosition(position);
            _charSprite.scale(sf::Vector2f(1.5,1.5));
            this->texture.setSmooth(true);
        }
        void ApplyToSprite(sf::Sprite& sprite){
            sprite.setTexture(this->texture);
            sprite.setTextureRect(frames[currentFrame]);
        }
        void Draw(sf::RenderTarget &rt){
            rt.draw(_charSprite);
        }

        void Update(float dt){
            this->time += dt;

            if(time >= this->holdTime){

                this->time -= this->holdTime;

                if(++currentFrame >= nFrames)
                    currentFrame = 0;
            }
            this->ApplyToSprite(_charSprite);
        }

        void Idle(){
            this->texture.loadFromFile("sprite/craftpix-net-483897-free-knight-character-sprites-pixel-art/Spritesheet 128/Knight_1/Idle.png");
            for(int i = 0; i < nFrames; ++i)
                frames[i] = {i*((int)(this->texture.getSize().x))/nFrames, 0, ((int)(this->texture.getSize().x))/nFrames, (int)(this->texture.getSize().y)};
        }
        void Attack(){
            this->texture.loadFromFile("sprite/craftpix-net-483897-free-knight-character-sprites-pixel-art/Spritesheet 128/Knight_1/Attack 2.png");
            for(int i = 0; i < nFrames; ++i)
                frames[i] = {i*((int)(this->texture.getSize().x))/nFrames, 0, ((int)(this->texture.getSize().x))/nFrames, (int)(this->texture.getSize().y)};
        }
        
};
class EnemySprite : public Animation{

    private:

        static constexpr int nFrames = 4;
        sf::IntRect frames[nFrames];
        sf::Sprite _enemySprite;
        sf::Vector2f position; // {width / 2 - 400, 230};

    public:
        EnemySprite(){};
        EnemySprite(sf::Vector2f position) : position(position){
            _enemySprite.setPosition(position);
            _enemySprite.scale(sf::Vector2f(1,1));
            this->texture.setSmooth(true);
        }
        void Idle(){
            Animation::texture.loadFromFile("sprite/enemy1_idie.png");
            for(int i = 0; i < nFrames; ++i)
                frames[i] = {i*((int)(this->texture.getSize().x))/nFrames, 0, ((int)(this->texture.getSize().x))/nFrames, (int)(this->texture.getSize().y)};
        }
        void ApplyToSprite(sf::Sprite& sprite){
            sprite.setTexture(this->texture);
            sprite.setTextureRect(frames[currentFrame]);
        }
        void Draw(sf::RenderTarget &rt){
            rt.draw(_enemySprite);
        }

        void Update(float dt){
            this->time += dt;

            if(this->time >= this->holdTime){

                this->time -= this->holdTime;

                if(++currentFrame >= nFrames)
                    currentFrame = 0;
            }
            this->ApplyToSprite(_enemySprite);
        }
};

int main()
{
    sf::ContextSettings Setting;
    Setting.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "my gem", sf::Style::Default, Setting);

//--------------------------------BACKGROUND--------------------------//

    sf::RectangleShape background(sf::Vector2f(width,1116)); sf::Texture t;
    background.setPosition(sf::Vector2f(0, -400));   
    if(t.loadFromFile("sprite/Background.png")){
        cout << "Loading background successfully..." << endl;
        background.setTexture(&t, false);
    } else cout << "Loading failed..." << endl;
    
//------------------------------PLAYER/ENEMY--------------------------//



//-----------------------------TEXT--------------------------------------//
sf::Font font;
    sf::Text text;

    font.loadFromFile("breathe-fire-font/BreatheFire-65pg.ttf");
    text.setFont(font);
    text.setString("Chiko");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

//----------------------------SOMETHING-----------------------------------//

    sf::Texture* boxTexture[4];
    sf::RectangleShape* boxSprite[4]; 
    for(int i = 0; i < 4; i++){
        boxSprite[i] = new sf::RectangleShape(sf::Vector2f(151, 56));
        boxTexture[i] = new sf::Texture;
        boxSprite[i]->scale(sf::Vector2f(1, 1));
    }

    boxTexture[0]->loadFromFile("sprite/Frame/Fight.png");
        boxSprite[0]->setTexture(boxTexture[0], false);
    boxTexture[1]->loadFromFile("sprite/Frame/ActNoSword.png");
        boxSprite[1]->setTexture(boxTexture[1], false);
    boxTexture[2]->loadFromFile("sprite/Frame/ItemNoSword.png");
        boxSprite[2]->setTexture(boxTexture[2], false);
    boxTexture[3]->loadFromFile("sprite/Frame/RunNoSword.png");
        boxSprite[3]->setTexture(boxTexture[3], false);
    

    boxSprite[0]->setPosition(sf::Vector2f(width/2 -18 - 151 - 37 - 151, 600));
    boxSprite[1]->setPosition(sf::Vector2f(width/2 - 18 - 151, 600));
    boxSprite[2]->setPosition(sf::Vector2f(width/2 + 18, 600));
    boxSprite[3]->setPosition(sf::Vector2f(width/2 + 18 + 151 + 37, 600));
    

 
    
    int j = 0;

int choice = 1;    
sf::Clock clock;

CharacterSprite _char({width / 2 - 400, 130});
_char.Attack();
EnemySprite _enemy({width/2.0f + 325.0f, 220.0f});
_enemy.Idle();

while (window.isOpen()){

        sf::Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        
        float dt;
        dt = clock.restart().asSeconds();

 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && choice < 4)  choice++;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && choice > 1) choice--;

        switch(choice){
            case 1:
                boxTexture[0]->loadFromFile("sprite/Frame/Fight.png");
                    boxSprite[0]->setTexture(boxTexture[0], false);
                boxTexture[1]->loadFromFile("sprite/Frame/ActNoSword.png");
                    boxSprite[1]->setTexture(boxTexture[1], false);
            break;

            case 2:
                boxTexture[0]->loadFromFile("sprite/Frame/FightNoSword.png");
                    boxSprite[0]->setTexture(boxTexture[0], false);
                boxTexture[1]->loadFromFile("sprite/Frame/Act.png");
                    boxSprite[1]->setTexture(boxTexture[1], false);
                boxTexture[2]->loadFromFile("sprite/Frame/ItemNoSword.png");
                    boxSprite[2]->setTexture(boxTexture[2], false);              
            break;

            case 3:
                boxTexture[1]->loadFromFile("sprite/Frame/ActNoSword.png");
                    boxSprite[1]->setTexture(boxTexture[1], false);
                boxTexture[2]->loadFromFile("sprite/Frame/Item.png");
                    boxSprite[2]->setTexture(boxTexture[2], false);
                boxTexture[3]->loadFromFile("sprite/Frame/RunNoSword.png");
                    boxSprite[3]->setTexture(boxTexture[3], false);  
            break;

            case 4:
                boxTexture[2]->loadFromFile("sprite/Frame/ItemNoSword.png");
                    boxSprite[2]->setTexture(boxTexture[2], false);
                boxTexture[3]->loadFromFile("sprite/Frame/Run.png");
                    boxSprite[3]->setTexture(boxTexture[3], false); 
            break;

        }

        j++; if(j == 4) j = 0;

        _char.Update(dt);
        _enemy.Update(dt);

        window.clear();
        window.draw(background);
        _char.Draw(window);
        _enemy.Draw(window);
        for(int i = 0; i < 4; i++)
            window.draw(*boxSprite[i]);
     
        //window.draw(*playerSprite[0]);
        window.display();
        //window.setFramerateLimit(7);
        cout << "frame: " << dt << endl;
    }

    return 0;
}