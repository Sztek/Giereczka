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
    tpc.loadFromFile("x.png");
    pc.setTexture(tpc);
    pc.setScale(ekranx/1600,ekrany/900);
    pc.setPosition(x*100,y*100);
    pc.setOrigin(50,100);
    pc.setTextureRect(sf::IntRect(0,0, 100,100));
}

int main()
{
    Protagonista gracz;

    srand(time(NULL));
    sf::Vector2i mysz;
    sf::Vector2f pozycja;
    sf::Event event;
    sf::Clock clock;
    double nowyczas=0,staryczas=0,klatka=0.015f;
    int klatki=0;
    double rup=0,rdown=0,rright=0,rleft=0,k=0;

    gracz.rysuj(2,1);

    sf::ContextSettings settings;
    settings.antialiasingLevel=16;
    sf::RenderWindow okno(sf::VideoMode(ekranx,ekrany),":v",sf::Style::Fullscreen,settings);
    while(okno.isOpen())
    {
        nowyczas+=clock.restart().asSeconds();
        pozycja=gracz.pc.getPosition();
        while(okno.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                okno.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                okno.close();
            if(event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
            {
                mysz=sf::Mouse::getPosition(okno);
                k=(sqrt((pozycja.x-mysz.x)*(pozycja.x-mysz.x)+(pozycja.y-mysz.y)*(pozycja.y-mysz.y)))/4;
                rup=(pozycja.y-mysz.y)/k;
                rdown=(mysz.y-pozycja.y)/k;
                rleft=(pozycja.x-mysz.x)/k;
                rright=(mysz.x-pozycja.x)/k;
            }
        }
        if(nowyczas-staryczas>=klatka)
        {
            staryczas=nowyczas;
            klatki++;

            if(mysz.y<pozycja.y&&rup>0)
                gracz.pc.move(0,-rup);
            if(mysz.y>pozycja.y&&rdown>0)
                gracz.pc.move(0,rdown);
            if(mysz.x>pozycja.x&&rright>0)
                gracz.pc.move(rright,0);
            if(mysz.x<pozycja.x&&rleft>0)
                gracz.pc.move(-rleft,0);
        }
        okno.clear(sf::Color::Black);
        okno.draw(gracz.pc);
        okno.display();
    }
    return 0;
}
