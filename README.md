# Camlann

<!-- vim-markdown-toc GFM -->

* [Introduction](#introduction)
* [How does Camlann Work?](#how-does-camlann-work)
* [How to Use Camlann](#how-to-use-camlann)
	* [Installation](#installation)
	* [Necessary Modifications to your Source Code](#necessary-modifications-to-your-source-code)
	* [Using Camlann](#using-camlann)
* [FAQ](#faq)
	* [My Code Does Not Compile After I Add a New C File](#my-code-does-not-compile-after-i-add-a-new-c-file)
	* [Camlann is Missing a Function from the BSP My Code Uses](#camlann-is-missing-a-function-from-the-bsp-my-code-uses)
	* [How Can I Check If My Code is Compiling Under Camlann?](#how-can-i-check-if-my-code-is-compiling-under-camlann)
	* [Can I Call Camlann APIs or State Variables Directly?](#can-i-call-camlann-apis-or-state-variables-directly)
	* [How Accurate is Camlann?](#how-accurate-is-camlann)
	* [Is Camlann Sensitive to How I My Components in SOPCBuilder/Qsys?](#is-camlann-sensitive-to-how-i-my-components-in-sopcbuilderqsys)
	* [Is Camlann Compatible With Pointer Arithmetic That Interacts With The NIOSII Adress Space?](#is-camlann-compatible-with-pointer-arithmetic-that-interacts-with-the-niosii-adress-space)
	* [When I Attempt to Compile for the NIOSII I Get `underfined reference to main()`](#when-i-attempt-to-compile-for-the-niosii-i-get-underfined-reference-to-main)
	* [Will it Work on macOS?](#will-it-work-on-macos)
	* [Will it Work on Windows?](#will-it-work-on-windows)
	* [Will it Work on ArchLinux/Fedora/Debian/Slackware/etc?](#will-it-work-on-archlinuxfedoradebianslackwareetc)
	* [Why "Camlann"?](#why-camlann)
* [Roadmap](#roadmap)
	* [Near-Term](#near-term)
	* [Long-Term](#long-term)
* [Version History](#version-history)
* [Contributing](#contributing)
* [Disclaimer](#disclaimer)

<!-- vim-markdown-toc -->

# Introduction

Camlann is a compatibility layer that allows the same C codebase to
simultaneously target the [Altera
NIOSII](https://en.wikipedia.org/wiki/Nios_II) architecture as well as Linux on
general-purpose architectures such as AMD64 or IA32. Specifically, Camlann is
made to work with the NIOSII University Program extensions. Camlann is purpose
written for the University of South Carolina CSCE313 course, but may prove
useful to others wishing to target the NIOSII and IA32/AMD64 with the same
code.

Camlann is specially targeted at graphics-related code which interacts with the
NIOSII via the `alt_up_pixel_buffer_dma_draw` function, but may be extended to
other types of code in the future.

# How does Camlann Work?

Camlann provides alternative functions with the same method signatures and
calling conventions as the ones exported by the NIOS2 BSP. Many of these
functions don't really do anything, and simply allow the code to continue
running. Others hook into appropriate Camlann internals to render pixels or
display text in a cross-platform way.

Camlann gets hooks into the "user program" (the program the user has written on
the NIOSII) by acting as the insertion point (`main()`) for the application. At
present, all Camlann code is synchronous and runs in the same thread as the user
code, but this is planned to change in the future.

Camlann interdicts calls to Altera BSP functions via `camlann.h`, which uses
preprocessor macros to conditionally include either the BSP's headers or it's
own.

Camlann is activated by defining the macro `USE_CAMLANN` at compile time via
`-DUSE_CAMLANN`. If this preprocessor macro is not defined at compile time,
then `camlann.h` will cause the normal BSP functions to be used rather than
it's own, allowing the program to compile for and run on the DE2 board as
normal.

# How to Use Camlann

## Installation

Camlann depends on SDL. On Ubuntu 16, this means you need to install
`libsdl1.2-dev`.

Camlann's source files (the `./camlann`) directory need to be placed in the
top-level directory of your NIOS2 project. For example, lets say that my
Quartus project file was in `./lab_00`, and that my C code was
in`./lab_00/software/lab_00_code`. In this example, the `camlann` directory
would be copied to `./lab_00/software/lab_00_code/camlann`. The file
`camlann.mk` needs to be a sibling in the directory hierarchy to the `camlann/`
folder.

Additionally, `camlann.mk` needs to be modified to suit the needs of your
project. Specifically, the `NIOS2_OBJECTS` variable needs to be set to a list
of object files that need to be built for your project.

To automatically install Camlann into the right directory, and set
`NIOS2_OBJECTS` to a best-guess value (which should work for 99% of use cases),
you can use the `install.sh` script provided in the same folder as this
document. To use this script, run it like this: `./install.sh
./lab_00/software/lab_00_code/` using the same example as previously. If your
code is somewhere else, then give `install.sh` the path to the top-level of
your Eclipse software project.

## Necessary Modifications to your Source Code

To use Camlann successfully, you must make the following changes to your source
code:

* Your `main()` function must be renamed to `user_main()`
	* You cannot use the name `main()`, but you may use a different name by
	  modifying the macro `USER_MAIN` in `camlann.h`.
* Anywhere you would include any BSP header file (i.e.
  `altera_avalon_pio_regs.h`, you should instead include `camlann/camlann.h`.
	* If you include any parts of the BSP directly, your project will not
	  compile under Camlann.

## Using Camlann

To use Camlann, (in a terminal) `cd` to the top-level directory of your Eclipse
software project. If you followed the installation steps properly, then you
should have a file in this directory named `camlann.mk`. To compile your
project using Camlann, run `make -f camlann.mk camlann_bin`. To execute the
result of this compilation, run `./camlann_bin`.

You can use `-k` and `-s` to specify the starting values for the keys or
switches. Use `./camlann_bin -h` for more information.

# FAQ

## My Code Does Not Compile After I Add a New C File

The `NIOS2_OBJECTS` variable in `camlann.mk` is probably out of date. Either
update it manually or re-run `install.sh`.

## Camlann is Missing a Function from the BSP My Code Uses

Please report an issue on the Camlann GitHub page.

## How Can I Check If My Code is Compiling Under Camlann?

Use `ifdef USE_CAMLANN`, this is the same preprocessor Camlann itself uses.

## Can I Call Camlann APIs or State Variables Directly?

Technically yes, but you should not do this. The internal Camlann API is
not guaranteed to be stable. Please go through the BSP compatibility functions.

## How Accurate is Camlann?

Not very. Camlann is not cycle-accurate at all with the NIOSII. Many function
calls do nothing and simply return 0 or 1. Many functions are not implemented
at all. Code that works in Camlann is not guaranteed to work on an actual
NIOSII or vice-versa.

## Is Camlann Sensitive to How I My Components in SOPCBuilder/Qsys?

Yes, very.

## Is Camlann Compatible With Pointer Arithmetic That Interacts With The NIOSII Adress Space?

No, not at all. Camlann essentially fudges anything that requires a base
address to do nothing. Only a single video or character buffer are supported at
a time.  PIOs are supported by using `NAME_BASE` as a subscript into a
state-holding array. In short, if your code depends on accessing the NIOSII
address map directly, you are not in for a fun time.

## When I Attempt to Compile for the NIOSII I Get `underfined reference to main()`

You did not add `calmann/` to your NIOSII project. In eclipse, you can right
click the folder and add it to your NIOSII build. In BASH, you can use this
incantation to generate a new `Makefile`:

```
nios2-app-generate-makefile --src-dir ./ --bsp-dir ../the_bsp_dir --elf-name binary.elf  --src-dir ./camlann/
```

This assumes you are `cd` -ed to the top-level directory of your NIOSII
software.

## Will it Work on macOS?

Probably, if you have a working SDL installation and the right headers.  macOS
is not officially supported, but if you get it to work, please open a pull
request or issue with details on what steps you had to take so they can be
added to this document.

## Will it Work on Windows?

Maybe. You need a working `make`, `gcc`, as well as SDL. You might be able to
get it to work using Cygwin or WSL, but I don't use Windows so I cannot test
this.

As with macOS, Windows is not officially supported, but if changes can be made
that do not consume significant development time or break compatibility with
Linux, I will accept pull requests. If you do get it to work on Windows, please
open an issue or pull request so any special steps can be added to this
document.

## Will it Work on ArchLinux/Fedora/Debian/Slackware/etc?

Probably. Only Ubuntu 16.04 is officially supported, but broad compatibility
and portability is a goal. If you have any notes regarding using Camlann with a
Linux distro other than Ubuntu (or with BSD/Solaris), please open a pull
request or an issue so details can be added here.


## Why "Camlann"?

In Arthurian legend, King Arthur perished at the [Battle of
Camlann](https://en.wikipedia.org/wiki/Battle_of_Camlann). This is thus a bit
of a pun on the name of the [Avalon Switch
Fabric](https://en.wikipedia.org/wiki/Nios_II#Avalon_switch_fabric_interface),
as Avalon is the name of the island on which Camelot was said to have stood.

# Roadmap

## Near-Term

* Shape-drawing commands from `altera_up_avalon_video_pixel_buffer_dma.h` are
  not implemented at all. Eventually they will be wrapped with `FIXME` stubs,
and later actually implemented.
* The character buffer/overlay is not implemented at all, messages are sent
  only to standard out. In the future, we will use SDL text drawing to emulate
the character buffer.
* The HEX displays and LEDR/LEDG are only supported in that you can read the
  hexadecimal values sent to their PIOs by running your binary with `-v`.

## Long-Term

* The UI should run in a different thread from the user code. This will allow
the buttons/switches to be operated in "real time".

# Version History

* 0.0.1-ALPHA
	* `alt_types.h` functionality wrapped by `camlann_types.h`
	* Partial implementation of `system.h` via `camlann_system.h`
	* Partial implementation of `altera_up_video_pixel_buffer_dma.h` via
	  `camlann_video_pixel_buffer_dma.h`.
	* Partial implementation of
	  `altera_up_video_character_buffer_with_dma.h` via
	  `camlann_video_character_buffer_with_dma.h`.
	* Partial implementation of `altera_avalon_pio_regs.h` via
	  `camlann_pio_regs.h`.
* 0.0.2-ALPHA
	* Fixed use of SDL's fixed-width integer types, which prevented
	  compiling projects for the DE2.
	* Fixed varies name collisions which prevented compiling projects for
	  the DE2.
	* For better correctness, `calmann_types.h` now uses `stdint.h` to
	  provide fixed-width integer types.
* 0.0.3-ALPHA
	* Re-wrote Camlann rendering code to use SDL2.
		* Camlann now runs at a fixed framerate.

# Contributing

If you have comments, suggestions, or find a problem, please open a GitHub
issue.

If you would like to contribute code, pull requests are welcome - again please
use GitHub.

# Disclaimer

All source code in this repository is copyright 2018 by Charles Daniels, and
is subject to the project license (see `LICENSE.txt`).

This project is not affiliated in any with with the University of South
Carolina (I have developed this code on my own time, not using university
resources).

This project is also not affiliated in any way with Altera Cooperation, or it's
recent buyer Intel.
