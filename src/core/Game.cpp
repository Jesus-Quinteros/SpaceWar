#include "../../include/core/Game.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <string>

Game::Game()
: window(sf::VideoMode({1280, 720}), "Spaceship") {
  window.setFramerateLimit(60);

  worldBounds = sf::FloatRect({0.f, 0.f},{static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});

  if (!playerTexture.loadFromFile("textures/player/neutralP1.png")) { std::cout << "ERROR al cargar playerTexture\n"; }
  if (!projectileTexture.loadFromFile("textures/flame-orange.png")) { std::cout << "ERROR al cargar projectileTexture\n"; }
  if (!projectileEnemyTexture.loadFromFile("textures/shot-blue.png")) { std::cout << "ERROR al cargar projectileEnemyTexture\n"; }
  if (!enemyTexture.loadFromFile("textures/enemy.png")) { std::cout << "ERROR al cargar enemyTexture\n"; }
  if (!neutralTexture.loadFromFile("textures/asteroide.png")) { std::cout << "ERROR al cargar neutralTexture\n"; }

  playerUpTextures.reserve(3);
  playerDownTextures.reserve(3);
  playerDestroyTextures.reserve(7);
  enemyDestroyTextures.reserve(7);

  for (int i = 1; i <= 3; ++i) {
    playerUpTextures.emplace_back();
    if (!playerUpTextures.back().loadFromFile("textures/player/inclinedUpP10" + std::to_string(i) + ".png")) { std::cout << "ERROR up" << i << "\n"; }
    playerUpFrames.push_back(&playerUpTextures.back());
  }

  for (int i = 1; i <= 3; ++i) {
    playerDownTextures.emplace_back();
    if (!playerDownTextures.back().loadFromFile("textures/player/inclinedDownP10" + std::to_string(i) + ".png")) { std::cout << "ERROR down" << i << "\n"; }
    playerDownFrames.push_back(&playerDownTextures.back());
  }

  for (int i = 1; i <= 7; ++i) {
    playerDestroyTextures.emplace_back();
    if (!playerDestroyTextures.back().loadFromFile("textures/explosions/burst0" + std::to_string(i) + ".png")) { std::cout << "ERROR destroy" << i << "\n"; }
    playerDestroyFrames.push_back(&playerDestroyTextures.back());
  }

  for (int i = 1; i <= 7; ++i) {
    enemyDestroyTextures.emplace_back();
    if (!enemyDestroyTextures.back().loadFromFile("textures/explosions/burst-orange0" + std::to_string(i) + ".png")) { std::cout << "ERROR destroy" << i << "\n"; }
    enemyDestroyFrames.push_back(&enemyDestroyTextures.back());
  }

  player = std::make_unique<Player>(
    playerTexture,
    playerUpFrames,
    playerDownFrames,
    playerDestroyFrames,
    sf::Vector2f({200.f, window.getSize().y / 2.f})
  );

  decorativeSpawner = std::make_unique<DecorativeSpawner>(window.getSize());
  decorativeSpawner->spawnInitial(decoratives);
}

void Game::run() {
  sf::Clock clock;

  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();

    processEvents();

    if (started) {
      update(dt);
    }

    render();
  }
}

void Game::processEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
      if (key->scancode == sf::Keyboard::Scancode::Escape) {
        window.close();
      }
      if (key->scancode == sf::Keyboard::Scancode::Enter) {
        started = true;
        std::cout << "Juego Iniciado" << std::endl;
      }
      if (key->scancode == sf::Keyboard::Scancode::P && player) {
        player->shoot(projectiles, projectileTexture);
      }
    }
  }
}

void Game::update(float dt) {
  
  for (auto& p : projectiles)
    p->update(dt);

  handleCollisions();

  if (player && (player->isAlive() || player->isDestroying())) {
    player->update(dt);
    clampEntity(*player);
  }

  for (auto& e : enemies) {
    e->update(dt);
    clampEnemyVertical(*e);

    if (player && e->isAlive()) {
      e->shoot(projectiles, projectileEnemyTexture, player->bounds().getCenter());
    }
  }

  std::erase_if(projectiles,
      [](const auto& p) { return !p->isAlive(); });

  enemySpawnTimer -= dt;

  if (enemySpawnTimer <= 0.f && player) {
    float y = static_cast<float>(rand() % window.getSize().y);
    enemies.push_back(
      enemyFactory.create(
        enemyTexture,
        enemyDestroyFrames,
        {1100.f, y}
      )
    );
    enemySpawnTimer = enemySpawnRate;
  }

  std::erase_if(enemies,
      [](const auto& e) { return !e->isAlive(); });

  neutralSpawnTimer -= dt;

  if (neutralSpawnTimer <= 0.f) {
    float y = static_cast<float>(rand() % window.getSize().y);
    float speed = 100.f + rand() % 200;
    float rot = (rand() % 2 == 0 ? 1.f : -1.f) * (50.f + rand() % 100);

    neutrals.push_back(
      std::make_unique<Neutral>(
        neutralTexture,
        sf::Vector2f(1400.f, y),
        speed,
        rot
      )
    );

    neutralSpawnTimer = neutralSpawnRate;
  }

  for (auto& n : neutrals) {
    n->update(dt);
  }

  decorativeSpawner->update(dt, decoratives);

  for (auto& d : decoratives)
    d->update(dt);

  std::erase_if(decoratives,
      [](const auto& d) { return !d->isAlive(); });

  checkGameOver();
}

