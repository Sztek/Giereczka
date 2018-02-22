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
#include <string>

double ekranx=sf::VideoMode::getDesktopMode().width,ekrany=sf::VideoMode::getDesktopMode().height;
//double ekranx=1600,ekrany=900;
double skalax=ekranx/1600,skalay=ekrany/900;

class Protagonista
{
public:
    int hp,zamach,dmg,droga,aps;
    bool atak,atakowany;
    bool kolgora,koldol,kolprawo,kollewo;
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
    tpc.loadFromFile("siatkanapoleona.png");
    pc.setTexture(tpc);
    pc.setTextureRect(sf::IntRect(100,0, 100,100));
    pc.setScale(skalax,skalay);
    pc.setPosition(x*100*skalax,y*100*skalay);
    pc.setOrigin(50,50);
    hp=3;
    aps=120;
    dmg=1;
    atak=false;
    atakowany=false;
    kolgora=false;
    koldol=false;
    kolprawo=false;
    kollewo=false;
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
int icel;
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
    case '.':
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
        tpodloga.loadFromFile("tree1.png");
        sciana=true;
        break;
    case '1':
        tpodloga.loadFromFile("tree2.png");
        sciana=true;
        break;
    case '6':
        tpodloga.loadFromFile("korona.png");
        sciana=true;
        break;
    case '7':
        tpodloga.loadFromFile("treer2.png");
        sciana=true;
        break;
    case '8':
        tpodloga.loadFromFile("treer1.png");
        sciana=true;
        break;
    case '9':
        tpodloga.loadFromFile("korona2.png");
        sciana=true;
        break;
    case '0':
        tpodloga.loadFromFile("drzewo1.png");
        sciana=true;
        break;
    case 'q':
        tpodloga.loadFromFile("drzewo2.png");
        sciana=true;
        break;
    case 'Q':
        tpodloga.loadFromFile("drzewo.png");
        sciana=true;
        break;
    case 'w':
        tpodloga.loadFromFile("drzewo3.png");
        sciana=true;
        break;
    case 'W':
        tpodloga.loadFromFile("drzewo4.png");
        sciana=true;
        break;
    case 'a':
        tpodloga.loadFromFile("drzewo5.png");
        sciana=true;
        break;
    case 'd':
        tpodloga.loadFromFile("drewno1.png");
        sciana=true;
        break;
    case 'D':
        tpodloga.loadFromFile("drewnodrzwi.png");
        sciana=true;
        break;
    case 'f':
        tpodloga.loadFromFile("dach1.png");
        sciana=true;
        break;
    case 'k':
        tpodloga.loadFromFile("klif1.png");
        sciana=true;
        break;
    case 'j':
        tpodloga.loadFromFile("klif3.png");
        sciana=false;
        break;
    case 'l':
        tpodloga.loadFromFile("klif2.png");
        sciana=false;
        break;
    case ',':
        tpodloga.loadFromFile("plyty.png");
        sciana=false;
        break;
    case 'F':
        tpodloga.loadFromFile("dach2.png");
        sciana=true;
        break;
    case '*':
        tpodloga.loadFromFile("klatki.png");
        podloga.setTextureRect(sf::IntRect((icel)*100,0, 100,100));
        icel++;
        sciana=true;
        break;
    case 'c':
        tpodloga.loadFromFile("kraty.png");
        sciana=true;
        break;
    case '#':
        tpodloga.loadFromFile("kratki.png");
        podloga.setTextureRect(sf::IntRect(100,0, 100,100));
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

std::string intToStr(int n)
{
    std::string tmp;
    if(n < 0)
    {
        tmp = "-";
        n = -n;
    }
    if(n > 9)
        tmp += intToStr(n / 10);
    tmp += n % 10 + 48;
    return tmp;
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel=16;
    sf::RenderWindow okno(sf::VideoMode(ekranx,ekrany),":v",sf::Style::Fullscreen,settings);

    int procenty;
    sf::Font fnt;
    fnt.loadFromFile("paladin.ttf");
    sf::Text loading;
    loading.setCharacterSize(30);
    loading.setFont(fnt);
    loading.setFillColor(sf::Color::Black);
    loading.setPosition(ekranx-200,ekrany-150);
    sf::Texture tmap;
    sf::Sprite smap;
    tmap.loadFromFile("loadingscreen.png");
    smap.setTexture(tmap);
    smap.setScale(skalax,skalay);

    sf::Music music;            //muzyka
    music.setVolume(20);
    music.setLoop(true);
    music.openFromFile("riff_3.ogg");
    music.play();

    Protagonista gracz;         //klasy
    Protagonista wrog[25];
    Mapa siatka[2304];

    sf::Vector2i mysz,kursor;          //deklaracje
    sf::Vector2f pozycja,wall,przeciwnik;
    std::vector<int>sciezka;
    sf::Event event;
    sf::Clock clock;
    double nowyczas=0,staryczas=0,klatka=0.015f;
    int mapka=1,klatki=0,odleglosc,poz,punkty=0;
    double rup=0,rdown=0,rright=0,rleft=0,k=0,reup=0,redown=0,reright=0,releft=0;
    bool kolgora=false,koldol=false,kolprawo=false,kollewo=false,reached,ruch=false,uwolniony[3];
    char polozenie[2304];
    static int rk=10;//ruch kamery
    gracz.rysuj(0,0);
    Serce zycie[gracz.hp];

    while(mapka<=3)
    {
    if(mapka==1)
    {
        icel=1;
        punkty=0;
        uwolniony[0]=false;
        uwolniony[1]=false;
        uwolniony[2]=false;
        std::fstream plik("mapa1.txt",std::ios::in);
        plik.read(polozenie,2304);
        procenty=0;
        for(int i=0; i<64; i++)
            for(int j=0; j<36; j++)
                {
                    siatka[j*64+i].rysuj(i,j,polozenie[j*64+i]);
                    procenty++;
                    loading.setString(intToStr(procenty*100/2304)+"%");
                    okno.clear(sf::Color::Black);
                    okno.draw(smap);
                    okno.draw(loading);
                    okno.display();
                }
    gracz.rysuj(3,2);
    wrog[0].napoleon(50,34);
    wrog[1].napoleon(5,31);
    wrog[2].napoleon(8,30);
    wrog[3].napoleon(11,31);
    wrog[4].napoleon(60,12);
    wrog[5].napoleon(57,12);
    wrog[6].napoleon(61,11);
    wrog[7].napoleon(9,12);
    wrog[8].napoleon(7,11);
    wrog[9].napoleon(16,17);
    wrog[10].napoleon(18,16);
    wrog[11].napoleon(10,19);
    wrog[12].napoleon(40,1);
    wrog[13].napoleon(60,6);
    wrog[14].napoleon(57,7);
    wrog[15].napoleon(53,22);
    wrog[16].napoleon(50,25);
    wrog[17].napoleon(55,27);
    wrog[18].napoleon(46,26);
    wrog[19].napoleon(59,26);
    wrog[20].napoleon(43,16);
    wrog[21].napoleon(52,30);
    wrog[22].napoleon(31,32);
    wrog[23].napoleon(32,31);
    wrog[24].napoleon(27,18);
    for(int i=0; i<gracz.hp; i++)
        zycie[i].rysuj(i);
    }
    if(mapka==2)
    {
        icel=1;
        punkty=0;
        uwolniony[0]=false;
        uwolniony[1]=false;
        uwolniony[2]=false;
        std::fstream plik("mapa2.txt",std::ios::in);
        plik.read(polozenie,2304);
        procenty=0;
        for(int i=0; i<64; i++)
            for(int j=0; j<36; j++)
                {
                    siatka[j*64+i].rysuj(i,j,polozenie[j*64+i]);
                    procenty++;
                    loading.setString(intToStr(procenty*100/2304)+"%");
                    okno.clear(sf::Color::Black);
                    okno.draw(smap);
                    okno.draw(loading);
                    okno.display();
                }
    gracz.rysuj(3,2);
    wrog[0].napoleon(5,26);
    wrog[1].napoleon(5,31);
    wrog[2].napoleon(8,30);
    wrog[3].napoleon(11,31);
    wrog[4].napoleon(60,12);
    wrog[5].napoleon(57,12);
    wrog[6].napoleon(61,11);
    wrog[7].napoleon(9,12);
    wrog[8].napoleon(7,11);
    wrog[9].napoleon(16,17);
    wrog[10].napoleon(18,16);
    wrog[11].napoleon(10,19);
    wrog[12].napoleon(40,1);
    wrog[13].napoleon(60,6);
    wrog[14].napoleon(57,7);
    wrog[15].napoleon(53,22);
    wrog[16].napoleon(50,25);
    wrog[17].napoleon(55,27);
    wrog[18].napoleon(46,26);
    wrog[19].napoleon(59,26);
    wrog[20].napoleon(43,16);
    wrog[21].napoleon(52,30);
    wrog[22].napoleon(31,32);
    wrog[23].napoleon(32,31);
    wrog[24].napoleon(27,18);
    for(int i=0; i<gracz.hp; i++)
        zycie[i].rysuj(i);
    }
    if(mapka==3)
    {
        icel=1;
        punkty=0;
        uwolniony[0]=false;
        uwolniony[1]=false;
        uwolniony[2]=false;
        std::fstream plik("mapa3.txt",std::ios::in);
        plik.read(polozenie,2304);
        procenty=0;
        for(int i=0; i<64; i++)
            for(int j=0; j<36; j++)
                {
                    siatka[j*64+i].rysuj(i,j,polozenie[j*64+i]);
                    procenty++;
                    loading.setString(intToStr(procenty*100/2304)+"%");
                    okno.clear(sf::Color::Black);
                    okno.draw(smap);
                    okno.draw(loading);
                    okno.display();
                }
    gracz.rysuj(3,2);
    wrog[0].napoleon(5,26);
    wrog[1].napoleon(5,31);
    wrog[2].napoleon(8,30);
    wrog[3].napoleon(11,31);
    wrog[4].napoleon(60,12);
    wrog[5].napoleon(57,12);
    wrog[6].napoleon(61,11);
    wrog[7].napoleon(9,12);
    wrog[8].napoleon(7,11);
    wrog[9].napoleon(16,17);
    wrog[10].napoleon(18,16);
    wrog[11].napoleon(10,19);
    wrog[12].napoleon(40,1);
    wrog[13].napoleon(60,6);
    wrog[14].napoleon(57,7);
    wrog[15].napoleon(53,22);
    wrog[16].napoleon(50,25);
    wrog[17].napoleon(55,27);
    wrog[18].napoleon(46,26);
    wrog[19].napoleon(59,26);
    wrog[20].napoleon(43,16);
    wrog[21].napoleon(52,30);
    wrog[22].napoleon(31,32);
    wrog[23].napoleon(32,31);
    wrog[24].napoleon(27,18);
    for(int i=0; i<gracz.hp; i++)
        zycie[i].rysuj(i);
    }
    while(okno.isOpen()&&mapka!=0&&punkty<3)
    {
        nowyczas+=clock.restart().asSeconds();
        pozycja=gracz.pc.getPosition();
        kursor=sf::Mouse::getPosition(okno);
        while(okno.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                okno.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                okno.close();
                mapka=4;
            }
            if(event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
                ruch=true;
            if(event.type==sf::Event::MouseButtonReleased&&event.mouseButton.button==sf::Mouse::Left)
            {
                ruch=false;
                rup=0;
                rdown=0;
                rleft=0;
                rright=0;
            }
        }

        if(nowyczas-staryczas>=klatka)
        {
            staryczas=nowyczas;
            klatki++;

            if(ruch)
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

            if(mapka==1)
            {
                if(pozycja.x>siatka[700].podloga.getPosition().x&&pozycja.x<siatka[700].podloga.getPosition().x+100)
                    if(pozycja.y+100>siatka[700].podloga.getPosition().y&&pozycja.y<siatka[700].podloga.getPosition().y+200)
                        if(!uwolniony[0])
                        {
                            siatka[700].podloga.setTextureRect(sf::IntRect(0,0, 100,100));
                            punkty++;
                            uwolniony[0]=true;
                        }
                if(pozycja.x>siatka[1859].podloga.getPosition().x&&pozycja.x<siatka[1859].podloga.getPosition().x+100)
                    if(pozycja.y+100>siatka[1859].podloga.getPosition().y&&pozycja.y<siatka[1859].podloga.getPosition().y+200)
                        if(!uwolniony[1])
                        {
                            siatka[1859].podloga.setTextureRect(sf::IntRect(0,0, 100,100));
                            punkty++;
                            uwolniony[1]=true;
                        }
                if(pozycja.x>siatka[2156].podloga.getPosition().x&&pozycja.x<siatka[2156].podloga.getPosition().x+100)
                    if(pozycja.y+100>siatka[2156].podloga.getPosition().y&&pozycja.y<siatka[2156].podloga.getPosition().y+200)
                        if(!uwolniony[2])
                        {
                            siatka[2156].podloga.setTextureRect(sf::IntRect(0,0, 100,100));
                            punkty++;
                            uwolniony[2]=true;
                        }
            }
            if(punkty>=3)
                mapka++;

            for(int i=0; i<25; i++)
                if(wrog[i].hp>0)
                {
                    przeciwnik=wrog[i].pc.getPosition();
                    odleglosc=sqrt((pozycja.x-przeciwnik.x)*(pozycja.x-przeciwnik.x)+(pozycja.y-przeciwnik.y)*(pozycja.y-przeciwnik.y));
                    reup=(pozycja.y-przeciwnik.y)/(odleglosc/4);
                    redown=(przeciwnik.y-pozycja.y)/(odleglosc/4);
                    releft=(pozycja.x-przeciwnik.x)/(odleglosc/4);
                    reright=(przeciwnik.x-pozycja.x)/(odleglosc/4);
                    poz=przeciwnik.x/100*skalax+przeciwnik.y/100*skalay*64;
                        for(int j=0; j<2304; j++)        //kolizje
                            if(siatka[j].sciana==true)
                            {
                                wall=siatka[j].podloga.getPosition();
                                if(wall.x+140*skalax>=przeciwnik.x&&wall.x-40*skalax<przeciwnik.x)
                                {
                                    if(wall.y+140*skalay>=przeciwnik.y&&wall.y-50*skalay<przeciwnik.y)
                                        wrog[i].kolgora=true;
                                    if(wall.y+50>=przeciwnik.y&&wall.y-55*skalay<=przeciwnik.y)
                                        wrog[i].koldol=true;
                                }
                                if(wall.y-50*skalay<przeciwnik.y&&wall.y+150*skalay>przeciwnik.y)
                                {
                                    if(wall.x+130*skalax>=przeciwnik.x&&wall.x<=przeciwnik.x)
                                        wrog[i].kolprawo=true;
                                    if(wall.x>=przeciwnik.x&&wall.x+30*skalax<przeciwnik.x)
                                        wrog[i].kollewo=true;
                                }
                            }
                    if(odleglosc<600&&!wrog[i].atak)
                    {
                        if(odleglosc>400)
                        {
                            if(przeciwnik.y<pozycja.y&&reup>0&&!wrog[i].koldol)
                            {
                                wrog[i].pc.move(0,reup);
                                wrog[i].pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));
                            }
                            if(przeciwnik.y>pozycja.y&&redown>0&&!wrog[i].kolgora)
                            {
                                wrog[i].pc.move(0,-redown);
                                wrog[i].pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                            }
                            if(przeciwnik.x>pozycja.x&&reright>0&&!wrog[i].kollewo)
                            {
                                wrog[i].pc.move(-reright,0);
                                wrog[i].pc.setTextureRect(sf::IntRect(100*(klatki/5%4),100,100,100));
                                if(reright<=redown)
                                    wrog[i].pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                                if(reright<=reup)
                                    wrog[i].pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));
                            }
                            if(przeciwnik.x<pozycja.x&&releft>0&&!wrog[i].kolprawo)
                            {
                                wrog[i].pc.move(releft,0);
                                wrog[i].pc.setTextureRect(sf::IntRect(100*(klatki/5%4),200,100,100));
                                if(releft<=redown)
                                    wrog[i].pc.setTextureRect(sf::IntRect(100*(klatki/5%4),300,100,100));
                                if(releft<=reup)
                                    wrog[i].pc.setTextureRect(sf::IntRect(100*(klatki/5%4),0,100,100));
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
                    {
                        wrog[i].hp-=gracz.dmg;
                        ruch=false;
                        if(wrog[i].hp==0&&gracz.hp<10)
                            gracz.hp++;
                    }

                    wrog[i].kolprawo=false;
                    wrog[i].kollewo=false;
                    wrog[i].kolgora=false;
                    wrog[i].koldol=false;
                }


            if(kursor.y<10&&siatka[0].podloga.getPosition().y<=0)     //ruch ekranu
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
            if(kursor.x<10&&siatka[0].podloga.getPosition().x<=0)
            {
                for(int i=0; i<2304; i++)
                    siatka[i].podloga.move(rk,0);
                gracz.pc.move(rk,0);
                for(int i=0; i<25; i++)
                    wrog[i].pc.move(rk,0);
            }
            if(kursor.x>ekranx-10&&siatka[2303].podloga.getPosition().x<=23040)
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
                    if(wall.x+110*skalax>=pozycja.x&&wall.x-10<=pozycja.x)
                    {
                        if(wall.y+110*skalay>=pozycja.y&&wall.y<=pozycja.y)
                            kolgora=true;
                        if(wall.y>=pozycja.y&&wall.y<=pozycja.y+5)
                            koldol=true;
                    }
                    if(wall.y<=pozycja.y&&wall.y+100*skalay>=pozycja.y)
                    {
                        if(wall.x+130*skalax>=pozycja.x&&wall.x<=pozycja.x)
                            kollewo=true;
                        if(wall.x>=pozycja.x&&wall.x<=pozycja.x+30*skalax)
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
    }
    return 0;
}
