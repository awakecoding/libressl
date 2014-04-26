
#include <openssl/pal.h>

#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifndef __OpenBSD__

void explicit_bzero(void *p, size_t n)
{
	bzero(p, n);
}

size_t strlcpy(char *dst, const char *src, size_t dstsize)
{
	const size_t len = strlen(src);
	
	if (dstsize != 0) {
		memcpy(dst, src, (len > dstsize - 1) ? dstsize - 1 : len);
		dst[dstsize - 1] = 0;
	}

	return len;
}

size_t strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t used, length, copy;

	used = strlen(dst);
	length = strlen(src);

	if ((dstsize > 0) && (used < dstsize - 1)) {
		copy = (length >= dstsize - used) ? dstsize - used - 1 : length;
		memcpy(dst + used, src, copy);
		dst[used + copy] = '\0';
	}

	return used + length;	
}

/* this is taken from src/lib/libc/stdlib/malloc.c */

#define MUL_NO_OVERFLOW (1UL << (sizeof(size_t) * 4))

void* reallocarray(void *optr, size_t nmemb, size_t size)
{
	if ((nmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) && (nmemb > 0) && (SIZE_MAX / nmemb < size)) {
		errno = ENOMEM;
		return NULL;
	}

	return realloc(optr, size * nmemb);
}

void arc4random_buf(void *buf, size_t nbytes)
{
	#warning "FIXME: Do *NOT* forget to port arc4random_buf!"
}

FILE* funopen(const void *cookie,
        int (*readfn)(void *cookie, char *buf, int size),
        int (*writefn)(void *cookie, const char *buf, int size),
        off_t (*seekfn)(void *cookie, off_t offset, int whence),
        int (*closefn)(void *cookie))
{
	#warning "FIXME: Do *NOT* forget to port funopen!"
	return NULL;
}

int issetugid(void)
{
	#warning "FIXME: Do *NOT* forget to port issetugid!"
	return 0;
}

#endif

