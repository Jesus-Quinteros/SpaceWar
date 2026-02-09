#include "../../include/extras/Logo.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

P1Logo::P1Logo(sf::Texture& texture) {
  p1Logo.emplace(texture);
  p1Logo->setTexture(texture);
  p1Logo->setScale({0.9f,0.9f});
  sf::FloatRect bounds = p1Logo->getLocalBounds();
  p1Logo->setOrigin(bounds.getCenter());
  p1Logo->setPosition({220.f, 620.f});
}

void P1Logo::draw(sf::RenderWindow& window) {
  window.draw(*p1Logo);
}

P2Logo::P2Logo(sf::Texture& texture) {
  p2Logo.emplace(texture);
  p2Logo->setTexture(texture);
  p2Logo->setScale({0.8f,0.8f});
  sf::FloatRect bounds = p2Logo->getLocalBounds();
  p2Logo->setOrigin(bounds.getCenter());
  p2Logo->setPosition({1180.f, 520.f});
}

void P2Logo::draw(sf::RenderWindow& window) {
  window.draw(*p2Logo);
}

EnemyLogo::EnemyLogo(sf::Texture& texture) {
  enemyLogo.emplace(texture);
  enemyLogo->setTexture(texture);
  enemyLogo->setScale({2.f,2.f});
  sf::FloatRect bounds = enemyLogo->getLocalBounds();
  enemyLogo->setOrigin(bounds.getCenter());
  enemyLogo->setPosition({890.f, 40.f});
}

void EnemyLogo::draw(sf::RenderWindow& window) {
  window.draw(*enemyLogo);
}

NeutralLogo::NeutralLogo(sf::Texture& texture) {
  neutralLogo.emplace(texture);
  neutralLogo->setTexture(texture);
  neutralLogo->setScale({2.f,2.f});
  sf::FloatRect bounds = neutralLogo->getLocalBounds();
  neutralLogo->setOrigin(bounds.getCenter());
  neutralLogo->setPosition({290.f, 170.f});
}

void NeutralLogo::draw(sf::RenderWindow& window) {
  window.draw(*neutralLogo);
}

GameOverLogo::GameOverLogo(sf::Texture& texture) {
  gameOverLogo.emplace(texture);
  gameOverLogo->setTexture(texture);
  sf::FloatRect bounds = gameOverLogo->getLocalBounds();
  gameOverLogo->setOrigin(bounds.getCenter());
  gameOverLogo->setPosition({640.f, 360.f});
}

void GameOverLogo::draw(sf::RenderWindow& window) {
  window.draw(*gameOverLogo);
}

VictoryLogo::VictoryLogo(sf::Texture& texture) {
  victoryLogo.emplace(texture);
  victoryLogo->setTexture(texture);
  sf::FloatRect bounds = victoryLogo->getLocalBounds();
  victoryLogo->setOrigin(bounds.getCenter());
  victoryLogo->setPosition({640.f, 360.f});
}

void VictoryLogo::draw(sf::RenderWindow& window) {
  window.draw(*victoryLogo);
}

