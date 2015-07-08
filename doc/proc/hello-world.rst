.. _intro-compiler:
.. _intro-helloworld:


*******************************
From source code to executables
*******************************

When you write a C++ program, you start with the source code. That's a
human-readable notation of the program, in the C++ programming language. For
example a program that writes the text “Hello world!” to a console window looks
like

.. literalinclude:: ex/hello_world.cpp

You write this text using any plain text editor you like (e.g. `Notepad++`_ or Vim_,
but not a rich text editor like Word or Open Office Writer). The colors are just
added here and by good editors automatically to make the code more readable
(that feature is called :dfn:`syntax highlighting`); you do not set them yourself in
any way and they do not influence the program behaviour. The file is usually
saved as with a ``.cpp`` file name extension to make it clear that this is a C++
source code file. You might also encounter the ``.cc`` or ``.cxx`` extensions.

.. _Notepad++: http://notepad-plus-plus.org/
.. _Vim: http://www.vim.org/

Computers cannot execute such a source file, they must be translated into binary
processor instructions first. Thus, next step is to feed this program to a
:dfn:`compiler`, which does this translation for us. There is a multitude of ways of
doing that, depending on the compiler. The compiler then takes the source file
and “compiles” it into an executable program which you can then start.

More complex programs will usually consist of multiple C++ files which are then
separately compiled into intermediate output files (usually with a ``.o`` or
``.obj`` extension) and then “linked” together by a program called :dfn:`linker`
to an executable. In fact, even if just a single source file is compiled into an
executable, the compiler automatically invokes the linker behind the scenes.

Thus, the steps are

1. Write source code. Tool: editor; result: ``.cpp``-File
2. Compile source code to object file. Tool: compiler; result: intermediate
   object file
3. Link object file to executable. Tool: linker; result: executable File
   (``.exe`` on Windows, without extension on Unix-like systems like MacOS and
   Linux).

.. tikz:: From source code to executables.
  :libs: arrows.meta, positioning

  [
    -{Latex[length=4mm]}, auto, node distance=6em,
    file/.style={rectangle, draw, align=center},
    start/.style={circle, fill, draw}
  ]
  \node (start) [start] {};
  \node (cpp) [file, right=of start]
    {Source file\\\texttt{*.cpp}, \texttt{*.cc}};
  \node (obj) [file,right=of cpp] {Object file\\\texttt{*.o}, \texttt{*.obj}};
  \node (exe) [file,right=of obj]
    {Executable file\\\texttt{*.exe}, w/o extension};

  \path (start) edge node {Editor} (cpp)
        (cpp) edge node {Compiler} (obj)
        (obj) edge node {Linker} (exe);


How To: Install a compiler
==========================

Note that nowaydays every compiler comes with a linker, so there is no need to
install an extra linker.

Windows
-------

