
#ifndef BOY_2_CELL_H
#define BOY_2_CELL_H

//free -
//ship -
//discovered - пусиая, но стреляли
//attack - клетка, которую атаковали
//busy - клетки около убитого коробля
enum Cell {

    /**
     * Не атакованная и пустая
     */
    freee,
    /**
     * Корабль, но не атакованная
     */
    ship, discovered, attacked, busy
};

bool is_ship(const Cell &cell) {
    return cell == ship || cell == attacked;
}

bool is_empty(const Cell &cell) {
    return cell == freee || cell == discovered || cell == busy;
}


#endif //BOY_2_CELL_H
