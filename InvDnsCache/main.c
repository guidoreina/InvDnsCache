#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dnscache.h"

#define MAX_BUCKETS 15
#define MAX_ENTRIES (10 * 1024)

#ifndef WIN32
  #define _snprintf_s(buffer, sizeOfBuffer, count, format, ...) \
          snprintf(buffer, sizeOfBuffer, format, __VA_ARGS__)
#endif /* !WIN32 */

int main()
{
  UINT8 ip[4];
  char hostname[256];
  UINT16 hostnamelen;
  char str[256];
  unsigned i;

  /* Initialize DNS cache. */
  if (!InitDnsCache(MAX_BUCKETS, MAX_ENTRIES)) {
    fprintf(stderr, "Error initializing DNS cache.\n");
    return -1;
  }

  for (i = 0; i < 2 * MAX_ENTRIES; i++) {
    /* Build IP address. */
    ip[0] = (i >> 24) & 0xff;
    ip[1] = (i >> 16) & 0xff;
    ip[2] = (i >> 8) & 0xff;
    ip[3] = i & 0xff;

    /* Compose hostname. */
    hostnamelen = (UINT16) _snprintf_s(hostname,
                                       sizeof(hostname),
                                       _TRUNCATE,
                                       "www.%06u.net",
                                       i);

    /* Add pair (IP-address, hostname). */
    if (!AddIPv4ToDnsCache(ip, hostname, hostnamelen)) {
      fprintf(stderr, "Error inserting pair: (%s, %s).\n", ip, hostname);

      FreeDnsCache();
      return -1;
    }
  }

  for (i = (2 * MAX_ENTRIES) - 1; i >= MAX_ENTRIES; i--) {
    /* Build IP address. */
    ip[0] = (i >> 24) & 0xff;
    ip[1] = (i >> 16) & 0xff;
    ip[2] = (i >> 8) & 0xff;
    ip[3] = i & 0xff;

    /* Compose hostname. */
    hostnamelen = (UINT16) _snprintf_s(hostname,
                                       sizeof(hostname),
                                       _TRUNCATE,
                                       "www.%06u.net",
                                       i);

    /* If the IPv4 cannot be found... */
    if (!GetIPv4FromDnsCache(ip, str)) {
      fprintf(stderr,
              "Cannot get hostname for IP address: %u.%u.%u.%u.\n",
              ip[0],
              ip[1],
              ip[2],
              ip[3]);

      FreeDnsCache();
      return -1;
    }

    /* If the hostnames are different... */
    if (strcmp(hostname, str) != 0) {
      fprintf(stderr, "Got hostname '%s', expected '%s'.\n", str, hostname);

      FreeDnsCache();
      return -1;
    }
  }

  PrintDnsCache();

  FreeDnsCache();

  return 0;
}
