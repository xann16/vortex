from cpp_utils import get_class_name, get_namespace, add_include, add_blank, add_line, add_block_comment, begin_test_case, end_test_case, add_require, begin_namespace, end_namespace, begin_class, end_class, add_access_qualifier, add_ctor_declaration, add_ctor_definition, add_method_definition, add_method_declaration, add_function_declaration, add_function_definition, add_data_field
import gen_cpp_enums
from gen_cpp_properties import add_property_public_declarations, add_property_private_declarations, add_property_definitions, add_property_unit_tests, get_stringify_body, add_pre_validate_all_definition, has_any_heap_stored_properties, get_extra_data_size_body
from gen_cpp_static import generate_cpp_static
from gen_cpp_validation import generate_post_validate_all_body
from gen_utils import create_file
import os
from typing import Any

def get_header_path(data: dict[str, Any], suffix: str = '', root_path: str | None = None, ctx='cwd') -> str:
    package_name : str = data['__metadata__']['package'].lstrip('*')
    module_name : str = data['__metadata__']['module']
    namespace_path : list[str] = data['__metadata__']['namespace']
    path = os.path.join(package_name, *namespace_path, module_name + suffix + '.hpp')
    if ctx == 'include':
        return os.path.normpath(path)
    path = os.path.join('include', path)
    if ctx == 'cmake':
        return os.path.normpath(path)
    path = os.path.join(root_path if root_path else '.', package_name, path)
    if ctx == 'cwd':
        return os.path.normpath(path)

    raise RuntimeError(f"Unsupported context: '{ctx}'.")


def get_source_path(data: dict[str, Any], suffix: str = '', root_path: str | None = None, ctx='cwd') -> str:
    package_name : str = data['__metadata__']['package'].lstrip('*')
    module_name : str = data['__metadata__']['module']
    namespace_path : list[str] = data['__metadata__']['namespace']
    path = os.path.join('src', *namespace_path, module_name + suffix + '.cpp')
    if ctx == 'cmake':
        return os.path.normpath(path)
    path = os.path.join(root_path, package_name, path)
    if ctx == 'cwd':
        return os.path.normpath(path)

    raise RuntimeError(f"Unsupported context: '{ctx}'.")


def get_unit_test_path(data: dict[str, Any], suffix: str = '', root_path: str | None = None, ctx='cwd') -> str:
    package_name : str = data['__metadata__']['package'].lstrip('*')
    module_name : str = data['__metadata__']['module']
    namespace_path : list[str] = data['__metadata__']['namespace']
    path = os.path.join('tests', *namespace_path, module_name + suffix + '.test.cpp')
    if ctx == 'cmake':
        return os.path.normpath(path)
    path = os.path.join(root_path, package_name, path)
    if ctx == 'cwd':
        return os.path.normpath(path)

    raise RuntimeError(f"Unsupported context: '{ctx}'.")


def populate_cmake_data(data: dict[str, Any], ctx : dict[str, Any]) -> None:
    package_name : str = data['__metadata__']['package'].lstrip('*')
    if package_name not in ctx['cmake']:
        ctx['cmake'][package_name] = {}
    pkg_data = ctx['cmake'][package_name]

    if 'headers' not in pkg_data:
        pkg_data['headers'] = []
    pkg_data['headers'].append(get_header_path(data, ctx='cmake'))

    if 'sources' not in pkg_data:
        pkg_data['sources'] = []
    pkg_data['sources'].append(get_source_path(data, ctx='cmake'))

    if 'tests' not in pkg_data:
        pkg_data['tests'] = []
    pkg_data['tests'].append(get_unit_test_path(data, ctx='cmake'))


def add_provider_data(data: dict[str, Any], ctx : dict[str, Any]) -> None:
    if 'settings' not in data['__metadata__'] or 'providers' not in data['__metadata__']['settings']:
        return

    provider_types : list[str] = data['__metadata__']['settings']['providers']
    package_name : str = data['__metadata__']['package'].lstrip('*')
    if package_name not in ctx['providers']:
        ctx['providers'][package_name] = []
    pkg_data = ctx['providers'][package_name]

    pkg_data.append(data)


