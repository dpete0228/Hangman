# Overview

For this project, I developed a complete Hangman game written entirely in C++. The program includes a console-based interface, an object-oriented word management system, input validation, file persistence for storing a growing dictionary, and dynamic ASCII rendering of the hangman figure as the player progresses.

The software is built around two main components:

- Hangman.cpp – manages the overall game loop, user interaction, screen rendering, and input processing.

- Word class – loads possible words from a file, randomly selects words, tracks correct and incorrect guesses, updates the visible progress, and saves newly added words.

The system supports solo mode (randomly choosing words)  and a friend mode where another player inputs the secret word. It also includes user-friendly features such as preventing duplicate guesses, enforcing strict input validation, and persisting a minimum dictionary of 30 diverse words.

[Software Demo Video](https://youtu.be/9h211EAjYLI)

# Development Environment

Visual Studio
C++
- iostream for console work
- string for c++ strings
- fstring for reading and writing to a file
- algorithm for transforming a string to all lowercase
- vector for dynamically sized lists

# Useful Websites

- [W3Schools](https://www.w3schools.com/cpp/)
- [C++ STL Containers](https://cplusplus.com/reference/stl/)

# Future Work

- Graphical Interface
- Difficulty Options for solo
