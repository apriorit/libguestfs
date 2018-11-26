#ifndef SK_FS_UNIX_UTILS_H_
#define SK_FS_UNIX_UTILS_H_

#include <stdbool.h>
#include "sk_device_metadata.h"

struct path_build_data
{
    int virtioCount;
    int ideCount;
};

extern bool isDiskByPath(guestfs_h *g, const struct device_metadata *metadata, const char *part, 
                         const char *spec, struct path_build_data* pathBuildData); 

extern bool isDiskById(guestfs_h *g, const struct device_metadata *metadata, const char *part, 
                         const char *spec, struct path_build_data* pathBuildData); 

extern char *createDiskName(guestfs_h *g, size_t diskIndex, const char *part);

#endif /* SK_FS_UNIX_UTILS_H_ */