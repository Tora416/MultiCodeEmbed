



#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <asm/uaccess.h>    
#include <linux/cdev.h>
#include <asm-generic/errno.h>
#include <linux/init.h>
#include <linux/tty.h> 
#include <linux/kd.h> 
#include <linux/vt_kern.h>
#include <linux/version.h> 


MODULE_LICENSE("GPL");


int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);


#define SUCCESS 0

#define DEVICE_NAME "chardev_leds"  
#define BUF_LEN 80


dev_t start;


struct cdev* chardev=NULL;


static int Device_Open = 0;




static char *leidos_Ptr = NULL;


static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};


struct tty_driver* kbd_driver= NULL;


struct tty_driver* get_kbd_driver_handler(void)
{
    printk(KERN_INFO "modleds: loading\n");
    printk(KERN_INFO "modleds: fgconsole is %x\n", fg_console);
#if ( LINUX_VERSION_CODE > KERNEL_VERSION(2,6,32) )
    return vc_cons[fg_console].d->port.tty->driver;
#else
    return vc_cons[fg_console].d->vc_tty->driver;
#endif
}


static inline int set_leds(struct tty_driver* handler, unsigned int mask)
{
#if ( LINUX_VERSION_CODE > KERNEL_VERSION(2,6,32) )
    return (handler->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,mask);
#else
    return (handler->ops->ioctl) (vc_cons[fg_console].d->vc_tty, NULL, KDSETLED, mask);
#endif
}


int init_module(void)
{
    int major;      
    int minor;      
    int ret;

    
    
    
    if ((ret=alloc_chrdev_region (&start, 0, 1,DEVICE_NAME))) {
        printk(KERN_INFO "Can't allocate chrdev_region()");
        return ret;
    }

    
    if ((chardev=cdev_alloc())==NULL) {
        printk(KERN_INFO "cdev_alloc() failed ");
        unregister_chrdev_region(start, 1);
        return -ENOMEM;
    }

    
    cdev_init(chardev,&fops);

    
    if ((ret=cdev_add(chardev,start,1))) {
        printk(KERN_INFO "cdev_add() failed ");
        kobject_put(&chardev->kobj);
        unregister_chrdev_region(start, 1);
        return ret;
    }

    
    kbd_driver= get_kbd_driver_handler();

    major=MAJOR(start);
    minor=MINOR(start);

    
    printk(KERN_INFO "I was assigned major number %d. To talk to\n", major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    
    
    
    
    
    
    printk(KERN_INFO "'sudo mknod -m 666 /dev/%s c %d %d'.\n", DEVICE_NAME, major,minor);
    printk(KERN_INFO "Try to cat and echo to the device file.\n");
    printk(KERN_INFO "Remove the device file and module when done.\n");

    return SUCCESS;
}


void cleanup_module(void)
{
    
    if (chardev)
        cdev_del(chardev);

    
    set_leds(kbd_driver,0);
    
    unregister_chrdev_region(start, 1);
}


static int device_open(struct inode *inode, struct file *file)
{
    if (Device_Open){
        printk(KERN_ALERT "El dispositivo ya esaba abierto");
        return -EBUSY;
    }

    
    Device_Open++;
    printk(KERN_INFO "Se acaba de abrir el dispositivo\n");

    
    
    try_module_get(THIS_MODULE);

    return SUCCESS;
}


static int device_release(struct inode *inode, struct file *file)
{
    Device_Open--;      

    
    module_put(THIS_MODULE);
    printk(KERN_INFO "El dispositivo se acaba de cerrar\n");

    return 0;
}


static ssize_t device_read(struct file *filp,   
                           char *buffer,    
                           size_t length,   
                           loff_t * offset)
{
    printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
    return -EPERM;
}






static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off){
    int bytes_to_write = len;

    

    printk(KERN_INFO "Longitud: %d\n", len);

    printk(KERN_INFO "Estamos en el write\n");

    
    
    
    leidos_Ptr = (char *) vmalloc(len);

    
    if(copy_from_user(leidos_Ptr, buff, bytes_to_write))
        return -EFAULT;

    
    unsigned int mask = 0;

    
    int encender_numLock = 0;
    int encender_capsLock = 0;
    int encender_scrollLock = 0;

    
    
    int i = 0;
    while (i < len){
        if (*leidos_Ptr == '1'){
            encender_numLock = 2;
        }
        else if (*leidos_Ptr == '2'){
            encender_capsLock = 4;
        }
        else if (*leidos_Ptr == '3'){
            encender_scrollLock = 1;
        }
        else{
            
            
        }
        printk(KERN_INFO "Leido: %c \n", *leidos_Ptr);
        leidos_Ptr++;
        i++;
    }

    
    mask = encender_numLock+encender_capsLock+encender_scrollLock;
    printk(KERN_INFO "Mascara: %d \n", mask);

    
    set_leds(kbd_driver,mask);

    
    return bytes_to_write;
}