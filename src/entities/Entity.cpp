#include "../../include/entities/Entity.hpp"
#include <SFML/System/Vector2.hpp>

void Entity::draw(sf::RenderWindow& window) {
  window.draw(*sprite);
}

sf::Vector2f Entity::getPosition() const {
  return sprite->getPosition();
}

void Entity::setPosition(const sf::Vector2f& pos) {
  sprite->setPosition(pos);
}

sf::FloatRect Entity::bounds() const {
  return sprite->getGlobalBounds();
}

