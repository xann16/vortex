from gen import generate
from gen_cmake import adjust_package_cmakelists
from gen_cpp_providers import generate_settings_provider
import tomllib as toml
from typing import Any
from utils import load_defs

defs = load_defs('../defs')

ctx : dict[str, Any] = {
    'defs': defs,
    'cmake': {},
    'providers': {}
}

root_path : str = '../../../libs'

for key, data in defs.items():
    generate(root_path, data, ctx)

for package_name in ctx['providers']:
    generate_settings_provider(root_path, package_name, ctx)

for package_name, data in ctx['cmake'].items():
    adjust_package_cmakelists(root_path, package_name, data)
