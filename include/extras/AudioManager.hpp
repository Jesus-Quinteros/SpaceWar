#pragma once
#include <SFML/Audio.hpp>
#include <optional>
#include <map>

enum class MusicType {
  Menu,
  Gameplay
};

enum class SoundType {
  Select,
  PlayerShoot,
  EnemyExplosion,
  PlayerExplosion,
  GameOver,
  Victory
};

class AudioManager {
public:
  AudioManager();

  bool loadResources();

  void playMusic(MusicType type);
  void stopMusic();

  void playSound(SoundType type);

private:
  std::optional<sf::Music> menuMusic;
  std::optional<sf::Music> gameplayMusic;

  std::map<SoundType, sf::SoundBuffer> soundBuffers;
  std::map<SoundType, std::optional<sf::Sound>> sounds;

  MusicType currentMusic;
};

