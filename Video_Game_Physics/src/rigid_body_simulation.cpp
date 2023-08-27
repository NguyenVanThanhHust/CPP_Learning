#include <iostream>
#include <random>
#include <chrono>
#include <thread>


using std::cout;
using std::cin;
using std::endl;

#define NUM_RIGID_BODIES 1
struct Vector2d {
    float x;
    float y;
};

struct BoxShape {
    float width;
    float height;
    float mass;
    float momentOfInertia;
};

// Calculate the inertia of box shape
void CalculateInertia(BoxShape &box_shape)
{
    float m = box_shape.mass;
    float w = box_shape.width;
    float h = box_shape.height;
    float inertia = m*(h*h + w*w)/12;
    box_shape.momentOfInertia = inertia;
};

// Two dimension rigid body
struct RigidBody {
    Vector2d position;
    Vector2d linearVelocity;
    float angle;
    float angularVelocity;
    Vector2d force;
    float torque;
    BoxShape shape;
};

RigidBody rigidBodies[NUM_RIGID_BODIES];

void PrintRigidBodies() {
    for (int i = 0; i < NUM_RIGID_BODIES; i++)
    {
        cout << "Object: " << i << " x: " << rigidBodies[i].position.x << " y: "<<rigidBodies[i].position.y<< " m: "<<rigidBodies[i].shape.mass << endl;
    }
};

void InitializeRigidBodies() {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<float> distr_position(20.0, 80.0); // define the range
    std::uniform_real_distribution<float> distr_angle(0, 360.0); // define the range
    for (int i = 0; i < NUM_RIGID_BODIES; i++)
    {
        rigidBodies[i].position= { distr_position(gen), distr_position(gen) };
        rigidBodies[i].angle= distr_angle(gen);
        rigidBodies[i].linearVelocity = { 0, 0 };
        rigidBodies[i].angularVelocity = 0;

        BoxShape shape;
        shape.mass = i;
        shape.width = distr_position(gen) - 10;
        shape.height = distr_position(gen) - 10;
        CalculateInertia(shape);
        rigidBodies[i].shape = shape; 
    }
};

// Apply force a point in the body
void ComputeForceAndTorque(RigidBody &rigidBody)
{
    Vector2d force{0, 100};
    rigidBody.force = force;
    Vector2d arm_vector = {rigidBody.shape.width / 2, rigidBody.shape.height};
    rigidBody.torque = arm_vector.x * force.y - arm_vector.y * force.x;
}

void RunSimulation()
{
    float totalSimulationTime = 10;
    float currentTime = 0;
    float dt = 1;
    
    InitializeRigidBodies();
    PrintRigidBodies();

    while (currentTime < totalSimulationTime)           
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        for (int i = 0; i < NUM_RIGID_BODIES; i++)
        {
            ComputeForceAndTorque(rigidBodies[i]);
            Vector2d linearAcceleration{rigidBodies[i].force.x / rigidBodies[i].shape.mass, rigidBodies[i].force.y / rigidBodies[i].shape.mass};
            rigidBodies[i].linearVelocity.x += linearAcceleration.x * dt;
            rigidBodies[i].linearVelocity.y += linearAcceleration.y * dt;
            rigidBodies[i].position.x += rigidBodies[i].linearVelocity.x * dt;
            rigidBodies[i].position.y += rigidBodies[i].linearVelocity.y * dt;
            float angularAcceleration = rigidBodies[i].torque / rigidBodies[i].shape.momentOfInertia;
            rigidBodies[i].angularVelocity += angularAcceleration * dt;
            rigidBodies[i].angle += rigidBodies[i].angularVelocity * dt;
        }
        PrintRigidBodies();
        currentTime += dt;
    }
};

int main()
{
    RunSimulation();
    return 0;
}