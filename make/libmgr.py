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
import json
import copy
import pathlib
import shutil
import subprocess

from tkinter import ttk
from tkinter import Toplevel
from tkinter import messagebox

debug_level = 1

config_file_name = "liblist.json"

# config_name_base
# config_name_variation
# config_name = <config_name_base>__<config_name_variation>
# config_extension
# config_file_name = <config_name>.<config_extension>
# config_dir
# config_file_path = <config_dir>/<config_file_name>

def print_help():
    print("===============================================================================")
    print("Usage:")
    print("    python %s <project base dir> <library relative dir>" % (sys.argv[0]))
    print("===============================================================================")

def set_geometry_center(win, width, height):
    screen_width = win.winfo_screenwidth()
    screen_height = win.winfo_screenheight()
    x_cordinate = int((screen_width/2) - (width/2))
    y_cordinate = int((screen_height/2) - (height/2))
    win.geometry("{}x{}+{}+{}".format(width, height, x_cordinate, y_cordinate))

def file_open(fname, mode):
    if sys.version_info.major >= 3:
        return open(fname, mode, encoding="UTF-8")
    else:
        return open(fname, mode)

class clone_dialog(tk.Toplevel):

    def __init__(self, parent):
        super().__init__(parent)

        self.parent = parent

        self.title('Ubinos library command')

        set_geometry_center(self, 1100, 500)

        self.transient(self.parent)
        self.protocol("WM_DELETE_WINDOW", self.parent.press_install_dialog_cancel)

        self.rowconfigure(0, weight=3)
        self.rowconfigure(1, weight=1)
        self.columnconfigure(0, weight=1)

        ##
        self.command_text_var = ""

        frame_command_text = tk.Frame(self)
        frame_command_text.grid(row=0, column=0, sticky="nsew")
        frame_command_text.rowconfigure(0, weight=1)
        frame_command_text.columnconfigure(0, weight=1)

        frame_command_text = tk.Frame(frame_command_text)
        frame_command_text.grid(row=0, column=0, sticky="nsew")
        frame_command_text.rowconfigure(0, weight=1)
        frame_command_text.columnconfigure(0, weight=1)

        self.command_text = tk.Text(frame_command_text)
        self.command_text.grid(row=0, column=0, sticky="nsew")
        self.command_text.config(state=tk.DISABLED)

        sb = tk.Scrollbar(frame_command_text, orient=tk.VERTICAL)
        sb.grid(row=0, column=1, sticky="ns")
        self.command_text.config(yscrollcommand=sb.set)
        sb.config(command=self.command_text.yview)

        ##
        self.result_text_var = ""

        frame_result_text = tk.Frame(self)
        frame_result_text.grid(row=1, column=0, sticky="nsew")
        frame_result_text.rowconfigure(1, weight=1)
        frame_result_text.columnconfigure(0, weight=1)

        frame_result_text = tk.Frame(frame_result_text)
        frame_result_text.grid(row=1, column=0, sticky="nsew")
        frame_result_text.rowconfigure(1, weight=1)
        frame_result_text.columnconfigure(0, weight=1)

        self.result_text = tk.Text(frame_result_text)
        self.result_text.grid(row=1, column=0, sticky="nsew")
        self.result_text.config(state=tk.DISABLED)

        sb = tk.Scrollbar(frame_result_text, orient=tk.VERTICAL)
        sb.grid(row=1, column=1, sticky="ns")
        self.result_text.config(yscrollcommand=sb.set)
        sb.config(command=self.result_text.yview)

        ##
        frame_bt = tk.Frame(self)
        frame_bt.grid(row=2, column=0, sticky="nsew", padx=10, pady=20)

        self.ok_button = tk.Button(frame_bt, text="Run", command=self.parent.press_install_dialog_ok)
        self.ok_button.pack(side=tk.LEFT, padx=10, pady=0)
        self.cancel_button = tk.Button(frame_bt, text="Close", command=self.parent.press_install_dialog_cancel)
        self.cancel_button.pack(side=tk.RIGHT, padx=10, pady=0)

        self.update_items(True)

    def update_items(self, init=False):
        self.command_text.config(state=tk.NORMAL)
        self.command_text.delete(1.0, tk.END)
        self.command_text.insert(tk.END, self.command_text_var)
        last_line_index = self.command_text.index("end-1c linestart")
        self.command_text.see(last_line_index)
        self.command_text.config(state=tk.DISABLED)

        self.result_text.config(state=tk.NORMAL)
        self.result_text.delete(1.0, tk.END)
        self.result_text.insert(tk.END, self.result_text_var)
        last_line_index = self.result_text.index("end-1c linestart")
        self.result_text.see(last_line_index)
        self.result_text.config(state=tk.DISABLED)

    def set_command(self, commands):
        for cmd in commands:
            self.command_text_var += (cmd + "\n")
        self.update_items()

    def clear_result(self):
        self.result_text_var = ""
        self.update_items()

    def append_result(self, result):
        self.result_text_var += result
        self.update_items()

    def disalbe_run(self):
        self.ok_button.config(state=tk.DISABLED)

