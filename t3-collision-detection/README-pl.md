# Kolizje

![demo](pictures/demo.gif)

- [Filmik 1](https://youtu.be/uD7VBqZty5M)
- [Filmik 2](https://youtu.be/9EaZpsD0348)

## Opis

Dany projekt jest realizacją zadania 3. Do wizualizatora został wykorzystany mój własny
silnik [Algine](https://github.com/congard/algine).

## Algorytm

Algorytm jest zbudowany w oparciu o twierdzenie, które mówi, że jeżeli da się wybrać jakąś
krawędź jednego z trójkątów tak, że wszystkie wierzchołki drugiego trójkąta leżą po jednej
stronie od tej krawędzi oraz że trzeci wierzchołek pierwszego trójkąta leży po stronie
przeciwnej, to takie trójkąty się nie przecinają.

Implementacja algorytmu znajduje się w katalogu `src/CollisionDetector`.

## Testy

Testy nie potrzebują silnika jako zależności i znajdują się w katalogu `tests`.
Jako framework do testowania został użyty **GTest 1.14.0** (zostanie pobrany automatycznie).

## Zależności wizualizatora

Systemowe zależności i narzędzia niezbędne do kompilacji wizualizatora (na przykładzie Fedora 39):

```bash
sudo dnf install mesa-libGL-devel libXrandr-devel \
    libXinerama-devel libXcursor-devel libXi-devel \
    clang clang-devel mold
```

## Kompilacja wizualizatora

Ze względu na to, że użyłem własnego silnika, kompilacja jest nieco skomplikowana:

1. Należy sklonować silnik:
   ```bash
   git clone https://github.com/congard/algine.git
   git checkout ea020af48dbe1e7ab7fe01d46a96affcdd97c56b
   ```

2. W celu kompilacji wizualizatora należy wykonać poniższe polecenie:
   ```bash
   mkdir cmake-build
   cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug -B cmake-build -G "Ninja" -DALGINE_PATH="/ścieżka/do/silnika"
   cmake --build cmake-build --target visualizer -- -j 16
   ```
   to trochę potrwa.

## Uruchomienie

Przed uruchomieniem należy ustawić katalog roboczy na `src/visualizer/resources`:

```bash
cd src/visualizer/resources
../../../cmake-build/visualizer
```