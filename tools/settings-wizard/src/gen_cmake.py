import os

AUTOGEN_COMMENT = "# files added automatically using vxsw"

def get_cmakelists_path(root_path: str, package_name: str):
    return os.path.normpath(os.path.join(root_path, package_name, 'CMakeLists.txt'))

def adjust_package_cmakelists(root_path: str, package_name: str, data: dict[str, list[str]]):
    path : str = get_cmakelists_path(root_path, package_name)    
    
    with open(path, mode='r') as fp:
        ls = fp.readlines()

    nls : list[str] = []

    mode : str | None = None
    skip = False
    for line in ls:

        if mode is None:
            if (line.lstrip().startswith('set')):
                mode = line.split('(', 1)[-1].strip().lower()
                if mode not in ['headers', 'sources', 'tests']:
                    mode = None

        else:
            str_line = line.strip()
            if str_line == AUTOGEN_COMMENT:
                skip = True
            elif str_line == ')':
                nls.append('\n')
                nls.append('    ' + AUTOGEN_COMMENT + '\n')
                for item in data[mode]:
                    nls.append('    ' + item + '\n')
                mode = None
                skip = False

        if not skip:
            nls.append(line)

    with open(path, mode='w') as fp:
        fp.writelines(nls)
