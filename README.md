# libtc

`libtc` implements a portion of `libc` functionality and more. It provides a
portable, well defined, useful, and consistent interface with unit tests.

## Description

Several different features which make this library useful.

### Provides Consistency Across Platforms

Different C libraries return different values for `malloc(0)`. `tc_malloc(0)`
will always exhibit the same behaviour regardless of the underlying C library.

### Adds New APIs

`getopt()` is nice, but `getopt_long()` is nicer. However `getopt_long()` isn't
available everywhere. Additionally, it doesn't provide a consistent and simple
way to process `--help`/`-h` and `--version`/`-V`.

The args feature of `libtc` provides command line argument processing
and it can provide functions to show help and version information with examples.

```
        struct tc_prog_arg *arg;

        static struct tc_prog_arg args[] = {
                TC_PROG_ARG_HELP,
                TC_PROG_ARG_VERSION,
                TC_PROG_ARG_END
        };

        static struct tc_prog_example examples[] = {
                { .command = "true", .description = "exit successfully" },
                TC_PROG_EXAMPLE_END
        };

        static struct tc_prog prog = {
                .program = "true",
                .usage = "[OPTIONS]",
                .description = "exits with a success return code",
                .version = TC_VERSION_STRING,
                .copyright = TC_VERSION_COPYRIGHT,
                .license = TC_VERSION_LICENSE,
                .author =  TC_VERSION_AUTHOR,
                .args = args,
                .examples = examples
        };

        while ((arg = tc_args_process(&prog, argc, argv)) != TC_NULL) {
                switch (arg->arg) {
                        case 'h':
                                tc_args_show_help(&prog);
                                break;
                        case 'V':
                                tc_args_show_version(&prog);
                                break;
                }

        }

        argc -= argi;
        argv += argi;
```

Output of `true -h`:
```
true -- exits with a success return code

usage: true [OPTIONS]

  -h, --help	print help text
  -V, --version	print version and copyright info

examples:

  # exit successfully
  true
```

Output of `true -V`
```
true v2022 (Build 0)
Copyright (C) 2022  Thomas Cort
License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Written by Thomas Cort
```

### Improves Existing APIs

It's common to set a pointer variable to `NULL` after the memory it points
to is freed to help prevent and detect use after free bugs:

```
free(obj);
obj = NULL;
```

The `tc_free(void *)` function returns `NULL` to make this pattern a bit more
convenient.

```
obj = tc_free(obj);
```

### Depends on a Small Subset of libc

Only a few handfuls of system calls are used by `libtc` and they're all
confined to one source file in `libtc`. Any `POSIX.1`/`C89` compliant system
should be able to handle `libtc`.

### Easy to Reuse

Unlike `gnulib`, `libtc` doesn't require a complex system of `m4` macros to
configure it. Use the shared library or just copy and paste the desired
code and associated license.

### Easy to Use

`libtc` Provides a `pkg-config` file which makes building software with it
simple and painless as many build systems support `pkg-config`.

### Well Tested

A test suite is provided with `libtc` to help ensure it is working properly
on your platform.

### Well Documented

The `libtc` source has copious comments.

## Requirements

* C compiler and standard build tools (make, sh, ...).
* [cmake](https://cmake.org/)

## Installation

Installing in your home directory:

```
cd bin
cmake ..
make
sudo make install
```

## Versioning and Releases

`libtc` releases once a year on July 1st. The version number corresponds
to the year the software collection was released. For example, on July 1,
2038, `tcutils` `v2038` will be released.

## Conformance

None of this software has been designed to conform to any standard. Any
resemblance to standards compliant software is purely coincidental.

## Contributing

The author is not open to external contributions at this time.
Feel free to report bugs or suggest new features.

## License

SPDX: `GPL-3.0-or-later`

See the file `COPYING` for the full license. Each file in the repository should
include its own license information.

<!--
  README.md
  Copyright 2022, 2023, 2024  Thomas Cort

  Copying and distribution of this file, with or without modification, are
  permitted in any medium without royalty, provided the copyright notice and
  this notice are preserved. This file is offered as-is, without any warranty.
-->
