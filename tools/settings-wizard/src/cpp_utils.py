TAB_SIZE = 4

def _get_line(i: int) -> str:
    return ' ' * (i * TAB_SIZE)

def add_line(ls: list[str], i: int, line: str) -> int:
    ls.append(_get_line(i) + line + '\n')
    return i

def open_brace(ls: list[str], i: int, do_indent=True) -> int:
    i = add_line(ls, i, '{')
    return (i + 1) if do_indent else i 

def close_brace(ls: list[str], i: int, undo_indent=True, suffix='') -> int:
    return add_line(ls, (i - 1) if undo_indent else i, '}' + suffix)

def add_include(ls: list[str], i: int, header: str, is_quoted: bool = True) -> int:
    return add_line(ls, i, '#include ' + (f'"{header}"' if is_quoted else f'<{header}>'))

def add_blank(ls: list[str], count: int = 1) -> None:
    for _ in range(count):
        add_line(ls, 0, '')

def add_block_comment(ls: list[str], i: int, *args) -> int:
    for arg in args:
        i = add_line(ls, i, '// ' + str(arg).rstrip())
    return i

def begin_namespace(ls: list[str], i: int, *args, do_indent=False) -> int:
    i = add_line(ls, i, f'namespace {"::".join(str(arg) for arg in args)}')
    return open_brace(ls, i, do_indent=do_indent)

def end_namespace(ls: list[str], i: int, *args, undo_indent=False) -> None:
    comment = f' // end of namespace {"::".join(str(arg) for arg in args)}' if args else '' 
    return close_brace(ls, i, undo_indent=undo_indent, suffix=comment)

def begin_class(ls: list[str], i: int, class_name: str) -> None:
    i = add_line(ls, i, f'class {class_name}')
    return open_brace(ls, i)

def end_class(ls: list[str], i: int, class_name: str) -> None:
    comment = f' // end of class {class_name}' if class_name else '' 
    return close_brace(ls, i, suffix=';' + comment)


# TESTING

def begin_test_case(ls: list[str], i: int, case_name: str, case_tags: str = '') -> None:
    i = add_line(ls, i, f'TEST_CASE("{case_name}", "[{case_tags}]")')
    return open_brace(ls, i)

def end_test_case(ls: list[str], i: int) -> None:
    return close_brace(ls, i)

def add_require(ls: list[str], i: int, condition: str) -> None:
    return add_line(ls, i, f'REQUIRE({condition});')
