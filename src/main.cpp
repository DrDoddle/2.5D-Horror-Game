#include <SFML/Graphics.hpp>

#include "renderer.h"
#include "util.h"
#include "wad.h"

int main() {
    constexpr unsigned RENDER_WIDTH = 320;
    constexpr unsigned RENDER_HEIGHT = 200;

    DEBUG_LOG("Opening Window");
    sf::RenderWindow window(sf::VideoMode({1280, 800}), "DoomClone");
    DEBUG_LOG("Window Initialized");

    DEBUG_LOG("Initializing Map");
    World world;
    {
        UdmfMapLoader loader;
        if (auto loaded = loader.loadFromFile("C:/Users/joshu/Documents/programming/cc++/doomclone/MAP01.wad"))
            world.map() = loaded.value();
        else
            return 1;
    }
    DEBUG_LOG("Map Loaded");
    Player player;
    world.initPlayer(player);
    Renderer renderer(RENDER_WIDTH, RENDER_HEIGHT);

    sf::Sprite screen(renderer.texture());

    screen.setScale({
        static_cast<float>(window.getSize().x) / RENDER_WIDTH,
        static_cast<float>(window.getSize().y) / RENDER_HEIGHT
    });

    sf::Clock clock;

    int frames = 0;
    float time = 0.f;
    DEBUG_LOG("Starting main loop");
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        const float deltaTime = clock.restart().asSeconds();
        time += deltaTime;
        // DEBUG_LOG(deltaTime);
        if (time >= 1.0f) {
            std::cout << frames << " ";
            frames = 0;
            time = 0.f;
        }


        // Update player/world here
        player.update(deltaTime);

        renderer.render(world, player);

        window.clear();

        window.draw(screen);

        window.display();
        frames++;
    }
}
