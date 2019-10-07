#!/usr/bin/python

import os
import sys
import multiprocessing
from distutils.spawn import find_executable

def print_help():
    print("===============================================================================")
    print("Usage:")
    print("    %s cpu_count" % (sys.argv[0]))
    print("    %s realpath <file name>" % (sys.argv[0]))
    print("    %s is_existing_path <path name>" % (sys.argv[0]))
    print("    %s is_removable_dir <output dir>" % (sys.argv[0]))
    print("    %s which <executable file name>" % (sys.argv[0]))
    print("    %s getuid" % (sys.argv[0]))
    print("    %s getgid" % (sys.argv[0]))
    print("    %s refine_gdbscript <source file name> <destination file name> <app file name>" % (sys.argv[0]))
    print("    %s refine_linkscript <source file name> <destination file name> <memory type> <origin> <length>" % (sys.argv[0]))
    print("    %s parse_mapfile_get_value <source file name> <symbol>" % (sys.argv[0]))
    print("    %s show_mapfile_info <source file name>" % (sys.argv[0]))
    print("    %s replace_string <source file name> <destination file name> <old string> <new string>" % (sys.argv[0]))
    print("===============================================================================")

def cpu_count():
    print(multiprocessing.cpu_count())

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
    print(find_executable(ename))

def getuid():
    print(os.getuid())

def getgid():
    print(os.getgid())

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

def replace_string(sfn, dfn, oldstr, newstr):
    sf = open(sfn, 'r')
    lines = sf.readlines()
    sf.close()

    df = open(dfn, 'w')
    for line in lines:
        if -1 != line.find(oldstr):
            newline = line.replace(oldstr, newstr)
            df.write(newline)
        else:
            df.write(line)
    df.close()

def parse_mapfile_get_value(sfn, symbol):
    sf = open(sfn, 'r')
    lines = sf.readlines()
    sf.close()

    for line in lines:
        if -1 != line.find(symbol + " ="):
            return int(line.split()[0], 16)

    return 0

