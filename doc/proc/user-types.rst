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

  * The player variables are not explicitly separated from each other or other
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
for the data members by writing them inside the braces, separated by comma:

.. literalinclude:: ex/user-types/player-init.cpp

Output:

.. code-block:: none

  5,3: 100
  1,2: 3
  5,0: 0
  1,2: 42
  10,7: 250
  0,0: 310

If you study the above program and its output you will also notice that 

  * ``= {...}`` can also be used for reassigning variables that have a
    ``struct`` type.
  * If you specify less values in the braces than the struct has members, the
    rest is filled with zero/false. In fact the ``= {}`` syntax we have seen
    before is just a special case of this.
  * If you have a function with a parameter of a ``struct`` type, you can use
    ``{...}`` to create a object of that type with the given values on the fly,
    withouth needing a variable.
  * Similarly, if you have a function with ``struct`` return type, you can use
    ``{...}`` to return create an object of that type with the given values on
    the fly.

Naturally, in all cases where literals like ``42`` or ``5`` were used, you can
use arbitrary expressions like variables or computations of the right type.



``const`` and ``struct``\ s
---------------------------

Of course variables with ``struct`` types can also be made ``const``, meaning
that neither the object as whole nor any of its data members may be modified::

  const Player player = {5, 5, 100};
  print_player(player);
  //player = {3, 3, 500}; // Does not compile, player is const.
  std::cout << player.x;
  //player.x = 6; // Does not compile, player is const.


Nested structs
--------------

Like nearly everything in C++, ``struct``\ s can be nested too. For example, it
is probable that in a game, we will neeed x/y-positions not just for the player
but also for other things like monsters, doors, coins or whatever things are
lying around in the game's virtual world. Thus it totally makes sense to break
out these positions from the ``Player`` type into a new type ``Point``::

  struct Point {
    int x;
    int y;
  };

  struct Player {
    Point position;
    int n_points;
  };

Initialization and member access is naturally also nested then::

  Player pl = {{1, 2}, 0};
  std::cout << pl.position.y << '\n'; // Prints “2”.
  std::cout << pl.n_points << '\n'; // Prints “0”.


Efficiently passing ``struct``\ s to functions
----------------------------------------------

