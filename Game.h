
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

    bool try_place_single_ship(int x1, int y1);

    bool try_place_ship(const size_t size, int x1, int y1, int x2, int y2);

    void user_arrangement(); // заполенение для пользователя

    // проверка клетки

    static bool is_out_of_bounds(int x, int y); //входит в диапазон

    Attack attack(int x, int y); // статус атаки

    bool is_cell_visited(int x, int y); //проверка на клетку, про которую мы знаем, уже атаковали

    bool get_cell_miss(int x, int y); // 1 - пустая клетка

    void place(int x, int y, Cell c); // выставление значения клетке
    // проверка конца игры: 0 - не конец игры

    void undiscover();

    void print_everything(); // вывод всего
    void print_known(); // вывод известного
};

void Game::user_arrangement() {
    cout << "Use capital letters!" << endl;
    cout << "Ship arrangement" << endl;

    print_everything(); // Вывод пустого поля

    {
        int x1, y1, x2, y2;
        cout << "Four deck" << endl;
        do {
            cout << "Enter beginning and ending cells" << endl;
            char x1_char, x2_char;
            cin >> x1_char >> y1 >> x2_char >> y2;
            x1 = x1_char - 'A';
            x2 = x2_char - 'A';
        } while (!try_place_ship(4, x1, y1, x2, y2));
        print_everything();
    }

    {
        for (int i = 0; i < 2; ++i) {
            int x1, y1, x2, y2;
            cout << "Three deck #" << i << endl;
            do {
                cout << "Enter beginning and ending cells" << endl;
                char x1_char, x2_char;
                cin >> x1_char >> y1 >> x2_char >> y2;
                x1 = x1_char - 'A';
                x2 = x2_char - 'A';
            } while (!try_place_ship(3, x1, y1, x2, y2));
            print_everything();
        }
    }

    {
        for (int i = 0; i < 3; ++i) {
            int x1, y1, x2, y2;
            cout << "Two deck #" << i << endl;
            do {
                cout << "Enter beginning and ending cells" << endl;
                char x1_char, x2_char;
                cin >> x1_char >> y1 >> x2_char >> y2;
                x1 = x1_char - 'A';
                x2 = x2_char - 'A';
            } while (!try_place_ship(2, x1, y1, x2, y2));
            print_everything();
        }
    }

    {
        for (int i = 0; i < 4; ++i) {
            int x, y;
            cout << "One deck #" << i << endl;
            do {
                cout << "Enter beginning and ending cells" << endl;
                {
                    char x_char;
                    cin >> x_char >> y;
                    x = x_char - 'A';
                }
            } while (!try_place_single_ship(x, y));
            print_everything();
        }
    }

    undiscover();
}

//enum attack Game::attack_(int x, int y) {
//    return win;
//}

void Game::place(int x, int y, Cell c) {
    cells[x][y] = c;
    if (c == ship) ++k;
}

void Game::print_known() {
    cout << " ";
    for (int x = 0; x < 10; ++x) cout << "   " << ((char) ('A' + x));
    cout << endl;

    for (int y = 0; y < 10; ++y) {
        cout << y;
        for (auto &x : cells) {
            const auto cell = x[y];
            switch (cell) {
                case freee:
                case ship:
                    cout << "   .";
                    break;
                case discovered:
                    cout << "   ~";
                    break;
                case attacked:
                    cout << "   x";
                    break;
            }
        }
        cout << endl;
    }
    cout << "                         " << k << " ships left" << endl;
}

void Game::print_everything() {
    cout << " ";
    for (int x = 0; x < 10; ++x) cout << "   " << ((char) ('A' + x));
    cout << endl;

    for (int y = 0; y < 10; ++y) {
        cout << y;
        for (auto &x : cells) {
            const auto cell = x[y];
            switch (cell) {
                case freee:
                    cout << "   .";
                    break;
                case discovered:
                    cout << "   ~";
                    break;
                case ship:
                    cout << "   #";
                    break;
                case attacked:
                    cout << "   x";
                    break;
            }
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
        cout << "K was = " << k << " and became = " << k - 1 << endl;
        --k;
        if (k == 0) return win; // нет смысла ещё что-то проверять
        return try_attack(x, y) ? destroy : damage;
    }
    throw runtime_error("Всё пошло плохо!!!! Как и вся моя жизнь!!!!!!!!!!!!!!!!!!");
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
            ship_coordinates.push_back(ship_coordinate{x, tested_y});
        }
        tested_y = y;
        while (++tested_y < 10) {
            const auto cell = cells[x][tested_y];
            if (is_empty(cell)) break;
            if (cell == ship) return false;
            ship_coordinates.push_back(ship_coordinate{x, tested_y});
        }
    }

    {
        int tested_x = x;
        while (--tested_x >= 0) {
            const auto cell = cells[tested_x][y];
            if (is_empty(cell)) break;
            if (cell == ship) return false;
            ship_coordinates.push_back(ship_coordinate{tested_x, y});
        }
        tested_x = x;
        while (++tested_x < 10) {
            const auto cell = cells[tested_x][y];
            if (is_empty(cell)) break;
            if (cell == ship) return false;
            ship_coordinates.push_back(ship_coordinate{tested_x, y});
        }
    }

    surround_ship_cell(x, y);
    for (const auto &coordinate : ship_coordinates) {
        cout << "Handling at " << char(coordinate.x + 'A') << ":" << coordinate.y << endl;
        surround_ship_cell(coordinate.x, coordinate.y);
    }

    return true;
}

void Game::surround_ship_cell(const int &x, const int &y) {
    for (int i = x - 1; i <= x + 1; i++) for (int j = y - 1; j <= y + 1; j++) if (cells[i][j] == freee) cells[i][j]
            = discovered;
}

void Game::undiscover() {
    for (auto &column : cells) {
        for (auto &cell : column) {
            switch (cell) {
                case freee: case ship:
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

bool Game::try_place_single_ship(int x1, int y1) {
    for (int tested_x = x1 - 1; tested_x <= x1 + 1; ++tested_x) {
        for (int tested_y = y1 - 1; tested_y <= y1 + 1; ++tested_y) {
            if (is_out_of_bounds(tested_x, tested_y)) continue; // всё норм

            if (!is_empty(cells[tested_x][tested_y])) return false;
        }
    }

    place(x1, y1, ship);
    surround_ship_cell(x1, y1);

    return true;
}

bool Game::try_place_ship(const size_t size, int x1, int y1, int x2, int y2) {
    // проверить правильность координат
    if (x1 == x2) {
        if (y1 == y2) {// одинаковые координаты
            if (size == 1) return try_place_single_ship(x1, y1);
            return false;
        }
        if (y1 > y2) std::swap(y1, y2);
        if (y2 - y1 != size - 1) return false;
    } else {
        if (y1 != y2) return false; // *диагональный* корабль
        if (x1 > x2) std::swap(x1, x2);
        if (y2 - y1 != size - 1) return false;
    }

    for (int tested_x = x1 - 1; tested_x <= x1 + 1; ++tested_x) {
        for (int tested_y = y1 - 1; tested_y <= y1 + 1; ++tested_y) {
            if (is_out_of_bounds(tested_x, tested_y)) continue; // всё норм

            if (!is_empty(cells[tested_x][tested_y])) return false;
        }
    }

    for (int tested_x = x1; tested_x <= x2; ++tested_x) {
        for (int tested_y = y1; tested_y <= y2; ++tested_y) {
            cells[tested_x][tested_y] = ship;
            surround_ship_cell(tested_x, tested_y);
        }
    }

    k += size;

    return true;
}


#endif //BOY_2_GAME_H
