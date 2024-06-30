# Task 1: Data compression

[Wersja w języku polskim](README-pl.md)

A universal data compressor potentially supporting any types (not only `Array2D`!).

## Description

The task was completed according to the instructions: the `compressData` function was implemented.
It takes a two-dimensional `Array2D` and returns an optional `CompressedData` containing the compressed data.
Additionally, if the size of the compressed data **in bytes** is larger than the input data size,
an empty optional will be returned.

## Structure

| Directory | Description                                               |
|-----------|-----------------------------------------------------------|
| `include` | Header files of the implemented library (data compressor) |
| `tests`   | Tests                                                     |

## Dependencies

This solution does not rely on any external dependencies.

## Tests

Tests can be found in the `tests` directory.
The **GTest 1.14.0** framework has been used for testing (it will be downloaded automatically).
