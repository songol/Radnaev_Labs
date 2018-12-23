#include <iostream>
#include <fstream>
#include "life.h"
#include <SFML/Graphics.hpp>	
#include <utility>
life::life(): life::life(1, 1) {};
life::life(const int32_t rows, const int32_t columns) {
	board = std::vector<std::vector<bool>>(rows, std::vector<bool>(columns, false));
}
void life::set(int32_t row, int32_t column, bool value) {
    board[row][column] = value;
}
//int32_t life::get_m() {return m;}
//int32_t life::get_n() {return n;}
std::ifstream& operator >> (std::ifstream& in,
                            life& Game) {
    in >> Game.m >> Game.n;
    in.get();
    std::vector<std::vector<bool>> board(Game.m);
    for (int32_t row = 0; row < Game.m; ++row) {
        board[row].resize(Game.n, false);
    }
    for (int32_t row = 0; row < Game.m; ++row) {
        for (int32_t column = 0; column < Game.n; ++column) {
            char point = in.get();
            if (point == '*') {
                board[row][column] = 1;
            } else {
                board[row][column] = 0;
            }

        }
        in.get();
    }
    Game.board = board;
    return in;
}
bool life::isAlive(int32_t row, int32_t column) {
    while (row >= m) {
        row -= m;
    }
    while (row < 0) {
        row += m;
    }
    while (column >= n) {
        column -= n;
    }
    while (column < 0) {
        column += n;
    }
    return board[row][column];
}

int32_t life::numb_of_alive_neighboors(int32_t row, int32_t column) {
    int32_t res = 0;
    int32_t di[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int32_t dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int32_t l = 0; l < 8; ++l) {
        if (isAlive(row + di[l], column + dj[l])) {
            res++;
        }
    }
    return res;
}

void life::DoStep() {
    auto copy_board = board;
    for (int32_t row = 0; row < m; ++row) {
        for (int32_t column = 0; column < n; ++column) {
            const auto alives = numb_of_alive_neighboors(row, column);
            if (board[row][column]) {
                if (alives == 3 || alives == 2) {
                    copy_board[row][column] = true;
                } else {
                    copy_board[row][column] = false;
                }
            } else {
                if (alives == 3) {
                    copy_board[row][column] = true;
                }
            }
        }
    }
    board = copy_board;
}
void life::DoSteps(int32_t number_of_iterations) {
    for (int32_t i = 0; i < number_of_iterations; ++i){
        DoStep();
    }
}

void drow(sf::RenderWindow& window,
        life& game,
        int32_t win_width,
        int32_t win_height) {
    int32_t m = game.m;
    int32_t n = game.n;
    std::vector<std::vector<sf::RectangleShape>> sector(m);

    for (int32_t i = 0; i < m; ++i) {
        sector[i].resize(n);
    }

    int32_t cell_w = win_width / n;
    int32_t cell_h = win_height / m;
    for (int32_t i = 0; i < m; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            sector[i][j].setSize(sf::Vector2f(cell_w, cell_h));
            sector[i][j].setPosition(cell_w * j, cell_h * i);
            if (game.board[i][j]) {
                sector[i][j].setFillColor(sf::Color::Red);
            } else {
                sector[i][j].setFillColor(sf::Color::White);
            }
            window.draw(sector[i][j]);
        }
    }
    sector.clear();
}