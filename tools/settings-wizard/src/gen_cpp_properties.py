from cpp_utils import get_class_name, get_namespace, begin_namespace, end_namespace, add_blank, add_line, add_block_comment, add_method_declaration, add_method_definition, begin_test_case, end_test_case, add_require
from gen_utils import to_pascal_case
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

def _get_module_type(name: str, data: dict[str, Any], ctx: dict[str, Any]) -> str:
    from_path : str = [inc['from'] for inc in data['__includes__'] if name in inc['import']['modules']][0] if ('__includes__' in data) else ''
    import_metadata : dict[str, Any] = ctx['defs'][from_path]['__metadata__']
    return '::'.join([import_metadata['package'].lstrip('*')] + import_metadata['namespace'] + [to_pascal_case(name)])


def _get_return_type(p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> str:
    property_type : str = p['type']
    if property_type == 'module':
        return _get_module_type(p['module']['name'], data, ctx)
    elif property_type == 'settings':
        return 'core::settings::json::AnySettings'
    elif property_type == 'enum':
        return to_pascal_case(p['enum']['name'])
    elif property_type in BASE_TYPES:
        return BASE_TYPES[property_type][0]
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

def _get_arg_type(p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> str:
    property_type : str = p['type']
    if property_type == 'module':
        return _get_module_type(p['module']['name'], data, ctx)
    elif property_type == 'settings':
        return 'core::settings::json::AnySettings'
    elif property_type == 'enum':
        return to_pascal_case(p['enum']['name'])
    elif property_type in BASE_TYPES:
        return BASE_TYPES[property_type][0]
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')


def _get_default_value(name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> str:
    property_type : str = p['type']
    default_value : str | None = p['default'] if 'default' in p else None

    if isinstance(default_value, str) and default_value.startswith('@'):
        return f'{default_value.lstrip('@')}()'

    if property_type in ['module', 'settings']:
        return _get_return_type(p, data, ctx) + '{}'
    elif property_type == 'enum':
        enum_values : list[str] = p['enum']['values']
        if default_value and default_value not in enum_values:
            print(f"WARNING: Invalid default value '{default_value}' for enum '{name}'. Valid values include: {', '.join(enum_values)}. Using first value '{enum_values[0]}' instead.")
            default_value = None
        return to_pascal_case(p['enum']['name']) + '::' + to_pascal_case(enum_values[0] if not default_value else default_value)
    elif property_type in BASE_TYPES:
        default_str : str = f'"{default_value}"' if (property_type == 'string' or property_type == 'path') else str(default_value)
        return default_str if default_value is not None else (BASE_TYPES[property_type][0] + '{}')
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

def get_stringify_body(data: list[str]) -> list[(int, str)]:
    result : list[(int, str)] = []

    result.append((0, 'if ( !display_all && ( is_empty() || data()->empty() ) )'))
    result.append((0, '{'))
    result.append((1, 'os << "<empty>\\n"; '))
    result.append((1, 'return os;'))
    result.append((0, '}'))
    result.append((0, ''))

    for name, prop in data.items():
        if not name.startswith('__'):
            result.append((0, f'if ( display_all || has_{name}_set() )'))
            result.append((0, '{'))

            property_type : str = prop['type']
            line_start : str = f'os << std::setw( indent_size * indent_level ) << "" << "{name}:'
            if property_type in BASE_TYPES:
                if property_type != 'boolean':
                    result.append((1, f'{line_start} " << {name}() << \'\\n\';'))
                else:
                    result.append((1, f'{line_start} " << ( {name}() ? "true" : "false" ) << \'\\n\';'))
            elif (property_type == 'enum'):
                    result.append((1, f'{line_start} " << to_c_str( {name}() ) << \'\\n\';'))
            elif (property_type in ['settings', 'module']):
                    result.append((1, f'{line_start}\\n";'))
                    result.append((1, f'{name}().stringify( os, indent_size, indent_level + 1, display_all );'))

            result.append((0, '}'))

    result.append((0, ''))
    result.append((0, 'return os;'))

    return result


### DEFAULT VALUE

def _add_default_value_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p, data, ctx)
    default_value : str = _get_default_value(name, p, data, ctx)
    body : list[(int, str)] = [(0, f'return {default_value};' )]
    preq : str = '' if ('default' in p and isinstance(p['default'], str) and p['default'].startswith('@')) else 'constexpr'
    return add_method_declaration(ls, i, f'default_{name}', return_type, [], body=body, is_const=True, is_nodiscard=True, is_noexcept=True, is_definition=True, pre_qualifiers=preq)

### HAS_SET

def _add_has_set_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return add_method_declaration(ls, i, f'has_{name}_set', 'bool', [], is_const=True, is_nodiscard=True, is_noexcept=True)

def _add_has_set_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    body : list[(int, str)] = []

    body.append((0, f'if ( is_empty() ) return false;'))
    body.append((0, f'auto it = data()->find( "{name}" );'))
    body.append((0, f'return it != data()->end() && !it->is_null();'))

    return add_method_definition(ls, i, f'has_{name}_set', 'bool', class_name, [], body, is_const=True, is_nodiscard=True, is_noexcept=True)

### GETTERS

def _add_getter_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p, data, ctx)
    return add_method_declaration(ls, i, name, return_type, [], is_const=True, is_nodiscard=True)

def _add_getter_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p, data, ctx)
    property_type : str = p['type']

    body : list[(int, str)] = []

    body.append((0, f'if ( is_empty() ) return default_{name}();'))
    body.append((0, f'auto it = data()->find( "{name}" );'))
    body.append((0, f'if ( it == data()->end() || it->is_null() ) return default_{name}();'))

    if property_type in ['module', 'settings']:
        body.append((0, f'return {return_type}' + '{ &( *it ) };'))
    elif property_type == 'enum':
        body.append((0, f'return it->template get<{return_type}>();'))
    elif property_type in BASE_TYPES:
        if property_type == 'string' or property_type == 'path':
            body.append((0, 'return std::string_view{' + f' it->template get_ref<std::string const&>() ' + '};'))
        else:
            body.append((0, f'return it->template get<{return_type}>();'))
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

    return add_method_definition(ls, i, name, return_type, class_name, [], body, is_const=True, is_nodiscard=True)

