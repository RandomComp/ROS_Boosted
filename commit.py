import sys

import subprocess

from pathlib import Path

from typing import Iterator, Any, Generator, Iterable, TextIO

from types import FunctionType

import os

import zipfile

import traceback

import time

import json.decoder

from math import floor, ceil

import re

def log(message: object="", end: str="\n", out: TextIO=sys.stdout) -> None:
	out.write(str(message).expandtabs(4) + end)

def system(command: str) -> str:
	log(command)

	return subprocess.getoutput(f"(chcp 65001 >nul) & {command}", encoding="utf-8")

def get_commits_hash() -> list[str]:
	this = get_commits_hash

	if (not hasattr(this, "commits_hash")):
		this.commits_hash = system("git rev-list --first-parent HEAD").splitlines()

	return this.commits_hash

def get_commit_count() -> int:
	return len(get_commits_hash())

def update_version_index(obj: Path) -> int:
	result = get_commit_count()

	log(result)

	if (not obj.is_file()):
		log(f"File \"{obj}\" is not existing, creating new...")

	obj.write_text(str(result))

	return result

def check_version_index(obj: Path) -> int:
	if (not obj.is_file() or not obj.read_text().isnumeric()):
		return update_version_index(obj)
	
	return int(obj.read_text())

gitignore = [r".*.o$",
		   r".*.VSCODE-DB$",
		   r"^\.",
		   r".*.exe$"]

def check_for_matching_gitignore(str: str) -> bool:
	for reg in gitignore:
		if not reg: continue

		if re.match(reg, str):
			return True
	
	return False
		
def get_local_file_list() -> list[Path]:
	result: list[Path] = []

	for obj in Path(".").rglob("*"):
		if not obj.is_file(): continue

		if not check_for_matching_gitignore(str(obj)):
			result.append(obj)

	return result

def get_local_folder_list() -> list[Path]:
	result: list[Path] = []

	for obj in Path(".").rglob("*"):
		if not obj.is_dir(): continue

		if not check_for_matching_gitignore(str(obj)):
			result.append(obj)

	return result

def get_folder_list_from_files(files_path: list[Path], root: Path=Path(".")) -> list[Path]:
	root = root.resolve()

	files = map(Path.resolve, files_path)

	result = []

	for file in files:
		parent = file.parent
		
		if parent not in result:
			result.append(parent)
	
	return result
		
def get_remote_file_list(hash: str) -> list[str]:
	this = get_remote_file_list

	key = hash

	if check_cache(this, key):
		return this.cache[key]
	
	result =  system(f"git ls-tree -r {hash} --name-only").splitlines()

	this.cache[key] = result

	return result

def get_remote_folder_list(hash: str) -> list[str]:
	result = []

	this = get_remote_folder_list

	key = hash

	if check_cache(this, key):
		return this.cache[key]
	
	for file in get_remote_file_list(hash):
		folder = Path(file).parent

		if folder not in result:
			result.append(folder)
	
	this.cache[key] = result
	
	return result

def get_remote_object_list(hash: str) -> list[str]:
	return get_remote_folder_list(hash) + get_remote_file_list(hash)

def check_for_path_including_match(obj: Path, includings: list[str]=[]) -> bool:
	if (not includings): return False

	return any(	including in parent.name
				for parent in obj.parents
				for including in includings)

def get_files_in(obj: Path, notincluding: list[str]=[]) -> Iterator[Path]:
	if (check_for_path_including_match(obj, notincluding)):
		return

	if (obj.is_file()):
		yield obj; return

	for object in obj.iterdir():
		yield from get_files_in(object, notincluding)

def get_folders_in(obj: Path, notincluding: list[str]=[""]) -> Iterator[Path]:
	if (obj.is_file() or check_for_path_including_match(obj, notincluding)):
		return

	yield obj

	for object in obj.iterdir():
		yield from get_folders_in(object, notincluding)

