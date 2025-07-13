#! /usr/bin/python

#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

import os
import sys
import multiprocessing
import platform
import shutil
import json
import subprocess
import re
import glob

config_info_keyword = "ubinos_config_info {"
config_info_make_dir_key = "make_dir"
config_info_name_base_key = "name_base"
config_info_build_type_key = "build_type"

def print_help():
    print("===============================================================================")
    print("Usage:")
    print("    python %s system_name" % (sys.argv[0]))
    print("    python %s cpu_count" % (sys.argv[0]))
    print("    python %s get_start_command_for_cmake" % (sys.argv[0]))
    print("    python %s get_open_command_for_cmake" % (sys.argv[0]))
    print("    python %s get_python_venv_activate_command_for_cmake <venv path>" % (sys.argv[0]))
    print("    python %s get_python_venv_activate_command <venv path>" % (sys.argv[0]))
    print("    python %s realpath <file name>" % (sys.argv[0]))
    print("    python %s is_existing_path <path name>" % (sys.argv[0]))
    print("    python %s is_removable_dir <output dir>" % (sys.argv[0]))
    print("    python %s which <executable file name>" % (sys.argv[0]))
    print("    python %s copy_file <src> <dst>"% (sys.argv[0]))
    print("    python %s getuid" % (sys.argv[0]))
    print("    python %s getgid" % (sys.argv[0]))
    print("    python %s is_python3" % (sys.argv[0]))
    print("    python %s refine_gdbscript <source file name> <destination file name> <app file name>" % (sys.argv[0]))
    print("    python %s refine_linkscript <source file name> <destination file name> <memory type> <origin> <length>" % (sys.argv[0]))
    print("    python %s parse_mapfile_get_value_gcc <source file name> <symbol>" % (sys.argv[0]))
    print("    python %s parse_mapfile_get_value_local_gcc <source file name> <symbol>" % (sys.argv[0]))
    print("    python %s parse_mapfile_get_value_local_llvm <source file name> <symbol>" % (sys.argv[0]))
    print("    python %s show_mapfile_info <source file name> <toolchain type>" % (sys.argv[0]))
    print("    python %s replace_string <source file name> <destination file name> <old string> <new string>" % (sys.argv[0]))
    print("    python %s get_make_dir_from_config_file <config file name>" % (sys.argv[0]))
    print("    python %s get_name_base_from_config_file <config file name>" % (sys.argv[0]))
    print("    python %s get_build_type_from_config_file <config file name>" % (sys.argv[0]))
    print("    python %s mkdir_p <directory path>" % (sys.argv[0]))
    print("    python %s rm_rf <path pattern>" % (sys.argv[0]))
    print("    python %s mv_f <source pattern> <destination>" % (sys.argv[0]))
    print("    python %s cp_f <source pattern> <destination>" % (sys.argv[0]))
    print("===============================================================================")

def system_name():
    # 'Linux', 'Windows', 'Darwin'
    print(platform.system())

def cpu_count():
    print(multiprocessing.cpu_count())

def get_start_command_for_cmake():
    if platform.system() == "Windows":
        print("cmd /c start \"\"")
    elif platform.system() == "Linux":
        print("xterm;-hold;-e")
    elif platform.system() == "Darwin":
        cmd_dir = os.path.dirname(os.path.abspath(__file__))
        cmd_path = os.path.join(cmd_dir, "start.applescript")
        print("osascript;%s;\"`pwd`\"" % cmd_path)

def get_open_command_for_cmake():
    if platform.system() == "Windows":
        print("cmd /c start \"\"")
    elif platform.system() == "Linux":
        print("xdg-open")
    elif platform.system() == "Darwin":
        print("open")

def get_python_venv_activate_command_for_cmake(venvpath):
    result = None

    if platform.system() == "Windows":
        result = f"{venvpath}\\Scripts\\activate.bat"
        result = result.replace('/', '\\')
    elif platform.system() == "Linux" or platform.system() == "Darwin":
        result = f". {venvpath}/bin/activate"

    print(result)

def get_python_venv_activate_command(venvpath):
    result = None

    if platform.system() == "Windows":
        result = f"{venvpath}\\Scripts\\activate.bat"
        result = result.replace('/', '\\')
    elif platform.system() == "Linux" or platform.system() == "Darwin":
        result = f". {venvpath}/bin/activate"

    print(result)

