from copy import deepcopy
#from cpp_utils import get_class_name, get_namespace, begin_namespace, end_namespace, add_blank, add_line, add_block_comment, add_method_declaration, add_method_definition, begin_test_case, end_test_case, add_require
#from gen_utils import to_pascal_case
from typing import Any, Tuple
from utils import try_parse_expr

# duplciate from gen_cpp_properties
def _get_singular_name(name: str, p: dict[str, Any]) -> str:
    if 'singular_name' in p and p['singular_name']:
        return p['singular_name']
    return name[:-1] if name.endswith('s') else (name + '_item')

def _get_exception_text(name: str, message: str) -> str:
    return f'throw std::runtime_error{{ "Validation failed for property \'{name}\': {message}." }};'

def _get_validated_value_name(base_name: str, v: dict[str, Any], force_getter: bool = False) -> str:
    result : str = base_name + ('()' if force_getter else '')

    if 'args' in v and 'mapping' in v['args']:
        mapping : Any = try_parse_expr(v['args']['mapping'])
        # TODO: currently only properties are supported as mappings and are not validated (+ fallback values)
        if not isinstance(mapping, dict) or 'expr' not in mapping or mapping['expr'] != 'property':
            raise Exception("Vaildator: 'mapping' parameter must be a property expression.")
        result += '.' + '.'.join([token + '()' for token in mapping['target']])

    return result

def _generate_validator_is_set(name: str, v: dict[str, Any], p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], array_ctx: bool = False, force_getter: bool = False) -> Tuple[bool, list[(int, str)]]
    body: list[(int, str)] = []

    body.append((0, f"if ( !is_{name}_set() )"))
    body.append((0, "{"))
    body.append((1, _get_exception_text(name, 'Required property is not specified')))
    body.append((0, "}"))

    return True, body

def _generate_validator_nonempty(name: str, v: dict[str, Any], p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], array_ctx: bool = False, force_getter: bool = False) -> Tuple[bool, list[(int, str)]]:
    property_type : str = p['type']

    if property_type not in ['string', 'path']:
        raise Exception(f"Property '{name}': 'nonempty' validator may only be used with 'string' and 'path' types.")

    body: list[(int, str)] = []
    is_member : bool = force_getter

    if force_getter:
        body.append((0, f'auto {name} = {name}();'))
    if array_ctx:
        sg_name : str = _get_singular_name(name, p)
        body.append((0, f'if ( std::any_of( std::begin( {name} ), std::end( {name} ), []( auto {sg_name} ){{ return {_get_validated_value_name(sg_name, v)}.empty() }} ) )'))
        body.append((0, '{'))
        body.append((1, _get_exception_text(name, 'Array contains empty elements')))
        body.append((0, '}'))
    else:
        body.append((0, f'if ( {_get_validated_value_name(name, v)}.empty() )'))
        body.append((0, '{'))
        body.append((1, _get_exception_text(name, 'Value is empty')))
        body.append((0, '}'))

    return is_member, body

