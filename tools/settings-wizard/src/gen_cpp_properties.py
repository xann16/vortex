from cpp_utils import get_class_name, get_namespace, begin_namespace, end_namespace, add_blank, add_line, add_block_comment, add_method_declaration, add_method_definition, begin_test_case, end_test_case, add_require
from gen_cpp_validation import generate_pre_validate_property_body
from gen_utils import to_pascal_case
from typing import Any, Tuple

FP_CMP_EPS = 0.00001
BASE_TYPES = {
    'boolean': ('bool',             'true',    'false',   'true'    ),
    'i8':      ('i8',               '4',       '77',      '1'       ),
    'i16':     ('i16',              '3',       '66',      '1000'    ),
    'i32':     ('i32',              '8l',      '16l',     '1024l'  ),
    'i64':     ('i64',              '1ll',     '111ll',   '11111ll' ),
    'u8':      ('u8',               '1u',      '66u',     '121u'    ),
    'u16':     ('u16',              '2u',      '44u',     '22u'     ),
    'u32':     ('u32',              '3ul',     '42ul',    '33ul'    ),
    'u64':     ('u64',              '4ull',    '444ull',  '4141ull' ),
    'f32':     ('f32',              '8.1f',    '111.1f',  '11.0f'   ),
    'f64':     ('f64',              '8.2',     '222.2',   '12.0'    ),
    'real':    ('real',             '8.3',     '333.3',   '14.0'    ),
    'string':  ('std::string_view', '"stest"', '"ttest"', '"utest"' ),
    'path':    ('std::string_view', '"ptest"', '"qtest"', '"rtest"' ),
}


def get_required_list(data: dict[str, Any], ctx: dict[str, Any]) -> list[str, Any]:
    return [ item for item in data.items() if (not item[0].startswith('__') and is_required(item[1], data, ctx)) ]

def is_required(p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> bool:
    if 'is_required' in p and p['is_required']:
        return True
    if 'is_array' in p and p['is_array'] and ( 'default' not in p or not p['default'] ):
        return False
    if p['type'] == 'module':
        module_key : str = [entry['from'] for entry in data['__includes__'] if p['module']['name'] in entry['import']['modules']][0]
        return has_module_required(ctx['defs'][module_key], ctx)
    return False

def has_module_required(data: dict[str, Any], ctx: dict[str, Any]) -> bool:
    return any(get_required_list(data, ctx))

def _is_array(p: dict[str, Any]) -> bool:
    return 'is_array' in p and p['is_array']

def _get_singular_name(name: str, p: dict[str, Any]) -> str:
    if 'singular_name' in p and p['singular_name']:
        return p['singular_name']
    return name[:-1] if name.endswith('s') else (name + '_item')


def _get_module_type(name: str, data: dict[str, Any], ctx: dict[str, Any], is_static: bool = False) -> str:
    from_path : str = [inc['from'] for inc in data['__includes__'] if name in inc['import']['modules']][0] if ('__includes__' in data) else ''
    import_metadata : dict[str, Any] = ctx['defs'][from_path]['__metadata__']
    return '::'.join([import_metadata['package'].lstrip('*')] + import_metadata['namespace'] + (['stat'] if is_static else []) + [to_pascal_case(name)])


def _get_return_type(p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], skip_array: bool = False, is_static: bool = False) -> str:
    is_array : bool = _is_array(p)
    property_type : str = p['type']

    if not skip_array and is_array:
        if is_static:
            return f'std::span< {_get_return_type(p, data, ctx, skip_array=True, is_static=is_static)} >'
        else:
            return f'std::vector< {_get_return_type(p, data, ctx, skip_array=True, is_static=is_static).replace('_view', '')} >'

    if property_type == 'module':
        return _get_module_type(p['module']['name'], data, ctx, is_static=is_static)
    elif property_type == 'settings':
        if is_static:
            raise RuntimeError( "Properties of type 'settings' cannot be used in static context." )
        return 'core::settings::json::AnySettings'
    elif property_type == 'enum':
        return to_pascal_case(p['enum']['name'])
    elif property_type in BASE_TYPES:
        return BASE_TYPES[property_type][0]
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

def _get_arg_type(p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], skip_array: bool = False) -> str:
    is_array : bool = _is_array(p)
    property_type : str = p['type']

    if not skip_array and is_array:
        return f'std::vector< {_get_return_type(p, data, ctx, skip_array=True).replace('_view', '')} > const&'

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

def _get_default_value(name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], skip_arrays: bool = False, is_static: bool = False) -> str:
    property_type : str = p['type']
    default_value : Any = p['default'] if 'default' in p else None

    if is_static and property_type in ['string', 'path']:
        default_value = None

    if property_type in ['module', 'settings']:
        return _get_return_type(p, data, ctx, is_static=is_static) + '{}'
    elif property_type == 'enum':
        enum_values : list[str] = p['enum']['values']
        if default_value and default_value not in enum_values:
            print(f"WARNING: Invalid default value '{default_value}' for enum '{name}'. Valid values include: {', '.join(enum_values)}. Using first value '{enum_values[0]}' instead.")
            default_value = None
        return _get_return_type(p, data, ctx) + '::' + to_pascal_case(enum_values[0] if not default_value else default_value)
    elif property_type in BASE_TYPES:
        default_str : str = ''
        if default_value is not None:
            if property_type in ['string', 'path']:
                default_str = f'"{default_value}"'
            elif property_type == 'boolean':
                default_str = 'true' if default_value else 'false'
            else:
                default_str = str(default_value)
        return default_str if default_value is not None else (_get_return_type(p, data, ctx) + '{}')
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

def _get_value_stingification(name: str, property_type: str, is_array: bool, indent: int, is_in_array: bool = False, is_static: bool = False) -> list[(int, str)]:
    result : list[(int, str)] = []

    line_start : str = f'os << std::setw( indent_size * {"( indent_level + 1 )" if is_in_array else "indent_level"} ) << "" << "{'- ' if is_in_array else f"{name}:"}'
    if not is_array:
        getter : str = 'el' if is_in_array else f"{name}()"
        if property_type in BASE_TYPES:
            if property_type != 'boolean':
                result.append((indent, f'{line_start} " << {getter} << \'\\n\';'))
            else:
                result.append((indent, f'{line_start} " << ( {getter} ? "true" : "false" ) << \'\\n\';'))
        elif property_type == 'enum':
            result.append((indent, f'{line_start} " << to_c_str( {getter} ) << \'\\n\';'))
        elif property_type in ['settings', 'module']:
            result.append((indent, f'{line_start}\\n";'))
            result.append((indent, f'{getter}.stringify( os, indent_size, indent_level + {'2' if is_in_array else '1'}{"" if is_static else ", display_all"} );'))
    else:
        result.append((indent, f'{line_start}";'))
        result.append((indent, f'auto const& {name}_arr = {name}();'))
        result.append((indent, ''))
        result.append((indent, f'if ( {name}_arr.empty() )'))
        result.append((indent, '{'))
        result.append((indent + 1, 'os << " <empty>\\n";'))
        result.append((indent, '}'))
        result.append((indent, 'else'))
        result.append((indent, '{'))
        result.append((indent + 1, 'os << \'\\n\';'))
        result.append((indent + 1, f'for (auto const& el : {name}_arr)'))
        result.append((indent + 1, '{'))
        result.extend(_get_value_stingification(name, property_type, False, indent + 2, is_in_array=True, is_static=is_static))
        result.append((indent + 1, '}'))
        result.append((indent, '}'))

    return result


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
            result.extend(_get_value_stingification(name, prop['type'], _is_array(prop), 1))
            result.append((0, '}'))

    result.append((0, ''))
    result.append((0, 'return os;'))

    return result


