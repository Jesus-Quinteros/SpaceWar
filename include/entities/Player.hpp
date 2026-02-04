#pragma once
#include "Entity.hpp"
#include "Projectile.hpp"

#include <vector>
#include <memory>

enum class PlayerState {
  Spawning,
  Active
};

class Player : public Entity {
public:
  Player(sf::Texture& texture, sf::Vector2f targetPos);

  void update(float dt) override;
  void shoot(std::vector<std::unique_ptr<Projectile>>& projectiles,
             sf::Texture& projectileTexture);

private:
  void handleInput();
  void updateSpawning(float dt);

private:
  PlayerState state = PlayerState::Spawning;

  float speed = 300.f;

  float shootCooldown = 0.2f;
  float shootTimer = 0.f;

  sf::Vector2f spawnTarget;
};

