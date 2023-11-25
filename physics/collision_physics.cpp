#include <cmath>
#include <iostream>

class Particle {
 public:
    double mass;
    double velocity;

    Particle(double m, double v) : mass(m), velocity(v) {}

    // Function to compute kinetic energy
    double kineticEnergy() const { return 0.5 * mass * velocity * velocity; }

    // Function to update velocity after a collision
    void updateVelocity(double newVelocity) { velocity = newVelocity; }
};

// Function to simulate elastic collision between two particles
void elasticCollision(Particle& particle1, Particle& particle2) {
    double u1 = particle1.velocity;
    double u2 = particle2.velocity;
    double m1 = particle1.mass;
    double m2 = particle2.mass;

    // Using conservation of linear momentum and kinetic energy
    double v1 = ((m1 - m2) * u1 + 2 * m2 * u2) / (m1 + m2);
    double v2 = ((m2 - m1) * u2 + 2 * m1 * u1) / (m1 + m2);

    particle1.updateVelocity(v1);
    particle2.updateVelocity(v2);
}

// Function to simulate inelastic collision between two particles
void inelasticCollision(Particle& particle1, Particle& particle2,
                        double coefficientOfRestitution) {
    double u1 = particle1.velocity;
    double u2 = particle2.velocity;
    double m1 = particle1.mass;
    double m2 = particle2.mass;

    // Using the formula for inelastic collision
    double v = (m1 * u1 + m2 * u2) / (m1 + m2);

    // Updating velocities based on the coefficient of restitution
    double v1 = coefficientOfRestitution * v;
    double v2 = (1.0 - coefficientOfRestitution) * v;

    particle1.updateVelocity(v1);
    particle2.updateVelocity(v2);
}

int main() {
    // Create two particles with masses and velocities
    Particle particle1(2.0, 5.0);
    Particle particle2(1.5, -2.0);

    // Display initial kinetic energies
    std::cout << "Initial Kinetic Energies:" << std::endl;
    std::cout << "Particle 1: " << particle1.kineticEnergy() << std::endl;
    std::cout << "Particle 2: " << particle2.kineticEnergy() << std::endl;

    // Simulate an elastic collision
    elasticCollision(particle1, particle2);

    // Display kinetic energies after elastic collision
    std::cout << "\nKinetic Energies After Elastic Collision:" << std::endl;
    std::cout << "Particle 1: " << particle1.kineticEnergy() << std::endl;
    std::cout << "Particle 2: " << particle2.kineticEnergy() << std::endl;

    // Reset particles for inelastic collision
    particle1.updateVelocity(5.0);
    particle2.updateVelocity(-2.0);

    // Simulate an inelastic collision with a coefficient of restitution
    double coefficientOfRestitution = 0.5;
    inelasticCollision(particle1, particle2, coefficientOfRestitution);

    // Display kinetic energies after inelastic collision
    std::cout << "\nKinetic Energies After Inelastic Collision:" << std::endl;
    std::cout << "Particle 1: " << particle1.kineticEnergy() << std::endl;
    std::cout << "Particle 2: " << particle2.kineticEnergy() << std::endl;

    return 0;
}
