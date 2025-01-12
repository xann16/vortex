from gen_cpp import generate_cpp
from typing import Any

def generate(root_path: str, data: dict[str, Any], ctx: dict[str, dict[str, Any]]) -> None:
    generate_cpp(root_path, data, ctx)

