#include <iostream>
#include <format>
#include <SFML/Graphics.hpp>
#include "GameSystem.hpp"

int WinMain()
{   
    GameSystem system{};
    system.run();

    return 0;
}