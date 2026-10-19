<br />
<div align="center">
  <a href="https://github.com/MjnMixael/Etak">
    <img src="Etak/icon.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Etak</h3>

  <p align="center">
    A translation tool for FreespaceOpen!
  </p>
</div>

## About

Etak is a tool meant to facilitate creating a full tstrings.tbl for games in the [FreespaceOpen engine](https://github.com/scp-fs2open/fs2open.github.com). It recursively scans a directory for valid files and uses regex to find translatable strings and string IDs. It will then replace the ID with a valid one and save the string and ID to the generated tstrings.tbl file.

Etak uses [QT Designer](https://www.qt.io/product/ui-design-tools) for it's UI development.

## Features

- Recursively scan a directory for translatable strings using configurable regex
- Generate unique, valid string IDs and write a proper `tstrings.tbl`
- Fill in missing IDs in sequence, or apply a custom ID offset
- Read-only mode: report string/ID pairs without modifying source files
- Ignore specific files or string IDs
- Output sorting with optional header and verbose annotations
- Optional case-insensitive string comparison
- Cross-platform (Windows/Linux)

## Building

Etak builds with CMake and Qt 6.8.3 (Core, Gui, Widgets). It builds on Windows (MSVC) and Linux (GCC/Clang); the GitHub Actions workflow builds and packages both.

### Requirements

- CMake 3.21+
- Qt 6.8.3
- A C++17 compiler — MSVC (Visual Studio 2026) on Windows, GCC or Clang on Linux

### Visual Studio 2026

Generate the solution against your Qt install, then open it:

```bash
cmake -S . -B build/vs2026 -G "Visual Studio 18 2026" -A x64 -DCMAKE_PREFIX_PATH=C:/Qt6/6.8.3/msvc2022_64
```

Open `build\vs2026\Etak.slnx` and build/run with F5 (Etak is the default startup project). Alternatively, use **File → Open → Folder** on the repo root — VS reads `CMakePresets.json` directly.

### Command line (Linux or Windows)

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/path/to/Qt/6.8.3/gcc_64
cmake --build build
```

## Usage

<img src="Preview.png">

Etak will scan the provided directory for parsable files. It will then search each file with each provided Regex to try to find possible matches for translatable strings. If a match is found it will decipher the ID and check that it is both unique and not invalid*. If necessary it will provide a new unique string ID. Then the string and the ID will be saved to the output file in a proper [tstrings.tbl format](https://wiki.hard-light.net/index.php/Tstrings.tbl) for the FreepsaceOpen Engine.

Below is an explenation of the home settings:

* Directory Path: The root path to the game files you want to run Etak on.
* Regex List: The [Regular Expressions](https://en.wikipedia.org/wiki/Regular_expression) to be used when searching for translatable strings and IDs. Each expression also needs to specify which of the patterns in the expression are the string and the ID. This is done with index values from left to right starting with 1.
* File Formats List: In order to speed up the process, Etak will only parse files with extensions listed here. All other files will be ignored.
* ID Offset: By default Etak will generate new string IDs at 0, but you can provide an optional offset here instead.
* Replace Existing: By default Etak will not replace strings that have an existing valid ID. Check this button if you would like to change that behavior.
* Read Only Mode: In this mode, Etak will scan for String/ID pairs and print them all to the output file without generating new IDs and modifying the source files. The output file will include comments that note invalid IDs if they are detected.

Below is an explenation of the preferences settings:

* Comprehensive Scan: This setting will force a complete scan of the game files before any action is taken. Etak will then generate new string IDs ensuring no conflicts. After that it will begin modifying files. This process can take twice as long as a normal scan. Note that if Replace Existing is set then this setting will be ignored.
* Fill In Missing IDs: This setting will force the scan to attempt to fill in any missing IDs in the sequence between 0 and maximum ID before creating IDs beyond the current maximum. Any ID Offset will be ignored if this is option is turned on.  Note that if Replace Existing is set then this setting will be ignored.
* Output File Sorting: You can set your preferred soring method for the output file.
* Output File Header Annotations: If set then Etak will print a commented out line before each pair that will list the first file the pair was found in. If sorting by filename, it will only do this once per group.
* Verbose Output File Annotations: If set then Etak will print a commented out line for every pair that lists all files the pair was found in.
* Use Case-Insensitive String Comparisons: By default Etak is case sensitive. If this is set then all string comparisons for pair strings will be case insensitive.

Below is an explenation of the Ignore Files settings:

* Any file listed in this dialog will not be scanned even if it matches a valid file extension. The file listed here must contain the full path to the file and not just the filename.

Below is an explenation of the Ignore Ids settings:

* Any ID listed in this dialog will not be allowed in any case and will be considered invalid. This is useful if you have some types of string/id pairs that cannot be effectively searched with Regex and must be done manually.

When your settings are correct, click Begin and Etak will begin processing your game files. The output will list any terminal errors, otherwise it will display the file it is currently parsing. A full output log can be found in %appdata%/Etak/Etak.log if needed.

You may Terminate the process at any time by clicking on Terminate, but the action cannot be undone! Any files that have been processed may have already been altered. It is a good idea to use this in conjunction with a versioning system like GIT or SVN which can then be used to verify Etak's output.

*Invalid IDs are IDs where two strings share an ID but the strings are not identical

## Known Issues

- None currently!

## Dependencies

Etak is built purely on Qt 6 and has no additional third-party libraries.

# Credits

Etak is developed by Mike Nelson.
Licensed under the GNU GPL v3. See [LICENSE](LICENSE.md).
