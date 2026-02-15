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

1. `SFML 3.0.2`, igualmente desde la v3.0.0 también es funcional, puede revisar la versión con:
   - En Windows:
     
       - Si instalaste SFML con vcpkg:
         
           ```bash
           // En PowerShell
           vcpkg list | Select-String sfml
           ```
           
           ```bash
           // En CMD
           vcpkg list | findstr sfml
           ```
           
       - Si instalaste SFML con MSYS2 o MinGW:
         
           ```bash
           // Para MSYS2 revisa las rutas
           cd C:/msys64/ucrt64/bin
           cd C:/msys64/ucrt64/include
           cd C:/msys64/ucrt64/bin
           // Deben estar las .dll, el directorio SFML, y las lib respectivamente.
           ```
           
           Si usas MinGW las rutas son las mismas pero con `'mingw32'` o `'mingw64'` en el nombre, o puede que varíe un poco la ruta completa, depende de tu instalación de MSYS2
           (y de no tener estas rutas en el PATH, tendrá que especificarlas en el CMakeLists.txt del proyecto)
         
       - Si instalaste SFML manualmente en otro directorio dirígite al mismo, y el nombre del comprimido .zip (u otro) contendrá la versión, o también
         en la carpeta include/SFML en el archivo Config.hpp (con este archivo cmake será capaz de encontrar la versión de SFML) y revisa las macros de versión.
     
   - En Arch Linux:

     ```bash
     pkg-config --modversion sfml-all
     ```
    
   - En Ubuntu:

     ```bash
     Dpkg -s sfml
     ```
     
2. Herramienta de automatización de compilación `Cmake` versión mínima 3.30, puede revisar con:

    ```bash
    cmake --version
    ```
    Puede utilizar GNU Make configurando un Makefile personalizado, pero naturalmente este proyecto ya está configurado para una compilación rápida con Cmake.
     
3. Estándar de leguaje `C++20`, el archivo CMakeLists.txt llamará automáticamente a ese estándar y lo utilizará para la compilación.

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
   // O también
   make
   ```

4. **Ejecución:** Esto generará el target `spacewar` por defecto en la raíz del proyecto, y lo puede correr con `./spacewar` y empezar a jugar.
   
   - Consideración: En caso haya realizado la compilación desde `/build` se sugiere regresar al directorio raíz del proyecto (`cd ..`) y correr el ejecutable desde ahí,
     ya que intentar ejecutar desde build (por ejemplo `../spacewar`) resultará en un error general del programa, ya que no será capaz de encontrar las rutas
     a los recursos (fonts, textures, sounds) del juego.

## Contribuciones

   ¡Contribuciones son bienvenidas! Si tienes ideas para mejorar este proyecto, por favor, abre un issue o una pull request.

---

¡Esperamos que disfrutes jugando o aprendiendo de este juego! Si tienes alguna pregunta o sugerencia, no dudes en contactarme. ¡Dominate SpaceWar!
