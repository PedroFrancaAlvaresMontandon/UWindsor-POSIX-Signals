# POSIX Signals and Process Management (COMP.2560)

This repository contains practical implementations of process control and signal handling in C, developed during the System Programming course at the **University of Windsor**.

The projects focus on the life cycle of processes, inter-process communication via signals, and the persistence of system behaviors across different execution contexts.

## 🛠️ Technical Implementation Details

### 1. Process Hierarchy and Orphanage
* **File:** `orphan_process_management.c`
* Demonstrates the creation of orphan processes and how the parent process uses `waitpid()` to monitor specific child exit statuses.

### 2. Signal Persistence across Exec
* **File:** `signal_handler_exec_test.c`
* Investigates how signal handlers behave after an `exec()` call, verifying that custom handlers are reset to default while ignored signals remain ignored.
* **Helper:** `helper_do_nothing.c` (Target program for exec testing).

### 3. Inter-process Alarm Synchronization
* **File:** `interprocess_alarm_clock.c`
* A simulation of an alarm clock where a child process triggers a timed `SIGALRM` to the parent process based on command-line arguments.

### 4. Unified Multi-Signal Handling
* **File:** `unified_multi_signal_handler.c`
* Implementation of a single signal handler function designed to catch and process multiple signals (`SIGINT`, `SIGQUIT`) effectively.

## 💻 Environment & Tools
* **Language:** C (POSIX standard)
* **Compiler:** GCC
* **Operating System:** Linux (developed and tested on University of Windsor CS Servers)
* **Debugger:** GDB (used for tracing process execution and signal delivery)

---
*Developed by Pedro Montandon as part of the Bachelor of Computer Science program.*