def _generate_validator_range(name: str, v: dict[str, Any], p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], array_ctx: bool = False, force_getter: bool = False) -> Tuple[bool, list[(int, str)]]:
    property_type : str = p['type']

    if property_type in ['string', 'path', 'settings', 'module', 'enum']:
        raise Exception(f"Property '{name}': 'range' validator may only be used with numeric types.")

    min_str : str | None = None if 'args' not in v or 'min' not in v['args'] else v['args']['min']
    max_str : str | None = None if 'args' not in v or 'max' not in v['args'] else v['args']['max']
    is_inclusive : bool = True if 'args' not in v or 'inclusive' not in v['args'] else v['args']['inclusive']

    min_val = int | float | str | None = None
    if min_str is not None:
        min_tmp : str | dict[str, Any] = try_parse_expr(min_str)
        # currently only parameter expressions are supported
        if isinstance(min_tmp, dict):
            if 'expr' in min_tmp and min_tmp['expr'] == 'property':
                min_val = '.'.join([token + '()' for token in min_tmp['target'].split('.')])
                is_member = True
        elif isinstance(min_tmp, str):
            min_val = float(min_str) if property_type in ['real', 'f32', 'f64'] else int(min_str)

    max_val = int | float | str | None = None
    if max_str is not None:
        max_tmp : str | dict[str, Any] = try_parse_expr(max_str)
        # currently only parameter expressions are supported
        if isinstance(max_tmp, dict):
            if 'expr' in max_tmp and max_tmp['expr'] == 'property':
                max_val = '.'.join([token + '()' for token in max_tmp['target'].split('.')])
                is_member = True
        elif isinstance(max_tmp, str):
            max_val = float(max_str) if property_type in ['real', 'f32', 'f64'] else int(max_str)

    if min_val is not None and not isinstance(min_val, str) and max_val is not None and not isinstance(max_val, str) and min_val > max_val:
        raise Exception(f"Property '{name}': 'range' validator requires 'min' parameter smaller than 'max'.")

    if min_val is None and max_val is None:
        raise Exception(f"Property '{name}': 'range' validator requires at least 'min' or 'max' parameter.")

    if property_type.startswith('i'):
        if max_val is not None and not isinstance(max_val, str) and max_val < 0:
            raise Exception(f"Property '{name}': 'range' validator for unsigned type 'max' parameter greater than 0.")
        if min_val is not None and not isinstance(min_val, str) and min_val <= 0:
            # condition is always satisfied
            return False, []

    conditions : list[str] = []
    if min_val is not None:
        conditions.append(f' value <{"" if is_inclusive else "="} {str(min_val)} ')
    if max_val is not None:
        conditions.append(f' value >{"" if is_inclusive else "="} {str(max_val)} ')
    condition : str = '||'.join(conditions)

    body: list[(int, str)] = []
    is_member : bool = force_getter

    if force_getter:
        body.append((0, f'auto {name} = {name}();'))
    if array_ctx:
        sg_name : str = _get_singular_name(name, p)
        body.append((0, f'auto check = []( auto {sg_name} )'))
        body.append((0, '{'))
        body.append((1, f'auto value = {_get_validated_value_name(sg_name, v)};'))
        body.append((1, f'return {condition.strip()};'))
        body.append((0, '}'))
        body.append((0, f'if ( std::any_of( std::begin( {name} ), std::end( {name} ), check )'))
        body.append((0, '{'))
        body.append((1, _get_exception_text(name, f'Array contains elements that fall out of required range')))
        body.append((0, '}'))
    else:
        body.append((0, f'auto val = {_get_validated_value_name(name, v)};'))
        body.append((0, f'if ( {condition} )'))
        body.append((0, '{'))
        body.append((1, _get_exception_text(name, f'Value is not within required range')))
        body.append((0, '}'))

    return is_member, body


def _generate_validator_positive(name: str, v: dict[str, Any], p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], array_ctx: bool = False, force_getter: bool = False) -> Tuple[bool, list[(int, str)]]:
    new_v = deepcopy(v)
    new_v['validator'] = 'range'
    if p['type'] in ['real', 'f32', 'f64']:
        new_v['min'] = '0.0'
        new_v['inclusive'] = 'false'
    else:
        new_v['min'] = '1'
    return _generate_validator_range(name, new_v, p, data, ctx, array_ctx, force_getter)

def _generate_validator_nonneg(name: str, v: dict[str, Any], p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], array_ctx: bool = False, force_getter: bool = False) -> Tuple[bool, list[(int, str)]]:
    new_v = deepcopy(v)
    new_v['validator'] = 'range'
    if p['type'] in ['real', 'f32', 'f64']:
        new_v['min'] = '0.0'
    else:
        new_v['min'] = '0'
    return _generate_validator_range(name, new_v, p, data, ctx, array_ctx, force_getter)