def _add_getter_test(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], namespace: list[str], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p, data, ctx)
    property_type : str = p['type']

    i = begin_test_case(ls, i, f'{class_name} - property: \\\"{name}\\\" - getter, default, has_set', 'settings')

    if property_type in BASE_TYPES:
        i = add_line(ls, i, 'nlohmann::json obj = { { "' + name + f'", {BASE_TYPES[property_type][1]}' + ' } };' )
    elif property_type == 'enum':
        i = add_line(ls, i, 'nlohmann::json obj = { { "' + name + f'", "{p['enum']['values'][-1]}"' + ' } };' )
    elif property_type in ['module', 'settings']:
        # TODO - specific sets for specific setting classes (i.e. module)
        i = add_line(ls, i, 'nlohmann::json obj = { { "' + name + '", { { "x", "y" } } } };' )
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

    i = add_line(ls, i, 'auto s = ' + '::'.join(namespace) + '::' + class_name + '{ &obj };')
    i = add_line(ls, i, 'auto s_null = ' + '::'.join(namespace) + '::' + class_name + '{};')
    add_blank(ls)

    i = add_line(ls, i, f'auto value = s.{name}();')
    i = add_line(ls, i, f'auto default_value = s_null.{name}();')
    add_blank(ls)

    if property_type in ['module', 'settings']:
        i = add_require(ls, i, '!value.is_empty()')
        i = add_require(ls, i, 'value.data()->at( "x" ) == "y"')
        i = add_require(ls, i, 'default_value.is_empty()')
    elif property_type == 'enum':
        i = add_require(ls, i, f'value == {'::'.join(namespace)}::{to_pascal_case(p['enum']['name'])}::{to_pascal_case(p['enum']['values'][-1])}')
        i = add_require(ls, i, f'default_value == {'::'.join(namespace)}::{_get_default_value(name, p, data, ctx)}')
    elif property_type in BASE_TYPES:
        is_fp : bool = property_type in ['f32', 'f64', 'real']
        val_str : str = 'value' if property_type in ['boolean', 'string', 'path'] else f'static_cast< vortex::{BASE_TYPES[property_type][0]} >( value )'
        def_val_str : str = 'default_value' if property_type in ['boolean', 'string', 'path'] else f'static_cast< vortex::{BASE_TYPES[property_type][0]} >( default_value )'
        default_value : str = _get_default_value(name, p, data, ctx)
        def_prefix = 's_null.' if ('default' in p and isinstance(p['default'], str) and p['default'].startswith('@')) else ('' if ('default' in p or property_type in ['string', 'path', 'boolean']) else 'vortex::')

        if is_fp:
            i = add_require(ls, i, f'{val_str}, Catch::Matchers::WithinAbs( {BASE_TYPES[property_type][1]}, {FP_CMP_EPS} )', suffix='that')
            i = add_require(ls, i, f'{def_val_str}, Catch::Matchers::WithinAbs( {def_prefix}{default_value}, {FP_CMP_EPS} )', suffix='that')
        else:
            i = add_require(ls, i, f'{val_str} == {BASE_TYPES[property_type][1]}')
            i = add_require(ls, i, f'{def_val_str} == {def_prefix}{default_value}')
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

    add_blank(ls)
    add_require(ls, i, f's.has_{name}_set()')
    add_require(ls, i, f'!s_null.has_{name}_set()')

    i = end_test_case(ls, i)

    return i

