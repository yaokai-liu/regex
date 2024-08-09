import os.path
from pathlib import Path
import json
from string import Template as Tp
from DATA import *

__DIR__ = Path(os.path.dirname(__file__))
PROJECT_ROOT = __DIR__ / ".."
GRAMMAR_DIR = PROJECT_ROOT / "grammar"


def get_json_from(filename: str):
    global GRAMMAR_DIR
    with open(GRAMMAR_DIR / "json" / filename, 'r') as fp:
        return json.load(fp)


__tokens = get_json_from("tokens.json")
terminals = sorted(['TERMINATOR'] + __tokens['terminal'])
targets = __tokens['non-terminal']
targets.remove("~")
targets = sorted(targets)
tokens = sorted(terminals + targets)
if os.path.isfile(GRAMMAR_DIR / "json" / "machine-compact.json"):
    table = get_json_from("machine-compact.json")
else:
    table = get_json_from("machine.json")
for val in table.values():
    if '$' in val.keys():
        val['TERMINATOR'] = val.pop('$')
rules = get_json_from("rules.json")


class Rule:
    def __init__(self, name):
        self.name = name
        target, items = rules[name].split('->')
        self.target = target.strip()
        if self.target == '~':
            self.target = 'Regexp'
        items = items.strip()
        if len(items) > 0:
            self.items = items.split(' ')
        else:
            self.items = []


def get_temp_from(filename: str):
    with open(GRAMMAR_DIR / "templates" / filename, 'r') as fp:
        return fp.read()


def gen_token_enum():
    global tokens
    template = Tp(get_temp_from("tokens.h.tpl"))
    enums = ',\n  '.join([f"enum_{t} = {i + 1}" for i, t in enumerate(tokens)])
    enums_entry = template.substitute(enums=enums)
    with open(GRAMMAR_DIR / "tokens.gen.h", 'w') as fp:
        fp.write(enums_entry)


def gen_token_name():
    template = Tp(get_temp_from("tokens.c.tpl"))
    names = ',\n  '.join([f'[enum_{t}] = string_t("{t}")' for t in tokens])
    names_entry = template.substitute(names=names)
    with open(GRAMMAR_DIR / "tokens.gen.c", 'w') as fp:
        fp.write(names_entry)


def gen_terminals():
    global terminals
    template = Tp(get_temp_from("terminal.c.tpl"))
    body = ',\n  '.join([f'enum_{t}' for t in terminals if TERMINALS[t] != 0])
    string = ''.join([f'{TERMINALS[t]}' for t in terminals if TERMINALS[t] != 0])
    terminals_entry = template.substitute(string=string, terminals=body)
    with open(GRAMMAR_DIR / "terminal.gen.c", 'w') as fp:
        fp.write(terminals_entry)


status, reflect = dict(), dict()
for s, p in enumerate(table.keys()):
    status[s], reflect[p] = table[p], s


def state_to_enum(p):
    _state = '_'.join(p.strip('()').split(', '))
    _state = ('__' + _state) if _state else '__EMPTY__'
    return _state


class Action:
    def __init__(self, p):
        if not p.startswith('('):
            rule = Rule(p)
            self.action = "reduce"
            self.type = f"enum_{rule.target}"
            self.count = len(rule.items)
            self.offset = f"{p}"
        else:
            self.action = "stack"
            self.type = 0
            self.count = 0
            self.offset = f"{state_to_enum(p)}"

    def __eq__(self, other):
        return self.action == other.action \
            and self.type == other.type \
            and self.count == other.count \
            and self.offset == other.offset

    def toString(self):
        return ("{"
                f".action = {self.action},"
                f".type = {self.type},"
                f".count = {self.count},"
                f".offset = {self.offset},"
                "}")


def gen_reduces():
    global rules
    rule_names = rules.keys()
    args = "(void * argv[], const Allocator * allocator);"
    enum_reduces = sorted(f"{r} = {i}" for i, r in enumerate(rule_names))
    reduces = sorted(f"{r.split('_')[0]} * p_{r}" + args
                     if r != '__EXTEND_RULE__'
                     else f"Regexp * p_{r}" + args
                     for r in rule_names)
    assign_reduces = sorted([f"[{r}] = (fn_product *) p_{r}" for r in rule_names])
    template = Tp(get_temp_from("reduce.h.tpl"))
    content = template.substitute(
        enum_reduces=',\n  '.join(enum_reduces),
        reduces='\n'.join(reduces)
    )
    with open(GRAMMAR_DIR / "reduce.gen.h", 'w') as fp:
        fp.write(content)
    content = Tp(get_temp_from("target.c.tpl")).substitute(
        assign_reduces=',\n  '.join(assign_reduces)
    )
    with open(GRAMMAR_DIR / "target.gen.c", 'w') as fp:
        fp.write(content)


def gen_action_table():
    global table, terminals, targets
    state_enum, states, actions, jumps, units = [], [], [], [], []
    for p, q in table.items():
        _state = state_to_enum(p)
        state_enum.append(f'{_state} = {len(state_enum)}')
        _tokens = q.keys()
        _terminals = sorted(_tokens & set(terminals))
        _targets = sorted(_tokens & set(targets))
        state = {
            "ndx_base": len(actions),
            "goto_base": len(jumps),
            "token_base": len(units),
            "n_tokens": len(_tokens),
        }
        items, ndx, addend = dict(), [], []
        for t in _terminals:
            act = Action(q[t])
            if act not in addend:
                addend.append(act)
            items[t] = addend.index(act)
        actions += [a.toString() for a in addend]
        for i, t in enumerate(_targets):
            jumps.append(f"{state_to_enum(q[t])}")
            items[t] = i
        for i, t in enumerate(sorted(_tokens)):
            ndx.append(str(i))
            units.append(f"{{.type = enum_{t}, .offset = {items[t]}}}")
        string = ', '.join([f".{k} = {v}" for k, v in state.items()])
        states.append(f"[{_state}] = {{{string}}}")
    template = Tp(get_temp_from("action-table.c.tpl"))
    content = template.substitute(
        state_enum=',\n  '.join(state_enum),
        actions=",\n  ".join(actions),
        jumps=", ".join(jumps),
        units=", \n  ".join(units),
        states=",\n  ".join(states)
    )
    with open(GRAMMAR_DIR / "action-table.gen.c", 'w') as fp:
        fp.write(content)


if __name__ == '__main__':
    gen_token_enum()
    gen_token_name()
    gen_terminals()
    gen_reduces()
    gen_action_table()
