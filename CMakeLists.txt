cmake_minimum_required(VERSION 3.30)
project(spacewar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

find_package(SFML 3 REQUIRED Graphics Window System Audio COMPONENTS)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/core/Game.cpp
  src/extras/Animation.cpp
  src/entities/Entity.cpp
  src/entities/Player.cpp
  src/entities/Projectile.cpp
  src/entities/Enemy.cpp
  src/entities/Neutral.cpp
  src/entities/Decorative.cpp
  src/systems/EnemyFactory.cpp
  src/systems/DecorativeSpawner.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME}
  SFML::Graphics
  SFML::Window
  SFML::System
  SFML::Audio
)

