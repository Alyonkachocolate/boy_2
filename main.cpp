#include <iostream>
#include "Game.h"
#include "Cell.h"
#include "Attack.h"

using std::cout;
using std::cin;
using std::endl;

Cell comp_arrangement(int x, int y) {
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
                if (k == 1 && chip[i][j] != ship) chip[i][j] = busy;
            }
        }
    } else {
        line = start_;
        column = rand1;
        for (int i = line - 1; i <= line + 4; i++) {
            for (int j = column - 1; j <= column + 1; j++) {
                if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                if (k == 1 && chip[i][j] != ship) chip[i][j] = busy;
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
                    if (k == 1) if (chip[i][j] != ship) chip[i][j] = busy;
                }
            }
        } else {
            line = start_;
            column = rand1;
            for (int i = line - 1; i <= line + 3; i++) {
                for (int j = column - 1; j <= column + 1; j++) {
                    if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                    if (k == 1 && chip[i][j] != ship) chip[i][j] = busy;
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
                    if (k == 1) if (chip[i][j] != ship) chip[i][j] = busy;
                }
            }
        } else {
            line = start_;
            column = rand1;
            for (int i = line - 1; i <= line + 2; i++) {
                for (int j = column - 1; j <= column + 1; j++) {
                    if ((i < 10) && (i >= 0) && (j < 10) && (j >= 0)) k = 1; else k = 0;
                    if (k == 1 && chip[i][j] != ship) chip[i][j] = busy;
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
                if (k == 1) if (chip[i][j] != ship) chip[i][j] = busy;
            }
        }

    }
    return chip[x][y];
}

int main() {
    Game user_game; //создание Game для пользователя и бота
    Game comp_game;
    // рандомное заполение для бота
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            comp_game.place(i, j, comp_arrangement(i, j));
        }
    }

//    // вывод полный
    //comp_game.print_fully();
//    // заполенение пользователем
//    user_game.user_arrangement();
//    // вывод полный
//    user_game.print_fully();
//    // вывод красивый
    comp_game.print_beat();
    //cout<<comp_game.end();
    while (!comp_game.end() || !user_game.end()) {
        int x, y;
        cout << "Your turn" << endl;
        {
            char char_x;
            do {
                cin >> char_x >> y;
                x = int(char_x) - 65;
            } while (!comp_game.is_out_of_bounds(x, y) || !comp_game.is_cell_visited(x, y));
        }
        /*
        char X;
        int x, y;
        cout << x << ' ' << y << endl;

        while (!comp_game.is_out_of_bounds(x, y) || !comp_game.get_cell_attack(x, y)) {
            cout << "Выход за гарницы поля или уже атакованная клетка. Введите заново" << endl;
            cin >> X >> y;
            x = int(X) - 65;
        }
         */
        if (comp_game.get_cell_miss(x, y)) {
            cout << comp_game.get_cell_miss(x, y) << endl;
            comp_game.place(x, y, miss);
            cout << comp_game.get_cell_miss(x, y) << endl;
            comp_game.print_fully();
        }
        //else {
//            if (comp_game.get_cell_damage(x, y)) {
//
//
//
//                comp_game.place(x, y, damage); comp_game.print_fully();}
//        }


    }
    return 0;
}