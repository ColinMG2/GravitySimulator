#include <SFML/Graphics.hpp>
#include "events.hpp"
#include "configurations.hpp"
#include "renderer.hpp"
#include "solver.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({conf::window_size.x, conf::window_size.y}),
                                                "Gravity Simulator", sf::Style::Default, sf::State::Windowed);
    window.setFramerateLimit(conf::max_framerate);
    Renderer renderer{window};
    Solver solver;
    sf::Vector2f spawn_position = {420.0f, 100.0f};
    float radius = 10.0f;
    float mass = 1.0f;
    auto& object = solver.addObject({spawn_position.x, spawn_position.y}, radius, mass);


    while (window.isOpen())
    {
        ProcessEvents(window);
        
        solver.update();
        window.clear();
        renderer.render(solver);
        window.display();
    }
}