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

def print_help():
    print("===============================================================================")
    print("Usage:")
    print("    python %s <project base dir> <library relative dir>" % (sys.argv[0]))
    print("===============================================================================")

def set_geometry_center(win, width, height):
    screen_width = win.winfo_screenwidth()
    screen_height = win.winfo_screenheight()
    x_cordinate = (screen_width  // 2) - (width  // 2)
    y_cordinate = (screen_height // 2) - (height // 2)
    win.geometry("{}x{}+{}+{}".format(width, height, x_cordinate, y_cordinate))

def set_dialog_geometry_center(parent, win, width, height):
    parent_width = parent.winfo_width()
    parent_height = parent.winfo_height()
    parent_x = parent.winfo_x()
    parent_y = parent.winfo_y()
    x_cordinate = (parent_width  // 2) - (width  // 2) + parent_x
    y_cordinate = (parent_height // 2) - (height // 2) + parent_y
    win.geometry("{}x{}+{}+{}".format(width, height, x_cordinate, y_cordinate))

def file_open(fname, mode):
    if sys.version_info.major >= 3:
        return open(fname, mode, encoding="UTF-8")
    else:
        return open(fname, mode)

class run_dialog(tk.Toplevel):

    def __init__(self, parent):
        super().__init__(parent)

        self.parent = parent
        
        self.runable = True
        self.running = False

        self.title('Ubinos library command')
        
        set_dialog_geometry_center(parent, self, 1100, 500)

        self.transient(self.parent)
        self.protocol("WM_DELETE_WINDOW", self.close)

        self.rowconfigure(0, weight=3)
        self.rowconfigure(1, weight=1)
        self.columnconfigure(0, weight=1)

        self.bind('<Key>', self.key_pressed)

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

        self.run_button = tk.Button(frame_bt, text="Run", command=self.parent.press_run_dialog_run)
        self.run_button.pack(side=tk.LEFT, padx=10, pady=0)
        
        self.close_button = tk.Button(frame_bt, text="Close", command=self.parent.press_run_dialog_close)
        self.close_button.pack(side=tk.RIGHT, padx=10, pady=0)

        ##
        self.update_command_text(True)
        self.update_result_text(True)
        self.update_buttons(True)

    def key_pressed(self, event):
        # print(event.keysym)
        if event.keysym == "Escape":
            self.close()

    def close(self):
        if not self.running:
            self.parent.press_run_dialog_close()

    def update_command_text(self, init=False):
        self.command_text.config(state=tk.NORMAL)
        self.command_text.delete(1.0, tk.END)
        self.command_text.insert(tk.END, self.command_text_var)
        last_line_index = self.command_text.index("end-1c linestart")
        self.command_text.see(last_line_index)
        self.command_text.config(state=tk.DISABLED)

    def update_result_text(self, init=False):
        self.result_text.config(state=tk.NORMAL)
        self.result_text.delete(1.0, tk.END)
        self.result_text.insert(tk.END, self.result_text_var)
        last_line_index = self.result_text.index("end-1c linestart")
        self.result_text.see(last_line_index)
        self.result_text.config(state=tk.DISABLED)

    def update_buttons(self, init=False):
        if not self.runable or self.running:
            self.run_button.config(state=tk.DISABLED)
        else:
            self.run_button.config(state=tk.NORMAL)

        if self.running:
            self.close_button.config(state=tk.DISABLED)
        else:
            self.close_button.config(state=tk.NORMAL)

    def set_command(self, commands):
        for cmd in commands:
            self.command_text_var += (cmd + "\n")
        self.update_command_text()

    def clear_result(self):
        self.result_text_var = ""
        self.update_result_text()

    def append_result(self, result):
        self.result_text_var += result
        self.update_result_text()

    def set_runable(self, runable):
        self.runable = runable
        self.update_buttons()

    def set_running(self, running):
        self.running = running
        self.update_buttons()

class libmgr(tk.Tk):
    prj_dir_base = ".."
    lib_rel_dir = "library"
    lib_list_file_name = "liblist.json"
    lib_list_file_rel_dir = os.path.join(lib_rel_dir, "ubinos", "make")

    lib_items = []
    lib_item_idx = 0
    lib_item_len = 0

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

        ##
        frame_tv = tk.Frame(self)
        frame_tv.grid(row=0, column=0, sticky="nsew")
        frame_tv.rowconfigure(0, weight=1)
        frame_tv.columnconfigure(0, weight=1)

        self.tv = ttk.Treeview(frame_tv, columns=(1, 2, 3, 4, 5, 6, 7, 8), show="headings", selectmode="browse")
        self.tv.grid(row=0, column=0, sticky="nsew")

        sb = tk.Scrollbar(frame_tv, orient=tk.VERTICAL)
        sb.grid(row=0, column=1, sticky="ns")
        self.tv.config(yscrollcommand=sb.set)
        sb.config(command=self.tv.yview)
        self.tv.bind('<ButtonRelease-1>', self.select_item)

        self.tv.heading(1, text="No.") # Index
        self.tv.column(1, width=20)
        self.tv.heading(2, text="Name")
        self.tv.column(2, width=180)
        self.tv.heading(3, text="URL")
        self.tv.column(3, width=370)
        self.tv.heading(4, text="Default branch")
        self.tv.column(4, width=100)
        self.tv.heading(5, text="I", anchor=tk.CENTER) # Installed
        self.tv.column(5, width=20, anchor=tk.CENTER)
        self.tv.heading(6, text="Local branch")
        self.tv.column(6, width=100)
        self.tv.heading(7, text="M", anchor=tk.CENTER) # Modified
        self.tv.column(7, width=20, anchor=tk.CENTER)
        self.tv.heading(8, text="U", anchor=tk.CENTER) # Updatable
        self.tv.column(8, width=20, anchor=tk.CENTER)

        ##
        frame_bt = tk.Frame(self)
        frame_bt.grid(row=1, column=0, sticky="nsew", padx=10, pady=20)

        self.install_button = tk.Button(frame_bt, text="Install", command=self.press_install)
        self.install_button.pack(side=tk.LEFT, padx=10, pady=0)

        self.uninstall_button = tk.Button(frame_bt, text="Uninstall", command=self.press_uninstall)
        self.uninstall_button.pack(side=tk.LEFT, padx=10, pady=0)

        self.check_button = tk.Button(frame_bt, text="Check for updates", command=self.press_check)
        self.check_button.pack(side=tk.LEFT, padx=10, pady=0)

        self.close_button = tk.Button(frame_bt, text="Cancel", command=quit)
        self.close_button.pack(side=tk.RIGHT, padx=10, pady=0)

        self.update_lib_items()
        self.update_selection()

    def update_lib_items(self):
        index = 0
        lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
        lib_list_file_path = os.path.join(self.prj_dir_base, self.lib_list_file_rel_dir, self.lib_list_file_name)
        lib_list = self.load_lib_list(lib_list_file_path)

        self.lib_items = []
        
        for info in lib_list:
            lib_path = os.path.join(lib_dir, info["name"])
            lib_state = "X"
            if os.path.exists(lib_path) and os.path.isdir(lib_path):
                lib_state = "O"
            self.lib_items.append({"index": index, "name": info["name"], "url": info["url"], "branch": info["branch"], "installed": lib_state})
            index += 1

        self.config_len = index

        self.tv.delete(*self.tv.get_children())
        for conf in self.lib_items:
            self.tv.insert(parent='', index=conf["index"], iid=conf["index"],  values=(conf["index"], conf["name"], conf["url"], conf["branch"], conf["installed"]))

        if debug_level >= 3:
            for conf in self.lib_items:
                print(conf)
            print("")

    def update_selection(self):
        if self.lib_items[self.lib_item_idx]["name"] == "ubinos":
            self.install_button.config(state=tk.DISABLED)
            self.uninstall_button.config(state=tk.DISABLED)
            self.check_button.config(state=tk.NORMAL)
        elif self.lib_items[self.lib_item_idx]["installed"] != "X":
            self.install_button.config(state=tk.DISABLED)
            self.uninstall_button.config(state=tk.NORMAL)
            self.check_button.config(state=tk.NORMAL)
        else:
            self.install_button.config(state=tk.NORMAL)
            self.uninstall_button.config(state=tk.DISABLED)
            self.check_button.config(state=tk.DISABLED)
        self.tv.selection_set(self.lib_item_idx)
        self.tv.see(self.lib_item_idx)

    def load_lib_list(self, config_file_path):
        try:
            with file_open(config_file_path, 'r') as file:
                lib_list = json.load(file)
                return lib_list
        except Exception as e:
            print('Exception occurred.', e, config_file_path)


    def print_selection(self):
        selection = self.lib_items[self.lib_item_idx]
        print(selection)
        print("")

    def select_item(self, event):
        item = self.tv.focus()
        if item != '':
            self.lib_item_idx = int(item)
            self.update_selection()
            if debug_level >= 2:
                self.print_selection()

    def key_pressed(self, event):
        # print(event.keysym)
        if event.keysym == "Escape":
            self.quit()
        elif event.keysym == "Up":
            if self.lib_item_idx > 0:
                self.lib_item_idx -= 1
                self.update_selection()
                if debug_level >= 2:
                    self.print_selection()
        elif event.keysym == "Down":
            if self.lib_item_idx < (self.config_len - 1):
                self.lib_item_idx += 1
                self.update_selection()
                if debug_level >= 2:
                    self.print_selection()

    def press_install(self):
        if self.config_len > 0:
            if debug_level >= 1:
                print("Install library\n")
                self.print_selection()

            lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
            selection = self.lib_items[self.lib_item_idx]
            target_dir = os.path.join(lib_dir, selection["name"])
            self.git_commands = []
            self.git_commands.append("git submodule add -f " + selection["url"] + " " + target_dir)
            self.git_commands.append("cd "  + target_dir + "; git checkout -f " + selection["branch"])
            # self.git_commands.append("git submodule status " + target_dir)
            self.run_dialog = run_dialog(self)
            self.run_dialog.title("Install library commands")
            self.run_dialog.set_command(self.git_commands)
            self.run_dialog.grab_set()

    def press_uninstall(self):
        if self.config_len > 0:
            if debug_level >= 1:
                print("Uninstall library\n")
                self.print_selection()

            lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
            selection = self.lib_items[self.lib_item_idx]
            target_dir = os.path.join(lib_dir, selection["name"])
            git_dir = os.path.join(self.prj_dir_base, ".git", "modules", selection["name"])
            self.git_commands = []
            self.git_commands.append("git submodule deinit -f " + target_dir)
            self.git_commands.append("rm -rf " + git_dir)
            self.git_commands.append("git rm -f " + target_dir)
            # self.git_commands.append("git config -f " + os.path.join(self.prj_dir_base, ".gitmodules") 
            #                          + " --remove-section submodule." 
            #                          + os.path.basename(target_dir))
            self.run_dialog = run_dialog(self)
            self.run_dialog.title("Uninstall library commands")
            self.run_dialog.set_command(self.git_commands)
            self.run_dialog.grab_set()

    def press_check(self):
        if self.config_len > 0:
            if debug_level >= 1:
                print("Check for library updates\n")
                self.print_selection()

            lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
            selection = self.lib_items[self.lib_item_idx]
            target_dir = os.path.join(lib_dir, selection["name"])
            git_dir = os.path.join(self.prj_dir_base, ".git", "modules", selection["name"])
            self.git_commands = []
            self.git_commands.append("cd "  + target_dir + "; git fetch" + "; git status")
            self.run_dialog = run_dialog(self)
            self.run_dialog.title("Check for library updates commands")
            self.run_dialog.set_command(self.git_commands)
            self.run_dialog.grab_set()

    def press_run_dialog_close(self):
        self.run_dialog.destroy()
        self.deiconify()

    def press_run_dialog_run(self):
        result = False
        self.run_dialog.set_running(True)

        for cmd in self.git_commands:
            result = self.run_git_command(cmd)
            if not result:
                messagebox.showinfo(
                    title='Result',
                    message="Failed",
                )
                break

        if result:
            messagebox.showinfo(
                title='Result',
                message="Succeeded",
            )
            # self.run_dialog.destroy()
            # self.deiconify()
            # self.quit()

        self.run_dialog.set_running(False)
        self.run_dialog.set_runable(False)

        self.update_lib_items()
        self.update_selection()

    def run_git_command(self, command):
        result = False
        self.run_dialog.clear_result()
        self.run_dialog.append_result(command + "\n")
        try:
            process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=1, universal_newlines=True)
            for line in process.stdout:
                self.run_dialog.append_result(line)
            for line in process.stderr:
                self.run_dialog.append_result(line)
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
