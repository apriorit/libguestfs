#ifndef SK_FS_UNIX_UTILS_H_
#define SK_FS_UNIX_UTILS_H_

#include <stdbool.h>
#include "sk_device_metadata.h"

struct PathBuildData
{
    int virtioCount;
    int ideCount;
};

extern bool isDiskByPath(guestfs_h *g, const struct device_metadata *metadata, const char *part, 
                         const char *spec, struct PathBuildData* mdSpec); 

#endif /* SK_FS_UNIX_UTILS_H_ */