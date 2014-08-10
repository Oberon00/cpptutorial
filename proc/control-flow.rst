************
Control flow
************

Until now, the “paths” that the execution of our programs took have been quite
simple: It started with the first statement, went on with the second, and so on,
executing one statement after the other, each exactly once and after the last
statement, the program ends. It turns out that this is not enough for all but
the most trivial programs. What is needed are special statements that influence
this :dfn:`control flow`.


Conditional execution: ``if`` and ``else``
==========================================


``if``
------

The simplest control flow statement is ``if``. The syntax is::

  if (boolean_expression)
      statement

This executes the given ``statement`` only if ``boolean_expression`` evaluates
to ``true``.

The following program demonstrates that:

.. literalinclude:: conditional-division.cpp
   :emphasize-lines: 13-14

Example output with dividend 3 and divisor 4 (note that the statement printing
the divisions result is executed):

.. code-block:: none

  Enter dividend: 3
  Enter divisor: 4
  Result: 0.75
  Good bye!

Example output with dividend 3 and divisor 0 (note that the statement printing
the division is *skipped*):

.. code-block:: none

  Enter dividend: 3
  Enter divisor: 0
  Good bye!

You have probably noted that I indented the statement that is conditionally
executed. The compiler :ref:`ignores this <proc-hello-ws>`, but it is the usual
convention to indent the contents of a control-flow statement, just like you
indent the contents of the main program.


``else``
--------

An obvious missing “feature” of the above program is the output of an error
message, when the divisor is zero. You could do that like this (only relevant
part of the main program shown)::

  if (divisor != 0)
      std::cout << "Result: " << dividend / divisor << "\n";
  if (divisor == 0)
      std::cout << "E: Cannot compute result: Divisor is zero.\n";

But this is not an ideal solution: First, the condition has to be written twice
(once “normal” and once logically inversed), and secondly the condition is also
checked twice at runtime. You could workaround this, by storing the result of
the normal condition in a Boolean variable and using the ``!`` operator for the
inversed condition, but C++ already has a keyword that does the equivalent for
you: ``else``. Using this, the above snippet could be rewritten as::

  if (divisor != 0)
      std::cout << "Result: " << dividend / divisor << "\n";
  else
      std::cout << "E: Cannot compute result: Divisor is zero.\n";

This also has the advantage of being immediately clear to the reader: ``if`` the
condition is true, do this, ``else`` do that.

.. aside:: Checking if ``std::cin`` succeeded

   When using ``std::cin`` we have always trusted the user to enter correct
   values. If a incorrect value was entered, our program would screw up,
   invoking undefined behavior because the variable that we meant to get from
   the user was not initialized. Using ``if`` we can now check if ``std::cin``
   suceeded. You might :ref:`remember <proc-logic-io>` that the ``>>`` operator
   ``std::cin`` returns the input stream (i.e. ``std::cin``) after trying to
   read in the value. It turns out that streams can be converted to booleans:
   They evaluate to ``false`` if any previous operation on them (like reading in
   a variable) failed and to ``true`` otherwise. This means that you can do the
   following::

     if (std::cin >> x)
         std::cout << "Got x = " << x << "\n";
     else
         std::cout << "E: You entered a bad value for x.";

   For real programs you should definitely do that but for simplicity, I will
   ignore that error checking in our example programs.

   Still better would be to let the user reenter a correct value, but
   ``std::cin`` does not make this too easy: As soon as a bad value is entered,
   it basically stops working and you have to do special things we will cover
   (much) later to restore it.


Block statements
================

In the previous program and snippets, there always has been only one statement
that was conditionally executed. Indeed, in C++ only the one next statement
after the ``if`` or ``else`` is influenced by it. However, most of the time, you
will have execute more statements conditionally. The way to do this is to use a
special kind of statement after ``if``/``else``: a block statement. It has the
following syntax::

  {
      statement_1
      statement_2
      …
      statement_n
  }

That is, as many statements as you like (one or zero statements are also
allowed), inside a pair of braces. Block statements have no special meaning on
their own (apart from scope; we will come to this in the next section). For
example, the following snippets are completely equivalent::

  std::cout << "A";
  {
      std::cout << "very";
      std::cout << "simple";
  }
  std::cout << "program.\n";

prints “A very simple program.”, just like the following::

  std::cout << "A";
  std::cout << "very";
  std::cout << "simple";
  std::cout << "program.\n";

