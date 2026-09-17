# Powered-pong
---

> Note: This project is wip and not completely completed. Some feature will probably get added in the future

## What is this project about ?

- The goal of this project is to learn more about **C++ game programming and C++ networking**. Its a Pong game made by scratch in C++ using the **SDL graphical library** and the C++ **ASIO networking framework** **. This project will probably have more updates in the future that add more features already programmed but not really implemented (like the custom rules or real online multiplayer).

** No need to install the ASIO framework, it is localised in /external/

> I used the **javidx9 tutorials** for the networking aspects.

Source: https://www.youtube.com/@javidx9

## Is this Game really playable with anyone ?

- For now, **no**. Only in the same network using static ip. 

---

## Build

## Requirements

| Tool | Version |
|------|---------|
| CMake | 3.21+ |
| Ninja | Any recent version |
| C++ compiler | C++20 compatible |
| vcpkg | Recent version |

### Dependencies

Dependencies are automatically managed through vcpkg:

- SDL2
- SDL2_image
- SDL2_ttf

## Steps

### Windows

#### 1. Clone the repository
```bash
git clone https://github.com/M-Chd/powered-pong.git
cd powered-pong 
```
#### 2. Configure the project
```bash
cmake --preset=release
```
#### 3. Build
```bash
cmake --build --preset=release
```

Note: The executable will be generated in *build/release/*

#### debug conf.
```bash
cmake --preset=debug
cmake --build --preset=debug
```

### Linux

#### 1. Debian/Ubuntu
```bash
sudo apt update
sudo apt install git cmake ninja-build build-essential
```
You will also need vcpkg installed and VCPKG_ROOT configured.

#### 2. Clone the repository

```bash
cmake --preset=release
cmake --build --preset=release
```

#### for debug

```bash
cmake --preset=debug
cmake --build --preset=debug
```

#### 3. Execute
```bash
./build/release/powered-pong
```
---

# How to play ?

- using **Z** or **W** and **S** to move upside and downside.

- If in **Local Multiplayer mode**, the second player moves with **UP** and **DOWN**.

- In the **Menus**
    - Use UP, DOWN and ENTER

- **ESCAPE** to pause the game.
---
## Structure
    Directory structure:
    └── m-chd-powered-pong/
        ├── README.md
        ├── CMakeLists.txt
        ├── Cmakepresets.json
        ├── CMakeSettings.json
        ├── LICENSE
        ├── vcpkg-configuration.json
        ├── vcpkg.json
        ├── assets/
        │   └── fonts/
        │       └── Beach-Ball.ttf
        ├── external/
        │   └── asio/...
        │       
        ├── NetCommon/
        │   ├── net_client.h
        │   ├── net_common.h
        │   ├── net_connection.h
        │   ├── net_message.h
        │   ├── net_server.h
        │   ├── net_tsqueue.h
        │   ├── NetCommon.vcxproj
        │   ├── NetCommon.vcxproj.filters
        │   └── pong_net.h
        └── src/
            ├── main.cpp
            ├── core/
            │   ├── aiController.cpp
            │   ├── aiController.h
            │   ├── board.cpp
            │   ├── board.h
            │   ├── difficulty.h
            │   ├── game.cpp
            │   ├── game.h
            │   ├── inputManager.cpp
            │   ├── inputManager.h
            │   ├── match.cpp
            │   ├── match.h
            │   ├── matchEvent.h
            │   ├── playerInputState.h
            │   ├── textureCache.h
            │   ├── window.cpp
            │   └── window.h
            ├── entities/
            │   ├── activeEffect.cpp
            │   ├── activeEffect.h
            │   ├── ball.cpp
            │   ├── ball.h
            │   ├── item.cpp
            │   ├── item.h
            │   ├── player.cpp
            │   └── player.h
            ├── net/
            │   ├── connectionState.h
            │   ├── messageType.h
            │   ├── netCommon.h
            │   ├── netGameState.h
            │   ├── networkClient.cpp
            │   ├── networkClient.h
            │   ├── networkManager.cpp
            │   ├── networkManager.h
            │   ├── networkServer.cpp
            │   └── networkServer.h
            ├── ui/
            │   ├── buttonList.hpp
            │   ├── connectUi.h
            │   ├── debugOverlay.cpp
            │   ├── debugOverlay.h
            │   ├── inputIP.cpp
            │   ├── inputIP.h
            │   ├── menu.cpp
            │   ├── menu.h
            │   ├── menuManager.cpp
            │   ├── menuManager.h
            │   ├── scoreBoard.cpp
            │   ├── scoreBoard.h
            │   ├── uiElement.h
            │   └── view.h
            └── util/
                ├── util.h
                ├── vector2.cpp
                └── vector2.hpp

### Diagram

![image](/images/diagram.png)

---
# Server Configuration

```bash
TODO
```
