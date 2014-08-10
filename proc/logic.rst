***************************
Logic and more on operators
***************************

The ``bool`` type
=================

Apart from numbers and text, there is one more fundamental type in C++: The
truth value. They have the type name ``bool`` (which is short for :dfn:`Boolean
value`, named after the mathematician `George Boole`_) and can have one of two
values: ``true`` or ``false``. Booleans are crucial to every program, as they
allow to make decisions, as we will see in later sections of this chapter.

.. _George Boole: http://en.wikipedia.org/wiki/George_Boole

The syntax for declaring, assigning, and so on is the same as for other types.
The only difference is that the literals are the keywords ``true`` and ``false``
instead of numbers or quoted strings. ``cout`` and ``cin``, however, will
print/accept “0” and “1” (mainly for historical reasons).

.. sidebar:: Integers as booleans

   The historical reasons for the 0/1 instead of false/true lie in C, the
   language on which C++ is built. C had no ``bool`` type. Instead, one would
   use an integer type like ``int`` and let, by convention, 0 represent
   false and 1 true. Even today, one can assign ``0`` to a ``bool`` in C++ and
   it will be converted to ``false`` and any nonzero value will become ``true``.
   This is the same principle as with floating point numbers being converted to
   integers. In fact, C++ even does the conversion from floating point to
   boolean, as in ::

     bool foo = 3.14; // foo becomes true

   The language is even crazy enough to accept text (for reasons we will come to
   when talking about strings)::

     bool bar = "Some text"; // Both true
     bool baz = "";          //

   Of course, you usually don't want that and your compiler will, if given the
   right command line options, warn you about such mistakes.

.. literalinclude:: logic-bool-vars.cpp

Example output (with input “0”):

.. code-block:: none

  true : 1
  false: 0

  Valid? 1
  Still valid? 0

  Enter a boolean value (0 for false, 1 for true): 0
  You entered 0.


“Calculating” with Booleans
===========================

There exist three useful operations which you can perform on Booleans. The first
one is `logical negation`_ aka :dfn:`not` with the unary ``!`` operator. It
makes ``true`` values ``false`` and vice versa (it is true if x is *not* true):

=====  =====
x      !x
=====  =====
false  true
true   false
=====  =====

