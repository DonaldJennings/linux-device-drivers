#include <linux/ioctl.h>
#include <linux/cdev.h>

#undef PDEBUG             /* undef it, just in case */
#ifdef SCULLC_DEBUG
#  ifdef __KERNEL__
     /* This one if debugging is on, and kernel space */
#    define PDEBUG(fmt, args...) printk( KERN_DEBUG "scullc: " fmt, ## args)
#  else
     /* This one for user space */
#    define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#  endif
#else
#  define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif

#undef PDEBUGG
#define PDEBUGG(fmt, args...)

#define SCULLC_MAJOR 0 // dynamic-allocation by default
#define SCULLC_DEVS  4 // numbers of devices

#define SCULLC_QUANTUM 4000
#define SCULLC_QSET    500


struct scullc_dev
{
    void **data;
    struct scullc_dev *next;
    int vmas;
    int quantum;
    int qset;
    size_t size;
    struct mutex lock;
    struct cdev cdev;
}

extern struct scullc_dev *scullc_devices;
extern struct file_operations sculc_fops;

extern int sculc_major;
extern int scullc_devs;
extern int scullc_order;
extern int sculc_qset;

int scullc_trim;
struct scullc_dev *scullc_follow(struct scullc_dev *dev, int n);

#ifdef SCULC_DEBUG
#     define SCULLC_USE_PROC
#endif

/*
 * Ioctl definitions
 */

/* Use 'K' as magic number */
#define SCULLC_IOC_MAGIC  'K'

#define SCULLC_IOCRESET    _IO(SCULLC_IOC_MAGIC, 0)

/*
 * S means "Set" through a ptr,
 * T means "Tell" directly
 * G means "Get" (to a pointed var)
 * Q means "Query", response is on the return value
 * X means "eXchange": G and S atomically
 * H means "sHift": T and Q atomically
 */
#define SCULLC_IOCSQUANTUM _IOW(SCULLC_IOC_MAGIC,  1, int)
#define SCULLC_IOCTQUANTUM _IO(SCULLC_IOC_MAGIC,   2)
#define SCULLC_IOCGQUANTUM _IOR(SCULLC_IOC_MAGIC,  3, int)
#define SCULLC_IOCQQUANTUM _IO(SCULLC_IOC_MAGIC,   4)
#define SCULLC_IOCXQUANTUM _IOWR(SCULLC_IOC_MAGIC, 5, int)
#define SCULLC_IOCHQUANTUM _IO(SCULLC_IOC_MAGIC,   6)
#define SCULLC_IOCSQSET    _IOW(SCULLC_IOC_MAGIC,  7, int)
#define SCULLC_IOCTQSET    _IO(SCULLC_IOC_MAGIC,   8)
#define SCULLC_IOCGQSET    _IOR(SCULLC_IOC_MAGIC,  9, int)
#define SCULLC_IOCQQSET    _IO(SCULLC_IOC_MAGIC,  10)
#define SCULLC_IOCXQSET    _IOWR(SCULLC_IOC_MAGIC,11, int)
#define SCULLC_IOCHQSET    _IO(SCULLC_IOC_MAGIC,  12)

#define SCULLC_IOC_MAXNR 12