On Windows, I recommend using Microsoft's free :program:`Visual C++ Express for
Windows Desktop` [#long-ms-names]_. At the time of this writing, the most recent
version (which we will of course use) is 2013 Update 3, downloadable at
http://www.visualstudio.com/downloads/download-visual-studio-vs#d-express-windows-8.
Just click the “Install now!” link, and run the downloaded installer. You can
untick any checkboxes saying something about Windows Phone or .NET.

I will refer to this compiler as :abbr:`MSVC (Microsoft Visual C++)`.

Debian/Ubuntu based Linux
-------------------------

On Debian/Ubuntu based Linux, we will use the :program:`g++` compiler, a part of
the :abbr:`GCC (GNU Compiler Collection)`. Installing is as easy as opening a
terminal and typing ``sudo apt-get install g++``, but since you're using Linux,
I assume you know what you're doing anyway. ;-)

.. _gcc: http://gcc.gnu.org/

.. _intro-compiler-howto:

How To: Compile your source code
================================

(Assuming you saved your file as :file:`hello_world.cpp`)

Windows
-------

Open the :program:`VS2013 x86 Native Tools Command Prompt`. It is located in the
start menu (or whatever you call it nowadays) at :menuselection:`Visual Studio
2013 --> Visual Studio Tools`. Then change the current directory to the folder
where you saved your file using ``cd``, e.g. :samp:`cd
C:\\Users\\{YOURNAME}\\somefolder\\somesubfolder`.

.. note::

  If your source code is on a drive different from the one where the initial
  directory of the command prompt is, use the :samp:`cd /D {YOURDIRECTORY}`
  command (the ``/D`` option means “change the Drive if necessary”).

Compiling is then done with the
command ``cl /EHsc /W4 hello_world.cpp``. You should now see (among others) a
new file :file:`hello_wold.exe`. You can check in the command prompt by typing
``dir``. If you want to execute your program now, type ``hello_world``, and you
should see a line ``Hello world!`` appearing in the console window.

The compiler command
^^^^^^^^^^^^^^^^^^^^

Let's break down the compiler command. ::

  cl /EHsc /W4 hello_world.cpp

``cl`` is the name of Microsoft's compiler. The things preceded by slashes ``/``
are options which tell the compiler how to process your source code. ``/EHsc``
tells it to enable so called *exceptions*, which really should be enabled by
default but isn't. You don't need to understand this, just remember to add this
option whenever you compile C++ code. ``/W4`` stands for “warning level 4” and
tells the compiler to tell you about any suspicious things it notices in your
source code (this also should be a default but sadly isn't in any compiler I
know of).  ``hello_world.cpp`` is obviously the name of the source file to
compile.

Linux
-----

Open a terminal and change the current directory to the one containing your
source file. Then execute
``g++ -std=c++14 -Wall -Wextra -ohello_world hello_world.cpp``. An executable
``hello_world`` should now appear. You can check in the terminal by typing
``ls``. If you want to execute your program now, type ``./hello_world``, and you
should see a line ``Hello world!`` appearing in the terminal.

The compiler command
^^^^^^^^^^^^^^^^^^^^

Let's break down the compiler command. ::

  g++ -std=c++14 -Wall -Wextra -ohello_world hello_world.cpp

``g++`` is the name of the compiler. The things preceded by dashes ``-``
are options which tell the compiler how to process your source code.
``-std=c++14`` tells it that we want to use the newest C++14 standard. ``-Wall``
and ``-Wextra`` tell the compiler to tell you about any suspicious things it
notices in your source code (this should be a default but sadly isn't in
any compiler I know of). ``-ohello_world`` means “output (``-o``) as
``hello_world`` ” and simply specifies the name of the executable to produce. If
you leave this option out, it will be called ``a.out``. 
``hello_world.cpp`` is obviously the name of the source file to compile.


A few command line tips
-----------------------

To use the command line effectively, I recommend reading a good tutorial
[#cmdtut]_. I will, however, give a few tips here:

* You can use the :kbd:`Up` and :kbd:`Down` keys to cycle through your last
  commands. For example, if you want to run the last command again, just press
  :kbd:`Up` again, and the command will reappear, ready to be edited or directly
  started with :kbd:`Return`.
* You can use the :kbd:`Tab` key to complete filenames: for instance, if you
  typed ``hel`` and the file :file:`hello_world.cpp` is in the current
  directory, you can press :kbd:`Tab` to complete the filename.
* Pressing :kbd:`Ctrl+C` quits the running console program and drops you back to
  the command prompt, without closing the console window.
* On Linux, use the ``ls`` or ``ls -l`` command to show the files and
  subdirectories in the current directory. On Windows, ``dir`` does that.
* To open the current directory in your GUI file system browser (e.g. Nautilus,
  Dolphin or Windows Explorer) Use ``xdg-open .`` on Linux and ``explorer .`` on
  Windows.


********************************
The Hello World program analyzed
********************************

Now that you have compiled and run the Hello World program, you are probably
curious what all these cryptic lines in the source code mean. Let's repeat our
little program here:

.. literalinclude:: ex/hello_world.cpp


Linewise breakdown
==================

Preprocessor #includes
----------------------

Let's start with the first line: This is a so-called :term:`preprocessor directive`
more specifically an :dfn:`include directive`. It instructs to compiler to read the
``iostream`` file and paste it contents in place of the directive, just as if we
had written the whole file's content there instead of just the ``#include``. We
need this file because it tells the compiler what ``std::cout`` in line 5 means.
It is part of the :dfn:`standard library`, a set of files that comes with every
C++ compiler.

.. _proc-hello-ws:

Whitespace
----------


The second line is empty, it has no special meaning. I just inserted it to make
the source code look nicer. Generally, C++ ignores all :dfn:`whitespace` (that's
how programmers collectively call spaces, tab(ulator)s and line breaks), except
that they are sometimes needed to separate words. The only time where this was
needed in this program is the space between ``int`` and ``main`` in line 3. The
second case where whitespace has a meaning is preprocessor directives: Here, a
line break is needed to tell the compiler where it ends. This means that, if I
wanted, I could have written the entire program as short as ::

  #include<iostream>
  int main(){std::cout<<"Hello world!\n";}

and it would mean exactly the same as the long version. Oh yes, I have also left
the space between ``Hello`` and ``world`` there, but that will become obvious
when we get to line 5. One can also insert as many whitespace as one wants, for
example::

  #include              <iostream>
                int
  main
                        (
                 ){
     std  ::         cout <<
  "Hello world!\n"

  ;



  }

Pretty much the only place where you cant freely sprinkle whitespace is in
preprocessor directives (the ``#include``-directive in our Hello World program),
where everything must be written on one line, meaning that exactly the following
line breaks are illegal in the program above::

  #
  include
  <
  iostream
  >

Of course, you also can't insert whitespace in the middle of words like writing
``c out`` instead of ``cout``, and there are a few other exceptions in the
form of symbols that are written using more than one character, namely the ``<<``
and the ``::`` in the program above, that could not have been written as e.g.
``< <`` and ``:  :``.

However, I think you see why I wrote the program like I did in the first place:
it is just easier to read.


Defining the main program
-------------------------

Now it starts to get interesting!

.. literalinclude:: ex/hello_world.cpp
   :emphasize-lines: 3,4,6

The third line basically says to the compiler: “Here comes the main program!”
[#fdef]_, and the curly braces show the compiler where it starts (``{`` in line
4) and ends (``}`` in line 6). Everything between them will be executed when the
program is started.


Writing to the console
----------------------

.. literalinclude:: ex/hello_world.cpp
   :emphasize-lines: 5

This line really is the only one that is actually executed at runtime. It is a
so called :dfn:`statement`. These are really “instructions”, or “commands” that
instruct the computer to do something. In this case, it tells the computer to
print the text “Hello world!” followed by a line break (``\n``) to the standard
output (``std::cout``) [#tellcompiler]_. For now, you can thus think of the
``<<`` symbol symbol as meaning “Print the value at the right hand side to the
thing on the left hand side”. [#convoluted]_ The value here is the text between
the quotes (``"``). Such quoted text will be printed as you typed it, except
that a backslash ``\`` is used to give the next character a special meaning
(like the line break/newline character for ``\n``).

