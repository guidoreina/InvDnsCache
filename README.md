InvDnsCache
===========

InvDnsCache is an inverted DNS cache for IPv4/IPv6. The cache is implemented as two hash tables, one for IPv4 addresses and one for IPv6 and works under Linux and Windows.


To initialize the inverted DNS cache:
```
BOOL InitDnsCache(unsigned nbuckets, unsigned max);
```

where:
* `nbuckets`: number of slots of the hash table. This value should be a prime number to get a uniform distribution of the IP addresses.
* `max`: maximum number of IP addresses in the hash table.


To free the inverted DNS cache:
```
BOOL FreeDnsCache();
```


To add an IPv4 address to the cache:
```
BOOL AddIPv4ToDnsCache(const UINT8* ipv4, const char* hostname, UINT16 hostnamelen);
```


To add an IPv6 address to the cache:
```
BOOL AddIPv6ToDnsCache(const UINT8* ipv4, const char* hostname, UINT16 hostnamelen);
```


To get the hostname of an IPv4 address:
```
const char* GetIPv4FromDnsCache(const UINT8* ipv4, char* hostname);
```


To get the hostname of an IPv6 address:
```
const char* GetIPv6FromDnsCache(const UINT8* ipv4, char* hostname);
```


The function `PrintDnsCache()` can be used for debugging purposes.
