# BingoCLI

BingoCLI is a command-line Bingo game written in standard C.  
It reads one or more Bingo cards from a CSV file, generates number draws using a deterministic random algorithm (with an optional seed), and plays until a Bingo is detected.

---

## Project Overview

This project demonstrates:

- File I/O and CSV parsing in C
- Deterministic randomness via seeded RNG
- Modular program design
- Error handling and validation
- Command-line compilation and execution with a Makefile

---

## System Requirements

**Environment**

- macOS or Linux (or Windows via WSL)
- Compiler: `gcc` or `clang`

**Compiler Settings**

- C Standard: `-std=c11`
- Required flags: `-Wall -Wextra -Werror`

**Libraries Allowed**
No external libraries or frameworks.

---

## Project Structure

```text
BingoCLI/
├─ src/
│  ├─ main.c        // CLI entry point
│  ├─ csv.c         // Read and validate Bingo cards from CSV
│  ├─ game.c        // Card logic: marking and Bingo detection
│  ├─ draw.c        // RNG and draw sequence generation
├─ include/         // Core structs, constants, shared prototypes
├─ data/
│  ├─ cards_sample_1.csv
├─ tests/
│  ├─ test_csv.c
│  ├─ test_game.c
│  └─ test_draw.c
├─ Makefile
└─ README.md