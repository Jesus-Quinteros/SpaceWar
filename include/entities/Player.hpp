#pragma once
#include "Entity.hpp"
#include "Projectile.hpp"
#include "../extras/Animation.hpp"

#include <vector>
#include <memory>

enum class PlayerState {
  Spawning,
  Active,
  Destroying,
  Dead
};

enum class PlayerAnim {
  Idle,
  MoveUp,
  MoveDown,
  Destroy
};

class Player : public Entity {
public:
  Player(
    sf::Texture& idle,
    std::vector<sf::Texture*>& upFrames,
    std::vector<sf::Texture*>& downFrames,
    std::vector<sf::Texture*>& destroyFrames,
    sf::Vector2f targetPos
  );

  void update(float dt) override;
  void shoot(std::vector<std::unique_ptr<Projectile>>& projectiles,
             sf::Texture& projectileTexture);
  void setAnimation(PlayerAnim anim);
  bool isDestroying() const { return state == PlayerState::Destroying; }

private:
  void handleInput();
  void updateSpawning(float dt);

  void updateAnimation(float dt);

private:
  PlayerState state = PlayerState::Spawning;

  float speed = 300.f;

  float shootCooldown = 0.2f;
  float shootTimer = 0.f;

  sf::Vector2f spawnTarget;

  PlayerAnim currentAnim = PlayerAnim::Idle;

  Animation animIdle;
  Animation animUp;
  Animation animDown;
  Animation animDestroy;
};