def get_size(obj: Path) -> int:
	if obj.is_file():
		return obj.stat().st_size
	elif obj.is_dir():
		return sum(get_size(object) for object in obj.iterdir())
	
	return 0

def get_short_formated_size(bytes: int) -> str:
	base = 1024

	gb_base = base ** 3

	mb_base = base ** 2

	kb_base = base ** 1

	if bytes < kb_base:
		return f"{bytes} B"

	elif bytes < mb_base:
		return f"{(bytes / kb_base):.2f} KB"

	elif bytes < gb_base:
		return f"{(bytes / mb_base):.2f} MB"

	return f"{(bytes / gb_base):.2f} GB"

def get_formated_size(bytes: int) -> str:
	base = 1024

	gb_base = base ** 3

	mb_base = base ** 2

	kb_base = base ** 1

	gb = int(bytes / gb_base)

	mb = int((bytes % gb_base) / mb_base)

	kb = int((bytes % mb_base) / kb_base)

	b = bytes % kb_base

	result = ""

	if (gb > 0):
		result += f"{gb} GB "

	if (mb > 0):
		result += f"{mb} MB "

	if (kb > 0):
		result += f"{kb} KB "

	if (len(result) == 0 or b > 0):
		result += f"{b} B"

	return result

def create_backup_zip(backup_name: str) -> None:
	start_backup_operations_time = time.perf_counter()

	start = time.perf_counter()

	cur_dir = Path(".").absolute()

	log(f"Creating a backup zip archive \"{backup_name}\" for folder \"{cur_dir.absolute()}\" in progress...")

	size = 0

	files = get_files_in(cur_dir, [".", "backup"])

	backup_dir = Path("backups")

	backup_file = backup_dir / backup_name

	backup_dir.mkdir(exist_ok=True)

	with zipfile.ZipFile(backup_file, "w") as f:
		for file in files:
			size += get_size(file)

			f.write(file)
	
	processor_time = time.perf_counter() - start

	log(f"Backup creating processor time: {processor_time * 1000} ms")

	log(f"Successfully created backup zip file \"{backup_file}\" for folder \"{cur_dir.absolute()}\"!")

	log(f"Copying backup zip file for other volumes in progress...")

	start = time.perf_counter()

	mounts_list = map(os.listmounts, os.listvolumes())

	for volume in mounts_list:
		for mount in volume:
			if not mount: continue

			start_copying_time = time.perf_counter()

			backup_dir = Path(mount) / Path(backup_dir.name)

			backup_dir.mkdir(exist_ok=True)

			log(f"Copying for volume {mount} to {backup_dir / backup_name} in progress...")

			backup_file.copy_into(backup_dir)

			processor_time = time.perf_counter() - start_copying_time

			log(f"Copying to {backup_dir / backup_name} processor time: {processor_time * 1000:.6f} ms")

			log()
	
	processor_time = time.perf_counter() - start

	log(f"Backup copy to other volumes processor time: {processor_time * 1000:.6f} ms")

	processor_time = time.perf_counter() - start_backup_operations_time

	log(f"Backup operations processor time: {processor_time * 1000:.6f} ms")

def check_cache(this, key) -> Any:
	if (not hasattr(this, "cache")):
		this.cache = dict()
	
	return key in this.cache

def get_commit_by_hash(hash: str) -> dict:
	this = get_commit_by_hash

	key = hash

	if check_cache(this, key):
		return this.cache[key]
	
	result = system(f"gh api /repos/RandomComp/RandomOS_Boosted/commits/{hash}")

	this.cache = result = json.decoder.JSONDecoder().decode(result)

	return result

def read_file_from_commit(hash: str, file_name: Path) -> str:
	this = read_file_from_commit

	key = (hash, file_name)

	if check_cache(this, key):
		return this.cache[key]
	
	this.cache[key] = result = system(f"git show {hash}:{file_name}")

	return result

