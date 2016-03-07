/* The <math.h> header contains prototypes for mathematical functions. */

#ifndef _MATH_H
#define _MATH_H

#include "sys/typedefs.h"

typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

#define HUGE_VAL	(__huge_val())		/* may be infinity */

/* Function Prototypes. */

double __huge_val(void				);
int __IsNan      (double _x			);

int     abs (int _j                  );
div_t   div (int _numer, int _denom  );
int_max labs(long _j                 );
ldiv_t  ldiv(long _numer, long _denom);

double acos   (double _x				);
double asin   (double _x				);
double atan   (double _x				);
double atan2  (double _y, double _x		);
double cos    (double _x				);
double cosh   (double _x				);
double sin    (double _x				);
double sinh   (double _x				);
double tan    (double _x				);
double tanh   (double _x				);

double ceil   (double _x				);

double exp    (double _x				);
double fabs   (double _x				);
double floor  (double _x				);
double fmod   (double _x, double _y		);
double frexp  (double _x, int *_exp		);
double ldexp  (double _x, int _exp			);
double log    (double _x				);
double log10  (double _x				);
double modf   (double _x, double *_iptr		);
double pow    (double _x, double _y		);
double sqrt   (double _x				);


#endif /* _MATH_H */
