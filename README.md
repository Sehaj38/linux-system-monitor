# Linux System Monitor (C++)

A terminal-based **Linux system monitor** written in **pure C++**, using **ncurses** for UI and the Linux **/proc filesystem** for data.

This project is built to understand how real system monitors (like `top` and `htop`) work internally.

Linux-only by design.

---

## Features

### Tier 1 — Core Health Indicators
- Overall CPU Utilization
- Memory Usage (Used / Available)
- Swap Usage
- Load Average (1, 5, 15 minutes)
- Process Count (Running / Total)

### Tier 2 — Bottleneck Diagnostics
- IO Wait Percentage (CPU stalled on disk)
- Disk Read / Write Throughput (KB/s)
- Context Switch Rate (/second)
- Interrupt Rate (/second)

> Tier 2 focuses on **why** the system feels slow, not just how busy it is.

---

## Architecture Overview

- All metrics are read directly from the Linux **`/proc` filesystem**
- Each metric is isolated into its own module
- Tier-2 metrics are **delta-based** (calculated per second)
- UI is built with **ncurses windows**, no screen flicker
- No STL-heavy abstractions, no external dependencies

This mirrors how real system monitoring tools are structured.

---

## Project Structure
```
src/
├── ui/
│ └── main.cpp # ncurses UI + main loop
│
├── core/ # Tier 1 metrics
│ ├── cpu.cpp / cpu.h
│ ├── mem.cpp / mem.h
│ ├── swap.cpp / swap.h
│ ├── load.cpp / load.h
│ └── process.cpp / process.h
│
├── tier2/ # Bottleneck diagnostics
│ ├── iowait.cpp / iowait.h
│ ├── disk.cpp / disk.h
│ ├── context.cpp / context.h
│ └── interrupt.cpp / interrupt.h
```
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/fb624f9f-6abd-4e3b-b2a2-1ab107ef5834" />

