from cpp_utils import get_class_name, get_namespace, add_blank, add_line, add_block_comment, add_method_declaration, add_method_definition, begin_test_case, end_test_case, add_require
from typing import Any

FP_CMP_EPS = 0.00001
BASE_TYPES = {
    'boolean': ('bool',        True,  'true'),
    'i8':      ('i8',          True,  '-4'),
    'i16':     ('i16',         True,  '-3'),
    'i32':     ('i32',         True,  '-2l'),
    'i64':     ('i64',         True,  '-1ll'),
    'u8':      ('u8',          True,  '1u'),
    'u16':     ('u16',         True,  '2u'),
    'u32':     ('u32',         True,  '3ul'),
    'u64':     ('u64',         True,  '4ull'),
    'f32':     ('f32',         True,  '0.1f'),
    'f64':     ('f64',         True,  '0.2'),
    'real':    ('real',        True,  '0.3'),
    'string':  ('std::string', False, '"stest"'),
    'path':    ('std::string', False, '"ptest"'),
}

def _get_return_type(p: dict[str, Any]) -> str:
    property_type : str = p['type']
    if property_type == 'module':
        return '/* TODO: settings dynamic class */ void *'
    elif property_type == 'settings':
        return '/* TODO: settings opaque interface */ void *'
    elif property_type == 'enum':
        return '/* TODO: enum type */ i32'
    elif property_type in BASE_TYPES:
        (cpp_type, return_by_value, _) = BASE_TYPES[property_type]
        return cpp_type + ('' if return_by_value else ' const&')
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')


def _add_getter_declaration(ls: list[str], i: int, name: str, p: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p)
    return add_method_declaration(ls, i, name, return_type, [], is_const=True, is_nodiscard=True)

def _add_getter_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p)
    property_type : str = p['type']

    body : list[(int, str)] = []
    if property_type == 'module':
        body.append((0, 'return nullptr;'))
    elif property_type == 'settings':
        body.append((0, 'return nullptr;'))
    elif property_type == 'enum':
        body.append((0, 'return 0;'))
    elif property_type in BASE_TYPES:
        json_getter_name : str = 'get' if BASE_TYPES[property_type][1] else 'get_ref'
        body.append((0, f'// TODO : Add handling of default values if property is not set.'))
        body.append((0, f'return m_data_p->at( "{name}" ).template {json_getter_name}<{return_type}>();'))
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

    return add_method_definition(ls, i, name, return_type, class_name, [], body, is_const=True, is_nodiscard=True)

def _add_getter_test(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], namespace: list[str]) -> int:
    return_type : str = _get_return_type(p)
    property_type : str = p['type']

    i = begin_test_case(ls, i, f'{class_name} - property: \\\"{name}\\\" - getter', 'settings')

    if property_type in BASE_TYPES:
        i = add_line(ls, i, 'auto obj = nlohmann::json{ { "' + name + f'", {BASE_TYPES[property_type][2]}' + ' } };' )
        i = add_line(ls, i, 'auto obj_p = &obj;')
    else:
        i = add_line(ls, i, 'nlohmann::json * obj_p = nullptr;')
    i = add_line(ls, i, 'auto s = ' + '::'.join(namespace) + '::' + class_name + '{ obj_p };')
    add_blank(ls)

    i = add_line(ls, i, f'auto value = s.{name}();')
    add_blank(ls)

    if property_type == 'module':
        i = add_require(ls, i, 'value == nullptr')
    elif property_type == 'settings':
        i = add_require(ls, i, 'value == nullptr')
    elif property_type == 'enum':
        i = add_require(ls, i, 'value == 0')
    elif property_type in BASE_TYPES:
        is_fp : bool = property_type in ['f32', 'f64', 'real']
        val_str : str = 'value' if property_type in ['boolean', 'string', 'path'] else f'static_cast< vortex::{BASE_TYPES[property_type][0]} >( value )'
        if is_fp:
            i = add_require(ls, i, f'{val_str}, Catch::Matchers::WithinAbs( {BASE_TYPES[property_type][2]}, {FP_CMP_EPS} )', suffix='that')
        else:
            i = add_require(ls, i, f'{val_str} == {BASE_TYPES[property_type][2]}')
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

    i = end_test_case(ls, i)

    return i


def add_property_public_declarations(ls: list[str], i: int, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    for name, prop in data.items():
        if not name.startswith('__'):
            i = add_block_comment(ls, i, f'"{name}" property')
            i = _add_getter_declaration(ls, i, name, prop)
            add_blank(ls)
    return i


def add_property_private_declarations(ls: list[str], i: int, props: dict[str, Any], ctx: dict[str, Any]) -> int:
#    for name, prop in data.items():
#        if not name.startswith('__'):
#            pass
#            #i = _add_raw_getter(ls, i, name, prop, ctx)
    return i

def add_property_definitions(ls: list[str], i: int, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    class_name : str = get_class_name(data)

    for name, prop in data.items():
        if not name.startswith('__'):
            i = add_block_comment(ls, i, f'"{name}" property')
            add_blank(ls)
            i = _add_getter_definition(ls, i, class_name, name, prop)
            add_blank(ls)
    return i

def add_property_unit_tests(ls: list[str], i: int, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    class_name : str = get_class_name(data)
    namespace : str = get_namespace(data)

    for name, prop in data.items():
        if not name.startswith('__'):
            i = add_block_comment(ls, i, f'"{name}" property')
            add_blank(ls)
            i = _add_getter_test(ls, i, class_name, name, prop, namespace)
            add_blank(ls)
    return i