Statements are always terminated with a semicolon (``;``). 


Successive Statements
=====================


Of course we can write more than just one statement in the main program. Let's
throw in some more output statements::

  #include <iostream>

  int main()
  {
     std::cout << "This is executed first.\n";
     std::cout << "Hello world!\n";
     std::cout << "Then this,\n"; std::cout << "And this at last.\n";
  }

As you probably expected, this will print:

.. code-block:: none

  This is executed first.
  Hello world!
  Then this,
  And this at last.

The statements are executed in the same order as you write them.

It has no special meaning that I wrote the last two statements in the same line.
As I already :ref:`said <proc-hello-ws>`, the compiler does not care about
whitespace such as line breaks. It determines where one statement ends and the
next one starts based on the semicolons. However, you should generally write
only one statement per line. The above was just for demonstration purposes, it's
no good style.


More output
===========

Here are are a two more things you can do with ``cout``, which will be useful
later on:

You can omit the trailing ``\n`` in the output text, so that the next output
statement will continue in the line started by the former::

  std::cout << "This is "
  std::cout << "on a single line.\n";

yields

.. code-block:: none

  This is on a single line.

And you can use multiple ``<<`` in a single statement::

  std::cout << "Something.\n" << "Something " << "other.\n";

yields

.. code-block:: none

  Something.
  Something other.

