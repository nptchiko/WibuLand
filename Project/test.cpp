#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int main(){

    sf::ContextSettings Setting;
    Setting.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(400, 400), "my gem", sf::Style::Default, Setting);

    sf::Texture* texture[4];
    for(int i = 0; i < 4; ++i) texture[i] = new sf::Texture;

    texture[0]->loadFromFile("sprite/Slash/small_slash_1/slash_5.png");
    texture[1]->loadFromFile("sprite/Slash/small_slash_1/slash_6.png");
    texture[2]->loadFromFile("sprite/Slash/small_slash_1/slash_7.png");
    texture[3]->loadFromFile("sprite/Slash/small_slash_1/slash_8.png");

    sf::Sprite sprite;
    sprite.setTexture(*texture[0]);
    sprite.setPosition({0,0});
    sprite.scale({1.5,1.5});

    int i = 0;
while (window.isOpen()){

        sf::Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        sprite.setTexture(*texture[i]);
        

        while(++i >= 4){
            i = 0;
        } 

        window.clear();

        window.draw(sprite);

        //window.draw(*playerSprite[0]);
        window.display();
        window.setFramerateLimit(5);
      
    }
}