#ifndef SK_DEVICE_METADATA_H_
#define SK_DEVICE_METADATA_H_

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
    char check[10 + 1];
};

#endif /* SK_DEVICE_METADATA_H_ */