#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2 AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 averageVelocity = Vector2::zero();

    // todo: add your code here to align each boid in a neighborhood
    // hint: iterate over the neighborhood

    if (!neighborhood.empty()) {
        Vector2 position = boid->transform.position;
        int countCloseFlockmates = 0;

        Vector2 averageDirection(0, 0);

        float distance = 0;
        int divisor = 0;

        Vector2 boidPos = boid->transform.position;

        for (int i = 0; i < neighborhood.size(); i++) {
            averageDirection += neighborhood[i]->getVelocity() / neighborhood[i]->getVelocity().getMagnitude();
            divisor++;
        }

        // calculate center of mass
        averageDirection /= divisor;

        if (distance < 0.1)
            distance = 0.1;

        averageVelocity = (averageDirection * distance) * this->weight;
    }

    averageVelocity = Vector2::normalized(averageVelocity);

    return averageVelocity;

    return Vector2::normalized(averageVelocity);
}