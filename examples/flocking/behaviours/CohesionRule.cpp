#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2 CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 cohesionForce;

    // todo: add your code here to make a force towards the center of mass
    // hint: iterate over the neighborhood
    for (int i = 0; i < neighborhood.size(); i++)
    {
        if (!neighborhood.empty()) {
            Vector2 position = boid->transform.position;
            int countCloseFlockmates = 0;

            Vector2 cm(0, 0);

            float distance = 0;
            int divisor = 0;

            Vector2 boidPos = boid->transform.position;

            for (int i = 0; i < neighborhood.size(); i++) {
                cm += neighborhood[i]->transform.position;
                divisor++;
            }

            // calculate center of mass
            cm /= divisor;

            Vector2 direction = cm - boidPos;

            distance = direction.getMagnitude();

            if (distance < 0.1)
                distance = 0.1;

            cohesionForce = (direction / distance)*this->weight; 
        }

        cohesionForce = Vector2::normalized(cohesionForce);

        return cohesionForce;
    }

    return cohesionForce;
}