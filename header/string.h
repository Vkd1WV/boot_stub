/* The <string.h> header contains prototypes for the string handling 
 * functions.
 */

#ifndef _STRING_H
#define _STRING_H

#include "sys/typedefs.h"


//void*  memchr  (const void *_s, int _c, size_t _n)		);
//int    memcmp  (const void *_s1, const void *_s2, size_t _n)	);
//void*  memcpy  (void *_s1, const void *_s2, size_t _n)	);
//void*  memmove (void *_s1, const void *_s2, size_t _n)	);
//void*  memset  (void *_s, int _c, size_t _n)			);
//char*  strcat  (char *_s1, const char *_s2)			);
//char*  strchr  (const char *_s, int _c)			);
int    strncmp (const char *_s1, const char *_s2, size_t _n);
int    strcmp  (const char *_s1, const char *_s2           );
//int    strcoll (const char *_s1, const char *_s2)		);
char*  strcpy  (char *_s1, const char *_s2			);
//size_t strcspn (const char *_s1, const char *_s2)		);
//char*  strerror(int _errnum)				);
size_t strlen  (const char *_s                             );
//char*  strncat (char *_s1, const char *_s2, size_t _n)	);
//char*  strncpy (char *_s1, const char *_s2, size_t _n)	);
//char*  strpbrk (const char *_s1, const char *_s2)		);
//char*  strrchr (const char *_s, int _c)			);
//size_t strspn  (const char *_s1, const char *_s2)		);
char*  strstr  (const char *_s1, const char *_s2           );
//char*  strtok  (char *_s1, const char *_s2)			);
//size_t strxfrm (char *_s1, const char *_s2, size_t _n)	);

//#ifdef _MINIX
///* For backward compatibility. */
//char *index, (const char *_s, int _charwanted)		);
//char *rindex, (const char *_s, int _charwanted)		);
//void bcopy, (const void *_src, void *_dst, size_t _length)	);
//int bcmp, (const void *_s1, const void *_s2, size_t _length));
//void bzero, (void *_dst, size_t _length)			);
//void *memccpy, (char *_dst, const char *_src, int _ucharstop,
//						    size_t _size)	);
///* BSD functions */
//int strcasecmp, (const char *_s1, const char *_s2)		);
//#endif

#endif /* _STRING_H */