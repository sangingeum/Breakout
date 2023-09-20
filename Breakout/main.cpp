#include <iostream>
#include <format>
#include <SFML/Graphics.hpp>
#include "GameSystem.hpp"
#include "Profiler.hpp"
int WinMain()
{   
    PROFILE_FUNCTION();
    GameSystem system{};
    system.run();

    return 0;
}