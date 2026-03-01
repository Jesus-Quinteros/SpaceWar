# SpaceWar

SpaceWar es un juego desarrollado en C++ utilizando la librería SFML.
Este proyecto busca, promover la curiosidad para mejorar el aprendizaje sobre técnicas, diseño, abstracción e implementación de dicho lenguaje de una forma recreativa.

## Características

- **Lenguaje:** C++20
- **Gráficos y audio:** SFML
- **Multiplataforma:** gracias a CMake, puede compilarse en Windows, Linux y macOS con distintos generadores (Visual Studio, Ninja, MinGW Makefiles, MSYS Makefiles, Unix Makefiles, etc.)
- **Gestión de memoria:** uso de `std::unique_ptr` y RAII.
- **Aleatoriedad:** `std::mt19937`, `std::uniform_real_distribution`, entre otros, para simular comportamiento autónomo de enemigos (*pseudo-bots*).
- **Patrón de diseño:** *Factory Method* para instanciación de enemigos.
- **Arquitectura:** modular y orientada a objetos.

## Controles por defecto
Pueden modificarse a conveniencia desde el código fuente.
| Tecla | Acción |
|:-:|-|
| `A` `W` `D` `S` | Movimiento P1 |
| `T` | Disparo P1 |
| `Left` `Up` `Right` `Down` | Movimiento P2 |
| `RShift` | Disparo P2 |
| `Up` / `Down` | Seleccionar cantidad de jugadores (en modo menú) |
| `Enter` | Empezar / reiniciar juego (en modo menú, gameover o victory) |
| `Esc` | Salir del juego |

## Requerimientos

> [!NOTE]
> De no tener SFML instalado, no contar con la versión requerida, o no desea actualizar su versión actual; puede continuar con la Compilación.
> El archivo cmake se encargará de descargar y administrar las dependencias necesarias localmente en el directorio del proyecto, para compilar y ejecutar el programa.

1. `SFML 3.0.2`, igualmente desde la v3.0.0 también es funcional, puede revisar la versión con:

   - En Arch Linux:

     ```bash
     pkg-config --modversion sfml-all
     ```
     
   - En Windows:
     
       - Si instalaste SFML con vcpkg:
         
           ```bash
           // En PowerShell
           vcpkg list | Select-String sfml
           // En CMD
           vcpkg list | findstr sfml
           ```
           
       - Si instalaste SFML con MSYS2 o MinGW: (las rutas pueden variar un poco, depende de tu instalación de la herramienta)
         
           ```bash
           // Para MSYS2
           cd C:/msys64/ucrt64/include/SFML
           // Para MinGW
           cd C:/msys64/mingw64/include/SFML
           ```
    
           Aquí deberías encontrar el archivo Config.hpp, abrirlo y revisar las macros de versión.
           
         
       - Si instalaste SFML manualmente en otro directorio dirígite al mismo,
         y el nombre del comprimido .zip (u otro) indicará la versión, o de igual forma el archivo Config.hpp contendrá la versión.
         Además, tendrás que especificar las rutas concretas a los recursos de SFML en el CMakeLists.txt del proyecto, a menos que ya estén incluidas en el PATH)
     
3. Herramienta de automatización de compilación `Cmake` versión mínima 3.30, puede revisar con:

    ```bash
    cmake --version
    ```
    Puede utilizar GNU Make configurando un Makefile personalizado, pero naturalmente este proyecto ya está configurado para una compilación rápida con Cmake.
     
4. Estándar de leguaje `C++20`, el archivo CMakeLists.txt llamará automáticamente a dicho estándar y lo utilizará para la compilación.

## Compilación

1. Crear el directorio `build`:
   
   ```bash
   mkdir build
   ```

2. Iniciar generación:

    ```bash
    // Desde directorio raíz
    cmake -S . -B build -G "<generador de preferencia>"
    // O también simplmente (dejar que cmake elija el generador predeterminado según la plataforma en que se está ejecutando)
    cmake -B build
    // O desde el directorio /build
    cmake ..
    ```
3. Iniciar compilación:

   ```bash
   // Desde directorio raíz
   cmake --build build
   // O desde directorio /build
   cmake .
   // O también desde directorio /build
   make
   ```

## Ejecución

La compilación generará el target `spacewar` por defecto en la raíz del proyecto, y lo puede correr con `./spacewar` y empezar a jugar.

   > [!IMPORTANT]
   >  En caso haya realizado la compilación desde `/build` se sugiere regresar al directorio raíz del proyecto (`cd ..`) y correr el ejecutable desde ahí,
   > ya que intentar ejecutar desde build (por ejemplo `../spacewar`) resultará en un error general del programa, ya que no será capaz de encontrar las rutas
   > a los recursos (fonts, textures, sounds) del juego.

## Contribuciones

   ¡Contribuciones son bienvenidas! Si tienes ideas para mejorar este proyecto, por favor, abre un issue o una pull request.

---

¡Esperamos que disfrutes jugando o aprendiendo de este juego! Si tienes alguna pregunta o sugerencia, no dudes en contactarme. ¡Dominate SpaceWar!
