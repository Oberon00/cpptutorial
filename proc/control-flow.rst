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

.. todo::

   * indentation
   * block-statements
   * else
