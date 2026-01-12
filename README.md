# Linux Kernel Module: Memory and Per-Process RSS via /proc

This repository contains a Linux kernel module that exposes **system-wide memory statistics**
and **per-process Resident Set Size (RSS)** through a custom `/proc` interface.

The module is intended purely for **learning and exploration of Linux kernel internals**,
specifically memory accounting, process iteration, and `/proc` file implementation.

---

## What This Module Does

- Creates a virtual `/proc` entry at:


- Reports system memory information using `si_meminfo()`:
- Total RAM
- Free RAM
- Used RAM
- Buffer memory

- Iterates over all user-space processes using `for_each_process`
- Displays for each process:
- PID
- Process name (`comm`)
- Resident Set Size (RSS) via `get_mm_rss()`
- Uses the `seq_file` interface for safe, scalable, multi-page output

---

## Kernel Concepts Reinforced

This module reinforces several fundamental Linux kernel concepts:

- Memory tracking through `mm_struct`
- Why kernel threads do not have an associated `mm` structure
- Dynamic generation of `/proc` entries (not stored on disk)
- Correct use of the `seq_file` API to avoid buffer overflows
- Safe iteration over the global task list

---

## Repository Structure

├── README.md
├── src/
│ ├── Makefile
│ └── proc_mem_info.c
└── LICENSE


---

## Build and Load

### Build

```bash
cd src
make

Insert Module

sudo insmod proc_mem_info.ko

View Output

cat /proc/proc_mem_info


Kernel Logs

dmesg | tail


Remove Module

sudo rmmod proc_mem_info


Notes

Secure Boot systems may block unsigned kernel modules.

Module signing using MOK keys may be required.

Kernel headers must match the running kernel (uname -r).

Disclaimer

This module is for educational purposes only.
Do not use on production systems.

Author

Amit Joshi
