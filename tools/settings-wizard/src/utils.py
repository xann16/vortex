import os
import tomllib as toml
from typing import Any


def load_def(path: str) -> dict[str, Any]:
    with open(path, mode='rb') as fp:
        data = toml.load(fp)

    if '__metadata__' not in data:
        print(f"WARNING: '{path}' does not contain '__metadata__' section. Skipped.")
        return

    if 'module' not in data['__metadata__']:
        print(f"WARNING: '{path}' does not contain 'module' name in '__metadata__' section. Skipped")
        return

    if 'package' not in data['__metadata__']:
        print(f"WARNING: '{path}' does not contain 'package' name in '__metadata__' section. Skipped")
        return

    if 'namespace' not in data['__metadata__']:
        data['__metadata__']['namespace'] = []

    return data


def load_defs(root_path: str) -> dict[str, dict[str, Any]]:
    result : dict[str, dict[str, Any]] = {}

    with os.scandir(root_path if root_path else '.') as def_dir:
        for entry in def_dir:
            if entry.is_file() and entry.name.endswith('.toml'):
                data = load_def(entry.path)
                key = entry.name.rstrip('.toml')
                result[key] = data

    return result

# TEMP
_GLOBALS = {}

def get_global(key: str, fallback_value: Any = None):
    return _GLOBALS[key] if key in _GLOBALS else fallback_value


def try_parse_expr(input: Any) -> Any:
    if input is None or not isinstance(input, str) or len(input) < 3:
        return input

    trimmed_input : str = input.strip()
    init : str = trimmed_input[0:1]
    result : dict[str, Any] | None = None

    if init == '{{':
        # TODO : Full expressions - not implemented yet
        print("WARNING: Full expressions, i.e. {{ ... }} notation, not implemented yet.")
    elif init == '@{':
        if trimmed_input[-1] != '}':
            raise Exception( "Expression parse error: Missing '}' for closing of matching '@{'." )
        result = { "expr": "property" }
    elif init == '#{':
        if trimmed_input[-1] != '}':
            raise Exception( "Expression parse error: Missing '}' for closing of matching '#{'." )
        result = { "expr": "global" }
    elif init == '${':
        if trimmed_input[-1] != '}':
            raise Exception( "Expression parse error: Missing '}' for closing of matching '${'." )
        result = { "expr": "env" }

    if result is not None:
        if trimmed_input[-1] == '!':
            result['is_required'] = True
            result['target'] = trimmed_input[:-1].strip()
        else:
            tokens : list[str] = trimmed_input[2:-1].split(':', 1)
            result['target'] = tokens[0].strip()
            if len(tokens) > 1:
                result['fallback_value'] = tokens[1]
        return result

    return input
