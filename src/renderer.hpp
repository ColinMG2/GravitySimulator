#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "solver.hpp"

class Renderer {
public:
    Renderer(sf::RenderTarget& target_) : target(target_) {}

    void render(Solver& solver) const {
        target.clear(sf::Color::White);
        
        sf::Vector3f boundary = solver.getBoundary();
        sf::CircleShape bound{boundary.z};
        bound.setOrigin({boundary.z, boundary.z});
        bound.setPosition({boundary.x, boundary.y});
        bound.setFillColor(sf::Color::Black);
        bound.setPointCount(128);
        target.draw(bound);

        sf::CircleShape circle;
        circle.setPointCount(32);
        const auto& objects = solver.getObjects();
        for (const auto& obj : objects) {
            circle.setPosition(obj.position);
            circle.setRadius(obj.radius);
            circle.setOrigin({obj.radius, obj.radius});
            circle.setFillColor(sf::Color::Cyan);
            target.draw(circle);
        }

    }


private:
    sf::RenderTarget& target;
};