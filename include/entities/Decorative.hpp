#pragma once
#include "Entity.hpp"

class Decorative : public Entity {
public:
  Decorative(
    const sf::Texture& texture,
    sf::Vector2f position,
    float speed
  );

  void update(float dt) override;
};

