#include "../../include/systems/EnemyFactory.hpp"

EnemyFactory::EnemyFactory()
: rng(std::random_device{}()) {}

std::unique_ptr<Enemy> EnemyFactory::create(sf::Texture& texture, sf::Vector2f pos) {
  std::uniform_real_distribution<float> fireDist(0.8f, 2.0f);
  std::uniform_real_distribution<float> moveDist(0.5f, 2.0f);
  std::uniform_int_distribution<int> shootTypeDist(0, 1);

  EnemyShootType type =
    shootTypeDist(rng) == 0 ?
    EnemyShootType::Straight :
    EnemyShootType::TargetLastPlayerPos;

  return std::make_unique<Enemy>(
    texture,
    pos,
    type,
    fireDist(rng),
    moveDist(rng)
  );
}