def realpath(fname):
    print(os.path.realpath(fname))

def is_existing_path(pname):
    if os.path.exists(pname):
        print("1")
    else:
        print("0")

def is_removable_dir(output_dir):
    if os.path.exists(output_dir) and os.path.isdir(output_dir) and output_dir != "/":
        print("1")
    else:
        print("0")

def which(ename):
    print(shutil.which(ename))

def copy_file(src, dst):
    if os.path.isdir(dst):
        dst = os.path.join(dst, os.path.split(src)[1])
    shutil.copyfile(src, dst)

def copy_tree(src, dst):
    if os.path.isdir(dst):
        dst = os.path.join(dst, os.path.split(src)[1])
    shutil.copytree(src, dst)

def getuid():
    print(os.getuid())

def getgid():
    print(os.getgid())

def is_python3():
    if sys.version_info.major == 3:
        print("1")
    else:
        print("0")

def refine_gdbscript(sfn, dfn, afn):
    oldstr = "<size_of_app.bin>"
    newstr = ("0x%x" % os.stat(afn).st_size)
    replace_string(sfn, dfn, oldstr, newstr)

def refine_linkscript(sfn, dfn, memtype, origin, length):
    oldstr = ("<%s_ORIGIN>" % memtype)
    newstr = ("%s" % origin)
    replace_string(sfn, dfn, oldstr, newstr)
    oldstr = ("<%s_LENGTH>" % memtype)
    newstr = ("%s" % length)
    replace_string(sfn, dfn, oldstr, newstr)

def file_open(fname, mode):
    if sys.version_info.major >= 3:
        return open(fname, mode, encoding="UTF-8")
    else:
        return open(fname, mode)

def replace_string(sfn, dfn, oldstr, newstr):
    if not os.path.exists(sfn):
        print("Source file does not exist: %s" % sfn)
        return
    
    sf = file_open(sfn, 'r')
    lines = sf.readlines()
    sf.close()

    df = file_open(dfn, 'w')
    for line in lines:
        if -1 != line.find(oldstr):
            newline = line.replace(oldstr, newstr)
            df.write(newline)
        else:
            df.write(line)
    df.close()

def parse_mapfile_get_value_gcc(sfn, symbol):
    sf = file_open(sfn, 'r')
    lines = sf.readlines()
    sf.close()

    for line in lines:
        if -1 != line.find(symbol + " ="):
            return int(line.split()[0], 16)

    for line in lines:
        if -1 != line.find(symbol + "\n"):
            return int(line.split()[0], 16)

    return 0

def parse_mapfile_get_value_local_gcc(sfn, symbol):
    sf = file_open(sfn, 'r')
    lines = sf.readlines()
    sf.close()

    for line in lines:
        if line.startswith(symbol + " "):
            addr = int(line.split()[1], 16)
            size = int(line.split()[2], 16)
            limit = addr + size
            return addr, limit, size

    return 0, 0, 0

def parse_mapfile_get_value_local_llvm(sfn, symbol):
    sf = file_open(sfn, 'r')
    lines = sf.readlines()
    sf.close()

    for line in lines:
        if -1 != line.find(symbol + "\n"):
            addr = int(line.split()[0], 16)
            size = int(line.split()[1], 16)
            limit = addr + size
            return addr, limit, size

    return 0, 0, 0

