/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class methods
*/

#include "MovementSystem.hpp"

void ECS::System::MovementSystem::update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{
    for (auto &entity : entities)
        if (entity.second->hasComponent(Component::Flags::transform)) {
            std::cout << "Transform component found. Casting ..." << std::endl;

            auto component = static_cast<ECS::Component::Transform *>(entity.second->component(Component::Flags::transform).get());
            std::cout << "values : " << std::endl;
            std::cout << "x : " << component->x << std::endl;
            std::cout << "y : " << component->y << std::endl;
            std::cout << "z : " << component->z << std::endl;
            
            std::cout << "Increment x ..." << std::endl;
            component->x++;
        }
}

std::tuple<float, float, float> ECS::System::MovementSystem::transform(const std::shared_ptr<Entity> &entity) const
{
    // Casting it to the correct component
    auto component = static_cast<ECS::Component::Transform *>(entity->component(Component::Flags::transform).get());

    // Modifying the component of the current entity
    return std::make_tuple(component->x, component->y, component->z);
}

void ECS::System::MovementSystem::setTransform(std::shared_ptr<Entity> &entity, float x, float y, float z)
{
    // Casting it to the correct component
    auto component = static_cast<ECS::Component::Transform *>(entity->component(Component::Flags::transform).get());

    // Modifying the component of the current entity
    component->x = x;
    component->y = y;
    component->z = z;
}

void ECS::System::MovementSystem::move(const std::shared_ptr<Entity> &entity, float x, float y, float z)
{
    // Casting it to the correct component
    auto component = static_cast<ECS::Component::Transform *>(entity->component(Component::Flags::transform).get());

    // Modifying the component of the current entity
    component->x += x;
    component->y += y;
    component->z += z;
}