The real use of block statements is after ``if``, ``else`` and the other control
flow statements we will see later: since a block statement is just a single
(though composite) statement, using it as the one statement after the ``if`` (or
``else`` or other control flow statement) allows to execute multiple statements
conditionally.

For example, the following program sorts two numbers that the user enters:

.. literalinclude:: conditional-sort.cpp

Example output with input “1 2”:

.. code-block:: none

  Enter two numbers: 1 2
  Numbers already sorted.
  Smaller number: 1
  Bigger number: 2

and with “2 1”:

.. code-block:: none

  Enter two numbers: 2 1
  Smaller number: 1
  Bigger number: 2

There are mainly two things to note about this program (apart from the fact that
it uses a block statement, but this should be obvious): The placement of the
braces and the ``else`` and the statements inside the ``if``.

Brace style
-----------

I placed the first opening brace on the same line as the ``if`` keyword and the
closing brace at a new line, at the same :dfn:`indentation level` (i.e. with the
same indentation) as the corresponding ``if``. The ``else`` directly follows the
brace that closes the block of the ``if`` to which it belongs. I also put the
``std::cout << "Numbers already sorted";`` inside a block statement, although
there would be no need for it; I just prefer to have the parts that belong to
the same ``if`` either all in blocks or all without blocks. The braces of the
``else`` statement follow the same principle as the ``if``'s: opening one
directly after the ``else``, closing one with the same indentation as the
line of the ``else`` keyword. The closing brace is on a line of its own because
the next statement is not part of the ``if``/``else``.

There are other ways to do this. In a common one, the ``if``/``else`` would look
like this::

    if (a > b)
    {
        auto original_a = a;
        a = b;
        b = original_a;
    }
    else
    {
        std::cout << "Numbers already sorted.\n";
    }

This style puts every brace on a line of its own. It has the advantage of making
the control flow statements even more visible. It does, however, need three
lines more in this example, which I personally think makes the code look so
“stretched” that it hinders my flow of reading.

There are other styles of brace formatting and indentation in general. You can
read about them e.g. in `Wikipedia <http://en.wikipedia.org/wiki/Indent_style>`_.


Swapping
--------

The other interesting part of the program are the statements inside the ``if``::

  auto original_a = a;
  a = b;
  b = original_a;

This has the effect of swapping ``a`` and ``b`` and is probably the simplest
well known “algorithm”. First, ``a`` is copied into the new variable
``original_a``, then ``b`` is assigned to ``a`` and finally ``b`` gets the value
that ``a`` had before ``b`` was assigned to it. This might seem needlessly
complicated at first look, but consider what the naïve variant would do::

  a = b;
  b = a;

First ``a`` gets assigned the value of ``b``. Then ``b`` gets assigned the value
of ``a`` --- but wait! What value does ``a`` have at this point? It was already
assigned from ``b`` and its original value was overwritten and is now lost.

Why do we want to swap ``a`` and ``b`` here in the first place? Because the two
numbers are either already sorted (then we do nothing) or they are not sorted,
in which case they must be in completely reverse order (because there are only
two numbers) and swapping them reverses the order again, thus establishing the
right (sorted from smallest to largest) order. Of course, sorting more than just
two numbers is more involved than that, but many algorithms that do it still use
the swapping of two numbers as a fundamental operation.


Scope
-----

If you play with the sorting program above, you might notice that you cant't
access the ``original_a`` variable outside the block in which it is defined,
i.e. inside or after the ``else`` block.

Apart from type, value and associated memory, a variable also has a
:dfn:`scope`. The scope is the area of the source code in which the variable can
be referred to. It starts at it's definition and ends where the (innermost)
block in which it was declared ends. Thus the scope of ``original_a`` extends
only to the end of the ``if``'s block statement, but not outside it. If you
wanted to use the variable after the ``if`` you would have to define it outside
the block::

  auto original_a = a; // Point of definition for original_a.
  if (a > b) {
      // original_a can be used here
  } else {
      // and here
  }
  // and also here

However, since in this example we don't need ``original_a`` outside the ``if``,
it's best to leave it's definition were it was: In general you should always
make the scope of a variable as small as possible and as big necessary.


Nested control flow and ``else if``
===================================

Like you can write arbitrarily complex expressions, you can also write
arbitrarily complex control flow structures. The following program demonstrates
that:

.. literalinclude:: conditional-nested.cpp

Try the program out yourself! Make sure you see all four possible outputs.

