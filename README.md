# GDB with fzf

**Patch file from [https://github.com/filipkilibarda/gdb_fzf_patch](https://github.com/filipkilibarda/gdb_fzf_patch)**

This is a patch for GDB that integrates [FZF fuzzy finder](https://github.com/junegunn/fzf) with GDB's history search.

## Install fzf

follow https://github.com/junegunn/fzf#installation
or just try
```
sudo apt install fzf
```

## Build gdb

```
# Get the source code
git clone https://github.com/veritas501/gdb-with-fzf.git --depth 1

# Enter the build directory 
mkdir gdb-build && cd gdb-build

# Configure the build
# --prefix is the root directory to install resulting files at
# --enable-targets=all gives us support for all architectures
# $(which python) is the python venv that I have pwndbg installed in
../gdb-with-fzf/configure \
    --prefix=$(pwd) \
    --with-python=$(which python) \
    --enable-targets=all

# This should get all the build dependencies
apt build-dep gdb

# build gdb
# gdb binary should appear in bin/ of the build directory
make all-gdb -j`nproc` && make install-gdb
```

## Use it

Press ctrl+r to use it.

![](example.gif)

## More

Customize FZF options with the environment variable GDB_FZF_OPTS.

```
# E.g., change the layout
export GDB_FZF_OPTS='--layout=reverse-list'
```

Set up infinite GDB history. Should be added to ~/.gdbinit.

```
# https://stackoverflow.com/a/3176802/6824752
set history save on
set history size unlimited
set history remove-duplicates unlimited
set history filename ~/.gdb_eternal_history
```