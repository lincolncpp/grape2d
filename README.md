![Logo](https://raw.githubusercontent.com/lincolncpp/grape2d/master/logo.png)

[![release](https://img.shields.io/github/release-pre/lincolncpp/grape2d.svg)](https://github.com/lincolncpp/grape2d/releases)
![platform](https://img.shields.io/badge/platform-linux%20|%20windows-blue.svg?style=flat)
![issues open](https://img.shields.io/github/issues/lincolncpp/grape2d.svg)
![pull request](https://img.shields.io/github/issues-pr/lincolncpp/grape2d.svg)
[![license](https://img.shields.io/github/license/lincolncpp/grape2d.svg)](https://github.com/lincolncpp/grape2d/blob/master/LICENSE)
===

Grape2D is a open-source 2D game engine with focus in performance and simplicity written in C++. It supports Linux and Windows and interacts with hardware using [SDL](https://www.libsdl.org/)

## Getting started
If you want to compile it in Windows, you will need to install [MingW](http://www.mingw.org/)

You can do the following instructions both on Windows and Linux.

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
Next, use the make command and you are done
```
make
```

### Installing
You can install it from [release version](https://github.com/lincolncpp/grape2d/releases) or from source code.

For the second option, do the following (after you have already built)
```
make install
```

## Example codes
- [`texture`](https://github.com/lincolncpp/grape2d/tree/master/test/texture) — Shows a simple texture on the screen
- [`audio`](https://github.com/lincolncpp/grape2d/tree/master/test/audio) — Plays music and sound with 2D ambient effect

### Running

To run any example code, first use the make command in their respective folder to build it
```
make
```
And then, run the generated file

## Authors
- **Fernando Lincoln** - [lincolncpp](https://github.com/lincolncpp)

See also the list of [contributors](https://github.com/lincolncpp/grape2d/graphs/contributors) who participated in this project.

## License
This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/lincolncpp/grape2d/blob/master/LICENSE) file for details
