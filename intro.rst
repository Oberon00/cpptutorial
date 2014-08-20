############
Introduction
############



*******************
About this tutorial
*******************

There exist many good tutorials and articles about specific parts and features
of C++ but I have never heard of any good tutorial on the Language as a whole.
Of course, :ref:`attempts <intro-res-tutorials>` have been made but often, the
tutorials cover only what the author(s) found particularly interesting, and only
superficially touch the rest or are incomplete altogether. Still more tutorials
are outdated, or advocate bad coding style.

If you ask anywhere on the web for a good tutorial on C++, you will thus
inevitably be pointed to :ref:`books <intro-res-books>`, of which there *are*
many good ones.

This tutorial aims to fill the gap, or at least make it into the category of
tutorials with good partial coverage.


Target audience
===============

If you have never programmed before and want to learn C++ as your first language
[#cppfirst]_, this tutorial is for you. You should, however, have a solid
knowledge of your computer and operating system, as I wont give instructions on
how to move files, extract archives, etc.

If you have experience in another programming language, I hope that this
tutorial is useful to you nevertheless, as I try to highlight concepts and
techniques not found in other languages, or put them in dedicated sections, so
that you can skip the parts that you already know.


.. _intro-proglangs:

*********************
Programming languages
*********************

.. highlight:: none

At the lowest (logical) level, a computer processes only a series of zeros and
ones (:dfn:`bits`). Both data and programs thus have to be represented as such.
However, as you can probably imagine, developing software by entering just zeros
and ones is not really feasible: it is very hard to write such :dfn:`machine
code` correctly, and even harder to read. To solve this problem, :dfn:`assembler
languages` were created. I use the plural here, because, like with bitwise
programming, every processor (or processor family) had it's own assembler
language. Such “languages” allow programmers to use words instead of bit
patterns for the instructions that the corresponding CPU supports. For example,
to add the constant 4 to the value that is saved in the 123th memory cell, the
bit pattern that the CPU understands might look like (completely made up)
``00000100 00000010 01111011``. In assembler language you could write that as
something like ``ADD 123, $4``. You would then use a special program (an
:dfn:`assembler`) that reads this text and outputs an executable program that
contains the bit patterns you would otherwise have to write yourself.

However, such assembler languages are still very primitive. You have to tell the
computer *exactly* what it should do, using only the instructions that the CPU
can understand. And that's not very much. For example, to tell the CPU to do
*something* 10 times you would have to write in assembler language the
equivalent of ::

  Reserve one byte of memory and let me refer to it as “i”.
  Write 0 (one byte) to “i”.
  ASSEMBLER: Remember this point in the program as “loop start”.
  (Do something.)
  Add (using one byte numbers) 1 to “i”.
  Test (using one byte numbers) if “i” is less than 10.
  If the last test resulted in false, continue at “loop start”.

.. todo:: In practice, registers would be used instead of reserving memory.

Of course you would not write it like this; the above is just pseudocode,
to give you an idea of how verbosely precise assembler programs are, even
conceptually. If you wrote this program in the correct way, i.e. using a syntax
that an actual assembler can understand, the lines would shorter but also more
arcane. There are several things to note about this pseudocode:

* You have to explicitly tell the assembler to reserve memory.
* You always have to explicitly tell the assembler explicitly how much memory
  “i” occupies: Of course when initially reserving the memory, but also when
  initializing it with zero, when adding to it and when comparing it.
* There is no instruction for doing something a certain number of times. There
  is not even an instruction for doing something as long as a certain
  condition is true: Instead, you explicitly have to label a “loop start”,
  increment the counter, test the condition and jump conditionally.
* Each of these lines, except the one labeled with ``ASSEMBLER:`` will cause
  the assembler program to emit exactly one CPU instruction.

Also, the ability to refer to locations in the program code or memory
locations with names instead of numbers can already be considered as pretty
advanced for assembly languages. More basic ones require you to write
“The memory at the address I reserved last” instead of “i”, and something
like “3 instructions back” instead of “loop start”.

High-level programming languages, like C++, allow you to write this conceptually
like the following::

  For 10 times:
    (Do something.)

This is far closer to plain English than assembler. Additionally, the program
flow is immediately visible from the indent. This might not be a very great
advantage for this tiny program, but imagine writing the following in an assembly
language::

  For each i from 1 to 10:
    If i is odd:
      (Do something.)
    Else:
      (Do somehing other.)
    (Do something more (no matter if i is odd or even)).

Like for assembly languages, high-level languages need a program that translates
the human readable (and writeable) :dfn:`source code` into machine code. But
these are not called assemblers but :dfn:`compilers`. The process itself is
consequently called :dfn:`compiling`.

Note that while machine code and assembly languages work only for a specific set
of CPUs and operating systems, high-level languages allow to write a program
just once and then compile it for an run it on all systems for which there is a
compiler (e.g. a Windows PC and an Android Smartphone). This is another
great advantage of high-level languages.


Abstraction
===========

High-level programming languages hide the specifics of a particular CPU from us,
so that we do not have to care about it. However they still provide us with a
set of well defined instructions that enable us to do whatever we want. The
compiler the makes sure that the CPU understands these instructions. This hiding
is an application of :dfn:`abstraction`: Hiding the things that we do not want
to care about (the available CPU instructions) for our problem (e.g. doing
something 10 times or calculating the tax or simulating a game world) behind a
simpler, more expressive, more portable (across CPUs and operating systems)
language.

But an important part of this expressiveness is to provide us with the means to
make our own abstractions. For example, let's take the following instructions
for making Sphagetti alla Carbonara [WikiSpaghetti]_:

1. Dice the pancetta into small pieces.
2. Bring a big pot of water to a boil and add salt when it begins to simmer.
3. Cook the spaghetti until it is al dente and drain it, reserving ½ cup of
   water.
4. As spaghetti is cooking, heat the olive oil in a large skillet over a
   medium-high heat. When the oil is hot, add the pancetta and cook for about 10
   minutes over a low flame.
5. In a bowl, slowly whisk about ½ cup of the pasta water into the egg yolks,
   using a fork. Add the Parmesan cheese and pepper. Mix with a fork.
6. Transfer the spaghetti immediately to the skillet with the pancetta. Toss it
   and turn off the heat. Add the egg mixture to the skillet with the pasta and
   toss all the ingredients to coat the pasta. Taste the pasta and add salt and
   black pepper, if necessary.

If you read carefully you will notice that not everything is explicitly spelled
out: E.g. the recipe does not say how dicing works, how to boil the water,
how to whisk the egg yolks and so on; the recipe would be quite unreadably long
if it minutely told you all that. Instead, it is assumed that you know how to do
that or at least know where to look it up. The instructions could even be
refined further: For example, you could look in your stove's manual to find out
out how exactly to turn it on and if you had to program a robot to do this you
would probably have to tell it exactly how to move every finger. The abstraction
could also be expanded into the other direction: The Spaghetti could be part of
a whole meal. This stepwise refinement is the concept of procedural abstraction,
and the main features in programming languages to support it are :ref:`functions
<proc-functions>`.

There is also data (object) abstraction in the above recipe: One does not need
to know, for example, the ingredients of the noodles to use them in the recipe.
It is enough to know that you can boil them, and when they are al dente. The
main feature to support this in programming languages are :ref:`classes
<oo>`.

When something cannot (or need not) be refined further, it is called a
:dfn:`primitive`. Generally, it is in the eye of the beholder if something is a
primitive or an abstraction. For programming languages however, there is a well
defined set of things the compiler understands and upon which you can thus build
your abstractions. Most of the time, your programs will use much more
abstractions than primitives.


.. [WikiSpaghetti] http://en.wikibooks.org/wiki/Cookbook:Spaghetti_alla_Carbonara



.. highlight:: cpp

.. _intro-whycpp:

********
Why C++?
********

Advantages
==========

Why should you learn (or use) C++? Because C++ is a widely used general purpose
language with an unique set of advantages (the following reflects only my
personal priorities; it is not intended to be complete):

1. Powerful abstraction with multiple supported paradigms
2. Many available libraries for nearly all tasks you can think of
3. Very good runtime performance
4. Direct access to C-APIs
5. Possibility to directly access system resources
6. Requires no installed runtime (or only minimal)

There are programming languages which do better in some of these aspect, but
no single one (at least not in wide use) that has all of the advantages.

For example, C# fails #6, by requiring the .NET Framework or Mono to be
installed.  Its also not completely on par with C++ in terms of performance. The
same applies to Java, which requires a JRE (Java Runtime Environment) to be
installed.

C, the predecessor language of C++, is not really known for its abstraction
capabilities (#1), which is arguably the most important feature of a programming
language.


Disadvantages and why learning C++ is still a good idea
=======================================================

It has to be said that C++ also does not lack disadvantages:

1. Hard to learn
2. Easy to make mistakes and introduce bugs
3. Lacks a real module system, making it often difficult to install or use
   libraries, and leading to greatly increased :ref:`compile <intro-compiler>` times

Thus, learning C++ as a first language is a bad idea if you do not need all of
the advantages mentioned before and just want to get a particular application
done quickly. However, learning C++ has the advantage that afterwards, you know
nearly all concepts that can be found in the usual imperative programming
languages and will find it quite easy to learn them. Additionally, C++ promotes
a good understanding of the technical foundations of abstract concepts by
providing the primitive tools to investigate them or even to implement them
yourself (as we will see for example with object oriented programming).

Thus, if you really want to become a proficient programmer, C++ is a very
reasonable choice as a first language.



*********************
A tiny bit of history
*********************

The roots of C++ date back to 1979, when Bjarne Stroustrup needed a language
that was both suitable for writing highly efficient programs and provided
abstraction mechanisms comparable to the Simula. The language he began to
develop then was called “C with Classes” as it mainly added basic object
oriented capabilities to the C programming language. In 1983, the name was
changed to C++, as more features were added.
In 1985, Stroustrup wrote first edition of `The C++ programming Language`_
codifying the language for the first time.

.. _The C++ programming Language: http://www.stroustrup.com/4th.html


The ISO Standard
================

In 1998, the ISO standardized C++. A new version of the standard, which
contained only a few fixes was released in 2003. These standards are commonly
referred to as C++98.

In 2011, the next version of C++ was standardized: C++11 adds many enhancements
that, make C++ “feel like a new language” [Stroustrup01]_. A new minor (though
by far not as minor as C++03) update is expected in late summer 2014, the next
major one is planned for 2017, which shows that since C++11 the
speed of the standardization committee has greatly increased. See
https://isocpp.org/std/status for more on this.

The standard is intended mainly for :ref:`compiler <intro-compiler>` writers but it may also be useful
to experienced C++ programmers who seek authoritative, formal, detailed
information. See https://isocpp.org/std/the-standard for how to get it. But note
that the standard is hard to read even for those already knowing C++. It is not
intended for learning the language.

.. [Stroustrup01] Bjarne Stroustrup in his `C++11 FAQ
   <http://www.stroustrup.com/C++11FAQ.html#think>`_

*********
Resources
*********

.. _intro-res-books:

There are many good resources for C++, both on the web and in printed form. For
the latter, I will just refer `The Definitive C++ Book Guide and List`_ on
Stackoverflow_ , which, if you ask me, really *is* the definitive list of good
C++ books (at least in the English language).

.. _Stackoverflow: http://stackoverflow.com
.. _The Definitive C++ Book Guide and List: http://stackoverflow.com/q/388242/2128694


For reference purposes, e.g. when you want to look up a standard library
function, I recommend http://cppreference.com. You might also find
http://www.cplusplus.com/reference/ useful, though I consider it largely
superseded by cppreference.com. However, the descriptions there are often more
informal and thus maybe better suited for beginners.

For general information about the standard and the C++ community I want to point
to http://isocpp.org/, a page set up by Microsoft.

Bjarne Stroustrup, the creator of C++ also has a homepage with some interesting
information at http://www.stroustrup.com/.

Reading the C++ FAQ by Marshall Cline at http://www.parashift.com/c++-faq/ can
keep you from falling into many pitfalls of C++ and also does a good job on
explaining the practical aspects of many of C++'s concepts. It also has a
section on `Big Picture Issues`_, which answers questions like
`What are some features of C++ from a business perspective?
<http://www.parashift.com/c++-faq/overview-cpp.html>`_.

.. _Big Picture Issues: http://www.parashift.com/c++-faq/big-picture.html

`Stackoverflow`_ is a valuable resource for almost any programming language. C++
questions usually have the tag `[c++]
<http://stackoverflow.com/questions/tagged/c++>`_. Apart from asking and
answering questions yourself, you can also read questions and answers by others.
The most interesting ones are gathered at the `[c++-faq]
<http://stackoverflow.com/questions/tagged/c++-faq>`_ tag.



.. _intro-res-tutorials:

Tutorials
=========

There are some other C++-Tutorials on the web, e.g.:

* `On Wikibooks <http://en.wikibooks.org/wiki/C++_Programming>`_
* `On cplusplus.com <http://www.cplusplus.com/doc/tutorial/>`_

Before reading any tutorial (including this!) make sure to do some searching on
how well this tutorial is accepted in the C++ community, or ask yourself, e.g.
on `Stackoverflow`_. The danger of reading a bad tutorial teaching bad coding
habits is great with C++.

--------

.. rubric:: Footnotes

.. [#cppfirst] See :ref:`intro-whycpp` for whether this is a good idea.
