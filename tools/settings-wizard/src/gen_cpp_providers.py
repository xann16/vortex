from cpp_utils import get_class_name, get_namespace, add_include, add_blank, add_line, add_block_comment, begin_test_case, end_test_case, add_require, begin_namespace, end_namespace, begin_class, end_class, add_access_qualifier, add_dtor_declaration, add_dtor_definition, add_copy_and_move_ctor_deletes, add_method_declaration, add_method_definition
from gen_cpp import get_header_path
from gen_utils import create_file, to_pascal_case
import os
from typing import Any


def _get_provider_module_name(package_name : str) -> str:
    return f'{package_name}_settings_json_provider'


def _get_provider_namespace(package_name : str, ctx : dict[str, Any]) -> list[str]:
    return ctx['providers'][package_name][0]['__metadata__']['namespace'] + ['providers']


def get_header_path(package_name: str, namespace_path: list[str], root_path: str | None = None, ctx='cwd') -> str:
    module_name : str = _get_provider_module_name(package_name)
    path : str = os.path.join(package_name, *namespace_path, module_name + '.hpp')
    if ctx == 'include':
        return os.path.normpath(path)
    path = os.path.join('include', path)
    if ctx == 'cmake':
        return os.path.normpath(path)
    path = os.path.join(root_path if root_path else '.', package_name, path)
    if ctx == 'cwd':
        return os.path.normpath(path)

    raise RuntimeError(f"Unsupported context: '{ctx}'.")


def get_source_path(package_name: str, namespace_path: list[str], root_path: str | None = None, ctx='cwd') -> str:
    module_name : str = _get_provider_module_name(package_name)
    path : str = os.path.join('src', *namespace_path, module_name + '.hpp')
    if ctx == 'cmake':
        return os.path.normpath(path)
    path = os.path.join(root_path, package_name, path)
    if ctx == 'cwd':
        return os.path.normpath(path)

    raise RuntimeError(f"Unsupported context: '{ctx}'.")


def get_unit_test_path(package_name: str, namespace_path: list[str], root_path: str | None = None, ctx='cwd') -> str:
    module_name : str = _get_provider_module_name(package_name)
    path : str = os.path.join('tests', *namespace_path, module_name + '.hpp')
    if ctx == 'cmake':
        return os.path.normpath(path)
    path = os.path.join(root_path, package_name, path)
    if ctx == 'cwd':
        return os.path.normpath(path)

    raise RuntimeError(f"Unsupported context: '{ctx}'.")

def _add_getter_includes(ls: list[str], i: int, modules: list[Any]) -> int:
    for module_data in modules:
        i = add_include(ls, i, get_header_path(data, ctx='include'))
    return i

def _add_getter_declarations(ls: list[str], i: int, modules: list[Any]) -> int:
    for module_data in modules:
        module_name : str = module_data['__metadata__']['module']
        i = add_method_definition(ls, i, f'get_{module_name}', to_pascal_case(module_name), [('std::string const&', 'key')], is_nodiscard=True)
        i = add_method_definition(ls, i, f'get_{module_name}', to_pascal_case(module_name), [('std::string const&', 'key'), ('std::ifstream&', 'is')], is_nodiscard=True)
        i = add_method_definition(ls, i, f'get_{module_name}', to_pascal_case(module_name), [('std::string const&', 'key'), ('std::filestream::path const&', 'path')], is_nodiscard=True)
        i = add_method_definition(ls, i, f'get_{module_name}', to_pascal_case(module_name), [('std::filestream::path const&', 'path')], is_nodiscard=True)
        add_blank(ls)
    return i

def _add_getter_definitions(ls: list[str], i: int, modules: list[Any], package_name: str) -> int:
    for module_data in modules:
        module_name : str = module_data['__metadata__']['module']
        class_name : str = to_pascal_case(module_name)
        provider_class_name : str = to_pascal_case(_get_provider_module_name(package_name))

        i = add_method_definition(ls, i, f'get_{module_name}', class_name, provider_class_name, [('std::string const&', 'key')], [(0, f'return get<{class_name}>(key);')], is_nodiscard=True)
        i = add_method_definition(ls, i, f'get_{module_name}', class_name, provider_class_name, [('std::string const&', 'key'), ('std::ifstream&', 'is')], [(0, f'return get<{class_name}>(key, is);')], is_nodiscard=True)
        i = add_method_definition(ls, i, f'get_{module_name}', class_name, provider_class_name, [('std::string const&', 'key'), ('std::filestream::path const&', 'path')], [(0, f'return get<{class_name}>(key, path);')], is_nodiscard=True)
        i = add_method_definition(ls, i, f'get_{module_name}', class_name, provider_class_name, [('std::filestream::path const&', 'path')], [(0, f'return get<{class_name}>(path);')], is_nodiscard=True)
        add_blank(ls)
    return i

