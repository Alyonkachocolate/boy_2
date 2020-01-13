

//
// Created by user on 25/12/2019.
//

#ifndef BOY_2_BOT_H
#define BOY_2_BOT_H

#include <stdexcept>
#include "Game.h"
#include "Position.h"

using std::runtime_error;

class Bot {

protected:
    Game *own_field;
    Game *rival_field;
    int last_ship_x = -1;
    int last_ship_y = -1;
    Position position = unknown;
public:

    Bot(Game *own_field, Game *rival_field) : own_field(own_field), rival_field(rival_field) {}

    void place_ships();

    bool play();

    bool random_attack();

    bool attack_ship();

};

void Bot::place_ships() {
    Cell chip[10][10];
    for (auto &i : chip) {
        for (Cell &j : i) {
            j = freee;
        }
    }
    srand(time(NULL));

//  Четырехпалубный
    int position, rand1, start_;
    position = rand() % 2;
    // 0 - горизонтально; 1 - вертикально
    rand1 = rand() % 10;//буква 65-rand1
    start_ = rand() % 10;
    if (start_ >= 7) start_ = rand() % 7;
    if (position == 1) for (int i = start_; i < start_ + 4; i++) chip[i][rand1] = ship;
    if (position == 0) for (int i = start_; i < start_ + 4; i++) chip[rand1][i] = ship;
    int line, column, k = 1;
    if (position == 0) {
        line = rand1;
        column = start_;
        for (int i = line - 1; i <= line + 1; i++) {
            for (int j = column - 1; j <= column + 4; j++) {
                if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                if (k == 1 && chip[i][j] != ship) chip[i][j] = discovered;
            }
        }
    } else {
        line = start_;
        column = rand1;
        for (int i = line - 1; i <= line + 4; i++) {
            for (int j = column - 1; j <= column + 1; j++) {
                if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                if (k == 1 && chip[i][j] != ship) chip[i][j] = discovered;
            }

        }
    }

    // Трёхпалубники
    for (int j = 0; j < 2; j++) {
        rand1 = 0, start_ = 0;
        position = rand() % 2;
        int u = 0;
        while (u != 3) {
            rand1 = rand() % 10;
            start_ = rand() % 10;
            if (start_ >= 8) start_ = (rand() % 8);
            if (position == 0)
                for (int i = start_; i < start_ + 3; i++)
                    if (chip[rand1][i] == freee) u++;
            if (position == 1)
                for (int i = start_; i < start_ + 3; i++)
                    if (chip[i][rand1] == freee) u++;
            if (u < 3) u = 0;
        }
        if (position == 1) for (int i = start_; i < start_ + 3; i++) chip[i][rand1] = ship;
        if (position == 0) for (int i = start_; i < start_ + 3; i++) chip[rand1][i] = ship;
        if (position == 0) {
            line = rand1;
            column = start_;
            for (int i = line - 1; i <= line + 1; i++) {
                for (int l = column - 1; l <= column + 3; l++) {
                    if ((i < 10) && (i >= 0) && (l < 10) && (l >= 0)) k = 1; else k = 0;
                    if (k == 1) if (chip[i][l] != ship) chip[i][l] = discovered;
                }
            }
        } else {
            line = start_;
            column = rand1;
            for (int i = line - 1; i <= line + 3; i++) {
                for (int l = column - 1; l <= column + 1; l++) {
                    if ((i < 10) && (i >= 0) && (l < 10) && (l >= 0)) k = 1; else k = 0;
                    if (k == 1 && chip[i][l] != ship) chip[i][l] = discovered;
                }

            }
        }
    }


    // Двухпалубники
    for (int j = 0; j < 3; j++) {
        rand1 = 0, start_ = 0;
        position = rand() % 2;
        int u = 0;
        while (u != 2) {
            rand1 = rand() % 10;
            start_ = rand() % 10;
            if (start_ == 9) start_ = (rand() % 9);
            if (position == 0)
                for (int i = start_; i < start_ + 2; i++)
                    if (chip[rand1][i] == freee) u++;
            if (position == 1)
                for (int i = start_; i < start_ + 2; i++)
                    if (chip[i][rand1] == freee) u++;
            if (u < 2) u = 0;
        }
        if (position == 1) for (int i = start_; i < start_ + 2; i++) chip[i][rand1] = ship;
        if (position == 0) for (int i = start_; i < start_ + 2; i++) chip[rand1][i] = ship;
        if (position == 0) {
            line = rand1;
            column = start_;
            for (int i = line - 1; i <= line + 1; i++) {
                for (int l = column - 1; l <= column + 2; l++) {
                    if ((i < 10) && (i >= 0) && (l < 10) && (l >= 0)) k = 1; else k = 0;
                    if (k == 1) if (chip[i][l] != ship) chip[i][l] = discovered;
                }
            }
        } else {
            line = start_;
            column = rand1;
            for (int i = line - 1; i <= line + 2; i++) {
                for (int l = column - 1; l <= column + 1; l++) {
                    if ((i < 10) && (i >= 0) && (l < 10) && (l >= 0)) k = 1; else k = 0;
                    if (k == 1 && chip[i][l] != ship) chip[i][l] = discovered;
                }

            }
        }
    }

    // Однопалубники
    for (int j = 0; j < 4; j++) {
        rand1 = 0, start_ = 0;
        int u = 0;
        while (u == 0) {
            rand1 = rand() % 10;
            start_ = rand() % 10;
            if (chip[rand1][start_] == freee) u++;
        }
        chip[rand1][start_] = ship;
        for (int i = rand1 - 1; i <= rand1 + 1; i++) {
            for (int j = start_ - 1; j <= start_ + 1; j++) {
                if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                if (k == 1) if (chip[i][j] != ship) chip[i][j] = discovered;
            }
        }

    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            own_field->place(i, j, chip[i][j]);
        }
    }
    own_field->undiscover();
}


