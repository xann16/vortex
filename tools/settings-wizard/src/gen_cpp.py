from cpp_utils import add_include, add_blank, add_line, add_block_comment, begin_test_case, end_test_case, add_require, begin_namespace, end_namespace, begin_class, end_class
import os
from typing import Any

def _create_file(path: str, content: list[str]):
    dir_path = os.path.dirname(path)
    os.makedirs(dir_path, exist_ok=True)
    with open(path, mode='w', encoding='utf-8') as fp:
        fp.writelines(content)

def _to_pascal_case(snake_name: str):
    tokens = snake_name.lower().split('_')
    return ''.join(t.title() for t in tokens)

def get_class_name(data: dict[str, Any], suffix: str = ''):
    snake_name = data['__metadata__']['module'] + (f'_{suffix}' if suffix else '')
    return _to_pascal_case(snake_name)

def get_namespace(data: dict[str, Any]):
    package_name : str = data['__metadata__']['package'].lstrip('*')
    namespace_path : list[str] = data['__metadata__']['namespace']
    return ['vortex'] + [package_name] + namespace_path

def get_header_path(data: dict[str, Any], suffix: str = '', root_path: str | None = None, ctx='cwd'):
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

def get_source_path(data: dict[str, Any], suffix: str = '', root_path: str | None = None, ctx='cwd'):
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

def get_unit_test_path(data: dict[str, Any], suffix: str = '', root_path: str | None = None, ctx='cwd'):
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

def populate_cmake_data(data: dict[str, Any], ctx : dict[str, Any]):
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

def generate_cpp(root_path: str, data: dict[str, Any], ctx: dict[str, Any]) -> None:

    dyn_hdr_path : str = generate_dynamic_header_file(root_path, data, ctx)
    dyn_src_path : str = generate_dynamic_source_file(root_path, data, ctx)
    dyn_tst_path : str = generate_dynamic_unit_test_file(root_path, data, ctx)

    print(dyn_hdr_path)
    print(dyn_src_path)
    print(dyn_tst_path)

    populate_cmake_data(data, ctx)

def generate_dynamic_header_file(root_path: str, data: dict[str, Any], ctx: dict[str, Any]) -> str:
    path : str = get_header_path(data, root_path=root_path)
    class_name : str = get_class_name(data)
    namespace : list[str] = get_namespace(data)
    
    ls : list[str] = []
    i = 0

    i = add_block_comment(ls, i, '', 'Header file auto-generated by VORTEX SETTINGS WIZARD', '', 'TODO: Just testing', '')
    add_blank(ls)

    i = begin_namespace(ls, i, *namespace)
    add_blank(ls)
    i = begin_class(ls, i, class_name)
    i = add_block_comment(ls, i, 'TODO')
    i = end_class(ls, i, class_name)
    add_blank(ls)
    i = end_namespace(ls, i, *namespace)

    _create_file(path, ls)

    return path

def generate_dynamic_source_file(root_path: str, data: dict[str, Any], ctx: dict[str, Any]) -> str:
    path : str = get_source_path(data, root_path=root_path)
    class_name : str = get_class_name(data)
    namespace : str = get_namespace(data)

    ls : list[str] = []
    i = 0

    i = add_block_comment(ls, i,'', 'Header file auto-generated by VORTEX SETTINGS WIZARD', '', 'TODO: Just testing', '')
    add_blank(ls)

    i = add_include(ls, i, get_header_path(data, ctx='include'))
    add_blank(ls)

    i = begin_namespace(ls, i, *namespace)
    add_blank(ls)
    i = add_block_comment(ls, i, 'TODO')
    add_blank(ls)
    i = end_namespace(ls, i, *namespace)

    _create_file(path, ls)

    return path

def generate_dynamic_unit_test_file(root_path: str, data: dict[str, Any], ctx: dict[str, Any]) -> str:
    path : str = get_unit_test_path(data, root_path=root_path)
    class_name : str = get_class_name(data)
    namespace : str = get_namespace(data)

    ls : list[str] = []
    i = 0

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

    _create_file(path, ls)

    return path
