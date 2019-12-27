

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
    int x, y;
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
                for (int j = column - 1; j <= column + 3; j++) {
                    if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                    if (k == 1) if (chip[i][j] != ship) chip[i][j] = discovered;
                }
            }
        } else {
            line = start_;
            column = rand1;
            for (int i = line - 1; i <= line + 3; i++) {
                for (int j = column - 1; j <= column + 1; j++) {
                    if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                    if (k == 1 && chip[i][j] != ship) chip[i][j] = discovered;
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
                for (int j = column - 1; j <= column + 2; j++) {
                    if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                    if (k == 1) if (chip[i][j] != ship) chip[i][j] = discovered;
                }
            }
        } else {
            line = start_;
            column = rand1;
            for (int i = line - 1; i <= line + 2; i++) {
                for (int j = column - 1; j <= column + 1; j++) {
                    if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                    if (k == 1 && chip[i][j] != ship) chip[i][j] = discovered;
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

    own_field->undiscover();
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

        if (rival_field->is_cell_visited(x, y)) {
            for (x = 0; x < 10; ++x) {
                bool free_cell_found = false;
                for (y = 0; y < 10; ++y) if (!rival_field->is_cell_visited(x, y)) {
                    free_cell_found = true;
                    break;
                }
                if (free_cell_found) break;
            }
        }

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

bool Bot::attack_ship() {
    // попытка продолжения атаки корабля
    if (position == unknown) {
        int x = last_ship_x;
        int y = last_ship_y;
        int variant = rand() % 4;

        bool exit = true;
        // находим случайную сторону, которую можно атаковать
        while (true) {
            switch (variant) {
                case 0:
                    if (x != 9 && !rival_field->is_cell_visited(x + 1, y)) {
                        ++x;
                        exit = true;
                    } else ++variant;
                    break;
                case 1:
                    if (x != 0 && !rival_field->is_cell_visited(x - 1, y)) {
                        --x;
                        exit = true;
                    } else ++variant;
                    break;
                case 2:
                    if (y != 9 && !rival_field->is_cell_visited(x, y + 1)) {
                        ++y;
                        exit = true;
                    } else ++variant;
                    break;
                case 3:
                    if (y != 0 && !rival_field->is_cell_visited(x, y - 1)) {
                        --y;
                        exit = true;
                    } else variant = 0;
                    break;
            }
            if (exit) break;
        }

        switch (rival_field->attack(x, y)) {
            case miss:
                return false;
            case damage: { // ранили, но не убили
                position = (x == last_ship_x) ? gorizont : vertical;
                return attack_ship();
            }
            case destroy:
                last_ship_x = -1;
                last_ship_y = -1;
                position = unknown;
                break; // убили корабль
            case win:
                return true; // победили
            case already_attacked:
                throw runtime_error("R U Tam ofigeli_______2");
        }
    }

    while (true) {
        int s = 1;
        if (position == vertical) {

            bool positive = true;
            while (true) {
                if (rival_field->is_out_of_bounds(last_ship_x + s, last_ship_y)) {
                    if (positive) {
                        s = -1;
                        positive = false;
                    } else throw runtime_error("R U Tam ofigeli ______3");
                }

                switch (rival_field->attack(last_ship_x + s, last_ship_y)) {
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
                    case already_attacked:
                        throw runtime_error("R U Tam ofigeli______4");
                }
                if (positive) ++s;
                else --s;
            }
        } else {

            bool positive = true;
            while (true) {
                if (rival_field->is_out_of_bounds(last_ship_x, last_ship_y + s)) {
                    if (positive) {
                        s = -1;
                        positive = false;
                    } else throw runtime_error("R U Tam ofigeli_________5");
                }

                switch (rival_field->attack(last_ship_x, last_ship_y + s)) {
                    case miss:
                        return false;
                    case damage: { // ранили, но не убили
                        break;
                    }
                    case destroy:
                        last_ship_x = -1;
                        last_ship_y = -1;
                        position = unknown;
                        return random_attack();
                    case win:
                        return true; // победили
                    case already_attacked:
                        throw runtime_error("R U Tam ofigeli________6");
                }
                if (positive) ++s;
                else --s;

            }

        }

    }
}

#endif //BOY_2_BOT_H