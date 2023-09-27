#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <vector>
#include <cassert>
#include <list>
using namespace std;
class Audio{
    private:
        sf::Sound sound;
        sf::SoundBuffer sb;

    public:
        bool isPlayed;   

    public:

        static Audio* init(string filename){
            Audio* a = new Audio();
                a->sb.loadFromFile(filename);
                a->sound.setBuffer(a->sb);
                a->isPlayed = false;
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
        sf::SoundSource::Status getStatus(){
            return this->sound.getStatus();
        } 
        void delay(float Pre_Sound_Dur, float dt){
            static float loading_time = 0;

            if(loading_time < Pre_Sound_Dur && loading_time >= 0) loading_time += dt;
            else if(loading_time >= Pre_Sound_Dur){
                play(); loading_time = -1;
            }

        }
};

class AudioManager{
    private:
        sf::SoundSource::Status current_status = sf::SoundSource::Stopped;
    public:
        void Merge_Play(list<Audio*> radio){
            

            if(radio.front()->getStatus() == sf::SoundSource::Stopped && this->current_status == sf::SoundSource::Playing){

                //radio.remove_if( [](Audio* s){return (s->getStatus() == sf::SoundSource::Stopped);});
                radio.pop_front();

                if(radio.empty()){
                    return;
                } 
                this->current_status = sf::SoundSource::Stopped;
            }

            if(radio.front()->getStatus() == sf::SoundSource::Stopped && radio.front()->isPlayed == false){
                radio.front()->play(); this->current_status = sf::SoundSource::Playing;
                radio.front()->isPlayed = true;
            }
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
    
    list<Audio*> Gawr_Blaster;

    Gawr_Blaster.push_back(Audio::init("sprite/Sounds_gasterintro.wav"));
    Gawr_Blaster.push_back(Audio::init("sprite/Sounds_gasterfire.wav"));


    AudioManager radio;
     

    float time = 0;  sf::Clock clock;     

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float dt;
        dt = clock.restart().asSeconds();    
      
       
       // manager->playRespectively(Gawr_Blaster, dt);

    

       radio.Merge_Play(Gawr_Blaster);  
      
      //  else if(Gawr_Blaster[0]->Status(sf::SoundSource::Stopped)) Gawr_Blaster[1]->play();    

       

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