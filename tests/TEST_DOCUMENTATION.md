# PIPEX Test Suite Documentation

## Overview
Comprehensive test suite for pipex project with 30+ test cases covering:
- Basic piping (2 commands)
- Command arguments and options
- Complex shell commands (awk, sed, grep, etc.)
- File handling
- Error cases

## Test Files Created

### 1. `tests/test_pipex.sh` - Integration Tests
Bash script that tests pipex against reference shell output.

**Test Categories:**

#### Tests de Base (4 tests)
- `cat | wc -l` - Line counting
- `cat | grep a` - Pattern matching
- `cat | sort` - Sorting
- `sort | uniq` - Duplicate removal

#### Tests avec AWK (4 tests)
- `cat | awk '{print NF}'` - Field counting
- `cat | awk '{print $2}'` - Column extraction
- `cat | awk 'NR>1 {print $0}'` - Skip header
- `cat | awk 'BEGIN {sum=0} {sum+=$1} END {print sum}'` - Sum computation

#### Tests avec GREP (4 tests)
- `cat | grep -E 'e$'` - Extended regex
- `cat | grep -v apple` - Inverse match
- `cat | grep -i APPLE` - Case insensitive
- `cat | grep -c '='` - Count matches

#### Tests avec SED (3 tests)
- `cat | sed 's/a/A/g'` - Substitution
- `cat | sed '/^#/d'` - Delete pattern
- `cat | sed 's/^/LINE: /'` - Prepend

#### Tests avec SORT/UNIQ (3 tests)
- `cat | sort -n` - Numeric sort
- `cat | sort | uniq -c` - Count unique
- `cat | sort -r` - Reverse sort

#### Tests avec HEAD/TAIL (3 tests)
- `cat | head -n 3` - First N lines
- `cat | tail -n 2` - Last N lines
- `head -n 3 | tail -n 1` - Range extraction

#### Tests avec WC (3 tests)
- `cat | wc -c` - Character count
- `cat | wc -w` - Word count
- `cat | wc -l` - Line count

#### Tests avec CUT (2 tests)
- `cat | cut -d',' -f2` - CSV column extraction
- `cat | cut -c 1-5` - Character range

#### Tests avec TR (2 tests)
- `cat | tr 'a' 'A'` - Character translation
- `cat | tr -d '\\n'` - Delete characters

#### Tests Complexes (3 tests)
- `grep | awk` - Filter then extract
- `grep | cut | sort` - Multi-stage pipeline
- `awk | sort | uniq` - Process and deduplicate

**Total: 30+ integration tests**

### 2. `tests/test_lexing.c` - Unit Tests
C program testing lexing, quote removal, and path resolution.

#### Tokenization Tests (12 tests)
Tests `ft_split_almost_like_shell()`:
- Simple command with args: `ls -la` → `['ls', '-la']`
- Piped commands: `cat file.txt | grep test` → `['cat', 'file.txt', '|', 'grep', 'test']`
- Quoted arguments: `echo "hello world"` → `['echo', 'hello world']`
- AWK with braces: `awk '{print $1}'` → `['awk', '{print $1}']`
- SED with regex: `sed 's/a/b/g' input.txt` → `['sed', 's/a/b/g', 'input.txt']`
- CUT with delimiter: `cut -d',' -f2 data.csv` → `['cut', '-d,', '-f2', 'data.csv']`
- GREP with regex: `grep -E '^[a-z]+$' file` → `['grep', '-E', '^[a-z]+$', 'file']`
- Multiple pipes: `sort | uniq | wc -l` → `['sort', '|', 'uniq', '|', 'wc', '-l']`
- TR command: `tr 'a' 'A'` → `['tr', 'a', 'A']`
- HEAD/TAIL combo: `head -n 10 | tail -n 5` → `['head', '-n', '10', '|', 'tail', '-n', '5']`
- AWK with condition: `awk 'NR>1 {print $2}'` → `['awk', 'NR>1 {print $2}']`
- SED with wildcard: `sed -i 's/old/new/g' *` → `['sed', '-i', 's/old/new/g', '*']`

