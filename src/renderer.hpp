#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "solver.hpp"

class Renderer {
public:
    Renderer(sf::RenderTarget& target_) : target(target_) {}

    void render(Solver& solver) const {
        target.clear();
        sf::CircleShape circle;
        circle.setPointCount(32);
        const auto& objects = solver.getObjects();
        for (const auto& obj : objects) {
            circle.setPosition(obj.position);
            circle.setRadius(obj.radius);
            // circle.setScale({obj.radius, obj.radius});
            circle.setFillColor(sf::Color::Cyan);
            target.draw(circle);
        }

    }


private:
    sf::RenderTarget& target;
};

#endif