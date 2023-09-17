#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <vector>
using namespace std;
class Audio{
    private:
        sf::Sound sound;
        sf::SoundBuffer sb;
    
    public:

        static Audio* init(string filename){
            Audio* a = new Audio();
                a->sb.loadFromFile(filename);
                a->sound.setBuffer(a->sb);
            return a;
        }
        void play(){
            this->sound.play();
        }
        void pause(){
            this->sound.pause();
        }
        float GetDuration() const {
            return this->sb.getDuration().asSeconds();
        }
        void Update(float Pre_Sound_Dur, float dt){
            static float loading_time = 0;

            if(loading_time < Pre_Sound_Dur) loading_time += dt;
            else if(loading_time >= Pre_Sound_Dur){
                play(); loading_time = 0;
                return ;
            }

        }
        void playRespectively(vector<Audio*> sfx, float dt){
        
            static float LOADING_TIME = 0; static int index = 0;
            if(index >= sfx.size()) return;

            if(LOADING_TIME + dt >= sfx[index]->GetDuration() && index != 0){
                LOADING_TIME = 0; ++index;
            } else if(LOADING_TIME + dt >= sfx[sfx.size()- 1]->GetDuration()){
                sfx[sfx.size()- 1]->Update(sfx.size()- 2, dt);
                LOADING_TIM
            }

            if(!index){ sfx[index]->Update(0, dt); ++index;}
            else sfx[index]->Update(sfx[index - 1]->GetDuration(), dt);
        }
};

int main(){
   
    sf::ContextSettings Setting;
    Setting.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(920, 680), "my gem", sf::Style::Default, Setting);

//--------------------------------BACKGROUND--------------------------//
    
    sf::RectangleShape background(sf::Vector2f(920,928)); sf::Texture t;
    background.setPosition(sf::Vector2f(0, -210));   
    if(t.loadFromFile("sprite/Background4.png")){
        cout << "Loading background successfully..." << endl;
        background.setTexture(&t, false);
    } else cout << "Loading failed..." << endl;
    
    sf::Texture t_beam; t_beam.loadFromFile("sprite/test_beam.png");

    sf::RectangleShape beam(sf::Vector2f(t_beam.getSize().x, t_beam.getSize().y)); 
    
    
    beam.setTexture(&t_beam, false);
    beam.setOrigin({57.5, 66});
    beam.setPosition({460,340}); 
    
    vector<Audio*> Gawr_Blaster;

    Gawr_Blaster.push_back(Audio::init("sprite/Sounds_gasterintro.wav"));
    Gawr_Blaster.push_back(Audio::init("sprite/Sounds_gasterfire.wav"));

    Audio* manager = new Audio();
    
    
    float time = 0;  sf::Clock clock;     

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonPressed){
                   
                }
            }
        float dt;
        dt = clock.restart().asSeconds();    
        cout << "fps: " << dt << endl;
       
        manager->playRespectively(Gawr_Blaster, dt);
       

        beam.move({(float)50.0*cos(time),(float)50.0*sin(time)});
        beam.rotate(10);
        if(beam.getPosition().x >= 920) beam.setPosition({0, beam.getPosition().y});
        else if(beam.getPosition().x <= 0) beam.setPosition({920, beam.getPosition().y});
        window.clear(sf::Color::White);
        
        if(time >= 6.18) time = 0;

        time += 3.14159/8;

        window.draw(background);window.draw(beam);
        window.display();
        window.setFramerateLimit(60);
 
    }
    
    return 0;
}