def get_matching_files_from_commits(file_name: str) -> list[tuple[str, Path]]:
	commits_hash = get_commits_hash()

	key = file_name

	this = get_matching_files_from_commits

	result = []

	if check_cache(this, key):
		return this.cache[key]

	result = [	(commit_hash, Path(file)) 
		   		for commit_hash in commits_hash 
				for file in get_remote_file_list(commit_hash)
				if file_name == file]
	
	this.cache[key] = result

	return result

def get_file_versions(file: str) -> Generator[str]:
	commits_hash = get_commits_hash() 

	for commit_hash in commits_hash:
		remote_file_list = get_remote_file_list(commit_hash)
		
		for remote_file in remote_file_list:
			if Path(remote_file).name == file:
				yield remote_file

				break

def get_file_max_version(file: str) -> int:
	return len(list(get_file_versions(file)))

def get_file_from_commit(file_name: str, file_ver: int) -> str:
	this = get_file_from_commit

	key = (file_name, file_ver)
	
	if check_cache(this, key):
		return this.cache[key]

	files = get_matching_files_from_commits(file_name)

	hash, file = files[file_ver]

	result = ""

	try:
		this.cache[key] = result = read_file_from_commit(hash, file)
	except UnicodeDecodeError as e:
		log(f"Error: {e}")

	return result

def clear_cache(this: FunctionType):
	if (not hasattr(this, "cache")):
		this.cache = dict()
	else:
		this.cache.clear()

def git_fetch_origin() -> None:
	system("git fetch origin")

	if hasattr(get_commits_hash, "commits_hash"):
		del get_commits_hash.commits_hash

	clear_cache(get_commit_by_hash)
	clear_cache(get_file_from_commit)
	clear_cache(get_remote_file_list)
	clear_cache(read_file_from_commit)
	clear_cache(get_matching_files_from_commits)

def get_file_list(new_commit_hash: str="", old_commit_hash: str="HEAD", filter: str="") -> dict[Path | int, Path]:
	command = f"git diff {new_commit_hash} {old_commit_hash} --find-copies-harder --name-status"

	if filter:
		command += f" --diff-filter={filter}"

	lines = system(command).splitlines()

	result: dict[Path | int, Path] = dict()

	for i, line in enumerate(lines):
		temp_result = line.split("\t")

		source_name = Path(temp_result[1])

		if (len(temp_result) == 2):
			result[i] = source_name

		elif (len(temp_result) == 3):
			dest_name = Path(temp_result[2])

			result[source_name] = dest_name

	return result

def sub_array(a: list, b: list) -> list:
	return [elem for elem in a if elem not in b]

def get_cur_struct_time() -> tuple[int, int, int, int, int, int]:
	cur_time = time.localtime()

	return cur_time.tm_year, cur_time.tm_mon, cur_time.tm_mday, cur_time.tm_hour, cur_time.tm_min, cur_time.tm_sec

def get_ISO_8601_time(s_time: tuple[int, int, int, int, int, int]) -> str:
	return f"{s_time[0]:04d}-{s_time[1]:02d}-{s_time[2]:02d}T{s_time[3]:02d}:{s_time[4]:02d}:{s_time[5]:02d}"
	
def normalize_dir(dir: Path, root=None) -> Path:
	result = dir.resolve()

	if root is not None:
		return result.relative_to(root.resolve())
	
	return result

def split_lines_for_length(content: str, max_width: int) -> list[str]:
	file_lines = content.expandtabs(4).splitlines()

	result = []

	for line in file_lines:
		line_len = len(line)

		dest_len = min(line_len, max_width)

		if line_len <= dest_len:
			result.append(line)
		else:
			result.append(line[:dest_len])

			result.extend(split_lines_for_length(line[dest_len:], dest_len))

	return result

def avg(l: Iterable, default=None) -> float:
	l = list(l)

	length = len(l)

	if length == 0:
		if default is not None:
			return default
		else:
			raise ValueError("avg() arg is an empty sequence")

	return sum(l) / length

