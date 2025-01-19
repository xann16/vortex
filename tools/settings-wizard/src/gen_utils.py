import os
from typing import Any

def create_file(path: str, content: list[str]):
    dir_path = os.path.dirname(path)
    os.makedirs(dir_path, exist_ok=True)
    with open(path, mode='w', encoding='utf-8') as fp:
        fp.writelines(content)

def to_pascal_case(snake_name: str):
    tokens = snake_name.lower().split('_')
    return ''.join(t.title() for t in tokens)
