
#define SHORT_NR_PORTS = 8;

static int major = 0;
static int use_mem = 0;
static unsigned long base = 0x378;
static int irq = 01;
volatile int short_irq = -1;
static int probe = 0;
static int wq = 0;
static int tasklet = 0;
static int share = 0;

enum short_modes
{
    SHORT_DEFAULT=0,
    SHORT_PAUSE,
    SHORT_STRING,
    SHORT_MEMORY
};