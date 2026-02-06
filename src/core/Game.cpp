#include "../../include/core/Game.hpp"
#include "../../include/extras/PlayerControls.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <string>

PlayerControls p1Controls {
  sf::Keyboard::Key::W,
  sf::Keyboard::Key::S,
  sf::Keyboard::Key::A,
  sf::Keyboard::Key::D,
  sf::Keyboard::Key::P
};

PlayerControls p2Controls {
  sf::Keyboard::Key::Up,
  sf::Keyboard::Key::Down,
  sf::Keyboard::Key::Left,
  sf::Keyboard::Key::Right,
  sf::Keyboard::Key::RControl
};

Game::Game()
: window(sf::VideoMode({1280, 720}), "Spaceship") {
  window.setFramerateLimit(60);

  worldBounds = sf::FloatRect({0.f, 0.f},{static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});

  if (!P1Texture.loadFromFile("textures/player/neutralP1.png")) { std::cout << "ERROR al cargar P1Texture\n"; }
  if (!P2Texture.loadFromFile("textures/player/neutralP2.png")) { std::cout << "ERROR al cargar P2Texture\n"; }
  if (!projectileTexture.loadFromFile("textures/flame-orange.png")) { std::cout << "ERROR al cargar projectileTexture\n"; }
  if (!projectileEnemyTexture.loadFromFile("textures/shot-blue.png")) { std::cout << "ERROR al cargar projectileEnemyTexture\n"; }
  if (!enemyTexture.loadFromFile("textures/enemy.png")) { std::cout << "ERROR al cargar enemyTexture\n"; }
  if (!neutralTexture.loadFromFile("textures/asteroide.png")) { std::cout << "ERROR al cargar neutralTexture\n"; }

  P1UpTextures.reserve(3);
  P1DownTextures.reserve(3);
  P1DestroyTextures.reserve(7);

  P2UpTextures.reserve(3);
  P2DownTextures.reserve(3);
  P2DestroyTextures.reserve(7);

  enemyDestroyTextures.reserve(7);

   for (int i = 1; i <= 7; ++i) {
    enemyDestroyTextures.emplace_back();
    if (!enemyDestroyTextures.back().loadFromFile("textures/explosions/burst-orange0" + std::to_string(i) + ".png")) { std::cout << "ERROR destroy" << i << "\n"; }
    enemyDestroyFrames.push_back(&enemyDestroyTextures.back());
  }

  for (int i = 1; i <= 3; ++i) {
    P1UpTextures.emplace_back();
    if (!P1UpTextures.back().loadFromFile("textures/player/inclinedUpP10" + std::to_string(i) + ".png")) { std::cout << "ERROR upP1" << i << "\n"; }
    P1UpFrames.push_back(&P1UpTextures.back());
  }

  for (int i = 1; i <= 3; ++i) {
    P1DownTextures.emplace_back();
    if (!P1DownTextures.back().loadFromFile("textures/player/inclinedDownP10" + std::to_string(i) + ".png")) { std::cout << "ERROR downP1" << i << "\n"; }
    P1DownFrames.push_back(&P1DownTextures.back());
  }

  for (int i = 1; i <= 7; ++i) {
    P1DestroyTextures.emplace_back();
    if (!P1DestroyTextures.back().loadFromFile("textures/explosions/burst0" + std::to_string(i) + ".png")) { std::cout << "ERROR destroyP1" << i << "\n"; }
    P1DestroyFrames.push_back(&P1DestroyTextures.back());
  }

  for (int i = 1; i <= 3; ++i) {
    P2UpTextures.emplace_back();
    if (!P2UpTextures.back().loadFromFile("textures/player/inclinedUpP20" + std::to_string(i) + ".png")) { std::cout << "ERROR upP2" << i << "\n"; }
    P2UpFrames.push_back(&P2UpTextures.back());
  }

  for (int i = 1; i <= 3; ++i) {
    P2DownTextures.emplace_back();
    if (!P2DownTextures.back().loadFromFile("textures/player/inclinedDownP20" + std::to_string(i) + ".png")) { std::cout << "ERROR downP2" << i << "\n"; }
    P2DownFrames.push_back(&P2DownTextures.back());
  }

  for (int i = 1; i <= 7; ++i) {
    P2DestroyTextures.emplace_back();
    if (!P2DestroyTextures.back().loadFromFile("textures/explosions/burst0" + std::to_string(i) + ".png")) { std::cout << "ERROR destroyP2" << i << "\n"; }
    P2DestroyFrames.push_back(&P2DestroyTextures.back());
  }

  player1 = std::make_unique<Player>(
    p1Controls, P1Texture, P1UpFrames, P1DownFrames, P1DestroyFrames,
    sf::Vector2f({200.f, window.getSize().y / 3.f}),
    projectiles, projectileTexture
  );

  player2 = std::make_unique<Player>(
    p2Controls, P2Texture, P2UpFrames, P2DownFrames, P2DestroyFrames,
    sf::Vector2f({220.f, window.getSize().y / 2.f}),
    projectiles, projectileTexture
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

      if (gameState == GameState::WaitingStart) {
        if (key->scancode == sf::Keyboard::Scancode::Up) {
          twoPlayers = false;
          std::cout << "Seleccionado: 1 jugador\n";
        }
        if (key->scancode == sf::Keyboard::Scancode::Down) {
          twoPlayers = true;
          std::cout << "Seleccionado: 2 jugadores\n";
        }
        if (key->scancode == sf::Keyboard::Scancode::Enter) {
          started = true;
          gameState = GameState::Playing;
          std::cout << "Juego Iniciado con " << (twoPlayers ? 2 : 1) << " jugador(es)\n";
        }
      }
    }
  }
}

