#ifndef SOLVER_HPP
#define SOLVER_HPP

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

    void update() {
        applyGravity();
        applyBoundary();
        updateObjects(step_dt);

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
    std::vector<Particle> objects;
    sf::Vector2f gravity = {0.0f, 1000.0f};
    sf::Vector2f boundary_center = {conf::window_size_f.x/2, conf::window_size_f.y/2};
    float boundary_radius = conf::window_size_f.x/2;
    float step_dt = conf::dt;

    void applyGravity() {
        for (auto &obj : objects)
            obj.accelerate(gravity);
    }

    void applyBoundary() {
        for (auto &obj : objects) {
            const sf::Vector2f r = boundary_center - obj.position;
            const float dist = std::sqrt(r.x * r.x + r.y * r.y);
            if (dist > boundary_radius - obj.radius) {
                const sf::Vector2f n = r/dist;
                const sf::Vector2f vel = obj.getVelocity();
                if (vel.x * n.x + vel.y * n.y < 0) {
                    obj.position = boundary_center - n * (boundary_radius - obj.radius + 10.0f);
                    sf::Vector2f reflected_vel = vel - 2.0f * (vel.x * n.x + vel.y * n.y) * n;
                    obj.setVelocity(reflected_vel, step_dt);
                    std::cout << "Before: " << vel.x << ", " << vel.y << " | After: " << reflected_vel.x << ", " << reflected_vel.y << std::endl;
                }
                else {
                    obj.position = boundary_center - n * (boundary_radius - obj.radius + 10.0f);
                    obj.setVelocity(vel, step_dt);
                }
                
            }
        }
    }

    void updateObjects(float dt) {
        for (auto &obj : objects) {
            obj.update(dt);
        }
    }
};

#endif