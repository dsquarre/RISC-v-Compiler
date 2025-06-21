🔧 Overview

This project implements a custom RISC-V CPU simulation using Quartus and ModelSim, as part of the e-Yantra 2024 competition by IIT Bombay. It includes:

A Verilog-based CPU supporting core RISC-V instructions

A C-based path planning algorithm compiled to RISC-V and tested via simulation



---

🛠️ Tech Stack

Hardware Simulation: Quartus, ModelSim

Languages: Verilog, C

Architecture: RISC-V (RV32I Base ISA)

---

🚀 Features

Implementation of basic RISC-V CPU architecture:

Fetch, Decode, Execute, Memory, Writeback stages

ALU operations, branching, and memory access


Instruction simulation in ModelSim using .v and .do files

Custom C path planner algorithm compiled into RISC-V binary

Memory-mapped input/output for instruction simulation

---

🧪 How to Run

1. Simulate the CPU

Open riscv_cpu.v in Quartus

Load testbench.v for simulation

Use ModelSim to simulate and view waveforms


2. Run Path Planner

Compile path_planner.c to RISC-V binary using riscv32-unknown-elf-gcc

Convert binary to .hex format and load into memory file

Re-run simulation and observe execution

![](img2.jpg)