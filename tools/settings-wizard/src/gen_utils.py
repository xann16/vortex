import os
from typing import Any

def create_file(path: str, content: list[str]):
    dir_path = os.path.dirname(path)
    os.makedirs(dir_path, exist_ok=True)

    already_exists: bool = os.path.exists(path)

    if already_exists:
        with open(path, mode='r', encoding='utf-8') as fp:
            old_content = fp.readlines()
        if old_content == content:
            # TODO : Add verbosity switch
            #print(f'         {path} - no changes detected. Skipped.')
            return

    with open(path, mode='w', encoding='utf-8') as fp:
        fp.writelines(content)

    print(('UPDATED' if already_exists else 'CREATED') + ': ' + path)


def to_pascal_case(snake_name: str):
    return ''.join(t.title() for t in snake_name.lower().split('_'))