// 1 -  выиграл игру, 0 - убил или ранил корабль
bool Bot::play() {
    if (last_ship_x == -1) return random_attack();
    else return attack_ship();
}

bool Bot::random_attack() {
    // случайная атака корабля
    while (true) {
        auto x = rand() % 10, y = rand() % 10;

        int count = 0;
        if (rival_field->is_cell_visited(x, y)) {
            for (x = 0; x < 10; ++x) {
                bool free_cell_found = false;
                for (y = 0; y < 10; ++y) if (!rival_field->is_cell_visited(x, y)) {
                    ++count;
                    free_cell_found = true;
                    break;
                }
                if (free_cell_found) break;
            }
        }
        cout << count << endl;

        // x, y -- координаты, которые мы можем атаковать
        switch (rival_field->attack(x, y)) {
            case miss:
                return false;
            case damage: { // сбили не однопалубник, а значит нужно перейти в режим атаки корабля
                last_ship_x = x;
                last_ship_y = y;

                return attack_ship();
            }
            case destroy:
                continue; // просто сбили однопалубник
            case win:
                return true; // победили, сбив однопалубник
            case already_attacked:
                throw runtime_error("R U Tam ofigeli___1");
        }
    }
}

// попытка продолжения атаки корабля
bool Bot::attack_ship() {
    cout << "<<<<<<<<<< Bot attacks a ship >>>>>>>>>>>>>>>" << endl;

    if (position == unknown) { // пока не знаем ничего о корабле
        cout << "<<< Bot does not yet know the position of the ship >>>" << endl;
        int x = last_ship_x;
        int y = last_ship_y;
        int variant = rand() % 4;

        bool exit = false;
        // находим случайную сторону, которую можно атаковать
        while (true) {
            switch (variant) {
                case 0:
                    if (x != 9 && !rival_field->is_cell_visited(x + 1, y)) {
                        cout << "<<< It is x+1 >>>" << endl;
                        ++x;
                        exit = true;
                    } else variant = 1;
                    break;
                case 1:
                    if (x != 0 && !rival_field->is_cell_visited(x - 1, y)) {
                        cout << "<<< It is x-1 >>>" << endl;
                        --x;
                        exit = true;
                    } else variant = 2;
                    break;
                case 2:
                    if (y != 9 && !rival_field->is_cell_visited(x, y + 1)) {
                        cout << "<<< It is y+1 >>>" << endl;
                        ++y;
                        exit = true;
                    } else variant = 3;
                    break;
                case 3:
                    if (y != 0 && !rival_field->is_cell_visited(x, y - 1)) {
                        cout << "<<< It is y-1 >>>" << endl;
                        --y;
                        exit = true;
                    } else variant = 0;
                    break;
            }
            if (exit) break;
        }


        cout << "<<< Bot decides to attack " << x << ":" << y << " >>>" << endl;
        switch (rival_field->attack(x, y)) {
            case miss:
                return false;
            case damage: { // ранили, но не убили
                position = (x == last_ship_x) ? gorizont : vertical;
                break;
            }
            case destroy:
                last_ship_x = -1;
                last_ship_y = -1;
                position = unknown;
                return random_attack(); // убили корабль, снова случайно атакуем
            case win:
                return true; // победили
            case already_attacked:
                throw runtime_error("R U Tam ofigeli_______2");
        }
    }
    cout << "<<< Continue " << (position == vertical ? "vertical" : "horizontal") << " attack >>>" << endl;

    while (true) {
        int delta = 1;
        if (position == vertical) {
            bool positive = true;
            while (true) {
                if (rival_field->is_out_of_bounds(last_ship_x + delta, last_ship_y)) {
                    if (positive) {
                        delta = -1;
                        positive = false;
                    } else throw runtime_error("R U Tam ofigeli ______3");
                }

                cout << "<<< Bot continues smart attack on  " << last_ship_x + delta << ":" << last_ship_y << endl;
                switch (rival_field->attack(last_ship_x + delta, last_ship_y)) {
                    case miss:
                        return false; // передаём ход игроку
                    case damage:
                        break; // продолжаем перебор в эту сторону
                    case destroy:
                        last_ship_x = last_ship_y = -1;
                        position = unknown;
                        return random_attack(); // снова переходим на случайные атаки
                    case win:
                        return true; // победа
                    case already_attacked: {
                        // мы продолжаем атаку в эту же сторону, если клетка, на которую мы наткнулись - корабль,
                        // который мы просто уже атаковали ранее
                        if (rival_field->is_attacked_ship(last_ship_x + delta, last_ship_y)) break;
                        else {
                            // если же мы уже упёрлись в воду, то нужно развернуться
                            if (positive) {
                                delta = 0;
                                positive = false;
                            } else throw runtime_error("R U Tam ofigeli ______255");
                        }
                        break;
                    }
                }
                if (positive) ++delta;
                else --delta;
            }
        } else {

            bool positive = true;
            while (true) {
                if (rival_field->is_out_of_bounds(last_ship_x, last_ship_y + delta)) {
                    if (positive) {
                        delta = -1;
                        positive = false;
                    } else throw runtime_error("R U Tam ofigeli_________5");
                }

                cout << "<<< Bot continues smart attack on  " << last_ship_x + delta << ":" << last_ship_y << endl;
                switch (rival_field->attack(last_ship_x, last_ship_y + delta)) {
                    case miss:
                        return false;
                    case damage: { // ранили, но не убили
                        break;
                    }
                    case destroy:
                        last_ship_x = last_ship_y = -1;
                        position = unknown;
                        return random_attack();
                    case win:
                        return true; // победили
                    case already_attacked: {
                        // мы продолжаем атаку в эту же сторону, если клетка, на которую мы наткнулись - корабль,
                        // который мы просто уже атаковали ранее
                        if (rival_field->is_attacked_ship(last_ship_x, last_ship_y + delta)) break;
                        else {
                            // если же мы уже упёрлись в воду, то нужно развернуться
                            if (positive) {
                                delta = 0;
                                positive = false;
                            } else throw runtime_error("R U Tam ofigeli ______254");
                        }
                        break;
                    }
                }
                if (positive) ++delta;
                else --delta;
            }

        }
    }
}

#endif //BOY_2_BOT_H