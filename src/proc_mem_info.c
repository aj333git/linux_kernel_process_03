#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched/signal.h>
#include <linux/sysinfo.h>
//Memory-management helpers
#include <linux/mm.h>         // for si_meminfo
//Defines struct mm_struct,Required to access task->mm
#include <linux/mm_types.h>   // for task->mm
//Provides get_mm_rss(),Used to calculate resident memory (RSS) of a process
#include <linux/sched/mm.h>   // for get_mm_rss
//module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("YourName");
MODULE_DESCRIPTION("Process & Memory Monitor using /proc");
MODULE_VERSION("1.1");
//create virtual file, that user will read
#define PROC_NAME "proc_mem_info"

/* Function that prints data to /proc file */
//m->kernel managed output buffer
//unused iterator
static int proc_show(struct seq_file *m, void *v)
{
    struct task_struct *task;
    struct sysinfo info;
    unsigned long free_mb, total_mb, used_mb, buffers_mb;

    /* Get memory info */
    si_meminfo(&info);
    free_mb    = (info.freeram * info.mem_unit) >> 20;
    total_mb   = (info.totalram * info.mem_unit) >> 20;
    used_mb    = total_mb - free_mb;
    buffers_mb = (info.bufferram * info.mem_unit) >> 20;
//print memory into proc
    seq_printf(m, "Memory Information\n------------------\n");
    seq_printf(m, "Free RAM  : %lu MB\n", free_mb);
    seq_printf(m, "Total RAM : %lu MB\n", total_mb);
    seq_printf(m, "Used RAM  : %lu MB\n", used_mb);
    seq_printf(m, "Buffers   : %lu MB\n\n", buffers_mb);

    seq_printf(m, "Running User Processes\n----------------------\n");
//iterate over all processes |walk the global process list |kernel macro
    for_each_process(task) {
        /* Skip kernel threads */
        if (!task->mm)
            continue;

        /* Print PID, name, and RSS memory in KB */
        seq_printf(m, "PID: %-6d | Name: %-20s | RSS: %lu KB\n",
                   task->pid,
                   task->comm,
                   get_mm_rss(task->mm) << (PAGE_SHIFT - 10));
    }

    return 0;
}

/* Open function */
static int proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_show, NULL);
}

/* Proc file operations */
static const struct proc_ops proc_fops = {
    .proc_open    = proc_open,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};

/* Module init */
static int __init proc_mem_init(void)
{
    struct proc_dir_entry *entry;

    entry = proc_create(PROC_NAME, 0, NULL, &proc_fops);
    if (!entry) {
        pr_err("proc_mem_info: Failed to create /proc entry\n");
        return -ENOMEM;
    }

    pr_info("proc_mem_info: Module loaded\n");
    return 0;
}

/* Module exit */
static void __exit proc_mem_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
    pr_info("proc_mem_info: Module unloaded\n");
}

module_init(proc_mem_init);
module_exit(proc_mem_exit);

