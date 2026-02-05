#pragma once
#include "Entity.hpp"
#include "Projectile.hpp"
#include "../extras/Animation.hpp"

enum class EnemyShootType {
  Straight,
  TargetLastPlayerPos
};

enum class EnemyAnim {
  Idle,
  Destroy
};

enum class EnemyState {
  Spawning,
  Active,
  Destroying,
  Dead
};

class Enemy : public Entity {
public:
  Enemy(
    sf::Texture& texture,
    std::vector<sf::Texture*>& destroyFrames,
    sf::Vector2f targetPos,
    EnemyShootType shootType,
    float fireRate,
    float moveChangeRate
  );

  void update(float dt) override;

  void shoot(std::vector<std::unique_ptr<Projectile>>& projectiles,
             sf::Texture& projectileTexture,
             sf::Vector2f playerPos);
  void startDestroy();
  bool isDestroying() const { return state == EnemyState::Destroying; }

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

  Animation animDestroy;
  EnemyAnim currentAnim = EnemyAnim::Idle;
};

