# Library Automation System (C)

This project was developed as an academic course project for the
Structured Programming course at Yıldız Technical University.

The system implements a small-scale library automation using
linked lists and CSV-based file persistence without using any database.

## Features
- Author management (add, delete, update, list) using a singly linked list
- Student management using a doubly linked list
- Book and copy tracking with ISBN-based labeling (ISBN_1, ISBN_2, ...)
- Book–author mapping stored and managed via CSV files
- Borrow and return operations with validation rules
- Penalty point calculation for late returns
- File-based data persistence using CSV files

## Project Structure
- Source code: `src/main.c`
- Report: `docs/project-report.pdf`
- Sample data files: `data/`

## Technologies
- C
- Dynamic memory management (malloc, free)
- File I/O (CSV)

## Notes

- This project was developed for educational purposes as part of a university course.

## How to Run
Compile the program:
```bash
gcc -o library_automation src/main.c

./library_automation

