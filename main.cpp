#include <iostream>
#include "Game.h"
#include "Attack.h"
#include "Bot.h"

using std::cout;
using std::cin;
using std::endl;


int main() {
    Game user_game; //создание Game для пользователя и бота
    Game comp_game;
    Bot bot(&comp_game, &user_game);
   // user_game.user_arrangement();
    bot.place_ships();

    cout << "=== bot's field ===" << endl;
    comp_game.print_known();
    cout << "=== your field ===" << endl;
    user_game.print_everything();

    bool game_over = false;
    bool player = true;
    while (true) {
        cout << "=========================================" << endl;

        // user
        if (player) {
            while (true) {
                int x, y;
                cout << "Your turn" << endl;
                {
                    char char_x;
                    do {
                        cin >> char_x >> y;
                        x = int(char_x) - 65;
                    } while (comp_game.is_out_of_bounds(x, y));
                }

                bool exit = false;
                switch (comp_game.attack(x, y)) {
                    case miss:
                        cout << "You missed" << endl;
                        exit = true;
                        break;
                    case damage:
                        cout << "You damaged the ship" << endl;
                        exit = false;
                        break;
                    case destroy:
                        cout << "You destroyed the ship" << endl;
                        exit = false;
                        break;
                    case win:
                        cout << "You won!" << endl;
                        exit = true;
                        game_over = true;
                        break;
                    case already_attacked:
                        cout << "You have already attacked at this coordinates, try again" << endl;
                        exit = false;
                        break;
                }
                cout << "=== bot's field ===" << endl;
                comp_game.print_known();
                cout << endl;
                if (exit) break;
            }
        } else {
            const auto bot_won = bot.play();
            cout << "=== your field ===" << endl;
            user_game.print_everything();
            cout << endl;
            if (bot_won) {
                cout << "Bot won!!!!!!!" << endl;
                game_over = true;
            }
        }

        if (game_over) break;

        player = !player;
    }

    return 0;
}