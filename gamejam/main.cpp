#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>

double ekrany=sf::VideoMode::getDesktopMode().height,ekranx=sf::VideoMode::getDesktopMode().width;
//double ekranx=1600,ekrany=900;

class Protagonista
{
public:
    sf::Texture tpc;
    sf::Sprite pc;
    void rysuj(int x,int y);
};
void Protagonista::rysuj(int x,int y)
{
    tpc.loadFromFile("box.png");
    pc.setTexture(tpc);
    pc.setScale(ekranx/1600,ekrany/900);
    pc.setPosition(x*100,y*100);
}

int main()
{
    Protagonista gracz;

    srand(time(NULL));
    sf::Event event;
    sf::Clock clock;
    double nowyczas=0,staryczas=0,klatka=0.03f;
    int klatki=0;

    gracz.rysuj(2,1);

    sf::ContextSettings settings;
    settings.antialiasingLevel=16;
    sf::RenderWindow okno(sf::VideoMode(ekranx,ekrany),":v",sf::Style::Fullscreen,settings);
    while(okno.isOpen())
    {
        nowyczas+=clock.restart().asSeconds();
        while(okno.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                okno.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                okno.close();
        }
        if(nowyczas-staryczas>=klatka)
        {
            staryczas=nowyczas;
            klatki++;
            std::cout<<klatki<<std::endl;
        }
        okno.clear(sf::Color::Black);
        okno.draw(gracz.pc);
        okno.display();
    }
    return 0;
}