### RESET

def _add_reset_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return add_method_declaration(ls, i, f'reset_{name}', 'void', [])

def _add_reset_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return add_method_definition(ls, i, f'reset_{name}', 'void', class_name, [], [(0, f'if ( is_empty() ) return;'), (0, f'data()->erase( "{name}" );')])

### SETTERS

def _add_setter_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    arg_type : str = _get_arg_type(p, data, ctx)
    if arg_type != 'std::string_view':
        i = add_method_declaration(ls, i, f'set_{name}', 'void', [(arg_type, name)])
    else:
        i = add_method_declaration(ls, i, f'set_{name}', 'void', [('std::string const&', name)])
        i = add_method_declaration(ls, i, f'set_{name}', 'void', [('std::string &&', name)])
        i = add_method_declaration(ls, i, f'set_{name}', 'void', [('std::string_view', name)], is_definition=True, body=[(0, f'set_{name}( std::string{{ {name} }} );')])
        i = add_method_declaration(ls, i, f'set_{name}', 'void', [('char const *', name)], is_definition=True, body=[(0, f'set_{name}( std::string{{ {name} }} );')])
    return i

def _add_setter_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    arg_type : str = _get_arg_type(p, data, ctx)
    property_type : str = p['type']

    body : list[(int, str)] = []

    body.append((0, f'if ( is_empty() ) throw std::runtime_error{{ "Cannot set value for property \\"{name}\\". Object is empty." }};'))

    if property_type in ['module', 'settings']:
        body.append((0, f'if ( {name}.is_empty() )'))
        body.append((0, '{'))
        body.append((1, f'reset_{name}();'))
        body.append((0, '}'))
        body.append((0, 'else'))
        body.append((0, '{'))
        body.append((1, f'data()->operator[]( "{name}" ) = *( {name}.data() );'))
        body.append((0, '}'))
    elif property_type in BASE_TYPES or property_type == 'enum':
        body.append((0, f'data()->operator[]( "{name}" ) = {name};'))
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

    if arg_type == 'std::string_view':
        i = add_method_definition(ls, i, f'set_{name}', 'void', class_name, [('std::string const&', name)], body)
        i = add_method_definition(ls, i, f'set_{name}', 'void', class_name, [('std::string &&', name)], body)
    else:
        i = add_method_definition(ls, i, f'set_{name}', 'void', class_name, [(arg_type, name)], body)

    return i