def get_static_stringify_body(data: list[str]) -> list[(int, str)]:
    result : list[(int, str)] = []

    for name, prop in data.items():
        if not name.startswith('__'):
            result.extend(_get_value_stingification(name, prop['type'], _is_array(prop), 1, is_static=True))

    result.append((0, ''))
    result.append((0, 'return os;'))

    return result

##### GENERAL PROPERTIES #####

### DEFAULT VALUE

def _add_default_value_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p, data, ctx)
    default_value : str = _get_default_value(name, p, data, ctx)
    body : list[(int, str)] = [(0, f'return {default_value};' )]
    preq : str = '' if _is_array(p) or ('default' in p and isinstance(p['default'], str) and p['default'].startswith('@')) else 'constexpr'
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

    if not _is_array(p):
        if property_type in ['module', 'settings']:
            body.append((0, f'return {return_type}' + '{ &( *it ) };'))
        elif property_type == 'enum':
            body.append((0, f'return it->template get< {return_type} >();'))
        elif property_type in BASE_TYPES:
            if property_type == 'string' or property_type == 'path':
                body.append((0, 'return std::string_view{' + f' it->template get_ref<std::string const&>() ' + '};'))
            else:
                body.append((0, f'return it->template get< {return_type} >();'))
        else:
            raise RuntimeError(f'Unexpected property type: {property_type}.')

    else:
        value_type : str = _get_return_type(p, data, ctx, skip_array=True)

        body.append((0, ''))
        body.append((0, f'auto result = {return_type}{{}};'))
        body.append((0, 'result.reserve( it->size() );'))
        body.append((0, ''))
        body.append((0, f'auto value_mapping = []( auto& value )'))
        body.append((0, '{'))

        if property_type in ['module', 'settings']:
            body.append((1, f'return {value_type}' + '{ &value };'))
        elif property_type == 'enum':
            body.append((1, f'return value.template get< {value_type} >();'))
        elif property_type in BASE_TYPES:
            return_type = return_type.replace('_view', '')
            if property_type == 'string' or property_type == 'path':
                body.append((1, 'return  value.template get< std::string >();'))
            else:
                body.append((1, f'return value.template get< {value_type} >();'))
        else:
            raise RuntimeError(f'Unexpected property type: {property_type}.')

        body.append((0, '};'))
        body.append((0, ''))
        body.append((0, 'std::transform( it->begin(), it->end(), std::back_inserter( result ), value_mapping );'))
        body.append((0, 'return result;'))

    return add_method_definition(ls, i, name, return_type, class_name, [], body, is_const=True, is_nodiscard=True)

def _add_getter_test(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], namespace: list[str], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    is_array : bool = _is_array(p)
    return_type : str = _get_return_type(p, data, ctx)
    property_type : str = p['type']

    i = begin_test_case(ls, i, f'{class_name} - property: \\\"{name}\\\" - getter, default, has_set', 'settings')

    if property_type in BASE_TYPES:
        val_str : str = f'{{ {BASE_TYPES[property_type][1]}, {BASE_TYPES[property_type][2]}, {BASE_TYPES[property_type][3]} }}' if is_array else BASE_TYPES[property_type][1]
        i = add_line(ls, i, 'nlohmann::json obj = { { "' + name + f'", {val_str}' + ' } };' )
    elif property_type == 'enum':
        val_str : str = f'{{ {", ".join(str(val) for val in p['enum']['values'])} }}' if is_array else p['enum']['values'][-1]
        i = add_line(ls, i, 'nlohmann::json obj = { { "' + name + f'", "{val_str}"' + ' } };' )
    elif property_type in ['module', 'settings']:
        # TODO - specific sets for specific setting classes (i.e. module)
        init_str : str = '{ { "name", "x"} }'
        full_init_str : str = ('{ ' + ', '.join([init_str, init_str.replace('x', 'y'), init_str.replace('x', 'z')]) + ' }') if is_array else init_str
        i = add_line(ls, i, 'nlohmann::json obj = { { "' + name + '", ' + full_init_str + ' } };' )
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

    i = add_line(ls, i, 'auto s = ' + '::'.join(namespace) + '::' + class_name + '{ &obj };')
    i = add_line(ls, i, 'auto s_null = ' + '::'.join(namespace) + '::' + class_name + '{};')
    add_blank(ls)

    i = add_line(ls, i, f'auto value = s.{name}();')
    i = add_line(ls, i, f'auto default_value = s_null.{name}();')
    add_blank(ls)

    if not is_array:
        if property_type in ['module', 'settings']:
            i = add_require(ls, i, '!value.is_empty()')
            i = add_require(ls, i, 'value.data()->at( "name" ) == "x"')
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

    else:
        if property_type in ['module', 'settings']:
            i = add_require(ls, i, '!value.empty()')
            i = add_require(ls, i, 'value.size() == 3ull')
            i = add_require(ls, i, '!value[ 0 ].is_empty()')
            i = add_require(ls, i, 'value[ 0 ].data()->at( "name" ) == "x"')
            i = add_require(ls, i, '!value[ 1 ].is_empty()')
            i = add_require(ls, i, 'value[ 1 ].data()->at( "name" ) == "y"')
            i = add_require(ls, i, '!value[ 2 ].is_empty()')
            i = add_require(ls, i, 'value[ 2 ].data()->at( "name" ) == "z"')
            i = add_require(ls, i, 'default_value.empty()')
        elif property_type == 'enum':
            for ii, ename in enumerate(p['enum']['values']):
                i = add_require(ls, i, f'value.size() == {len(p['enum']['values'])}ull')
                i = add_require(ls, i, f'value[ {ii} ] == {'::'.join(namespace)}::{to_pascal_case(p['enum']['name'])}::{to_pascal_case(ename)}')
            i = add_require(ls, i, f'default_value.empty()')
        elif property_type in BASE_TYPES:
            is_fp : bool = property_type in ['f32', 'f64', 'real']
            val_str : str = 'value[ XXXXX ]' if property_type in ['boolean', 'string', 'path'] else f'static_cast< vortex::{BASE_TYPES[property_type][0]} >( value[ XXXXX ] )'
            i = add_require(ls, i, 'value.size() == 3ull')
            for ii in [0, 1, 2]:
                if is_fp:
                    i = add_require(ls, i, f'{val_str.replace('XXXXX', str(ii))}, Catch::Matchers::WithinAbs( {BASE_TYPES[property_type][1 + ii]}, {FP_CMP_EPS} )', suffix='that')
                else:
                    i = add_require(ls, i, f'{val_str.replace('XXXXX', str(ii))} == {BASE_TYPES[property_type][1 + ii]}')
            i = add_require(ls, i, f'default_value.empty()')
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
    body : list[(int, str)] = []
    if is_required(p, data, ctx):
        body.append((0, f'throw std::runtime_error{{ "Property \'{name}\' is required. It cannot be reset." }};'))
    else:
        body.append((0, 'if ( is_empty() ) return;'))
        body.append((0, f'data()->erase( "{name}" );'))
    return add_method_definition(ls, i, f'reset_{name}', 'void', class_name, [], body)

