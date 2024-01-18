#!/usr/bin/env bash
# runs a clean build

declare -r APP="hsh"
declare -ra CFLAGS=("-Wall" "-Wextra" "-Werror" "-pedantic" "-std=gnu89")
declare -ra SRC=("input.c" "main.c" "parser.c" "utils.c" "strings.c" "strings2.c" "strings3.c" "mem.c" "executor.c" "builtin.c" "builds.c" "env.c" "scanner.c" "cmd.c")

if [ -e "$APP" ]; then
        rm -r "$APP"
fi
gcc -o "$APP" "${CFLAGS[@]}" *.c

