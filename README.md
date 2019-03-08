![Logo](https://raw.githubusercontent.com/lincolncpp/grape2d/master/logo.png)

[![release](https://img.shields.io/github/release-pre/lincolncpp/grape2d.svg)](https://github.com/lincolncpp/grape2d/releases)
![platform](https://img.shields.io/badge/platform-linux%20|%20mingw-blue.svg?style=flat)
![issues open](https://img.shields.io/github/issues/lincolncpp/grape2d.svg)
![pull request](https://img.shields.io/github/issues-pr/lincolncpp/grape2d.svg)
[![license](https://img.shields.io/github/license/lincolncpp/grape2d.svg)](https://github.com/lincolncpp/grape2d/blob/master/LICENSE)
===


2D game engine for Linux and Windows (MingW) utilizing SDL2/C++

## Getting started

### Prerequisites
First of all, you will need to install the following libraries
- SDL2
- SDL2_ttf
- SDL2_image
- SDL2_mixer

### Building and installing
To install you can download the [release](https://github.com/lincolncpp/grape2d/releases) version and install it by the install.sh

You can too build and install from source code using the make command. First, to build use
```
make
```
Then, install using the command
```
make install
```

## Running the tests
There is a Makefile in each [test folder](https://github.com/lincolncpp/grape2d/tree/master/test/), you just need to execute the make command and run the generated file.

## Authors
- **Fernando Lincoln** - [lincolncpp](https://github.com/lincolncpp)

See also the list of [contributors](https://github.com/lincolncpp/grape2d/graphs/contributors) who participated in this project.

## License
This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/lincolncpp/grape2d/blob/master/LICENSE) file for details