def ceil_int(x: int, y: int) -> int:
	if x % y == 0: return x

	return (int(x / y) + 1) * y

def CLI_help(root: Path, cur_dir: Path, args: list[str]) -> tuple[bool, Path]:
	commands = {"cd": 		"cd <dir> Changes the current directory to the specified directory",
				"dir": 		"dir <dir> Displays a folders/files in current or specified directory",
				"cat": 		"cat <file> Displays a file",
				"clear": 	"clear <without-arg> Clears a console",
				"alias":	"alias <new_command_name> <old_command_name> Creates an alias for a specified command",
			 	"ignore": 	"ignore <file> Add file to .gitignore",
				"deignore": "deignore <file> Delete file from .gitignore",
				"quit": 	"quit <without-arg> Close the CLI"
				}
	
	max_description_len = max(map(len, commands.values()))

	for arg in args:
		if not arg in commands:
			log(f"Error: Unrecognized command \"{arg}\"")
		else:
			log(f"{arg} - {commands[arg].ljust(max_description_len)}")

	if not args:
		for command in commands:
			log(f"{command} - {commands[command]}")
	
	return False, cur_dir

def CLI_cd(root: Path, cur_dir: Path, args: list[str]) -> tuple[bool, Path]:
	if not args: return False, cur_dir

	arg = Path(' '.join(args))

	dest_path = cur_dir / arg

	result = cur_dir

	if not dest_path.exists():
		log(f"Error: Directory \"{dest_path}\" does not exist")
	elif dest_path.is_file():
		log(f"Error: Directory \"{dest_path}\" is not a directory, it's a file")

		log(f"Note: Type \"cat {dest_path}\" to see file content")

	else:
		try:
			result = normalize_dir(dest_path, root)
		except ValueError:
			log(f"Error: Cannot leave the working folder")

			result = cur_dir

	return False, result

def CLI_dir(root: Path, _cur_dir: Path, args: list[str]) -> tuple[bool, Path]:
	if len(args) >= 0: _, cur_dir = CLI_cd(root, _cur_dir, args)

	log(f"Directory of \"{cur_dir}\": ")

	for obj in cur_dir.iterdir():
		log(f"\t{obj.relative_to(cur_dir)}", end="")

		if obj.is_dir():
			log("/", end="")
		
		log()

	return False, _cur_dir

def CLI_cat(root: Path, _cur_dir: Path, args: list[str]) -> tuple[bool, Path]:
	cur_dir = _cur_dir.absolute()

	for arg in args:
		try:
			file_path = normalize_dir(cur_dir / arg, root)
		except ValueError:
			log(f"Error: Cannot leave the working folder")

			break

		if (file_path.is_file()):
			try:
				file_content = file_path.read_text()
			except UnicodeDecodeError:
				log(f"Error: file {file_path} it's a binary file, not text")

				break

			file_lines = file_content.splitlines()

			file_lines_len = list(map(len, file_lines))

			term_size = os.get_terminal_size()

			width = term_size.columns

			coef = 5 / 6

			file_lines_count = len(file_lines)

			file_lines_count_digit_count = len(str(file_lines_count))
			
			max_line_len_digit_count = len(str(max(map(len, file_lines))))

			max_file_lines_len = max(file_lines_len)

			outline_size = 2 + 2 + 3 + file_lines_count_digit_count 

			max_width = int(min(width * coef, ceil_int(floor(max(file_lines_len) - avg(file_lines_len)), 20)))

			if max_width == 0 or max_file_lines_len - max_width <= width / 8:
				max_width = max_file_lines_len
			
			max_width -= 4 + len("chars") + max_line_len_digit_count

			outline_size += max_width

			file_lines = split_lines_for_length(file_content, max_width)
			
			max_line_len_digit_count = len(str(max(map(len, file_lines))))

			log(f"Content of file \"{Path(arg).name}\": ")

			log(f"{"_" * outline_size}")

			for i, line in enumerate(file_lines):
				num_line = str(i).zfill(file_lines_count_digit_count)

				line_char_count = str(len(line.strip()))

				log(f"| {num_line} | {line.ljust(max_width)} | {line_char_count.rjust(max_line_len_digit_count)} chars")
			
			log(f"{"‾" * outline_size}")
		elif (file_path.is_dir()):
			log(f"Error: Directory \"{file_path}\" is not a file, it's a dir")

			log(f"Note: Type \"dir {file_path}\" to see dir content")
		elif (not file_path.exists()):
			log(f"Error: File \"{file_path}\" is not exist")
	
	return False, _cur_dir

