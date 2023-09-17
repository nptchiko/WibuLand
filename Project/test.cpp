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
        float delaytime;

        static Audio* init(string filename){
            Audio* a = new Audio();
                a->sb.loadFromFile(filename);
                a->sound.setBuffer(a->sb);
                a->delaytime = a->sb.getDuration().asSeconds();
            return a;
        }
        void play(){
            this->sound.play();
        }
        void Update(float dt, float extraTime){
            if(this->delaytime == this->sb.getDuration().asSeconds())
                this->delaytime += extraTime;

            if(this->delaytime > 0)
                this->delaytime -= dt;

            if(this->delaytime <= 0){
                this->delaytime = this->sb.getDuration().asSeconds();
                play();
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
    
    vector<Audio*> Gawr_Blaster;

    Gawr_Blaster.push_back(Audio::init("sprite/Sounds_gasterintro.wav"));
    Gawr_Blaster.push_back(Audio::init("sprite/Sounds_gasterfire.wav"));

     
    

    float time = 0;  sf::Clock clock;     

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonPressed){
                   Gawr_Blaster[0]->play(); Sleep(1000); Gawr_Blaster[1]->play();
                }
            }
        float dt;
        dt = clock.restart().asSeconds();    
        

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