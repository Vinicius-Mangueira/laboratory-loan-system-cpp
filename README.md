# Laboratory Loan System (C++)

## Overview

This project is a **console-based C++ application** developed for a Practical Assignment of the **Object-Oriented Programming (OOP)** course. The system manages the loan of laboratory equipment, ensuring proper control, validation, and safe state transitions using OOP principles.

The application was designed to strictly follow the rules defined in the assignment statement and to prevent invalid system states.

---

## Features

* Register laboratory equipment
* List all registered equipment with availability status
* Loan equipment to a person
* Return borrowed equipment
* Search equipment by ID
* Console-based interactive menu

---

## Business Rules

* Each equipment has:

  * Unique positive ID
  * Name with at least 3 characters
  * Non-empty category
  * Availability status (available / borrowed)
* Equipment cannot be loaned if it is already borrowed
* Equipment cannot be returned if it is already available
* State changes are performed only through **business methods**, not direct setters
* Loans store:

  * Equipment ID
  * Borrower name
  * Date
  * Active / inactive status

---

## Object-Oriented Design

The system is structured using the following classes:

### `Equipamento`

* Private attributes
* Parameterized constructor with validation
* Getters only (no unsafe setters)
* Business methods:

  * `marcarEmprestado()`
  * `marcarDevolvido()`

### `Emprestimo`

* Stores loan information
* Controls active/inactive loan state
* Method:

  * `encerrar()`

### `SistemaLab`

* Manages collections of equipment and loans
* Implements all system operations
* Handles validations and user interaction

---

## How to Compile and Run

### Using MSYS2 (MINGW64)

```bash
cd /c/Users/your_user/path_to_project/MATRICULA_POO-2025-E001
g++ main.cpp -o sistema
./sistema
```

### Using PowerShell (Windows)

```powershell
g++ main.cpp -o sistema
.\sistema.exe
```

---

## Project Structure

```
MATRICULA_POO-2025-E001/
├── main.cpp
├── README.md
└── LLM_LOG.txt
```

---

## Notes on LLM Usage

The use of a Large Language Model (LLM) was limited to:

* Clarifying OOP concepts
* Debugging compilation and execution issues
* Improving code organization and documentation

All code logic was fully understood and reviewed by the student.

---

## Academic Context

* Course: Object-Oriented Programming (C++)
* Institution: Federal University of Paraíba (UFPB)
* Assignment: Practical Exercise E001
* Submission: Individual work

---

## Author

Vinicius Mangueira – UFPB

---

## License

This project is intended **for academic purposes only**.

---

## Professor

CARLOS EDUARDO COELHO FREIRE BATISTA
