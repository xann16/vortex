from cpp_utils import get_class_name, get_namespace, add_include, add_blank, add_line, add_block_comment, begin_test_case, end_test_case, add_require, begin_namespace, end_namespace, begin_class, end_class, add_access_qualifier, add_ctor_declaration, add_ctor_definition, add_data_field
import gen_cpp_enums
from gen_cpp_properties import add_property_public_declarations, add_property_private_declarations, add_property_definitions, add_property_unit_tests
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
        ctx['cmake'][package_name] : dict[str, dict[str, Any]] = {}
    pkg_data = ctx['cmake'][package_name]

    if 'headers' not in pkg_data:
        pkg_data['headers'] : dict[str, Any] = []
    pkg_data['headers'].append(get_header_path(data, ctx='cmake'))

    if 'sources' not in pkg_data:
        pkg_data['sources'] : dict[str, Any] = []
    pkg_data['sources'].append(get_source_path(data, ctx='cmake'))

    if 'tests' not in pkg_data:
        pkg_data['tests'] : dict[str, Any] = []
    pkg_data['tests'].append(get_unit_test_path(data, ctx='cmake'))


def add_provider_data(data: dict[str, Any], ctx : dict[str, Any]) -> None:
    if 'settings' not in data['__metadata__'] or 'providers' not in data['__metadata__']['settings']:
        return

    provider_types : list[str] = data['__metadata__']['settings']['providers']
    package_name : str = data['__metadata__']['package'].lstrip('*')
    if package_name not in ctx['providers']:
        ctx['providers'][package_name] : dict[str, dict[str, Any]] = []
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

    i = add_include(ls, i, 'nlohmann/json_fwd.hpp', is_quoted=False)
    add_blank(ls)

    i = add_include(ls, i, 'core/common/types.hpp')
    i = _add_enum_includes(ls, i, data)
    if '__includes__' in data:
        i = _add_settings_includes(ls, i, data['__includes__'], ctx)
    add_blank(ls)

    i = begin_namespace(ls, i, *namespace)
    add_blank(ls)
    i = begin_class(ls, i, class_name)

    i = add_access_qualifier(ls, i, 'public')
    i = add_ctor_declaration(ls, i, class_name, [('nlohmann::json *', 'data_p')], is_explicit=True)
    add_blank(ls)

    i = add_access_qualifier(ls, i, 'public')
    i = add_property_public_declarations(ls, i, data, ctx)
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

    i = add_include(ls, i, 'nlohmann/json.hpp', is_quoted=False)
    add_blank(ls)

    i = _add_enum_includes(ls, i, data, ctx='json')
    add_blank(ls)

    i = begin_namespace(ls, i, *namespace)
    add_blank(ls)
    i = add_ctor_definition(ls, i, class_name, [('nlohmann::json *', 'data_p')], body=[(0, '// add initial validation')])
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

    i = begin_test_case(ls, i, f'{class_name} - Sample Test', 'sample')
    i = add_line(ls, i, '::'.join(namespace) + '::' + class_name + '( nullptr );')
    add_blank(ls)
    i = add_require(ls, i, 'true')
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
