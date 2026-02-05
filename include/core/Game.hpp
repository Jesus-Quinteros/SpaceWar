#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "../entities/Player.hpp"
#include "../entities/Enemy.hpp"
#include "../entities/Projectile.hpp"
#include "../entities/Neutral.hpp"
#include "../entities/Decorative.hpp"
#include "../systems/EnemyFactory.hpp"
#include "../systems/DecorativeSpawner.hpp"

class Game {
public:
  Game();
  void run();

private:
  void processEvents();
  void update(float dt);
  void render();
  void handleCollisions();
  void checkGameOver();
  void clampEntity(Entity& entity);
  void clampEnemyVertical(Entity& entity);

private:
  sf::RenderWindow window;
  sf::FloatRect worldBounds;

  bool running = true;
  bool started = false; // Enter para comenzar
  bool gameOver = false;
  
  sf::Texture playerTexture;
  std::unique_ptr<Player> player;
  sf::Texture projectileTexture;
  sf::Texture projectileEnemyTexture;
  std::vector<std::unique_ptr<Projectile>> projectiles;
  sf::Texture enemyTexture;
  EnemyFactory enemyFactory;
  std::vector<std::unique_ptr<Enemy>> enemies;
  float enemySpawnTimer = 0.f;
  float enemySpawnRate = 2.f;
  sf::Texture neutralTexture;
  std::vector<std::unique_ptr<Neutral>> neutrals;
  float neutralSpawnTimer = 0.f;
  float neutralSpawnRate = 4.f;
  std::vector<std::unique_ptr<Decorative>> decoratives;
  std::unique_ptr<DecorativeSpawner> decorativeSpawner;
  
  std::vector<sf::Texture> playerUpTextures;
  std::vector<sf::Texture> playerDownTextures;
  std::vector<sf::Texture> playerDestroyTextures;
  std::vector<sf::Texture> enemyDestroyTextures;

  std::vector<sf::Texture*> playerUpFrames;
  std::vector<sf::Texture*> playerDownFrames;
  std::vector<sf::Texture*> playerDestroyFrames;
  std::vector<sf::Texture*> enemyDestroyFrames;
};