def _add_settings_includes(ls: list[str], i: int, includes: list[dict[str, Any]], ctx: dict[str, Any]) -> int:
    for include_from in (include['from'] for include in includes):
        i = add_include(ls, i, get_header_path(ctx['defs'][include_from], ctx='include'))
    return i


def _add_enum_includes(ls: list[str], i: int, data: dict[str, Any], ctx: str = 'base'):
    for prop_data in data.values():
        if 'type' in prop_data and prop_data['type'] == 'enum':
            enum_data: dict[str, Any] = prop_data['enum']
            include_path : str = gen_cpp_enums.get_header_include_path_ext(data, enum_data, ctx)
            i = add_include(ls, i, include_path)
    return i

def generate_required_enum_classes(root_path: str, data: dict[str, Any], ctx: dict[str, Any]) -> None:
    for prop_data in data.values():
        if 'type' in prop_data and prop_data['type'] == 'enum':
            enum_data: dict[str, Any] = prop_data['enum']
            gen_cpp_enums.generate_enum(root_path, data, enum_data, ctx)


def generate_dynamic_header_file(root_path: str, data: dict[str, Any], ctx: dict[str, Any]) -> None:
    path : str = get_header_path(data, root_path=root_path)
    class_name : str = get_class_name(data)
    namespace : list[str] = get_namespace(data)

    ls : list[str] = []
    i = 0

    i = add_block_comment(ls, i, '', 'Header file auto-generated by VORTEX SETTINGS WIZARD', '', 'TODO: Just testing', '')
    add_blank(ls)

    i = add_line(ls, i, '#pragma once')
    add_blank(ls)

    i = add_include(ls, i, 'ostream', is_quoted=False)
    add_blank(ls)

    i = add_include(ls, i, 'nlohmann/json_fwd.hpp', is_quoted=False)
    add_blank(ls)

    i = add_include(ls, i, 'core/common/types.hpp')
    i = add_include(ls, i, 'core/settings/json/any_settings.hpp')
    i = _add_enum_includes(ls, i, data)
    if '__includes__' in data:
        i = _add_settings_includes(ls, i, data['__includes__'], ctx)
    add_blank(ls)

    i = begin_namespace(ls, i, *namespace)
    add_blank(ls)
    i = begin_class(ls, i, class_name)

    i = add_access_qualifier(ls, i, 'public')
    i = add_line(ls, i, f'{class_name}() noexcept = default;')
    i = add_ctor_declaration(ls, i, class_name, [('nlohmann::json *', 'data_p', None, None)], is_explicit=True)
    i = add_ctor_declaration(ls, i, class_name, [('core::settings::json::AnySettings', 's', class_name, 's.data()')], is_explicit=True, is_definition=True, body=[])
    add_blank(ls)

    i = add_access_qualifier(ls, i, 'public')
    add_blank(ls)
    i = add_method_declaration(ls, i, 'data', 'nlohmann::json *', [], body=[(0, 'return m_data_p;')], is_definition=True, is_noexcept=True, is_const=True, is_nodiscard=True)
    i = add_method_declaration(ls, i, 'is_empty', 'bool', [], body=[(0, 'return data() == nullptr;')], is_definition=True, is_noexcept=True, is_const=True, is_nodiscard=True)
    i = add_method_declaration(ls, i, 'as_any', 'core::settings::json::AnySettings', [], body=[(0, 'return core::settings::json::AnySettings{ data() };')], is_definition=True, is_noexcept=True, is_const=True, is_nodiscard=True)
    add_blank(ls)
    i = add_method_declaration(ls, i, 'update_with', f'{class_name}&', [('nlohmann::json *', 'other_data_p')])
    i = add_method_declaration(ls, i, 'update_with', f'{class_name}&', [('core::settings::json::AnySettings const&', 'other')], body=[(0, 'return update_with( other.data() );')], is_definition=True)
    i = add_method_declaration(ls, i, 'update_with', f'{class_name}&', [(f'{class_name} const&', 'other')], body=[(0, 'return update_with( other.data() );')], is_definition=True)
    add_blank(ls)
    i = add_method_declaration(ls, i, 'has_extra_data', 'bool', [], body=[(0, f'return {('true' if has_any_heap_stored_properties(data, ctx) else 'false')};')], is_const=True, is_nodiscard=True, is_noexcept=True, is_definition=True, pre_qualifiers='consteval')
    i = add_method_declaration(ls, i, 'extra_data_size', 'std::size_t', [], body=get_extra_data_size_body(data, ctx), is_const=True, is_nodiscard=True, is_definition=True)
    add_blank(ls)
    i = add_method_declaration(ls, i, 'to_string', 'std::string', [], is_const=True, is_nodiscard=True)
    i = add_method_declaration(ls, i, 'stringify', 'std::ostream&', [('std::ostream&', 'os'), ('int', 'indent_size'), ('int', 'indent_level'), ('bool', 'display_all')], is_const=True)
    add_blank(ls)
    i = add_method_declaration(ls, i, 'validate', 'void', [], is_const=True)
    add_blank(ls)
    i = add_method_declaration(ls, i, 'operator<<', 'std::ostream&', [('std::ostream&', 'os'), (f'{class_name} const&', 's')], pre_qualifiers='friend')
    add_blank(ls)
    i = add_method_declaration(ls, i, 'operator==', 'bool', [(f'{class_name} const&', 'lhs'), (f'{class_name} const&', 'rhs')], pre_qualifiers='friend')
    i = add_function_declaration(ls, i, 'operator!=', 'bool', [(f'{class_name} const&', 'lhs'), (f'{class_name} const&', 'rhs')], pre_qualifiers='friend', is_definition=True, body=[(0, 'return !( lhs == rhs );')])
    add_blank(ls)

    i = add_property_public_declarations(ls, i, data, ctx)
    add_blank(ls)

    i = add_access_qualifier(ls, i, 'private')
    i = add_property_private_declarations(ls, i, data, ctx)
    add_blank(ls)

    i = add_access_qualifier(ls, i, 'private')
    i = add_data_field(ls, i, 'nlohmann::json *', 'data_p', 'nullptr')

    i = end_class(ls, i, class_name)
    add_blank(ls)
    i = end_namespace(ls, i, *namespace)

    create_file(path, ls)


