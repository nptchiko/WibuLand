#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <list>
#include <conio.h>
#include <windows.h>
using namespace std;

#define width 920
#define height 680


//green_point 320
//hit box area
// w 352    h 351
// x 287    y 222
class Animation {
    public:
        sf::Texture texture;
        sf::Texture sideTexture;
        string currentAnimation;
        float time = 0.0f;
        int currentFrame = 0; 

        void Update(float dt){};
        void Draw(sf::RenderTarget &rt){};
        void ApplyToSprite(sf::Sprite& sprite){};
};
class CharacterSprite : public Animation{

    private:
        float holdTime = 0.2f;
        static constexpr int nFrames = 4;
        sf::IntRect frames[nFrames];
        sf::Sprite _charSprite;
        sf::Sprite sideSprite;
        sf::Vector2f position; // {width / 2 - 400, 230};
        bool is_sideSprite_included = false;

    public:
        CharacterSprite(){};
        CharacterSprite(sf::Vector2f position) : position(position){
            _charSprite.setPosition(position);
            _charSprite.scale(sf::Vector2f(1.5,1.5));
            sideSprite.setPosition({width / 2.0f + 300.0f, 250.0f});
            sideSprite.scale(sf::Vector2f(1.5,1.5));
            
            this->texture.setSmooth(true);
        }
        void ApplyToSprite(sf::Sprite& sprite){
            sprite.setTexture(this->texture);
            sprite.setTextureRect(frames[currentFrame]);

            if(this->is_sideSprite_included){
                sideSprite.setTexture(this->sideTexture);
                sideSprite.setTextureRect({currentFrame*66, 0, 66, 56});
            }
        }
        void Draw(sf::RenderTarget &rt){
            rt.draw(_charSprite);
            if(this->is_sideSprite_included) rt.draw(sideSprite);
        }

        void Update(float dt){
            this->time += dt;

            if(time >= this->holdTime){

                this->time -= this->holdTime;

                if(++currentFrame >= nFrames){
                    if(this->currentAnimation != "Idle")
                        this->Idle();
                    currentFrame = 0;
                }
                
            }
            this->ApplyToSprite(_charSprite);
        }

        void Idle(){
            this->texture.loadFromFile("sprite/craftpix-net-483897-free-knight-character-sprites-pixel-art/Spritesheet 128/Knight_1/Idle.png");
            for(int i = 0; i < nFrames; ++i)
                frames[i] = {i*((int)(this->texture.getSize().x))/nFrames, 0, ((int)(this->texture.getSize().x))/nFrames, (int)(this->texture.getSize().y)};
            this->currentAnimation = "Idle"; is_sideSprite_included = false;
        }
        void Attack(){
            this->texture.loadFromFile("sprite/craftpix-net-483897-free-knight-character-sprites-pixel-art/Spritesheet 128/Knight_1/Attack 2.png");
            this->sideTexture.loadFromFile("sprite/Slash/small_slash_1/slash_spritesheet.png");
            for(int i = 0; i < nFrames; ++i)
                frames[i] = {i*((int)(this->texture.getSize().x))/nFrames, 0, ((int)(this->texture.getSize().x))/nFrames, (int)(this->texture.getSize().y)};
            this->currentAnimation = "Attack"; is_sideSprite_included = true;
            this->currentFrame = 0;
        }
        
};
class EnemySprite : public Animation{

    private:
        float holdTime = 0.2f;
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

                if(++currentFrame >= nFrames){
                  if(++currentFrame >= nFrames){
                    if(this->currentAnimation != "Idle")
                        this->Idle();
                    currentFrame = 0;              
                }
                }

            }
            this->ApplyToSprite(_enemySprite);
        }
        void Idle(){
            this->texture.loadFromFile("sprite/enemy1_idie.png");
            for(int i = 0; i < nFrames; ++i)
                frames[i] = {i*((int)(this->texture.getSize().x))/nFrames, 0, ((int)(this->texture.getSize().x))/nFrames, (int)(this->texture.getSize().y)};
            this->currentAnimation = "Idle";

        }
        
};

class QuickAnimation : public Animation{

    private:
        float holdTime = 0.05f;
        int currentFrame = 0; 
        static constexpr int nFrames = 50;
        sf::IntRect frames[nFrames];
        sf::Sprite _Sprite;
        // {width / 2 - 400, 230};
        sf::Vector2i numFrames;
        bool loop = false;

    public:

