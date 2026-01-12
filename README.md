# Linux Kernel Module: Memory and Per-Process RSS via /proc

This repository contains a Linux kernel module that exposes **system-wide memory statistics**
and **per-process Resident Set Size (RSS)** through a custom `/proc` interface.

The module is intended purely for **learning and exploration of Linux kernel internals**,
specifically memory accounting, process iteration, and `/proc` file implementation.

---

## What This Module Does

- Creates a virtual `/proc` entry at:


