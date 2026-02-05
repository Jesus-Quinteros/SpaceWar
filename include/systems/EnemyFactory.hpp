#pragma once
#include <random>
#include "../entities/Enemy.hpp"

class EnemyFactory {
public:
  EnemyFactory();

  std::unique_ptr<Enemy> create(sf::Texture& texture, std::vector<sf::Texture*>& destroyFrames, sf::Vector2f pos);

private:
  std::mt19937 rng;
};

