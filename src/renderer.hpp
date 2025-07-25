#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "solver.hpp"

class Renderer {
public:
    Renderer(sf::RenderTarget& target_) : target(target_) {}

    void render(Solver& solver) const {
        target.clear(sf::Color::White);
        
        sf::Vector3f boundary = solver.getBoundary();
        sf::Vector2f boundary_center = {boundary.x, boundary.y};
        float boundary_radius = boundary.z;

        sf::CircleShape bound;
        bound.setRadius(boundary_radius);
        bound.setPosition(boundary_center - sf::Vector2f(boundary_radius, boundary_radius));
        bound.setFillColor(sf::Color::Black);
        bound.setPointCount(64);
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

#endif