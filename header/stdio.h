/*
 * stdio.h - input/output definitions
 *
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: stdio.h,v 1.3 89/12/18 14:00:10 eck Exp $ */

#ifndef _STDIO_H
#define	_STDIO_H

#include "typedef.h"
#include "limits.h"

/*
 * Focus point of all stdio activity.
 */
typedef struct __iobuf {
	int		_count;
	int		_fd;
	int		_flags;
	int		_bufsiz;
	unsigned char	*_buf;
	unsigned char	*_ptr;
} FILE;

extern FILE* __iotab[FOPEN_MAX];
extern FILE	__stdin, __stdout, __stderr;

#define	stdin		(&__stdin)
#define	stdout		(&__stdout)
#define	stderr		(&__stderr)

// FILE.flags?
#define	_IOFBF		0x000
#define	_IOREAD		0x001
#define	_IOWRITE	0x002
#define	_IONBF		0x004
#define	_IOMYBUF	0x008
#define	_IOEOF		0x010
#define	_IOERR		0x020
#define	_IOLBF		0x040
#define	_IOREADING	0x080
#define	_IOWRITING	0x100
#define	_IOAPPEND	0x200

/* The following definitions are also in <unistd.h>. They should not
 * conflict.
 */
#define	SEEK_SET	0
#define	SEEK_CUR	1
#define	SEEK_END	2

#define	TMP_MAX		999

#define	L_tmpnam	(sizeof("/tmp/") + FILENAME_MAX)
//#define __STDIO_VA_LIST__	void *

typedef max_int	fpos_t;

// File Operations
int   fclose (                                          FILE *_stream);
int   fflush (                                          FILE *_stream);
FILE* fopen  (const char *_filename, const char *_mode               );
FILE* freopen(const char *_filename, const char *_mode, FILE *_stream);
int   remove (const char *_filename                                  );
int   rename (const char *_old     , const char *_new                );
FILE* tmpfile(                        void                           );
//char* tmpnam (char *_s                                               );

//void  setbuf (FILE *_stream, char *_buf                         );
//int   setvbuf(FILE *_stream, char *_buf, int _mode, size_t _size);

//FILE* popen (const char *_command, const char *_type);
//int   pclose(FILE *_stream                          );


//File Positioning Functions
int     fgetpos(FILE *_stream, fpos_t *_pos	);
int     fseek  (FILE *_stream, long _offset, int _whence)	);
int     fsetpos(FILE *_stream, fpos_t *_pos	);
int_max ftell  (FILE *_stream			);
void    rewind (FILE *_stream		);

// Error Functions
void clearerr(FILE* _stream );
int  feof    (FILE* _stream );
int  ferror  (FILE* _stream );
void perror  (const char* _s);

#define	feof(p)     (((p)->_flags & _IOEOF) != 0)
#define	ferror(p)   (((p)->_flags & _IOERR) != 0)
#define clearerr(p) ((p)->_flags &= ~(_IOERR|_IOEOF))


//Formatted Output
int fprintf (FILE *_stream, const char *_format, ...       );
int printf  (               const char *_format, ...       );
//int sprintf (char *_s     , const char *_format, ...       );
//int vfprintf(FILE *_stream, const char *_format, char *_arg);
//int vprintf (               const char *_format, char *_arg);
//int vsprintf(char *_s,      const char *_format, char *_arg);

//Formatted Input
//int    fscanf  (FILE *_stream, const char *_format, ...)	);
//int    scanf   (const char *_format, ...	);
//int    sscanf  (const char *_s, const char *_format, ...)	);
//#define vfscanf _doscan
//int    vfscanf (FILE *_stream, const char *_format, char *_arg));
//int    vscanf  (const char *_format, char *_arg);
//int    vsscanf (const char *_s, const char *_format, char *_arg));

//Character IO Operations
int   fgetc  (                FILE *_stream        );
char* fgets  (char *_s      , int _n, FILE *_stream);
int   fputc  (int _c        , FILE *_stream        );
int   fputs  (const char *_s, FILE *_stream        );
int   ungetc (int _c        , FILE *_stream        );

//int   getc   (                FILE *_stream        );
//int   putc   (int _c        , FILE *_stream        );
int   getchar(             void                    );
int   putchar(int _c                               );
int   puts   (const char *_s                       );

#define	getchar()	fgetc(stdin)
#define	putchar(c)	fputc(c,stdout)
#define puts(s)		fputs(s,stdout)

//#define	getc(p)		(--(p)->_count >= 0 ? (int) (*(p)->_ptr++) : \
//				__fillbuf(p))
//#define	putc(c, p)	(--(p)->_count >= 0 ? \
//			 (int) (*(p)->_ptr++ = (c)) : \
//			 __flushbuf((c),(p)))


//Direct IO Functions
size_t fread,
	    (void *_ptr, size_t _size, size_t _nmemb, FILE *_stream)	);
size_t fwrite,
	(const void *_ptr, size_t _size, size_t _nmemb, FILE *_stream)	);


int __fillbuf  (FILE *_stream		);
int __flushbuf  (int _c, FILE *_stream	);


int   fileno(FILE *_stream                    );
FILE* fdopen(int _fildes  , const char *_types);
#define	fileno(stream)		((stream)->_fd)


#endif /* _STDIO_H */