def _generate_validator_negative(name: str, v: dict[str, Any], p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], array_ctx: bool = False, force_getter: bool = False) -> Tuple[bool, list[(int, str)]]:
    new_v = deepcopy(v)
    new_v['validator'] = 'range'
    if p['type'] in ['real', 'f32', 'f64']:
        new_v['max'] = '0.0'
        new_v['inclusive'] = 'false'
    else:
        new_v['max'] = '-1'
    return _generate_validator_range(name, new_v, p, data, ctx, array_ctx, force_getter)

def _generate_validator_nonpos(name: str, v: dict[str, Any], p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], array_ctx: bool = False, force_getter: bool = False) -> Tuple[bool, list[(int, str)]]:
    new_v = deepcopy(v)
    new_v['validator'] = 'range'
    if p['type'] in ['real', 'f32', 'f64']:
        new_v['max'] = '0.0'
    else:
        new_v['max'] = '0'
    return _generate_validator_range(name, new_v, p, data, ctx, array_ctx, force_getter)

def _generate_validator_unique(name: str, v: dict[str, Any], p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], array_ctx: bool = False, force_getter: bool = False) -> Tuple[bool, list[(int, str)]]:
    property_type : str = p['type']

    if 'is_array' not in p or not p['is_array']:
        raise Exception(f"Property '{name}': 'unique' validator may only be used with array types.")
    if 'args' in


    body: list[(int, str)] = []
    is_member : bool = force_getter

    if force_getter:
        body.append((0, f'auto {name} = {name}();'))
    if array_ctx:
        sg_name : str = _get_singular_name(name, p)
        body.append((0, f'auto predicate = []( auto const& lhs, auto const& rhs )'))
        body.append((0, '{'))
        body.append((1, f'return {_get_validated_value_name("lhs", v)} == {_get_validated_value_name("rhs", v)};'))
        body.append((0, '}'))
        body.append((0, f'std::sort( std::begin( {name} ), std::end( {name} ) );'))
        body.append((0, f'if ( std::adjacent_find( std::begin( {name} ), std::end( {name} ), predicate ) != std::end( {name} ) )'))
        body.append((0, '{'))
        body.append((1, _get_exception_text(name, 'Array contains duplicates')))
        body.append((0, '}'))
    else:
        # NOTE: currently only works for arrays with names ending in 's'
        is_member = True
        body.append((0, f'auto arr = {name}s();'))
        body.append((0, f'if ( arr.find( {name} ) != std::end( arr ) )'))
        body.append((0, '{'))
        body.append((1, _get_exception_text(name, 'Value already exists in array')))
        body.append((0, '}'))

    return is_member, body

def _generate_validator_is_pow2(name: str, v: dict[str, Any], p: dict[str, Any], data: dict[str, Any], ctx: dict[str, Any], array_ctx: bool = False, force_getter: bool = False) -> Tuple[bool, list[(int, str)]]:
    property_type : str = p['type']

    if property_type in ['string', 'path', 'settings', 'module', 'enum', 'real', 'f32', 'f64']:
        raise Exception(f"Property '{name}': 'is_pow2' validator may only be used with integer types.")

    body: list[(int, str)] = []
    is_member : bool = force_getter

    if force_getter:
        body.append((0, f'auto {name} = {name}();'))
    if array_ctx:
        sg_name : str = _get_singular_name(name, p)
        body.append((0, f'auto check = []( auto {sg_name} )'))
        body.append((0, '{'))
        body.append((1, f'auto v = {_get_validated_value_name(sg_name, v)};'))
        body.append((1, f'return v == 0 || ( v & ( v - 1 ) ) != 0;'))
        body.append((0, '}'))
        body.append((0, f'if ( std::any_of( std::begin( {name} ), std::end( {name} ), check )'))
        body.append((0, '{'))
        body.append((1, _get_exception_text(name, 'Array contains elements that are not powers of 2')))
        body.append((0, '}'))
    else:
        body.append((0, f'auto v = {_get_validated_value_name(name, v)};'))
        body.append((0, f'if ( v == 0 || ( v & ( v - 1 ) ) != 0 )'))
        body.append((0, '{'))
        body.append((1, _get_exception_text(name, 'Value is not a power of 2')))
        body.append((0, '}'))

    return is_member, body


