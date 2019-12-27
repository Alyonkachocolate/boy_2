
#ifndef BOY_2_CELL_H
#define BOY_2_CELL_H

//free -
//ship -
//discovered - пусиая, но стреляли
//attack - клетка, которую атаковали
//discovered - клетки около убитого коробля
enum Cell {

    /**
     * Не атакованная и пустая
     */
            freee,
    /**
     * Корабль, но не атакованная
     */
            ship,
    /**
     *
     */
            discovered,
    /**
     *
     */
            attacked
};

bool is_ship(const Cell &cell) {
    return cell == ship || cell == attacked;
}

bool is_empty(const Cell &cell) {
    return cell == freee || cell == discovered;
}


#endif //BOY_2_CELL_H
