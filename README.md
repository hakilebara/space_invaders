# Space Invaders

## Dependencies for Running Locally
* cmake >= 3.10
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Instructions for running the project.

1. git clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SpaceInvaders`

## Features

This program implement a subset of the Space Invaders game. A fleet of invader moves is slowing moving down the screen and the player must shoot them all before they reach his y position.

This is what the game looks like:

https://github.com/user-attachments/assets/e00894eb-c02c-489c-83c1-107d326db85a

## Udacity C++ Nanodegree Capstone Rubric Points

### Loops, Functions, I/O

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| :white_check_mark: | The project demonstrates an understanding of C++ functions and control structures.| A variety of control structures are used in the project. The project code is clearly organized into functions.| [game.cpp](src/game.cpp#L68-L142) |
| :white_check_mark: | The project reads data from a file and process the data, or the program writes data to a file. | The project reads data from an external file or writes data to a file as part of the necessary operation of the program.| [audio.cpp](src/audio.cpp#L50) |
| :white_check_mark: | The project accepts user input and processes the input.|The project accepts input from a user as part of the necessary operation of the program.| [controller.cpp](src/controller.cpp#L4-L55) |

### Object Oriented Programming

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
|:white_check_mark:|The project uses Object Oriented Programming techniques. | The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.| `*.hpp` |
|:white_check_mark:|Classes use appropriate access specifiers for class members.| All class data members are explicitly specified as public, protected, or private.|`*.hpp`|
|:white_check_mark:|Class constructors utilize member initialization lists.| All class members that are set to argument values are initialized through member initialization lists.|[renderer.cpp](src/renderer.cpp#L6-L14)|
|:white_check_mark:|Classes abstract implementation details from their interfaces.| All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.|`*.hpp`|
|:white_check_mark:| Classes encapsulate behavior. | Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.|`*.hpp`|
|:white_check_mark:| Classes follow an appropriate inheritance hierarchy.  Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.|[invader.hpp](src/invader.hpp#L8)|
|  | Overloaded functions allow the same function to operate on different parameters. |  |
|  | Derived class functions override virtual base class functions. | One member function in an inherited class overrides a virtual base class member function.| |
|  | Templates generalize functions in the project. | One function is declared with a template that allows it to accept a generic parameter.| |

### Memory Management

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
|:white_check_mark:|The project makes use of references in function declarations.|At least two variables are defined as references, or two functions use pass-by-reference in the project code.| [renderer.hpp](src/renderer.hpp#L16) [renderer.hpp](src/renderer.hpp#L33) |
|:white_check_mark:| The project uses destructors appropriately. | At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor. |[audio.cpp](src/audio.cpp#L16-L24) |
|:white_check_mark:| The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. | The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.|[audio.cpp](src/audio.cpp#L37-L43)|
|  | The project follows the Rule of 5. | For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.|  |
|:white_check_mark:| The project uses move semantics to move data, instead of copying it, where possible. | For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object. |[audio.cpp](src/audio.cpp#L40)|
|:white_check_mark:| The project uses smart pointers instead of raw pointers. | The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.|[game.hpp](src/game.hpp#L30)|

### Concurrency

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
|:white_check_mark:| The project uses multithreading. | The project uses multiple threads in the execution.|[audio.cpp](src/audio.cpp#L13)|
|| A promise and future is used in the project. | A promise and future is used to pass data from a worker thread to a parent thread in the project code.| |
|:white_check_mark:| A mutex or lock is used in the project. | A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.|[audio.cpp](src/audio.cpp#L28)|
|  | A condition variable is used in the project. | A std::condition_variable is used in the project code to synchronize thread execution.| |
