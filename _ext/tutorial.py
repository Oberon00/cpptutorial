# encoding: utf-8
"""
File: tutorial.py
Author: Christian Neumüller
Email: cn00@gmx.at
Github: Oberon00
Description: Tutorial extension for sphinx-doc.
"""

from docutils import nodes
from sphinx.util.compat import make_admonition
from docutils.parsers.rst import Directive

def setup(app):
    app.add_node(task,
                 html=(visit_task_node, depart_task_node),
                 latex=(visit_task_node, depart_task_node),
                 text=(visit_task_node, depart_task_node))
    app.add_directive('task', TaskDirective)

def visit_task_node(self, node):
    self.visit_admonition(node)

def depart_task_node(self, node):
    self.depart_admonition(node)

class task(nodes.Admonition, nodes.Element):
    pass

class TaskDirective(Directive):

    has_content = True

    def run(self):
        return make_admonition(task, self.name, ['Task'], self.options,
                               self.content, self.lineno, self.content_offset,
                               self.block_text, self.state, self.state_machine)
