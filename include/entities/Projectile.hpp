#pragma once
#include "Entity.hpp"

enum class ProjectileOwner {
  Player,
  Enemy
};

class Projectile : public Entity {
public:
  Projectile(
    sf::Texture& texture,
    sf::Vector2f position,
    sf::Vector2f direction,
    ProjectileOwner owner
  );

  void update(float dt) override;

  ProjectileOwner getOwner() const { return owner; }

  Circle circleBounds() const override;

private:
  sf::Vector2f direction;
  float speed = 700.f;
  ProjectileOwner owner;
};

