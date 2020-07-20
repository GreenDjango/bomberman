/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/
#include "Game.hpp"

int main(int argc, char const *argv[])
{
    if (argc >= 2 && (!strcmp("-h", argv[1]) || !strcmp("--help", argv[1]))) {
        printf("%s [OPTION]...\n"
        "    -h          : show help\n"
        "    -silent     : mute sound and music game\n"
        "    -direct3D9  : set video driver to windows\n"
        "    -openGL     : set video driver to linux (default)\n", argv[0]);
        return 0;
    }
    std::srand(std::time(nullptr));
    Game bomberman{argv};

    bomberman.loadObjects();
    bomberman.run();
    return 0;
}