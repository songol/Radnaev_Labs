#ifndef LIFE_H
#define LIFE_H
#include <cstdint>
#include <fstream>
#include <SFML/Graphics.hpp> 


class life {
    int32_t m;
    int32_t n;

    std::vector<std::vector<bool>> board;

public:
    life();
    life(int32_t rows, int32_t columns);
    void set(int32_t row, int32_t column, bool value);
    void DoSteps(int32_t number_of_iterations);
    bool isAlive(int32_t row, int32_t column);
    void DoStep();
    int32_t numb_of_alive_neighboors(int32_t row, int32_t column);

    /*friend std::ofstream& operator
    << (std::ofstream& o, life& A);*/

    friend std::ifstream& operator
    >> (std::ifstream& in, life& A);
    friend void drow(sf::RenderWindow& window,
                     life& A,
                     int32_t win_width,
                     int32_t win_height);
};
#endif // LIFE_H