Note that it does not directly play a role if blocks are used or not. For
example, the following does what one would expect (and what the indentation
suggests)::

  if (x >= 0)
    if (x <= 100)
      std::cout << "x is between 0 and 100.\n";

The outer ``if`` applies to the one next statement, which is the inner ``if``.
This inner if, however, applies to the ``cout`` expression, so that from the
outer ``if``'s point of view, ``if (x <= 100) std::cout << …`` is just one
statement.

In this case, the nesting does not really make sense: the and operator `&&``
could (and should) be used instead::

  if (x >= 0 && x <= 100)
    std::cout << "x is between 0 and 100\n";


The dangling ``else`` problem
-----------------------------

You should be particularly careful with nested ``else``. For example, consider
the following program:

.. literalinclude:: conditional-dangling-else.cpp

Did you expect these outputs?

.. code-block:: none

  Enter x: 2
  x is between 0 and 100.

.. code-block:: none

  Enter x: -5

.. code-block:: none

  Enter x: 101
  x is negative.

If not, remember that the compiler does not care about indentation. For it, the
``if``/``else`` part of the program could also have been written as ::

  if (x >= 0)
  if (x <= 100)
  std::cout << "x is between 0 and 100.\n";
  else
  std::cout << "x is negative.\n";

How should the compiler know which ``else`` belongs to which ``if``? This
problem is so common in imperative languages, that it ha got it's own name: the
`dangling else problem`_. In C++ (and most other languages), there is a simple
rule: When there is an ambiguity, the ``else`` belongs to the nearest possible
``if``. Thus, the “correct” indentation of the code above (i.e. the indentation
that reflects its meaning) would be::

  if (x >= 0)
      if (x <= 100)
          std::cout << "x is between 0 and 100.\n";
      else
          std::cout << "x is negative.\n";

That should explain the output. To give the code the originally intended
meaning, the inner ``if`` should be put in a block statement::

  if (x >= 0) {
      if (x <= 100)
          std::cout << "x is between 0 and 100.\n";
  } else {
      std::cout << "x is negative.\n";
  }

Alternatively, the following also means the same:

.. code-block:: cpp
  :emphasize-lines: 4

  if (x >= 0)
      if (x <= 100)
          std::cout << "x is between 0 and 100.\n";
      else {}
  else
      std::cout << "x is negative.\n";

By giving the inner ``if`` an empty ``else`` branch, the next ``else`` is force
to the outer ``if``. However, although technically correct, this is rather
obscure and I recommend just using block statements instead.

.. _dangling else problem: http://en.wikipedia.org/wiki/Dangling_else


``else if``
-----------

There is, however a common use for nesting control flow statements without
blocks. Look for example at the following program that determines, whether a
number is positive, negative or zero:

.. literalinclude:: conditional-else-if.cpp
   :emphasize-lines: 11-12

The ``else if`` is not a new statement: it's just an ``if`` nested inside a
``else``. However, it is usually formatted like a single control flow statement
(also in the above). Using the technically correct indentation, the code would
look like::

    if (x < 0)
        std::cout << "x is negative. (-)\n";
    else
        if (x > 0)
            std::cout << "x is positive. (+)\n";
        else
            std::cout << "x is zero. (0)\n";



Loops
=====

While ``if`` executes its “attached” statement either one or zero times, loops
allow you to conditionally execute a statement many times. Finally, you can let
the computer do the repetition for you!

Repeat conditionally -- ``while``
---------------------------------

The ``while`` loop has nearly the same syntax as ``if``, only the keyword is
different::

  while (boolean_expression)
    statement

It executes ``statement`` as long as ``boolean_expression`` is true.
``boolean_expression`` is checked each time before executing ``statement``.
This means that if ``boolean_expression`` is already ``false`` at the point
where the ``while`` is first reached, ``statement`` will never be executed.

Play around with the following program!

.. literalinclude:: loop-while.cpp

.. note::

  Basically, that's it for control flow! Using ``if`` and ``while`` you can
  express every imaginable control flow. Theoretically, you would not even need
  ``if``, because you can express it using ``while``::

    if (something)
        std::cout << "Something!\n";

  could be written as ::

    auto first_execution = true;
    while (first_execution && something) {
        first_execution = false;
        std::cout << "Something!\n";
    }


``do … while``
--------------

.. todo::
   Not necessary most of the time.
   Precondition vs. postcondition


Counter loops -- ``for``
------------------------


``break`` and ``continue``
--------------------------

.. todo:: Use sparingly!
