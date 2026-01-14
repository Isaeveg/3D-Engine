# 3D-Engine
Silnik grafiki 3D napisany w C++ z wykorzystaniem OpenGL. Projekt przeznaczony do wizualizacji scen 3D z obsługą kamery, prymitywów i systemu obserwatorów.

## Cechy

- **Grafika OpenGL** - nowoczesny rendering 3D
- **System kamer** - pełna obsługa nawigacji w przestrzeni 3D
- **Prymitywy** - wbudowane obiekty 3D (sześciany, sfery itp.)
- **System zdarzeń** - wzorzec Observer do zarządzania zdarzeniami
- **Matematyka GLM** - algebra liniowa do obliczeń 3D
- **Kompatybilność wieloplatformowa** - obsługa Windows/Linux/macOS

## Wymagania

- C++17 lub nowszy
- CMake 3.10+
- OpenGL 3.3+
- FreeGLUT 3.0+
- GLM 0.9+

## Struktura projektu

```
├── src/                    # Kod źródłowy
│   ├── main.cpp           # Punkt wejścia
│   ├── Engine.h/cpp       # Główny silnik
│   ├── Camera.h/cpp       # System kamer
│   ├── Primitives.h/cpp   # Prymitywy 3D
│   ├── Cube.h/cpp         # Sześcian
│   ├── Observer.h/cpp     # System zdarzeń
│   └── ...
├── libs/                  # Biblioteki zewnętrzne
│   ├── freeglut/         # Narzędzia OpenGL
│   └── glm/              # Matematyka
├── build/                 # Skompilowany projekt
├── CMakeLists.txt        # Konfiguracja CMake
└── stb_image.h           # Ładowanie obrazów
```

## Kompilacja

### Windows (MSVC)

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

### Linux/macOS (GCC/Clang)

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

## Uruchomienie

Po kompilacji uruchom plik wykonywalny:

```bash
# Windows
./build/Release/Game.exe

# Linux/macOS
./build/Game
```

## Główne komponenty

### Engine
Główna klasa silnika zarządzająca inicjalizacją OpenGL i główną pętlą aktualizacji.

### Camera
System kamer do nawigacji w scenie 3D. Obsługuje macierze projekcji i widoku.

### Primitives
Klasa bazowa dla wszystkich obiektów 3D w scenie.

### Cube
Implementacja sześcianu jako prymitywu sceny.

### Observer
Wzorzec Observer dla systemu zdarzeń i powiadomień.

## Użycie

```cpp
#include "Engine.h"

int main() {
    Engine engine;
    if (!engine.Initialize()) {
        return -1;
    }
    
    engine.Run();
    
    return 0;
}
```

## Zależności

- **FreeGLUT** - zarządzanie oknem i wejściem
- **GLM** - matematyka wektorowa i macierze
- **STB Image** - ładowanie tekstur

## Licencja

Swobodne użytkowanie w celach edukacyjnych i komercyjnych.

## Rozwój

Projekt jest w aktywnym rozwoju. Powitane są ulepszenia i optymalizacje.