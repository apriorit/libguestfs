#ifndef SK_DEVICE_METADATA_H_
#define SK_DEVICE_METADATA_H_

#define DISK_BUS_IDE "ide"
#define DISK_BUS_SCSI "scsi"
#define DISK_BUS_VIRTIO "virtio"
#define DISK_BUS_XEN "xen"
#define DISK_BUS_USB "usb"
#define DISK_BUS_SATA "sata"
#define DISK_BUS_SD "sd" //since 1.1.2.

struct device_metadata_address
{
    const char *type; //'pci' 
    const char *domain; //'0x0000' 
    const char *bus; //'0x00' 
    const char *slot; //'0x07'
    const char *function;//='0x0'/>
};

struct device_metadata_target
{
    const char *dev; //'vda' 
    const char *bus; //'virtio'
};

struct device_metadata
{
    struct device_metadata_address address;
    struct device_metadata_target target; 
};

#endif /* SK_DEVICE_METADATA_H_ */