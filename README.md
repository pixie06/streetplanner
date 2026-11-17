# Streetplanner

A Qt desktop application that lets you build a road map of cities and streets on a canvas and find the **shortest route between two cities with Dijkstra's algorithm**.

Built in 2023 for the *Praktikum Informatik 1* course (C++ / Qt).

## Features

- Add cities by name and coordinates, then connect them with streets via a dialog
- Draw cities and streets live on a `QGraphicsScene`
- Load a predefined map (`MapIoNrw`, cities in North Rhine-Westphalia)
- Pick start and destination from drop-down lists and highlight the shortest path
- Built-in test buttons for `City`, `Street`, `Map`, `AbstractMap` and `Dijkstra`
- Chinese UI translation (`streetplanner_zh_CN.ts`)

## Architecture

| File | Responsibility |
|---|---|
| `abstractmap.h` | Interface for the map (provided by the course) |
| `map.cpp/.h` | My implementation: stores cities/streets, looks up neighbours and street lengths |
| `city`, `street` | Data classes that can draw themselves on the scene |
| `dijkstra.cpp/.h` | Shortest-path search using open ("yellow") and settled ("green") node sets |
| `mapio`, `mapionrw` | Loads a sample map |
| `mainwindow`, `dialog` | Qt Widgets UI |

## Build

Requires Qt 5 or Qt 6 (Widgets, LinguistTools) and CMake ≥ 3.5.

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=<path-to-Qt>
cmake --build build
```

Or open `CMakeLists.txt` / `Streetplanner.pro` in Qt Creator.

## What I learned

- Writing Qt Widgets apps with signals/slots and Designer `.ui` files
- Implementing an abstract interface against a fixed specification
- Implementing Dijkstra's algorithm on a graph built from pointers
