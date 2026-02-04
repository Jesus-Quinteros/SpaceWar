#pragma once
#include "Entity.hpp"

class Neutral : public Entity {
public:
  Neutral(sf::Texture& texture, sf::Vector2f pos, float speed, float rotation);

  void update(float dt) override;

private:
  float rotationSpeed;
};

