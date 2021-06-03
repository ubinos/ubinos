#!/usr/bin/python

import os
import sys
import glob
import io
import tkinter as tk
import tkinter.font as font

from os import listdir
from os.path import isfile, isdir, join, splitext
from shutil import copyfile

def print_help():
    print("===============================================================================")
    print("Usage:")
    print("    python %s <project base dir> <library relative dir>" % (sys.argv[0]))
    print("===============================================================================")

class confsel(tk.Tk):
    keyword = "{ubinos_config_type: [buildable"
    conf_dir_names = ["app", "config"]
    prj_base_dir = ".."
    lib_rel_dir = "library"
    make_fname = "Makefile"

    conf_list = []
    conf_index = 0
    conf_len = 0

    def __init__(self, prj_base_dir, lib_rel_dir):
        super().__init__()

        self.prj_base_dir = prj_base_dir
        self.lib_rel_dir = lib_rel_dir

        print("Ubinos config selector")
        print("    base dir : %s" % self.prj_base_dir)
        print("    library dir : %s" % self.lib_rel_dir)
        print("")

        self.update_options()

        self.title('Ubinos config selector')
        frame = tk.Frame(self)

        if self.conf_len > 0:
            self.options = tk.StringVar(frame)
            self.options.set(self.conf_list[self.conf_index])
            self.option_menu = tk.OptionMenu(frame, self.options, *self.conf_list, command=self.select_option)
            self.option_menu.pack()

        cancel_button = tk.Button(frame, text="Cancel", command=quit)
        cancel_button.pack(side=tk.LEFT)
        ok_button = tk.Button(frame, text="OK", command=self.press_ok)
        ok_button.pack(side=tk.RIGHT)

        frame.pack()
        self.bind('<Key>', self.key_pressed)
        self.eval('tk::PlaceWindow . center')

    def update_options(self):
        index = 0
        prjs = [{"name": ".", "dir": ".."}]
        lib_dir = join(self.prj_base_dir, self.lib_rel_dir)
        if os.path.exists(lib_dir):
            for f in sorted(listdir(lib_dir)):
                prj_dir = join(lib_dir, f)
                if isdir(prj_dir):
                    prjs += [{"name": f, "dir": prj_dir}]
        for prj in prjs:
            conf_dirs = []
            for conf_dir_name in self.conf_dir_names:
                conf_dir = join(prj["dir"], conf_dir_name)
                if os.path.exists(conf_dir) and os.path.isdir(conf_dir):
                    conf_dirs.append(conf_dir)
            for conf_dir in conf_dirs:
                conf_fnames = [f for f in sorted(listdir(conf_dir)) if isfile(join(conf_dir, f))]
                for conf_fname in conf_fnames:
                    file = open(join(conf_dir, conf_fname))
                    if (self.keyword in file.read()):
                        conf_name = splitext(conf_fname)[0]
                        self.conf_list.append({"index": index, "prj": prj["name"], "name": conf_name, "dir": conf_dir})
                        index += 1
                    file.close()
        self.conf_len = index

        # for conf in self.conf_list:
        #     print(conf)

    def key_pressed(self, event):
        # print(event.keysym)
        if event.keysym == "Return":
            self.press_ok()
        elif event.keysym == "Escape":
            self.quit()
        elif event.keysym == "Up":
            if self.conf_index > 0:
                self.conf_index -= 1
                self.options.set(self.conf_list[self.conf_index])
        elif event.keysym == "Down":
            if self.conf_index < (self.conf_len - 1):
                self.conf_index += 1
                self.options.set(self.conf_list[self.conf_index])

    def create_makefile(self):
        selection = self.conf_list[self.conf_index]
        # print(selection)
        mfname = self.make_fname
        file = open(mfname, 'w+')
        file.write("CONFIG_DIR ?= %s\n" % selection["dir"])
        file.write("CONFIG_NAME ?= %s\n" % selection["name"])
        file.write("\n")
        file.write("include makefile.mk\n")
        file.write("\n")
        file.close()

    def select_option(self, selection):
        self.conf_index = int(selection["index"])
        print(selection)
        print("")

    def press_ok(self):
        if self.conf_len > 0:
            selection = self.conf_list[self.conf_index]
            # print(selection)

            mfname = self.make_fname

            if not os.path.exists(mfname):
                self.create_makefile()

            elif not os.path.isdir(mfname):
                file = open(mfname, 'r')
                file.seek(0, io.SEEK_END)
                fsize = file.tell()
                file.close()

                if fsize <= 0:
                    self.create_makefile()

                else:
                    copyfile(mfname, mfname + ".bak")

                    need_dir = True
                    need_name = True

                    file = open(mfname, 'r')
                    lines = file.readlines()
                    file.close()
                    file = open(mfname, 'w+')
                    for line in lines:
                        if line.startswith("CONFIG_DIR "):
                            file.write("CONFIG_DIR ?= %s\n" % selection["dir"])
                            need_dir = False
                        elif line.startswith("CONFIG_NAME "):
                            file.write("CONFIG_NAME ?= %s\n" % selection["name"])
                            need_name = False
                        else:
                            file.write(line)
                    file.close()

                    if need_dir:
                        file = open(mfname, 'r')
                        lines = file.readlines()
                        file.close()
                        file = open(mfname, 'w+')
                        for line in lines:
                            if need_dir and line.startswith("include makefile.mk"):
                                file.write("CONFIG_DIR ?= %s\n" % selection["dir"])
                                file.write("\n")
                                file.write("include makefile.mk\n")
                                need_dir = False
                            else:
                                file.write(line)
                        file.close()
                    if need_name:
                        file = open(mfname, 'r')
                        lines = file.readlines()
                        file.close()
                        file = open(mfname, 'w+')
                        for line in lines:
                            if need_name and line.startswith("include makefile.mk"):
                                file.write("CONFIG_NAME ?= %s\n" % selection["name"])
                                file.write("\n")
                                file.write("include makefile.mk\n")
                                need_name = False
                            else:
                                file.write(line)
                        file.close()

        self.quit()

if __name__ == '__main__':
    if 3 > len(sys.argv):
        print_help()
    else:
        prj_base_dir = sys.argv[1]
        lib_rel_dir = sys.argv[2]
        csel = confsel(prj_base_dir, lib_rel_dir)
        csel.mainloop()

    # csel = confsel("..", "library")
    # csel.mainloop()
