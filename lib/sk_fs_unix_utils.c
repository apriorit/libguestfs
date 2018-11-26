#include <config.h>
#include <stddef.h>
#include "guestfs.h"
#include "guestfs-internal.h"

#include "sk_fs_unix_utils.h"

static const char *remove0xPrefix(const char *str)
{
    return str + 2;
}

static bool endsWith(const char *str, const char *end)
{
  size_t strLen = strlen(str);
  size_t endLen = strlen(end);

  if (endLen > strLen)
  {
      return false;
  }

  return (strcmp(end, str + (strLen - endLen)) == 0);
}

static char * getVirtioPath(guestfs_h *g, const struct device_metadata *metadata, const char *part)
{
  const struct device_metadata_address *address = &metadata->address;

  debug(g, "getVirtioPath metadata::address: type=%s, domain=%s, bus=%s, slot=%s, function=%s \n", 
            address->type, address->domain, address->bus, address->slot, address->function);


  if (!address->type || !address->domain || 
      !address->bus || !address->slot || !address->function)
  {
    return NULL;
  }

  return safe_asprintf (g, "%s-%s:%s:%s.%s%s%s", 
                        address->type,
                        remove0xPrefix(address->domain),
                        remove0xPrefix(address->bus),
                        remove0xPrefix(address->slot),
                        remove0xPrefix(address->function),
                        (part == NULL ? "" : "-part"),
                        (part == NULL ? "" : part));
}

static char * getIdePath(guestfs_h *g, const struct device_metadata *metadata, const char *part, struct PathBuildData* pathBuildData)
{
  const struct device_metadata_address *address = &metadata->address;

  debug(g, "getIdePath metadata::address: type=%s, domain=%s, bus=%s, slot=%s, function=%s \n", 
            address->type, address->domain, address->bus, address->slot, address->function);

  pathBuildData->ideCount++;

  return safe_asprintf (g, "pci-0000:00:01.1-ata-%d%s%s",
                        pathBuildData->ideCount,
                        (part == NULL ? "" : "-part"),
                        (part == NULL ? "" : part));

}

bool isDiskByPath(guestfs_h *g, const struct device_metadata *metadata, const char *part, 
                  const char *spec, struct PathBuildData* pathBuildData)
{
  const char *targetBus = metadata->target.bus;
  char *path = NULL;
  bool res = false;

  debug(g, "isDiskByPath spec=%s, part=%s", spec, part);
  debug(g, "isDiskByPath metadata::target: dev=%s, bus=%s \n", 
            metadata->target.dev, targetBus);

  if (!targetBus)
  {
    return false;
  }

  if (STREQ(targetBus, DISK_BUS_VIRTIO))
  {
    path = getVirtioPath(g, metadata, part);
  }
  else if (STREQ (targetBus, DISK_BUS_IDE) ||
           STREQ (targetBus, DISK_BUS_SCSI) || 
           STREQ (targetBus, DISK_BUS_SATA ))
  {
    path = getIdePath(g, metadata, part, pathBuildData);
  }
  
  if (!path)
  {
      return false;
  }

  debug(g, "isDiskByPath path=%s", path);

  //compare only tail
  res = endsWith(spec, path);
  free(path);

  return res;
}
