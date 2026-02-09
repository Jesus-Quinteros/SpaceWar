#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

#include "../entities/Player.hpp"
#include "../entities/Enemy.hpp"
#include "../entities/Projectile.hpp"
#include "../entities/Neutral.hpp"
#include "../entities/Decorative.hpp"
#include "../systems/EnemyFactory.hpp"
#include "../systems/DecorativeSpawner.hpp"
#include "../extras/Text.hpp"
#include "../extras/Logo.hpp"
#include "../extras/AudioManager.hpp"

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
  float victoryTimer = 61.f;

  bool started = false;
  bool gameOver = false;
  bool victory = false;

  GameState gameState = GameState::WaitingStart;
  bool twoPlayers = false; 

  AudioManager audio;

  sf::Font menuFont;
  sf::Font titleFont;
  sf::Font restartfont;
  sf::Font timerFont;
  std::optional<Menu> menu;
  std::optional<Title> title;
  std::optional<Restart> restart;
  std::optional<Timer> timer;

  sf::Texture p1LogoTexture;
  sf::Texture p2LogoTexture;
  sf::Texture enemyLogoTexture;
  sf::Texture neutralLogoTexture;
  sf::Texture gameOverLogoTexture;
  sf::Texture victoryLogoTexture;

  std::optional<P1Logo> p1Logo;
  std::optional<P2Logo> p2Logo;
  std::optional<EnemyLogo> enemyLogo;
  std::optional<NeutralLogo> neutralLogo;
  std::optional<GameOverLogo> gameOverLogo;
  std::optional<VictoryLogo> victoryLogo;

  sf::Texture projectileTexture;
  sf::Texture projectileEnemyTexture;
  std::vector<std::unique_ptr<Projectile>> projectiles;
  sf::Texture enemyTexture;
  EnemyFactory enemyFactory;
  std::vector<std::unique_ptr<Enemy>> enemies;
  float enemySpawnTimer = 0.f;
  float enemySpawnRate = 1.4f;
  sf::Texture neutralTexture;
  std::vector<std::unique_ptr<Neutral>> neutrals;
  float neutralSpawnTimer = 0.f;
  float neutralSpawnRate = 1.4f;
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

