#include <iostream>
#include <random>
#include <chrono>
#include <thread>


using std::cout;
using std::cin;
using std::endl;

#define NUM_PARTICLES 2

struct Vector2d {
    float x;
    float y;
};

struct Particle {
    Vector2d position;
    Vector2d velocity;
    float mass;
};


// Define global array of particles
Particle particles[NUM_PARTICLES];

// Print all partical position to outputs
void PrintParticles()
{
    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        cout << "Particle: " << i << " x: " << particles[i].position.x << " y: " << particles[i].position.y << endl;
    }
}

// Initialize all particals with random position, 
// zero velocity and 1kg mass
void InitializePosition()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<float> distr(20.0, 80.0); // define the range
    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        particles[i].position= { distr(gen), distr(gen) };
        particles[i].velocity = { 0, 0 }; 
        particles[i].mass = 1;
    }
}   

// Just applied gravity force
Vector2d ComputeForce(Particle& particle)
{
    Vector2d v = { 0, particle.mass * -9.81 };
    return v;
};

void runSimulation()
{
    int totalSimulationTime = 10;
    int currentTime = 0;
    int dt = 1;

    InitializePosition();
    PrintParticles();
    while (currentTime < totalSimulationTime)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * dt));
        for (int i = 0; i < NUM_PARTICLES; i++)
        {
            Vector2d force = ComputeForce(particles[i]);
            Vector2d acceleration = { force.x / particles[i].mass, force.y / particles[i].mass };
            particles[i].velocity.x += acceleration.x * dt;
            particles[i].velocity.y += acceleration.y * dt;
            particles[i].position.x += particles[i].velocity.x * dt;
            particles[i].position.y += particles[i].velocity.y * dt;
        }
        PrintParticles();
        currentTime += dt;
    }
};

int main()
{
    runSimulation();
    return 0;
}