#include <iostream>
#include <fstream>
#include "life.h"
#include <SFML/Graphics.hpp>
#include <vector>


int main(int argc, char** argv)
{
    const int32_t height = 400;
    const int32_t width = 600;

    if (argc != 3) {
        std::cout << "Input error (must be 3 args)"
                << std::endl;
        return 1;
    }
    std::ifstream input(argv[1], std::ios::in);
    if(!input.is_open()) {
        std::cout << "Open file error"
                << std::endl;
        return 1;
    }
    int32_t max_iter = atoi(argv[2]);
    if (max_iter < 0) {
        std::cout << "Number of iteration error"
                << std::endl;
        return 1;
    }

    life game;
    input >> game; // reading initial field

    sf::RenderWindow window(sf::VideoMode(width, height), "Game of life");

    if (max_iter > 0) {
      game.DoSteps(max_iter);
    }

    while(window.isOpen()) {
        sf::Event event;        
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(max_iter == 0
               && event.type == sf::Event::KeyPressed
               && event.key.code == sf::Keyboard::Return) {
                game.DoStep();
            }
        }
        window.clear();
        drow(window, game, width, height);
        window.display();
    }
    return 0;
}