def generate_provider_header_file(root_path: str, package_name: str, ctx: dict[str, Any]) -> str:
    namespace : list[str] = _get_provider_namespace(package_name, ctx)
    path : str = get_header_path(package_name, namespace, root_path=root_path)
    class_name : str = to_pascal_case(_get_provider_module_name(package_name))

    ls : list[str] = []
    i : int = 0

    i = add_block_comment(ls, i, '', 'Header file auto-generated by VORTEX SETTINGS WIZARD', '', 'TODO: Just testing', '')
    add_blank(ls)

    i = add_line(ls, i, '#pragma once')
    add_blank(ls)

    i = add_include(ls, i, 'core/settings/json/settings_provider.hpp')
    i = _add_getter_includes(ls, i, ctx['providers'][package_name])
    add_blank(ls)

    i = begin_namespace(ls, i, *namespace)
    add_blank(ls)
    i = begin_class(ls, i, class_name)

    i = add_access_qualifier(ls, i, 'public:')
    i = add_line(ls, i, 'using vortex::core::settings::SettingsProvider::SettingsProvider')
    add_blank(ls)
    i = add_copy_and_move_ctor_deletes(ls, i, class_name)
    add_blank(ls)
    i = add_dtor_declaration(ls, i, class_name, is_noexcept=True, is_default=True)
    add_blank(ls)

    i = add_access_qualifier(ls, i, 'public:')
    i = _add_getter_declarations(ls, i, ctx['providers'][package_name])

    i = end_class(ls, i, class_name)
    add_blank(ls)
    i = end_namespace(ls, i, *namespace)

    create_file(path, ls)

    return path


def generate_provider_source_file(root_path: str, package_name: str, ctx: dict[str, Any]) -> str:
    namespace : list[str] = _get_provider_namespace(package_name, ctx)
    path : str = get_source_path(package_name, namespace, root_path=root_path)
    class_name : str = to_pascal_case(_get_provider_module_name(package_name))

    ls : list[str] = []
    i : int = 0

    i = add_block_comment(ls, i,'', 'Source file auto-generated by VORTEX SETTINGS WIZARD', '', 'TODO: Just testing', '')
    add_blank(ls)

    i = add_include(ls, i, get_header_path(data, ctx='include'))
    add_blank(ls)

    i = begin_namespace(ls, i, *namespace)
    add_blank(ls)

    i = add_access_qualifier(ls, i, 'public')
    i = _add_getter_definitions(ls, i, ctx['providers'][package_name], package_name)

    add_blank(ls)
    i = end_namespace(ls, i, *namespace)

    create_file(path, ls)

    return path


def generate_provider_unit_test_file(root_path: str, package_name: str, ctx: dict[str, Any]) -> str:
    namespace : list[str] = _get_provider_namespace(package_name, ctx)
    path : str = get_unit_test_path(package_name, namespace, root_path=root_path)
    class_name : str = to_pascal_case(_get_provider_module_name(package_name))

    ls : list[str] = []
    i : int = 0

    i = add_block_comment(ls, i,'', 'Unit test source file auto-generated by VORTEX SETTINGS WIZARD', '', 'TODO: Just testing', '')
    add_blank(ls)
    i = add_include(ls, i, 'catch2/catch_test_macros.hpp', is_quoted=False)
    i = add_include(ls, i, get_header_path(data, ctx='include'))

    add_blank(ls)

    i = begin_test_case(ls, i, f'{class_name} - Sample Test', 'sample')
    i = add_line(ls, i, '::'.join(namespace) + '::' + class_name + '();')
    add_blank(ls)
    i = add_require(ls, i, 'true')
    i = end_test_case(ls, i)

    create_file(path, ls)

    return path


def populate_cmake_data(package_name: str, ctx : dict[str, Any]) -> None:
    namespace : list[str] = _get_provider_namespace(package_name, ctx)

    if package_name not in ctx['cmake']:
        ctx['cmake'][package_name] : dict[str, dict[str, Any]] = {}
    pkg_data = ctx['cmake'][package_name]

    if 'headers' not in pkg_data:
        pkg_data['headers'] : dict[str, Any] = []
    pkg_data['headers'].append(get_header_path(package_name, namespace, ctx='cmake'))

    if 'sources' not in pkg_data:
        pkg_data['sources'] : dict[str, Any] = []
    pkg_data['sources'].append(get_source_path(package_name, namespace, ctx='cmake'))

    if 'tests' not in pkg_data:
        pkg_data['tests'] : dict[str, Any] = []
    pkg_data['tests'].append(get_unit_test_path(package_name, namespace, ctx='cmake'))


def generate_settings_provider(root_path: str, package_name: str, ctx: dict[str, Any]) -> None:
    sp_hdr_path : str = generate_provider_header_file(root_path, package_name, ctx)
    sp_src_path : str = generate_provider_source_file(root_path, package_name, ctx)
    sp_tst_file : str = generate_provider_unit_test_file(root_path, package_name, ctx)

    print(sp_hdr_path)
    print(sp_src_path)
    print(sp_tst_path)

    populate_cmake_data(package_name, ctx)
