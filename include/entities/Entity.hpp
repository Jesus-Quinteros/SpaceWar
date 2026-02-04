#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
  Entity() = default;
  virtual ~Entity() = default;

  virtual void update(float dt) = 0;
  virtual void draw(sf::RenderWindow& window);

  sf::Vector2f getPosition() const;
  void setPosition(const sf::Vector2f& pos);
  sf::FloatRect bounds() const;

  bool isAlive() const { return alive; }
  void destroy() { alive = false; }

protected:
  std::optional<sf::Sprite> sprite;
  sf::Vector2f velocity{0.f, 0.f};
  bool alive = true;
};

