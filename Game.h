
#ifndef BOY_2_GAME_H
#define BOY_2_GAME_H


#include <stdexcept>
#include <vector>
#include "Cell.h"
#include "Attack.h"

using std::cin;
using std::endl;
using std::cout;
using std::vector;
using std::runtime_error;

class Game {
protected:
    Cell cells[10][10] = {};
    size_t k = 0;

    bool try_attack(int x, int y);

    void surround_ship_cell(const int &x, const int &y);

public:
    void user_arrangement(); // заполенение для пользователя

    Cell get_cell_(int x, int y); // проверка клетки

    static bool is_out_of_bounds(int x, int y);

    Attack attack(int x, int y); // статус атаки

    bool is_cell_visited(int x, int y); //проверка на клетку, про которую мы знаем, уже атаковали

    bool get_cell_miss(int x, int y); // 1 - пустая клетка

    void place(int x, int y, Cell c); // выставление значения клетке
    bool end(); // проверка конца игры: 0 - не конец игры

    void undiscover();

    void print_beat(); // вывод красивый
    void print_for(); // вывод компа для user
    void print_fully(); // вывод полный


};

void Game::user_arrangement() {
    int line, column;
    int k;
    //char chip[10][10];
    cout << "Use capital letters!" << endl;
    cout << "Ship arrangement" << endl;

    cout << "Four deck" << endl;
    cout << "Cells: ";
    int start4, end4;
    char start4_, end4_;
    cin >> start4_ >> start4 >> end4_ >> end4;
    if (start4 == end4) {
        cells[start4][int(start4_) - 65] = ship;
        cells[start4][int(start4_) - 64] = ship;
        cells[start4][int(start4_) - 63] = ship;
        cells[start4][int(end4_) - 65] = ship;
        line = start4;
        column = start4_;
        for (int i = line - 1; i <= line + 1; i++) {
            for (int j = column - 1; j <= column + 4; j++) {
                if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                if (k == 1) if (cells[i][j] != ship) cells[i][j] = discovered;
            }
        }
    }
    if (start4_ == end4_) {
        cells[start4][int(start4_) - 65] = ship;
        cells[start4 + 1][int(start4_) - 65] = ship;
        cells[start4 + 2][int(start4_) - 65] = ship;
        cells[end4][int(start4_) - 65] = ship;
        line = start4_;
        column = start4;
        for (int i = line - 1; i <= line + 4; i++) {
            for (int j = column - 1; j <= column + 1; j++) {
                if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                if (k == 1 && cells[i][j] != ship) cells[i][j] = discovered;
            }

        }
    }
    cout << endl;

    cout << "Three deck" << endl;
    cout << "Cells: ";
    for (int i = 0; i < 2; i++) {
        int start3, end3;
        char start3_, end3_;
        cin >> start3_ >> start3 >> end3_ >> end3;
        if (start3 == end3) {
            cells[start3][int(start3_) - 65] = ship;
            cells[start3][int(start3_) - 64] = ship;
            cells[start3][int(end3_) - 65] = ship;
        }
        if (start3_ == end3_) {
            cells[start3][int(start3_) - 65] = ship;
            cells[start3 + 1][int(start3_) - 65] = ship;
            cells[end3][int(start3_) - 65] = ship;
        }
    }
    cout << endl;


    cout << "Double deck" << endl;
    cout << "Cells: ";
    for (int i = 0; i < 3; i++) {
        int start2, end2;
        char start2_, end2_;
        cin >> start2_ >> start2 >> end2_ >> end2;
        if (start2 == end2) {
            cells[start2][int(start2_) - 65] = ship;
            cells[start2][int(end2_) - 65] = ship;
        }
        if (start2_ == end2_) {
            cells[start2][int(start2_) - 65] = ship;
            cells[end2][int(start2_) - 65] = ship;
        }
    }
    cout << endl;

    cout << "Single deck" << endl;
    cout << "Cells: ";
    for (int i = 0; i < 4; i++) {
        int start1;
        char start1_;
        cin >> start1_ >> start1;
        cells[start1][int(start1_) - 65] = ship;
    }
    cout << endl;
}

Cell Game::get_cell_(int x, int y) {
    return cells[x][y];
}

//enum attack Game::attack_(int x, int y) {
//    return win;
//}

void Game::place(int x, int y, Cell c) {
    cells[x][y] = c;
}

bool Game::end() {
    bool t = false;
    short k;
    for (auto &i : cells) {
        for (char j : i) {
            if (j == ship) k++;
        }
    }
    if (k == 20) t = true;
    return t;
}

void Game::print_beat() {
    char pole[11][11];
    pole[0][0] = ' ';
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 11; j++) {
            if (cells[i - 1][j - 1] == freee || cells[i - 1][j - 1] == discovered)
                pole[i][j] = '.';
            if (cells[i - 1][j - 1] == attacked) pole[i][j] = 'x';
            if (cells[i - 1][j - 1] == ship) pole[i][j] = '#';
        }
    }
    cout << "You" << endl;
    char c = '0';
    for (int i = 1; i < 11; i++) pole[0][i] = c++;
    for (char j = 1; j < 11; j++) pole[j][0] = 64 + j;
    for (auto &i : pole) {
        for (char j : i) {
            cout << j << ' ' << ' ' << ' ';
        }
        cout << endl;
    }

}

