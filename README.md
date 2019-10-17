![Logo](images/logo.png)

[![release](https://img.shields.io/github/release-pre/lincolncpp/grape2d.svg)](https://github.com/lincolncpp/grape2d/releases)
![platform](https://img.shields.io/badge/platform-linux%20|%20windows-blue.svg?style=flat)
![issues open](https://img.shields.io/github/issues/lincolncpp/grape2d.svg)
![pull request](https://img.shields.io/github/issues-pr/lincolncpp/grape2d.svg)
[![license](https://img.shields.io/github/license/lincolncpp/grape2d.svg)](https://github.com/lincolncpp/grape2d/blob/master/LICENSE)
===

Grape2D is an open-source 2D game engine with focus in performance and simplicity written in C++. It supports Linux and Windows and interacts with hardware using [SDL](https://www.libsdl.org/)

## Getting started
If you want to compile it in Windows, you will need to install [MingW](http://www.mingw.org/).
The instructions below works both on Windows and Linux.

### Prerequisites
First of all, you must to install the following libraries
- SDL2
- SDL2_ttf
- SDL2_image
- SDL2_mixer

### Building from source
To build it, first clone this repository
```
git clone https://github.com/lincolncpp/grape2d
```
Then, use the make command
```
make
```

### Installing
You can install it from [release version](https://github.com/lincolncpp/grape2d/releases) or from source code.

For the second option, use the make command (after you have already built)
```
make install
```

## Demos
- [`texture`](https://github.com/lincolncpp/grape2d/tree/master/demos/texture) — Shows a simple texture on the screen
- [`audio`](https://github.com/lincolncpp/grape2d/tree/master/demos/audio) — Plays music and sound with 2D ambient effect

### Running

To run any example code, first use the make command in the respective folder to build it
```
make
```
And then, execute the generated file

## Authors
- **Fernando Lincoln** - [lincolncpp](https://github.com/lincolncpp)

See also the list of [contributors](https://github.com/lincolncpp/grape2d/graphs/contributors) who participated in this project.

## License
This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/lincolncpp/grape2d/blob/master/LICENSE) file for details
