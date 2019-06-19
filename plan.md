# Overview

cren should be a general tool for renaming files.
It should use regex to get the files of interest and a regex pattern to determine their new name.

# Features

cren shall have a command line interface

cren should show the expected result without execution and ask for confirmation before actual renaming.


## Examples

Add postfix to files

```
cren test(.*).yaml test$1_fc.yaml
```
