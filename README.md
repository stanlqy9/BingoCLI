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

#### 🧠 Purpose
Explain the goal of this module (e.g., generating randomized Bingo number draws).

#### 📥 Inputs / 📤 Outputs
- What input(s) does this module need?
- What output(s) will it produce? (e.g., a full shuffled list of draws or one number at a time)

#### ⚙️ Internal Design (High-Level)
- How will the module represent and randomize numbers (1–75)?
- How will it ensure that numbers are not repeated?
- Will the module generate all numbers at once or one per function call?

#### 🚨 Error Handling
- How will it conceptually handle invalid input ?
- What should happen if generation fails?

#### 🔗 Integration Notes
- When and how will `main.c` use this module?
- What will other modules (like `game.c`) expect to receive from it?

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

### 🧾 Instructions for Each Team Member

Each person should:
1. Write **1–3 paragraphs** per subsection above.
2. Keep explanations **in plain English** — no code yet.
3. Focus on describing **behavior, structure, and interaction**, not implementation.
4. Use bullet points or short paragraphs for clarity.
5. Commit your design by editing this README and pushing your section to the repo.

Once all three modules are described, we’ll review as a group and then move forward to:
- Coding the modules based on the agreed design
- Integrating everything in `main.c`