void Game::update(float dt) {
  
  for (auto& p : projectiles)
    p->update(dt);

  handleCollisions();

  if (player1 && (player1->isAlive() || player1->isDestroying())) {
    player1->update(dt);
    clampEntity(*player1);
  }

  if (twoPlayers && player2 && (player2->isAlive() || player2->isDestroying())) {
    player2->update(dt);
    clampEntity(*player2);
  }

  for (auto& e : enemies) {
    e->update(dt);
    clampEnemyVertical(*e);

    std::vector<Player*> alivePlayers;
    if (player1 && player1->isAlive()) alivePlayers.push_back(player1.get());
    if (twoPlayers && player2 && player2->isAlive()) alivePlayers.push_back(player2.get());

    if (!alivePlayers.empty()) {
      // Elegir uno al azar
      static std::mt19937 rng{std::random_device{}()};
      std::uniform_int_distribution<size_t> dist(0, alivePlayers.size() - 1);

      Player* target = alivePlayers[dist(rng)];
      sf::Vector2f targetPos = target->bounds().getCenter();

      e->shoot(projectiles, projectileEnemyTexture, targetPos);
    }
  }

  std::erase_if(projectiles,
      [](const auto& p) { return !p->isAlive(); });

  enemySpawnTimer -= dt;

  if (enemySpawnTimer <= 0.f && player1) {
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

  if (started && player1 && (player1->isAlive() || player1->isDestroying())) {
    player1->draw(window);
  }

  if (twoPlayers && started && player2 && (player2->isAlive() || player2->isDestroying())) {
    player2->draw(window);
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
      if (player1 && player1->isAlive()) {
        Circle cpl = player1->circleBounds();
        sf::Vector2f diff = cp.center - cpl.center;
        float dist2 = diff.x*diff.x + diff.y*diff.y;
        float rsum = cp.radius + cpl.radius;

        if (dist2 < rsum*rsum) {
          player1->setAnimation(PlayerAnim::Destroy);
          p->destroy();
        }
      }
      if (twoPlayers && player2 && player2->isAlive()) {
        Circle cpl2 = player2->circleBounds();
        sf::Vector2f diff = cp.center - cpl2.center;
        float dist2 = diff.x*diff.x + diff.y*diff.y;
        float rsum = cp.radius + cpl2.radius;

        if (dist2 < rsum*rsum) {
          player2->setAnimation(PlayerAnim::Destroy);
          p->destroy();
        }
      }
    }
  }

  // Player vs enemigo
  for (auto& e : enemies) {
    if (player1 && player1->isAlive() && e->isAlive() &&
      player1->bounds().findIntersection(e->bounds())) {
      player1->setAnimation(PlayerAnim::Destroy);
      e->startDestroy();
    }
    if (twoPlayers && player2 && player2->isAlive() && e->isAlive() &&
      player2->bounds().findIntersection(e->bounds())) {
      player2->setAnimation(PlayerAnim::Destroy);
      e->startDestroy();
    }
  }

  // Player vs neutrales
  for (auto& n : neutrals) {
    if (player1 && player1->isAlive() && n->isAlive()) {
      Circle c1 = player1->circleBounds();
      Circle c2 = n->circleBounds();

      sf::Vector2f diff = c1.center - c2.center;
      float dist2 = diff.x*diff.x + diff.y*diff.y;
      float rsum = c1.radius + c2.radius;

      if (dist2 < rsum*rsum) {
        player1->setAnimation(PlayerAnim::Destroy);
      }
    }
    if (twoPlayers && player2 && player2->isAlive() && n->isAlive()) {
      Circle c1 = player2->circleBounds();
      Circle c2 = n->circleBounds();

      sf::Vector2f diff = c1.center - c2.center;
      float dist2 = diff.x*diff.x + diff.y*diff.y;
      float rsum = c1.radius + c2.radius;

      if (dist2 < rsum*rsum) {
        player2->setAnimation(PlayerAnim::Destroy);
      }
    }
  }
}

void Game::checkGameOver() {
  bool p1Dead = player1 && !player1->isAlive();
  bool p2Dead = twoPlayers && player2 && !player2->isAlive();

  if (p1Dead && (!twoPlayers || p2Dead)) {
    gameOver = true;
    gameState = GameState::GameOver;
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

