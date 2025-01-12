from gen import generate
import tomllib as toml
from utils import load_defs

defs = load_defs('../defs')

for key, data in defs.items():
    print(key)

    generate('../../../libs', data, defs)
    print()

