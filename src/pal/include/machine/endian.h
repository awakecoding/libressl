
#ifdef __OpenBSD__
#include <machine/endian.h>
#else
#include <endian.h>
#define _BYTE_ORDER __BYTE_ORDER
#define _BIG_ENDIAN __BIG_ENDIAN
#define _LITTLE_ENDIAN __LITTLE_ENDIAN
#endif

