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
    int hp,zamach,dmg,droga,aps;
    bool atak,atakowany;
    sf::Texture tpc;
    sf::Sprite pc;
    void rysuj(int x,int y);
    void napoleon(int x,int y);
};
void Protagonista::rysuj(int x,int y)
{
    tpc.loadFromFile("palk44.png");
    pc.setTexture(tpc);
    pc.setTextureRect(sf::IntRect(100,0, 100,100));
    pc.setScale(skalax,skalay);
    pc.setPosition(x*100*skalax,y*100*skalay);
    pc.setOrigin(50,100);
    hp=10;
    aps=10;
    droga=0;
    dmg=1;
    atak=false;
    atakowany=false;
}
void Protagonista::napoleon(int x,int y)
{
    tpc.loadFromFile("palk3.png");
    pc.setTexture(tpc);
    pc.setScale(skalax,skalay);
    pc.setPosition(x*100*skalax,y*100*skalay);
    pc.setOrigin(50,50);
    hp=3;
    aps=120;
    dmg=1;
    atak=false;
    atakowany=false;
}

class Serce
{
public:
    sf::Texture thrth;
    sf::Sprite hrth;
    void rysuj(int i);
};
void Serce::rysuj(int i)
{
    thrth.loadFromFile("hearth.png");
    hrth.setTexture(thrth);
    hrth.setScale(2,2);
    hrth.setPosition(i*24+2,0);
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
    Protagonista wrog[25];
    Mapa siatka[2304];

    sf::Vector2i mysz,kursor;          //deklaracje
    sf::Vector2f pozycja,wall,przeciwnik;
    std::vector<int>sciezka;
    sf::Event event;
    sf::Clock clock;
    double nowyczas=0,staryczas=0,klatka=0.015f;
    int klatki=0,odleglosc;
    double rup=0,rdown=0,rright=0,rleft=0,k=0,reup=0,redown=0,reright=0,releft=0;
    bool kolgora=false,koldol=false,kolprawo=false,kollewo=false,reached;
    static int rk=10;//ruch kamery

    gracz.rysuj(3,2);           //rysowanko
    for(int i=0; i<64; i++)
        for(int j=0; j<36; j++)
            siatka[j*64+i].rysuj(i,j,polozenie[j*64+i]);
    for(int i=0; i<25; i++)
        wrog[i].napoleon(5,10+i);

    Serce zycie[gracz.hp];
    for(int i=0; i<gracz.hp; i++)
        zycie[i].rysuj(i);

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
                for(int i=0; i<25; i++)
                {
                    przeciwnik=wrog[i].pc.getPosition();
                    if(mysz.x>przeciwnik.x-30*skalax&&mysz.x<przeciwnik.x+30*skalax&&mysz.y>przeciwnik.y-50*skalay&&mysz.y<przeciwnik.y+50*skalay)
                        wrog[i].atakowany=true;
                    else
                        wrog[i].atakowany=false;
                }
            }
        }

        if(nowyczas-staryczas>=klatka)
        {
            staryczas=nowyczas;
            klatki++;

            for(int i=0; i<25; i++)
                if(wrog[i].hp>0)
                {
                    przeciwnik=wrog[i].pc.getPosition();
                    odleglosc=sqrt((pozycja.x-przeciwnik.x)*(pozycja.x-przeciwnik.x)+(pozycja.y-przeciwnik.y)*(pozycja.y-przeciwnik.y));
                    reup=(pozycja.y-przeciwnik.y)/(odleglosc/4);
                    redown=(przeciwnik.y-pozycja.y)/(odleglosc/4);
                    releft=(pozycja.x-przeciwnik.x)/(odleglosc/4);
                    reright=(przeciwnik.x-pozycja.x)/(odleglosc/4);
                    if(odleglosc<600&&!wrog[i].atak)
                    {
                        if(odleglosc>400)
                        {
                            if(przeciwnik.y<pozycja.y&&reup>0)
                            {
                                wrog[i].pc.move(0,reup);
                                //gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                            }
                            if(przeciwnik.y>pozycja.y&&redown>0)
                            {
                                wrog[i].pc.move(0,-redown);
                                //gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));
                            }
                            if(przeciwnik.x>pozycja.x&&reright>0)
                            {
                                wrog[i].pc.move(-reright,0);
                                /*gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),100,100,100));
                                if(rright<=rup)
                                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                                if(rright<=rdown)
                                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));*/
                            }
                            if(przeciwnik.x<pozycja.x&&releft>0)
                            {
                                wrog[i].pc.move(releft,0);
                                /*gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),200,100,100));
                                if(rleft<=rup)
                                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                                if(rleft<=rdown)
                                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));*/
                            }
                        }
                        else
                        {
                            wrog[i].atak=true;
                            wrog[i].zamach=klatki;
                        }
                    }
                    if(wrog[i].atak)
                    {
                        if(wrog[i].zamach+wrog[i].aps<=klatki)
                        {
                            wrog[i].atak=false;
                            if(odleglosc<800)
                                gracz.hp-=wrog[i].dmg;
                        }
                    }
                    if(wrog[i].atakowany&&odleglosc<50&&klatki%gracz.aps==0)
                        wrog[i].hp-=gracz.dmg;
                }


            if(kursor.y<10)     //ruch ekranu
            {
                for(int i=0; i<2304; i++)
                    siatka[i].podloga.move(0,rk);
                gracz.pc.move(0,rk);
                for(int i=0; i<25; i++)
                    wrog[i].pc.move(0,rk);
            }
            if(kursor.y>ekrany-10)
            {
                for(int i=0; i<2304; i++)
                    siatka[i].podloga.move(0,-rk);
                gracz.pc.move(0,-rk);
                for(int i=0; i<25; i++)
                    wrog[i].pc.move(0,-rk);
            }
            if(kursor.x<10)
            {
                for(int i=0; i<2304; i++)
                    siatka[i].podloga.move(rk,0);
                gracz.pc.move(rk,0);
                for(int i=0; i<25; i++)
                    wrog[i].pc.move(rk,0);
            }
            if(kursor.x>ekranx-10)
            {
                for(int i=0; i<2304; i++)
                    siatka[i].podloga.move(-rk,0);
                gracz.pc.move(-rk,0);
                for(int i=0; i<25; i++)
                    wrog[i].pc.move(-rk,0);
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
                if(rup>0&&!kolgora)
                {
                    gracz.pc.move(0,-rup);
                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                    reached=false;
                }
                if(rdown>0&&!koldol)
                {
                    gracz.pc.move(0,rdown);
                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));
                    reached=false;
                }
                if(rright>0&&!kolprawo)
                {
                    gracz.pc.move(rright,0);
                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),100,100,100));
                    if(rright<=rup)
                        gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                    if(rright<=rdown)
                        gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));
                    reached=false;
                }
                if(rleft>0&&!kollewo)
                {
                    gracz.pc.move(-rleft,0);
                    gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),200,100,100));
                    if(rleft<=rup)
                        gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                    if(rleft<=rdown)
                        gracz.pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));
                    reached=false;
                }
                gracz.droga+=sqrt(pow(rup,2)+pow(rright,2));
                if(gracz.droga>=k*4)
                {
                    reached=true;
                    gracz.droga=0;
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
        for(int i=0; i<25; i++)
            if(wrog[i].hp>0)
                okno.draw(wrog[i].pc);
        if(gracz.hp>0)
            okno.draw(gracz.pc);
        for(int i=0; i<gracz.hp; i++)
            okno.draw(zycie[i].hrth);
        okno.display();
    }
    return 0;
}
