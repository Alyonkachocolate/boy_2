
#ifndef BOY_2_CELL_H
#define BOY_2_CELL_H

enum Cell {

    /**
     * Неатакованная пустая
     */
            freee,
    /**
     * Неатакованный корабль
     */
            ship,
    /**
     * Атакованная пустая
     */
            discovered,
    /**
     * Атакованный корабль
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
