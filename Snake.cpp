#include <SFML/Graphics.hpp>
#include "windows.h"
#include <iostream>
using namespace sf;


struct tochka
{
    int x = 0;
    int y = 0;
}znake[10000];


int main()
{
    setlocale(LC_ALL, "Russian");// переменные
    int score = 0;
    int corfudx = 0;
    int corfudy = 0;
    int skushano = 1;
    int gaame = 1;
    int dir = 0;
    int dlina = 0;
    int size = 0;
    int gamel = 1;
    int gpro = 1;
    int menu = 1;

    Texture square;


    while (gamel)
    {
        menu = 1;
        while (menu)// меню ввода размера карты
        {
            std::cout << "Ведите размеры поля 1 = 1на клетка." << std::endl;
            std::cout << "Для выхода из игры введите 0." << std::endl;
            std::cin >> size;
            dir = 0;


            if (size == 0)
            {
                menu = 0;
                gamel = 0;
                gpro = 0;
            }

            else
            {
                menu = 0;
            }

            system("cls");
        }

        int otrzmey = size;

        menu = 1;

        while (gpro)
        {
            for (int i = 0; i < 10000; i++)// перемещение тела змеи за карту
            {
                znake[i].x = -20;
                znake[i].y = -20;
            }

            int dlina = 3;
            score = 0;
            int sped = 750;

            
            RenderWindow game(VideoMode(size * 20, size * 20), "SNAKE by Zakhar");// открытие окна
            Event gameEv;

            Texture squuare;
            squuare.loadFromFile("Square.png");
            Sprite green(squuare), red(squuare);
            
            Color colour(0, 255, 0);
            green.setColor(colour);
            
            green.setPosition(-10, -10);
            
            Color colur(255, 0, 0);
            red.setColor(colur);
            

            srand(time(NULL));
            corfudx = 20 * (1 + rand() % (size));// генератор еды
            corfudy = 20 * (1 + rand() % (size));

            for (int i = 0; i < size; i++)
            {
                if (corfudx <= (i + 1) * 10 && corfudx > i * 10)
                    corfudx = (i + 1) * 10;

                if (corfudy <= (i + 1) * 10 && corfudy > i * 10)
                    corfudy = (i + 1) * 10;
            }

            
            znake[0].x = 0;
            znake[0].y = 0;


            while (game.isOpen())
            {
                while (game.pollEvent(gameEv))
                {
                    if (gameEv.type == Event::Closed)// если окно закрыто
                    {
                        game.close();
                        std::cout << "Ваш счет равен " << score << std::endl;
                        gpro = 0;
                    }

                    if (gameEv.type == Event::KeyPressed)//нажатие клавиш
                    {
                        if (gaame == 1)
                        {
                            if (gameEv.key.code == Keyboard::Right && dir != 1)
                                dir = 0;

                            else if (gameEv.key.code == Keyboard::Left && dir != 0)
                                dir = 1;

                            else if (gameEv.key.code == Keyboard::Down && dir != 3)
                                dir = 2;

                            else if (gameEv.key.code == Keyboard::Up && dir != 2)
                                dir = 3;
                        }
                    }
                }

                game.clear(Color(0, 0, 0));

                
                for (int i = dlina; i > 0; i--) // перемещение змеи
                {
                    znake[i].x = znake[i - 1].x;
                    znake[i].y = znake[i - 1].y;
                }

                if (dir == 0)
                    znake[0].x += 20;

                if (dir == 1)
                    znake[0].x -= 20;

                if (dir == 2)
                    znake[0].y += 20;
                    
                if (dir == 3)
                    znake[0].y -= 20;

                if (znake[0].x >= size * 20 || znake[0].x <= -5 || znake[0].y >= size * 20 || znake[0].y <= -5)// проверка на смерть
                {
                    game.close();
                    std::cout << "Ваш счет равен " << score << std::endl;
                    gpro = 0;
                }

                for (int i = 1; i < dlina; i++)
                {
                    if (znake[0].x == znake[i].x && znake[0].y == znake[i].y && menu != 0)
                    {
                        game.close();
                        std::cout << "Ваш счет равен " << score << std::endl;
                        gpro = 0;
                    }
                }

                if (znake[0].x == red.getPosition().x && znake[0].y == red.getPosition().y) // съедание плода
                {
                    size *= 100;
                    score += 1;
                    dlina += 1;
                    if (sped > 100)
                        sped -= 20;

                    else if (sped > 50 && sped <= 100)
                        sped -= 10;

                    else if (sped >= 0 && sped <= 50)
                        sped -= 5;
                    skushano = 1;
                    size /= 100;

                    while (skushano)
                    {
                        corfudx = 20 * (1 + rand() % (size));// генератор еды 2
                        corfudy = 20 * (1 + rand() % (size));

                        for (int i = 0; i < size; i++)
                        {
                            if (corfudx <= (i + 1) * 10 && corfudx > i * 10)
                                corfudx = (i + 1) * 10;

                            if (corfudy <= (i + 1) * 10 && corfudy > i * 10)
                                corfudy = (i + 1) * 10;
                        }

                        for (int i = 0; i < size; i++)
                        {
                            if (corfudx == znake[i].x && corfudy == znake[i].y)
                                break;

                            else if ((corfudx != znake[i].x || corfudy != znake[i].y) && i == size - 1)
                                skushano = 0;
                        }
                    }
                }

                red.setPosition((corfudx - 20), (corfudy - 20));
                game.draw(red);

                otrzmey++;

                for (int i = 0; i < otrzmey; i++)// отрисовка змеи
                {
                    green.setPosition(znake[i].x, znake[i].y);
                    game.draw(green);
                }
                
                game.display();
                Sleep(sped);
            }
        }

        gpro = 1;

    }
    return 0;
}