#### Quote Removal Tests (7 tests)
Tests `ft_remove_quote()`:
- Single quotes: `'hello'` → `hello`
- Double quotes: `"world"` → `world`
- Mixed quotes: `'hello' "world"` → `hello world`
- Quoted with spaces: `echo "a b c"` → `echo a b c`
- GREP pattern: `grep 'pattern'` → `grep pattern`
- AWK code: `awk '{print $1}'` → `awk {print $1}`
- SED pattern: `sed 's/a/b/'` → `sed s/a/b/`

#### Path Resolution Tests (15+ commands)
Tests `ft_extract_path()`:
- Common commands: ls, cat, grep, awk, sed, cut, sort, uniq, wc, tr, head, tail
- Absolute paths: `/usr/bin/python3`, `/bin/sh`
- Non-existent: `nonexistent_cmd_xyz` → NOT FOUND

**Total: 34 unit tests**

## Test Input Files

### `/tmp/test_input.txt`
```
apple
banana
cherry
date
elderberry
```

### `/tmp/test_numbers.txt`
```
3
1
4
1
5
9
2
6
```

### `/tmp/test_csv.txt`
```
id,name,age,city
1,Alice,30,Paris
2,Bob,25,London
3,Charlie,35,Berlin
4,Diana,28,Madrid
```

### `/tmp/test_config.txt`
```
# Configuration file
user=john
password=secret123
host=localhost
port=8080
```

### `/tmp/test_special.txt`
Special characters for edge case testing

### `/tmp/test_large.txt`
1000 lines (1-1000) for performance testing

## Running Tests

### Run Lexing/Parsing Tests
```bash
cd /Users/hishembekka/Documents/GitHub/pipex_42
gcc -Wall -Wextra -I./includes tests/test_lexing.c \
  lexing_parsing.c/first.c lexing_parsing.c/eyes_utils.c \
  lexing_parsing.c/token_utils.c lexing_parsing.c/cmds/cmds.c \
  lexing_parsing.c/path.c utils/utils.c -o tests/test_lexing
./tests/test_lexing
```

### Run Integration Tests (once pipex is implemented)
```bash
chmod +x tests/test_pipex.sh
./tests/test_pipex.sh
```

## Expected Results

### Lexing Tests
✅ All tokenization tests should match expected token counts
✅ Quote removal should strip outer quotes but preserve content
✅ PATH resolution should find all standard commands

### Integration Tests (when pipex is ready)
- Success rate: 100% (all 30+ tests pass)
- Output comparison: `diff` with shell reference
- File I/O: correct input/output file handling
- Error codes: proper exit codes for missing commands

## Next Steps to Implement

1. **Implement `ft_exec_pipeline`** 
   - Create pipes (on-demand to avoid FD exhaustion)
   - Fork child processes
   - Dup2 file descriptors
   - Execute commands with execve

2. **File I/O**
   - Open infile (O_RDONLY)
   - Open outfile (O_CREAT|O_TRUNC|O_WRONLY)
   - Proper error handling

3. **Error Handling**
   - Exit code 127 for command not found
   - Exit code 126 for permission denied
   - Proper cleanup and resource management

## Test Coverage Summary

| Category | Tests | Coverage |
|----------|-------|----------|
| Basic Piping | 4 | 2 commands |
| AWK | 4 | Various awk patterns |
| GREP | 4 | Multiple grep options |
| SED | 3 | Substitution, deletion, prepend |
| SORT/UNIQ | 3 | Numeric, counting, reverse |
| HEAD/TAIL | 3 | First N, Last N, ranges |
| WC | 3 | Lines, words, characters |
| CUT | 2 | CSV and character ranges |
| TR | 2 | Translation and deletion |
| Complex | 3 | Multi-stage pipelines |
| **Lexing Unit** | 12 | Tokenization |
| **Quote Removal** | 7 | Quote handling |
| **Path Resolution** | 15+ | Command location |
| **TOTAL** | **64+** | Comprehensive |

