#pragma once
#include "particle.hpp"
#include "configurations.hpp"
#include <iostream>
#include <cmath>

class Solver {
public:
    Solver() = default;

    Particle& addObject(sf::Vector2f position, float radius, float mass) {
        Particle newParticle = Particle(position, radius, mass);
        return objects.emplace_back(newParticle);
    }

    void mousePull(sf::Vector2f pos) {
    for (Particle& obj : objects) {
        sf::Vector2f dir = pos - obj.position;
        float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
        obj.accelerate(dir * std::max(0.0f, 10 * (120.0f - dist)));
    }
}

    void mousePush(sf::Vector2f pos) {
    for (Particle& obj : objects) {
        sf::Vector2f dir = pos - obj.position;
        float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
        obj.accelerate(dir * std::max(0.0f, -10 * (120.0f - dist)));
    }
}

    void update() {
        float substeps_dt = step_dt / substeps;
        for (int i = 0; i < substeps_dt; i++) {
            applyGravity();
            applyBoundary();
            updateObjects(substeps_dt);
        }

    }

    std::vector<Particle>& getObjects() {
        return objects;
    }

    void setBoundary(sf::Vector2f position, float radius) {
        boundary_center = position;
        boundary_radius = radius;

    }

    sf::Vector3f getBoundary() const {
        return {boundary_center.x, boundary_center.y, boundary_radius};
    }

private:
    std::vector<Particle>   objects;
    sf::Vector2f            gravity         = {0.0f, 1000.0f};
    sf::Vector2f            boundary_center = {conf::window_size_f.x, conf::window_size_f.y};
    float                   boundary_radius = conf::window_size_f.x / 2;
    float                   step_dt         = conf::dt;
    int                     substeps        = 8;

    void applyGravity() {
        for (auto &obj : objects)
            obj.accelerate(gravity);
    }

    void applyBoundary() {
        for (auto &obj : objects) {
            const sf::Vector2f r = boundary_center - obj.position;
            const float dist = sqrt(r.x * r.x + r.y * r.y);
            if (dist > boundary_radius - obj.radius) {
                const sf::Vector2f n = r/dist;
                const sf::Vector2f vel = obj.getVelocity();
                obj.position = boundary_center - n * (boundary_radius - obj.radius);
                sf::Vector2f reflected_vel = vel - 2.0f * (vel.x * n.x + vel.y * n.y) * n;
                obj.setVelocity(reflected_vel, 1.0f); // problem was inputting too small of dt input so the position didn't change enough and ball got stuck
                std::cout << "Before: " << vel.x << ", " << vel.y 
                          << " | After: " << reflected_vel.x << ", " << reflected_vel.y << std::endl;
                
            }
        }
    }

    void updateObjects(float dt) {
        for (auto &obj : objects) {
            obj.update(dt);
        }
    }
};