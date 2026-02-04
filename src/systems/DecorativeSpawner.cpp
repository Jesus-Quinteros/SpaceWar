#include "../../include/systems/DecorativeSpawner.hpp"
#include <cstdlib>
#include <iostream>

DecorativeSpawner::DecorativeSpawner(sf::Vector2u size)
: windowSize(size)
{
  if (!starSmall.loadFromFile("textures/background/starSmall.png")) { std::cout << "ERROR al cargar starSmall\n"; };
  if (!starBig.loadFromFile("textures/background/starBig.png")) { std::cout << "ERROR al cargar starBig\n"; };
  if (!spaceDust.loadFromFile("textures/background/nube-espacial.png")) { std::cout << "ERROR al cargar spaceDust\n"; };
  if (!planet.loadFromFile("textures/background/planeta.png")) { std::cout << "ERROR al cargar planet\n"; };
}

void DecorativeSpawner::spawnInitial(
  std::vector<std::unique_ptr<Decorative>>& decoratives
) {
  int count = 50; // estrellas iniciales

  for (int i = 0; i < count; ++i) {
    float x = static_cast<float>(std::rand() % windowSize.x);
    float y = static_cast<float>(std::rand() % windowSize.y);

    decoratives.push_back(
      std::make_unique<Decorative>(
        starSmall,
        sf::Vector2f(x, y),
        // 20.f + std::rand() % 40
        40.f
      )
    );
  }

  for (int i = 0; i < count; ++i) {
    float x = static_cast<float>(std::rand() % windowSize.x);
    float y = static_cast<float>(std::rand() % windowSize.y);

    decoratives.push_back(
      std::make_unique<Decorative>(
        starBig,
        sf::Vector2f(x, y),
        // 20.f + std::rand() % 40
        80.f
      )
    );
  }
}

void DecorativeSpawner::update(
  float dt,
  std::vector<std::unique_ptr<Decorative>>& decoratives
) {
  spawnTimer += dt;

  if (spawnTimer >= spawnInterval) {
    spawnTimer = 0.f;
    spawn(decoratives);
  }
}

void DecorativeSpawner::spawn(
  std::vector<std::unique_ptr<Decorative>>& decoratives
) {
  int roll = std::rand() % 100;
  float y = static_cast<float>(std::rand() % windowSize.y);
  float x = static_cast<float>(windowSize.x + 50);

  if (roll > 80 && roll < 90) {
    decoratives.push_back(
      std::make_unique<Decorative>(
        starSmall,
        sf::Vector2f(x, y),
        40.f
      )
    );
  }
  else if (roll < 93) {
    decoratives.push_back(
      std::make_unique<Decorative>(
        starBig,
        sf::Vector2f(x, y),
        80.f
      )
    );
  }
  else if (roll < 95) {
    decoratives.push_back(
      std::make_unique<Decorative>(
        spaceDust,
        sf::Vector2f(x, y),
        110.f
      )
    );
  }
  else if (roll < 97) {
    decoratives.push_back(
      std::make_unique<Decorative>(
        planet,
        sf::Vector2f(x, y),
        60.f
      )
    );
  }
}