class libmgr(tk.Tk):
    config_info_keyword = "ubinos_config_info {"
    cmake_inclucde_file_keyword = "include(${CMAKE_CURRENT_LIST_DIR}/"
    config_dir_names = ["app", "config"]
    prj_dir_base = ".."
    lib_rel_dir = "library"
    make_file_name = "Makefile"
    config_info_rel_dir = "ubinos/make"

    config_items = []
    config_item_idx = 0
    config_item_len = 0

    git_commands = []

    def __init__(self, prj_dir_base, lib_rel_dir):
        super().__init__()

        self.prj_dir_base = prj_dir_base
        self.lib_rel_dir = lib_rel_dir

        if debug_level >= 1:
            print("Ubinos library manager")
            print("    base dir : %s" % self.prj_dir_base)
            print("    library dir : %s" % self.lib_rel_dir)
            print("")

        self.title('Ubinos library manager')

        set_geometry_center(self, 1000, 700)

        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)

        self.bind('<Key>', self.key_pressed)

        frame_tv = tk.Frame(self)
        frame_tv.grid(row=0, column=0, sticky="nsew")
        frame_tv.rowconfigure(0, weight=1)
        frame_tv.columnconfigure(0, weight=1)

        self.tv = ttk.Treeview(frame_tv, columns=(1, 2, 3, 4, 5), show="headings", selectmode="browse")
        self.tv.grid(row=0, column=0, sticky="nsew")

        sb = tk.Scrollbar(frame_tv, orient=tk.VERTICAL)
        sb.grid(row=0, column=1, sticky="ns")
        self.tv.config(yscrollcommand=sb.set)
        sb.config(command=self.tv.yview)
        self.tv.bind('<ButtonRelease-1>', self.select_item)

        frame_bt = tk.Frame(self)
        frame_bt.grid(row=1, column=0, sticky="nsew", padx=10, pady=20)

        self.install_button = tk.Button(frame_bt, text="Install", command=self.press_install)
        self.install_button.pack(side=tk.LEFT, padx=10, pady=0)
        self.uninstall_button = tk.Button(frame_bt, text="Uninstall", command=self.press_uninstall)
        self.uninstall_button.pack(side=tk.LEFT, padx=10, pady=0)

        self.cancel_button = tk.Button(frame_bt, text="Cancel", command=quit)
        self.cancel_button.pack(side=tk.RIGHT, padx=10, pady=0)

        self.tv.heading(1, text="Index")
        self.tv.column(1, width=50)
        self.tv.heading(2, text="Name")
        self.tv.column(2, width=200)
        self.tv.heading(3, text="URL")
        self.tv.column(3, width=450)
        self.tv.heading(4, text="Branch")
        self.tv.column(4, width=160)
        self.tv.heading(5, text="Installed")
        self.tv.column(5, width=80)

        self.update_config_items()
        self.update_selection()

    def update_config_items(self):
        index = 0
        lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
        config_info_dir = os.path.join(lib_dir, self.config_info_rel_dir)
        config_info = self.load_config_info(os.path.join(config_info_dir, config_file_name))

        self.config_items = []
        
        for info in config_info:
            lib_path = os.path.join(lib_dir, info["name"])
            lib_state = "X"
            if os.path.exists(lib_path) and os.path.isdir(lib_path):
                lib_state = "O"
            self.config_items.append({"index": index, "name": info["name"], "url": info["url"], "branch": info["branch"], "installed": lib_state})
            index += 1

        self.config_len = index

        self.tv.delete(*self.tv.get_children())
        for conf in self.config_items:
            self.tv.insert(parent='', index=conf["index"], iid=conf["index"],  values=(conf["index"], conf["name"], conf["url"], conf["branch"], conf["installed"]))

        if debug_level >= 3:
            for conf in self.config_items:
                print(conf)
            print("")

    def update_selection(self):
        if self.config_items[self.config_item_idx]["name"] == "ubinos":
            self.install_button.config(state=tk.DISABLED)
            self.uninstall_button.config(state=tk.DISABLED)
        elif self.config_items[self.config_item_idx]["installed"] != "X":
            self.install_button.config(state=tk.DISABLED)
            self.uninstall_button.config(state=tk.NORMAL)
        else:
            self.install_button.config(state=tk.NORMAL)
            self.uninstall_button.config(state=tk.DISABLED)
        self.tv.selection_set(self.config_item_idx)
        self.tv.see(self.config_item_idx)

    def load_config_info(self, config_file_path):
        try:
            with file_open(config_file_path, 'r') as file:
                config_info = json.load(file)
                return config_info
        except Exception as e:
            print('Exception occurred.', e, config_file_path)

    def get_cmake_include_file_names(self, config_dir, config_file_name):
        include_file_names = []
        config_file_path = os.path.join(config_dir, config_file_name)

        with file_open(config_file_path, 'r') as file:
            lines = file.readlines()
            file.close()
            for line in lines:
                if line.startswith(self.cmake_inclucde_file_keyword):
                    k_len = len(self.cmake_inclucde_file_keyword)
                    include_file_name = line[k_len:].strip()[:-1]
                    include_file_path = os.path.join(config_dir, include_file_name)
                    include_file_names.append(include_file_name)
                    sub_include_file_names = self.get_cmake_include_file_names(config_dir, include_file_name)
                    include_file_names += sub_include_file_names

        return include_file_names

    def clone_config_info(self, src_config_info, dst_config_name_base):
        src_config_name_base = src_config_info["name_base"]

        dst_config_info = copy.deepcopy(src_config_info)
        dst_config_info["name_base"] = dst_config_name_base

        if "include_files" in src_config_info:
            for idx, src_file_name in enumerate(src_config_info["include_files"]):
                dst_file_name = src_file_name.replace(src_config_name_base, dst_config_name_base, 1)
                dst_config_info["include_files"][idx] = dst_file_name

        return dst_config_info

    def create_makefile(self, make_file_path, config_dir, config_name):
        file = file_open(make_file_path, 'w+')
        file.write("CONFIG_DIR ?= %s\n" % config_dir)
        file.write("CONFIG_NAME ?= %s\n" % config_name)
        file.write("\n")
        file.write("include makefile.mk\n")
        file.write("\n")
        file.close()

    def get_config_from_makefile(self, make_file_path):
        config_dir = ""
        config_name = ""

        with file_open(make_file_path, 'r') as file:
            lines = file.readlines()
            file.close()
            for line in lines:
                keyword = "CONFIG_DIR"
                if config_dir == "" and line.startswith(keyword):
                    k_len = len(keyword)
                    k_idx = k_len
                    keyword = "="
                    k_idx = line[k_idx:].find(keyword)
                    if k_idx > -1:
                        k_idx += k_len + len(keyword)
                        config_dir = line[k_idx:].strip()

                keyword = "CONFIG_NAME"
                if config_name == "" and line.startswith(keyword):
                    k_len = len(keyword)
                    k_idx = k_len
                    keyword = "="
                    k_idx = line[k_idx:].find(keyword)
                    if k_idx > -1:
                        k_idx += k_len + len(keyword)
                        config_name = line[k_idx:].strip()

        return config_dir, config_name

    def select_config(self, make_file_path, config_dir, config_name):
        if not os.path.exists(make_file_path):
            self.create_makefile(make_file_path, config_dir, config_name)

        elif not os.path.isdir(make_file_path):
            file = file_open(make_file_path, 'r')
            file.seek(0, io.SEEK_END)
            file_len = file.tell()
            file.close()

            if file_len <= 0:
                self.create_makefile(make_file_path, config_dir, config_name)

            else:
                shutil.copyfile(make_file_path, make_file_path + ".bak")

                need_config_dir = True
                need_config_name = True

                file = file_open(make_file_path, 'r')
                lines = file.readlines()
                file.close()
                file = file_open(make_file_path, 'w+')
                for line in lines:
                    if line.startswith("CONFIG_DIR "):
                        file.write("CONFIG_DIR ?= %s\n" % config_dir)
                        need_config_dir = False
                    elif line.startswith("CONFIG_NAME "):
                        file.write("CONFIG_NAME ?= %s\n" % config_name)
                        need_config_name = False
                    else:
                        file.write(line)
                file.close()

                if need_config_dir:
                    file = file_open(make_file_path, 'r')
                    lines = file.readlines()
                    file.close()
                    file = file_open(make_file_path, 'w+')
                    for line in lines:
                        if need_config_dir and line.startswith("include makefile.mk"):
                            file.write("CONFIG_DIR ?= %s\n" % config_dir)
                            file.write("\n")
                            file.write("include makefile.mk\n")
                            need_config_dir = False
                        else:
                            file.write(line)
                    file.close()
                if need_config_name:
                    file = file_open(make_file_path, 'r')
                    lines = file.readlines()
                    file.close()
                    file = file_open(make_file_path, 'w+')
                    for line in lines:
                        if need_config_name and line.startswith("include makefile.mk"):
                            file.write("CONFIG_NAME ?= %s\n" % config_name)
                            file.write("\n")
                            file.write("include makefile.mk\n")
                            need_config_name = False
                        else:
                            file.write(line)
                    file.close()

    def get_clone_params(self):
        selection = self.config_items[self.config_item_idx]
        src_url = selection["url"]
        lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
        dst_dir = os.path.join(lib_dir, selection["name"])

        return src_url, dst_dir

    def check_clone_dst_file_paths(self, dst_file_paths):
        is_valid = True

        for file_path in dst_file_paths:
            if os.path.exists(file_path):
                print("%s is already exists" % file_path)
                is_valid = False

        return is_valid

    def clone_config(self, make_file_path, src_config_dir, src_config_file_name, dst_config_dir, dst_config_name_base):
        src_file_paths, dst_file_paths, src_config_name_base, dst_config_name = self.get_clone_params(src_config_dir, src_config_file_name, dst_config_dir, dst_config_name_base)

        if debug_level >= 2:
            print(src_file_paths)
            print(dst_file_paths)
            print("")

        if not os.path.exists(dst_config_dir):
            os.mkdir(dst_config_dir)

        if self.check_clone_dst_file_paths(dst_file_paths):
            for idx, src_file_path in enumerate(src_file_paths):
                dst_file_path = dst_file_paths[idx]
                if os.path.isdir(src_file_path):
                    shutil.copytree(src_file_path, dst_file_path)
                else:
                    file = file_open(src_file_path, 'r')
                    lines = file.readlines()
                    file.close()
                    file = file_open(dst_file_path, 'w+')

                    for line in lines:
                        written = False

                        keyword = "ubinos_config_info"
                        k_idx = line.find(keyword)
                        if not written and k_idx > -1:
                            k_idx = k_idx + len(keyword)
                            config_info_idx = line[k_idx:].find("{")
                            tmp_config_info = json.loads(line[k_idx + config_info_idx:])
                            dst_config_info = self.clone_config_info(tmp_config_info, dst_config_name_base)
                            new_line = line[:k_idx] + " " + json.dumps(dst_config_info) + "\n"
                            file.write(new_line)
                            written = True

                        keyword = "set(APP__NAME"
                        k_idx = line.find(keyword)
                        if not written and k_idx > -1:
                            k_idx = k_idx + len(keyword)
                            new_line = line[:k_idx] + line[k_idx:].replace(src_config_name_base, dst_config_name_base, 1)
                            file.write(new_line)
                            written = True

                        keyword = "APP__NAME = "
                        k_idx = line.find(keyword)
                        if not written and k_idx > -1:
                            k_idx = k_idx + len(keyword)
                            new_line = line[:k_idx] + line[k_idx:].replace(src_config_name_base, dst_config_name_base, 1)
                            file.write(new_line)
                            written = True

                        keyword = "include(${CMAKE_CURRENT_LIST_DIR}"
                        k_idx = line.find(keyword)
                        if not written and k_idx > -1:
                            k_idx = k_idx + len(keyword)
                            new_line = line[:k_idx] + line[k_idx:].replace(src_config_name_base, dst_config_name_base, 1)
                            file.write(new_line)
                            written = True

                        keyword = ("${CMAKE_CURRENT_LIST_DIR}/%s" % src_config_name_base)
                        k_idx = line.find(keyword)
                        if not written and k_idx > -1:
                            new_line = line[:k_idx] + line[k_idx:].replace(src_config_name_base, dst_config_name_base, 1)
                            file.write(new_line)
                            written = True

                        if not written:
                            file.write(line)

                    file.close()

            self.select_config(make_file_path, dst_config_dir, dst_config_name)

            return True, ("%s cloned %s has been created successfully." % (dst_config_name, os.path.splitext(src_config_file_name)[0]))

        else:
            return False, "Files already exist."

    def print_selection(self):
        selection = self.config_items[self.config_item_idx]
        print(selection)
        print("")

    def select_item(self, event):
        item = self.tv.focus()
        if item != '':
            self.config_item_idx = int(item)
            self.update_selection()
            if debug_level >= 2:
                self.print_selection()

    def key_pressed(self, event):
        # print(event.keysym)
        if event.keysym == "Escape":
            self.quit()
        elif event.keysym == "Up":
            if self.config_item_idx > 0:
                self.config_item_idx -= 1
                self.update_selection()
                if debug_level >= 2:
                    self.print_selection()
        elif event.keysym == "Down":
            if self.config_item_idx < (self.config_len - 1):
                self.config_item_idx += 1
                self.update_selection()
                if debug_level >= 2:
                    self.print_selection()

    def press_install(self):
        if self.config_len > 0:
            if debug_level >= 1:
                print("Install library\n")
                self.print_selection()

            lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
            selection = self.config_items[self.config_item_idx]
            target_dir = os.path.join(lib_dir, selection["name"])
            self.git_commands = []
            self.git_commands.append("git submodule add -f " + selection["url"] + " " + target_dir)
            self.git_commands.append("cd "  + target_dir + "; git checkout -f " + selection["branch"])
            # self.git_commands.append("git submodule status " + target_dir)
            self.clone_dialog = clone_dialog(self)
            self.clone_dialog.title("Install library commands")
            self.clone_dialog.set_command(self.git_commands)
            self.clone_dialog.grab_set()

    def press_uninstall(self):
        if self.config_len > 0:
            if debug_level >= 1:
                print("Uninstall library\n")
                self.print_selection()

            lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
            selection = self.config_items[self.config_item_idx]
            target_dir = os.path.join(lib_dir, selection["name"])
            git_dir = os.path.join(self.prj_dir_base, ".git", "modules", selection["name"])
            self.git_commands = []
            self.git_commands.append("git submodule deinit -f " + target_dir)
            self.git_commands.append("rm -rf " + git_dir)
            self.git_commands.append("git rm -f " + target_dir)
            # self.git_commands.append("git config -f " + os.path.join(self.prj_dir_base, ".gitmodules") 
            #                          + " --remove-section submodule." 
            #                          + os.path.basename(target_dir))
            self.clone_dialog = clone_dialog(self)
            self.clone_dialog.title("Uninstall library commands")
            self.clone_dialog.set_command(self.git_commands)
            self.clone_dialog.grab_set()

    def press_install_dialog_cancel(self):
        self.clone_dialog.destroy()
        self.deiconify()

    def press_install_dialog_ok(self):
        result = False
        for cmd in self.git_commands:
            result = self.run_git_command(cmd)
            if not result:
                messagebox.showinfo(
                    title='Result',
                    message="Failed",
                )
                break

        self.update_config_items()
        self.update_selection()

        if result:
            messagebox.showinfo(
                title='Result',
                message="Succeeded",
            )
            # self.clone_dialog.destroy()
            # self.deiconify()
            # self.quit()

        self.clone_dialog.disalbe_run()

    def run_git_command(self, command):
        result = False
        self.clone_dialog.append_result(command + "\n")
        self.clone_dialog.update_items()
        try:
            process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=1, universal_newlines=True)
            for line in process.stdout:
                self.clone_dialog.append_result(line)
                self.clone_dialog.update_items()
            for line in process.stderr:
                self.clone_dialog.append_result(line)
                self.clone_dialog.update_items()
            process.wait()

            if process.returncode == 0:
                result = True
        except Exception as e:
            print('Exception occurred.', e, command)

        return result

if __name__ == '__main__':
    if 3 > len(sys.argv):
        print_help()
    else:
        if sys.argv[1] == "--lib-absolute" and 4 <= len(sys.argv):
            prj_dir_base = sys.argv[2]
            lib_rel_dir = os.path.relpath(sys.argv[3], os.path.abspath(prj_dir_base))
        else:
            prj_dir_base = sys.argv[1]
            lib_rel_dir = sys.argv[2]

        csel = libmgr(prj_dir_base, lib_rel_dir)
        csel.mainloop()

    # csel = libmgr("..", "library")
    # csel.mainloop()
