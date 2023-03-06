#include <ProjectSilver/SilverGame.hpp>
#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    silver::SilverGame game;

    game.setFPS(4);
    game.run();

    return 0;
}