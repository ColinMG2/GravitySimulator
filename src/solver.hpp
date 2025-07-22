#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "particle.hpp"
#include "configurations.hpp"
#include <iostream>

class Solver {
public:
    Solver() = default;
    Particle& addObject(sf::Vector2f position, float radius, float mass) {
        Particle newParticle = Particle(position, radius, mass);
        return objects.emplace_back(newParticle);
    }

    void update() {
        applyGravity();
        updateObjects(step_dt);

    }

    std::vector<Particle>& getObjects() {
        return objects;
    }

private:
    std::vector<Particle> objects;
    sf::Vector2f gravity = {0.0f, 1000.0f};
    float step_dt = conf::dt;

    void applyGravity() {
        for (auto &obj : objects)
            obj.accelerate(gravity);
    }

    void updateObjects(float dt) {
        for (auto &obj : objects)
            obj.update(dt);
    }
};

#endif