Title: On the C++ Programming Language: Readme  
Author: Christian Neumüller  

# About this project


This tutorial aims to teach C++ as a first programming language.
Read the [introduction][] for more information.

This tutorial is written using [Sphinx][] and ReStructuredText.

[introduction]: intro.rst
[Sphinx]: http://sphinx-doc.org/

# On the C++ Programming Language: Planned Outline

## Introduction
* Meta
  + About this tutorial
    - Audience
    - Goals
  + Why C++
  + The ISO Standard
  + A tiny bit of history
* Hello World
  + Compiler basics
    - Info
    - How To: Installing MSVC/g++
  + The Hello World program
  + Using the command line compiler
* Resources [As in: books, links, ect.]

## The Basics: Procedural programming
* Types, Expressions, Variables [hard!]
* Branching (`if`/`else`, `switch`)
* Loops (while, do…while, for)
* Functions [potentially hard!]
  + Pass by reference
* Arrays with `std::vector`
* Defining new types: `typedef`/`using`, `enum`, `struct`
* (Raw) Pointers
* The heap and `unique_ptr`
* Characters, Strings, string literals, `std::string`

## The C/C++ “Module-System”
* Translation Units, Headers, Linkage and the Linker
* Namespaces
* Example: Linked lists, stacks, queues
* A cross-platform build-system: CMake
* Using a library: SDL [good running example]
  + Note to reader: You can't start here!

## Object Orientation
* OO Principles
* Struct/incomplete-type based OO
* Classes and access control (“visibility”)
* Value semantics: The big three
  + RAII [SDL has many potential usages]
* Inheritance and virtual functions
* Interface idiom and a word about multiple inheritance
* Linked lists, object oriented edition
  + Iterators

* Interlude: Error handling and exceptions
  + Return values
  + Exceptions
  + signals?


## Introduction to Generic programming
* Template basics
* Function overloading
* Linked lists, generic edition & `std::list`

## Solving old myths
* Operator overloading: Demystifying `std::cout`
* While we are at it: More on IO
* Low Level Heap Management
  + `new` and `delete`
  + RAII: Implementing `ScopedPointer`
* Move-Semantics and `std::unique_ptr`
* Arrays and `std::vector`
  + … and `std::array`

## Functional Programming
* Function Pointers, Functors, Lambdas, `std::function`
* Higher order functions [Ex.: STL algorithms]
* Functional programming and OO

## Containers & algorithms (“STL”)
* Concepts
* Containers
* Associative containers
* Algorithms


# Missing/further interesting topics
* Test driven development
* Template Meta Programming (TMP)
  + Advanced template features
  + Faculty example
  + Tag dispatching
* Important libraries
  + boost
  + Qt?
* Network programming
* Multithreading
* Scripting: Lua