def generate_dynamic_source_file(root_path: str, data: dict[str, Any], ctx: dict[str, Any]) -> None:
    path : str = get_source_path(data, root_path=root_path)
    class_name : str = get_class_name(data)
    namespace : str = get_namespace(data)

    ls : list[str] = []
    i = 0

    i = add_block_comment(ls, i,'', 'Source file auto-generated by VORTEX SETTINGS WIZARD', '', 'TODO: Just testing', '')
    add_blank(ls)

    i = add_include(ls, i, get_header_path(data, ctx='include'))
    add_blank(ls)

    i = add_include(ls, i, 'iomanip', is_quoted=False)
    i = add_include(ls, i, 'sstream', is_quoted=False)
    add_blank(ls)

    i = add_include(ls, i, 'nlohmann/json.hpp', is_quoted=False)
    add_blank(ls)

    i = _add_enum_includes(ls, i, data, ctx='json')
    add_blank(ls)

    i = begin_namespace(ls, i, *namespace)
    add_blank(ls)
    i = add_ctor_definition(ls, i, class_name, [('nlohmann::json *', 'data_p', None, None)], body=[(0, 'pre_validate_all();')])
    add_blank(ls)

    update_body : list[(int, str)] = [
        (0, 'if (!is_empty() && other_data_p != nullptr)'),
        (0, '{'),
        (1, 'as_any().update_with( other_data_p );'),
        (1, 'pre_validate_all();'),
        (0, '}'),
        (0, 'return *this;'),
    ]
    i = add_method_definition(ls, i, 'update_with', f'{class_name}&', class_name, [('nlohmann::json *', 'other_data_p')], body=update_body)
    add_blank(ls)

    to_string_body : list[(int, str)] = [
        (0, 'auto oss = std::ostringstream{};'),
        (0, 'oss << *this;'),
        (0, 'return oss.str();')
    ]
    i = add_method_definition(ls, i, 'to_string', 'std::string', class_name, [], is_const=True, is_nodiscard=True, body=to_string_body)
    add_blank(ls)

    i = add_method_definition(ls, i, 'stringify', 'std::ostream&', class_name, [('std::ostream&', 'os'), ('int', 'indent_size'), ('int', 'indent_level'), ('bool', 'display_all')], body=get_stringify_body(data), is_const=True)
    add_blank(ls)

    i = add_method_definition(ls, i, 'validate', 'void', class_name, [], body=generate_post_validate_all_body(data, ctx), is_const=True)
    add_blank(ls)

    i = add_pre_validate_all_definition(ls, i, class_name, data, ctx)
    add_blank(ls)

    op_ln : str = 'return s.stringify( os, 2, 0, os.flags() & std::ios_base::boolalpha );'
    i = add_function_definition(ls, i, 'operator<<', 'std::ostream&', [('std::ostream&', 'os'), (f'{class_name} const&', 's')], body=[(0, op_ln)])
    add_blank(ls)

    equal_body : list[(int, str)] = [
        (0, 'return lhs.is_empty()'),
        (1, '? rhs.is_empty()'),
        (1, ': ( !rhs.is_empty() && *lhs.data() == *rhs.data() );')
    ]
    i = add_function_definition(ls, i, 'operator==', 'bool', [(f'{class_name} const&', 'lhs'), (f'{class_name} const&', 'rhs')], body=equal_body)
    add_blank(ls)

    i = add_property_definitions(ls, i, data, ctx)
    add_blank(ls)
    i = end_namespace(ls, i, *namespace)

    create_file(path, ls)