### SETTERS

def _add_setter_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    is_array : bool = _is_array(p)
    arg_type : str = _get_arg_type(p, data, ctx)

    if not is_array:
        if arg_type != 'std::string_view':
            i = add_method_declaration(ls, i, f'set_{name}', 'void', [(arg_type, name)])
        else:
            i = add_method_declaration(ls, i, f'set_{name}', 'void', [('std::string const&', name)])
            i = add_method_declaration(ls, i, f'set_{name}', 'void', [('std::string &&', name)])
            i = add_method_declaration(ls, i, f'set_{name}', 'void', [('std::string_view', name)], is_definition=True, body=[(0, f'set_{name}( std::string{{ {name} }} );')])
            i = add_method_declaration(ls, i, f'set_{name}', 'void', [('char const *', name)], is_definition=True, body=[(0, f'set_{name}( std::string{{ {name} }} );')])
    else:
            i = add_method_declaration(ls, i, f'set_{name}', 'void', [(arg_type, name)])
            i = add_method_declaration(ls, i, f'set_{name}', 'void', [(arg_type.replace('const', '&'), name)])
            i = add_method_declaration(ls, i, f'set_{name}', 'void', [(arg_type.replace('vector', 'initializer_list').replace(' const&', ''), name + '_list')])
    return i

def _add_setter_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    is_array : bool = _is_array(p)
    arg_type : str = _get_arg_type(p, data, ctx)
    property_type : str = p['type']

    body : list[(int, str)] = []

    body.append((0, f'if ( is_empty() ) throw std::runtime_error{{ "Cannot set value for property \\"{name}\\". Object is empty." }};'))
    body.append((0, f'pre_validate_{name}( {name} );'))

    if not is_array:
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

    else:
        if property_type in ['module', 'settings']:
            body.append((0, f'data()->operator[]( "{name}" ) = nlohmann::json::array();'))
            body.append((0, f'auto& {name}_arr =  data()->operator[]( "{name}" );'))
            body.append((0, f'for ( auto el : {name} )'))
            body.append((0, '{'))
            body.append((1, f'{name}_arr.emplace_back( *( el.data() ) );'))
            body.append((0, '}'))
        elif property_type in BASE_TYPES or property_type == 'enum':
            body.append((0, f'data()->operator[]( "{name}" ) = {name};'))
        else:
            raise RuntimeError(f'Unexpected property type: {property_type}.')

        i = add_method_definition(ls, i, f'set_{name}', 'void', class_name, [(arg_type, name)], body)
        i = add_method_definition(ls, i, f'set_{name}', 'void', class_name, [(arg_type.replace('const', '&'), name)], body)
        i = add_method_definition(ls, i, f'set_{name}', 'void', class_name, [(arg_type.replace('vector', 'initializer_list').replace(' const&', ''), name)], body)

    return i

def _add_setter_test(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], namespace: list[str], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    is_array : bool = _is_array(p)
    is_req : bool = is_required(p, data, ctx)
    arg_type : str = _get_arg_type(p, data, ctx)
    property_type : str = p['type']

    i = begin_test_case(ls, i, f'{class_name} - property: \\\"{name}\\\" - setter, reset', 'settings')

    i = add_line(ls, i, 'nlohmann::json obj = nlohmann::json::object();' )
    i = add_line(ls, i, 'auto s = ' + '::'.join(namespace) + '::' + class_name + '{ &obj };')
    i = add_line(ls, i, 'auto s_null = ' + '::'.join(namespace) + '::' + class_name + '{};')
    add_blank(ls)

    if not is_array:
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
    else:
        list_of_values_str = ''
        value_type : str = _get_return_type(p, data, ctx)
        if property_type in BASE_TYPES:
            list_of_values_str = '{ ' + BASE_TYPES[property_type][1] + ', ' + BASE_TYPES[property_type][2] + ', ' + BASE_TYPES[property_type][3] + ' }'
        if property_type == 'enum':
            enum_value_prefix : str = '::'.join(namespace) + '::' + to_pascal_case(p['enum']['name']) + '::'
            list_of_values_str = '{ ' + ', '.join(f'{enum_value_prefix}{to_pascal_case(ename)}' for ename in p['enum']['values']) + ' }'
        elif property_type in ['module', 'settings']:
            # TODO - specific sets for specific setting classes (i.e. module)
            i = add_line(ls, i, 'nlohmann::json vobj = { { "name", "v" } };')
            i = add_line(ls, i, 'nlohmann::json wobj = { { "name", "w" } };')
            i = add_line(ls, i, 'nlohmann::json zobj = { { "name", "z" } };')
            value_str : str = f'vortex::{_get_arg_type(p, data, ctx, skip_array=True)}{{ &[[[XXX]]]obj }}'
            list_of_values_str : str = '{ ' + ', '.join([value_str.replace('[[[XXX]]]', letter) for letter in ["v", "w", "z"]]) + ' }'
            value_type = value_type.replace('vector< ', 'vector< vortex::')
        i = add_line(ls, i, f'const auto value = {value_type}{list_of_values_str};')
    add_blank(ls)

    i = add_require(ls, i, f'!s.has_{name}_set()')
    i = add_require(ls, i, f'!s_null.has_{name}_set()')
    add_blank(ls)

    if is_req:
        i = add_require(ls, i, f's.reset_{name}(), std::runtime_error', suffix='throws_as')
        i = add_require(ls, i, f's_null.reset_{name}(), std::runtime_error', suffix='throws_as')
    else:
        i = add_require(ls, i, f's.reset_{name}()', suffix='nothrow')
        i = add_require(ls, i, f's_null.reset_{name}()', suffix='nothrow')
    add_blank(ls)

    if not is_array:
        if arg_type == 'std::string_view':
            i = add_require(ls, i, f's_null.set_{name}( sv ), std::runtime_error', suffix='throws_as')
            i = add_require(ls, i, f's_null.set_{name}( str ), std::runtime_error', suffix='throws_as')
            i = add_require(ls, i, f's_null.set_{name}( cstr ), std::runtime_error', suffix='throws_as')
            i = add_require(ls, i, f's_null.set_{name}( std::string{{ "mvstr" }} ), std::runtime_error', suffix='throws_as')
        else:
            i = add_require(ls, i, f's_null.set_{name}( value ), std::runtime_error', suffix='throws_as')
    else:
        i = add_require(ls, i, f's_null.set_{name}( value ), std::runtime_error', suffix='throws_as')
        i = add_require(ls, i, f's_null.set_{name}( {value_type}{{ value }} ), std::runtime_error', suffix='throws_as')
        i = add_require(ls, i, f's_null.set_{name}( {list_of_values_str} ), std::runtime_error', suffix='throws_as')
    add_blank(ls)

    if not is_array:
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

    else:
        if not is_req:
            i = add_line(ls, i, f's.reset_{name}();')
            i = add_require(ls, i, f'!s.has_{name}_set()')
            add_blank(ls)
        i = add_line(ls, i, f's.set_{name}( value );')
        i = add_require(ls, i, f's.has_{name}_set()')
        i = add_require(ls, i, f's.{name}() == value')
        add_blank(ls)

        if not is_req:
            i = add_line(ls, i, f's.reset_{name}();')
            i = add_require(ls, i, f'!s.has_{name}_set()')
            add_blank(ls)
        i = add_line(ls, i, f's.set_{name}( {value_type}{{ value }} );')
        i = add_require(ls, i, f's.has_{name}_set()')
        i = add_require(ls, i, f's.{name}() == value')
        add_blank(ls)

        if not is_req:
            i = add_line(ls, i, f's.reset_{name}();')
            i = add_require(ls, i, f'!s.has_{name}_set()')
            add_blank(ls)
        i = add_line(ls, i, f's.set_{name}( {list_of_values_str} );')
        i = add_require(ls, i, f's.has_{name}_set()')
        i = add_require(ls, i, f's.{name}() == value')
        add_blank(ls)

    if not is_req:
        i = add_line(ls, i, f's.reset_{name}();')
        i = add_require(ls, i, f'!s.has_{name}_set()')
        add_blank(ls)

    i = end_test_case(ls, i)

    return i

