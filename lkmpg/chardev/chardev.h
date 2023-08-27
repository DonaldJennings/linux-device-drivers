#include <linux/atomic.h> 
#include <linux/cdev.h> 
#include <linux/delay.h> 
#include <linux/device.h> 
#include <linux/fs.h> 
#include <linux/init.h> 
#include <linux/kernel.h> /* for sprintf() */ 
#include <linux/module.h> 
#include <linux/printk.h> 
#include <linux/types.h> 
#include <linux/uaccess.h> /* for get_user and put_user */ 
 
#include <asm/errno.h> 
 
#include <linux/atomic.h>
#include <linux/cdev.h>
#include <linux/delay.h>

static int device_open(struct inode *, struct file *filp);
static int device_release(struct inode *, struct file *filp);
static ssize_t device_read(struct file *, char __user *buf, size_t len, loff_t *offset);
static ssize_t device_write(struct file *, const char __user *buf, size_t len, loff_t *offset);

#define SUCCESS 0
#define DEVICE_NAME "chardev"
#define BUF_LEN 80

enum { 
    CDEV_NOT_USED = 0, 
    CDEV_EXCLUSIVE_OPEN = 1, 
}; 

static int major;