from cpp_utils import get_class_name, get_namespace, begin_namespace, end_namespace, add_blank, add_line, add_block_comment, add_method_declaration, add_method_definition, begin_test_case, end_test_case, add_require
from typing import Any

FP_CMP_EPS = 0.00001
BASE_TYPES = {
    'boolean': ('bool',             'true'),
    'i8':      ('i8',               '-4'),
    'i16':     ('i16',              '-3'),
    'i32':     ('i32',              '-2l'),
    'i64':     ('i64',              '-1ll'),
    'u8':      ('u8',               '1u'),
    'u16':     ('u16',              '2u'),
    'u32':     ('u32',              '3ul'),
    'u64':     ('u64',              '4ull'),
    'f32':     ('f32',              '0.1f'),
    'f64':     ('f64',              '0.2'),
    'real':    ('real',             '0.3'),
    'string':  ('std::string_view', '"stest"'),
    'path':    ('std::string_view', '"ptest"'),
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
        return BASE_TYPES[property_type][0]
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

def _get_default_value(name: str, p: dict[str, Any]) -> str:
    property_type : str = p['type']
    default_value : str = p['default'] if 'default' in p else None

    if isinstance(default_value, str) and default_value.startswith('@'):
        return f'{default_value.lstrip('@')}()'

    if property_type == 'module':
        return '/* TODO: settings dynamic class constructor from nullptr */ nullptr'
    elif property_type == 'enum':
        return '/* TODO: enum type first value or predefined - extra processing ??? */ 0'
    elif property_type in BASE_TYPES:
        default_str : str = f'"{default_value}"' if (property_type == 'string' or property_type == 'path') else str(default_value)

        return default_str if default_value is not None else (BASE_TYPES[property_type][0] + '{}')
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')


### DEFAULT VALUE

def _add_default_value_declaration(ls: list[str], i: int, name: str, p: dict[str, Any]) -> int:
    if p['type'] == 'settings':
        return i
    return_type : str = _get_return_type(p)
    default_value : str = _get_default_value(name, p)
    body : list[(int, str)] = [(0, f'return {default_value};' )]
    preq : str = '' if ('default' in p and isinstance(p['default'], str) and p['default'].startswith('@')) else 'constexpr'
    return add_method_declaration(ls, i, f'default_{name}', return_type, [], body=body, is_const=True, is_nodiscard=True, is_noexcept=True, is_definition=True, pre_qualifiers=preq)

### GETTERS

def _add_getter_declaration(ls: list[str], i: int, name: str, p: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p)
    return add_method_declaration(ls, i, name, return_type, [], is_const=True, is_nodiscard=True)

def _add_getter_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p)
    property_type : str = p['type']

    body : list[(int, str)] = []

    if property_type == 'settings':
        body.append((0, f'if ( m_data_p == nullptr ) throw std::runtime_error( "{class_name}: cannot get default value of unset property with settings type." );'))
    else:
        body.append((0, f'if ( m_data_p == nullptr ) return default_{name}();'))

    # TEMP IF
    if property_type in BASE_TYPES:
        body.append((0, f'auto it = m_data_p->find( "{name}" );'))
        body.append((0, f'if ( it == m_data_p->end() || it->is_null() ) return default_{name}();'))

    if property_type == 'module':
        body.append((0, 'return nullptr;'))
    elif property_type == 'settings':
        body.append((0, 'return nullptr;'))
    elif property_type == 'enum':
        body.append((0, 'return 0;'))
    elif property_type in BASE_TYPES:
        if property_type == 'string' or property_type == 'path':
            body.append((0, 'return std::string_view{' + f' it->template get_ref<std::string const&>() ' + '};'))
        else:
            body.append((0, f'return it->template get<{return_type}>();'))
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

    return add_method_definition(ls, i, name, return_type, class_name, [], body, is_const=True, is_nodiscard=True)

def _add_getter_test(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], namespace: list[str]) -> int:
    return_type : str = _get_return_type(p)
    property_type : str = p['type']

    i = begin_test_case(ls, i, f'{class_name} - property: \\\"{name}\\\" - getter', 'settings')

    if property_type in BASE_TYPES:
        i = add_line(ls, i, 'auto obj = nlohmann::json{ { "' + name + f'", {BASE_TYPES[property_type][1]}' + ' } };' )
        i = add_line(ls, i, 'auto obj_p = &obj;')
        i = add_line(ls, i, 'auto s = ' + '::'.join(namespace) + '::' + class_name + '{ obj_p };')
    i = add_line(ls, i, 'auto s_null = ' + '::'.join(namespace) + '::' + class_name + '{ nullptr };')
    add_blank(ls)

    if property_type in BASE_TYPES:
        i = add_line(ls, i, f'auto value = s.{name}();')
    if property_type == 'settings':
        add_blank(ls)
        i = add_require(ls, i, f's_null.{name}(), std::runtime_error', suffix='throws_as')
    else:
        i = add_line(ls, i, f'auto default_value = s_null.{name}();')
        add_blank(ls)

    if property_type == 'module':
        i = add_require(ls, i, 'default_value == nullptr')
    elif property_type == 'settings':
        pass
    elif property_type == 'enum':
        i = add_require(ls, i, 'default_value == 0')
    elif property_type in BASE_TYPES:
        is_fp : bool = property_type in ['f32', 'f64', 'real']
        val_str : str = 'value' if property_type in ['boolean', 'string', 'path'] else f'static_cast< vortex::{BASE_TYPES[property_type][0]} >( value )'
        def_val_str : str = 'default_value' if property_type in ['boolean', 'string', 'path'] else f'static_cast< vortex::{BASE_TYPES[property_type][0]} >( default_value )'
        default_value : str = _get_default_value(name, p)
        def_prefix = 's_null.' if ('default' in p and isinstance(p['default'], str) and p['default'].startswith('@')) else ('' if ('default' in p or property_type in ['string', 'path', 'boolean']) else 'vortex::')

        if is_fp:
            i = add_require(ls, i, f'{val_str}, Catch::Matchers::WithinAbs( {BASE_TYPES[property_type][1]}, {FP_CMP_EPS} )', suffix='that')
            i = add_require(ls, i, f'{def_val_str}, Catch::Matchers::WithinAbs( {def_prefix}{default_value}, {FP_CMP_EPS} )', suffix='that')
        else:
            i = add_require(ls, i, f'{val_str} == {BASE_TYPES[property_type][1]}')
            i = add_require(ls, i, f'{def_val_str} == {def_prefix}{default_value}')
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

    i = end_test_case(ls, i)

    return i


def add_property_public_declarations(ls: list[str], i: int, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    for name, prop in data.items():
        if not name.startswith('__'):
            i = add_block_comment(ls, i, f'"{name}" property')
            i = _add_getter_declaration(ls, i, name, prop)
            i = _add_default_value_declaration(ls, i, name, prop)
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
