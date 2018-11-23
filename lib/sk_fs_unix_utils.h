#ifndef SK_FS_UNIX_UTILS_H_
#define SK_FS_UNIX_UTILS_H_

#include <stdbool.h>
#include "sk_device_metadata.h"

extern bool isDiskByPath(guestfs_h *g, struct device_metadata *metadata, const char *part, const char *spec); 

#endif /* SK_FS_UNIX_UTILS_H_ */