#pragma once
#include "Entity.hpp"
#include "Projectile.hpp"

enum class EnemyShootType {
  Straight,
  TargetLastPlayerPos
};

enum class EnemyState {
  Spawning,
  Active
};

class Enemy : public Entity {
public:
  Enemy(
    sf::Texture& texture,
    sf::Vector2f targetPos,
    EnemyShootType shootType,
    float fireRate,
    float moveChangeRate
  );

  void update(float dt) override;

  void shoot(std::vector<std::unique_ptr<Projectile>>& projectiles,
             sf::Texture& projectileTexture,
             sf::Vector2f playerPos);

private:
  void updateSpawning(float dt);
  void updateMovement(float dt);

private:
  EnemyState state = EnemyState::Spawning;

  EnemyShootType shootType;

  float fireRate;
  float fireTimer = 0.f;

  float moveChangeRate;
  float moveTimer = 0.f;

  sf::Vector2f spawnTarget;
};

