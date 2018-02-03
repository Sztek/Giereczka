#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <cmath>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <fstream>

double ekranx=sf::VideoMode::getDesktopMode().width,ekrany=sf::VideoMode::getDesktopMode().height;
//double ekranx=1600,ekrany=900;
double skalax=ekranx/1600,skalay=ekrany/900;

class Protagonista
{
public:
    sf::Texture tpc;
    sf::Sprite pc;
    void rysuj(int x,int y);
};
void Protagonista::rysuj(int x,int y)
{
    tpc.loadFromFile("palk44.png");
    pc.setTexture(tpc);
    pc.setTextureRect(sf::IntRect(100,0, 100,100));
    pc.setScale(skalax,skalay);
    pc.setPosition(x*100*skalax,y*100*skalay);
    pc.setOrigin(50,100);
}

class Mapa
{
public:
    sf::Texture tpodloga;
    sf::Sprite podloga;
    bool sciana;
    char i;
    void rysuj(int x,int y,char t);
};
void Mapa::rysuj(int x,int y,char t)
{
    switch(t)
    {
    case '1':
        i=rand()%2;
        tpodloga.loadFromFile("trawa.png");
        podloga.setTextureRect(sf::IntRect(i*100,0, 100,100));
        sciana=false;
        break;
    case '2':
        tpodloga.loadFromFile("wall.png");
        sciana=true;
        break;
    case '3':
        tpodloga.loadFromFile("wallleft.png");
        sciana=true;
        break;
    case '4':
        tpodloga.loadFromFile("wallright.png");
        sciana=true;
        break;
    case '5':
        tpodloga.loadFromFile("las.png");
        sciana=true;
        break;
    case '6':
        tpodloga.loadFromFile("korona.png");
        sciana=true;
        break;
    default:
        tpodloga.loadFromFile("");
        sciana=false;
        break;
    }
    podloga.setTexture(tpodloga);
    podloga.setScale(skalax,skalay);
    podloga.setPosition(x*100*skalax,y*100*skalay);
}

int main()
{
    std::fstream plik("mapa1.txt",std::ios::in);
    char polozenie[2306];
    plik.read(polozenie,2306);


    sf::Music music;            //muzyka
    music.setVolume(20);
    music.setLoop(true);
    music.openFromFile("riff_3.ogg");
    //music.play();

    Protagonista gracz;         //klasy
    Mapa siatka[2304];

    sf::Vector2i mysz,kursor;          //deklaracje
    sf::Vector2f pozycja,wall;
    std::vector<int>sciezka;
    sf::Event event;
    sf::Clock clock;
    double nowyczas=0,staryczas=0,klatka=0.015f;
    int klatki=0,xx,yy,poz;
    double rup=0,rdown=0,rright=0,rleft=0,k=0;
    bool kolgora=false,koldol=false,kolprawo=false,kollewo=false,reached;

    gracz.rysuj(3,2);           //rysowanko
    for(int i=0; i<64; i++)
        for(int j=0; j<36; j++)
            siatka[j*64+i].rysuj(i,j,polozenie[j*64+i]);

    sf::ContextSettings settings;
    settings.antialiasingLevel=16;
    sf::RenderWindow okno(sf::VideoMode(ekranx,ekrany),":v",sf::Style::Fullscreen,settings);
    while(okno.isOpen())
    {
        nowyczas+=clock.restart().asSeconds();
        pozycja=gracz.pc.getPosition();
        kursor=sf::Mouse::getPosition(okno);
        while(okno.pollEvent(event))
        {
            xx=pozycja.x/100;
            yy=pozycja.y/100;
            poz=(yy*64)+(xx);
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
                reached=false;
                if(rup>=sqrt(8)&&siatka[poz-64].sciana)     //wyszukiwanie drogi
                {

                }
                if(rdown>=sqrt(8)&&siatka[poz+64].sciana)
                {

                }
                if(rright>=sqrt(8)&&siatka[poz+1].sciana)
                {

                }
                if(rleft>=sqrt(8)&&siatka[poz-1].sciana)
                {

                }
            }
        }

        if(nowyczas-staryczas>=klatka)
        {
            staryczas=nowyczas;
            klatki++;

        if(kursor.y<10)     //ruch ekranu
        {
            for(int i=0; i<2304; i++)
                siatka[i].podloga.move(0,5);
            gracz.pc.move(0,5);
        }
        if(kursor.y>ekrany-10)
        {
            for(int i=0; i<2304; i++)
                siatka[i].podloga.move(0,-5);
            gracz.pc.move(0,-5);
        }
        if(kursor.x<10)
        {
            for(int i=0; i<2304; i++)
                siatka[i].podloga.move(5,0);
            gracz.pc.move(5,0);
        }
        if(kursor.x>ekranx-10)
        {
            for(int i=0; i<2304; i++)
                siatka[i].podloga.move(-5,0);
            gracz.pc.move(-5,0);
        }

            for(int i=0; i<2304; i++)        //kolizje
                if(siatka[i].sciana==true)
                {
                    wall=siatka[i].podloga.getPosition();
                    if(wall.x+110*skalax>=pozycja.x&&wall.x-10<pozycja.x)
                    {
                        if(wall.y+110*skalay>=pozycja.y&&wall.y<pozycja.y)
                            kolgora=true;
                        if(wall.y>=pozycja.y&&wall.y<=pozycja.y+5)
                            koldol=true;
                    }
                    if(wall.y<pozycja.y&&wall.y+100*skalay>pozycja.y)
                    {
                        if(wall.x+130*skalax>=pozycja.x&&wall.x<=pozycja.x)
                            kollewo=true;
                        if(wall.x>=pozycja.x&&wall.x<pozycja.x+30*skalax)
                            kolprawo=true;
                    }
                }
            gracz.pc.setTextureRect(sf::IntRect(0,0, 100,100));
            if(!reached)    //ruch paladyna
            {
                reached=true;
            if(mysz.y<pozycja.y&&rup>0&&!kolgora)
            {
                gracz.pc.move(0,-rup);
                gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                reached=false;
            }
            if(mysz.y>pozycja.y&&rdown>0&&!koldol)
            {
                gracz.pc.move(0,rdown);
                gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));
                reached=false;
            }
            if(mysz.x>pozycja.x&&rright>0&&!kolprawo)
            {
                gracz.pc.move(rright,0);
                gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),100,100,100));
                if(rright<=rup)
                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                if(rright<=rdown)
                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));
                reached=false;
            }
            if(mysz.x<pozycja.x&&rleft>0&&!kollewo)
            {
                gracz.pc.move(-rleft,0);
                gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),200,100,100));
                if(rleft<=rup)
                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                if(rleft<=rdown)
                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));
                reached=false;
            }
            }
        }
        kolgora=false;
        koldol=false;
        kolprawo=false;
        kollewo=false;
        okno.clear(sf::Color::Black);
        for(int i=0; i<2304; i++)
            if(siatka[i].podloga.getPosition().x<ekranx+10&&siatka[i].podloga.getPosition().y<ekrany+10&&siatka[i].podloga.getPosition().x>-110&&siatka[i].podloga.getPosition().y>-110)
                okno.draw(siatka[i].podloga);
        okno.draw(gracz.pc);
        okno.display();
    }
    return 0;
}
