/* The <stdlib.h> header defines certain common macros, types, and functions.*/

#ifndef _STDLIB_H
#define _STDLIB_H

#include "sys/typedefs.h"

// Type Conversions
double              atof  (const char *_nptr);
int                 atoi  (const char *_nptr);
long                atol  (const char *_nptr);
//size_t            mbstowcs(wchar_t *_pwcs   , const char *_s      , size_t _n);
//int                mbtowc (wchar_t *_pwc    , const char *_s      , size_t _n);
//double            strtod  (const char *_nptr, char **_endptr                 );
//long              strtol  (const char *_nptr, char **_endptr      , int _base);
//size_t            wcstombs(char *_s         , const wchar_t* _pwcs, size_t _n);
//int                wctomb (char *_s         , wchar_t _wchar                 );
//unsigned long int strtoul (const char *_nptr, char **_endptr      , int _base);

// Memory Management
void* alloc  (size_t _size              );
void* alloci (size_t _size              );
void  dealloc(void*  _ptr               );
void* realloc(void*  _ptr , size_t _size);

// System Calls
void  abort (void               );
int   atexit(void (*_func)(void));
void  exit  (int _status        );
char* getenv(const char *_name  );
int   system(const char *_string);
int   rand  (void               );

int mblen(const char *_s, size_t _n);

void *bsearch(const void *_key, const void *_base, 
	size_t _nmemb, size_t _size, 
	int (*compar) (const void *, const void *));
void qsort(void *_base, size_t _nmemb, size_t _size,
	int (*compar) (const void *, const void *));

int putenv(const char *_name);
int getopt(int _argc, char **_argv, char *_opts);
extern char *optarg;
extern int optind, opterr, optopt;

#endif /* STDLIB_H */
