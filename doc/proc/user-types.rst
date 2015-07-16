******************
Defining new types
******************

When developing complex programs, you only seldom have to to with ``int``\ s or
``double``\ s directly. Most of the time you will work with objects that
correspond to real-world (or virtual-world) objects like persons, credit cards,
bank accounts, players, monsters, books, dates and so on. Dealing with these by
explicitly juggling with C++'s built-in types quickly becomes cumbersome and
error-prone.

For example, assume we are developing a game in which two player can move across
the screen and has a certain amount of points. To represent this player in our
program we could use two ``int``\s for the x and y-coordinate of the position
and another one for the points:

.. literalinclude:: ex/user-types/player-notypes.cpp

This code suffers from several problems:

  * The player variables are not explicitly seperated from each other or other
    unrelated variables.
  * The variables are are ordinary ``int``\ s. E.g. nothing would prevent you
    from accidentally writing nonsensical statements like::

      // Oops, wrong order!
      draw_player(player_a_points, player_a_x, player_a_y);

      // Oops, players mixed!
      draw_player(player_a_x, player_a_y, player_b_points);

      // More nonsense:
      next_round(player_a_points);
      draw_player(player_b_x, player_b_y, game_round);

  * Adding a new data component to a player involves changing all places where
    a player was used.


Simple compound types: ``struct``
=================================

By using the ``struct`` construct and the ``.`` (dot) operator, we can improve
our program as follows:

.. literalinclude:: ex/user-types/player-struct.cpp
  :linenos:

First, we define the ``Player`` structure in line 3 ‒ 6. It starts with the
keyword ``struct`` followed by a name. Then come, inside curly braces ``{}`` the
data members of the ``struct``: these are just explicitly typed variable
definitions, like with local variables. After the closing curly brace follows a
semicolon ``;`` (contrary to functions, where this is neither required nor
allowed).

This structure is its own type. It can be used quite similarly to built-in types
like ``int``: It can e.g. be used as function parameter type (line 8) or for
local variables (line 24). However, since it is a distinct type, you cannot
assign a ``Player`` variable to an ``int`` variable or vice versa, solving the
second of the aforementioned problems. To use variables of the type ``Player``
the program above uses the following operations on the whole ``struct Player``
object:

  * Initialize all members to zero by using ``= {}`` (``bool``\s would become
    ``false``; see line 24).
  * Assign players to each other (happens implicitly when passing the player by
    value to ``draw_player``; see lines 8 and 27, 28 and 32).

However, in the end a ``struct`` only consists of its data members, and hence
the most important operation of a ``struct`` object is accessing its members.
This is done with the ``.`` (dot) operator in lines 11, 12 and 31 of the above
program. An member access expression like ``player.x`` can be used like a normal
variable: both reading the data member (e.g. writing it to ``std::cout`` or
saving it into an ``int`` variable) and writing to it (i.e. assigning to it
using ``=`` or using a compound assignment operator like ``+=``) is possible: it
yields an *lvalue*. As a consequence of being an lvalue you can also bind this
to a reference like::

  Player player = {};
  int& rx = player.x;
  rx = 3; // Now player.x is also 3.
  player.x = 42; // Now rx is also 42.

Note that the two ``Player`` variables are of course independent of each other,
just like the ``int`` variables were in the initial program. This means that
changing data members of one player will not change the other player.

``struct`` initialization with ``{}``
-------------------------------------

In the above example programs we have always used ``= {}`` to initialize all of
a ``struct``\ s members with zero. However, we can also choose our own values
for the data members by writing them inside the braces, seperated by comma:

.. literalinclude:: ex/user-types/player-init.cpp

Output:

.. code-block:: none

  5,3: 100
  1,2: 3
  5,0: 0
  1,2: 42
  10,7: 250

If you study the above program and its output you will also notice that 

  * ``= {...}`` can also be used for reassigning variables that have a
    ``struct`` type.
  * If you specify less values in the braces than the struct has members, the
    rest is filled with zero/false. In fact the ``= {}`` syntax we have seen
    before is just a special case of this.
  * If you have a function with a parameter of a ``struct`` type, you can use
    ``{...}`` to create a object of that type with the given values on the fly,
    withouth needing a variable.

Naturally, in all cases where literals like ``42`` or ``5`` where used, you can
use arbitrary expressions like variables or computations of the right type.


``const`` and ``struct``\ s
---------------------------

Of course variables with ``struct`` types can also be made ``const``, meaning
that neither the object as whole nor any of its data members may be modified::

  const Player player = {5, 5, 100};
  print_player(player);
  //player = {3, 3, 500}; // Does not compile.
  std::cout << player.x;
  //player.x = 6; // Does not compile.