def CLI_clear(root: Path, cur_dir: Path, args: list[str]) -> tuple[bool, Path]:
	os.system("cls")

	return False, cur_dir

alias: dict[str, str] = {}

def get_command(name: str) -> str:
	if name in commands:
		return name
	elif name in alias:
		return alias[name]
	
	log(f"Error: Command \"{name}\" not found.")
	
	return ""

def CLI_alias(root: Path, cur_dir: Path, args: list[str]) -> tuple[bool, Path]:
	if len(args) < 2:
		log(f"Error: Too few arguments, type \"help alias\" for help.")

		return False, cur_dir

	new_command_name = args[0]

	old_command_name = args[1]
			
	if old_command_name in commands:
		if new_command_name not in commands:
			alias[new_command_name] = ' '.join(args[1:])

			log(f"Succesfully created alias \"{args[0]}\" for command \"{args[1]}\"!")
		else:
			log(f"Error: Cannot override an existing command \"{args[0]}\" for \"{args[1]}\".")
	else:
		log(f"Error: Unrecognized command \"{args[1]}\", type \"help\" to see available commands.")
	
	return False, cur_dir

def CLI_unalias(root: Path, cur_dir: Path, args: list[str]) -> tuple[bool, Path]:
	if len(args) < 1:
		log(f"Error: Too few arguments, type \"help unalias\" for help.")
	elif len(args) > 1:
		log(f"Error: Too many arguments, type \"help unalias\" for help.")
	elif args[0] in alias:
		alias.pop(args[0])
	else:
		log(f"Error: Command \"{args[0]}\" not found.")

	return False, cur_dir

def CLI_quit(root: Path, cur_dir: Path, args: list[str]) -> tuple[bool, Path]:
	return True, cur_dir

commands: dict[str, FunctionType] = {
			"help": 	CLI_help,
			"cd": 		CLI_cd,
			"dir": 		CLI_dir,
			"cat": 		CLI_cat,
			"clear":	CLI_clear,
			"alias":	CLI_alias,
			"unalias":	CLI_unalias,
			"quit": 	CLI_quit
			}
	
def CLI_process_command(input: str, root: Path, cur_dir: Path) -> tuple[bool, Path]:
	inputed_command, *args = input.lstrip().lower().split(" ")

	isQuit = False

	if inputed_command in commands:
		command_func = commands[inputed_command]

		isQuit, cur_dir = command_func(root, cur_dir, args)
	elif inputed_command in alias:
		command = get_command(inputed_command)

		input = f"{command} {' '.join(args)}"
		
		CLI_process_command(input, root, cur_dir)
	elif not inputed_command: pass
	else:
		command_names = list(commands.keys()) + list(alias.keys())

		variants: list[str] = []
		
		for i, ch in enumerate(inputed_command):
			for command in command_names:
				if i < len(command) and command not in variants and command[i] == ch:
					variants.append(command)
		
		if not variants:
			variants = [command 
						for command in command_names 
						if inputed_command in command or command in inputed_command]

		if variants:
			log(f"Note: Did you mean \"{"\", \"".join(variants)}\"?")

		log(f"Error: Unrecognized command \"{inputed_command}\". Type help for help.")

	return (isQuit, cur_dir)

