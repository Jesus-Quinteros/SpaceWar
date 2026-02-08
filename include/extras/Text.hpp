#pragma once
#include <SFML/Graphics.hpp>

class Title {
public:
  Title(sf::Font& font);
  void draw(sf::RenderWindow& window);

private:
  std::optional<sf::Text> title;
};

class Menu {
public:
  Menu(sf::Font& font);

  void setSelection(bool twoPlayers);
  void draw(sf::RenderWindow& window);

private:
  std::optional<sf::Text> onePlayerText;
  std::optional<sf::Text> twoPlayerText;
  bool twoPlayersSelected = false;
};

class Restart {
public:
  Restart(sf::Font& font);
  void draw(sf::RenderWindow& window);

private:
  std::optional<sf::Text> restart;
};

