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
