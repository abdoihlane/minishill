#!/bin/bash

MINISHELL=./minishell
BASH=/bin/bash

# Colors
GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

# Test cases (dir chi bghiti tzed)
TESTS=(
  "echo hello"
  "ls"
  "pwd"
  "cd .. && pwd"
  "export TEST_VAR=42 && echo \$TEST_VAR"
  "unset TEST_VAR && echo \$TEST_VAR"
  "echo \$?"
  "cat < Makefile"
  "echo hello > out.txt && cat out.txt"
  "echo one >> out.txt && cat out.txt"
  "cat << EOF\nhello\nEOF"
  "exit 42"
)

# Run test
# Run test
run_test() {
    CMD="$1"
    TMP_OUT_MINI=$(mktemp)
    TMP_ERR_MINI=$(mktemp)
    TMP_OUT_BASH=$(mktemp)
    TMP_ERR_BASH=$(mktemp)

    # Run minishell
    echo -e "$CMD" | $MINISHELL >$TMP_OUT_MINI 2>$TMP_ERR_MINI
    EXIT_MINI=$?

    # Run bash
    echo -e "$CMD" | $BASH >$TMP_OUT_BASH 2>$TMP_ERR_BASH
    EXIT_BASH=$?

    # Remove prompt lines from minishell output
    # Assume prompt starts with ➜ or "minishell", adjust as needed
    sed -i '/^➜/d' $TMP_OUT_MINI
    sed -i '/^➜/d' $TMP_ERR_MINI
    sed -i '/^minishell/d' $TMP_OUT_MINI
    sed -i '/^minishell/d' $TMP_ERR_MINI

    DIFF_OUT=$(diff $TMP_OUT_MINI $TMP_OUT_BASH)
    DIFF_ERR=$(diff $TMP_ERR_MINI $TMP_ERR_BASH)

    if [[ "$DIFF_OUT" == "" && "$DIFF_ERR" == "" && "$EXIT_MINI" == "$EXIT_BASH" ]]; then
        echo -e "${GREEN}[OK]${NC} $CMD"
    else
        echo -e "${RED}[KO]${NC} $CMD"
        echo "  Expected exit: $EXIT_BASH, Got: $EXIT_MINI"
        echo "  --- Output diff ---"
        diff -u $TMP_OUT_BASH $TMP_OUT_MINI
        echo "  --- Error diff ---"
        diff -u $TMP_ERR_BASH $TMP_ERR_MINI
    fi

    rm -f $TMP_OUT_MINI $TMP_OUT_BASH $TMP_ERR_MINI $TMP_ERR_BASH
}


# Run all
echo "🚀 Starting minishell tests..."
for TEST in "${TESTS[@]}"; do
    run_test "$TEST"
done

