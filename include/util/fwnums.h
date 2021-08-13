/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 18/05/2021
 */

/*
 . Fixed width number types
 .
 . Sort of based on this source: 
 .
 .       https://github.com/jdah/tetris-os/blob/master/src/util.h
*/

#ifndef _FWNUMS_H 
#define _FWNUMS_H 

/* Signed */

typedef char                i8;
typedef short               i16;
typedef int                 i32;

/* Unsigned */

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned            u32;

/* Hardware specific */

#ifdef __x86_64__

typedef long                i64;
typedef unsigned long       u64;

#else

typedef long long           i64;
typedef unsigned long long  u64;

#endif

/* Floating point, duh */

typedef float               f32;
typedef double              f64;

#endif /*_FWNUMS_H */