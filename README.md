# libmagic
A library that presents a data model for Magic The Gathering game.

It covers most of the things needed to represent the state of a MTG card game and MTG decks. 

# COMPILE
Sorry! No makefile yet, so you need to set your favorite C++ compiler to C++14 and create a library with all files under src folder. 
Library clients should #include <magic.h>, which includes all necessary header files from src subdirectories. 

# TEST
The directory libmagic-test has the sources for an application which has some unit tests for libmagic. 
You will need to have tut.h in your include path to build the test application (which also will need to link with libmagic).

TUT can be found here: http://mrzechonek.github.io/tut-framework/      

# TODO
- add a makefile (compile and install)
- Color needs redesign
- Abilities (model, not rules)
- more nuts and bolts for a basic rules engine (e.g: matchers for battlefield and other zones)
- API for external control (to be used by embedded LUA, Python or JS scripts for card abilities)
