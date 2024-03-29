# cren
Program for renaming files

# Description
cren takes a regex pattern for filenames and a regex pattern for new filenames and renames the files

# Build

cren has the folling dependencies that need to be installed before building
  - boost

```
git clone --recursive git@github.com:ashwinmr/cren.git
cd cren
mkdir build
cd build
cmake ..
make
```

# Install
```
sudo make install
```

# Usage

```
cren <"old_filename_pattern"> <"new_filename_pattern"> [ -d <path/to/directory> ]
```
The following flags are supported:
- -i - ignore case
- -y - Don't ask for confirmation

## Examples
Example 1: Basic rename
```
cren "old.txt" "new.txt"
```

Example 2: Rename keeping extension
```
cren "old(.*)" "new\$1"
```
The `\` is needed to escape the `$` sign.
# Running tests
```
cd build
ctest -V
```
