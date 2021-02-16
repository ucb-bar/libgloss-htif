# libgloss-htif

This is a minimalistic libgloss port for RISC-V M-mode that implements
system calls through the Berkeley Host-Target Interface (HTIF).

## Installation

    $ mkdir build
    $ cd build
    $ ../configure --prefix=${RISCV}/riscv64-unknown-elf --host=riscv64-unknown-elf
    $ make
    $ make install

**Note**: The installation prefix must be chosen such that the `libdir`
variable matches one of the library search paths of the RISC-V compiler.
For a typical cross-compiler toolchain, the prefix would generally be
the sysroot directory (`riscv64-unknown-elf-gcc -print-sysroot`).
Use the `--libdir` configure option to adjust the location if the final
directory component is not `/lib`.

Test static linking with a suite of "Hello World" demonstration programs:

    $ make check
    $ spike hello.riscv
    $ spike hello.nano.riscv
    $ spike hello.pico.riscv

### multilib

The `--enable-multilib` or `--disable-multilib` configure options
control whether both RV32 and RV64 libraries are built.
A list of ISA/ABI combinations can be passed as an argument to override
the default set:

    --enable-multilib='rv32i/ilp32 rv32iac/ilp32 rv32im/ilp32 rv32imac/ilp32 rv32imafc/ilp32f rv64imac/lp64 rv64imafdc/lp64d'

If these options are omitted, `configure` dynamically detects the set of
multilib mappings supported by the compiler (`$CC`).

## Usage

For convenience, the compiler/linker switches needed to replace the
standard `-lgloss` are encapsulated in GCC spec files, along with a
[bare-metal linker script](util/htif.ld).

Spec File | Description
--- | ---
[`htif.specs`](util/htif.specs) | Link with newlib
[`htif_nano.specs`](util/htif_nano.specs) | Link with newlib-nano
[`htif_wrap.specs`](util/htif_wrap.specs) | Switch to minimal stdio implementation
[`htif_argv.specs`](util/htif_argv.specs) | Retrieve `argv` from fesvr

    $ riscv64-unknown-elf-gcc -O2 -specs=htif.specs -o hello tests/hello.c

`htif_wrap.specs` further reduces static code size by inserting custom
implementations of common `stdio.h` functions, which support only a
constrained subset of format specifiers (e.g., non-floating-point).
This depends on the `--wrap` feature of GNU ld and is intended to be
used in conjuction with the other newlib spec files.

    $ riscv64-unknown-elf-gcc -O2 -specs=htif_nano.specs -specs=htif_wrap.specs -o hello tests/hello.c

`htif_argv.specs` adds extra initialization code to retrieve
command-line arguments from the frontend server.  The program will exit
with an error (typically `ENOMEM`) if the number or length of the
argument strings exceeds the fixed buffer size set by `ARG_MAX`.
If this feature is omitted, `argv` defaults to a static array with no
arguments.

    $ riscv64-unknown-elf-gcc -O2 -specs=htif_nano.specs -specs=htif_argv.specs -o hello tests/hello.c

### Local usage

For simple testing, it is possible to directly link against
`libgloss_htif.a` in the build directory without installing:

* Add `-L <builddir>` to the link command.
* Pass the actual path to the spec file in `-specs` argument.
* Symlink [`htif.ld`](util/htif.ld) to the current working directory.
  (This bypasses a limitation where gcc searches only the default
  library path for the linker script, ignoring `-L`.)

## Stack and heap sizes

Override the `__stack_size_min` symbol to change the minimum stack
size in bytes:\
`-Wl,--defsym=__stack_size_min=$N`.

Override the `__heap_size` symbol to change the heap size in bytes:\
`-Wl,--defsym=__heap_size=$N`.

## Multi-threading

Static TLS is supported through the Local Executable access model, which
allows the declaration of thread-local variables with the `__thread`
specifier.

By default, hart 0 is designated as the primary hart for handling global
initialization and executing the `main()` function.
A different hart ID can be specified by redefining the `__boot_hart`
symbol, such as with a linker option: `-Wl,--defsym=__boot_hart=$N`.

All other harts execute the secondary `__main()` function, which
defaults to a busy loop.
Multi-threaded programs should either override this function or alias
`__main` with `main` to force a common entry point:
`-Wl,--defsym=__main=main`.

## Exception handling

A custom exception handler can be implemented by overriding the
`handle_trap()` function, which should match the following signature:

```C
uintptr_t handle_trap(uintptr_t epc, uintptr_t cause, uintptr_t tval, uintptr_t regs[32])
```

The return value sets the new `mepc` for returning from the exception.
