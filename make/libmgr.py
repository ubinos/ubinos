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

from ttkwidgets import CheckboxTreeview

from collections import Counter

debug_level = 1

true_string = "O"
false_string = "X"
unknown_string = "-"

def print_help():
    print("===============================================================================")
    print("Usage:")
    print("    python %s <project base dir> <library relative dir>" % (sys.argv[0]))
    print("===============================================================================")

def set_geometry_center(win, width, height):
    screen_width = win.winfo_screenwidth()
    screen_height = win.winfo_screenheight()
    # screen_width = win.winfo_screenwidth() // 2
    # screen_height = win.winfo_screenheight() // 2
    x_cordinate = (screen_width  // 2) - (width  // 2)
    y_cordinate = (screen_height // 2) - (height // 2)
    win.geometry("{}x{}+{}+{}".format(width, height, x_cordinate, y_cordinate))

def set_dialog_geometry_center(parent, win, width, height):
    parent_width = parent.winfo_width()
    parent_height = parent.winfo_height()
    parent_x = parent.winfo_x()
    parent_y = parent.winfo_y()
    x_cordinate = (parent_width  // 2) - (width  // 2) + parent_x - 10
    y_cordinate = (parent_height // 2) - (height // 2) + parent_y - 40
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
        
        set_dialog_geometry_center(parent, self, 1100, 600)

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
    def __init__(self, prj_dir_base, lib_rel_dir):
        super().__init__()

        self.prj_dir_base = ".."
        self.lib_rel_dir = "library"
        self.lib_list_file_name = "liblist.json"
        self.lib_list_file_rel_dir = os.path.join(lib_rel_dir, "ubinos", "make")
        self.lib_custom_list_file_rel_dir = "make"

        self.lib_items = []
        self.lib_items_updatable = []
        self.lib_item_idx = 0
        self.lib_item_idx_prev = 0
        self.git_commands = []

        self.run_command_type = ""

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

        self.tv = CheckboxTreeview(frame_tv)
        self.tv["columns"] = ("Name", "URL", "Branch", "I", "M", "U")
        self.tv.pack(fill="both", expand=True)
        self.tv.grid(row=0, column=0, sticky="nsew")
        self.tv.tag_configure("checked", background="palegoldenrod")

        sb = tk.Scrollbar(frame_tv, orient=tk.VERTICAL)
        sb.grid(row=0, column=1, sticky="ns")
        self.tv.config(yscrollcommand=sb.set)
        sb.config(command=self.tv.yview)

        self.tv.bind('<ButtonRelease-1>', self.button_release_1)

        self.tv.heading("#0", text="Index") # Index
        self.tv.column("#0", width=80)
        self.tv.heading("Name", text="Name")
        self.tv.column("Name", width=200)
        self.tv.heading("URL", text="URL")
        self.tv.column("URL", width=530)
        self.tv.heading("Branch", text="Branch")
        self.tv.column("Branch", width=100)
        self.tv.heading("I", text="I", anchor=tk.CENTER) # Installed
        self.tv.column("I", width=20, anchor=tk.CENTER)
        self.tv.heading("M", text="M", anchor=tk.CENTER) # Modified
        self.tv.column("M", width=20, anchor=tk.CENTER)
        self.tv.heading("U", text="U", anchor=tk.CENTER) # Updatable
        self.tv.column("U", width=20, anchor=tk.CENTER)

        ##
        frame_bt = tk.Frame(self)
        frame_bt.grid(row=1, column=0, sticky="nsew", padx=10, pady=20)

        self.install_button = tk.Button(frame_bt, text="Install", command=self.press_install)
        self.install_button.pack(side=tk.LEFT, padx=4, pady=0)

        self.uninstall_button = tk.Button(frame_bt, text="Uninstall", command=self.press_uninstall)
        self.uninstall_button.pack(side=tk.LEFT, padx=4, pady=0)

        self.reset_button = tk.Button(frame_bt, text="Reset", command=self.press_reset)
        self.reset_button.pack(side=tk.LEFT, padx=4, pady=0)

        self.update_button = tk.Button(frame_bt, text="Update", command=self.press_update)
        self.update_button.pack(side=tk.LEFT, padx=4, pady=0)

        self.close_button = tk.Button(frame_bt, text="Close", command=quit)
        self.close_button.pack(side=tk.RIGHT, padx=4, pady=0)

        self.check_all_button = tk.Button(frame_bt, text="Check for update all", command=self.press_check)
        self.check_all_button.pack(side=tk.RIGHT, padx=40, pady=0)

        self.update_lib_items()

    def update_lib_items(self):
        lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)

        lib_list_file_path = os.path.join(self.prj_dir_base, self.lib_list_file_rel_dir, self.lib_list_file_name)
        lib_list = self.load_lib_list(lib_list_file_path)

        lib_custom_list_file_path = os.path.join(self.prj_dir_base, self.lib_custom_list_file_rel_dir, self.lib_list_file_name)
        if os.path.exists(lib_custom_list_file_path):
            lib_list_custom = self.load_lib_list(lib_custom_list_file_path)
            lib_list += lib_list_custom

        self.lib_items = []
        for i, lib_info in enumerate(lib_list):
            lib_path = os.path.join(lib_dir, lib_info["name"])
            lib_installed = unknown_string
            lib_local_branch = unknown_string
            lib_modified = unknown_string
            lib_updatable = unknown_string
            lib_local_url = unknown_string

            if os.path.exists(lib_path) and os.path.isdir(lib_path):
                lib_installed = true_string
                lib_local_branch = self.git_local_branch(lib_info["name"])
                if lib_local_branch != unknown_string:
                    lib_local_url = self.git_local_urls(lib_info["name"])[0]
                    if self.git_check_modified(lib_info["name"]):
                        lib_modified = true_string
                    else:
                        lib_modified = false_string
                        if lib_local_branch == "HEAD":
                            if self.git_checkout_branch(lib_info["name"], lib_info["branch"]):
                                lib_local_branch = self.git_local_branch(lib_info["name"])

                    for item_updatable in self.lib_items_updatable:
                        if item_updatable["name"] == lib_info["name"] and item_updatable["url"] == lib_info["url"] and item_updatable["branch"] == lib_info["branch"]:
                            lib_updatable = true_string
            else:
                lib_installed = false_string

            self.lib_items.append({"index": i, 
                                   "name": lib_info["name"], 
                                   "url": lib_info["url"], 
                                   "local_url": lib_local_url, 
                                   "branch": lib_info["branch"], 
                                   "local_branch": lib_local_branch, 
                                   "installed": lib_installed, 
                                   "modified": lib_modified, 
                                   "updatable": lib_updatable})

        self.tv.delete(*self.tv.get_children())
        for lib_item in self.lib_items:
            index = lib_item["index"]
            self.tv.insert(parent="", index=lib_item["index"], iid=lib_item["index"],
                            text=f"{index + 1}",
                            values=(
                                lib_item["name"], 
                                lib_item["local_url"] if lib_item["local_url"] != unknown_string else lib_item["url"], 
                                lib_item["local_branch"] if lib_item["local_branch"] != unknown_string else lib_item["branch"], 
                                lib_item["installed"], 
                                lib_item["modified"], 
                                lib_item["updatable"]))

        if debug_level >= 3:
            for lib in self.lib_items:
                print(lib)
            print("")

        self.update_selection()

    def update_selection(self):
        include_ubinos = False
        include_installed = False
        include_not_installed = False
        include_modified = False
        include_not_modified = False
        include_updatable = False
        include_not_updatable = False
        checked_items = self.tv.get_checked()
        for index in checked_items:
            item = self.lib_items[int(index)]
            if item["name"] == "ubinos":
                include_ubinos = True

            if item["installed"] == true_string:
                include_installed = True
            else:
                include_not_installed = True

            if item["modified"] == true_string:
                include_modified = True
            else:
                include_not_modified = True

            if item["updatable"] == true_string:
                include_updatable = True
            else:
                include_not_updatable = True

        if include_ubinos:
            self.install_button.config(state=tk.DISABLED)
            self.uninstall_button.config(state=tk.DISABLED)
        else:
            if include_installed and not include_not_installed:
                self.install_button.config(state=tk.DISABLED)
                self.uninstall_button.config(state=tk.NORMAL)
            elif include_not_installed and not include_installed:
                self.install_button.config(state=tk.NORMAL)
                self.uninstall_button.config(state=tk.DISABLED)
            else:
                self.install_button.config(state=tk.DISABLED)
                self.uninstall_button.config(state=tk.DISABLED)
        
        if include_modified and not include_not_modified:
            self.reset_button.config(state=tk.NORMAL)
        else:
            self.reset_button.config(state=tk.DISABLED)

        if include_updatable and not include_not_updatable:
            self.update_button.config(state=tk.NORMAL)
        else:
            self.update_button.config(state=tk.DISABLED)

        self.check_all_button.config(state=tk.NORMAL)

        index = self.lib_item_idx_prev
        self.tv.item(index, text=f"{index + 1}")
        index = self.lib_item_idx
        self.tv.item(index, text=f"{index + 1}<-")
        self.tv.selection_set(index)
        self.tv.see(index)

    def load_lib_list(self, file_path):
        try:
            with file_open(file_path, 'r') as file:
                lib_list = json.load(file)
                return lib_list
        except Exception as e:
            print('Exception occurred.', e)

    def print_selection(self):
        selection = self.lib_items[self.lib_item_idx]
        print(selection)
        print("")

    def select_item(self, index):
        self.lib_item_idx_prev = self.lib_item_idx
        self.lib_item_idx = index
        self.update_selection()
        if debug_level >= 2:
            self.print_selection()

    def button_release_1(self, event):
        item = self.tv.focus()
        if item != '':
            self.select_item(int(item))

    def key_pressed(self, event):
        # print(event.keysym)
        if event.keysym == "Escape":
            self.quit()
        elif event.keysym == "Up":
            if self.lib_item_idx > 0:
                self.select_item(self.lib_item_idx - 1)
        elif event.keysym == "Down":
            if self.lib_item_idx < (len(self.lib_items) - 1):
                self.select_item(self.lib_item_idx + 1)
        elif event.keysym == "space":
            state = self.tv.item(self.lib_item_idx, "tag")[0]
            if state == "checked":
                state = "unchecked"
            elif state == "unchecked":
                state = "checked"
            self.tv.change_state(self.lib_item_idx, state)
            self.update_selection()

    def press_install(self):
        if len(self.lib_items) > 0:
            if debug_level >= 1:
                print("Install library\n")
                self.print_selection()

            checked_items = self.tv.get_checked()
            if len(checked_items) > 0:
                lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
                self.run_command_type = "install"
                self.git_commands = []
                for index in checked_items:
                    selection = self.lib_items[int(index)]
                    target_dir = os.path.join(lib_dir, selection["name"])
                    source_url = selection["url"]
                    source_branch = selection["branch"]
                    self.git_commands.append(f"git submodule add -f {source_url} {target_dir}")
                    self.git_commands.append(f"cd {target_dir}; git checkout -f {source_branch}")
                self.run_dialog = run_dialog(self)
                self.run_dialog.title("Install library commands")
                self.run_dialog.set_command(self.git_commands)
                self.run_dialog.grab_set()

    def press_uninstall(self):
        if len(self.lib_items) > 0:
            if debug_level >= 1:
                print("Uninstall library\n")
                self.print_selection()

            checked_items = self.tv.get_checked()
            if len(checked_items) > 0:
                lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
                self.run_command_type = "uninstall"
                self.git_commands = []
                for index in checked_items:
                    selection = self.lib_items[int(index)]
                    target_dir = os.path.join(lib_dir, selection["name"])
                    target_base_name = os.path.basename(target_dir)
                    git_dir = os.path.join(self.prj_dir_base, ".git", "modules", selection["name"])
                    dot_gitmodule_path = os.path.join(self.prj_dir_base, ".gitmodules")
                    self.git_commands.append(f"git submodule deinit -f {target_dir}")
                    self.git_commands.append(f"rm -rf {git_dir}")
                    self.git_commands.append(f"git rm -f {target_dir}")
                    # self.git_commands.append(f"git config -f {dot_gitmodule_path} --remove-section submodule.{target_base_name}")
                self.run_dialog = run_dialog(self)
                self.run_dialog.title("Uninstall library commands")
                self.run_dialog.set_command(self.git_commands)
                self.run_dialog.grab_set()

    def press_reset(self):
        if len(self.lib_items) > 0:
            if debug_level >= 1:
                print("Reset library\n")
                self.print_selection()

            checked_items = self.tv.get_checked()
            if len(checked_items) > 0:
                lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
                self.run_command_type = "reset"
                self.git_commands = []
                for index in checked_items:
                    selection = self.lib_items[int(index)]
                    target_dir = os.path.join(lib_dir, selection["name"])
                    self.git_commands.append(f"cd {target_dir}; git reset --hard HEAD")
                    self.git_commands.append(f"cd {target_dir}; git clean -fd")
                self.run_dialog = run_dialog(self)
                self.run_dialog.title("Uninstall library commands")
                self.run_dialog.set_command(self.git_commands)
                self.run_dialog.grab_set()

    def press_check(self):
        if len(self.lib_items) > 0:
            if debug_level >= 1:
                print("Check library updatable all\n")
                self.print_selection()

            self.lib_items_updatable = []
            for lib_item in self.lib_items:
                item_updatable = {"name": lib_item["name"], "url": lib_item["url"], "branch": lib_item["branch"]}
                if self.git_check_updatable(lib_item["name"]):
                    self.lib_items_updatable.append(item_updatable)

            if debug_level >= 1:
                print(self.lib_items_updatable)

            self.update_lib_items()

    def press_update(self):
        if len(self.lib_items) > 0:
            if debug_level >= 1:
                print("Update library\n")
                self.print_selection()

            checked_items = self.tv.get_checked()
            if len(checked_items) > 0:
                lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
                self.run_command_type = "update"
                self.git_commands = []
                for index in checked_items:
                    selection = self.lib_items[int(index)]
                    target_dir = os.path.join(lib_dir, selection["name"])
                    self.git_commands.append(f"cd {target_dir}; git pull")
                self.run_dialog = run_dialog(self)
                self.run_dialog.title("Uninstall library commands")
                self.run_dialog.set_command(self.git_commands)
                self.run_dialog.grab_set()

    def press_run_dialog_close(self):
        self.run_command_type = ""
        self.run_dialog.destroy()
        self.deiconify()

    def press_run_dialog_run(self):
        result = False
        self.run_dialog.set_running(True)
        self.run_dialog.clear_result()

        for cmd in self.git_commands:
            result = self.run_git_command_with_dialog(cmd)
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

        self.run_dialog.set_running(False)
        self.run_dialog.set_runable(False)

        if self.run_command_type == "update":
            self.press_check()

        self.update_lib_items()

        self.run_command_type = ""

    def run_git_command_with_dialog(self, command):
        result = False
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
            print('Exception occurred.', e)
        
        return result

    def run_git_command(self, directory, command):
        result = None

        try:
            result = subprocess.run(command, cwd=directory, capture_output=True, text=True, check=True)
        except Exception as e:
            print('Exception occurred.', e)
        
        return result

    def git_check_updatable(self, name):
        lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
        target_dir = os.path.join(lib_dir, name)
        git_command = ["git", "fetch"]
        result = self.run_git_command(target_dir, git_command)
        if debug_level >= 1:
            print(result)
        
        local_branch = self.git_local_branch(name)
        if local_branch == "HEAD":
            return False
        
        git_command = ['git', 'log', f'{local_branch}..origin/{local_branch}']
        result = self.run_git_command(target_dir, git_command)
        if debug_level >= 1:
            print(result)

        if result != None and result.stdout.strip():
            return True
        else:
            return False

    def git_checkout_branch(self, name, branch):
        lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
        target_dir = os.path.join(lib_dir, name)
        git_command = ["git", "checkout", "-f", branch]
        result = self.run_git_command(target_dir, git_command)
        if debug_level >= 1:
            print(result)
        
        if result != None and result.returncode == 0:
            return True
        else:
            return False

    def git_check_modified(self, name):
        lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
        target_dir = os.path.join(lib_dir, name)
        git_command = ["git", "status", "--porcelain"]
        result = self.run_git_command(target_dir, git_command)
        if debug_level >= 1:
            print(result)
        
        if result != None and result.stdout.strip():
            return True
        else:
            return False

    def git_local_branch(self, name):
        lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
        target_dir = os.path.join(lib_dir, name)
        git_command = ['git', 'rev-parse', '--abbrev-ref', 'HEAD']
        result = self.run_git_command(target_dir, git_command)
        if debug_level >= 1:
            print(result)
        if result != None:
            return result.stdout.strip()
        else:
            return unknown_string

    def git_local_urls(self, name):
        lib_dir = os.path.join(self.prj_dir_base, self.lib_rel_dir)
        target_dir = os.path.join(lib_dir, name)
        git_command = ["git", "remote", "-v"]
        result = self.run_git_command(target_dir, git_command)
        if debug_level >= 1:
            print(result)
        if result != None:
            output_lines = result.stdout.splitlines()
            remote_urls = []
            for line in output_lines:
                parts = line.split()
                if len(parts) >= 2:
                    if (parts[0] == "origin"):
                        remote_urls.append(parts[1])
            for line in output_lines:
                parts = line.split()
                if len(parts) >= 2:
                    if (parts[0] != "origin"):
                        remote_urls.append(parts[1])

            return remote_urls
        else:
            return unknown_string

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