def show_mapfile_info_gcc(sfn):
    print("")
    print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__entry_address__")
    print("entry address                = 0x%08x (%12d)" % (addr, addr))
    print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__isr_vector_start__")
    limit = parse_mapfile_get_value_gcc(sfn, "__isr_vector_end__")
    size = parse_mapfile_get_value_gcc(sfn, "__isr_vector_size__")
    print("isr vector start             = 0x%08x (%12d)" % (addr, addr))
    print("isr vector end               = 0x%08x (%12d)" % (limit, limit))
    print("isr vector size              = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr2 = parse_mapfile_get_value_gcc(sfn, "__relocated_isr_vector_start__")
    limit2 = parse_mapfile_get_value_gcc(sfn, "__relocated_isr_vector_end__")
    size2 = parse_mapfile_get_value_gcc(sfn, "__relocated_isr_vector_size__")
    if addr != addr2 or limit != limit2 or size != size2:
        print("relocated isr vector start   = 0x%08x (%12d)" % (addr2, addr2))
        print("relocated isr vector end     = 0x%08x (%12d)" % (limit2, limit2))
        print("relocated isr vector size    = 0x%08x (%12d) bytes" % (size2, size2))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__text_start__")
    limit = parse_mapfile_get_value_gcc(sfn, "__text_end__")
    size = parse_mapfile_get_value_gcc(sfn, "__text_size__")
    print("text start                   = 0x%08x (%12d)" % (addr, addr))
    print("text end                     = 0x%08x (%12d)" % (limit, limit))
    print("text size                    = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__data_start__")
    limit = parse_mapfile_get_value_gcc(sfn, "__data_end__")
    size = parse_mapfile_get_value_gcc(sfn, "__data_size__")
    print("data start                   = 0x%08x (%12d)" % (addr, addr))
    print("data end                     = 0x%08x (%12d)" % (limit, limit))
    print("data size                    = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__bss_start__")
    limit = parse_mapfile_get_value_gcc(sfn, "__bss_end__")
    size = parse_mapfile_get_value_gcc(sfn, "__bss_size__")
    print("bss start                    = 0x%08x (%12d)" % (addr, addr))
    print("bss end                      = 0x%08x (%12d)" % (limit, limit))
    print("bss size                     = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr = parse_mapfile_get_value_gcc(sfn, "_heap_base__")
    limit = parse_mapfile_get_value_gcc(sfn, "__heap_limit__")
    size = parse_mapfile_get_value_gcc(sfn, "__heap_size__")
    print("heap base                    = 0x%08x (%12d)" % (addr, addr))
    print("heap limit                   = 0x%08x (%12d)" % (limit, limit))
    print("heap size                    = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__stack_top__")
    limit = parse_mapfile_get_value_gcc(sfn, "__stack_limit__")
    size = parse_mapfile_get_value_gcc(sfn, "__stack_size__")
    print("stack limit                  = 0x%08x (%12d)" % (limit, limit))
    print("stack top                    = 0x%08x (%12d)" % (addr, addr))
    print("stack size                   = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__flash_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__flash_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__flash_usage__")
    if size > 0:
        print("flash start                  = 0x%08x (%12d)      " % (addr, addr))
        print("flash size                   = 0x%08x (%12d) bytes" % (size, size))
        print("flash usage                  = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__flash2_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__flash2_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__flash2_usage__")
    if size > 0:
        print("flash2 start                 = 0x%08x (%12d)      " % (addr, addr))
        print("flash2 size                  = 0x%08x (%12d) bytes" % (size, size))
        print("flash2 usage                 = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__flash3_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__flash3_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__flash3_usage__")
    if size > 0:
        print("flash3 start                 = 0x%08x (%12d)      " % (addr, addr))
        print("flash3 size                  = 0x%08x (%12d) bytes" % (size, size))
        print("flash3 usage                 = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__flash4_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__flash4_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__flash4_usage__")
    if size > 0:
        print("flash4 start                 = 0x%08x (%12d)      " % (addr, addr))
        print("flash4 size                  = 0x%08x (%12d) bytes" % (size, size))
        print("flash4 usage                 = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__flash5_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__flash5_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__flash5_usage__")
    if size > 0:
        print("flash5 start                 = 0x%08x (%12d)      " % (addr, addr))
        print("flash5 size                  = 0x%08x (%12d) bytes" % (size, size))
        print("flash5 usage                 = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__flash6_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__flash6_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__flash6_usage__")
    if size > 0:
        print("flash6 start                 = 0x%08x (%12d)      " % (addr, addr))
        print("flash6 size                  = 0x%08x (%12d) bytes" % (size, size))
        print("flash6 usage                 = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__flash7_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__flash7_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__flash7_usage__")
    if size > 0:
        print("flash7 start                 = 0x%08x (%12d)      " % (addr, addr))
        print("flash7 size                  = 0x%08x (%12d) bytes" % (size, size))
        print("flash7 usage                 = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__ram_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__ram_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__ram_static_usage__")
    if size > 0:
        print("ram start                    = 0x%08x (%12d)      " % (addr, addr))
        print("ram size                     = 0x%08x (%12d) bytes" % (size, size))
        print("ram static usage             = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__ram2_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__ram2_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__ram2_static_usage__")
    if size > 0:
        print("ram2 start                   = 0x%08x (%12d)      " % (addr, addr))
        print("ram2 size                    = 0x%08x (%12d) bytes" % (size, size))
        print("ram2 static usage            = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__ram3_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__ram3_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__ram3_static_usage__")
    if size > 0:
        print("ram3 start                   = 0x%08x (%12d)      " % (addr, addr))
        print("ram3 size                    = 0x%08x (%12d) bytes" % (size, size))
        print("ram3 static usage            = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__ram4_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__ram4_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__ram4_static_usage__")
    if size > 0:
        print("ram4 start                   = 0x%08x (%12d)      " % (addr, addr))
        print("ram4 size                    = 0x%08x (%12d) bytes" % (size, size))
        print("ram4 static usage            = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__ram5_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__ram5_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__ram5_static_usage__")
    if size > 0:
        print("ram5 start                   = 0x%08x (%12d)      " % (addr, addr))
        print("ram5 size                    = 0x%08x (%12d) bytes" % (size, size))
        print("ram5 static usage            = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__ram6_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__ram6_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__ram6_static_usage__")
    if size > 0:
        print("ram6 start                   = 0x%08x (%12d)      " % (addr, addr))
        print("ram6 size                    = 0x%08x (%12d) bytes" % (size, size))
        print("ram6 static usage            = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "__ram7_start__")
    size = parse_mapfile_get_value_gcc(sfn, "__ram7_size__")
    usage = parse_mapfile_get_value_gcc(sfn, "__ram7_static_usage__")
    if size > 0:
        print("ram7 start                   = 0x%08x (%12d)      " % (addr, addr))
        print("ram7 size                    = 0x%08x (%12d) bytes" % (size, size))
        print("ram7 static usage            = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    addr = parse_mapfile_get_value_gcc(sfn, "  _SEGGER_RTT")
    if addr > 0:
        print("SEGGER RTT CB address        = 0x%08x (%12d)" % (addr, addr))
        print("")

    print("")

def show_mapfile_info_local_gcc(sfn):
    print("")
    print("")

    addr, limit, size = parse_mapfile_get_value_local_gcc(sfn, ".text")
    print("text start                   = 0x%08x (%12d)" % (addr, addr))
    print("text end                     = 0x%08x (%12d)" % (limit, limit))
    print("text size                    = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr, limit, size = parse_mapfile_get_value_local_gcc(sfn, ".rodata")
    print("data_const start             = 0x%08x (%12d)" % (addr, addr))
    print("data_const end               = 0x%08x (%12d)" % (limit, limit))
    print("data_const size              = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr, limit, size = parse_mapfile_get_value_local_gcc(sfn, ".data")
    print("data start                   = 0x%08x (%12d)" % (addr, addr))
    print("data end                     = 0x%08x (%12d)" % (limit, limit))
    print("data size                    = 0x%08x (%12d) bytes" % (size, size))
    print("")

    print("")

def show_mapfile_info_local_llvm(sfn):
    print("")
    print("")

    addr, limit, size = parse_mapfile_get_value_local_llvm(sfn, "__text")
    print("text start                   = 0x%08x (%12d)" % (addr, addr))
    print("text end                     = 0x%08x (%12d)" % (limit, limit))
    print("text size                    = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr, limit, size = parse_mapfile_get_value_local_llvm(sfn, "__got")
    print("data_const start             = 0x%08x (%12d)" % (addr, addr))
    print("data_const end               = 0x%08x (%12d)" % (limit, limit))
    print("data_const size              = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr, limit, size = parse_mapfile_get_value_local_llvm(sfn, "__data")
    print("data start                   = 0x%08x (%12d)" % (addr, addr))
    print("data end                     = 0x%08x (%12d)" % (limit, limit))
    print("data size                    = 0x%08x (%12d) bytes" % (size, size))
    print("")

    print("")

def show_mapfile_info(sfn, type):
    if (type == "gcc"):
        show_mapfile_info_gcc(sfn)
    elif (type == "local_gcc"):
        show_mapfile_info_local_gcc(sfn)
    elif (type == "local_llvm"):
        show_mapfile_info_local_llvm(sfn)

def get_make_dir_from_config_file(config_file_path):
    config_info = None

    with file_open(config_file_path, 'r') as file:
        try:
            lines = file.readlines()
            for line in lines:
                k_idx = line.find(config_info_keyword)
                if k_idx > -1:
                    k_len = len(config_info_keyword)
                    config_info_string = line[k_idx + k_len - 1:]
                    config_info = json.loads(config_info_string)
                    break
        except Exception as e:
            print('Exception occurred.', e)

        file.close()

    if config_info != None and config_info_make_dir_key in config_info:
        print(config_info[config_info_make_dir_key])
    else:
        print("")

def get_name_base_from_config_file(config_file_path):
    config_info = None

    with file_open(config_file_path, 'r') as file:
        try:
            lines = file.readlines()
            for line in lines:
                k_idx = line.find(config_info_keyword)
                if k_idx > -1:
                    k_len = len(config_info_keyword)
                    config_info_string = line[k_idx + k_len - 1:]
                    config_info = json.loads(config_info_string)
                    break
        except Exception as e:
            print('Exception occurred.', e)

        file.close()

    if config_info != None and config_info_name_base_key in config_info:
        print(config_info[config_info_name_base_key])
    else:
        print("")

def get_build_type_from_config_file(config_file_path):
    config_info = None

    with file_open(config_file_path, 'r') as file:
        try:
            lines = file.readlines()
            for line in lines:
                k_idx = line.find(config_info_keyword)
                if k_idx > -1:
                    k_len = len(config_info_keyword)
                    config_info_string = line[k_idx + k_len - 1:]
                    config_info = json.loads(config_info_string)
                    break
        except Exception as e:
            print('Exception occurred.', e)

        file.close()

    if config_info != None and config_info_build_type_key in config_info:
        print(config_info[config_info_build_type_key])
    else:
        print("")

def mkdir_p(path_str: str):
    """안전하게 디렉토리를 생성하는 함수 (mkdir -p와 유사)"""
    path_str = path_str.strip()
    try:
        path = os.path.normpath(path_str)
        os.makedirs(path, exist_ok=True)
    except Exception as e:
        print(f'Failed to create directory: {e}', file=sys.stderr)
        sys.exit(1)
# 사용 예:
# mkdir_p("build/output")

def rm_rf(patterns: str):
    """안전한 rm -rf 구현: 공백으로 구분된 glob 패턴들을 사용해 경로 제거"""

    patterns = patterns.strip()
    if not patterns:
        print("Error: Empty pattern provided", file=sys.stderr)
        sys.exit(1)

    pattern_list = patterns.split()
    for pattern in pattern_list:
        if '**' in pattern:
            print(f"Recursive glob patterns (**) are not allowed: {pattern}", file=sys.stderr)
            sys.exit(1)

    dangerous_patterns = []
    if platform.system() == 'Windows':
        dangerous_patterns = ['C:\\Windows']
    else:
        dangerous_patterns = [
            '/bin', '/usr', '/etc', '/root',
            '/*', os.path.expanduser('~/*')
        ]

    current_dir = os.getcwd()
    paths = []

    for pattern in pattern_list:
        if pattern.startswith('~/'):
            pattern = os.path.expanduser(pattern)

        abs_pattern = os.path.abspath(pattern)
        for dangerous in dangerous_patterns:
            if abs_pattern.startswith(os.path.abspath(dangerous)):
                print(f'Dangerous pattern rejected: {pattern}', file=sys.stderr)
                sys.exit(1)

        try:
            rel_path = os.path.relpath(abs_pattern, current_dir)
            if rel_path.startswith('..') and rel_path.count('..') > 3:
                print(f'Suspicious pattern rejected: {pattern}', file=sys.stderr)
                sys.exit(1)
        except ValueError:
            pass

        if any(c in pattern for c in ['*', '?', '[']):
            paths += glob.glob(pattern, recursive=False)
        else:
            paths.append(pattern)

    paths = sorted(set(paths), key=len, reverse=True)

    removed_count = 0
    error_count = 0

    for path in paths:
        abs_path = os.path.abspath(path)
        for dangerous in dangerous_patterns:
            if abs_path.startswith(os.path.abspath(dangerous)):
                print(f'Dangerous expanded path rejected: {path}', file=sys.stderr)
                sys.exit(1)

        try:
            if os.path.lexists(path):
                if os.path.isdir(path) and not os.path.islink(path):
                    shutil.rmtree(path)
                else:
                    os.remove(path)
                removed_count += 1
        except FileNotFoundError:
            pass
        except PermissionError:
            print(f'Permission denied: {path}', file=sys.stderr)
            error_count += 1
        except Exception as e:
            print(f'Failed to remove {path}: {e}', file=sys.stderr)
            error_count += 1

    if removed_count > 0:
        print(f'Removed {removed_count} items', file=sys.stderr)
    if error_count > 0:
        sys.exit(1)
# 사용 예:
# rm_rf("build/*")
# rm_rf("*.aux *.bbl *.blg)

def is_dangerous_path(path: str, dangerous_patterns: list) -> bool:
    abs_path = os.path.abspath(path)
    if platform.system() == 'Windows':
        return any(abs_path.lower().startswith(os.path.abspath(dangerous).lower()) 
                   for dangerous in dangerous_patterns)
    else:
        return any(abs_path.startswith(os.path.abspath(dangerous)) 
                   for dangerous in dangerous_patterns)

def mv_f(patterns: str, destination: str):
    """
    Move files with glob pattern support (similar to mv -f).
    
    Args:
        patterns: Space-separated glob patterns
        destination: Target directory or file path
    """

    # print(f"\n\n patterns {patterns} destination {destination} \n\n", file=sys.stderr)

    patterns = patterns.strip()
    if not patterns:
        print("Error: Empty patterns provided", file=sys.stderr)
        sys.exit(1)

    destination = destination.strip()
    if not destination:
        print("Error: Empty destination provided", file=sys.stderr)
        sys.exit(1)

    pattern_list = patterns.split()
    for pattern in pattern_list:
        if '**' in pattern:
            print(f"Recursive glob patterns (**) are not allowed: {pattern}", file=sys.stderr)
            sys.exit(1)

    dangerous_patterns = []
    if platform.system() == 'Windows':
        dangerous_patterns = [
            'C:\\Windows', 'C:\\Program Files', 'C:\\Program Files (x86)', 'C:\\System32', 'C:\\Windows\\System32'
        ]
    else:
        dangerous_patterns = [
            '/', '/bin', '/usr', '/etc', '/root', '/var', '/sys', '/proc',
        ]

    paths = []

    for pattern in pattern_list:
        if any(c in pattern for c in ['*', '?', '[']):
            matched = glob.glob(pattern, recursive=False)
        else:
            matched = [pattern]

        for path in matched:
            abs_path = os.path.abspath(path)
            if not os.path.exists(path) and not os.path.islink(path):
                continue
            if is_dangerous_path(path, dangerous_patterns):
                print(f'Dangerous path rejected: {path}', file=sys.stderr)
                sys.exit(1)

            paths.append(path)

    paths = sorted(set(paths), key=len, reverse=True)

    done_count = 0
    error_count = 0

    dst_norm = os.path.normpath(destination)
    is_dst_dir = (
        len(paths) > 1 or
        destination.endswith(os.sep) or
        os.path.isdir(dst_norm)
    )

    if is_dst_dir:
        os.makedirs(dst_norm, exist_ok=True)

    for path in paths:
        try:
            src = os.path.normpath(path)
            target = os.path.join(dst_norm, os.path.basename(src)) if is_dst_dir else dst_norm

            if os.path.abspath(src) != os.path.abspath(target):
                # 순환 이동 방지: target이 src의 하위 디렉토리인지 확인
                try:
                    rel_path = os.path.relpath(os.path.abspath(target), os.path.abspath(src))
                    if not rel_path.startswith('..'):
                        print(f'Cannot move {src} into itself or its subdirectory', file=sys.stderr)
                        error_count += 1
                        continue
                except ValueError:
                    pass  # 다른 드라이브, 계속 진행

                if os.path.lexists(target):
                    if os.path.isdir(target) and not os.path.islink(target):
                        shutil.rmtree(target)
                    else:
                        os.remove(target)

                shutil.move(src, target)
                done_count += 1
        except FileNotFoundError:
            pass
        except PermissionError:
            print(f'Permission denied: {path}', file=sys.stderr)
            error_count += 1
        except Exception as e:
            print(f'Failed to move {path}: {e}', file=sys.stderr)
            error_count += 1

    if done_count > 0:
        print(f'Moved {done_count} items', file=sys.stderr)
    if error_count > 0:
        sys.exit(1)
# 사용 예:
# mv_f("build/*.o", "build/obj")

def cp_f(patterns: str, destination: str):
    """
    Copy files with glob pattern support (similar to cp -f).
    
    Args:
        patterns: Space-separated glob patterns
        destination: Target directory or file path
    """

    # print(f"\n\n patterns {patterns} destination {destination} \n\n", file=sys.stderr)

    patterns = patterns.strip()
    if not patterns:
        print("Error: Empty patterns provided", file=sys.stderr)
        sys.exit(1)

    destination = destination.strip()
    if not destination:
        print("Error: Empty destination provided", file=sys.stderr)
        sys.exit(1)

    pattern_list = patterns.split()
    for pattern in pattern_list:
        if '**' in pattern:
            print(f"Recursive glob patterns (**) are not allowed: {pattern}", file=sys.stderr)
            sys.exit(1)

    dangerous_patterns = []
    if platform.system() == 'Windows':
        dangerous_patterns = [
            'C:\\Windows', 'C:\\Program Files', 'C:\\Program Files (x86)', 'C:\\System32', 'C:\\Windows\\System32'
        ]
    else:
        dangerous_patterns = [
            '/', '/bin', '/usr', '/etc', '/root', '/var', '/sys', '/proc',
        ]

    paths = []

    for pattern in pattern_list:
        if any(c in pattern for c in ['*', '?', '[']):
            matched = glob.glob(pattern, recursive=False)
        else:
            matched = [pattern]

        for path in matched:
            abs_path = os.path.abspath(path)
            if not os.path.exists(path) and not os.path.islink(path):
                continue
            if is_dangerous_path(path, dangerous_patterns):
                print(f'Dangerous path rejected: {path}', file=sys.stderr)
                sys.exit(1)

            paths.append(path)

    paths = sorted(set(paths), key=len, reverse=True)

    done_count = 0
    error_count = 0

    dst_norm = os.path.normpath(destination)
    is_dst_dir = (
        len(paths) > 1 or
        destination.endswith(os.sep) or
        os.path.isdir(dst_norm)
    )

    if is_dst_dir:
        os.makedirs(dst_norm, exist_ok=True)

    for path in paths:
        try:
            src = os.path.normpath(path)
            target = os.path.join(dst_norm, os.path.basename(src)) if is_dst_dir else dst_norm

            if os.path.abspath(src) != os.path.abspath(target):
                # 순환 복사 방지: target이 src의 하위 디렉토리인지 확인
                try:
                    rel_path = os.path.relpath(os.path.abspath(target), os.path.abspath(src))
                    if not rel_path.startswith('..'):
                        print(f'Cannot copy {src} into itself or its subdirectory', file=sys.stderr)
                        error_count += 1
                        continue
                except ValueError:
                    pass  # 다른 드라이브, 계속 진행

                if os.path.lexists(target):
                    if os.path.isdir(target) and not os.path.islink(target):
                        shutil.rmtree(target)
                    else:
                        os.remove(target)

                if os.path.isdir(src) and not os.path.islink(src):
                    if sys.version_info >= (3, 8):
                        shutil.copytree(src, target, dirs_exist_ok=True)
                    else:
                        shutil.copytree(src, target)
                else:
                    shutil.copy2(src, target)
                done_count += 1
        except FileNotFoundError:
            pass
        except PermissionError:
            print(f'Permission denied: {path}', file=sys.stderr)
            error_count += 1
        except Exception as e:
            print(f'Failed to copy {path}: {e}', file=sys.stderr)
            error_count += 1

    if done_count > 0:
        print(f'Copied {done_count} items', file=sys.stderr)
    if error_count > 0:
        sys.exit(1)
# 사용 예:
# cp_f("build/*.o", "build/obj")

if __name__ == '__main__':
    if 2 > len(sys.argv):
        print_help()
    else:
        if "system_name" == sys.argv[1]:
            system_name()
        elif "cpu_count" == sys.argv[1]:
            cpu_count()
        elif "get_start_command_for_cmake" == sys.argv[1]:
            get_start_command_for_cmake()
        elif "get_open_command_for_cmake" == sys.argv[1]:
            get_open_command_for_cmake()
        elif "get_python_venv_activate_command_for_cmake" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                venvname = sys.argv[2]
                get_python_venv_activate_command_for_cmake(venvname)
        elif "get_python_venv_activate_command" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                venvpath = sys.argv[2]
                get_python_venv_activate_command(venvpath)
        elif "realpath" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                fname = sys.argv[2]
                realpath(fname)
        elif "is_existing_path" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                pname = sys.argv[2]
                is_existing_path(pname)
        elif "is_removable_dir" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                output_dir = sys.argv[2]
                is_removable_dir(output_dir)
        elif "which" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                ename = sys.argv[2]
                which(ename)
        elif "copy_file" == sys.argv[1]:
            if 4 > len(sys.argv):
                print_help()
            else:
                copy_file(sys.argv[2], sys.argv[3])
        elif "getuid" == sys.argv[1]:
            getuid()
        elif "getgid" == sys.argv[1]:
            getgid()
        elif "is_python3" == sys.argv[1]:
            is_python3()
        elif "refine_gdbscript" == sys.argv[1]:
            if 5 > len(sys.argv):
                print_help()
            else:
                sfn = sys.argv[2]
                dfn = sys.argv[3]
                afn = sys.argv[4]
                refine_gdbscript(sfn, dfn, afn)
        elif "refine_linkscript" == sys.argv[1]:
            if 7 > len(sys.argv):
                print_help()
            else:
                sfn = sys.argv[2]
                dfn = sys.argv[3]
                memtype = sys.argv[4]
                origin = sys.argv[5]
                length = sys.argv[6]
                refine_linkscript(sfn, dfn, memtype, origin, length)
        elif "parse_mapfile_get_value_gcc" == sys.argv[1]:
            if 4 > len(sys.argv):
                print_help()
            else:
                sfn = sys.argv[2]
                symbol = sys.argv[3]
                parse_mapfile_get_value_gcc(sfn, symbol)
        elif "parse_mapfile_get_value_local_gcc" == sys.argv[1]:
            if 4 > len(sys.argv):
                print_help()
            else:
                sfn = sys.argv[2]
                symbol = sys.argv[3]
                parse_mapfile_get_value_local_gcc(sfn, symbol)
        elif "parse_mapfile_get_value_local_llvm" == sys.argv[1]:
            if 4 > len(sys.argv):
                print_help()
            else:
                sfn = sys.argv[2]
                symbol = sys.argv[3]
                parse_mapfile_get_value_local_llvm(sfn, symbol)
        elif "show_mapfile_info" == sys.argv[1]:
            if 4 > len(sys.argv):
                print_help()
            else:
                sfn = sys.argv[2]
                type = sys.argv[3]
                show_mapfile_info(sfn, type)
        elif "replace_string" == sys.argv[1]:
            if 6 > len(sys.argv):
                print_help()
            else:
                sfn = sys.argv[2]
                dfn = sys.argv[3]
                oldstr = sys.argv[4]
                newstr = sys.argv[5]
                replace_string(sfn, dfn, oldstr, newstr)
        elif "get_make_dir_from_config_file" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                fname = sys.argv[2]
                get_make_dir_from_config_file(fname)
        elif "get_name_base_from_config_file" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                fname = sys.argv[2]
                get_name_base_from_config_file(fname)
        elif "get_build_type_from_config_file" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                fname = sys.argv[2]
                get_build_type_from_config_file(fname)

        elif "mkdir_p" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                directory_path = sys.argv[2]
                mkdir_p(directory_path)
        elif "rm_rf" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                path_pattern = sys.argv[2]
                rm_rf(path_pattern)
        elif "mv_f" == sys.argv[1]:
            if 4 > len(sys.argv):
                print_help()
            else:
                source_pattern = sys.argv[2]
                destination = sys.argv[3]
                mv_f(source_pattern, destination)
        elif "cp_f" == sys.argv[1]:
            if 4 > len(sys.argv):
                print_help()
            else:
                source_pattern = sys.argv[2]
                destination = sys.argv[3]
                cp_f(source_pattern, destination)
        else:
            print_help()


