#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>

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
    pc.setPosition(x,y);
}

int main()
{
    Protagonista gracz;

    srand(time(NULL));
    int ekrany=sf::VideoMode::getDesktopMode().height,ekranx=sf::VideoMode::getDesktopMode().width;
    sf::Event event;
    sf::Clock clock;
    double czas=0,klatka=0.03f;
    int klatki=0;

    gracz.rysuj(0,0);

    sf::ContextSettings settings;
    settings.antialiasingLevel=16;
    sf::RenderWindow okno(sf::VideoMode(ekranx,ekrany),":v",sf::Style::Fullscreen,settings);
    while(okno.isOpen())
    {
        czas+=clock.restart().asSeconds();
        while(okno.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                okno.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                okno.close();
        }
        if(czas>klatka)
        {
            czas-=klatka;
            klatki++;
        }
        okno.clear(sf::Color::Black);
        okno.draw(gracz.pc);
        okno.display();
    }
    return 0;
}
