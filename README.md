# My own simple shell :shell:

**Author**: Predescu Sebastian-Ion

## Overview

The goal of this project is to make a practical project with *C language*: 
a shell. Of course, this shell is very minimalist and doesn't have too many 
commands, but is something for learning.

## Setup

Clone the repository and you are good to go:

```bash
git clone
cd myshell
```

## Build and Run :gear:

The main `Makefile` is found in the `src` folder, but because of the other 
`Makefile` found in root folder you can type `make run` anywhere in the project 
and the shell will start.

## Supported commands

Built-ins:

|Command|Description|Exemple|
|:-----:|:---------|:-----:|
|help   |print a minimalist instructions list|help|
|exit   |quit the shell| exit|
|pwd    |print working directory| pwd|
|cd     |print working directory| cd folder|


## LICENSE

This project is [UNLICENSED](LICENSE).
