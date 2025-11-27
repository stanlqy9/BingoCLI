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
```

## 🧩 Module Design Descriptions (High-Level Only)

Before coding begins, each team member will write a short **high-level design** explaining how their assigned module will work.  
These designs will describe **what each module does, how it interacts with the rest of the system, and what assumptions or decisions guide its logic.**  
This section serves as a shared plan before any code or headers are created.

Each section should include:
- **Purpose:** What the module is responsible for.
- **Inputs / Outputs:** What it receives and what it provides to others.
- **Internal Design:** How it will conceptually accomplish its job.
- **Error Handling:** How it will deal with invalid or unexpected data.
- **Integration Notes:** How other parts of the program will use this module.

---

### 🎲 `draw.c` — Draw Generation Module  
**Owner:** Danya  

### 🧠 Purpose: 

The draw module is responsible for generating randomized Bingo numbers between 1 and 75. It ensures that each number is unique within a single game session. It separate the random number generation logic from the rest of the program, making the system much easier to test, maintain and integrate with other components like the game logic and CSV card reader. 

### 📥 Inputs:
- An internal list or array containing all of the possible Bingo numbers (1 to 75).
- The random number generator is already seeded using the current system time.


### 📤 Outputs:
- A single randomized Bingo number each time a draw is requested. 
- The module will stop producing numbers once all 75 have been drawn.

### ⚙️ Internal Design (HIGH Level):

The module begins by creating a list from 1 to 75. Then uses a randomization algorithm to shuffle these numbers into a random order. When it is drawn, the module returns the next value from the shuffled list, ensuring that no number is repeated. 

The module will likely keep an internal index counter that tracks how many numbers have already been drawn. Each time a draw is requested, the next available number is returned, and the count is updated. Once all of the numbers are used, the module signals that no more draws remain. This kind of approach avoids duplicates and keeps the drawing process efficient and predictable . 

### 🚨 Error Handling: 

If a draw is requested after all 75 numbers have been drawn, the module will return a special value IE: 0, or a signal that indicates no more numbers are available for a draw. If the module fails to initialize properly (i.e. memory or  internal setup etc), it will print an error message to standard error. The design assumes normal conditions will rarely cause errors  but it would still include simple checks to make the model predictable and robust. 


### 🔗 Integration Notes: 

The `main.c` file will initialize the draw system once at the start of the game, calling a setup function to seed and shuffle the numbers. During gameplay, `main.c` or `game.c` will repeatedly call a function from this module to get the next number. 

The `game.c` module will use the numbers to mark spaces on the Bingo cards, while the testing module `test_draw.c` can use the same functions to confirm that numbers are correctly randomized and not repetitive. In return this keeps the random number logic contained and easy to verify. 



---

### 🎯 `game.c` — Bingo Logic Module  
**Owner:** Ryan  

#### 🧠 Purpose
Describe the overall goal of this module (e.g., handling game state, marking numbers, checking for Bingo).

#### 📥 Inputs / 📤 Outputs
- What data does this module receive? (e.g., card data, drawn numbers)
- What results does it return? (e.g., Bingo detected, card index)

- Input:
- It recieves bingo card structure from csv.c
- The current number that is drawn from draw.c

- Output:
- A Bingo or Loss
- The card being updated when a number is marked

#### ⚙️ Internal Design (High-Level)
- How will Bingo cards and marked states be represented conceptually?
- How will marking work when a number is drawn?
- How will the module detect Bingo (rows, columns, diagonals)?
- How will it track the overall game status or winning card?
- Bingo Cards will be represented as a 5x5 array of numbers with another 5x5 boolean array that marks whether a number has been drawn.
- When a number is drawn, it will scan all the cards and mark any of them true.
- It will detect a Bingo by:
- Checking the Rows: check to see if 5 are marked(same with the others)
- Checking the Columns
- Checking Diagonally
- It will track the overall game status by recording which card has BINGO and it will tell main.c
- Maybe with variable that says if the game is won or still playing.

#### 🚨 Error Handling
- What assumptions does it make about valid input (e.g., 5x5 card)?
- How will it handle invalid or missing card data?
- How will it behave if no Bingo is found?

Assumptions that are made:
- The cards should be 5x5 grids and be in correct format
- The center of the grid has the "free" mark
Errors that can happen:
- Handling Invalid/missing card data, it will be ignored
- Any duplicate or out of range numbers drawn will be skipped
- If no bingo is found, it will tell us that there is no winner.
#### 🔗 Integration Notes
- When should `main.c` call this module?
- What does this module provide back to the main program or other modules?

- 'main.c' should call this module when 'draw.c' is done drawing a number
-  This module provides an update to the cards and whether we have a winner or not.
- This module, once a winner(BINGO) is found, signals 'main.c' to print an output(winner or no winner)

---

### 📄 `csv.c` — CSV Input Module  
**Owner:** Angel  

#### 🧠 Purpose
Summarize the main purpose of this module (e.g., reading Bingo cards from a CSV file).
Read a bingo from a CSV file and turn them into a design that can be used. There will be one or more 5x5 bingo cards and it will be ensured that they are correctly formatted.


#### 📥 Inputs / 📤 Outputs
- What input does this module process? (e.g., CSV file path)
- What output does it produce? (e.g., list of cards, total number of cards loaded)
- Input:
- it receives a CSV file path from the user
- Every line contains 5 comma separated values that represent the row of a bingo card
- Output: A bingo with the total amount of cards


#### ⚙️ Internal Design (High-Level)
- How will the file be read conceptually (line by line, buffer, etc.)?
- How will the module interpret and convert CSV text into card data?
- How will it identify where one card ends and another begins?
- What validation checks will it perform (e.g., 5 rows per card, 5 values per row)?
- a file will open and line by line it will be read with a text buffer.
- Each line is split by commas and every five lines it will turn into a bingo card.
- if a line is blank then the card is complete.
- Every value gets turned into an integer and “FREE” spaces are marked as special.
- it will check that each row only has 5 inputs and they are all within 1-75. Also that every card has five rows before it stores it.


#### 🚨 Error Handling
- How will it handle missing files, malformed rows, or non-numeric data?
- What will it do when no valid cards are found?
- if the file cant be opened then no cards will be returned.
- any lines with missing our extra values will be invalid
- those cards will be skipped and if no cards are found then the main program will get signaled and error
- if the file cant be opened then no cards will be returned.
- any lines with missing our extra values will be invalid
- those cards will be skipped and if no cards are found then the main program will get signaled and error



#### 🔗 Integration Notes
- How will `main.c` call this module during startup?
- What does the rest of the program need to know about how data is stored or returned?
- the module will get called by the main program to load the bingo cards.
- the cards will be loaded and it will receive both arrays of cards.
- the program knows that every card is a 5x5 grid and it gets ready to mark them

---

## 🧪 Test Suite

The `tests/` directory contains unit tests for each module. Each test file can be compiled and run independently to verify module functionality.

---

### `test_csv.c` — CSV Module Tests

| Test Function | Description |
|---------------|-------------|
| `test_load_valid_file` | Loads cards from `data/cards_sample_1.csv` and verifies count > 0 |
| `test_load_invalid_file` | Verifies -1 is returned for a nonexistent file |
| `test_card_structure` | Checks that card IDs are assigned correctly |
| `test_free_space` | Verifies center cell is -1 (FREE) and pre-marked |
| `test_card_values` | Validates parsed numbers are in range [1, 75] |
| `test_multiple_cards` | Tests loading 2 cards with correct values |

---

### `test_draw.c` — Draw Module Tests

| Test Function | Description |
|---------------|-------------|
| `test_init_draw_sequence` | Verifies draws are available after initialization |
| `test_get_next_draw` | Checks returned number is in valid range [1, 75] |
| `test_unique_draws` | Draws all 75 numbers and verifies no duplicates |
| `test_has_more_draws` | Tests availability checking before/after draws |
| `test_exhausted_draws` | Verifies -1 is returned when all numbers are drawn |
| `test_draw_count` | Tests that draw count increments correctly |

---

### `test_game.c` — Game Module Tests

| Test Function | Description |
|---------------|-------------|
| `test_init_card` | Verifies card ID, FREE space at center, and all other cells unmarked |
| `test_mark_number` | Tests marking a number on multiple matching cells |
| `test_check_bingo_row` | Detects horizontal (row) bingo |
| `test_check_bingo_column` | Detects vertical (column) bingo |
| `test_check_bingo_diagonal` | Detects both main and anti-diagonal bingos |
| `test_check_bingo_no_win` | Ensures no false positives with scattered marks |
| `test_check_all_cards` | Tests finding a winner among multiple cards |
| `test_print_card` | Verifies `print_card` executes without crashing |

---