The second one is `logical conjunction`_ aka :dfn:`and`. The binary ``&&``
operator results in true if and only if [#iff]_ both of its operands are
``true`` (if x *and* y are true):

=====  =====  ========
x      y      x && y
=====  =====  ========
false  false  false
false  true   false
true   false  false
true   true   true
=====  =====  ========

The third one is `logical disjunction`_ aka (inclusive) :dfn:`or`. The binary
``||`` operator is true if at least one operand is ``true``. Note that this is
also true if both operands are ``true``; that is, it's not an “either x or y”,
(exclusive or) it's “x or y or both” (inclusive or).

=====  =====  ======
x      y      x || y
=====  =====  ======
false  false  false
false  true   true
true   false  true
true   true   true
=====  =====  ======

In composite expressions like ``x || y && !z``, ``!`` is evaluated first (in
general, unary operators are evaluated before binary ones in C++) and ``&&`` is
evaluated before ``||``. That is, the aforementioned expression has the same
meaning as ``x || (y && (!z))``.


.. _logical negation: http://en.wikipedia.org/wiki/Negation
.. _logical conjunction: http://en.wikipedia.org/wiki/Logical_conjunction
.. _logical disjunction: http://en.wikipedia.org/wiki/Logical_disjunction


The following program demonstrates some uses of these operators:

.. literalinclude:: logic-boolops.cpp

Note that we had to put the expressions in parentheses for output. That's
because the compiler would otherwise try to generate instructions that evaluate
``<<`` first, reading the code like e.g. ::

  (std::cout << "Ready for boss fight: " << has_armor)
  && has_sword && (quest_complete << "\n");

which is, of course, bogus and leads to a compile error.


Comparison operators
====================

We already saw the arithmetic operators ``+``, ``-``, ``*`` and ``/`` on
numbers. These took two numbers, converted it to a common type if necessary,
and returned a number of that common type. There is, however, another category
of operators which are used to compare numbers. Like the arithmetic operators,
they take two numbers, converting to a common type if necessary. However, they
do not return a number, but a truth value: a ``bool``. Here they are:

* The equality operators:

  + ``==`` (that's a double equals sign) returns ``true`` if its operands are
    the same. E.g. ``1 == 1`` yields ``true``, while ``1 == 2`` yields false.
    Don't confuse it with the assignment operator ``=`` which is written with
    just a single equals sign. 
  + ``!=`` means not-equal (≠) and is the opposite of ``==``: it returns
    ``true`` if its operands are *not* the same. E.g. ``1 != 2`` returns
    ``true``, while ``1 != 1`` is false.

* The relational operators:

  + Less-than ``<`` returns ``true`` if its left-hand side operand is smaller
    than its right-hand side operand. E.g. ``1 < 2`` is true, while ``2 < 1``
    and ``1 < 1`` are both false.
  + Less-than-or-equal ``<=`` tests if the right-hand side is at least as big as
    the left-hand side: ``1 <= 2`` and ``1 <= 1`` are ``true``, while ``2 <= 1``
    is not.
  + Greater-than ``>`` tests if the left-hand side is greater than the
    right-hand side. E.g. ``2 > 1`` is true, while ``1 > 2`` and ``1 > 1``
    aren't. It always returns the opposite of ``<=`` (and not of ``<``, as one
    might think; this is not a quirk, it's perfectly, mathematically logical).
  + Greater-than-or-equal ``>=`` tests if the left-hand side is at least as big as
    the right-hand side: ``2 >= 1`` and ``1 >= 1`` are ``true``, while ``1 >= 2``
    is not. It always returns the opposite of ``<``.

.. warning:: Be careful when comparing floating point values for equality!

  Due to their inexactness, this can have unexpected results.  The usual way to
  deal with this (if you cannot avoid equality comparison) is to check if the
  difference between two numbers is below a certain threshold (e.g. ``0.00001``)
  instead.

This example program let's you enter two numbers and outputs the results of all
comparison operators on them as a table:

.. literalinclude:: logic-comparison.cpp

Example output for inputs x = 1 and y = 2:

.. code-block:: none

  Enter x: 1
  Enter y: 2

  x == y? 0
  x != y? 1

  Relation: <   <=  >   >=
  ------------------------
  x OP y? | 1   1   0   0
  y OP x? | 0   0   1   1

Example output for x and y both 1:

.. code-block:: none

  Enter x: 1
  Enter y: 1

  x == y? 1
  x != y? 0

  Relation: <   <=  >   >=
  ------------------------
  x OP y? | 0   1   0   1
  y OP x? | 0   1   0   1


Mixed expressions and more on operators
=======================================

Before we go on with using Booleans to influence which parts of our programs
execute, you should know some more things about operators and expressions.

It is entirely possible and often useful do arithmetic calculations in
expressions with comparison operators and use logical connectives on their
Boolean results:

.. literalinclude:: logic-mixed-expressions.cpp

Example output with player level 5 and sword strength 6 (no cheating):

.. code-block:: none

  Enter your level: 5
  Enter your sword's strength: 6
  Are you a cheater? 0
  You beat the monster: 0


Note that operators are evaluated in this order:

1. Unary operators (unary ``-`` and ``!``)
2. Arithmetic operators (first ``*`` and ``/`` then ``+`` and ``-``)
3. “Input and output” operators (``>>`` and ``<<``)
4. Comparison operators (first ``<``, ``<=``, ``>`` and ``>=``
   then ``==`` and ``!=``).
5. Logical connectives (first ``&&``, then ``||``).
6. Assignment operator (``=``) and compound assignment operators (``+=``,
   ``-=``, ``*=``, ``/=`` and ``%=``)

That is, the initialization expression of ``winning`` has the same meaning as ::

  is_player_in_god_mode
  || ((player_level + sword_strength) > monster_level)

C++'s order of operator evaluation is intended to allow omitting parentheses in
most cases; however, I recommend using better too many than too few parentheses:
not everyone can always correctly remember the order of operator evaluation and
parentheses make the order of evaluation unambiguous to the reader.

How early an operator is evaluated in relation to other operators is a property
that has it's own name: the :dfn:`precedence` (level) of an operator. The higher
the level, the earlier an operator is evaluated.

Operator associativity and “multi-assignment”
---------------------------------------------

As the complement to its precedence, there is also the :dfn:`associativity` of
a binary operator: It tells you in which order operators of the same
precedence level are evaluated (thus all operators of the same precedence
level must have the same associativity). Most operators we know yet are
left-associative; that is they are evaluated from left to right. For example
the expression ``x - y - z`` is evaluated as ``(x - y) - z``. If ``-`` was
right-associative, this expression would be evaluated as ``x - (y - z)``.

The only right-associative operators we have seen until now are the assignment
operators. Thus the expression ``x = y = z`` is evaluated as ``x = (y = z)``.
What does it mean?

The assignment operator does two things (in this order): first, it (obviously)
assigns the right-hand side operand to the variable on the left-hand side. And
second, it returns the assigned-to variable. Thus ``x = y = z;`` is the same as
``y = z; x = y;``: ``x`` and ``y`` both get the value of ``z``. If ``=`` was
left-associative, ``x = y = z`` would be evaluated as ``(x = y) = z``, which is
the same as ``x = y; x = z;``, leaving ``y`` unchanged and assigning to ``x``
twice in a row. Fortunately, this is not the case. You can thus use statements
of the form ::

  a = b = … = z = some_expression;

to assign the value ``some_expression`` to all of the variables ``a`` through
``z``.

The same that has been said about ``=`` also applies to the compound assignment
operators ``+=``, ``-=``, ``*=``, ``/=`` and ``%=``. However, while ``a = b =
c`` has an intuitive and easy-to-read meaning, ``a += b += c`` does not. I thus
recommend using either one or multiple “simple” assignment operators ``=`` or
only one compound assignment operator [#good-comment]_.

Background: The input/output operators (``>>``/``<<``)
------------------------------------------------------

The statement ::

  std::cout << "x = " << x << "\n";

consists solely of an expression: The ``<<``\ s are the operators and
``std::cout``, ``"x = "``, ``x`` and ``"\n"`` are the operands. Because ``<<`` is
left-associative, this expression means the same as ::

  ((std::cout << "x = ") << x) << "\n";

The trick here is that ``std::cout`` is an object of a special type (a
``std::ostream``, i.e. output stream [#stream]_) for which the ``<<`` is defined
as “Output the ritht-hand side operand (on the stream on the left-hand side) and
then return the left-hand side”. Thus, the expression ``std::cout << "x = "``
returns ``std::cout`` after printing ``"x = "``, and what is left of the
original expression is equivalent to ::

  (std::cout << x) << "\n";

this process continues with ``std::cout << x`` returning ``std::cout`` (after
printing ``x``' value) leaving just ::

  std::cout << "\n";

This prints the linebreak and then returns ``std::cout`` again, but this time
the expression's value is not used, which is legal in C++: you can even write
statements like ``1 + 2;`` as-is in your source code and it will compile and do
nothing (this is one more thing where (at least some) compilers can warn you;
more often than not, such pointless statements result from typing mistakes or
copy & paste errors).

Analogously the same applies to ``std::cin`` (which is of type
``std::istreaam``, i.e. input stream) and the ``>>`` operator; that is you can
read more than one variable in one expression (and thus statement), like this::

  int x;
  int y;
  std::cout << "Enter the x and y coordinates: ";
  std::cin >> x >> y;


.. rubric:: Footnotes

.. [#iff] The phrase “if and only if” is so common in mathematics and logic
   that it is shortened to the single word :dfn:`iff`.

.. [#good-comment] If you should ever come across a situation where the multiple
   compound assignments would make the code a lot shorter, this would be a good
   opportunity for a comment, like::

     // Calculate a1 as the sum of a1..a9;
     // ai will contain the intermediate value a9 + a 8 + ... + ai
     a1 += a2 += a3 += a4 += a5 += a6 += a7 += a8 += a9;

   However, the above would most certainly be better written using two concepts
   we will cover later, namely loops and arrays.

.. [#stream] You can imagine a stream as a pipeline where you put data in at one
   end (e.g. your program or the keyboard) and it comes out at the other end
   (e.g. the screen or in the variable given to ``std::cin``).
