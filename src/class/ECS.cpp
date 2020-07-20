/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ECSCore
*/

#include "ECS.hpp"
#include "component/MotionComponent.hpp"
#include "component/TransformComponent.hpp"
#include "component/GraphicsComponent.hpp"
#include "component/ActionEventComponent.hpp"
#include "component/TimeEventComponent.hpp"
#include "component/InteractionComponent.hpp"

void ECS::renderSystem(IEntityComponent *e, const irr::f32 frameDeltaTime)
{
    auto t = (TransformComponent *)e->getComponent(IEntityComponent::Component::Transform);
    // Compute System
    auto m = (MotionComponent *)e->getComponent(IEntityComponent::Component::Motion);
    if (t && m) {
        m->update(frameDeltaTime);
        t->update(m, frameDeltaTime);
    }
    // ---

    // Render System
    if (t && t->needUpdate() == true) {
        auto g = (GraphicsComponent *)e->getComponent(IEntityComponent::Component::Graphics);
        if (g) {
            g->update(t);
        }
    }
    // ---
}

void ECS::eventSystem(IEntityComponent *e, const irr::f32 frameDeltaTime)
{
    auto t = (TimeEventComponent *)e->getComponent(IEntityComponent::Component::TimeEvent);
    if (t)
        t->update(frameDeltaTime);
}

void ECS::actionSystem(IEntityComponent *e, void *game)
{
    auto a = (ActionEventComponent *)e->getComponent(IEntityComponent::Component::ActionEvent);
    if (a && a->getNbAction() > 0)
        a->processAction(game);
    // ---
}

#include <iostream>

void ECS::interactionSystem(IEntityComponent *e, std::vector<IEntityComponent *> &entities)
{
    auto i = (InteractionComponent *)e->getComponent(IEntityComponent::Component::Interaction);
    auto t = (TransformComponent *)e->getComponent(IEntityComponent::Component::Transform);
    if (!i || !t)
        return;
    for (auto *e2 : entities) {
        auto i2 = (InteractionComponent *)e2->getComponent(IEntityComponent::Component::Interaction);
        auto t2 = (TransformComponent *)e2->getComponent(IEntityComponent::Component::Transform);
        if (e == e2 || !i2 || !t2)
            continue;
        // Range
        if (i->getRange().X <= 0 || i2->getRange().X < 0)
            continue; // can't take object
        if (t->getPos().X - i->getRange().X < t2->getPos().X && t2->getPos().X < t->getPos().X + i->getRange().X
        && t->getPos().Y - i->getRange().Y < t2->getPos().Y && t2->getPos().Y < t->getPos().Y + i->getRange().Y
        && t->getPos().Z - i->getRange().Z < t2->getPos().Z && t2->getPos().Z < t->getPos().Z + i->getRange().Z) {
            i->processInteraction(InteractionComponent::interaction::Range, e2);
            i2->processInteraction(InteractionComponent::interaction::Range, e);
        }
        // ---
    }
}