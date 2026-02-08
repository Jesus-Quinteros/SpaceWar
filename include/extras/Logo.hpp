#pragma once
#include <SFML/Graphics.hpp>

class GameOverLogo {
public:
  GameOverLogo(sf::Texture& texture);
  void draw(sf::RenderWindow& window);

private:
  std::optional<sf::Sprite> gameOverLogo;
};

class P1Logo {
public:
  P1Logo(sf::Texture& texture);
  void draw(sf::RenderWindow& window);

private:
  std::optional<sf::Sprite> p1Logo;
};

class P2Logo {
public:
  P2Logo(sf::Texture& texture);
  void draw(sf::RenderWindow& window);

private:
  std::optional<sf::Sprite> p2Logo;
};

class EnemyLogo {
public:
  EnemyLogo(sf::Texture& texture);
  void draw(sf::RenderWindow& window);

private:
  std::optional<sf::Sprite> enemyLogo;
};

class NeutralLogo {
public:
  NeutralLogo(sf::Texture& texture);
  void draw(sf::RenderWindow& window);

private:
  std::optional<sf::Sprite> neutralLogo;
};

