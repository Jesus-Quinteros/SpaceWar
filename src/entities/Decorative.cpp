#include "../../include/entities/Decorative.hpp"

Decorative::Decorative(
  const sf::Texture& texture,
  sf::Vector2f position,
  float speed
) {
  sprite.emplace(texture);
  sprite->setTexture(texture);
  sprite->setColor(sf::Color(255,255,255,128));
  sprite->setPosition(position);
  velocity.x = -speed;
}

void Decorative::update(float dt) {
  sprite->move(velocity * dt);

  // Si sale completamente por la izquierda -> destruir
  if (sprite->getPosition().x + sprite->getGlobalBounds().size.x < 0) {
      destroy();
  }
}

