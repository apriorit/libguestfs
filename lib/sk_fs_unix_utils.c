#include <config.h>
#include <stddef.h>
#include "guestfs.h"
#include "guestfs-internal.h"

#include "sk_fs_unix_utils.h"

const char g_tbIde[] = "ide";
const char g_tbScsi[] = "scsi";
const char g_tbVirtio[] = "virtio";
const char g_tbXen[] = "xen";
const char g_tbUsb[] = "usb";
const char g_tbSata[] = "sata";
const char g_tbSd[] = "sd"; //since 1.1.2.

static const char * remove0xPrefix(const char *str)
{
    return str + 2;
}

static char * getVirtioPath(guestfs_h *g, struct device_metadata* metadata, const char* part)
{
  struct device_metadata_address* address = &metadata->address;
  struct device_metadata_target* target = &metadata->target;

  debug(g, "getVirtioPath metadata::address: type=%s, domain=%s, bus=%s, slot=%s, function=%s \n", 
            address->type, address->domain, address->bus, address->slot, address->function);


  if (!target->bus || !address->type || !address->domain || 
      !address->bus || !address->slot || !address->function)
  {
    return NULL;
  }

  return safe_asprintf (g, "%s-%s-%s:%s:%s.%s%s%s", 
                        target->bus,
                        address->type,
                        remove0xPrefix(address->domain),
                        remove0xPrefix(address->bus),
                        remove0xPrefix(address->slot),
                        remove0xPrefix(address->function),
                        (part == NULL ? "" : "-part"),
                        (part == NULL ? "" : part));
}

bool isDiskByPath(guestfs_h *g, struct device_metadata* metadata, const char* part, const char* spec)
{
  const char *targetBus = metadata->target.bus;
  char *path = NULL;
  size_t pathLen = 0;
  size_t specLen = 0;
  bool res = false;

  debug(g, "isDiskByPath spec=%s, part=%s", spec, part);
  debug(g, "isDiskByPath metadata::target: dev=%s, bus=%s \n", 
            metadata->target.dev, targetBus);

  if (!targetBus)
  {
    return false;
  }

  if (strcmp(targetBus, g_tbVirtio) == 0)
  {
    path = getVirtioPath(g, metadata, part);
  }
  //else if (strcmp(targetBus, g_tbIde))
  
  if (!path)
  {
      return false;
  }

  debug(g, "isDiskByPath path=%s", path);

  //compare only tail
  pathLen = strlen(path);
  specLen = strlen(spec);
  if (pathLen > specLen)
  {
      return false;
  }

  res = (strcmp(path, spec + (specLen - pathLen)) == 0);
  free(path);

  return res;
}