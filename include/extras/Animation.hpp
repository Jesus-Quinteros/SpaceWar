#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
  void addFrame(const sf::Texture& tex);
  void setFrameTime(float t);
  void reset();
  void setLoop(bool loop);
  bool finished() const;

  void update(float dt);
  const sf::Texture& getCurrentTexture() const;

private:
  std::vector<const sf::Texture*> frames;
  float frameTime = 0.1f;
  float timer = 0.f;
  std::size_t current = 0;
  bool looping = true;
  bool done = false;
};

