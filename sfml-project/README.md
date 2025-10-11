# SFML Project

This project is a simple game built using the SFML (Simple and Fast Multimedia Library) framework. It serves as a starting point for developing 2D games in C++.

## Project Structure

```
sfml-project
├── src
│   ├── main.cpp          # Entry point of the application
│   └── headers
│       └── Game.h       # Declaration of the Game class
├── assets
│   ├── textures          # Folder for texture files
│   └── fonts             # Folder for font files
├── CMakeLists.txt        # CMake configuration file
├── Makefile              # Build instructions
└── README.md             # Project documentation
```

## Setup Instructions

1. **Install SFML**: Make sure you have SFML installed on your system. You can download it from the [SFML website](https://www.sfml-dev.org/download.php).

2. **Clone the Repository**: Clone this repository to your local machine.

   ```bash
   git clone <repository-url>
   cd sfml-project
   ```

3. **Build the Project**:
   - If you are using CMake, create a build directory and run CMake:

     ```bash
     mkdir build
     cd build
     cmake ..
     make
     ```

   - If you are using the Makefile, simply run:

     ```bash
     make
     ```

## Usage

After building the project, you can run the executable generated in the build directory. The game window will open, and you can interact with the game as designed.

## Contributing

Feel free to fork the repository and submit pull requests for any improvements or features you would like to add.