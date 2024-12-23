# Monte Carlo π Estimation

This project implements a multi-threaded Monte Carlo simulation to estimate the value of π (Pi). It leverages **POSIX threads** (`pthread`) to parallelize the computation of points within a unit circle, improving performance and accuracy for larger datasets.

---

## Overview

The program:
- Uses the Monte Carlo method to estimate the value of π.
- Simulates random points within a square of side length 2 centered at the origin.
- Calculates the ratio of points falling inside a unit circle to the total number of points generated.
- Implements two threads to divide the computation for improved efficiency.

---

## Key Features

- **Multi-threaded Design**: Utilizes two threads to distribute the computation evenly.
- **Monte Carlo Method**: Approximates π using randomly generated points.
- **Error Handling**: Validates user input for correctness and handles invalid arguments gracefully.
- **Precision Control**: The more points specified, the more accurate the π estimation.

---

## Compilation and Execution

### Prerequisites
- GCC Compiler
- POSIX Thread Library (`pthread`)
- Math Library (`-lm`)

### Compilation
```bash
gcc mcarlo.c -o mcarlo -lpthread -lm
```

### Execution
```bash
./mcarlo <number_of_points>
```

- `<number_of_points>`: The total number of random points to be generated.

---

## How It Works

1. **Input Validation**:
   - Ensures the number of points is a valid positive integer.
   - Adjusts odd inputs to the nearest even number for even workload distribution.

2. **Point Generation**:
   - Generates random `(x, y)` coordinates in the range [-1, 1].
   - Checks if each point lies within the unit circle using the equation:  
     \[
     \sqrt{x^2 + y^2} < 1
     \]

3. **Parallel Computation**:
   - Divides the total number of points evenly between two threads.
   - Each thread calculates the number of points inside the circle.

4. **π Estimation**:
   - Combines results from both threads.
   - Estimates π using the formula:  
     \[
     \pi \approx 4 \times \frac{\text{total points inside circle}}{\text{total points generated}}
     \]

---

## Input Parameters

- `<number_of_points>`:  
  Specifies the total number of random points to generate for the simulation. Larger values improve the accuracy of the π estimation.

Example:
```bash
./mcarlo 1000000
```
- Generates 1,000,000 random points.

---

## Output Example

Sample Execution:
```bash
$ ./mcarlo 1000000
the estimation of pi is: 3.141592
```

- **Output**: Displays the calculated value of π based on the given number of points.

---

## Project Design

### Core Components

1. **Random Point Generator**:
   - Generates random double-precision numbers in the range [-1.0, 1.0).

2. **Threads**:
   - **Thread 1**: Handles the first half of points.
   - **Thread 2**: Handles the second half of points.

3. **Synchronization**:
   - Each thread updates a shared `total_hit_count` variable to record points inside the circle.

4. **Final Calculation**:
   - Combines thread results to estimate π using the Monte Carlo formula.

### Limitations
- The program does not support more than two threads.
- Shared variable `total_hit_count` is not protected by a mutex, so adding synchronization for thread safety is recommended for further scaling.

---

This project demonstrates the power of Monte Carlo methods and parallel computing for approximating mathematical constants like π. It's a great starting point for exploring multi-threading and numerical simulations in C.
