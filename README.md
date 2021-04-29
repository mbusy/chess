# Chess

<!-- start -->
<p align="middle">
	<img src="resources/images/chess_game.png"/>
</p>
<!-- end -->

A simple C++ chess game, using the SFML library.

## Installation
### Prerequisites
This project uses the SMFL library (2.5.1), it should be installed before compiling the project (see [this link](https://www.sfml-dev.org/tutorials/2.5/)). This project has only been tested for Linux for now.

### Compiling the project
Create a build folder, and generate the project in that folder:
```shell
mkdir build
cd build
cmake ..
```

You can now build the project:
```shell
make
```

This will generate the `chess` executable.

## Usage
To launch a chess game, just launch the generated `chess` executable:
```shell
./build/chess
```

The escape key can be used to exit the game.

## Credits
* Lichess project (Thibault Duplessis) - sounds