VALIDATORS = {
    "is_set": _generate_validator_is_set,
    "nonempty": _generate_validator_nonempty,
    "range": _generate_validator_range,
    "unique": _generate_validator_unique,
    "is_pow2": _generate_validator_is_pow2,
    "negative": _generate_validator_negative,
    "positive": _generate_validator_positive,
    "nonneg": _generate_validator_nonneg,
    "nonpos": _generate_validator_nonpos
}


def _try_parse_validator(input: Any):
    if isinstance(input, dict):
        return input
    if not isinstance(input, str):
        raise Exception( "Invalid type for validator item: must be either explicit object or string representation." )

    result : dict[str, Any] = { "params": {} }
    str_repr : str = input.strip()

    result['is_post'] = str_repr[0] == '*'
    str_repr = str_repr.lstrip('*')

    tokens : list[str] = str_repr.strip().split('(', 1)
    validator_type : str = tokens[0].strip()
    result['validator'] = validator_type
    if len(tokens) > 1:
        args_str : str = tokens[1].strip()
        if args_str[-1] != ')':
            raise Exception( f"No matching closing parentheses for '{validator_type}' validator parameter list" )
        args_str = args_str[:-1].strip()
        args_tokens : list[str] = args_str.split(',')
        for arg_str in args_tokens:
            arg_tokens : list[str] = arg_str.strip().split('=', 1)
            if len(arg_tokens) != 2:
                raise Exception( f"Invalid parameter format in {validator_type}. Must be 'key=value'." )
            result['args'][arg_tokens[0].strip] = try_parse_expr(arg_tokens[1].strip())
    return result

def _preprocess_property_validator_list(p: dict[str, Any]) -> list[dict[str,Any]]:
    result = [_try_parse_validator(validator) for validator in p['requires']] if 'requires' in p and p['requires'] else []
    if 'is_required' in p and p['is_required']:
        result.append( { "validator": "is_set", "is_post": True } )
    return result

def generate_post_validate_all_body(data: dict[str,Any], ctx: dict[str,Any]) -> list[(int, str)]:
    body : list[(int, str)] = body

    for name, prop in data:
        if name.startswith('__'):
            continue
        for v in _preprocess_property_validator_list(prop):
            if 'is_post' not in v or not v['is_post']:
                continue
            validator_type : str = v['type']
            if validator_type not in VALIDATORS:
                raise Exception( f"Unknown validator type in property '{name}': {validator_type}." )
        body.extend(VALIDATORS[validator_type](name, v, prop, data, ctx, array_ctx=('is_array' in prop and prop['is_array']), force_getter=True)[1])
        body.append((0, ''))

    return body


def generate_pre_validate_property_body(name: str, p: dict[str,Any], data: dict[str,Any], ctx: dict[str,Any], array_ctx: bool = False) -> Tuple[bool, list[(int, str)]]:
    is_member : bool = False
    body : list[(int, str)] = body

    for v in _preprocess_property_validator_list(p):
        if 'is_post' in v and v['is_post']:
            continue
        validator_type : str = v['type']
        if validator_type not in VALIDATORS:
            raise Exception( f"Unknown vaidator type in propert '{name}': {validator_type}." )
        requires_member_data, part_body = VALIDATORS[validator_type](name, v, p, data, ctx, array_ctx)
        is_member = is_member or requires_member_data
        body.extend(part_body)
        body.append((0, ''))

    return is_member, body