Note that in the code examples above, I have only included what is written
between the curly braces of the main program. You already know the rest and
always reading/writing the same :term:`boilerplate code` starts getting boring.


Comments
========

And while we are in the progress of introducing useful misc things, let's do one
more: A *comment* is a part of the code which is ignored by the compiler::


  // Hello World: Print a text to the terminal and exit.

  #include <iostream> // For std::cout.

  int main()
  {
     std::cout << /* The classic text: */ "Hello world!";
  }

This program really just prints “Hello world!”. The source code showcases the
two kinds of comments in C++:

* Line comments start with ``//`` and extend until the line ends.
* C-Style comments start with ``/*`` and end with ``*/``. Note that they
  cannot be nested, so the following is a syntax error::

    /* In comment. /* Still in comment. */ Already outside comment. */

Use comments whenever you think that other people (including your future self)
will have an easier time reading the code with them than without them. Always
assume that these people know C++ and do not comment what the code already says.

You can also use comments to temporarily disable (:dfn:`comment out`) parts of your
code:

.. code-block:: cpp
  :emphasize-lines: 6

  #include <iostream>

  int main()
  {
     std::cout << "Hello world!";
     //std::cout << "Won't be executed.";
  }

This still prints only “Hello world.”. Note that I have not put a space between
the double slash and the comment's content. That's just my personal style: For a
real comment, I separate the text from the comment sign, for commented out code,
I don't.

Summary
=======

* Spaces, tabs and line breaks are collectively called whitespace.
* Except in words, multi-character symbols and preprocessor directives, you can
  freely add whitespace (for the latter, you can still freely add spaces and
  tabs).
* The ``#include`` preprocessor directive inserts the contents of the file with
  the given name literally.
* The ``iostream`` file is necessary for ``std::cout``.
* The main program is executed when the program starts. It is introduced by
  ``int main()`` and  surrounded by curly braces (``{`` and ``}``).
* A statement tells the computer to do something. The semicolon ``;`` tells the
  compiler where the statement ends.
* A program can contain multiple statements. They are executed in the order in
  which they occur in the source code.
* Text between ``/*`` and ``*/`` and the remainder of a line after ``//`` are
  comments: they are ignored by the compiler.
* A value can be printed to the screen with :samp:`std::cout << {value}`.
* ``<<`` can be used multiple times with ``std::cout``, e.g. ``std::cout <<
  "x = " << 42;``
* Text (*strings*) that should be printed literally, has to be enclosed in double
  quotes like ``"Some text."``.
* A ``\n`` in a string will be printed as a line break.

----

.. rubric:: Footnotes

.. [#long-ms-names] Microsoft is infamous for its long product names.

.. [#cmdtut] Although I have not read it and it uses PowerShell on Windows
   instead of the ordinary ``cmd``, http://cli.learncodethehardway.org/book/
   made a good first impression on me, if you can find nothing else.

.. [#fdef] More technically, it says “Here comes a *function* called ``main``
   that *returns* an integer (``int``) and takes no *arguments* (``()``).”
   Because exactly such a function is defined by the standard as being the main
   program, it really does, in effect, say “Here comes the main program!”. We
   will get to the other parts later, step by step.

.. [#tellcompiler] To be more precise, it of course does not directly tell the
   computer to print anything; it tells the compiler to emit the binary machine
   instructions into the output executable that will cause the computer to print
   “Hello World” when the program is executed.

.. [#convoluted] In fact, this line uses many features of the C++ language
   that we will partly come to only very late, e.g. classes, namespaces and
   operator overloading.

