#pragma once

# define I8MIN	(-128)
# define I8MAX	127
# define U8MIN	0U
# define U8MAX	255U

# define I16MIN	(-32767 - 1)
# define I16MAX	32767
# define U16MIN	0U
# define U16MAX	65535U

# define I32MIN	(-2147483647 - 1)
# define I32MAX	2147483647
# define U32MIN	0U
# define U32MAX	4294967295U

# define I64MIN	(-9223372036854775807LL - 1)
# define I64MAX	9223372036854775807LL
# define U64MIN	0ULL
# define U64MAX	18446744073709551615ULL

typedef char				i8;
typedef unsigned char		u8;

typedef short				i16;
typedef unsigned short		u16;

typedef int					i32;
typedef unsigned int		u32;

typedef long long			i64;
typedef unsigned long long	u64;

typedef float				f32;
typedef double				f64;