def CLI():
	root = Path(".").absolute()

	isQuit = False

	cur_dir = Path(".")

	CLI_alias(root, cur_dir, ["exit", "quit"])

	CLI_alias(root, cur_dir, ["cls", "clear"])

	CLI_alias(root, cur_dir, ["ls", "dir"])

	while not isQuit:
		inputed = input(f"{cur_dir}>")

		isQuit, cur_dir = CLI_process_command(inputed, root, cur_dir)

def show_git_edited_files(	added_files: 	dict[Path | int, Path]={}, 
			  				deleted_files: 	dict[Path | int, Path]={}, 
			   				modified_files: dict[Path | int, Path]={}, 
			   				copied_files: 	dict[Path | int, Path]={}, 
			   				renamed_files: 	dict[Path | int, Path]={}) -> None:
	
	ADDED, DELETED, MODIFIED, COPIED, RENAMED = range(5)

	old_files = {
		ADDED: len(added_files),
		DELETED: len(deleted_files),
		MODIFIED: len(modified_files),
		COPIED: len(copied_files),
		RENAMED: len(renamed_files)
	}

	files = dict(sorted(old_files.items(), key=lambda x: x[1]))

	files_keys = list(files.keys())

	files_keys.reverse()

	status_names = ["Added", 
				 	"Deleted", 
				 	"Modified", 
				 	"Copied", 
				 	"Renamed", 
				 	]
	
	status_dicts = [added_files,
					deleted_files,
					modified_files,
					copied_files,
					renamed_files
					]

	for file_key in files_keys:
		status_name = status_names[file_key]

		status_dict = status_dicts[file_key]

		status_dict_keys = list(status_dict.keys())

		status_dict_values = list(status_dict.values())

		if file_key in (COPIED, RENAMED):
			log(f"{status_name} files from: ")

			show_r_files(status_dict_keys, tab_level=1)

			log(f"{status_name} files to: ")
		else:
			log(f"{status_name} files: ")

		show_r_files(status_dict_values, tab_level=1)
		
	for i, file_key in enumerate(files_keys):
		status_name = status_names[i]

		log(f"Summary {status_name.lower()} {len(status_dicts[i])} files")

def path_list_to_str_list(x: list[Path]) -> list[str]:
	return list(map(str, x))

def str_list_to_path_list(x: list[str]) -> list[Path]:
	return list(map(Path, x))

def explore(files: list[Path], root=Path(".")) -> list[Path]:
	result = []

	for file in files:
		try:
			file = normalize_dir(file, root)
		except ValueError:
			continue

		parents = list(file.parents)

		if Path(".") in parents:
			parents.remove(Path("."))

		parent_count = len(parents)

		if parent_count >= 1:
			parent = parents[-1]

			if parent not in result:
				result.append(parent)

		elif file not in result:
			result.append(file)

	return result

def is_file_obj(obj: Path) -> bool:
	return True if re.match(r".*\..*$", obj.name) or obj.is_file() else False

def is_dir_obj(obj: Path) -> bool:
	return not is_file_obj(obj)

width = os.get_terminal_size().columns

def show_r_files(source_r_objs: list[Path], tab_level=0, root=Path(".")) -> None:
	source_flat_objs = explore(source_r_objs, root=root)

	for obj in source_flat_objs:
		size = get_size(root / obj)

		formated_size = get_formated_size(size)

		short_formated_size = get_short_formated_size(size)

		msg = "    " * tab_level

		if is_file_obj(obj):
			msg += str(obj)
		else:
			msg += f"Files in \"{obj}\": "

		msg += short_formated_size.rjust(width - len(msg))

		log(msg)

		if is_dir_obj(obj):
			show_r_files(source_r_objs, tab_level + 1, root=root / obj)

