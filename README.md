# Sorting Visualizer in C++ (SFML)

##  Project Overview
This project is a real-time sorting visualizer implemented in C++ using the SFML (Simple and Fast Multimedia Library).  
It graphically demonstrates how different sorting algorithms work by visualizing comparisons and swaps step-by-step

##  Project Motivation
Sorting algorithms are often difficult to understand through theory alone.  
This project was developed to visually explain the internal working of various sorting techniques in real time.

##  Sorting Algorithms Implemented
- Bubble Sort
- Selection Sort
- Insertion Sort
- Quick Sort
- Merge Sort
- Heap Sort

##  How Visualization Works
- Each array element is represented as a vertical bar.
- The height of the bar corresponds to the element’s value.
- Red bars indicate elements currently being compared or swapped.
- The screen is refreshed after every operation to create smooth real-time animation.

##  User Interaction
1. Run the program from the terminal.
2. Select a sorting algorithm from the menu.
3. A graphical window opens displaying the sorting process.
4. Close the window to exit the program.

##  Requirements
- Linux Operating System
- g++ compiler
- SFML graphics library

##  Installing SFML (Ubuntu/Debian)
```bash
 sudo apt install libsfml-dev
## Compile and Run
g++ main.cpp -o visualizer -lsfml-graphics -lsfml-window -lsfml-system
./visualizer