##### ARRAY-SPECIFIC PROPERTIES - SIMPLE #####

def _add_array_is_empty_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    prefix : str = 'are' if name.endswith('s') else 'is'
    return add_method_declaration(ls, i, f'{prefix}_{name}_empty', 'bool', [], is_const=True, is_nodiscard=True, is_noexcept=True)

def _add_array_is_empty_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    # TODO - consider non-zero sized defaults
    prefix : str = 'are' if name.endswith('s') else 'is'

    body : list[(int, str)] = []

    body.append((0, f'if ( is_empty() ) return true;'))
    body.append((0, f'return data()->at( "{name}" ).empty();'))

    return add_method_definition(ls, i, f'{prefix}_{name}_empty', 'bool', class_name, [], body, is_const=True, is_nodiscard=True, is_noexcept=True)


def _add_array_count_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return add_method_declaration(ls, i, f'{name}_count', 'std::size_t', [], is_const=True, is_nodiscard=True, is_noexcept=True)

def _add_array_count_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    # TODO - consider non-zero sized defaults
    body : list[(int, str)] = []

    body.append((0, f'if ( is_empty() ) return 0ull;'))
    body.append((0, f'return data()->at( "{name}" ).size();'))

    return add_method_definition(ls, i, f'{name}_count', 'std::size_t', class_name, [], body, is_const=True, is_nodiscard=True, is_noexcept=True)


def _add_array_clear_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return add_method_declaration(ls, i, f'clear_{name}', 'void', [])

def _add_array_clear_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    # TODO - consider non-zero sized defaults
    body : list[(int, str)] = []

    body.append((0, f'if ( is_empty() ) return;'))
    body.append((0, f'auto it = data()->find( "{name}" );'))
    body.append((0, f'if ( it == data()->end() || it->is_null() )'))
    body.append((0, '{'))
    body.append((1, f'data()->operator[]( "{name}" ) = nlohmann::json::array();'))
    body.append((0, '}'))
    body.append((0, 'else'))
    body.append((0, '{'))
    body.append((1, f'it->clear();'))
    body.append((0, '}'))

    return add_method_definition(ls, i, f'clear_{name}', 'void', class_name, [], body)


def _add_array_getter_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p, data, ctx, skip_array=True)
    return add_method_declaration(ls, i, f'{_get_singular_name(name, p)}_at', return_type, [('std::size_t', 'index')], is_const=True, is_nodiscard=True)

def _add_array_getter_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p, data, ctx, skip_array=True)
    property_type : str = p['type']

    # TODO - consider non-zero sized defaults
    body : list[(int, str)] = []

    body.append((0, 'if ( is_empty() ) throw std::runtime_error{ "Item cannot be accessed. Parent object is empty." };'))

    body.append((0, f'auto it = data()->find( "{name}" );'))
    body.append((0, f'if ( it == data()->end() || it->is_null() ) return default_{name}().at( index );'))
    body.append((0, f'auto& json_value = data()->at( "{name}" ).at( index );'))

    if property_type in ['module', 'settings']:
        body.append((0, f'return {return_type}' + '{ &json_value };'))
    elif property_type == 'enum':
        body.append((0, f'return json_value.template get< {return_type} >();'))
    elif property_type in BASE_TYPES:
        if property_type == 'string' or property_type == 'path':
            body.append((0, 'return std::string_view{' + f' json_value.template get_ref<std::string const&>() ' + '};'))
        else:
            body.append((0, f'return json_value.template get< {return_type} >();'))
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

    return add_method_definition(ls, i, f'{_get_singular_name(name, p)}_at', return_type, class_name, [('std::size_t', 'index')], body, is_const=True, is_nodiscard=True)


def _add_array_add_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    arg_type : str = _get_arg_type(p, data, ctx, skip_array=True)
    sg_name : str = _get_singular_name(name, p)

    if arg_type == 'std::string_view':
        i = add_method_declaration(ls, i, f'add_{sg_name}', 'void', [('std::string const&', sg_name)])
        i = add_method_declaration(ls, i, f'add_{sg_name}', 'void', [('std::string &&', sg_name)])
        i = add_method_declaration(ls, i, f'add_{sg_name}', 'void', [('std::string_view', sg_name)], is_definition=True, body=[(0, f'add_{sg_name}( std::string{{ {sg_name} }} );')])
        i = add_method_declaration(ls, i, f'add_{sg_name}', 'void', [('char const *', sg_name)], is_definition=True, body=[(0, f'add_{sg_name}( std::string{{ {sg_name} }} );')])
    else:
        i = add_method_declaration(ls, i, f'add_{sg_name}', 'void', [(arg_type, sg_name)])

    return i

def _add_array_add_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    arg_type : str = _get_arg_type(p, data, ctx, skip_array=True)
    property_type : str = p['type']
    sg_name : str = _get_singular_name(name, p)

    body : list[(int, str)] = []

    body.append((0, 'if ( is_empty() ) throw std::runtime_error{ "Item cannot be added. Parent object is empty." };'))
    if property_type in ['module', 'settings']:
        body.append((0, f'if ( {sg_name}.is_empty() ) return;'))
    body.append((0, f'pre_validate_{sg_name}( {sg_name} );'))
    body.append((0, f'auto it = data()->find( "{name}" );'))
    body.append((0, f'if ( it == data()->end() || it->is_null() )'))
    body.append((0, '{'))
    body.append((1, f'data()->operator[]( "{name}" ) = nullptr;'))
    body.append((0, '}'))

    if property_type in ['module', 'settings']:
        body.append((0, f'data()->operator[]( "{name}" ).push_back( *( {sg_name}.data() ) );'))
    elif property_type in BASE_TYPES or property_type == 'enum':
        body.append((0, f'data()->operator[]( "{name}" ).emplace_back( {sg_name} );'))
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')


    if arg_type == 'std::string_view':
        i = add_method_definition(ls, i, f'add_{sg_name}', 'void', class_name, [('std::string const&', sg_name)], body)
        i = add_method_definition(ls, i, f'add_{sg_name}', 'void', class_name, [('std::string &&', sg_name)], body)
    else:
        i = add_method_definition(ls, i, f'add_{sg_name}', 'void', class_name, [(arg_type, sg_name)], body)

    return i


