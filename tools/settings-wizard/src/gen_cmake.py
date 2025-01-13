import os

AUTOGEN_BEGIN = "# files added automatically using vxsw"
AUTOGEN_END = "# end of vxsw managed section"

def get_cmakelists_path(root_path: str, package_name: str):
    return os.path.normpath(os.path.join(root_path, package_name, 'CMakeLists.txt'))

def _insert_items(nls : list[str], items : list[str]) -> None:
    if nls[-1].strip():
        nls.append('\n')
    nls.append('    ' + AUTOGEN_BEGIN + '\n')
    for item in items:
        nls.append('    ' + item + '\n')
    nls.append('    ' + AUTOGEN_END + '\n')

def adjust_package_cmakelists(root_path: str, package_name: str, data: dict[str, list[str]]):
    path : str = get_cmakelists_path(root_path, package_name)    
    
    with open(path, mode='r') as fp:
        ls = fp.readlines()

    nls : list[str] = []

    mode : str | None = None
    skip : bool = False
    inserted : bool = False
    for line in ls:

        if mode is None:
            if (line.lstrip().startswith('set')):
                mode = line.split('(', 1)[-1].strip().lower()
                if mode not in ['headers', 'sources', 'tests']:
                    mode = None

        else:
            str_line = line.strip()
            if str_line == AUTOGEN_BEGIN:
                skip = True
            elif str_line == AUTOGEN_END:
                _insert_items(nls, data[mode])
                skip = False
                inserted = True
                continue
            elif str_line == ')':
                if not inserted:
                    _insert_items(nls, data[mode])
                skip = False
                inserted = False
                mode = None

        if not skip:
            nls.append(line)

    with open(path, mode='w') as fp:
        fp.writelines(nls)
