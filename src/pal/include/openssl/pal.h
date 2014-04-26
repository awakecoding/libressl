
#ifndef OPENSSL_PAL_H
#define OPENSSL_PAL_H

#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifndef __OpenBSD__

void explicit_bzero(void *p, size_t n);

size_t strlcpy(char *dst, const char *src, size_t dstsize);
size_t strlcat(char *dst, const char *src, size_t dstsize);

void* reallocarray(void *optr, size_t nmemb, size_t size);

void arc4random_buf(void *buf, size_t nbytes);

#ifndef _WIN32
FILE* funopen(const void *cookie,
        int (*readfn)(void *cookie, char *buf, int size),
        int (*writefn)(void *cookie, const char *buf, int size),
        off_t (*seekfn)(void *cookie, off_t offset, int whence),
        int (*closefn)(void *cookie));
#endif

int issetugid(void);

#endif

#endif /* OPENSSL_PAL_H */