def _add_array_remove_declaration(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    arg_type : str = _get_arg_type(p, data, ctx, skip_array=True)
    property_type : str = p['type']
    sg_name : str = _get_singular_name(name, p)

    i = add_method_declaration(ls, i, f'remove_{sg_name}_at', 'void', [('std::size_t', 'index')])

    if arg_type == 'std::string_view':
        i = add_method_declaration(ls, i, f'remove_{sg_name}', 'void', [('std::string const&', sg_name)])
        i = add_method_declaration(ls, i, f'remove_{sg_name}', 'void', [('std::string &&', sg_name)])
        i = add_method_declaration(ls, i, f'remove_{sg_name}', 'void', [('std::string_view', sg_name)], is_definition=True, body=[(0, f'remove_{sg_name}( std::string{{ {sg_name} }} );')])
        i = add_method_declaration(ls, i, f'remove_{sg_name}', 'void', [('char const *', sg_name)], is_definition=True, body=[(0, f'remove_{sg_name}( std::string{{ {sg_name} }} );')])
    else:
        i = add_method_declaration(ls, i, f'remove_{sg_name}', 'void', [(arg_type, '' if property_type in ['module', 'settings'] else sg_name)])

    return i


def _add_array_remove_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    arg_type : str = _get_arg_type(p, data, ctx, skip_array=True)
    property_type : str = p['type']
    sg_name : str = _get_singular_name(name, p)

    body_by_index : list[(int, str)] = []

    body_by_index.append((0, 'if ( is_empty() ) return;'))
    body_by_index.append((0, f'auto it = data()->find( "{name}" );'))
    body_by_index.append((0, f'if ( it == data()->end() || it->is_null() ) return;'))
    body_by_index.append((0, f'it->erase( index );'))

    i = add_method_definition(ls, i, f'remove_{sg_name}_at', 'void', class_name, [('std::size_t', 'index')], body_by_index)
    add_blank(ls)


    body_by_value : list[(int, str)] = []

    if property_type in ['module', 'settings']:
        body_by_value.append((0, 'throw std::runtime_error{ "Remove method not implemented for arrays of settings objects." };'))
    else:
        body_by_value.append((0, 'if ( is_empty() ) return;'))
        body_by_value.append((0, f'auto it = data()->find( "{name}" );'))
        body_by_value.append((0, f'if ( it == data()->end() || it->is_null() ) return;'))
        body_by_value.append((0, ''))
        body_by_value.append((0, f'for ( auto arr_it = it->begin(); arr_it != it->end(); arr_it++ )'))
        body_by_value.append((0, '{'))
        body_by_value.append((1, f'if (*arr_it == {sg_name})'))
        body_by_value.append((1, '{'))
        body_by_value.append((2, 'it->erase( arr_it );'))
        body_by_value.append((2, 'return;'))
        body_by_value.append((1, '}'))
        body_by_value.append((0, '}'))

    if arg_type == 'std::string_view':
        i = add_method_definition(ls, i, f'remove_{sg_name}', 'void', class_name, [('std::string const&', sg_name)], body_by_value)
        add_blank(ls)
        i = add_method_definition(ls, i, f'remove_{sg_name}', 'void', class_name, [('std::string &&', sg_name)], body_by_value)
        add_blank(ls)
    else:
        i = add_method_definition(ls, i, f'remove_{sg_name}', 'void', class_name, [(arg_type, '' if property_type in ['module', 'settings'] else sg_name)], body_by_value)
        add_blank(ls)

    return i

def _add_array_specific_tests(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], namespace: list[str], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    value_arg_type : str = _get_arg_type(p, data, ctx, skip_array=True)
    property_type : str = p['type']
    sg_name : str = _get_singular_name(name, p)

    i = begin_test_case(ls, i, f'{class_name} - property: \\\"{name}\\\" - array-specific', 'settings')

    i = add_line(ls, i, 'nlohmann::json obj = nlohmann::json::object();' )
    i = add_line(ls, i, 'auto s = ' + '::'.join(namespace) + '::' + class_name + '{ &obj };')
    add_blank(ls)

    if property_type in BASE_TYPES:
        if value_arg_type == 'std::string_view':
            i = add_line(ls, i, f'const auto value = std::string{{ "str" }};')
            i = add_line(ls, i, f'const auto xvalue = std::string{{ "xstr" }};')
            i = add_line(ls, i, f'const auto sv = std::string_view{{ "sv" }};')
            i = add_line(ls, i, f'const auto cstr = "cstr";')
        else:
            i = add_line(ls, i, f'const auto value = {BASE_TYPES[property_type][1]};')
            if property_type == 'bool':
                i = add_line(ls, i, f'const auto xvalue = true;')
            else:
                i = add_line(ls, i, f'const auto xvalue = {BASE_TYPES[property_type][1]} + {BASE_TYPES[property_type][1]};')
    if property_type == 'enum':
        i = add_line(ls, i, f'const auto value = {'::'.join(namespace)}::{to_pascal_case(p['enum']['name'])}::{to_pascal_case(p['enum']['values'][-1])};')
        i = add_line(ls, i, f'const auto xvalue = {'::'.join(namespace)}::{to_pascal_case(p['enum']['name'])}::{to_pascal_case(p['enum']['values'][-2])};')
    elif property_type in ['module', 'settings']:
        # TODO - specific sets for specific setting classes (i.e. module)
        i = add_line(ls, i, f'nlohmann::json vobj = nlohmann::json::object();')
        i = add_line(ls, i, 'nlohmann::json xobj = { { "name", "x" } };')
        i = add_line(ls, i, f'const auto value = vortex::{value_arg_type}{{ &vobj }};')
        i = add_line(ls, i, f'const auto xvalue = vortex::{value_arg_type}{{ &xobj }};')
        i = add_line(ls, i, f'const auto nvalue = vortex::{value_arg_type}{{}};')
    add_blank(ls)

    i = add_require(ls, i, f'!s.has_{name}_set()')
    add_blank(ls)
    i = add_line(ls, i, f's.clear_{name}();')
    add_blank(ls)
    i = add_require(ls, i, f's.has_{name}_set()')
    i = add_require(ls, i, f's.{"are" if name.endswith("s") else "is"}_{name}_empty()')
    i = add_require(ls, i, f's.{name}_count() == 0ull')
    add_blank(ls)
    if not is_required(p, data, ctx):
        i = add_line(ls, i, f's.reset_{name}();')
        i = add_require(ls, i, f'!s.has_{name}_set()')
        add_blank(ls)

    i = add_line(ls, i, f's.add_{sg_name}( value );')
    add_blank(ls)
    i = add_require(ls, i, f's.has_{name}_set()')
    i = add_require(ls, i, f'!s.{"are" if name.endswith("s") else "is"}_{name}_empty()')
    i = add_require(ls, i, f's.{name}_count() == 1ull')
    i = add_require(ls, i, f's.{sg_name}_at( 0 ) == value')
    add_blank(ls)
    i = add_line(ls, i, f's.add_{sg_name}( xvalue );')
    add_blank(ls)
    i = add_require(ls, i, f's.has_{name}_set()')
    i = add_require(ls, i, f'!s.{"are" if name.endswith("s") else "is"}_{name}_empty()')
    i = add_require(ls, i, f's.{name}_count() == 2ull')
    i = add_require(ls, i, f's.{sg_name}_at( 0 ) == value')
    i = add_require(ls, i, f's.{sg_name}_at( 1 ) == xvalue')
    add_blank(ls)
    if property_type in ['module', 'settings']:
        i = add_line(ls, i, f's.remove_{sg_name}_at( 0 );')
    else:
        i = add_line(ls, i, f's.remove_{sg_name}( value );')
    add_blank(ls)
    i = add_require(ls, i, f's.has_{name}_set()')
    i = add_require(ls, i, f'!s.{"are" if name.endswith("s") else "is"}_{name}_empty()')
    i = add_require(ls, i, f's.{name}_count() == 1ull')
    i = add_require(ls, i, f's.{sg_name}_at( 0 ) == xvalue')
    add_blank(ls)
    i = add_line(ls, i, f's.add_{sg_name}( value );')
    add_blank(ls)
    i = add_require(ls, i, f's.has_{name}_set()')
    i = add_require(ls, i, f'!s.{"are" if name.endswith("s") else "is"}_{name}_empty()')
    i = add_require(ls, i, f's.{name}_count() == 2ull')
    i = add_require(ls, i, f's.{sg_name}_at( 0 ) == xvalue')
    i = add_require(ls, i, f's.{sg_name}_at( 1 ) == value')
    add_blank(ls)
    i = add_line(ls, i, f's.remove_{sg_name}_at( 0 );')
    add_blank(ls)
    i = add_require(ls, i, f's.has_{name}_set()')
    i = add_require(ls, i, f'!s.{"are" if name.endswith("s") else "is"}_{name}_empty()')
    i = add_require(ls, i, f's.{name}_count() == 1ull')
    i = add_require(ls, i, f's.{sg_name}_at( 0 ) == value')
    add_blank(ls)
    if property_type not in ['module', 'settings']:
        i = add_line(ls, i, f's.remove_{sg_name}( xvalue );')
        add_blank(ls)
        i = add_require(ls, i, f's.has_{name}_set()')
        i = add_require(ls, i, f'!s.{"are" if name.endswith("s") else "is"}_{name}_empty()')
        i = add_require(ls, i, f's.{name}_count() == 1ull')
        i = add_require(ls, i, f's.{sg_name}_at( 0 ) == value')
        add_blank(ls)
    else:
        i = add_require(ls, i, f's.remove_{sg_name}( xvalue ), std::runtime_error', suffix='throws_as')
        add_blank(ls)
        i = add_line(ls, i, f's.add_{sg_name}( nvalue );')
        add_blank(ls)
        i = add_require(ls, i, f's.has_{name}_set()')
        i = add_require(ls, i, f'!s.{"are" if name.endswith("s") else "is"}_{name}_empty()')
        i = add_require(ls, i, f's.{name}_count() == 1ull')
        i = add_require(ls, i, f's.{sg_name}_at( 0 ) == value')
        add_blank(ls)
    i = add_line(ls, i, f's.clear_{name}();')
    add_blank(ls)
    i = add_require(ls, i, f's.has_{name}_set()')
    i = add_require(ls, i, f's.{"are" if name.endswith("s") else "is"}_{name}_empty()')
    i = add_require(ls, i, f's.{name}_count() == 0ull')
    add_blank(ls)
    i = add_require(ls, i, f's.{sg_name}_at( 0 ), nlohmann::json::out_of_range', 'throws_as')
    i = add_require(ls, i, f's.remove_{sg_name}_at( 0 ), nlohmann::json::out_of_range', 'throws_as')
    i = add_require(ls, i, f's.clear_{name}()', 'nothrow')
    if property_type not in ['module', 'settings']:
        i = add_require(ls, i, f's.remove_{sg_name}( value )', 'nothrow')

    if value_arg_type == 'std::string_view':
        add_blank(ls)
        i = add_line(ls, i, f's.add_{sg_name}( value );')
        i = add_require(ls, i, f's.{name}_count() == 1ull')
        i = add_require(ls, i, f's.{sg_name}_at( 0 ) == value')
        add_blank(ls)
        i = add_line(ls, i, f's.add_{sg_name}( std::string{{ xvalue }} );')
        i = add_require(ls, i, f's.{name}_count() == 2ull')
        i = add_require(ls, i, f's.{sg_name}_at( 1 ) == xvalue')
        add_blank(ls)
        i = add_line(ls, i, f's.add_{sg_name}( sv );')
        i = add_require(ls, i, f's.{name}_count() == 3ull')
        i = add_require(ls, i, f's.{sg_name}_at( 2 ) == sv')
        add_blank(ls)
        i = add_line(ls, i, f's.add_{sg_name}( cstr );')
        i = add_require(ls, i, f's.{name}_count() == 4ull')
        i = add_require(ls, i, f's.{sg_name}_at( 3 ) == cstr')
        add_blank(ls)
        i = add_line(ls, i, f's.remove_{sg_name}( value );')
        i = add_require(ls, i, f's.{name}_count() == 3ull')
        i = add_require(ls, i, f's.{sg_name}_at( 0 ) == xvalue')
        add_blank(ls)
        i = add_line(ls, i, f's.remove_{sg_name}( std::string{{ xvalue }} );')
        i = add_require(ls, i, f's.{name}_count() == 2ull')
        i = add_require(ls, i, f's.{sg_name}_at( 0 ) == sv')
        add_blank(ls)
        i = add_line(ls, i, f's.remove_{sg_name}( sv );')
        i = add_require(ls, i, f's.{name}_count() == 1ull')
        i = add_require(ls, i, f's.{sg_name}_at( 0 ) == cstr')
        add_blank(ls)
        i = add_line(ls, i, f's.remove_{sg_name}( cstr );')
        i = add_require(ls, i, f's.{name}_count() == 0ull')

    i = end_test_case(ls, i)

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - property: \\\"{name}\\\" - array-specific - empty object', 'settings')

    i = add_line(ls, i, 'auto s_null = ' + '::'.join(namespace) + '::' + class_name + '{};')
    if property_type in BASE_TYPES:
        if value_arg_type == 'std::string_view':
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
        i = add_line(ls, i, f'const auto value = vortex::{value_arg_type}{{ &vobj }};')
        i = add_line(ls, i, f'const auto nvalue = vortex::{value_arg_type}{{}};')
    add_blank(ls)

    i = add_require(ls, i, f's_null.{"are" if name.endswith("s") else "is"}_{name}_empty()')
    i = add_require(ls, i, f's_null.{name}_count() == 0ull')
    add_blank(ls)

    i = add_require(ls, i, f's_null.{sg_name}_at( 0ull ), std::runtime_error', suffix='throws_as')
    i = add_require(ls, i, f's_null.clear_{name}()', suffix='nothrow')
    i = add_require(ls, i, f's_null.remove_{sg_name}_at( 0ull )', suffix='nothrow')
    add_blank(ls)

    if property_type in BASE_TYPES or property_type == 'enum':
        if value_arg_type == 'std::string_view':
            i = add_require(ls, i, f's_null.add_{sg_name}( sv ), std::runtime_error', suffix='throws_as')
            i = add_require(ls, i, f's_null.add_{sg_name}( str ), std::runtime_error', suffix='throws_as')
            i = add_require(ls, i, f's_null.add_{sg_name}( cstr ), std::runtime_error', suffix='throws_as')
            i = add_require(ls, i, f's_null.add_{sg_name}( std::string{{ str }} ), std::runtime_error', suffix='throws_as')
            add_blank(ls)
            i = add_require(ls, i, f's_null.remove_{sg_name}( sv )', suffix='nothrow')
            i = add_require(ls, i, f's_null.remove_{sg_name}( str )', suffix='nothrow')
            i = add_require(ls, i, f's_null.remove_{sg_name}( cstr )', suffix='nothrow')
            i = add_require(ls, i, f's_null.remove_{sg_name}( std::string{{ str }} )', suffix='nothrow')
        else:
            i = add_require(ls, i, f's_null.add_{sg_name}( value ), std::runtime_error', suffix='throws_as')
            i = add_require(ls, i, f's_null.remove_{sg_name}( value )', suffix='nothrow')
    elif property_type in ['module', 'settings']:
        # TODO - specific sets for specific setting classes (i.e. module)
        i = add_require(ls, i, f's_null.add_{sg_name}( value ), std::runtime_error', suffix='throws_as')
        i = add_require(ls, i, f's_null.add_{sg_name}( nvalue ), std::runtime_error', suffix='throws_as')

    i = end_test_case(ls, i)

    return i

###########


def _add_property_pre_validate_declarations(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    is_array : bool = 'is_array' in p and p['is_array']

    if is_array:
        arg_type : str = _get_arg_type(p, data, ctx)
        prefix : str = '' if generate_pre_validate_property_body(name, p, data, ctx, array_ctx=True)[0] else 'static'
        i = add_method_declaration(ls, i, 'pre_validate_' + name, 'void', [('[[maybe_unused]] ' + arg_type, name)], pre_qualifiers=prefix)
        elem_name : str = _get_singular_name(name, p)
        elem_arg_type : str = _get_arg_type(p, data, ctx, skip_array=True)
        elem_prefix : str = '' if generate_pre_validate_property_body(name, p, data, ctx)[0] else 'static'
        i = add_method_declaration(ls, i, 'pre_validate_' + elem_name, 'void', [('[[maybe_unused]] ' + elem_arg_type, elem_name)], pre_qualifiers=elem_prefix)
    else:
        arg_type : str = _get_arg_type(p, data, ctx)
        prefix : str = '' if generate_pre_validate_property_body(name, p, data, ctx)[0] else 'static'
        i = add_method_declaration(ls, i, 'pre_validate_' + name, 'void', [('[[maybe_unused]] ' + arg_type, name)], pre_qualifiers=prefix)

    return i

def _add_property_pre_validate_definition(ls: list[str], i: int, class_name: str, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    is_array : bool = 'is_array' in p and p['is_array']

    if is_array:
        arg_type : str = _get_arg_type(p, data, ctx)
        _, body = generate_pre_validate_property_body(name, p, data, ctx, array_ctx=True)
        i = add_method_definition(ls, i, 'pre_validate_' + name, 'void', class_name, [('[[maybe_unused]] ' + arg_type, name)], body)
        add_blank(ls)

        elem_name : str = _get_singular_name(name, p)
        elem_arg_type : str = _get_arg_type(p, data, ctx, skip_array=True)
        _, elem_body = generate_pre_validate_property_body(name, p, data, ctx)
        i = add_method_definition(ls, i, 'pre_validate_' + elem_name, 'void', class_name, [('[[maybe_unused]] ' + elem_arg_type, elem_name)], elem_body)
    else:
        arg_type : str = _get_arg_type(p, data, ctx)
        _, body = generate_pre_validate_property_body(name, p, data, ctx)
        i = add_method_definition(ls, i, 'pre_validate_' + name, 'void', class_name, [('[[maybe_unused]] ' + arg_type, name)], body)

    return i

def add_pre_validate_all_definition(ls: list[str], i: int, class_name: str, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    body : list[(int, str)] = []

    body.append((0, f'if ( is_empty() ) return;'))
    body.append((0, ''))

    for name, prop in data.items():
        if not name.startswith('__'):
            body.append((0, f'if ( has_{name}_set() )'))
            body.append((0, '{'))
            body.append((1, f'pre_validate_{name}( {name}() );'))
            body.append((0, '}'))

    return add_method_definition(ls, i, 'pre_validate_all', 'void', class_name, [], body=body)

# STATICs

def _add_static_property_data_member(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p, data, ctx, is_static=True)
    default_value : str = _get_default_value(name, p, data, ctx, is_static=True)
    return add_line(ls, i, f'{return_type} m_{name} = {default_value};')

def _add_static_property_getter(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    return_type : str = _get_return_type(p, data, ctx, is_static=True)
    return add_method_declaration(ls, i, name, return_type, [], body=[(0, f'return m_{name};')], is_const=True, is_nodiscard=True, is_noexcept=True, is_definition=True, pre_qualifiers='constexpr')

def _add_static_property_unit_test(ls: list[str], i: int, name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> int:
    is_array : bool = _is_array(p)
    return_type : str = _get_return_type(p, data, ctx, is_static=True)
    property_type : str = p['type']
    class_name : str = get_class_name(data)
    namespace : list[str] = get_namespace(data)

    i = begin_test_case(ls, i, f'{class_name} - property: \\\"{name}\\\" - static', 'settings')

    i = add_block_comment(ls, i, "TODO - supply test implementation")
    i = add_require(ls, i, "true")

    """
    if property_type in BASE_TYPES:
        val_str : str = f'{{ {BASE_TYPES[property_type][1]}, {BASE_TYPES[property_type][2]}, {BASE_TYPES[property_type][3]} }}' if is_array else BASE_TYPES[property_type][1]
        i = add_line(ls, i, 'nlohmann::json obj = { { "' + name + f'", {val_str}' + ' } };' )
    elif property_type == 'enum':
        val_str : str = f'{{ {", ".join(str(val) for val in p['enum']['values'])} }}' if is_array else p['enum']['values'][-1]
        i = add_line(ls, i, 'nlohmann::json obj = { { "' + name + f'", "{val_str}"' + ' } };' )
    elif property_type in ['module', 'settings']:
        # TODO - specific sets for specific setting classes (i.e. module)
        init_str : str = '{ { "name", "x"} }'
        full_init_str : str = ('{ ' + ', '.join([init_str, init_str.replace('x', 'y'), init_str.replace('x', 'z')]) + ' }') if is_array else init_str
        i = add_line(ls, i, 'nlohmann::json obj = { { "' + name + '", ' + full_init_str + ' } };' )
    else:
        raise RuntimeError(f'Unexpected property type: {property_type}.')

    i = add_line(ls, i, 'auto s = ' + '::'.join(namespace) + '::' + class_name + '{ &obj };')
    i = add_line(ls, i, 'auto s_null = ' + '::'.join(namespace) + '::' + class_name + '{};')
    add_blank(ls)

    i = add_line(ls, i, f'auto value = s.{name}();')
    i = add_line(ls, i, f'auto default_value = s_null.{name}();')
    add_blank(ls)

    if not is_array:
        if property_type in ['module', 'settings']:
            i = add_require(ls, i, '!value.is_empty()')
            i = add_require(ls, i, 'value.data()->at( "name" ) == "x"')
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

    else:
        if property_type in ['module', 'settings']:
            i = add_require(ls, i, '!value.empty()')
            i = add_require(ls, i, 'value.size() == 3ull')
            i = add_require(ls, i, '!value[ 0 ].is_empty()')
            i = add_require(ls, i, 'value[ 0 ].data()->at( "name" ) == "x"')
            i = add_require(ls, i, '!value[ 1 ].is_empty()')
            i = add_require(ls, i, 'value[ 1 ].data()->at( "name" ) == "y"')
            i = add_require(ls, i, '!value[ 2 ].is_empty()')
            i = add_require(ls, i, 'value[ 2 ].data()->at( "name" ) == "z"')
            i = add_require(ls, i, 'default_value.empty()')
        elif property_type == 'enum':
            for ii, ename in enumerate(p['enum']['values']):
                i = add_require(ls, i, f'value.size() == {len(p['enum']['values'])}ull')
                i = add_require(ls, i, f'value[ {ii} ] == {'::'.join(namespace)}::{to_pascal_case(p['enum']['name'])}::{to_pascal_case(ename)}')
            i = add_require(ls, i, f'default_value.empty()')
        elif property_type in BASE_TYPES:
            is_fp : bool = property_type in ['f32', 'f64', 'real']
            val_str : str = 'value[ XXXXX ]' if property_type in ['boolean', 'string', 'path'] else f'static_cast< vortex::{BASE_TYPES[property_type][0]} >( value[ XXXXX ] )'
            i = add_require(ls, i, 'value.size() == 3ull')
            for ii in [0, 1, 2]:
                if is_fp:
                    i = add_require(ls, i, f'{val_str.replace('XXXXX', str(ii))}, Catch::Matchers::WithinAbs( {BASE_TYPES[property_type][1 + ii]}, {FP_CMP_EPS} )', suffix='that')
                else:
                    i = add_require(ls, i, f'{val_str.replace('XXXXX', str(ii))} == {BASE_TYPES[property_type][1 + ii]}')
            i = add_require(ls, i, f'default_value.empty()')
        else:
            raise RuntimeError(f'Unexpected property type: {property_type}.')

    add_blank(ls)
    add_require(ls, i, f's.has_{name}_set()')
    add_require(ls, i, f'!s_null.has_{name}_set()')
    """

    i = end_test_case(ls, i)

    return i

def get_heap_using_or_nested_properties(data: dict[str, Any], ctx: dict[str, Any]) -> Tuple[list[str], list[str]]:
    nested : list[str] = []
    heap_using : list[str] = []

    for name, prop in data.items():
        if not name.startswith('__'):
            if _is_array(prop):
                raise Exception( f"Property '{name}' is an array. Arrays are currently unsupported in static mode." )
            elif prop['type'] in ['string', 'path']:
                heap_using.append(name)
            elif prop['type'] in ['module', 'settings']:
                if prop['type'] == 'settings':
                    raise Exception( f"Property '{name}' is an abstract settings module. Such type is currently unsupported in static mode." )
                nested.append(name)

    return heap_using, nested

def _get_hacky_static_ctor_param(name: str, p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any]) -> Tuple[str, str, str | None, str | None]:
    return _get_return_type(p, data, ctx, is_static=True), name, None, None

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
            if _is_array(prop):
                i = _add_array_is_empty_declaration(ls, i, name, prop, data, ctx)
                i = _add_array_count_declaration(ls, i, name, prop, data, ctx)
                i = _add_array_clear_declaration(ls, i, name, prop, data, ctx)
                i = _add_array_getter_declaration(ls, i, name, prop, data, ctx)
                i = _add_array_add_declaration(ls, i, name, prop, data, ctx)
                i = _add_array_remove_declaration(ls, i, name, prop, data, ctx)
            add_blank(ls)
    return i

def add_property_private_declarations(ls: list[str], i: int, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    i = add_method_declaration(ls, i, 'pre_validate_all', 'void', [])
    for name, prop in data.items():
        if not name.startswith('__'):
            i = _add_property_pre_validate_declarations(ls, i, name, prop, data, ctx)
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
            if _is_array(prop):
                i = _add_array_is_empty_definition(ls, i, class_name, name, prop, data, ctx)
                add_blank(ls)
                i = _add_array_count_definition(ls, i, class_name, name, prop, data, ctx)
                add_blank(ls)
                i = _add_array_clear_definition(ls, i, class_name, name, prop, data, ctx)
                add_blank(ls)
                i = _add_array_getter_definition(ls, i, class_name, name, prop, data, ctx)
                add_blank(ls)
                i = _add_array_add_definition(ls, i, class_name, name, prop, data, ctx)
                add_blank(ls)
                i = _add_array_remove_definition(ls, i, class_name, name, prop, data, ctx)
                add_blank(ls)
            i = _add_property_pre_validate_definition(ls, i, class_name, name, prop, data, ctx)
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
            if _is_array(prop):
                i = _add_array_specific_tests(ls, i, class_name, name, prop, namespace, data, ctx)
                add_blank(ls)
    return i

###########

def has_any_heap_stored_properties(data: dict[str, Any], ctx: dict[str, Any]) -> bool:
    try:
        return any(get_heap_using_or_nested_properties(data, ctx)[0])
    except Exception:
        # currently returning false to cover problematic / unsupported cases
        return False

def get_extra_data_size_body(data: dict[str, Any], ctx: dict[str, Any], is_static: bool = False) -> list[(int, str)]:
    try:
        extra_data, nested = get_heap_using_or_nested_properties(data, ctx)
    except Exception as ex:
        if is_static:
            raise ex
        return [(0, f'throw std::runtime_error{{ "Unsupported operation for settings with abstract nested settings or arrays." }};')]

    components : list[str] = []

    components.extend(f'{p}().size() + 1ull' for p in extra_data)
    components.extend(f'{p}().extra_data_size()' for p in nested)

    if not components:
        components.append('0ull')

    sum_str : str = ' + '.join(components)

    return [(0, f"return {sum_str};")]

def add_static_property_data_members(ls: list[str], i: int, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    for name, prop in data.items():
        if not name.startswith('__'):
            i = _add_static_property_data_member(ls, i, name, prop, data, ctx)
    return i

def add_static_property_getters(ls: list[str], i: int, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    for name, prop in data.items():
        if not name.startswith('__'):
            i = _add_static_property_getter(ls, i, name, prop, data, ctx)
    return i

def add_static_property_unit_tests(ls: list[str], i: int, data: dict[str, Any], ctx: dict[str, Any]) -> int:
    for name, prop in data.items():
        if not name.startswith('__'):
            i = _add_static_property_unit_test(ls, i, name, prop, data, ctx)
    return i

def get_hacky_static_ctor_params(data: dict[str, Any], ctx: dict[str, Any]) -> list[(str, str, str| None, str | None)]:
    return [_get_hacky_static_ctor_param(name, prop, data, ctx) for name, prop in data.items() if not name.startswith('__')]
