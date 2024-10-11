# C++ Console Program
	
## Overview
This C++ program is a multi-functional console-based application that provides several utilities. The program consists of four key functionalities:
1. Sentence correction: Corrects user-entered sentences by adjusting capitalization and spacing.
2. Prime number generation: Generates prime numbers up to a user-defined limit using the Sieve of Eratosthenes algorithm.
3. Domino chain formation: Checks whether a set of dominoes can be arranged in a valid chain.
4. Text censorship: Reads an Arabic text file, censors specific words, and writes the modified text to a new file.

## Features
1. **Sentence Correction (`correction`)**:  
   The user can input a sentence, and the program will correct it by removing extra spaces and ensuring that it starts with a capital letter and ends with a period.

2. **Prime Number Generation (`SieveOfEratosthenes`)**:  
   The user enters a number `n`, and the program will output all prime numbers less than or equal to `n` using the Sieve of Eratosthenes algorithm.

3. **Domino Chain Formation (`FormsDominoChain`)**:  
   The user inputs a series of dominoes, and the program determines whether they can be arranged in a valid chain. A chain is valid if the right side of one domino matches the left side of the next.

4. **Text Censorship (`censorShip`)**:  
   The program reads an Arabic text file, replaces censored words with alternatives from a "censorFile.txt" file, and outputs the censored text into a new file.



## Getting Started
### Prerequisites
- A C++ compiler (e.g., GCC, Clang, MSVC)
- A basic understanding of C++ and terminal usage
- (Optional) Knowledge of UTF-8 and Arabic text handling

### Files
- **Main Program File**: `main.cpp`
- **Censorship Words File**: `censorFile.txt` (contains censored words and their replacements)

### Instructions
1. **Clone the repository**:
   ``` git clone https://github.com/nadaamiin/Assignment-1.git
cd Assignment-1   ```

2. **Compile the program**:
   ```
   g++ -std=c++11 main.cpp -o program
   ```

3. **Run the program**:
   ```
   ./program
   ```

### Usage
Upon running the program, you will be greeted with a menu where you can select one of the following options:

1. **Correct Your Sentence**:
   - Choose option `a` and input a sentence ending with a period (`.`).
   - The program will correct the sentence for capitalization and spacing.
   
2. **Get Prime Numbers**:
   - Choose option `b` and enter a positive number to generate all prime numbers up to that number.

3. **Dominoes Game**:
   - Choose option `c`, input the number of dominoes (more than 2), and provide the left and right values for each domino.
   - The program will check if these dominoes can form a valid chain.

4. **Message Altering to Avoid Censorship**:
   - Choose option `d`, input the file name of the Arabic text you want to censor.
   - The program will censor the text based on the words defined in `censorFile.txt` and output the modified text to a new file.

5. **Exit**:
   - Choose option `e` to exit the program.

### Example Workflow

1. **Correct Sentence**:
   - User enters: `a`.
   - Input sentence: `"   this   is   an example   sentence   ."`.
   - Output: `"This is an example sentence."`.

2. **Prime Numbers**:
   - User enters: `b`.
   - Input: `30`.
   - Output: `(2, 3, 5, 7, 11, 13, 17, 19, 23, 29)`.

3. **Domino Chain Formation**:
   - User enters: `c`.
   - Number of dominoes: `3`.
   - Input: `1 2`, `2 3`, `3 1`.
   - Output: `"A chain is formed successfully: 1|2 - 2|3 - 3|1"`.

4. **Text Censorship**:
   - User enters: The file name the input file that contains the Arabic text.
   - Input file: `arabic_text.txt`.
   - The program censors the text based on `censorFile.txt` and writes the result to a new file.
   -  output file: The user will create it

### Sample Censorship File (`censorFile.txt`)
```plaintext
bad_word replacement_word
offensive_term acceptable_term
```

## License
This project is open-source and available under the MIT License.

## Author
Created by [Nada Amin]( https://github.com/nadaamiin ).

---
