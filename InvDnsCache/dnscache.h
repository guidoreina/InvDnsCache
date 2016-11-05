#ifndef DNS_CACHE_H
#define DNS_CACHE_H

#ifndef BOOL
  #define BOOL int
#endif

#ifndef UINT8
  #define UINT8 unsigned char
#endif

#ifndef UINT16
  #define UINT16 unsigned short
#endif

#ifndef UINT32
  #define UINT32 unsigned
#endif

BOOL InitDnsCache(unsigned nbuckets, unsigned max);
void FreeDnsCache();

BOOL AddIPv4ToDnsCache(const UINT8* ipv4,
                       const char* hostname,
                       UINT16 hostnamelen);

BOOL AddIPv6ToDnsCache(const UINT8* ipv6,
                       const char* hostname,
                       UINT16 hostnamelen);

const char* GetIPv4FromDnsCache(const UINT8* ipv4, char* hostname);
const char* GetIPv6FromDnsCache(const UINT8* ipv6, char* hostname);

void PrintDnsCache();

#endif /* DNS_CACHE_H */