As explained in :ref:`proc-func-stack`, passing an argument to a function
involves pushing it on the stack. While this is fine for small arguments like
``int``\ s and ``double``\ s, most ``struct`` types are much bigger. For
example, our ``Player`` has at least the size of three ``int``\ s. We can check
the exact size with the uary ``sizeof`` operator. This operator can be applied
to a type or to any expression and evaluates to the size of the (expression's)
type measured in bytes [#sizeofbytes]_::

  std::cout << sizeof(int) << '\n';
  std::cout << sizeof(Player) << '\n';
  Player player_a = {};
  std::cout << sizeof(player_a) << '\n';

With the MSVC compiler, the Player has in fact twelve bytes. To avoid copying
all these bytes to the stack for passing it to a function, we could use
references, e.g.::

  void print_player(Player& player) { /* ... */ }

Now only the address (4 bytes on 32 bit systems and 8 bytes on 64 bit systems)
is pushed on the stack. There are two problems though: First, we cannot pass
``const Player`` variables or expressions like ``{5, 5, 100}`` (an rvalue) and
second, we could accidentally change the passed in variable. To avoid both
problems we use ``const`` references::

  void print_player(const Player& player) { /* ... */ }

This solves both of the above problems.

Of course you can also use ``const`` references to builtin types like ``int``,
but this usually makes no sense and is in fact slower than just copying the
``int`` over because accessing the value through a reference is slower than
accessing it directly.


Encapsulation and member functions
==================================

``struct``\ s can be more than simple data containers.


Member functions
----------------

So far, we have only had data members in ``struct``\ s, but it turns out that we
can also add functions to them. For example, we could write a member function
``draw()`` instead of a “free” function ``draw_player(const Player&)`` like this:

.. literalinclude:: ex/user-types/player-memberfn.cpp

While data members like ``position`` and ``n_points`` are stored in each
``Player`` object, functions are not really a part of the object. They behave
like normal functions with the difference that you can only call them on a
particular object (“instance”) of a ``Player`` / ``struct``-type. Behind the
scenes, the member function receives a hidden additional argument. You can think
of it as having the type ``Player const&`` if you write ``const`` after the
function, as done above, or ``Player&`` otherwise (note that this means that you
can only member functions marked as ``const`` on ``const`` objects). Then, when
a variable or function name appears in the member function's body, the compiler
looks in these places:

1. local variables and function parameters
2. members of the hidden additional parameter
3. global variables and free functions

Considering all this, what is the difference to the version with the free
function? If you were to look very closely at the machine code that is generated
from both version, you could see that they are in fact bit-by-bit identical. So
at runtime there is no difference. Now it seems to be only a matter of style,
but there is in fact a drawback: Later when we learn how to split a program into
multiple files, we will see that a ``struct``-definition must not span multiple
files. So without touching the file where the ``struct`` is defined, it is
impossible to add new functions. With free functions, you can add more functions
for working with the ``struct`` without changing the definition.


Encapsulation and access control
--------------------------------

There is an important technique that only works with member functions:
:dfn:`encapsulation` (also called :dfn:`information hiding`). By encapsulating
members of a type, you restrict access to them to member functions of the type
only. This has two advantages: First, you can often change the (now) internal
representation of the type without having to change code that uses the type.
Secondly, it allows you to enforce :dfn:`invariants` on the members, that is to
enforce that some conditions always hold.

For the first advantage, consider how, when we combined the ``x`` and ``y``
members of the player into a new ``Position`` type, we also had to change
``draw_player`` and all other code using ``x`` and ``y``. Were the position
encapsulated in the right way, we wouldn't have had to change anything but the
``Player``\ -\ ``struct`` itself. The following example demonstrates this part
of encapsulation.

.. literalinclude:: ex/user-types/player-hidden.cpp

Everything after ``private:`` is only accessible to member functions of the
``struct``. On the other hand, everything after ``public:`` is also accessible
to outside functions. These key words are called :dfn:`access control key
words`. It is customary to not intend them (relative to the ``struct`` itself).

.. note:: Access-control is per-type not per-object.

  That is, having a member function like the following ``Player``::

    void steal_points(Player& other) { m_n_points += other.m_n_points; }

  in ``Player`` and using it like this::

    player_a.steal_points(player_b);

  is completely OK.

Notice how instead of having a public data member ``n_points``, ``Player`` now
has a private data member ``m_n_points`` (the ``m_`` is just a fairly customary
name prefix to mark private data members) and two function for accessing it,
namely ``int n_points()`` to get the value and ``set_n_points(int)`` to set it
(the parameter name ``n_points_`` has a trailing underscore to distinguish it
from the ``n_points()`` function).  The former function is called a
:dfn:`getter` and the latter a :dfn:`setter`. Note that not every getters must
have a corresponding setter (or vice versa, though that is more unusual), e.g.
the position of a ``Player`` is read-only because only a getter ``Point
position() const`` is provided. On the other hand, there may be getters and
setters for “properties” that are not even directly backed by data members, as
is the case with the ``x`` and ``y`` properties of the player.

.. note:: Getters are often used in expressions involving more than one function
  call and thus should be side-effect free; see :ref:`sec-sideeffect`.


Constructors
------------

There is a problem with the previous example: it fails to realize the second
advantage of encapsulation, namely maintained invariants. Although we have not
explicitly stated any, it clearly undesirable to have a ``Player`` where any
members are initialized. In fact, the situation regarding initialization with
this partially-encapsulated example is worse than before since we cannot use the
``= { … }`` syntax anymore because the data members are private (in fact this
:dfn:`aggregate initialization`` cannot be used at all as soon as *any* members
of the initialized type are private). To remediate this, you can define a
special member function called the :dfn:`constructor`. Constructors functions
have no return type and the same name as the type. They can have parameters but
don't have to. A constructor that can be called without parameters is called a
:dfn:`default-constructor`. If we add a default-constructor to our ``struct
Player``, it looks like this::

  struct Player {
  public:
      Player():
          m_position{0, 0},
          m_n_points{0}
      {
      }

      // ... getters and setters as before ...
  private:
      Point m_position;
      int m_n_points;
  };

The effect of this change is that every ``Player`` variable will be
automatically initialized with position of (0, 0) and zero points.

Apart from the name, which is the same as the type's, and the missing return
type, constructors have one more feature that normal functions don't have:
Initializer lists. This comma-delimited list starts at the ``:`` after the
argument list and the entries have the form ``data_member_name{initial_value}``.
In the case of ``Player`` above, this is the same as if we had written::

  Player()
  {
      m_position = {0, 0};
      m_n_points = 0;
  }

There are cases where this makes a differences, namely when the some data
members have constructors themselves.

Instead of a default-constructor, we could also add a constructor that accepts
the initial values as arguments::

  Player(Position position_, int n_points_):
      m_position{position_},
      m_n_points{n_points_}
  {
  }

Now I can also explain where the initializer list behaves different from using
``=``: E.g. if ``Point`` had a constructor ``Point(int x, int y)``, then we
would have to use the initialization list, because if we leave it out, the
compiler will try to insert a call to the default constructor as if we had
written:

.. code-block:: cpp
  :emphasize-lines: 2

  Player(Position position_, int n_points_):
      m_position{}
  {
      m_position = position_;
      m_points = n_points;
  }

Since the constructor of ``m_position`` requires two ``int``\ s as parameters,
however, this would be an error.


A quick glance at templates
===========================

One thing that is a bit limiting for the ``struct Point`` is that it only has
``int``\ s as the ``x`` and ``y`` components. If we only use the ``Point`` for
one application and we only need ``int``, that may be fine. But in general, we
might need ``Point`` s of ``double`` or ``int`` or maybe in one case we need to
optimize for memory and even want to use a ``Point`` of ``signed char``. We
could just write a class for every case such as::

  struct IntPoint { int x; int y; };
  struct FloatPoint { float x; float y; };
  struct DoublePoint { double x; double y; };
  // ...

In the case of ``Point`` this may even be feasible as the ``struct`` is so tiny.
But now imagine we also wanted to provide some functions for ``Point``\ s, such
as::

  IntPoint move_int_point(IntPoint p, IntPoint by)
  {
      return {p.x + by.x, p.y + by.y};
  }

  void print_int_point(IntPoint p)
  {
      std::cout << '(' << p.x << ',' << p.y << ')';
  }

If we had :math:`n` functions and :math:`m` types of points, we would need to implement all
of the :math:`n` functions separately for all :math:`m` types which results in :math:`m \cdot n`
functions. Clearly this does not scale up well.


Class templates
---------------

With the template mechanism of C++, ``struct``\ s we can instead write a struct
template (usually called a :dfn:`class-template`) for ``Point``::

  template <typename T>
  struct Point {
      T x;
      T y;
  };

The ``template`` keyword tells the compiler that what follows is a template
definition and inside the angle brackets (which are used the usual less-than and
greater-than signs repurposed) come the template parameters. In this case the
template has as parameter a type (``typename``) with the parameter name ``T``.
Inside the template definition, you can use ``T`` just like a normal type.

To use this class template, we now need to specify the template parameter:

.. _lst-point-tpl-usage:

::

  void print_point(Point<int> p)
  {
      std::cout << '(' << p.x << ',' << p.y << ')';
  }

  int main()
  {
      Point<int> mypoint = {2, 5};
      print_point(mypoint)
  }

This is very similar to functions. In fact, you could view the class template
``Point`` as a “type function” that takes a component-type as parameter and
“returns” a point-type. The big difference is that this “computation” is done by
the compiler and not when the program runs.


Function templates
------------------

Now we need to write only one ``Point`` class-template instead of several
``SomeTypePoint`` classes, but we still would need :math:`m \cdot n` functions. But
function templates come to the rescue!

.. sidebar:: Function templates can be used without class templates

  Of course, you can also use function-templates without class-templates.  For
  example, we could make our good old factorial function a function template::

    template <typename T>
    T factorial(T n)
    {
        T result = 1;
        for (T i = 1; i <= n; ++i)
            result *= i;
        return result;
    }

::

  template <typename T>
  void print_point(Point<T> p)
  {
      std::cout << '(' << p.x << ',' << p.y << ')';
  }


Transforming ``print_point`` from a function to a function-template should look
extremely similar to the previous tranformation of ``Point`` to a
class-template. However, when calling a function template, there is a catch: You
usually don't need to specify the template parameter because the compiler
figures them out automatically by comparing the function argument with
parameter. That is, the ``main`` function :ref:`from before
<lst-point-tpl-usage>` now looks exactly the same!

By using class- and function-templates, instead of :math:`m \cdot n` functions,
we now need to write each function only once for all ``Point`` types, greatly
improving maintainability and readability of the program.

----

.. rubric:: Footnotes

.. [#sizeofbytes] Actually, the C++ standard defines ``sizeof`` to return the
   size in multiples of ``char``'s size (``sizeof(char)`` is defined to be
   ``1``). Although the standard only specifies that a ``char`` must be *at
   least* one byte large, in practice it has exactly one byte on all but some
   exotic platforms.
