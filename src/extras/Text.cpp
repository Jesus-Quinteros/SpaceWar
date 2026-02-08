#include "../../include/extras/Text.hpp"
#include <SFML/Graphics/Rect.hpp>

Title::Title(sf::Font& font) {
  title.emplace(font);
  title->setFont(font);
  title->setCharacterSize(150);
  title->setString("SpaceWar");
  sf::FloatRect boundingTitle = title->getLocalBounds();
  title->setOrigin({boundingTitle.size.x/2.f, boundingTitle.size.y/1.13f});
  title->setFillColor(sf::Color::Red);
  title->setOutlineThickness(8.f);
  title->setOutlineColor(sf::Color::Black);
  title->setPosition({640.f, 260.f});
}

void Title::draw(sf::RenderWindow& window) {
  window.draw(*title);
}

Menu::Menu(sf::Font& font) {
  onePlayerText.emplace(font);
  twoPlayerText.emplace(font);

  onePlayerText->setFont(font);
  onePlayerText->setCharacterSize(120);
  onePlayerText->setString("1 Player");
  onePlayerText->setFillColor(sf::Color::Green);
  onePlayerText->setOutlineThickness(5.f);
  onePlayerText->setOutlineColor(sf::Color::Blue);
  sf::FloatRect boundingOnePlayerText = onePlayerText->getLocalBounds();
  onePlayerText->setOrigin({boundingOnePlayerText.size.x/2.f, boundingOnePlayerText.size.y/1.13f});
  onePlayerText->setPosition({640.f, 460.f});
  onePlayerText->setFillColor(sf::Color::Green);

  twoPlayerText->setFont(font);
  twoPlayerText->setCharacterSize(100);
  twoPlayerText->setString("2 Players");
  twoPlayerText->setFillColor(sf::Color::Green);
  twoPlayerText->setOutlineThickness(2.f);
  twoPlayerText->setOutlineColor(sf::Color::Black);
  sf::FloatRect boundingTwoPlayerText = twoPlayerText->getLocalBounds();
  twoPlayerText->setOrigin({boundingTwoPlayerText.size.x/2.f, boundingTwoPlayerText.size.y/1.13f});
  twoPlayerText->setPosition({630.f, 570.f});
  twoPlayerText->setFillColor(sf::Color::Green);
}

void Menu::setSelection(bool twoPlayers) {
  twoPlayersSelected = twoPlayers;

  if (twoPlayersSelected) {
    twoPlayerText->setOutlineThickness(5.f);
    twoPlayerText->setOutlineColor(sf::Color::Blue);
    twoPlayerText->setFillColor(sf::Color::Green);
    twoPlayerText->setCharacterSize(120);
    twoPlayerText->setPosition({600.f, 550.f});

    onePlayerText->setOutlineThickness(2.f);
    onePlayerText->setOutlineColor(sf::Color::Black);
    onePlayerText->setCharacterSize(100);
    sf::FloatRect boundingOnePlayerText = onePlayerText->getLocalBounds();
    onePlayerText->setOrigin({boundingOnePlayerText.size.x/2.f, boundingOnePlayerText.size.y/1.13f});
    onePlayerText->setPosition({640.f, 450.f});
  } else {
    onePlayerText->setOutlineThickness(5.f);
    onePlayerText->setOutlineColor(sf::Color::Blue);
    onePlayerText->setCharacterSize(120);
    onePlayerText->setPosition({610.f, 450.f});

    twoPlayerText->setOutlineThickness(2.f);
    twoPlayerText->setOutlineColor(sf::Color::Black);
    twoPlayerText->setCharacterSize(100);
    sf::FloatRect boundingTwoPlayerText = twoPlayerText->getLocalBounds();
    twoPlayerText->setOrigin({boundingTwoPlayerText.size.x/2.f, boundingTwoPlayerText.size.y/1.13f});
    twoPlayerText->setPosition({630.f, 570.f});
  }
}

void Menu::draw(sf::RenderWindow& window) {
  window.draw(*onePlayerText);
  window.draw(*twoPlayerText);
}

Restart::Restart(sf::Font& font) {
  restart.emplace(font);
  restart->setFont(font);
  restart->setCharacterSize(50);
  restart->setString("Press 'Enter' to resume");
  sf::FloatRect boundingTitle = restart->getLocalBounds();
  restart->setOrigin({boundingTitle.size.x/2.f, boundingTitle.size.y/1.13f});
  restart->setPosition({640.f, 600.f});
}

void Restart::draw(sf::RenderWindow& window) {
  window.draw(*restart);
}

