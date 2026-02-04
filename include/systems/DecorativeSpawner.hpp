#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "../entities/Decorative.hpp"

class DecorativeSpawner {
public:
  DecorativeSpawner(sf::Vector2u windowSize);

  void update(float dt, std::vector<std::unique_ptr<Decorative>>& decoratives);
  void spawnInitial(std::vector<std::unique_ptr<Decorative>>& decoratives);

private:
  void spawn(std::vector<std::unique_ptr<Decorative>>& decoratives);

  sf::Vector2u windowSize;
  float spawnTimer = 0.f;
  float spawnInterval = 0.3f;

  // Texturas
  sf::Texture starSmall;
  sf::Texture starBig;
  sf::Texture spaceDust;
  sf::Texture planet;
};