def generate_dynamic_unit_test_file(root_path: str, data: dict[str, Any], ctx: dict[str, Any]) -> None:
    path : str = get_unit_test_path(data, root_path=root_path)
    class_name : str = get_class_name(data)
    namespace : str = get_namespace(data)

    ls : list[str] = []
    i = 0

    i = add_block_comment(ls, i,'', 'Unit test source file auto-generated by VORTEX SETTINGS WIZARD', '', 'TODO: Just testing', '')
    add_blank(ls)
    i = add_include(ls, i, 'catch2/catch_test_macros.hpp', is_quoted=False)
    i = add_include(ls, i, 'catch2/matchers/catch_matchers_floating_point.hpp', is_quoted=False)
    i = add_include(ls, i, 'nlohmann/json.hpp', is_quoted=False)
    add_blank(ls)
    i = add_include(ls, i, get_header_path(data, ctx='include'))

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - basic test', 'settings')
    i = add_line(ls, i, 'nlohmann::json obj = nlohmann::json::object();')
    i = add_line(ls, i, 'auto s = ' + '::'.join(namespace) + '::' + class_name + '{ &obj };')
    add_blank(ls)
    i = add_require(ls, i, '!s.is_empty()')
    add_blank(ls)
    i = add_line(ls, i, 'auto data_p = s.data();')
    i = add_line(ls, i, 'auto anys = s.as_any();')
    add_blank(ls)
    i = add_require(ls, i, '!anys.is_empty()')
    add_blank(ls)
    i = add_line(ls, i, 'auto ss = ' + '::'.join(namespace) + '::' + class_name + '{ anys };')
    add_blank(ls)
    i = add_require(ls, i, '!ss.is_empty()')
    i = add_require(ls, i, 'data_p != nullptr')
    i = add_require(ls, i, 'obj == *data_p')
    i = add_require(ls, i, '*anys.data() == *data_p')
    i = add_require(ls, i, '*ss.data() == *data_p')
    i = end_test_case(ls, i)

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - basic empty test', 'settings')
    i = add_line(ls, i, 'auto s = ' + '::'.join(namespace) + '::' + class_name + '{};')
    add_blank(ls)
    i = add_require(ls, i, 's.is_empty()')
    add_blank(ls)
    i = add_line(ls, i, 'auto anys = s.as_any();')
    add_blank(ls)
    i = add_require(ls, i, 'anys.is_empty()')
    add_blank(ls)
    i = add_line(ls, i, 'auto ss = ' + '::'.join(namespace) + '::' + class_name + '{ anys };')
    add_blank(ls)
    i = add_require(ls, i, 'ss.is_empty()')
    i = add_require(ls, i, 's.data() == nullptr')
    i = add_require(ls, i, 'anys.data() == nullptr')
    i = add_require(ls, i, 'ss.data() == nullptr')
    i = end_test_case(ls, i)

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - conversion to string', 'settings', '.', '!mayfail')
    i = add_block_comment(ls, i, 'TODO - add conversion to string tests for generated setting classes')
    i = add_require(ls, i, 'false')
    i = end_test_case(ls, i)

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - conversion to string - display all', 'settings', '.', '!mayfail')
    i = add_block_comment(ls, i, 'TODO - add conversion to string tests for generated setting classes')
    i = add_require(ls, i, 'false')
    i = end_test_case(ls, i)

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - conversion to string - extra indent size', 'settings', '.', '!mayfail')
    i = add_block_comment(ls, i, 'TODO - add conversion to string tests for generated setting classes')
    i = add_require(ls, i, 'false')
    i = end_test_case(ls, i)

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - conversion to string - extra indent level', 'settings', '.', '!mayfail')
    i = add_block_comment(ls, i, 'TODO - add conversion to string tests for generated setting classes')
    i = add_require(ls, i, 'false')
    i = end_test_case(ls, i)

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - conversion to string for empty', 'settings', '.', '!mayfail')
    i = add_block_comment(ls, i, 'TODO - add conversion to string tests for generated setting classes')
    i = add_require(ls, i, 'false')
    i = end_test_case(ls, i)

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - merge', 'settings', '.', '!mayfail')
    i = add_block_comment(ls, i, 'TODO - add merge tests for generated setting classes')
    i = add_require(ls, i, 'false')
    i = end_test_case(ls, i)

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - merge with removal', 'settings', '.', '!mayfail')
    i = add_block_comment(ls, i, 'TODO - add merge tests for generated setting classes')
    i = add_require(ls, i, 'false')
    i = end_test_case(ls, i)

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - merge with empties', 'settings', '.', '!mayfail')
    i = add_block_comment(ls, i, 'TODO - add merge tests for generated setting classes')
    i = add_require(ls, i, 'false')
    i = end_test_case(ls, i)

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - equality and inequality operators', 'settings', '.', '!mayfail')
    i = add_block_comment(ls, i, 'TODO - add merge tests for generated setting classes')
    i = add_require(ls, i, 'false')
    i = end_test_case(ls, i)

    add_blank(ls)

    i = add_property_unit_tests(ls, i, data, ctx)
    add_blank(ls)

    create_file(path, ls)


def generate_cpp(root_path: str, data: dict[str, Any], ctx: dict[str, Any]) -> None:

    generate_dynamic_header_file(root_path, data, ctx)
    generate_dynamic_source_file(root_path, data, ctx)
    generate_dynamic_unit_test_file(root_path, data, ctx)

    generate_required_enum_classes(root_path, data, ctx)

    add_provider_data(data, ctx)
    populate_cmake_data(data, ctx)

    if 'skip_static_generation' not in data['__metadata__'] or not data['__metadata__']['skip_static_generation']:
        generate_cpp_static(root_path, data, ctx)
