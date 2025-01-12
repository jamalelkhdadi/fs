
```markdown
# File Size Checker (fs)

`fs` is a command-line tool for calculating the size of files and directories. It provides options to check the size of individual files or calculate the total size of a directory, including all its subdirectories and files.

## Features
- Display the size of a file.
- Recursively calculate the size of a directory and all its contents.
- Display version information and help message.

## Installation

1. Clone or download the repository containing the source code.
2. Compile the program using `gcc`:

   ```bash
   gcc -o fs src/fs.c
   ```

3. The executable `fs` will be created and ready to use.

## Usage

### File Size

To calculate the size of a file:

```bash
fs <file_name>
```

Example:

```bash
fs myfile.txt
```

This will display the size of `myfile.txt`.

### Directory Size

To calculate the size of a directory and its contents:

```bash
fs -d <dir_name>  # or fs --dir <dir_name>
```

Example:

```bash
fs -d /path/to/directory
```

This will recursively calculate the size of the specified directory and all its subdirectories.

### Version

To display the version of the program:

```bash
fs -v  # or fs --version
```

Example:

```bash
fs -v
```

This will display the current version of the `fs` program.

### Help

To display the help message:

```bash
fs -h  # or fs --help
```

Example:

```bash
fs -h
```

This will display the usage information for the `fs` program.

## Example Output

For a file:

```bash
$ fs myfile.txt
Total size: 14.50 KB
```

For a directory:

```bash
$ fs -d /path/to/directory
Total size: 1.23 GB
```

## License

This program is released under the MIT License. See the LICENSE file for more information.
```

### Key Points in the README:
- **Installation**: Instructions for compiling the program.
- **Usage**: Detailed explanations of the commands and options.
- **Examples**: Sample commands and output to guide the user.
- **License**: Mention of the program’s licensing, assuming it’s under the MIT License.

