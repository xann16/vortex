from gen_utils import to_pascal_case
from typing import Any

TAB_SIZE = 4

def get_class_name(data: dict[str, Any], suffix: str = '') -> str:
    snake_name = data['__metadata__']['module'] + (f'_{suffix}' if suffix else '')
    return to_pascal_case(snake_name)

def get_namespace(data: dict[str, Any]) -> list[str]:
    package_name : str = data['__metadata__']['package'].lstrip('*')
    namespace_path : list[str] = data['__metadata__']['namespace']
    return ['vortex'] + [package_name] + namespace_path

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

def begin_class(ls: list[str], i: int, class_name: str, base_classes: list[str] | None = None) -> None:
    bases : str = (' : public ' + ', '.join(base_classes)) if base_classes else ''
    i = add_line(ls, i, f'class {class_name}' + bases)
    return open_brace(ls, i)

def end_class(ls: list[str], i: int, class_name: str) -> None:
    comment = f' // end of class {class_name}' if class_name else ''
    return close_brace(ls, i, suffix=';' + comment)

def add_access_qualifier(ls: list[str], i: int, qualifier: str) -> int:
    return add_line(ls, i - 1, f'{qualifier}:') + 1

def _add_ctor_body(ls: list[str], i: int, signature: str, args: list[(str, str, str)], body: list[(int, str)] | None) -> int:
    i = add_line(ls, i, signature)
    for j, (_, arg_name) in enumerate(args):
        i = add_line(ls, i, (':' if j == 0 else ',') + (' ' * (TAB_SIZE - 1)) + 'm_' + arg_name + '( ' + arg_name + ' )')
    if not body:
        return add_line(ls, i, '{}')

    i = open_brace(ls, i)
    for indent_offset, line in body:
        add_line(ls, i + indent_offset, line)
    return close_brace(ls, i)

def add_ctor_declaration(ls: list[str], i: int, class_name: str, args: list[(str, str)], body: list[(int, str)] | None = None, is_explicit: bool = False, is_definition: bool = False, is_noexcept: bool = False) -> int:
    args_list : list[str] = [f'{data_type} {name}' for data_type, name in args]
    signature : str = ('explicit ' if is_explicit else '') + class_name + '( ' + ', '.join(args_list) + ' )' + (' noexcept' if is_noexcept else '')
    if not is_definition:
        return add_line(ls, i, signature + ';')
    return _add_ctor_body(ls, i, signature, args, body)

def add_ctor_definition(ls: list[str], i: int, class_name: str, args: list[(str, str)], body: list[(int, str)], is_noexcept: bool = False) -> int:
    args_list : list[str] = [f'{data_type} {name}' for data_type, name in args]
    signature : str = class_name + '::' + class_name + '( ' + ', '.join(args_list) + ' )' + (' noexcept' if is_noexcept else '')
    return _add_ctor_body(ls, i, signature, args, body)

def add_copy_and_move_ctor_deletes(ls: list[str], i: int, class_name: str) -> None:
    i = add_line(ls, i, f'{class_name}( {class_name} const& ) = delete;')
    i = add_line(ls, i, f'{class_name}& operator=( {class_name} const& ) = delete;')
    i = add_line(ls, i, f'{class_name}( {class_name} && ) = delete;')
    i = add_line(ls, i, f'{class_name}& operator=( {class_name} && ) = delete;')
    return i

def _add_dtor_body(ls: list[str], i: int, signature: str, body: list[(int, str)] | None) -> int:
    i = add_line(ls, i, signature)
    if not body:
        print(f'WARNING: Non-defaulted destructor with empty body: {signature}.')
        return add_line(ls, i, '{}')

    i = open_brace(ls, i)
    for indent_offset, line in body:
        add_line(ls, i + indent_offset, line)
    return close_brace(ls, i)

def add_dtor_declaration(ls: list[str], i: int, class_name: str, is_noexcept: bool = False, is_default: bool = False, is_definition: bool = False, body: list[(int, str)] | None = None) -> int:
    if is_default and is_definition:
        raise RuntimeError('Invalid arguments')
    signature : str = f'~{class_name}()' + (' noexcept' if is_noexcept else '') + (' = default' if is_default else '')
    if not is_definition:
        return add_line(ls, i, signature + ';')
    return _add_dtor_body(ls, i, signature, body)

def add_dtor_definition(ls: list[str], i: int, class_name: str, is_noexcept: bool = False, body: list[(int, str)] | None = int) -> int:
    signature : str = f'~{class_name}::{class_name}()' + (' noexcept' if is_noexcept else '')
    return _add_dtor_body(ls, i, signature, body)

def add_data_field(ls: list[str], i: int, data_type: str, name: str, default_value: str) -> int:
    return add_line(ls, i, f'{data_type} m_{name}' + (f' = {default_value}' if default_value else '') + ';')

def _add_method_body(ls: list[str], i: int, signature: str, body: list[(int, str)] | None) -> int:
    i = add_line(ls, i, signature)
    if not body:
        return add_line(ls, i, '{}')

    i = open_brace(ls, i)
    for indent_offset, line in body:
        add_line(ls, i + indent_offset, line)
    return close_brace(ls, i)

def add_method_declaration(ls: list[str], i: int, method_name: str, return_type: str, args: list[(str, str)], body: list[(int, str)] | None = None, is_definition: bool = False, is_const: bool = False, is_noexcept: bool = False, is_nodiscard: bool = False) -> int:
    args_list : list[str] = [f'{data_type} {name}' for data_type, name in args]
    args : str = ', '.join(args_list)
    signature : str = ('[[nodiscard]] ' if is_nodiscard else '') + f'{return_type} {method_name}(' + (f' {args} ' if args else '') + ')' + (' const' if is_const else '') + (' noexcept' if is_noexcept else '')
    if not is_definition:
        return add_line(ls, i, signature + ';')
    return _add_method_body(ls, i, signature, body)

def add_method_definition(ls: list[str], i: int, method_name: str, return_type: str, class_name: str, args: list[(str, str)], body: list[(int, str)], is_const: bool = False, is_noexcept: bool = False, is_nodiscard: bool = False) -> int:
    args_list : list[str] = [f'{data_type} {name}' for data_type, name in args]
    args : str = ', '.join(args_list)
    signature : str = ('[[nodiscard]] ' if is_nodiscard else '') + f'{return_type} {class_name}::{method_name}(' + (f' {args} ' if args else '') + ')' + (' const' if is_const else '') + (' noexcept' if is_noexcept else '')
    return _add_method_body(ls, i, signature, body)


# TESTING

def begin_test_case(ls: list[str], i: int, case_name: str, case_tags: str = '') -> None:
    i = add_line(ls, i, f'TEST_CASE( "{case_name}", "[{case_tags}]" )')
    return open_brace(ls, i)

def end_test_case(ls: list[str], i: int) -> None:
    return close_brace(ls, i)

def add_require(ls: list[str], i: int, condition: str, suffix: str = '') -> None:
    if suffix:
        suffix = '_' + suffix.upper()
    return add_line(ls, i, f'REQUIRE{suffix}( {condition} );')
