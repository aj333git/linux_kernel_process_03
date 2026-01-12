

I built a Linux kernel module that exposes system-wide memory statistics and per-process Resident Set Size (RSS) via /proc, serving as a minimal kernel-space alternative to user-space tools such as top.

1) Module functionality

Creates a virtual proc file at /proc/proc_mem_info

Reports total, free, used RAM, and buffer memory using si_meminfo()

Iterates over all user-space processes via for_each_process

Displays PID, process name, and RSS calculated using get_mm_rss()

Uses the seq_file interface for safe, scalable, multi-page /proc output

2) Kernel concepts reinforced

Building this module required understanding several core kernel mechanisms:

Memory tracking via mm_struct

Absence of mm structures for kernel threads

Dynamic generation of /proc entries

Use of seq_file to prevent buffer overflows for large outputs

3) Debugging and learning experiences

UEFI Secure Boot lockdown blocking unsigned kernel modules, even for root

Kernel module signing using MOK keys and the sign-file utility

Debugging vermagic mismatches due to incorrect kernel headers

Understanding the importance of path-sensitive Kbuild Makefiles and separating kernel-facing build logic from human-facing project orchestration




