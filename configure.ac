AC_INIT([libgloss-htif], [0.1])

AC_PROG_CC
AC_CHECK_TOOL([AR], [ar])
AC_CHECK_TOOL([SIZE], [size])

AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [
#ifndef __riscv
#error "A RISC-V compiler is required"
#endif
])], [],
[AC_MSG_FAILURE([The target architecture of the C compiler does not appear to be RISC-V.
If cross-compiling, specify a target triplet such as '--host=riscv64-unknown-elf'.])])

AC_MSG_CHECKING([whether multilib is enabled])
AC_ARG_ENABLE([multilib],
[AS_HELP_STRING([--enable-multilib],
    [build libraries for multiple march/mabi combinations @<:@--disable-multilib@:>@])],
    [AS_CASE(["$enableval"],
        [yes], [multilib="rv32i/ilp32 rv32iac/ilp32 rv32im/ilp32 rv32imac/ilp32 rv32imafc/ilp32f rv64imac/lp64 rv64imafdc/lp64d"],
        [no], [multilib=""],
        [for multilib in $enableval ; do
            AS_CASE(["$multilib"], [rv32?*/?*|rv64?*/?*], [], [
                AC_MSG_RESULT([unknown])
                AC_MSG_ERROR([illegal march-mabi value: ${multilib}])])
            done
            multilib="$enableval"])],
    [multilib="`$CC -print-multi-lib | sed '/.*;@march=\(.*\)@mabi=\(.*\).*/{s//\1\/\2/;H;};$!d;x;s/\n/ /g'`"])

AS_IF([test "x$multilib" != x],
    [AC_MSG_RESULT([yes])],
    [AC_MSG_RESULT([no])])

AC_SUBST([MULTILIB], ["$multilib"])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