def _add_setter_test(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], namespace: list[str], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    arg_type : str = _get_arg_type(p, data, ctx)
    property_type : str = p['type']

    i = begin_test_case(ls, i, f'{class_name} - property: \\\"{name}\\\" - setter, reset', 'settings')

    i = add_line(ls, i, 'nlohmann::json obj = nlohmann::json::object();' )
    i = add_line(ls, i, 'auto s = ' + '::'.join(namespace) + '::' + class_name + '{ &obj };')
    i = add_line(ls, i, 'auto s_null = ' + '::'.join(namespace) + '::' + class_name + '{};')
    add_blank(ls)

    if property_type in BASE_TYPES:
        if arg_type == 'std::string_view':
            i = add_line(ls, i, f'const auto sv = std::string_view{{ "sv" }};')
            i = add_line(ls, i, f'const auto str = std::string{{ "str" }};')
            i = add_line(ls, i, f'const auto cstr = "cstr";')
        else:
            i = add_line(ls, i, f'const auto value = {BASE_TYPES[property_type][1]};')
    if property_type == 'enum':
        i = add_line(ls, i, f'const auto value = {'::'.join(namespace)}::{to_pascal_case(p['enum']['name'])}::{to_pascal_case(p['enum']['values'][-1])};')
    elif property_type in ['module', 'settings']:
        # TODO - specific sets for specific setting classes (i.e. module)
        i = add_line(ls, i, f'nlohmann::json vobj = nlohmann::json::object();')
        i = add_line(ls, i, f'const auto value = vortex::{arg_type}{{ &vobj }};')
        i = add_line(ls, i, f'const auto nvalue = vortex::{arg_type}{{}};')
    add_blank(ls)

    i = add_require(ls, i, f'!s.has_{name}_set()')
    i = add_require(ls, i, f'!s_null.has_{name}_set()')
    add_blank(ls)

    i = add_require(ls, i, f's.reset_{name}()', suffix='nothrow')
    i = add_require(ls, i, f's_null.reset_{name}()', suffix='nothrow')
    add_blank(ls)

    if arg_type == 'std::string_view':
        i = add_require(ls, i, f's_null.set_{name}( sv ), std::runtime_error', suffix='throws_as')
        i = add_require(ls, i, f's_null.set_{name}( str ), std::runtime_error', suffix='throws_as')
        i = add_require(ls, i, f's_null.set_{name}( cstr ), std::runtime_error', suffix='throws_as')
        i = add_require(ls, i, f's_null.set_{name}( std::string{{ "mvstr" }} ), std::runtime_error', suffix='throws_as')
    else:
        i = add_require(ls, i, f's_null.set_{name}( value ), std::runtime_error', suffix='throws_as')
    add_blank(ls)

    if arg_type == 'std::string_view':
        i = add_line(ls, i, f's.set_{name}( sv );')
        i = add_require(ls, i, f's.has_{name}_set()')
        i = add_require(ls, i, f's.{name}() == "sv"')
        add_blank(ls)

        i = add_line(ls, i, f's.set_{name}( str );')
        i = add_require(ls, i, f's.has_{name}_set()')
        i = add_require(ls, i, f's.{name}() == "str"')
        add_blank(ls)

        i = add_line(ls, i, f's.set_{name}( cstr );')
        i = add_require(ls, i, f's.has_{name}_set()')
        i = add_require(ls, i, f's.{name}() == "cstr"')
        add_blank(ls)

        i = add_line(ls, i, f's.set_{name}( std::string{{ "mvstr" }} );')
        i = add_require(ls, i, f's.has_{name}_set()')
        i = add_require(ls, i, f's.{name}() == "mvstr"')
        add_blank(ls)
    else:
        i = add_line(ls, i, f's.set_{name}( value );')
        i = add_require(ls, i, f's.has_{name}_set()')
        if property_type in ['module', 'settings']:
            i = add_require(ls, i, f'*( s.{name}().data() ) == nlohmann::json::object()')
        elif property_type in ['f32', 'f64', 'real']:
            i = add_require(ls, i, f's.{name}(), Catch::Matchers::WithinAbs( value, {FP_CMP_EPS} )', suffix='that')
        else:
            i = add_require(ls, i, f's.{name}() == value')
        add_blank(ls)

    if property_type in ['module', 'settings']:
        i = add_line(ls, i, f's.set_{name}( nvalue );')
        i = add_require(ls, i, f'!s.has_{name}_set()')
        add_blank(ls)
        i = add_line(ls, i, f's.set_{name}( value );')
        add_blank(ls)



    i = add_line(ls, i, f's.reset_{name}();')
    i = add_require(ls, i, f'!s.has_{name}_set()')
    add_blank(ls)

    i = end_test_case(ls, i)

    return i


###########

def add_property_public_declarations(ls: list[str], i: int, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    for name, prop in data.items():
        if not name.startswith('__'):
            i = add_block_comment(ls, i, f'"{name}" property')
            i = _add_getter_declaration(ls, i, name, prop, data, ctx)
            i = _add_has_set_declaration(ls, i, name, prop, data, ctx)
            i = _add_default_value_declaration(ls, i, name, prop, data, ctx)
            i = _add_reset_declaration(ls, i, name, prop, data, ctx)
            i = _add_setter_declaration(ls, i, name, prop, data, ctx)
            add_blank(ls)
    return i

def add_property_definitions(ls: list[str], i: int, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    class_name : str = get_class_name(data)

    for name, prop in data.items():
        if not name.startswith('__'):
            i = add_block_comment(ls, i, f'"{name}" property')
            add_blank(ls)
            i = _add_getter_definition(ls, i, class_name, name, prop, data, ctx)
            add_blank(ls)
            i = _add_has_set_definition(ls, i, class_name, name, prop, data, ctx)
            add_blank(ls)
            i = _add_reset_definition(ls, i, class_name, name, prop, data, ctx)
            add_blank(ls)
            i = _add_setter_definition(ls, i, class_name, name, prop, data, ctx)
            add_blank(ls)
    return i

def add_property_unit_tests(ls: list[str], i: int, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    class_name : str = get_class_name(data)
    namespace : str = get_namespace(data)

    for name, prop in data.items():
        if not name.startswith('__'):
            i = add_block_comment(ls, i, f'"{name}" property')
            add_blank(ls)
            i = _add_getter_test(ls, i, class_name, name, prop, namespace, data, ctx)
            add_blank(ls)
            i = _add_setter_test(ls, i, class_name, name, prop, namespace, data, ctx)
            add_blank(ls)
    return i
