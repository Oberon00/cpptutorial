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
from sphinx.errors import SphinxError
from docutils.parsers.rst import Directive, directives
from docutils.transforms import Transform
from sphinx.util.nodes import nested_parse_with_titles
from fnmatch import fnmatch # glob style matching

DEFAULT_SOLVED_PREFIX = "Solved task: "
UNSOLVED_MARKER = "No solution provided."


class CppTutError(SphinxError):
    pass

def setup(app):
    app.add_config_value(
            'tutorial_solved_title_prefix', DEFAULT_SOLVED_PREFIX, True)
    app.add_config_value('tutorial_solved_use_title_prefix', True, True)
    app.add_node(task,
                 html=(visit_task_node, depart_task_node),
                 latex=(visit_task_node, depart_task_node),
                 text=(visit_task_node, depart_task_node))
    app.add_node(tasksolutionfor)

    app.add_directive('task', TaskDirective)
    app.add_directive('tasksolutions', TaskSolutionsDirective)
    app.add_directive('tasksolution', TaskSolutionForDirective)

    app.connect('env-purge-doc', purge_tasks)
    app.connect('doctree-resolved', mark_unsolved_tasks)
    app.add_transform(TaskSolutionForTransform)

def visit_task_node(self, node):
    self.visit_admonition(node)

def depart_task_node(self, node):
    self.depart_admonition(node)

class task(nodes.Admonition, nodes.Element):
    pass

class tasksolutionfor(nodes.Special, nodes.Element):
    pass

class TaskSolutionsDirective(Directive):
    required_arguments = 1

    # TODO: Deduplicate!!!
    def run(self):
        env = self.state.document.settings.env
        #print("docname:", env.docname)
        if not hasattr(env, 'task_solutions'):
            raise self.warning("No tasks/solutions to list exist at all.")

        builder = env.app.builder
        pattern = self.arguments[0]
        if pattern == '.':
            pattern = env.docname

        content = []
        for ts in env.task_solutions:
            if not ts['solution']:
                continue # Skip tasks without solutions
            if not fnmatch(ts['docname'], pattern):
                continue
            sref = ts['solref'] # Reference from original task to this solution
            if 'task-solution-unresolved' in sref:
                sref['refdoc'] = env.docname
                sdocuri = builder.get_relative_uri(ts['docname'], env.docname)
                sref['refuri'] = sdocuri + "#" + ts['soltarget']['ids'][0]
                del sref['task-solution-unresolved']
            else:
                env.warn(
                    env.docname,
                    "Solution for '{}' already written to document '{}'".format(
                        ts['target_id'], sref['refdoc']),
                    self.lineno)
            docuri = builder.get_relative_uri(env.docname, ts['docname'])
            ts['backref']['refuri'] = docuri + "#" + ts['target_id']
            content.append(ts['solution'].deepcopy())
            env.note_dependency(ts['docname'])
        if not content:
            raise self.warning(
                "No tasks/solutions matched the pattern '{}'.".format(pattern))
        return content

def parse_title(state, text, lineno=None):
    titlenodes, titlemsgs = state.inline_text(
            text, lineno)
    return [nodes.title(text, '', *titlenodes)] + titlemsgs


def insert_solved_prefix(titlenode, env):
    prefix = env.app.config.tutorial_solved_title_prefix
    if prefix:
        titlenode.insert(0, nodes.Text(prefix, prefix))

class TaskSolutionForTransform(Transform):

    default_priority = 0


    def apply(self, **kwargs):
        for placeholder in self.document.traverse(tasksolutionfor):
            self._transform_solution(placeholder)

    def _transform_solution(self, placeholder):
        env = self.document.settings.env

        sectionnode = placeholder.parent
        if not isinstance(sectionnode, nodes.section):
            env.warn(
                placeholder.source,
                "tasksolutionfor directive must occur directly in section.",
                placeholder.line)
            placeholder.replace_self([])
            return

        titlenode = sectionnode.next_node(nodes.title)
        assert titlenode, "Section '{}' has no title.".format(section.names)


        if not hasattr(env, 'task_solutions'):
            env.warn(
                    placeholder.source,
                    "No tasks/solutions to solve exist at all.",
                    placeholder.line)
            placeholder.replace_self([])
            return

        builder = env.app.builder

        solved_task_id = placeholder['taskid']
        if solved_task_id:
            update_title = False
        else:
            solved_task_id = sectionnode['ids'][0]
            update_title = True
        solved_task_id = nodes.make_id("task-" + solved_task_id)

        ts = next((
                ts for ts in env.task_solutions
                if ts['target_id'] == solved_task_id),
            None)
        if not ts:
            env.warn(
                placeholder.source,
                "Task ID '{}' not found.".format(solved_task_id),
                placeholder.line)
            placeholder.replace_self([])
            return

        if ts['solution']:
            env.warn(
                    env.docname,
                    "Task {} has an attached solution.".format(
                        ts['target_id']),
                    self.lineno)

        if update_title:
            titlenodes = [n.deepcopy() for n in ts['titlenodes']]
            if placeholder['useprefix']:
                insert_solved_prefix(titlenodes[0], env)
            titlenode.replace_self(titlenodes)

        sref = ts['solref'] # Reference from original task to this solution
        if 'task-solution-unresolved' in sref:
            sref['refdoc'] = env.docname
            sdocuri = builder.get_relative_uri(ts['docname'], env.docname)
            sref['refuri'] = sdocuri + "#" + ts['soltarget']['ids'][0]
            del sref['task-solution-unresolved']
        else:
            env.warn(
                env.docname,
                "Solution for '{}' already written to document '{}'".format(
                    ts['target_id'], sref['refdoc']),
                self.lineno)
        docuri = builder.get_relative_uri(env.docname, ts['docname'])
        ts['backref']['refuri'] = docuri + "#" + ts['target_id']
        env.note_dependency(ts['docname'])
        placeholder.replace_self(
                [ts['repeatedtask'].deepcopy(), ts['soltarget'].deepcopy()])

