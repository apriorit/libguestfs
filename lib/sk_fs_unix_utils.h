#ifndef SK_FS_UNIX_UTILS_H_
#define SK_FS_UNIX_UTILS_H_

#include "sk_device_metadata.h"

#include <stdbool.h>

bool isDiskByPath(struct device_metadata* metadata, const char* part, const char* spec); 

#endif /* SK_FS_UNIX_UTILS_H_ */