        QuickAnimation(){};
        QuickAnimation(sf::Vector2f Position, sf::Vector2i numFrames, bool loop) : numFrames(numFrames), loop(loop){
            _Sprite.setPosition(Position);
            _Sprite.scale(sf::Vector2f(1.0,1.0));
            this->texture.setSmooth(true);
        }
        void ApplyToSprite(sf::Sprite& sprite){
            _Sprite.setTexture(this->texture);
            _Sprite.setTextureRect(frames[currentFrame]);
        }
        void Draw(sf::RenderTarget &rt){
            if(currentFrame >= this->numFrames.x*this->numFrames.y && !this->loop){}
            else rt.draw(_Sprite);
        }
        sf::Vector2f getPosition() const { return _Sprite.getPosition(); }  
        bool IsLoop() const { return this->loop; }
        void Update(float dt, sf::Vector2f position){
            this->time += dt;

            if(this->time >= this->holdTime){

                this->time -= this->holdTime;

                if(++currentFrame >= this->numFrames.x*this->numFrames.y && this->loop)
                     currentFrame = 0;
            }
            this->ApplyToSprite(_Sprite);
            _Sprite.setPosition(position);
            
        }
        void Load(string filename){
            this->texture.loadFromFile(filename);

            int width_t = (this->texture.getSize().x) , height_t = (this->texture.getSize().y);

            if(this->numFrames.x == 1) height_t /= (this->numFrames.y*this->numFrames.x);
            else width_t /= (this->numFrames.x*this->numFrames.y);

            for(int i = 0; i < this->numFrames.y; i++)
                for(int j = 0; j < this->numFrames.x; j++)
                    frames[j + (this->numFrames.x)*i] = { j*width_t, i*height_t, width_t, height_t };
        }
};
class AnimationManager{
    public:
        void multiAnimation(list<Animation*> _animation){

        }
};
void choice_box(sf::RenderWindow& rt,float dt, QuickAnimation &ani, CharacterSprite& _ch){
    static int choice = 1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            if(choice < 4) choice++;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            if(choice > 1) choice--;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
         rt.setFramerateLimit(30); 
        switch(choice){
            case 1:
                _ch.Attack();
            break;
        }
    }
    ani.Update(dt, {(float)(choice*width/5 - 75), (float)(600 + 20.f/2.f)});

    _ch.Update(dt); 
    rt.setFramerateLimit(10); 
    ani.Draw(rt);
    
}
int main()
{
    sf::ContextSettings Setting;
    Setting.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "my gem", sf::Style::Default, Setting);

//--------------------------------BACKGROUND--------------------------//

    sf::RectangleShape background(sf::Vector2f(928,928)); sf::Texture t;
   

    background.setPosition(sf::Vector2f(0, -210));   
    if(t.loadFromFile("sprite/Background4.png")){
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
        boxSprite[i] = new sf::RectangleShape(sf::Vector2f(151.28f, 57));
        boxTexture[i] = new sf::Texture;
        boxSprite[i]->scale(sf::Vector2f(1, 1));
    }

    boxTexture[0]->loadFromFile("sprite/Frame/Fight.png");
        boxSprite[0]->setTexture(boxTexture[0], false);
    boxTexture[1]->loadFromFile("sprite/Frame/Act.png");
        boxSprite[1]->setTexture(boxTexture[1], false);
    boxTexture[2]->loadFromFile("sprite/Frame/Item.png");
        boxSprite[2]->setTexture(boxTexture[2], false);
    boxTexture[3]->loadFromFile("sprite/Frame/Run.png");
        boxSprite[3]->setTexture(boxTexture[3], false);
    

    boxSprite[0]->setPosition(sf::Vector2f(width/5 - 172.5f/2.f, 600));
    boxSprite[1]->setPosition(sf::Vector2f(2*(width/5) - 172.5f/2.f, 600));
    boxSprite[2]->setPosition(sf::Vector2f(3*(width/5) - 172.5f/2.f, 600));
    boxSprite[3]->setPosition(sf::Vector2f(4*(width/5) - 172.5f/2.f, 600));
    

 
    
    int j = 0;

  
sf::Clock clock;

CharacterSprite _char({width / 2 - 400, 130});
_char.Idle();
EnemySprite _enemy({width/2.0f + 325.0f, 220.0f});
_enemy.Idle();
QuickAnimation sword({width/5 - 75, 600 + 20.f/2.f}, {5,2}, true);
//width/5 - 75, 600 + 20.f/2.f
sword.Load("sprite/layer_3.png");
QuickAnimation gawr_blaster({0, 320}, {1, 7}, 1); 
gawr_blaster.Load("sprite/Gawr_Blaster_Spritesheet.png");

sf::Texture _gura_texture; _gura_texture.loadFromFile("sprite/Gawr_intro1.png");
sf::RectangleShape _gura_sprite(sf::Vector2f(_gura_texture.getSize().x, _gura_texture.getSize().y));

_gura_sprite.setTexture(&_gura_texture); _gura_sprite.setPosition(gawr_blaster.getPosition());
_gura_sprite.setOrigin({57.5, 66}); _gura_sprite.setRotation(_gura_sprite.getRotation() - 180);

while (window.isOpen()){


        sf::Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
         }
        
        window.clear();
        window.draw(background);
        for(int i = 0; i < 4; i++)
        window.draw(*boxSprite[i]);
        
        float dt;
        dt = clock.restart().asSeconds();

        if(_gura_sprite.getPosition().x < 100.f) _gura_sprite.move(dt + 0.5, 0);

        if(_gura_sprite.getRotation() > 1) _gura_sprite.rotate(0.725);        

        _enemy.Update(dt);
       // gawr_blaster.Update(dt, gawr_blaster.getPosition());
       
        _enemy.Draw(window);
        _char.Draw(window);       
        //choice_box(window, dt, sword, _char);
       // gawr_blaster.Draw(window);
        
        window.draw(_gura_sprite);
        window.display();
        //window.setFramerateLimit(7);
   }

    return 0;
}