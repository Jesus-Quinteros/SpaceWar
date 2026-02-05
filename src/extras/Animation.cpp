#include "../../include/extras/Animation.hpp"

void Animation::addFrame(const sf::Texture& tex) {
  frames.push_back(&tex);
}

void Animation::setFrameTime(float t) {
  frameTime = t;
}

void Animation::setLoop(bool loop) {
  looping = loop;
}

void Animation::reset() {
  timer = 0.f;
  current = 0;
  done = false;
}

bool Animation::finished() const {
  return done;
}

// void Animation::update(float dt) {
//   if (frames.empty() || done) return;
//
//   timer += dt;
//   if (timer >= frameTime) {
//     timer = 0.f;
//     current++;
//
//     if (current >= frames.size()) {
//       if (looping) {
//         current = frames.size() - 1; // persistir último sprite
//       } else {
//         current = frames.size() - 1;
//         done = true;
//       }
//     }
//   }
// }

// void Animation::update(float dt) {
//   if (frames.empty()) return;
//
//   timer += dt;
//   if (timer >= frameTime && current < frames.size() - 1) {
//     timer = 0.f;
//     current++;
//     if (current >= frames.size()) {
//       current = frames.size() - 1;
//       // ya estamos en el último frame, nos quedamos aquí
//       done = true; 
//     }
//   }
// }

void Animation::update(float dt) {
    if (frames.empty() || done) return;

    timer += dt;
    if (timer >= frameTime) {
        timer = 0.f;
        current++;

        if (current >= frames.size()) {
            if (looping) {
                // Para animaciones en loop, vuelve al último frame y persiste
                current = frames.size() - 1;
            } else {
                // Para animaciones que no deben persistir, marca terminado
                current = frames.size() - 1;
                done = true;
            }
        }
    }
}

const sf::Texture& Animation::getCurrentTexture() const {
  return *frames[current];
}

