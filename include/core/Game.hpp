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

enum class GameState {
  WaitingStart,
  Playing,
  GameOver,
  Victory
};

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
  bool started = false;
  bool gameOver = false;

 GameState gameState = GameState::WaitingStart;
  bool twoPlayers = false; 

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
  
  std::vector<sf::Texture> enemyDestroyTextures;
  std::vector<sf::Texture*> enemyDestroyFrames;

  sf::Texture P1Texture;
  std::unique_ptr<Player> player1;
  sf::Texture P2Texture;
  std::unique_ptr<Player> player2;

  std::vector<sf::Texture> P1UpTextures;
  std::vector<sf::Texture> P1DownTextures;
  std::vector<sf::Texture> P1DestroyTextures;

  std::vector<sf::Texture*> P1UpFrames;
  std::vector<sf::Texture*> P1DownFrames;
  std::vector<sf::Texture*> P1DestroyFrames;

  std::vector<sf::Texture> P2UpTextures;
  std::vector<sf::Texture> P2DownTextures;
  std::vector<sf::Texture> P2DestroyTextures;

  std::vector<sf::Texture*> P2UpFrames;
  std::vector<sf::Texture*> P2DownFrames;
  std::vector<sf::Texture*> P2DestroyFrames;
};

