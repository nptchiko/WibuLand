#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <vector>
using namespace std;


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
    
    sf::Texture t_beam; t_beam.loadFromFile("sprite/Gawr_Blaster_Spritesheet.png");

    sf::RectangleShape beam(sf::Vector2f(t_beam.getSize().x, t_beam.getSize().y/7)); 
    
   beam.setTexture(&t_beam, false);
    beam.setPosition(0, 329);
    int i =0;
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
        beam.setTextureRect({0, i*924/7, 1125, 924/7});

       if(++i >= 7) i = 0;

        window.draw(background);window.draw(beam);
        window.display();
        window.setFramerateLimit(30);
 
    }
    
    return 0;
}