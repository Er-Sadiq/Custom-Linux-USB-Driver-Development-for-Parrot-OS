#include <linux/usb.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/mutex.h>

/* Define USB device table */
static struct usb_device_id id_table[] = {
    { USB_DEVICE(0x054c, 0x02a5) }, // Replace with your Vendor ID and Product ID
    {}
};
MODULE_DEVICE_TABLE(usb, id_table);

/* Define a structure to hold the device's private data */
struct usb_skel_device {
    struct usb_device *udev;
    struct usb_interface *interface;
    struct mutex lock;
};

/* Probe function */
static int skel_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    struct usb_skel_device *dev;
    struct usb_device *udev = interface_to_usbdev(interface);

    pr_info("USB device plugged in\n");

    // Allocate memory for the device's private data
    dev = kzalloc(sizeof(struct usb_skel_device), GFP_KERNEL);
    if (!dev) {
        pr_err("Failed to allocate memory for the device\n");
        return -ENOMEM;
    }

    dev->udev = udev;
    dev->interface = interface;
    mutex_init(&dev->lock);

    // Store private data in interface
    usb_set_intfdata(interface, dev);

    // Get the device descriptor (e.g., vendor and product info)
    pr_info("Device Descriptor: Vendor ID: 0x%04X, Product ID: 0x%04X\n", udev->descriptor.idVendor, udev->descriptor.idProduct);
    pr_info("Device Manufacturer: %s\n", udev->manufacturer);
    pr_info("Device Product: %s\n", udev->product);

    return 0;
}

/* Disconnect function */
static void skel_disconnect(struct usb_interface *interface)
{
    struct usb_skel_device *dev = usb_get_intfdata(interface);

    pr_info("USB device removed\n");

    // Cleanup device data and release memory
    if (dev) {
        mutex_destroy(&dev->lock);
        kfree(dev);
    }
}

/* Define USB driver */
static struct usb_driver skel_driver = {
    .name = "parrot_usb_driver",
    .id_table = id_table,
    .probe = skel_probe,
    .disconnect = skel_disconnect,
};

/* Module init function */
static int __init usb_skel_init(void)
{
    int result;

    result = usb_register(&skel_driver);
    if (result < 0) {
        pr_err("USB registration failed: %d\n", result);
        return result;
    }
    pr_info("USB driver initialized\n");

    return 0;
}

/* Module exit function */
static void __exit usb_exit(void)
{
    usb_deregister(&skel_driver);
    pr_info("USB driver unregistered\n");
}

module_init(usb_skel_init);
module_exit(usb_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sadiq Ahmed Killedar");
MODULE_DESCRIPTION("USB driver for Parrot OS");