def show_mapfile_info(sfn):
    print("")
    print("")
    
    addr = parse_mapfile_get_value(sfn, "__entry_address__")
    print("entry address                = 0x%08x (%12d)" % (addr, addr))
    print("")

    addr = parse_mapfile_get_value(sfn, "__isr_vector_start__")
    limit = parse_mapfile_get_value(sfn, "__isr_vector_end__")
    size = parse_mapfile_get_value(sfn, "__isr_vector_size__")
    print("isr vector start             = 0x%08x (%12d)" % (addr, addr))
    print("isr vector end               = 0x%08x (%12d)" % (limit, limit))
    print("isr vector size              = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr2 = parse_mapfile_get_value(sfn, "__relocated_isr_vector_start__")
    limit2 = parse_mapfile_get_value(sfn, "__relocated_isr_vector_end__")
    size2 = parse_mapfile_get_value(sfn, "__relocated_isr_vector_size__")
    if addr != addr2 or limit != limit2 or size != size2:
        print("relocated isr vector start   = 0x%08x (%12d)" % (addr2, addr2))
        print("relocated isr vector end     = 0x%08x (%12d)" % (limit2, limit2))
        print("relocated isr vector size    = 0x%08x (%12d) bytes" % (size2, size2))
        print("")

    addr = parse_mapfile_get_value(sfn, "__text_start__")
    limit = parse_mapfile_get_value(sfn, "__text_end__")
    size = parse_mapfile_get_value(sfn, "__text_size__")
    print("text start                   = 0x%08x (%12d)" % (addr, addr))
    print("text end                     = 0x%08x (%12d)" % (limit, limit))
    print("text size                    = 0x%08x (%12d) bytes" % (size, size))
    print("")

    addr = parse_mapfile_get_value(sfn, "__data_start__")
    limit = parse_mapfile_get_value(sfn, "__data_end__")
    size = parse_mapfile_get_value(sfn, "__data_size__")
    print("data start                   = 0x%08x (%12d)" % (addr, addr))
    print("data end                     = 0x%08x (%12d)" % (limit, limit))
    print("data size                    = 0x%08x (%12d) bytes" % (size, size))
    print("")
    
    addr = parse_mapfile_get_value(sfn, "__bss_start__")
    limit = parse_mapfile_get_value(sfn, "__bss_end__")
    size = parse_mapfile_get_value(sfn, "__bss_size__")
    print("bss start                    = 0x%08x (%12d)" % (addr, addr))
    print("bss end                      = 0x%08x (%12d)" % (limit, limit))
    print("bss size                     = 0x%08x (%12d) bytes" % (size, size))
    print("")
    
    addr = parse_mapfile_get_value(sfn, "_heap_base__")
    limit = parse_mapfile_get_value(sfn, "__heap_limit__")
    size = parse_mapfile_get_value(sfn, "__heap_size__")
    print("heap base                    = 0x%08x (%12d)" % (addr, addr))
    print("heap limit                   = 0x%08x (%12d)" % (limit, limit))
    print("heap size                    = 0x%08x (%12d) bytes" % (size, size))
    print("")
    
    addr = parse_mapfile_get_value(sfn, "__stack_top__")
    limit = parse_mapfile_get_value(sfn, "__stack_limit__")
    size = parse_mapfile_get_value(sfn, "__stack_size__")
    print("stack limit                  = 0x%08x (%12d)" % (limit, limit))
    print("stack top                    = 0x%08x (%12d)" % (addr, addr))
    print("stack size                   = 0x%08x (%12d) bytes" % (size, size))
    print("")

    size = parse_mapfile_get_value(sfn, "__flash_size__")
    usage = parse_mapfile_get_value(sfn, "__flash_usage__")
    if size > 0:
        print("flash size                   = 0x%08x (%12d) bytes" % (size, size))
        print("flash usage                  = 0x%08x (%12d) bytes" % (usage, usage))
        print("")
        size = parse_mapfile_get_value(sfn, "__ram_size__")
        usage = parse_mapfile_get_value(sfn, "__ram_static_usage__")
        print("ram size                     = 0x%08x (%12d) bytes" % (size, size))
        print("ram static usage             = 0x%08x (%12d) bytes" % (usage, usage))
        print("")

    size = parse_mapfile_get_value(sfn, "__flash2_size__")
    usage = parse_mapfile_get_value(sfn, "__flash2_usage__")
    if size > 0:
        print("flash2 size                  = 0x%08x (%12d) bytes" % (size, size))
        print("flash2 usage                 = 0x%08x (%12d) bytes" % (usage, usage))
        print("")
        size = parse_mapfile_get_value(sfn, "__ram2_size__")
        usage = parse_mapfile_get_value(sfn, "__ram2_static_usage__")
        print("ram2 size                    = 0x%08x (%12d) bytes" % (size, size))
        print("ram2 static usage            = 0x%08x (%12d) bytes" % (usage, usage))
        print("")
        
    print("")

if __name__ == '__main__':
    if 2 > len(sys.argv):
        print_help()
    else:
        if "cpu_count" == sys.argv[1]:
            cpu_count()
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
        elif "getuid" == sys.argv[1]:
            getuid()
        elif "getgid" == sys.argv[1]:
            getgid()
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
        elif "parse_mapfile_get_value" == sys.argv[1]:
            if 4 > len(sys.argv):
                print_help()
            else:
                sfn = sys.argv[2]
                symbol = sys.argv[3]
                parse_mapfile_get_value(sfn, symbol)
        elif "show_mapfile_info" == sys.argv[1]:
            if 3 > len(sys.argv):
                print_help()
            else:
                sfn = sys.argv[2]
                show_mapfile_info(sfn)
        elif "replace_string" == sys.argv[1]:
            if 6 > len(sys.argv):
                print_help()
            else:
                sfn = sys.argv[2]
                dfn = sys.argv[3]
                oldstr = sys.argv[4]
                newstr = sys.argv[5]
                replace_string(sfn, dfn, oldstr, newstr)
        else:
            print_help()