void Game::render() {
  window.clear(sf::Color(16,27,45));

  for (auto& d : decoratives)
    d->draw(window);

  for (auto& n : neutrals)
    n->draw(window);

  for (auto& p : projectiles)
    p->draw(window);

  if (started && player && (player->isAlive() || player->isDestroying())) {
    player->draw(window);
  }

  for (auto& e : enemies) {
    if (e->isAlive() || e->isDestroying()) {
      e->draw(window);
    }
  }

  if (gameOver) {
    // Más adelante: mostrar sprite de derrota
  }

  window.display();
}

void Game::handleCollisions() {

  // Proyectiles vs enemigos / jugador
  for (auto& p : projectiles) {
    if (!p->isAlive()) continue;

    Circle cp = p->circleBounds();

    if (p->getOwner() == ProjectileOwner::Player) {
      for (auto& e : enemies) {
        if (e->isAlive()) {
          Circle ce = e->circleBounds();
          sf::Vector2f diff = cp.center - ce.center;
          float dist2 = diff.x*diff.x + diff.y*diff.y;
          float rsum = cp.radius + ce.radius;

          if (dist2 < rsum*rsum) {
            p->destroy();
            e->startDestroy();
            break;
          }
        }
      }
    } else {
      if (player && player->isAlive()) {
        Circle cpl = player->circleBounds();
        sf::Vector2f diff = cp.center - cpl.center;
        float dist2 = diff.x*diff.x + diff.y*diff.y;
        float rsum = cp.radius + cpl.radius;

        if (dist2 < rsum*rsum) {
          player->setAnimation(PlayerAnim::Destroy);
          p->destroy();
        }
      }
    }
  }

  // Player vs enemigo
  for (auto& e : enemies) {
    if (player && player->isAlive() &&
      e->isAlive() &&
      player->bounds().findIntersection(e->bounds())) {
      player->setAnimation(PlayerAnim::Destroy);
      e->startDestroy();
    }
  }

  // Player vs neutrales
  for (auto& n : neutrals) {
    if (player && player->isAlive() && n->isAlive()) {
      Circle c1 = player->circleBounds();
      Circle c2 = n->circleBounds();

      sf::Vector2f diff = c1.center - c2.center;
      float dist2 = diff.x*diff.x + diff.y*diff.y;
      float rsum = c1.radius + c2.radius;

      if (dist2 < rsum*rsum) {
        player->setAnimation(PlayerAnim::Destroy);
      }
    }
  }
}

void Game::checkGameOver() {
  if (player && !player->isAlive()) {
    gameOver = true;
  }
}

void Game::clampEntity(Entity& entity) {
  auto bounds = entity.bounds();
  auto pos = entity.getPosition();

  float entityLeft   = pos.x - bounds.size.x / 2.f;
  float entityRight  = pos.x + bounds.size.x / 2.f;
  float entityTop    = pos.y - bounds.size.y / 2.f;
  float entityBottom = pos.y + bounds.size.y / 2.f;

  float worldLeft = worldBounds.getCenter().x - worldBounds.size.x / 2.f;
  float worldRight = worldBounds.getCenter().x + worldBounds.size.x / 2.f;
  float worldTop = worldBounds.getCenter().y - worldBounds.size.y / 2.f;
  float worldBottom = worldBounds.getCenter().y + worldBounds.size.y / 2.f;

  sf::Vector2f newPos = entity.bounds().getCenter();

  if (entityLeft < worldLeft)
      newPos.x += worldLeft - entityLeft;

  if (entityRight > worldRight)
      newPos.x -= entityRight - worldRight;

  if (entityTop < worldTop)
      newPos.y += worldTop - entityTop;

  if (entityBottom > worldBottom)
      newPos.y -= entityBottom - worldBottom;

  entity.setPosition(
    entity.getPosition() +
    (newPos - entity.bounds().getCenter())
  );
}

void Game::clampEnemyVertical(Entity& entity) {
  auto bounds = entity.bounds();
  auto pos = entity.getPosition();

  float entityTop = pos.y - bounds.size.y / 2.f;
  float entityBottom = pos.y + bounds.size.y / 2.f;
  float worldTop = worldBounds.getCenter().y - worldBounds.size.y / 2.f;
  float worldBottom = worldBounds.getCenter().y + worldBounds.size.y / 2.f;

  if (entityTop < worldTop)
    entity.setPosition({pos.x, pos.y + (worldTop - entityTop)});

  if (entityBottom > worldBottom)
    entity.setPosition({pos.x, pos.y - (entityBottom - worldBottom)});
}

