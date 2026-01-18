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

Projekt jest w aktywnym rozwoju. Powitane są ulepszenia i optymalizacje.# 3D-Engine

## Opis projektu
3D-Engine to autorski silnik graficzny napisany w języku C++, przeznaczony do tworzenia i wizualizacji scen trójwymiarowych. Projekt demonstruje kluczowe zagadnienia grafiki komputerowej, takie jak transformacje macierzowe, oświetlenie Phonga, cieniowanie, teksturowanie obiektów oraz obsługa kamery swobodnej (Free Camera). Silnik wykorzystuje biblioteki OpenGL i FreeGLUT.

## Główne cechy
* **Renderowanie prymitywów 3D:** Obsługa brył proceduralnych (Sfera, Czajnik, Torus) oraz definiowanych przez wierzchołki (Sześcian, Piramida).
* **Zaawansowane oświetlenie:** Implementacja modelu oświetlenia (Ambient, Diffuse, Specular) z możliwością dynamicznego włączania/wyłączania.
* **Cieniowanie:** Przełączanie w czasie rzeczywistym między cieniowaniem płaskim (Flat) a gładkim (Smooth).
* **Obsługa tekstur:** Ładowanie obrazów (JPG/PNG) i mapowanie UV na obiektach złożonych.
* **Interakcja i Edycja:** System wyboru obiektów (Highlighting) oraz ich transformacja (przesuwanie, obrót, skalowanie).
* **Kamera:** Swobodna kamera typu "FPS" sterowana myszą i klawiaturą.
* **Architektura obiektowa:** Rozbudowana hierarchia klas z wykorzystaniem polimorfizmu.

## Architektura

### Katalogi
* `src/Core/` - Główna pętla silnika i zarządzanie oknem (Engine).
* `src/Graphics/` - Obsługa renderowania, tekstur (BitmapHandler) i kamery.
* `src/Objects/` - Klasy reprezentujące obiekty na scenie (Cube, Pyramid, Sphere).

### Główne klasy
* **Engine** - Klasa typu Singleton zarządzająca cyklem życia aplikacji, inicjalizacją GLUT i listą obiektów.
* **Camera** - Odpowiada za obliczanie macierzy widoku (View Matrix) i obsługę wejścia sterującego widokiem.
* **BitmapHandler** - Wrapper dla biblioteki `stb_image`, zarządzający ładowaniem i bindowaniem tekstur.
* **GameObject** - Abstrakcyjna klasa bazowa dla wszystkich obiektów sceny, posiadająca właściwości transformacji.
* **TexturedObject** - Rozszerzenie klasy bazowej o obsługę tekstur, dziedziczone przez Sześcian i Piramidę.

### Schemat hierarchii klas
```text
GameObject
├── SphereObject
├── TeapotObject
├── TorusObject
└── TexturedObject
    ├── CubeObject
    └── PyramidObject

Użyte biblioteki

    FreeGLUT - Zarządzanie oknem, kontekstem OpenGL i wejściem (klawiatura/mysz).

    OpenGL - Niskopoziomowe API do renderowania grafiki 3D.

    GLM - Matematyka wektorowa i macierzowa.

    stb_image - Lekka biblioteka do ładowania plików graficznych.

Kompilacja

Projekt wykorzystuje system CMake. Aby zbudować projekt:
Bash

mkdir build
cd build
cmake ..
cmake --build .

Sterowanie (Demo)
Klawisz	Funkcja
WSAD / Mysz	Sterowanie kamerą (ruch i rozglądanie się)
TAB	Wybór obiektu (Highlighting)
DEL	Usunięcie wybranego obiektu
1 - 5	Dodanie obiektu (Cube, Pyramid, Sphere, Teapot, Torus)
L	Włącz/Wyłącz oświetlenie
K	Zmień tryb cieniowania (Flat/Smooth)
Strzałki	Przesuwanie wybranego obiektu (X/Z)
R / T / Y	Obrót wybranego obiektu
+ / -	Skalowanie wybranego obiektu
Dokumentacja

Dokumentacja techniczna kodu jest generowana za pomocą narzędzia Doxygen w języku polskim. Aby wygenerować dokumentację:
Bash

doxygen Doxyfile

Dokumentacja HTML będzie dostępna w katalogu doc/html/index.html.
Autor
    Khoprov Yakiv 

Wersja

1.0