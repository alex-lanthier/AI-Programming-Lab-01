#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

Vector2 SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Try to avoid boids too close
    Vector2 separatingForce = Vector2::zero();

    float desiredDistance = desiredMinimalDistance;

    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
    if (!neighborhood.empty()) {
        Vector2 position = boid->transform.position;
        int countCloseFlockmates = 0;

        Vector2 cm(0, 0);

        float distance = 0;
        int divisor = 0;

        Vector2 boidPos = boid->transform.position;

        for (int i = 0; i < neighborhood.size(); i++) {
            if (Vector2::getDistance(neighborhood[i]->getPosition(), boid->getPosition()) < desiredDistance) {
                cm += neighborhood[i]->transform.position;
                divisor++;
            }
        }

        if (divisor > 0) {
            // calculate center of mass
            cm /= divisor;

            Vector2 direction = boidPos - cm;

            distance = direction.getMagnitude();

            if (distance < 0.1)
                distance = 0.1;

            separatingForce = (direction / distance) * this->weight;
        }

        separatingForce = Vector2::normalized(separatingForce);
    }

    return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    bool valusHasChanged = false;

    if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
        valusHasChanged = true;
    }

    return valusHasChanged;
}