void Game::print_fully() {
    char pole[11][11];
    pole[0][0] = ' ';
    char c = '0';
    for (int i = 1; i < 11; i++) pole[i][0] = c++;
    for (char j = 1; j < 11; j++) pole[0][j] = 64 + j;
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 11; j++) {
            if (cells[i - 1][j - 1] == freee) pole[i][j] = '.';
            if (cells[i - 1][j - 1] == attacked) pole[i][j] = 'x';
            if (cells[i - 1][j - 1] == ship) pole[i][j] = '#';
            if (cells[i - 1][j - 1] == discovered) pole[i][j] = '-';
        }
    }
    for (auto &i : pole) {
        for (char j : i) {
            cout << j << ' ' << ' ' << ' ';
        }
        cout << endl;
    }
}

bool Game::get_cell_miss(int x, int y) {
    return cells[x][y] != ship;
}

bool Game::is_cell_visited(int x, int y) {
    return cells[x][y] == discovered || cells[x][y] == attacked;
}

bool Game::is_out_of_bounds(int x, int y) {
    return (x < 0 || x >= 10) || (y < 0 || y >= 10);
}

Attack Game::attack(int x, int y) {
    if (is_cell_visited(x, y)) return already_attacked;
    if (get_cell_miss(x, y)) {
        cells[x][y] = discovered;
        return miss;
    }
    if (cells[x][y] == ship) {
        cells[x][y] = attacked;
        --k;
        if (try_attack(x, y)) return k == 0 ? win : destroy; else return damage;
    }
    throw runtime_error("Всё пошло хреново!!!! Как и вся моя жизнь!!!!!!!!!!!!!!!!!!");
}


/**
 *
 * @param x
 * @param y
 * @return 1 - убил, 0 - ранил
 */
bool Game::try_attack(const int x, const int y) {
    struct ship_coordinate {
        int x, y;
    };
    vector<ship_coordinate> ship_coordinates;

    {
        int tested_y = y;
        while (--tested_y >= 0) {
            const auto cell = cells[x][tested_y];
            if (is_empty(cell)) break;
            if (cell == ship) return false;
            else ship_coordinates.push_back(ship_coordinate{x, y});
        }
        tested_y = y;
        while (++tested_y < 10) {
            const auto cell = cells[x][tested_y];
            if (is_empty(cell)) break;
            if (cell == ship) return false;
            else ship_coordinates.push_back(ship_coordinate{x, y});
        }
    }

    {
        int tested_x = x;
        while (--tested_x >= 0) {
            const auto cell = cells[tested_x][y];
            if (is_empty(cell)) break;
            if (cell == ship) return false;
            else ship_coordinates.push_back(ship_coordinate{x, y});
        }
        tested_x = x;
        while (++tested_x < 10) {
            const auto cell = cells[tested_x][y];
            if (is_empty(cell)) break;
            if (cell == ship) return false;
            else ship_coordinates.push_back(ship_coordinate{x, y});
        }
    }

    surround_ship_cell(x, y);
    for (const auto &coordinate : ship_coordinates) surround_ship_cell(coordinate.x, coordinate.y);

    return true;
}

void Game::surround_ship_cell(const int &x, const int &y) {
    for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++) {
            auto &cell = cells[i][j];
            if (cell == freee) cell = discovered;
        }
}

void Game::undiscover() {
    for (auto &column : cells) {
        for (auto &cell : column) {
            switch (cell) {
                case freee:
                    break;
                case ship:
                    break;
                case discovered:
                    cell = freee;
                    break;
                case attacked:
                    cell = ship;
                    break;
            }
        }
    }
}

//void Game::print_for() {
//    char pole[11][11];
//    pole[0][0] = ' ';
//    for (int i = 1; i < 11; i++) {
//        for (int j = 1; j < 11; j++) {
//            if (cells[i - 1][j - 1] != ship || cells[i - 1][j - 1] != busy || cells[i - 1][j - 1] != attack ||
//            cells[i - 1][j - 1] != damage || cells[i - 1][j - 1] != destroy ||
//            cells[i - 1][j - 1] != win) pole[i][j] = '.';
//            if (|| cells[i - 1][j - 1] == attack ||
//                   cells[i - 1][j - 1] == damage || cells[i - 1][j - 1] == destroy ||
//                   cells[i - 1][j - 1] == win) pole[i][j] = 'x';
//            if (cells[i - 1][j - 1] == destroy) pole[i][j] = '#';
//        }
//    }
//    cout << "Computer" << endl;
//    char c = '0';
//    for (int i = 1; i < 11; i++) pole[i][0] = c++;
//    for (char j = 1; j < 11; j++) pole[0][j] = 64 + j;
//    for (auto &i : pole) {
//        for (char j : i) {
//            cout << j << ' ' << ' ' << ' ';
//        }
//        cout << endl;
//    }
//
//}



#endif //BOY_2_GAME_H
