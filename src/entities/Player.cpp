#include "../../include/entities/Player.hpp"
#include "../../include/utils/Config.hpp"
#include <SFML/Window/Keyboard.hpp>

Player::Player(sf::Texture& texture, sf::Vector2f targetPos)
  : spawnTarget(targetPos) {

  sprite.emplace(texture);
  sprite->setTexture(texture);
  sprite->setScale({Config::GLOBAL_SCALE, Config::GLOBAL_SCALE});

  auto bounds = sprite->getLocalBounds();
  sprite->setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

  // Nace fuera de la pantalla
  sprite->setPosition({-150.f, targetPos.y});
}

void Player::updateSpawning(float dt) {
  sprite->move({400.f * dt, 0.f});

  if (sprite->getPosition().x >= spawnTarget.x) {
    sprite->setPosition(spawnTarget);
    state = PlayerState::Active;
  }
}

void Player::shoot(std::vector<std::unique_ptr<Projectile>>& projectiles,
                   sf::Texture& projectileTexture) {

  if (shootTimer > 0.f)
    return;

  sf::Vector2f pos = sprite->getPosition();
  sf::Vector2f dir = {1.f, 0.f};

  projectiles.push_back(
    std::make_unique<Projectile>(
      projectileTexture,
      pos,
      dir,
      ProjectileOwner::Player
    )
  );

  shootTimer = shootCooldown;
}

void Player::handleInput() {
  velocity = {0.f, 0.f};

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
      velocity.y -= speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
      velocity.y += speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
      velocity.x -= speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
      velocity.x += speed;
}

void Player::update(float dt) {
  if (state == PlayerState::Spawning) {
    updateSpawning(dt);
    return;
  }

  shootTimer -= dt;

  handleInput();
  sprite->move(velocity * dt);
}

