#include "../../include/extras/AudioManager.hpp"
#include <iostream>

AudioManager::AudioManager() {}

bool AudioManager::loadResources() {
  menuMusic.emplace();
  if (!menuMusic->openFromFile("sounds/menu-music.mp3")) {
    std::cout << "ERROR al cargar menu-music\n";
    return false;
  }
  menuMusic->setLooping(true);

  gameplayMusic.emplace();
  if (!gameplayMusic->openFromFile("sounds/gameplay-music.mp3")) {
    std::cout << "ERROR al cargar gameplay-music\n";
    return false;
  }
  gameplayMusic->setLooping(true);

  if (!soundBuffers[SoundType::Select].loadFromFile("sounds/select-sound.mp3")) { std::cout << "ERROR al cargar select-sound\n"; }
  if (!soundBuffers[SoundType::PlayerShoot].loadFromFile("sounds/playerShot-sound.wav")) { std::cout << "ERROR al cargar playerShot-sound\n"; }
  if (!soundBuffers[SoundType::EnemyExplosion].loadFromFile("sounds/enemyExplosion-sound.mp3")) { std::cout << "ERROR al cargar enemyExplosion-sound\n"; }
  if (!soundBuffers[SoundType::PlayerExplosion].loadFromFile("sounds/playerExplosion-sound.mp3")) { std::cout << "ERROR al cargar playerExplosion-sound\n"; }
  if (!soundBuffers[SoundType::GameOver].loadFromFile("sounds/gameover-sound.mp3")) { std::cout << "ERROR al cargar gameover-sound\n"; }

  for (auto& [type, buffer] : soundBuffers) {
    sounds[type].emplace(buffer);
    sounds[type]->setBuffer(buffer);
  }

  return true;
}

void AudioManager::playMusic(MusicType type) {
  stopMusic();
  currentMusic = type;

  if (type == MusicType::Menu && menuMusic) {
    menuMusic->play();
  } else if (type == MusicType::Gameplay && gameplayMusic) {
    gameplayMusic->play();
  }
}

void AudioManager::stopMusic() {
  if (menuMusic) menuMusic->stop();
  if (gameplayMusic) gameplayMusic->stop();
}

void AudioManager::playSound(SoundType type) {
  sounds[type]->play();
}
