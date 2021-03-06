# Gincu -- a simple match three game, game engine, and game framework written in C++

## Introduction and goals

Gincu is a lightweight cross platform 2D game framework and middleware written in C++.


The original work was a test work when I was applying a job with a game company. The company requires a simple match-three game written in C++ with SDL. I didn't join the company because I got another offer at the mean time.

Now I open source the project, and I've rewritten the render engine with SFML and Allegro.

Now there is a match-three game in the project. In the future we may add more games as prototypes to the project. Though the match three game is not as cool as Candy Crush Saga, it includes most basic stuff and may be a good kick off.

## Version

0.0.1

## Supported platform

 * Windows. Tested.
 * Android. Tested.
 * iOS/iPhone/iPad. Not tested.
 * Mac. Not tested.
 * Linux. Not tested.
 
## Environments and requirements

 * C++11 compiler (Visual C++ 2015 or later, or GCC (MingW) 4.8 or later)
 * [SFML 2.4.1](http://www.sfml-dev.org/) or later.
 * [Allegro 5.2](http://www.liballeg.org/) or later. Note, Gincu only need one render engine, SFML or Allegro, it doesn't need both.
 * My [cpgf library](https://github.com/cpgf/cpgf)
 * CMake 3.6 or later.
 * Need to `clone --recursive`.

## License

Apache License, Version 2.0

## Core system and features

 * Multi threaded OpenGL rendering.
 * Multi threaded task processing and resource loading.
 * Entity Component System (ECS).
 * Scene management.
 * Scene transition effect.
 * ECS based scene graph (GComponentLocalTransform).
 * Camera system.
 * Anchor and flip x/y (GComponentAnchor).
 * Sprite sheet.
 * Frame based animation.
 * Tween animation using the tween module in my cpgf library.
 * Low level automatically batching draw calls.
 * Finite state machine.
 * Event driven.
 * Memory pool and cached entities and components. So CPU cache optimization is considered.
 * Underlying rendering engine agnostic. We can replace SFML with any other engine or even 3D engine simply and easily.
 * Script binding using cpgf. Current Lua is supported and and is working in progress.

## Underlying render engine
Currently Gincu supports both SFML (desktop and Android) and Allegro (desktop only since I didn't succeeded compiling Allegro for Android).
But SFML will most likely be abandoned soon because it doesn't support iOS and very bad support for Android.
Most likely Gincu will rely on Allegro or some other libraries such as Irrlicht in the future.

## How to contribute

There are several ways to contribute to the project

 * Add new game beside the match-three. Such as adding a Super Mario Bros like game will demonstrate the basic 2D physics engine works perfectly, or adding a Box2D based game.
 * Add new test cast in the test bed.
 * Add or enhance the features. There are several features missed:
   * Physics system. Not used in matchtThree type games but is very useful. Solution: easy to add to ECS system as a kind of component.
 * Make some better art work. Current the art resource is very ugly.

## Build and run on desktop

 * Download [latest SFML binary](http://www.sfml-dev.org/) that matches your compiler.
 * Download [cpgf library source code](https://github.com/cpgf/cpgf)  and build the library, with Lua enabled.
 * Go to the "build/desktop" folder in this project.
 * Edit config.txt to set the proper directories to point to SFML and cpgf.
 * Run "make vc15" to generate VC2015 project file, or "make mingw" to compile using MingW directly, or just "make" to see the help. You can replace "make" with "mingw32-make" or "nmake".
 * If you run "make vc15", open gincu.sln in folder build/project_vc15 in VC IDE and compile the project.
 * The binary file is generated in folder bin.
 * Go to folder "bin", copy SFML graphics, system, and window DLL (or dynamic libraries on Linux) to bin folder, then run the compiled program.

## Build and run on Android

 * Setup Android SDK and NDK, and Apache ANT.
 * Download [latest SFML source code](http://www.sfml-dev.org/) then build SFML for Android (search for tutorial).
 * Download [cpgf library source code](https://github.com/cpgf/cpgf). You don't need to compile the library.
 * Go to folder "build/android".
 * Create sub folder "assets", copy the "resources" folder in "bin" there.
 * Run "android update project --target "android-23" --path . --subprojects --name gincu".
 * Run "ndk-build".
 * Then run "ant debug" for debug version or "ant release" for release version.
 * Now .apk is in "build/android/bin" folder.

## Folder structure

 * bin. The resources, libraries, and the game program. CMake was already configured to output compiled program there.
 * bin/art. The raw art assets. They are used to create the game assets and they are not used by the game directly.
 * bin/resources. The assets and scripts used by the game.
 * build. CMake build home.
 * include. The include folder of the library.
 * src. The source code of the library..
 * tests/application. All application code. Each sub folder is a single game or application.
 * tests/application/testbed. The test bed. It's easy to add small test case there.
 * tests/application/matchthree. The match-three game. If you need to add another game XYZ, create folder src/application/xyz.
 
 