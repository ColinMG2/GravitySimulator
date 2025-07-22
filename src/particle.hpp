#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

struct Particle {
    sf::Vector2f position;
    sf::Vector2f position_last;
    sf::Vector2f acceleration;
    float radius = 100.0f;
    float mass = 1.0f;

    Particle() = default;
    Particle(sf::Vector2f position_, float radius_, float mass_)
        : position{position_},
          position_last{position_},
          acceleration{0.0f, 0.0f}, // start with intially zero acceleration
          radius{radius_},
          mass{mass_} {}

    void update(float dt) {
        sf::Vector2f displacement = position - position_last;
        position_last = position;
        position = position + displacement + acceleration * (dt*dt);
        acceleration = {0.0f, 0.0f}; // Resets acceleration for next frame
    }

    void accelerate(sf::Vector2f a) {
        acceleration += a;
    }

    sf::Vector2f getVelocity() {
        return position - position_last;
    }

    void addForce(const sf::Vector2f& force) {
        acceleration += force / mass; // F = ma
    }


};

#endif