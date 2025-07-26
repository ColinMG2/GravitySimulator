#include <SFML/Graphics.hpp>
#include "events.hpp"
#include "configurations.hpp"
#include "renderer.hpp"
#include "solver.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 1;
    auto window = sf::RenderWindow(sf::VideoMode({conf::window_size.x, conf::window_size.y}),
                                                "Gravity Simulator", sf::Style::Default, sf::State::Windowed);
    window.setFramerateLimit(conf::max_framerate);
    Renderer renderer{window};
    Solver solver;
    solver.setBoundary({conf::window_size_f.x/2, conf::window_size_f.y/2}, (conf::window_size_f.x - 20.0f) / 2);
    
    sf::Vector2f spawn_position = {420.0f, 100.0f};
    float radius = 10.0f;
    float mass = 1.0f;
    auto& object = solver.addObject({spawn_position.x, spawn_position.y}, radius, mass);

    while (window.isOpen())
    {
        ProcessEvents(window);
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            float ratio = 840.0f / window.getSize().x; // Correct for scaled window
            sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) * ratio;
            solver.mousePull(pos);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            float ratio = 840.0f / window.getSize().x; // Correct for scaled window
            sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) * ratio;
            solver.mousePush(pos);
        }        

        solver.update();
        window.clear(sf::Color::White);
        renderer.render(solver);
        window.display();
    }
}