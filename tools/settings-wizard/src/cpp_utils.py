TAB_SIZE = 4

def _get_line(i: int) -> str:
    return ' ' * (i * TAB_SIZE)

def add_include(ls: list[str], i: int, header: str, is_quoted: bool = True) -> None:
    l = _get_line(i) + '#include '
    l += f'"{header}"' if is_quoted else f'<{header}>'
    l += '\n'
    ls.append(l)

def add_blank(ls: list[str], count: int = 1):
    for _ in range(count):
        ls.append('\n')

def add_block_comment(ls: list[str], i: int, *args) -> None:
    for arg in args:
        ls.append((_get_line(i) + '// ' + str(arg)).rstrip() + '\n')