class TaskSolutionForDirective(Directive):
    optional_arguments = 1
    final_argument_whitespace = True # But please don't use newlines
    option_spec = dict(invprefix=directives.flag)

    def run(self):
        taskid = self.arguments[0] if self.arguments else None
        config = self.state.document.settings.env.app.config
        useprefix_def = config.tutorial_solved_use_title_prefix
        useprefix = ('invprefix' in self.options) != prefix_def and not taskid
        return [tasksolutionfor(taskid=taskid, useprefix=useprefix)]


class TaskDirective(Directive):

    has_content = True
    optional_arguments = 1
    final_argument_whitespace = True
    option_spec = {'name': directives.unchanged}

    def _make_admonition(self, title="Task"):
        ad = make_admonition(task, self.name, [title], self.options,
                             self.content, self.lineno, self.content_offset,
                             self.block_text, self.state, self.state_machine)
        self.add_name(ad[0])
        #print(title, ad)
        return ad

    def _make_ref(self, text, extraclass=None):
        env = self.state.document.settings.env
        refpar = nodes.paragraph(classes=["taskref"])
        if extraclass:
            refpar['classes'].append(extraclass)
        refpar.append(nodes.Text('(', '('))
        ref = nodes.reference()
        ref.append(nodes.Text(text, text))
        refpar.append(ref)
        refpar.append(nodes.Text(')', ')'))
        return refpar, ref

    def run(self):
        self.assert_has_content()

        self.options['class'] = ["admonition-task"]
        if self.arguments:
            title = self.arguments[0]
            tasktitle = 'Task: ' + title
            env = self.state.document.settings.env
            if 'name' not in self.options or not self.options['name']:
                self.options['name'] = nodes.fully_normalize_name(tasktitle)
            name = self.options['name']

            solution_text = None
            try:
                for idx, line in enumerate(self.content):
                    if (not line
                        and self.content[idx + 1].startswith('SOLUTION:')
                    ):
                        useprefix = (
                            ("invprefix" in self.content[idx + 1]) !=
                            env.app.config.tutorial_solved_use_title_prefix)
                        solution_text = self.content[idx + 2:]
                        del self.content[idx:]
            except (ValueError, IndexError):
                pass


            ad = self._make_admonition('Task: ' + title)
            adnode = ad[0]

            if not hasattr(env, 'task_solutions'):
                env.task_solutions = []

            repeatedtask = self._make_admonition("Original task")[0]
            backrefpar, backref = self._make_ref(
                    "Original task's location", "taskorigref")
            backref['refdocname'] = env.docname
            repeatedtask.insert(1, backrefpar) # Insert after title
            repeatedtask['names'][:] = []
            repeatedtask['ids'][:] = []

            soltarget = nodes.target()
            self.options['name'] = name + " solution"
            self.add_name(soltarget)

            titlenodes = parse_title(self.state, title, self.lineno)

            if solution_text:
                self.options['name'] = name + " solved"
                solution = nodes.section()
                self.add_name(solution)
                if useprefix:
                    insert_solved_prefix(titlenodes[0], env)
                solution += [n.deepcopy() for n in titlenodes]
                solution += repeatedtask
                solution.append(soltarget)
                nested_parse_with_titles(self.state, solution_text, solution)
            else:
                solution = None

            solrefpar, solref = self._make_ref("Solution", "tasksolref")
            solref['task-solution-unresolved'] = True

            adnode.append(solrefpar)

            env.task_solutions.append(dict(
                docname=env.docname,
                solution=solution,
                repeatedtask=repeatedtask,
                titlenodes=titlenodes,
                target_id=adnode['ids'][0],
                soltarget=soltarget,
                solref=solref,
                backref=backref))
        else:
            ad = self._make_admonition()
        return ad

def purge_tasks(app, env, docname):
    if not hasattr(env, 'task_solutions'):
        return
    env.task_solutions = [ # Remove task solutions with this docname
            ts for ts in env.task_solutions if ts['docname'] != docname]

def mark_unsolved_tasks(app, doctree, fromdocname):
    for sref in doctree.traverse():
        if 'task-solution-unresolved' in sref:
            app.warn("unsolved task: {}".format(sref.parent.parent['names']),
                    fromdocname)
            sref.replace_self(nodes.Text(UNSOLVED_MARKER, UNSOLVED_MARKER))

