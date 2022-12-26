#include <iostream>
#include "Game.h"

int main()
{

    setlocale(LC_ALL, "Russian");

    

    int i = -1;

    cin >> i;

    cout << "0 - Создать новую игру\n1 - заргузить сохранение" << endl;

    if (i == 0) {
        Game game = Game::create_new_game();
        game.start();
    }
    else {
        Game game = Game::load_from_file();
        game.start();
    }

}