def main(argv: list[str]) -> None:
	version_index_path = Path("main_version_index.ver")
	version_index = check_version_index(version_index_path)

	log(f"Current version index: {version_index}")

	create_backup_zip(f"backup_ver{version_index}.zip")

	if (len(argv) <= 1):
		raise ValueError("Required arguments not reached. Required argument is commit summary description.")

	system("chcp 65001")

	git_fetch_origin()

	system("git add .")

	commits_hash = get_commits_hash()

	last_commit_hash = commits_hash[0]

	added_files = 		get_file_list(old_commit_hash=last_commit_hash, filter="A")
	deleted_files = 	get_file_list(old_commit_hash=last_commit_hash, filter="D")
	modified_files = 	get_file_list(old_commit_hash=last_commit_hash, filter="M")
	copied_file_list = 	get_file_list(old_commit_hash=last_commit_hash, filter="C")
	renamed_file_list = get_file_list(old_commit_hash=last_commit_hash, filter="R")

	files = (added_files, deleted_files, modified_files, copied_file_list, renamed_file_list)

	commit_changing_files = list((added_files | deleted_files | modified_files | copied_file_list | renamed_file_list).values())

	added_files = list(added_files)

	added_files_count = 	len(added_files)
	deleted_files_count = 	len(deleted_files)
	modified_file_count = 	len(modified_files)
	renamed_file_count = 	len(renamed_file_list)
	copied_file_count = 	len(copied_file_list)

	show_git_edited_files(*files)

	log(f"\nCalculated:")

	new_files_count =  added_files_count + copied_file_count

	edited_files_count = renamed_file_count + modified_file_count

	if (new_files_count > 0):
		log(f"Summary new {new_files_count} files")
	else:
		log(f"No new files")

	if (edited_files_count > 0):
		log(f"Summary edited {edited_files_count} files")
	else:
		log(f"No edited files")

	if (deleted_files_count > 0):
		log(f"Summary deleted {deleted_files_count} files")
	else:
		log(f"No deleted files")

	local_files = get_local_file_list()

	remote_files = get_remote_file_list(last_commit_hash)

	local_repo_file_count = len(local_files)

	log(f"Summary {local_repo_file_count} files in local repository")

	remote_repo_file_count = len(remote_files)

	log(f"Summary {remote_repo_file_count} files in remote repository")

	files_waiting_to_commit_count = added_files_count + modified_file_count + renamed_file_count + copied_file_count + deleted_files_count
	
	if (files_waiting_to_commit_count == 0):
		log("No changes in local repository. Stopping...")

		imd_exit()

	no_affected_files: list[Path] = list(str_list_to_path_list(sub_array(list(map(str, commit_changing_files)), remote_files)))

	no_affected_files_count = len(no_affected_files)

	log("Files that will not be affected by the commit: ")

	show_r_files(no_affected_files, tab_level=1)

	log(f"Summary {no_affected_files_count} no affected files by commit.")

	local_repo_file_count = len(local_files)
	
	log(f"Summary {files_waiting_to_commit_count} files is waiting to be commited")

	sure = "C"

	try:
		while sure == "C":
			log("""Are you sure commit changes?

C - Not now, go to CLI to edit changes.

Y - Yes, commit changes.

N - No. ( default )""")

			sure = input("Your answer: ").upper().strip()

			if (sure == "N" or not sure): imd_exit()

			elif (sure == "C"):
				CLI()

			elif (sure != "Y"):
				log(f"Unrecognized option \"{sure}\". Stopping...")

				imd_exit()
	except KeyboardInterrupt:
		log("\nInterrupted by keyboard.")

		imd_exit()

	version_index += 1

	log(f"New version index: {version_index}")

	version_index_path.write_text(str(version_index))

	commit_summary_message = f"\"{' '.join(argv[1:])}\" at {get_ISO_8601_time(get_cur_struct_time())}"

	log(commit_summary_message)

	# system(f"git commit --message=\"{commit_summary_message}\"")

	# system("git push origin")

	imd_exit()

def imd_exit() -> None:
	system("git reset")

	sys.exit(1)

if __name__ == "__main__":
	try:
		main(sys.argv)
	except Exception as e:
		traceback.print_exc()

		imd_exit()