#! /usr/bin/python

#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

import os
import sys
import glob
import io
import tkinter as tk
import tkinter.font as font

from os import listdir
from os.path import isfile, isdir, join, splitext
from shutil import copyfile
from tkinter import ttk

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

        self.title('Ubinos config selector')

        window_width = 1000
        window_height = 700
        screen_width = self.winfo_screenwidth()
        screen_height = self.winfo_screenheight()
        x_cordinate = int((screen_width/2) - (window_width/2))
        y_cordinate = int((screen_height/2) - (window_height/2))
        self.geometry("{}x{}+{}+{}".format(window_width, window_height, x_cordinate, y_cordinate))

        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)

        self.bind('<Key>', self.key_pressed)

        frame_tv = tk.Frame(self)
        frame_tv.grid(row=0, column=0, sticky="nsew")
        frame_tv.rowconfigure(0, weight=1)
        frame_tv.columnconfigure(0, weight=1)

        frame_bt = tk.Frame(self)
        frame_bt.grid(row=1, column=0, sticky="nsew", padx=10, pady=20)

        self.tv = ttk.Treeview(frame_tv, columns=(1, 2, 3, 4), show="headings", selectmode="browse")
        self.tv.grid(row=0, column=0, sticky="nsew")

        sb = tk.Scrollbar(frame_tv, orient=tk.VERTICAL)
        sb.grid(row=0, column=1, sticky="ns")

        self.tv.config(yscrollcommand=sb.set)
        sb.config(command=self.tv.yview)

        self.tv.bind('<ButtonRelease-1>', self.select_item)

        cancel_button = tk.Button(frame_bt, text="Cancel", command=quit)
        cancel_button.pack(side=tk.RIGHT, padx=10, pady=0)
        ok_button = tk.Button(frame_bt, text="OK", command=self.press_ok)
        ok_button.pack(side=tk.RIGHT, padx=10, pady=0)

        self.tv.heading(1, text="index")
        self.tv.column(1, width=50)
        self.tv.heading(2, text="project")
        self.tv.column(2, width=200)
        self.tv.heading(3, text="name")
        self.tv.column(3, width=450)
        self.tv.heading(4, text="dir")
        self.tv.column(4, width=280)

        self.update_options()
        for conf in self.conf_list:
            self.tv.insert(parent='', index=conf["index"], iid=conf["index"], values=(conf["index"], conf["project"], conf["name"], conf["dir"]))
            self.tv.selection_set(self.conf_index)
            self.tv.see(self.conf_index)

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
                        self.conf_list.append({"index": index, "project": prj["name"], "name": conf_name, "dir": conf_dir})
                        index += 1
                    file.close()
        self.conf_len = index

        # for conf in self.conf_list:
        #     print(conf)

    def print_selection(self):
        selection = self.conf_list[self.conf_index]
        print(selection)
        print("")

    def select_item(self, event):
        item = self.tv.focus()
        if item != '':
            self.conf_index = int(item)
            self.print_selection()

    def key_pressed(self, event):
        # print(event.keysym)
        if event.keysym == "Return":
            self.press_ok()
        elif event.keysym == "Escape":
            self.quit()
        elif event.keysym == "Up":
            if self.conf_index > 0:
                self.conf_index -= 1
                self.tv.selection_set(self.conf_index)
                self.tv.see(self.conf_index)
                self.print_selection()
        elif event.keysym == "Down":
            if self.conf_index < (self.conf_len - 1):
                self.conf_index += 1
                self.tv.selection_set(self.conf_index)
                self.tv.see(self.conf_index)
                self.print_selection()

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

    def press_ok(self):
        if self.conf_len > 0:
            print("Set config to\n")
            self.print_selection()

            selection = self.conf_list[self.conf_index]
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
