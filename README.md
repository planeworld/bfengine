[![Build Status](https://travis-ci.org/planeworld/bfengine.svg?branch=master)](https://travis-ci.org/planeworld/bfengine)
![Last commit](https://img.shields.io/github/last-commit/planeworld/bfengine.svg)
![Code size](https://img.shields.io/github/languages/code-size/planeworld/bfengine.svg)
![license](https://img.shields.io/github/license/planeworld/bfengine.svg)

BFEngine
==========

BFEngine is an a 2D simulation engine.

Dependencies
------------
* [eigen](http://eigen.tuxfamily.org/)
* [glm](https://glm.g-truc.net/)
* [Lua](https://www.lua.org/)
* [SFML](https://www.sfml-dev.org/)
* [libnoise2d](https://github.com/planeworld/libnoise2d/)

Installation
------------

    > git clone https://github.com/planeworld/bfengine.git
    > mkdir bfengine/build
    > cd bfengine/build
    > cmake ../
    > ccmake .
    (To configure compile and install details)
    > make install
