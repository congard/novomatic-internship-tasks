# Kompresja danych

Uniwersalny kompresor danych, potencjalnie obsługujący dowolne typy (nie tylko `Array2D`!).

## Opis

Zadanie zostało wykonane zgodnie z poleceniem: została zaimplementowana funkcja `compressData`,
która przyjmuje dwuwymiarową tablicę `Array2D`, a następnie zwraca optional `CompressedData`,
zawierający skompresowane dane. Ponadto, jeżeli rozmiar skompresowanych danych **w bajtach**
jest większy od rozmiaru danych wejściowych, zostanie zwrócony pusty optional.

## Struktura

| Katalog   | Opis                                                              |
|-----------|-------------------------------------------------------------------|
| `include` | Pliki nagłówkowe zaimplementowanej biblioteki (kompresora danych) |
| `tests`   | Testy                                                             |

## Zależności

To rozwiązanie nie korzysta z żadnych zewnętrznych zależności.

## Testy

Testy można znaleźć w katalogu `tests`.
Jako framework do testowania został użyty **GTest 1.14.0** (zostanie pobrany automatycznie).
