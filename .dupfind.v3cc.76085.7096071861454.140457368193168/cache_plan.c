// V comptime_definitions:
// V compile time defines by -d or -define flags:
//     All custom defines      : gcboehm,gcboehm_full,gcboehm_opt,skip_fastc,skip_arm64,skip_wasm,skip_ssa,skip_eval,glibc,v3_c_extern_declarations
//     Turned ON custom defines: gcboehm,gcboehm_full,gcboehm_opt,skip_fastc,skip_arm64,skip_wasm,skip_ssa,skip_eval,glibc,v3_c_extern_declarations
#define CUSTOM_DEFINE_gcboehm
#define CUSTOM_DEFINE_gcboehm_full
#define CUSTOM_DEFINE_gcboehm_opt
#define CUSTOM_DEFINE_skip_fastc
#define CUSTOM_DEFINE_skip_arm64
#define CUSTOM_DEFINE_skip_wasm
#define CUSTOM_DEFINE_skip_ssa
#define CUSTOM_DEFINE_skip_eval
#define CUSTOM_DEFINE_glibc
#define CUSTOM_DEFINE_v3_c_extern_declarations

#ifndef V_THREAD_STACK_SIZE
#define V_THREAD_STACK_SIZE 8388608
#endif
#if defined(_WIN32)
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#endif
#if defined(_WIN32) && !defined(WIN32_FULL) && !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <stdint.h>
#include <stddef.h>
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint8_t byte;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;



#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ <= 201710L)
#ifndef __bool_true_false_are_defined
#ifdef _MSC_VER
typedef unsigned char bool;
#else
typedef _Bool bool;
#endif
#define __bool_true_false_are_defined 1
#endif
#endif
typedef void* voidptr;
typedef i64 int_literal;
typedef double float_literal;
#if defined(_MSC_VER)
#define V_INT128_STRUCT_ATTR __declspec(align(16))
#else
#define V_INT128_STRUCT_ATTR __attribute__((aligned(16)))
#endif

#if defined(__SIZEOF_INT128__) && !defined(V_INT128_PORTABLE)

typedef unsigned __int128 u128;
typedef __int128 i128;

#define V_INT128_NATIVE 1

/* Generated code builds a wide literal from its halves, so this has to exist on
 * both representations. On the native type the halves are a shift and an or. */


/* A shift count, clamped to the one value the shift helpers have to recognise as
 * out of range. Reading only the low 64 bits let a count of 2^64 look like zero. */


/* The native type is two's complement, so every bit pattern is a value and the
 * conversions below are plain casts. */
































































/* min_i128 / -1 overflows a signed division in C and raises SIGFPE on x86, so
 * that one case is computed as a negation; every other pair divides directly.
 * The portable path answers the same way through its long division. */












/* Negating the minimum value has no representable result, so the negation is
 * computed in unsigned arithmetic and only then reinterpreted. That wraps to
 * the minimum again, the same answer the portable path gives. */






























#else

typedef struct v_int128_s {
	u64 lo;
	u64 hi;
} V_INT128_STRUCT_ATTR v_int128_t;

/* The portable representation is the same C struct for both signednesses: the
 * bits are two's complement either way, and V keeps signedness in its own type
 * table, so there is nothing for C to distinguish. */
typedef v_int128_t u128;
typedef v_int128_t i128;



/* A shift count, clamped to the one value the shift helpers have to recognise as
 * out of range. Anything above the low 64 bits is at least 2^64, which is over
 * the 128 a shift can use. */






/* A negative i64 sign-extends, because the struct holds a two's complement
 * pattern and the value keeps its sign when it widens. */


















/* 2^64 as a double, the weight of the high limb. */
#define V_INT128_TWO64 18446744073709551616.0







/* The magnitude of a signed value as an unsigned one. */






/* The low 64 bits come from the 32-bit limb products; the high 64 bits add the
 * cross products, which is everything a 128-bit result keeps. */




























/* Binary long division, one quotient bit per pass. */






/* A value wider than a double has to be rounded once, from the whole magnitude.
 * Converting each limb on its own rounds twice, and the first rounding throws away
 * the bit that decides the second: with hi = 2^53 + 1 and lo = 2^63, the high limb
 * rounds down to 2^117 and the answer lands 2^65 too low.
 *
 * Keep the top 53 bits and round on the guard bit below them plus every bit after
 * it, the way a hardware conversion does. The scale below is a power of two, which
 * multiplies exactly, so this decides the only rounding there is. */














/* Two's complement multiplication keeps its low 128 bits whatever the signs
 * are, so the unsigned product is the signed result. */




























/* The remainder takes the sign of the dividend, which is what C and V both
 * specify. */


#endif

/* Decimal text for the assert and panic printers.
 *
 * This comes after the main helper block, so it can call the arithmetic helpers
 * whatever representation the build picked. The buffer is static and the text is
 * written back-to-front, which keeps a failing path free of allocation. */


/* Signed decimal. The magnitude comes from the unsigned negation, which is also
 * the only way to print the minimum value. */


struct sync__Channel;
typedef struct sync__Channel* chan;
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ <= 201710L
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif
#endif
#if defined(__TINYC__) || defined(_MSC_VER)
#define E_STRUCT_DECL unsigned char _dummy_pad
#define E_STRUCT 0
#else
#define E_STRUCT_DECL
#define E_STRUCT
#endif
#define _S(s) ((string){.str=(u8*)("" s), .len=(sizeof(s)-1), .is_lit=1})
#define _SL(id, s, n) static const string id = {s, n, 1}
#if !defined(VNORETURN)
#if defined(__TINYC__)
#define VNORETURN __attribute__((noreturn))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define VNORETURN _Noreturn
#elif defined(__GNUC__) && __GNUC__ >= 2
#define VNORETURN __attribute__((noreturn))
#endif
#ifndef VNORETURN
#define VNORETURN
#endif
#endif
#if defined(_MSC_VER) && !defined(__clang__)
#define __attribute__(x)
#ifndef _Thread_local
#define _Thread_local __declspec(thread)
#endif
#define _Atomic volatile
#define __alignof__(x) __alignof(x)
#endif
typedef ptrdiff_t isize;
typedef size_t usize;
typedef char* charptr;
typedef unsigned char* byteptr;
typedef int (*qsort_callback_func)(const void*, const void*);
#ifndef VCALLCONV
#define VCALLCONV(x)
#endif
#if defined(__linux__) && !defined(__ANDROID__)
#include <features.h>
#endif
#ifdef sprintf
#undef sprintf
#endif
#ifdef snprintf
#undef snprintf
#endif
#ifdef vsnprintf
#undef vsnprintf
#endif
#ifdef memcpy
#undef memcpy
#endif
#ifdef memmove
#undef memmove
#endif
#ifdef memset
#undef memset
#endif
// GCC-compatible compilers also define __GNUC__, so keep V's discriminator
// in sync with the compiler that will consume a portable generated C file.
#if defined(__GNUC__) && !defined(__TINYC__) && !defined(__cplusplus) && !defined(__clang__)
	#define __V_GCC__
#endif
// c_headers
typedef int (*qsort_callback_func)(const void*, const void*);
#if defined(_MSC_VER) && !defined(__clang__)
	#define V_CRT_LINKAGE __declspec(dllimport)
	#define V_CRT_CALL VCALLCONV(cdecl)
#else
	#define V_CRT_LINKAGE
	#define V_CRT_CALL
#endif
#if (defined(__MINGW32__) || defined(__MINGW64__)) && defined(__V_GCC__)
	#define V_CRT_STDIO_LINKAGE __attribute__((dllimport))
#else
	#define V_CRT_STDIO_LINKAGE V_CRT_LINKAGE
#endif
#if (defined(_MSC_VER) && !defined(__clang__)) || defined(__cplusplus)
// Under C++ (g++/clang++), let libc declare FILE/stdio/string/stdlib to keep
// noexcept specifiers consistent — the manual extern "C" prototypes below
// would otherwise conflict with system headers under -std=c++NN.
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef va_copy
	#define va_copy(dest, src) ((dest) = (src))
#endif
#ifndef _TRUNCATE
	#define _TRUNCATE ((size_t)-1)
#endif
#elif defined(__NetBSD__)
// NetBSD exposes stdin/stdout/stderr as macros into a single `__sF[3]`
// array whose element size (sizeof(FILE)) depends on the platform and libc
// version, so we cannot forward-declare them. The FreeBSD-style
// `__stdinp/__stdoutp/__stderrp` symbols also do not exist on NetBSD (see
// vlang/v#27190). Defer to the system headers for FILE, the stdio streams,
// and the libc prototypes that would otherwise clash with the
// `__restrict`-qualified declarations in NetBSD libc.
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#elif defined(__TINYC__) && (defined(__FreeBSD__) || defined(__OpenBSD__))
// TinyCC reports a hard redefinition error if system OpenSSL pulls in
// <stdarg.h> after V has provided its own va_start macro. Include it first,
// but keep V manual FILE declarations on these BSD libc variants.
#include <stdarg.h>
#if defined(__FreeBSD__)
typedef struct __sFILE FILE;
extern FILE* __stdinp;
extern FILE* __stdoutp;
extern FILE* __stderrp;
#define stdin __stdinp
#define stdout __stdoutp
#define stderr __stderrp
#else
typedef struct __sFILE FILE;
#ifndef _STDFILES_DECLARED
	#define _STDFILES_DECLARED
struct __sFstub { long _stub; };
extern struct __sFstub __stdin[];
extern struct __sFstub __stdout[];
extern struct __sFstub __stderr[];
#endif
#define stdin ((struct __sFILE *)__stdin)
#define stdout ((struct __sFILE *)__stdout)
#define stderr ((struct __sFILE *)__stderr)
#endif
#elif (defined(__MINGW32__) || defined(__MINGW64__)) && defined(__V_GCC__)
// mingw-w64 stdio.h provides fprintf/vfprintf as static inline overrides
// when __USE_MINGW_ANSI_STDIO is enabled, so use the system declarations
// instead of the manual formatted-stdio prototypes below.
#include <stdarg.h>
#include <stdio.h>
#elif defined(__MINGW32__) || defined(__MINGW64__) || (defined(__clang__) && (defined(_WIN32) || defined(_WIN64)))
typedef struct _iobuf FILE;
FILE* __cdecl __acrt_iob_func(unsigned index);
#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))
#elif defined(__TINYC__) && (defined(_WIN32) || defined(_WIN64))
#ifndef _FILE_DEFINED
struct _iobuf {
	char *_ptr;
	int _cnt;
	char *_base;
	int _flag;
	int _file;
	int _charbuf;
	int _bufsiz;
	char *_tmpfname;
};
typedef struct _iobuf FILE;
#define _FILE_DEFINED
#endif
	#if defined(_WIN64)
FILE* __cdecl __iob_func(void);
	#else
		#ifdef _MSVCRT_
extern FILE _iob[];
			#define __iob_func() (_iob)
		#else
extern FILE (*_imp___iob)[];
			#define __iob_func() (*_imp___iob)
			#define _iob __iob_func()
		#endif
	#endif
#define stdin (&__iob_func()[0])
#define stdout (&__iob_func()[1])
#define stderr (&__iob_func()[2])
#elif defined(__vinix__)
typedef struct __file FILE;
extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;
struct __thread_data;
struct __threadattr;
// pthread_t handling for vinix builds:
//  - Vinix kernel (freestanding, __STDC_HOSTED__=0): no libc, define
//    pthread_t ourselves so V code that references it compiles.
//  - util-vinix cross-compiled on a libc-providing host (hosted, e.g.
//    glibc on Linux or macOS with -D__vinix__): pull pthread_t from
//    libc to avoid colliding with the libc typedef.
#if defined(__STDC_HOSTED__) && __STDC_HOSTED__ && defined(__has_include) && __has_include(<pthread.h>)
#include <pthread.h>
#else
typedef struct __thread_data *pthread_t;
#endif
typedef __builtin_va_list va_list;
#ifndef va_start
	#define va_start(ap, v) __builtin_va_start(ap, v)
#endif
#ifndef va_arg
	#define va_arg(ap, t) __builtin_va_arg(ap, t)
#endif
#ifndef va_end
	#define va_end(ap) __builtin_va_end(ap)
#endif
#ifndef va_copy
	#define va_copy(dest, src) __builtin_va_copy(dest, src)
#endif
#else
	#if defined(__APPLE__) || defined(__FreeBSD__)
typedef struct __sFILE FILE;
extern FILE* __stdinp;
extern FILE* __stdoutp;
extern FILE* __stderrp;
#define stdin __stdinp
#define stdout __stdoutp
#define stderr __stderrp
	#elif defined(__DragonFly__)
typedef struct __sFILE FILE;
extern FILE* __stdinp;
extern FILE* __stdoutp;
extern FILE* __stderrp;
#define stdin __stdinp
#define stdout __stdoutp
#define stderr __stderrp
	#elif defined(__OpenBSD__)
typedef struct __sFILE FILE;
#ifndef _STDFILES_DECLARED
	#define _STDFILES_DECLARED
struct __sFstub { long _stub; };
extern struct __sFstub __stdin[];
extern struct __sFstub __stdout[];
extern struct __sFstub __stderr[];
#endif
#define stdin ((struct __sFILE *)__stdin)
#define stdout ((struct __sFILE *)__stdout)
#define stderr ((struct __sFILE *)__stderr)
	#elif defined(__BIONIC__)
struct __sFILE;
typedef struct __sFILE FILE;
extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;
	#elif defined(__linux__) && !defined(__GLIBC__) && !defined(__GNU_LIBRARY__) && !defined(__BIONIC__) && !defined(__UCLIBC__)
typedef struct _IO_FILE FILE;
// musl exposes the stdio streams as `FILE *const`, so match that to stay
// compatible with later <stdio.h> includes from headers like miniz.h.
extern FILE* const stdin;
extern FILE* const stdout;
extern FILE* const stderr;
	#else
typedef struct _IO_FILE FILE;
extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;
#if defined(__GLIBC__) || defined(__GNU_LIBRARY__)
// V declares the stdio functions manually here, instead of including <stdio.h>.
// glibc defines L_tmpnam only while <stdio.h> is being processed (it sits behind
// `#ifdef _STDIO_H` in <bits/stdio_lim.h>), and it is the one stdio limit macro that
// <stdio.h> itself uses in a prototype: char *tmpnam(char[L_tmpnam]). So a <stdio.h>
// pulled in later by a module header (sqlite3.h, gc.h, ...) can fail with L_tmpnam
// being undeclared; see vlang/v#28108. Define it here, to the stable glibc value,
// without adding an include. A later identical redefinition by glibc is a no-op.
#ifndef L_tmpnam
#define L_tmpnam 20
#endif
#endif
	#endif
typedef __builtin_va_list va_list;
#ifndef va_start
	#define va_start(ap, v) __builtin_va_start(ap, v)
#endif
#ifndef va_arg
	#define va_arg(ap, t) __builtin_va_arg(ap, t)
#endif
#ifndef va_end
	#define va_end(ap) __builtin_va_end(ap)
#endif
#ifndef va_copy
	#define va_copy(dest, src) __builtin_va_copy(dest, src)
#endif
#endif
#if (!defined(_MSC_VER) || defined(__clang__)) && !defined(__cplusplus) && !defined(__NetBSD__)
// mingw-w64 stdio.h declares these as static __mingw_ovr inline overrides
// when __USE_MINGW_ANSI_STDIO is on. Skip them under gcc+mingw to avoid
// static-after-extern conflicts; clang+mingw needs them because it builds
// with -Werror=implicit-function-declaration and does not hit the conflict.
// NetBSD pulls these prototypes from <stdio.h>/<stdlib.h>/<string.h> via
// the include block above to avoid `__restrict` qualifier conflicts.
#if !((defined(__MINGW32__) || defined(__MINGW64__)) && !defined(__clang__))
V_CRT_LINKAGE int V_CRT_CALL vfprintf(FILE *stream, const char *format, va_list ap);
V_CRT_LINKAGE int V_CRT_CALL vsnprintf(char *str, size_t size, const char *format, va_list ap);
V_CRT_LINKAGE int V_CRT_CALL fprintf(FILE *stream, const char *format, ...);
V_CRT_LINKAGE int V_CRT_CALL printf(const char *format, ...);
V_CRT_LINKAGE int V_CRT_CALL snprintf(char *str, size_t size, const char *format, ...);
V_CRT_LINKAGE int V_CRT_CALL sprintf(char *str, const char *format, ...);
V_CRT_LINKAGE int V_CRT_CALL sscanf(const char *str, const char *format, ...);
V_CRT_LINKAGE int V_CRT_CALL scanf(const char *format, ...);
#endif
V_CRT_LINKAGE int V_CRT_CALL puts(const char *str);
V_CRT_LINKAGE void V_CRT_CALL perror(const char *str);
V_CRT_LINKAGE int V_CRT_CALL fputs(const char *str, FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL getchar(void);
V_CRT_LINKAGE int V_CRT_CALL putchar(int ch);
V_CRT_LINKAGE int V_CRT_CALL getc(FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL fgetc(FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL ungetc(int ch, FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL fflush(FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL feof(FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL ferror(FILE *stream);
V_CRT_LINKAGE void V_CRT_CALL clearerr(FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL setvbuf(FILE *stream, char *buf, int mode, size_t size);
V_CRT_LINKAGE long V_CRT_CALL ftell(FILE *stream);
V_CRT_LINKAGE void V_CRT_CALL rewind(FILE *stream);
V_CRT_LINKAGE FILE * V_CRT_CALL fopen(const char *filename, const char *mode);
V_CRT_LINKAGE FILE * V_CRT_CALL fdopen(int fd, const char *mode);
V_CRT_LINKAGE FILE * V_CRT_CALL freopen(const char *filename, const char *mode, FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL fileno(FILE *stream);
V_CRT_LINKAGE size_t V_CRT_CALL fread(void *ptr, size_t size, size_t items, FILE *stream);
V_CRT_LINKAGE size_t V_CRT_CALL fwrite(const void *ptr, size_t size, size_t items, FILE *stream);
#if defined(__vinix__)
V_CRT_LINKAGE char * V_CRT_CALL fgets(char *str, size_t size, FILE *stream);
#else
V_CRT_LINKAGE char * V_CRT_CALL fgets(char *str, int size, FILE *stream);
#endif
V_CRT_LINKAGE int V_CRT_CALL fclose(FILE *stream);
#if defined(__vinix__)
V_CRT_LINKAGE FILE * V_CRT_CALL popen(char *command, char *mode);
#else
V_CRT_STDIO_LINKAGE FILE * V_CRT_CALL popen(const char *command, const char *mode);
#endif
V_CRT_STDIO_LINKAGE int V_CRT_CALL pclose(FILE *stream);
V_CRT_LINKAGE void * V_CRT_CALL malloc(size_t size);
V_CRT_LINKAGE void * V_CRT_CALL calloc(size_t nitems, size_t size);
V_CRT_LINKAGE void * V_CRT_CALL realloc(void *ptr, size_t size);
V_CRT_LINKAGE void * V_CRT_CALL aligned_alloc(size_t alignment, size_t size);
V_CRT_LINKAGE int V_CRT_CALL posix_memalign(void **memptr, size_t alignment, size_t size);
V_CRT_LINKAGE void V_CRT_CALL free(void *ptr);
V_CRT_LINKAGE int V_CRT_CALL rand(void);
V_CRT_LINKAGE void V_CRT_CALL srand(unsigned int seed);
V_CRT_LINKAGE int V_CRT_CALL atexit(void (*cb)(void));
V_CRT_LINKAGE void V_CRT_CALL exit(int status);
V_CRT_LINKAGE int V_CRT_CALL abs(int n);
V_CRT_LINKAGE int V_CRT_CALL atoi(const char *str);
V_CRT_LINKAGE double V_CRT_CALL atof(const char *str);
V_CRT_LINKAGE char * V_CRT_CALL getenv(const char *name);
V_CRT_LINKAGE int V_CRT_CALL setenv(const char *name, const char *value, int overwrite);
V_CRT_LINKAGE int V_CRT_CALL unsetenv(const char *name);
V_CRT_LINKAGE int V_CRT_CALL system(const char *command);
V_CRT_LINKAGE int V_CRT_CALL remove(const char *path);
V_CRT_LINKAGE int V_CRT_CALL rename(const char *old_path, const char *new_path);
V_CRT_LINKAGE char * V_CRT_CALL realpath(const char *path, char *resolved_path);
V_CRT_LINKAGE int V_CRT_CALL mkstemp(char *stemplate);
V_CRT_LINKAGE void V_CRT_CALL qsort(void *base, size_t items, size_t item_size, qsort_callback_func cb);
#if defined(__vinix__)
V_CRT_LINKAGE int V_CRT_CALL strcmp(char *left, char *right);
V_CRT_LINKAGE int V_CRT_CALL strncmp(char *left, char *right, size_t n);
#else
V_CRT_LINKAGE int V_CRT_CALL strcmp(const char *left, const char *right);
V_CRT_LINKAGE int V_CRT_CALL strncmp(const char *left, const char *right, size_t n);
#endif
#if !defined(_WIN32) && !defined(_WIN64) && !defined(__BIONIC__)
V_CRT_LINKAGE char * V_CRT_CALL strdup(const char *str);
#endif
#if !defined(_WIN32) && !defined(_WIN64)
V_CRT_LINKAGE int V_CRT_CALL strcasecmp(const char *left, const char *right);
V_CRT_LINKAGE int V_CRT_CALL strncasecmp(const char *left, const char *right, size_t n);
#endif
#if defined(__vinix__)
V_CRT_LINKAGE size_t V_CRT_CALL strlen(char *str);
#else
V_CRT_LINKAGE size_t V_CRT_CALL strlen(const char *str);
#endif
V_CRT_LINKAGE char * V_CRT_CALL strerror(int errnum);
V_CRT_LINKAGE void * V_CRT_CALL memcpy(void *dest, const void *src, size_t n);
V_CRT_LINKAGE void * V_CRT_CALL memmove(void *dest, const void *src, size_t n);
V_CRT_LINKAGE void * V_CRT_CALL memset(void *dest, int ch, size_t n);
V_CRT_LINKAGE int V_CRT_CALL memcmp(const void *left, const void *right, size_t n);
// memchr/strchr/strrchr/strstr are the C23 type-generic string functions, and
// glibc 2.42+ implements them as function-like macros over _Generic, so that a
// const-qualified argument yields a const-qualified return type. If any include
// above already pulled in <string.h> (mbedtls/net_sockets.h, netdb.h, dirent.h,
// ... all do, and gcc 15 defaults to -std=gnu23), the name is already a macro
// here, and a declaration like
// `void *memchr(const void *str, int c, size_t n);` expands into the middle of
// a _Generic expression, which fails to parse:
// `error: expected identifier or ( before _Generic`.
// A defined macro also means <string.h> has already declared the real function,
// so skipping the declaration below loses nothing in that case. The reverse
// order stays fine as-is: a <string.h> pulled in later by a module header
// defines the macro after these declarations, which C permits.
#ifndef memchr
V_CRT_LINKAGE void * V_CRT_CALL memchr(const void *str, int c, size_t n);
#endif
#ifndef strchr
V_CRT_LINKAGE char * V_CRT_CALL strchr(const char *str, int c);
#endif
#ifndef strrchr
V_CRT_LINKAGE char * V_CRT_CALL strrchr(const char *str, int c);
#endif
#ifndef strstr
V_CRT_LINKAGE char * V_CRT_CALL strstr(const char *haystack, const char *needle);
#endif
V_CRT_LINKAGE int V_CRT_CALL fseek(FILE *stream, long offset, int whence);
V_CRT_LINKAGE isize V_CRT_CALL getline(char **lineptr, size_t *n, FILE *stream);
#if defined(_WIN32) || defined(_WIN64)
V_CRT_STDIO_LINKAGE int V_CRT_CALL _fseeki64(FILE *stream, i64 offset, int whence);
V_CRT_LINKAGE int V_CRT_CALL fgetpos(FILE *stream, i64 *pos);
V_CRT_STDIO_LINKAGE int V_CRT_CALL _fileno(FILE *stream);
V_CRT_STDIO_LINKAGE FILE * V_CRT_CALL _wfopen(const unsigned short *filename, const unsigned short *mode);
V_CRT_STDIO_LINKAGE int V_CRT_CALL freopen_s(FILE **new_stream, const char *filename, const char *mode, FILE *stream);
V_CRT_STDIO_LINKAGE FILE * V_CRT_CALL _wfreopen(const unsigned short *filename, const unsigned short *mode, FILE *stream);
V_CRT_STDIO_LINKAGE FILE * V_CRT_CALL _wpopen(const unsigned short *command, const unsigned short *mode);
V_CRT_STDIO_LINKAGE int V_CRT_CALL _pclose(FILE *stream);
V_CRT_STDIO_LINKAGE int V_CRT_CALL _wremove(const unsigned short *path);
V_CRT_LINKAGE void * V_CRT_CALL _aligned_malloc(size_t size, size_t alignment);
V_CRT_LINKAGE void * V_CRT_CALL _aligned_realloc(void *memory, size_t size, size_t alignment);
V_CRT_LINKAGE void V_CRT_CALL _aligned_free(void *memory);
V_CRT_LINKAGE unsigned short * V_CRT_CALL _wgetenv(const unsigned short *varname);
V_CRT_LINKAGE int V_CRT_CALL _wputenv(const unsigned short *envstring);
V_CRT_LINKAGE int V_CRT_CALL _putenv_s(const char *name, const char *value);
#endif
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef _TRUNCATE
	#define _TRUNCATE ((size_t)-1)
#endif
V_CRT_LINKAGE int V_CRT_CALL _vscprintf(const char *format, va_list ap);
V_CRT_LINKAGE int V_CRT_CALL _vsnprintf_s(char *buffer, size_t size, size_t count, const char *format, va_list ap);
#endif
#endif
#ifndef _IOFBF
	#define _IOFBF 0
#endif
#ifndef _IOLBF
	#define _IOLBF 1
#endif
#ifndef _IONBF
	#define _IONBF 2
#endif
#ifndef EOF
	#define EOF (-1)
#endif
#ifndef SEEK_SET
	#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
	#define SEEK_CUR 1
#endif
#ifndef SEEK_END
	#define SEEK_END 2
#endif
#ifndef RAND_MAX
enum {
	#if defined(_MSC_VER)
		RAND_MAX = 0x7fff
	#else
		RAND_MAX = 2147483647
	#endif
};
#endif
#undef V_CRT_STDIO_LINKAGE
#undef V_CRT_LINKAGE
#undef V_CRT_CALL
#define V_MANUAL_STDLIB_HEADERS 1
void abort(void);
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>
#if defined(__has_include)
#if __has_include(<wchar.h>)
#include <wchar.h>
#endif
#else
#include <wchar.h>
#endif
#if defined(_WIN32) && (defined(__TINYC__) || (defined(_MSC_VER) && !defined(__clang__)))
#include "/home/gab/Projects/v/thirdparty/stdatomic/win/atomic.h"
#else
#if defined(__OBJC__) && defined(__GNUC__) && !defined(__clang__)
#define _Atomic volatile
#endif
#include <stdatomic.h>
#if defined(__OBJC__) && defined(__GNUC__) && !defined(__clang__)
#undef _Atomic
#endif
#endif
#if defined(__linux__) || defined(__ANDROID__)
#include <sys/syscall.h>
#endif
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
#include <sys/event.h>
#endif
#ifdef _WIN32
#include <io.h>
#include <process.h>
#include <windows.h>
#ifdef __TINYC__
DWORD WINAPI GetFinalPathNameByHandleW(HANDLE, unsigned short*, DWORD, DWORD);
#endif
#if defined(_MSC_VER)
#include <intrin.h>
#include <dbghelp.h>
#endif
#else
#include <dirent.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <semaphore.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/un.h>
#include <sys/uio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <utime.h>
#if defined(__linux__) && defined(__GLIBC__)
#include <sys/poll.h>
#else
#include <poll.h>
#endif
#endif
#ifdef __APPLE__
#include <mach/mach.h>
#include <mach/mach_vm.h>
#include <CommonCrypto/CommonDigest.h>
#include <mach/mach_time.h>
#include <mach-o/dyld.h>
#endif
#if defined(__linux__) || defined(__ANDROID__)
#include <sys/epoll.h>
#endif
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
#include <sys/event.h>
#endif
#if defined(__FreeBSD__) || defined(__OpenBSD__)
#include <sys/sysctl.h>
#endif
#if defined(__has_include) && !defined(__TINYC__)
	#if __has_include(<execinfo.h>) && !defined(_WIN32)
		#define __V_HAVE_EXECINFO_H 1
		#include <execinfo.h>
	#endif
#elif (defined(__linux__) && (defined(__GLIBC__) || defined(__GNU_LIBRARY__))) || defined(__APPLE__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__)
	#define __V_HAVE_EXECINFO_H 1
	#include <execinfo.h>
#endif
#if !defined(__V_HAVE_EXECINFO_H) && !defined(_WIN32)
int backtrace(void** __array, int __size);
char** backtrace_symbols(void* const* __array, int __size);
void backtrace_symbols_fd(void* const* __array, int __size, int __fd);
#endif

#ifndef _WIN32
extern char** environ;
#endif
void* v_gc_malloc_uncollectable(size_t n);
void v_gc_free(void* ptr);
void GC_allow_register_threads(void);
i32 v_gc_pthread_create(void* thread, void* attr, void* start_routine, void* arg);
i32 v_gc_pthread_join(void* thread, void* retval);
i32 v_gc_pthread_detach(void* thread);
i32 v_gc_pthread_sigmask(i32 how, const void* const_set, void* oldset);
i32 v_gc_pthread_cancel(void* thread);
void v_gc_pthread_exit(void* result);
void* v_gc_dlopen(const char* const_path, i32 mode);
#define pthread_create v_gc_pthread_create
#define pthread_join v_gc_pthread_join
#define pthread_detach v_gc_pthread_detach
#define pthread_sigmask v_gc_pthread_sigmask
#define pthread_cancel v_gc_pthread_cancel
#define pthread_exit v_gc_pthread_exit
#define dlopen v_gc_dlopen
static void* __v_thread_alloc(size_t size) {
#if defined(_VGCBOEHM) || defined(CUSTOM_DEFINE_gcboehm)
	void* p = v_gc_malloc_uncollectable(size);
#else
	void* p = malloc(size);
#endif
	if (!p) { fprintf(stderr, "V thread allocation failed\n"); abort(); }
	return p;
}
static void __v_thread_free(void* ptr) {
#if defined(_VGCBOEHM) || defined(CUSTOM_DEFINE_gcboehm)
	v_gc_free(ptr);
#else
	free(ptr);
#endif
}
#ifdef _WIN32
typedef struct { HANDLE handle; void* context; } __v_thread;
static bool __v_thread_equal(__v_thread a, __v_thread b) { return a.handle == b.handle; }
typedef void* (*__v_thread_start_fn)(void*);
typedef struct { __v_thread_start_fn start; void* arg; void* result; } __v_windows_thread_context;
static const size_t __v_thread_stack_size = V_THREAD_STACK_SIZE;
static DWORD WINAPI __v_windows_thread_start(void* raw_context) { __v_windows_thread_context* context = (__v_windows_thread_context*)raw_context; context->result = context->start(context->arg); return 0; }
static __v_thread __v_thread_spawn(__v_thread_start_fn start, void* arg, void (*cleanup)(void*)) {
	__v_thread result;
	__v_windows_thread_context* context = (__v_windows_thread_context*)__v_thread_alloc(sizeof(__v_windows_thread_context));
	context->start = start; context->arg = arg; context->result = NULL;
	result.context = context;
	result.handle = CreateThread(NULL, __v_thread_stack_size, __v_windows_thread_start, context, 0, NULL);
	if (!result.handle) { DWORD error = GetLastError(); free(context); if (cleanup) cleanup(arg); fprintf(stderr, "V thread creation failed: %lu\n", (unsigned long)error); abort(); }
	return result;
}
static void* __v_thread_join(__v_thread thread) {
	DWORD rc = WaitForSingleObject(thread.handle, INFINITE);
	if (rc != WAIT_OBJECT_0) { fprintf(stderr, "V thread join failed: %lu\n", (unsigned long)rc); abort(); }
	void* result = ((__v_windows_thread_context*)thread.context)->result;
	if (!CloseHandle(thread.handle)) { DWORD error = GetLastError(); __v_thread_free(thread.context); fprintf(stderr, "V thread handle cleanup failed: %lu\n", (unsigned long)error); abort(); }
	__v_thread_free(thread.context);
	return result;
}
static DWORD WINAPI __v_windows_detached_thread_start(void* raw_context) { __v_windows_thread_context context = *(__v_windows_thread_context*)raw_context; __v_thread_free(raw_context); void* result = context.start(context.arg); if (result) __v_thread_free(result); return 0; }
static __v_thread __v_thread_spawn_detached(__v_thread_start_fn start, void* arg, void (*cleanup)(void*)) {
	__v_windows_thread_context* context = (__v_windows_thread_context*)__v_thread_alloc(sizeof(__v_windows_thread_context));
	context->start = start; context->arg = arg; context->result = NULL;
	HANDLE handle = CreateThread(NULL, __v_thread_stack_size, __v_windows_detached_thread_start, context, 0, NULL);
	if (!handle) { DWORD error = GetLastError(); __v_thread_free(context); if (cleanup) cleanup(arg); fprintf(stderr, "V thread creation failed: %lu\n", (unsigned long)error); abort(); }
	if (!CloseHandle(handle)) { fprintf(stderr, "V thread handle cleanup failed: %lu\n", (unsigned long)GetLastError()); abort(); }
	return (__v_thread){0};
}
static __v_thread __v_thread_spawn_comparable(__v_thread_start_fn start, void* arg, void (*cleanup)(void*)) {
	__v_windows_thread_context* context = (__v_windows_thread_context*)__v_thread_alloc(sizeof(__v_windows_thread_context));
	context->start = start; context->arg = arg; context->result = NULL;
	HANDLE handle = CreateThread(NULL, __v_thread_stack_size, __v_windows_detached_thread_start, context, 0, NULL);
	if (!handle) { DWORD error = GetLastError(); __v_thread_free(context); if (cleanup) cleanup(arg); fprintf(stderr, "V thread creation failed: %lu\n", (unsigned long)error); abort(); }
	return (__v_thread){.handle = handle, .context = NULL};
}
static void __v_thread_release_comparable(__v_thread thread) { if (thread.handle && !CloseHandle(thread.handle)) { fprintf(stderr, "V thread handle cleanup failed: %lu\n", (unsigned long)GetLastError()); abort(); } }
#else
typedef struct { pthread_t handle; } __v_thread;
static bool __v_thread_equal(__v_thread a, __v_thread b) { return pthread_equal(a.handle, b.handle) != 0; }
typedef void* (*__v_thread_start_fn)(void*);
static const size_t __v_thread_stack_size = V_THREAD_STACK_SIZE;
static __v_thread __v_thread_spawn(__v_thread_start_fn start, void* arg, void (*cleanup)(void*)) {
	__v_thread result;
	pthread_attr_t attr;
	int rc = pthread_attr_init(&attr);
	if (rc != 0) { if (cleanup) cleanup(arg); fprintf(stderr, "V thread attribute initialization failed: %d\n", rc); abort(); }
	rc = pthread_attr_setstacksize(&attr, __v_thread_stack_size);
	if (rc != 0) { pthread_attr_destroy(&attr); if (cleanup) cleanup(arg); fprintf(stderr, "V thread stack size setup failed: %d\n", rc); abort(); }
	rc = pthread_create(&result.handle, &attr, (void*)start, arg);
	int attr_rc = pthread_attr_destroy(&attr);
	if (rc != 0) { if (cleanup) cleanup(arg); fprintf(stderr, "V thread creation failed: %d\n", rc); abort(); }
	if (attr_rc != 0) { fprintf(stderr, "V thread attribute cleanup failed: %d\n", attr_rc); abort(); }
	return result;
}
static void* __v_thread_join(__v_thread thread) { void* result = NULL; int rc = pthread_join(thread.handle, &result); if (rc != 0) { fprintf(stderr, "V thread join failed: %d\n", rc); abort(); } return result; }
typedef struct { __v_thread_start_fn start; void* arg; } __v_detached_thread_context;
static void* __v_detached_thread_start(void* raw_context) { __v_detached_thread_context context = *(__v_detached_thread_context*)raw_context; __v_thread_free(raw_context); void* result = context.start(context.arg); if (result) __v_thread_free(result); return NULL; }
static __v_thread __v_thread_spawn_detached(__v_thread_start_fn start, void* arg, void (*cleanup)(void*)) {
	__v_detached_thread_context* context = (__v_detached_thread_context*)__v_thread_alloc(sizeof(__v_detached_thread_context));
	context->start = start; context->arg = arg;
	pthread_t handle;
	pthread_attr_t attr;
	int rc = pthread_attr_init(&attr);
	if (rc != 0) { __v_thread_free(context); if (cleanup) cleanup(arg); fprintf(stderr, "V thread attribute initialization failed: %d\n", rc); abort(); }
	rc = pthread_attr_setstacksize(&attr, __v_thread_stack_size);
	if (rc == 0) rc = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (rc != 0) { pthread_attr_destroy(&attr); __v_thread_free(context); if (cleanup) cleanup(arg); fprintf(stderr, "V thread attribute setup failed: %d\n", rc); abort(); }
	rc = pthread_create(&handle, &attr, (void*)__v_detached_thread_start, context);
	int attr_rc = pthread_attr_destroy(&attr);
	if (rc != 0) { __v_thread_free(context); if (cleanup) cleanup(arg); fprintf(stderr, "V thread creation failed: %d\n", rc); abort(); }
	if (attr_rc != 0) { fprintf(stderr, "V thread attribute cleanup failed: %d\n", attr_rc); abort(); }
	return (__v_thread){0};
}
static __v_thread __v_thread_spawn_comparable(__v_thread_start_fn start, void* arg, void (*cleanup)(void*)) { return __v_thread_spawn(start, arg, cleanup); }
static void __v_thread_release_comparable(__v_thread thread) { if (thread.handle) { int rc = pthread_detach(thread.handle); if (rc != 0) { fprintf(stderr, "V thread detach failed: %d\n", rc); abort(); } } }
#endif
void* v_thread_signal_stack_enter(void* stack_top, size_t stack_size);
void v_thread_signal_stack_leave(void* alt_stack);
#define __v_thread_signal_stack_enter(stack_top) v_thread_signal_stack_enter(stack_top, V_THREAD_STACK_SIZE)
#define __v_thread_signal_stack_leave(alt_stack) v_thread_signal_stack_leave(alt_stack)
#ifndef __V_architecture
#define __V_architecture 0
#endif
#if defined(__x86_64__) || defined(_M_AMD64)
#define __V_amd64 1
#undef __V_architecture
#define __V_architecture 1
#endif
#if defined(__aarch64__) || defined(__arm64__) || defined(_M_ARM64)
#define __V_arm64 1
#undef __V_architecture
#define __V_architecture 2
#endif
#if defined(__arm__) || defined(_M_ARM)
#define __V_arm32 1
#undef __V_architecture
#define __V_architecture 3
#endif
#if defined(__riscv) && __riscv_xlen == 64
#define __V_rv64 1
#undef __V_architecture
#define __V_architecture 4
#endif
#if defined(__riscv) && __riscv_xlen == 32
#define __V_rv32 1
#undef __V_architecture
#define __V_architecture 5
#endif
#if defined(__i386__) || defined(_M_IX86)
#define __V_x86 1
#undef __V_architecture
#define __V_architecture 6
#endif
#if defined(__s390x__)
#define __V_s390x 1
#undef __V_architecture
#define __V_architecture 7
#endif
#if defined(__powerpc64__) && defined(__LITTLE_ENDIAN__)
#define __V_ppc64le 1
#undef __V_architecture
#define __V_architecture 8
#endif
#if defined(__loongarch64)
#define __V_loongarch64 1
#undef __V_architecture
#define __V_architecture 9
#endif
#if defined(__sparc__)
#define __V_sparc64 1
#undef __V_architecture
#define __V_architecture 10
#endif
#if defined(__powerpc64__) && defined(__BIG_ENDIAN__)
#define __V_ppc64 1
#undef __V_architecture
#define __V_architecture 11
#endif
#if (defined(__powerpc__) || defined(__powerpc) || defined(__POWERPC__) || defined(__ppc__) || defined(__ppc) || defined(__PPC__)) && !defined(__powerpc64__) && !defined(__ppc64__) && !defined(__PPC64__)
#define __V_ppc 1
#undef __V_architecture
#define __V_architecture 12
#endif
#if UINTPTR_MAX == 0xFFFFFFFFFFFFFFFFu
#define TARGET_IS_64BIT 1
#else
#define TARGET_IS_32BIT 1
#endif
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define TARGET_ORDER_IS_BIG 1
#else
#define TARGET_ORDER_IS_LITTLE 1
#endif

#define elem_size element_size
#define c_name types__c_name
#define builtin__string_clone string__clone
#define builtin__tos2 tos2
/* V3CACHE_NATIVE_DIRECTIVES_BEGIN */
#ifndef V_TRACK_HEAP_CHECKS_H
#define V_TRACK_HEAP_CHECKS_H

#if defined(CUSTOM_DEFINE_track_heap) && (defined(_VGCBOEHM) || defined(CUSTOM_DEFINE_gcboehm))
#error "-d track_heap requires manual memory management; rebuild with -gc none"
#endif

#if defined(CUSTOM_DEFINE_track_heap) && defined(CUSTOM_DEFINE_vgc)
#error "-d track_heap requires manual memory management; rebuild with -gc none"
#endif

#if defined(CUSTOM_DEFINE_track_heap) && defined(_VPREALLOC)
#error "-d track_heap requires manual memory management; rebuild with -gc none (not -prealloc)"
#endif

#endif

#define v_signal_with_handler_cast(sig, handler) signal((sig), (void (*)(int))(handler))

/* V3CACHE_NATIVE_DIRECTIVES_END */
typedef enum {
	ArrayFlags__noslices = 1,
	ArrayFlags__noshrink = 2,
	ArrayFlags__nogrow = 4,
	ArrayFlags__nofree = 8,
	ArrayFlags__managed = 16,
	ArrayFlags__noscan_data = 32,
	ArrayFlags__is_slice = 64,
} ArrayFlags;

typedef enum {
	ChanState__success = 0,
	ChanState__not_ready = 1,
	ChanState__closed = 2,
} ChanState;

typedef enum {
	GraphemeBreakProperty__other = 0,
	GraphemeBreakProperty__cr = 1,
	GraphemeBreakProperty__lf = 2,
	GraphemeBreakProperty__control = 3,
	GraphemeBreakProperty__extend = 4,
	GraphemeBreakProperty__regional_indicator = 5,
	GraphemeBreakProperty__prepend = 6,
	GraphemeBreakProperty__spacing_mark = 7,
	GraphemeBreakProperty__l = 8,
	GraphemeBreakProperty__v = 9,
	GraphemeBreakProperty__t = 10,
	GraphemeBreakProperty__lv = 11,
	GraphemeBreakProperty__lvt = 12,
	GraphemeBreakProperty__zwj = 13,
} GraphemeBreakProperty;

typedef enum {
	AttributeKind__plain = 0,
	AttributeKind__string = 1,
	AttributeKind__number = 2,
	AttributeKind__bool = 3,
	AttributeKind__comptime_define = 4,
} AttributeKind;

typedef enum {
	MapMode__to_upper = 0,
	MapMode__to_lower = 1,
	MapMode__to_title = 2,
} MapMode;

typedef enum {
	TrimMode__trim_left = 0,
	TrimMode__trim_right = 1,
	TrimMode__trim_both = 2,
} TrimMode;

typedef enum {
	StrIntpType__si_no_str = 0,
	StrIntpType__si_c = 1,
	StrIntpType__si_u8 = 2,
	StrIntpType__si_i8 = 3,
	StrIntpType__si_u16 = 4,
	StrIntpType__si_i16 = 5,
	StrIntpType__si_u32 = 6,
	StrIntpType__si_i32 = 7,
	StrIntpType__si_u64 = 8,
	StrIntpType__si_i64 = 9,
	StrIntpType__si_e32 = 10,
	StrIntpType__si_e64 = 11,
	StrIntpType__si_f32 = 12,
	StrIntpType__si_f64 = 13,
	StrIntpType__si_g32 = 14,
	StrIntpType__si_g64 = 15,
	StrIntpType__si_s = 16,
	StrIntpType__si_p = 17,
	StrIntpType__si_r = 18,
	StrIntpType__si_vp = 19,
} StrIntpType;

typedef enum {
	strings__IndentState__normal = 0,
	strings__IndentState__in_string = 1,
} strings__IndentState;

typedef enum {
	strconv__Align_text__right = 0,
	strconv__Align_text__left = 1,
	strconv__Align_text__center = 2,
} strconv__Align_text;

typedef enum {
	strconv__ParserState__ok = 0,
	strconv__ParserState__pzero = 1,
	strconv__ParserState__mzero = 2,
	strconv__ParserState__pinf = 3,
	strconv__ParserState__minf = 4,
	strconv__ParserState__invalid_number = 5,
	strconv__ParserState__extra_char = 6,
} strconv__ParserState;

typedef enum {
	strconv__Char_parse_state__start = 0,
	strconv__Char_parse_state__norm_char = 1,
	strconv__Char_parse_state__field_char = 2,
	strconv__Char_parse_state__pad_ch = 3,
	strconv__Char_parse_state__len_set_start = 4,
	strconv__Char_parse_state__len_set_in = 5,
	strconv__Char_parse_state__check_type = 6,
	strconv__Char_parse_state__check_float = 7,
	strconv__Char_parse_state__check_float_in = 8,
	strconv__Char_parse_state__reset_params = 9,
} strconv__Char_parse_state;

typedef enum {
	os__MmapMode__read_only = 0,
	os__MmapMode__read_write = 1,
} os__MmapMode;

typedef enum {
	os__WalkDirAction__proceed = 0,
	os__WalkDirAction__skip_dir = 1,
	os__WalkDirAction__stop = 2,
} os__WalkDirAction;

typedef enum {
	os__ProcessState__not_started = 0,
	os__ProcessState__running = 1,
	os__ProcessState__stopped = 2,
	os__ProcessState__exited = 3,
	os__ProcessState__aborted = 4,
	os__ProcessState__closed = 5,
} os__ProcessState;

typedef enum {
	os__Signal__hup = 1,
	os__Signal__v_int = 2,
	os__Signal__quit = 3,
	os__Signal__ill = 4,
	os__Signal__trap = 5,
	os__Signal__abrt = 6,
	os__Signal__bus = 7,
	os__Signal__fpe = 8,
	os__Signal__kill = 9,
	os__Signal__usr1 = 10,
	os__Signal__segv = 11,
	os__Signal__usr2 = 12,
	os__Signal__v_pipe = 13,
	os__Signal__alrm = 14,
	os__Signal__term = 15,
	os__Signal__stkflt = 16,
	os__Signal__chld = 17,
	os__Signal__cont = 18,
	os__Signal__stop = 19,
	os__Signal__tstp = 20,
	os__Signal__ttin = 21,
	os__Signal__ttou = 22,
	os__Signal__urg = 23,
	os__Signal__xcpu = 24,
	os__Signal__xfsz = 25,
	os__Signal__vtalrm = 26,
	os__Signal__prof = 27,
	os__Signal__winch = 28,
	os__Signal__poll = 29,
	os__Signal__pwr = 30,
	os__Signal__sys = 31,
} os__Signal;

typedef enum {
	os__SeekMode__start = 0,
	os__SeekMode__current = 1,
	os__SeekMode__end = 2,
} os__SeekMode;

typedef enum {
	os__FileBufferMode__fully_buffered = _IOFBF,
	os__FileBufferMode__line_buffered = _IOLBF,
	os__FileBufferMode__not_buffered = _IONBF,
} os__FileBufferMode;

typedef enum {
	os__FileType__unknown = 0,
	os__FileType__regular = 1,
	os__FileType__directory = 2,
	os__FileType__character_device = 3,
	os__FileType__block_device = 4,
	os__FileType__fifo = 5,
	os__FileType__symbolic_link = 6,
	os__FileType__socket = 7,
} os__FileType;

typedef enum {
	os__GlobMatch__exact = 0,
	os__GlobMatch__ends_with = 1,
	os__GlobMatch__starts_with = 2,
	os__GlobMatch__start_and_ends_with = 3,
	os__GlobMatch__contains = 4,
	os__GlobMatch__any = 5,
} os__GlobMatch;

typedef enum {
	os__ChildProcessPipeKind__v_stdin = 0,
	os__ChildProcessPipeKind__v_stdout = 1,
	os__ChildProcessPipeKind__v_stderr = 2,
} os__ChildProcessPipeKind;

typedef enum {
	closure__MemoryProtectAtrr__read_exec = 0,
	closure__MemoryProtectAtrr__read_write = 1,
} closure__MemoryProtectAtrr;

typedef struct AutostrAddrStackState AutostrAddrStackState;
typedef struct DenseArray DenseArray;
typedef struct main__DupeGroup main__DupeGroup;
typedef struct Error Error;
typedef struct MessageError MessageError;
typedef struct None__ None__;
typedef struct OwnershipV3InterfacePayload OwnershipV3InterfacePayload;
typedef struct PanicDebugInfo PanicDebugInfo;
typedef struct PanicFrame PanicFrame;
typedef struct PanicRecord PanicRecord;
typedef struct PanicState PanicState;
typedef struct main__ScannedFile main__ScannedFile;
typedef struct VMapData VMapData;
typedef struct VMemoryBlock VMemoryBlock;
typedef struct VPreallocBlockCache VPreallocBlockCache;
typedef struct VPreallocRange VPreallocRange;
typedef struct VPreallocScope VPreallocScope;
typedef struct array array;
typedef struct closure__Closure closure__Closure;
typedef struct closure__ClosureLifetimeFrame closure__ClosureLifetimeFrame;
typedef struct closure__ClosureLifetimeRecord closure__ClosureLifetimeRecord;
typedef struct closure__ClosureLifetimeState closure__ClosureLifetimeState;
typedef struct closure__ClosureLiveInfo closure__ClosureLiveInfo;
typedef struct closure__ClosureMutex closure__ClosureMutex;
typedef struct closure__ClosurePage closure__ClosurePage;
typedef struct fnv1a__Fnv1a64 fnv1a__Fnv1a64;
typedef struct map map;
typedef struct os__Eof os__Eof;
typedef struct os__ExecutableNotFoundError os__ExecutableNotFoundError;
typedef struct os__File os__File;
typedef struct os__FileNotOpenedError os__FileNotOpenedError;
typedef struct os__NotExpected os__NotExpected;
typedef struct os__SizeOfTypeIs0Error os__SizeOfTypeIs0Error;
typedef struct os__WalkDirEntry os__WalkDirEntry;
typedef struct strconv__Dec32 strconv__Dec32;
typedef struct strconv__Dec64 strconv__Dec64;
typedef struct strconv__PrepNumber strconv__PrepNumber;
typedef struct string string;
typedef struct IError IError;
typedef struct hash__Hash hash__Hash;
typedef struct hash__Hash32er hash__Hash32er;
typedef struct hash__Hash64er hash__Hash64er;
typedef struct hash__Hasher hash__Hasher;
typedef array Array;

typedef struct multi_return_u32_u32 multi_return_u32_u32;
typedef struct multi_return_string_string multi_return_string_string;
typedef struct multi_return_i64_i64 multi_return_i64_i64;
typedef struct multi_return_u64_i64 multi_return_u64_i64;
typedef struct multi_return_int_strconv__PrepNumber multi_return_int_strconv__PrepNumber;
typedef struct multi_return_Array_Array multi_return_Array_Array;
typedef struct multi_return_string_i64 multi_return_string_i64;

typedef double Array_fixed_double_36[36];
typedef i32 Array_fixed_i32_1264[1264];
typedef i64 Array_fixed_i64_3[3];
typedef i64 Array_fixed_i64_64[64];
typedef u16 Array_fixed_u16_112[112];
typedef u16 Array_fixed_u16_133[133];
typedef u16 Array_fixed_u16_16[16];
typedef u16 Array_fixed_u16_424[424];
typedef u32 Array_fixed_u32_10[10];
typedef u32 Array_fixed_u32_508[508];
typedef u64 Array_fixed_u64_18[18];
typedef u64 Array_fixed_u64_20[20];
typedef u64 Array_fixed_u64_309[309];
typedef u64 Array_fixed_u64_31[31];
typedef u64 Array_fixed_u64_324[324];
typedef u64 Array_fixed_u64_47[47];
typedef u64 Array_fixed_u64_584[584];
typedef u64 Array_fixed_u64_652[652];
typedef u8 Array_fixed_u8_128[128];
typedef u8 Array_fixed_u8_15[15];
typedef u8 Array_fixed_u8_256[256];
typedef u8 Array_fixed_u8_6[6];
typedef u8 Array_fixed_u8_64[64];
typedef void* Array_fixed_voidptr_11[11];
typedef void* Array_fixed_voidptr_64[64];
typedef void* Array_fixed_voidptr_8[8];

typedef bool (*_fn_ptr_c95f092653bee64)(void*, void*);
typedef i64 (*_fn_ptr_ed95774d3a4e97ab)(void*, void*);
typedef int (*_fn_ptr_24927a217aab3552)(string, os__WalkDirEntry);
typedef u64 (*_fn_ptr_1e8d64a3d95a0da1)(void*);
typedef void* (*_fn_ptr_4104d547b520960a)(void);
typedef void (*_fn_ptr_1ad43b93b076e910)(char*);
typedef void (*_fn_ptr_a73f2ae88698453e)(char*, size_t);
typedef void (*_fn_ptr_21efbbd63959de6f)(i64);
typedef void (*_fn_ptr_22778bd639cd2677)(int);
typedef void (*_fn_ptr_f7530b1a1b506de7)(string);
typedef void (*_fn_ptr_39790037d38ea68)(void);
typedef void (*_fn_ptr_5373f7edc7b60e26)(void*);
typedef void (*_fn_ptr_a6b6a5be4f3dabb3)(void*, string);
typedef void (*_fn_ptr_1a3da2026b1489ea)(void*, void*);

typedef struct AutostrAddrStackState AutostrAddrStackState;
typedef struct DenseArray DenseArray;
typedef struct main__DupeGroup main__DupeGroup;
typedef struct Error Error;
typedef struct MessageError MessageError;
typedef struct None__ None__;
typedef struct OwnershipV3InterfacePayload OwnershipV3InterfacePayload;
typedef struct PanicDebugInfo PanicDebugInfo;
typedef struct PanicFrame PanicFrame;
typedef struct PanicRecord PanicRecord;
typedef struct PanicState PanicState;
typedef struct main__ScannedFile main__ScannedFile;
typedef struct VMapData VMapData;
typedef struct VMemoryBlock VMemoryBlock;
typedef struct VPreallocBlockCache VPreallocBlockCache;
typedef struct VPreallocRange VPreallocRange;
typedef struct VPreallocScope VPreallocScope;
typedef struct array array;
typedef struct closure__Closure closure__Closure;
typedef struct closure__ClosureLifetimeFrame closure__ClosureLifetimeFrame;
typedef struct closure__ClosureLifetimeRecord closure__ClosureLifetimeRecord;
typedef struct closure__ClosureLifetimeState closure__ClosureLifetimeState;
typedef struct closure__ClosureLiveInfo closure__ClosureLiveInfo;
typedef struct closure__ClosureMutex closure__ClosureMutex;
typedef struct closure__ClosurePage closure__ClosurePage;
typedef struct fnv1a__Fnv1a64 fnv1a__Fnv1a64;
typedef struct map map;
typedef struct os__Eof os__Eof;
typedef struct os__ExecutableNotFoundError os__ExecutableNotFoundError;
typedef struct os__File os__File;
typedef struct os__FileNotOpenedError os__FileNotOpenedError;
typedef struct os__NotExpected os__NotExpected;
typedef struct os__SizeOfTypeIs0Error os__SizeOfTypeIs0Error;
typedef struct os__WalkDirEntry os__WalkDirEntry;
typedef struct strconv__Dec32 strconv__Dec32;
typedef struct strconv__Dec64 strconv__Dec64;
typedef struct strconv__PrepNumber strconv__PrepNumber;
typedef struct string string;
typedef struct IError IError;
typedef struct hash__Hash hash__Hash;
typedef struct hash__Hash32er hash__Hash32er;
typedef struct hash__Hash64er hash__Hash64er;
typedef struct hash__Hasher hash__Hasher;
typedef array Array;
struct string {
	u8* str;
	i64 len;
	i64 is_lit;
};

struct IError {
	void* _object;
	union {
		void* _interface_meta;
		struct {
			u32 _typ : 31;
			u32 _object_is_boxed : 1;
		};
	};
};

typedef struct __v_option { bool ok; int value; } __v_option;
typedef struct __v_result { bool ok; union { IError err; int value; }; } __v_result;

struct array {
	void* data;
	i64 offset;
	i64 len;
	i64 cap;
	int flags;
	i64 element_size;
};

struct map {
	VMapData* data;
};

struct hash__Hash {
	void* _object;
	union {
		void* _interface_meta;
		struct {
			u32 _typ : 31;
			u32 _object_is_boxed : 1;
		};
	};
};

struct hash__Hash32er {
	void* _object;
	union {
		void* _interface_meta;
		struct {
			u32 _typ : 31;
			u32 _object_is_boxed : 1;
		};
	};
};

struct hash__Hash64er {
	void* _object;
	union {
		void* _interface_meta;
		struct {
			u32 _typ : 31;
			u32 _object_is_boxed : 1;
		};
	};
};

struct hash__Hasher {
	void* _object;
	union {
		void* _interface_meta;
		struct {
			u32 _typ : 31;
			u32 _object_is_boxed : 1;
		};
	};
};

struct AutostrAddrStackState {
	void* addrs[64];
	i64 types[64];
	i64 len;
	i64 overflow_depth;
};

typedef string Array_fixed_string_11[11];
typedef ptrdiff_t Array_fixed_ptrdiff_t_8[8];
typedef char Array_fixed_char_256[256];
typedef u8 Array_fixed_u8_32[32];
struct DenseArray {
	i64 key_bytes;
	i64 value_bytes;
	i64 cap;
	i64 len;
	u32 deletes;
	u8* all_deleted;
	u8* keys;
	u8* values;
};

struct main__DupeGroup {
	u64 size;
	string hash;
	Array files;
};

struct Error {
	E_STRUCT_DECL;
};

struct MessageError {
	string msg;
	i64 code;
};

struct None__ {
	Error Error;
};

struct OwnershipV3InterfacePayload {
	void* payload;
	i64 typ;
	bool is_boxed;
};

struct PanicDebugInfo {
	i64 line_no;
	string file;
	string mod;
	string fn_name;
};

struct PanicFrame {
	PanicFrame* prev;
	void* owner;
	_fn_ptr_5373f7edc7b60e26 jump;
};

struct PanicRecord {
	string msg;
	PanicDebugInfo debug;
	PanicFrame* frame;
	PanicFrame* resume;
	bool recovered;
	bool aborted;
};

struct PanicState {
	PanicFrame* top;
	PanicRecord* records;
	i64 len;
	i64 cap;
};

struct main__ScannedFile {
	string path;
	u64 size;
};

struct VMapData {
	i64 key_bytes;
	i64 value_bytes;
	u32 even_index;
	u8 cached_hashbits;
	u8 shift;
	DenseArray key_values;
	u32* metas;
	u32 extra_metas;
	bool has_string_keys;
	_fn_ptr_1e8d64a3d95a0da1 hash_fn;
	_fn_ptr_c95f092653bee64 key_eq_fn;
	_fn_ptr_1a3da2026b1489ea clone_fn;
	_fn_ptr_5373f7edc7b60e26 free_fn;
	i64 count;
};

struct VMemoryBlock {
	u8* current;
	u8* stop;
	u8* start;
	VMemoryBlock* previous;
	VMemoryBlock* next;
	VPreallocScope* scope;
	VPreallocBlockCache* recycle_cache;
	ptrdiff_t min_block_size;
	bool is_scope;
	bool mmap_allocated;
	i64 id;
	i64 mallocs;
};

struct VPreallocBlockCache {
	i64 count;
	ptrdiff_t bytes;
	void* starts[8];
	ptrdiff_t sizes[8];
};

struct VPreallocRange {
	size_t start;
	size_t stop;
};

struct VPreallocScope {
	VMemoryBlock* previous;
	VMemoryBlock* first;
	VMemoryBlock* saved_next;
	size_t min_address;
	size_t max_address;
	VPreallocRange* ranges;
	i64 ranges_len;
	i64 ranges_cap;
	i32 refs;
	i32 free_requested;
	i32 abandoned;
	i32 finalized;
};

struct closure__ClosureLifetimeFrame {
	i64 start;
	i64 end;
};

struct closure__ClosureLifetimeRecord {
	void* exec_ptr;
	u64 generation;
};

struct closure__ClosureLifetimeState {
	u64 owner_thread;
	bool active;
	bool disposed;
	i64 suspended;
	i64 frame_start;
	u64 frame_gen;
	u64 generation;
	u64 frame_generation;
	Array records;
	Array frames;
	closure__ClosureLifetimeState* next_free;
};

struct closure__ClosureLiveInfo {
	void* ctx;
	void* drop_data;
	u64 owns_data;
	u64 generation;
};

struct closure__ClosureMutex {
	u8 closure_mtx[128];
};

struct closure__ClosurePage {
	closure__ClosurePage* next;
	void* exec_page_start;
};

struct fnv1a__Fnv1a64 {
	u64 state;
};

struct os__Eof {
	Error Error;
};

struct os__ExecutableNotFoundError {
	Error Error;
};

struct os__File {
	void* cfile;
	i64 fd;
	bool is_opened;
};

struct os__FileNotOpenedError {
	Error Error;
};

struct os__NotExpected {
	string cause;
	i64 code;
};

struct os__SizeOfTypeIs0Error {
	Error Error;
};

typedef struct __v_option_IError { bool ok; IError value; } __v_option_IError;

struct os__WalkDirEntry {
	string name;
	bool is_dir;
	int typ;
	__v_option_IError err;
};

struct strconv__Dec32 {
	u32 m;
	i64 e;
};

struct strconv__Dec64 {
	u64 m;
	i64 e;
};

struct strconv__PrepNumber {
	bool negative;
	i64 exponent;
	u64 mantissa;
};

struct closure__Closure {
	closure__ClosureMutex ClosureMutex;
	void* closure_ptr;
	_fn_ptr_4104d547b520960a closure_get_data;
	i64 closure_cap;
	void* free_closure_ptr;
	closure__ClosurePage* pages;
	i64 v_page_size;
	map live;
	map active_lifetimes;
	u64 next_generation;
	closure__ClosureLifetimeState* free_lifetime_states;
	u64 next_lifetime_generation;
	u64 lifetime_state_allocs;
};

struct multi_return_u32_u32 {
	u32 arg0;
	u32 arg1;
};
struct multi_return_string_string {
	string arg0;
	string arg1;
};
struct multi_return_i64_i64 {
	i64 arg0;
	i64 arg1;
};
struct multi_return_u64_i64 {
	u64 arg0;
	i64 arg1;
};
struct multi_return_int_strconv__PrepNumber {
	int arg0;
	strconv__PrepNumber arg1;
};
struct multi_return_Array_Array {
	Array arg0;
	Array arg1;
};
struct multi_return_string_i64 {
	string arg0;
	i64 arg1;
};

typedef struct __v_option_string { bool ok; string value; } __v_option_string;
typedef struct __v_result_Array { bool ok; union { IError err; Array value; }; } __v_result_Array;
typedef struct __v_result_i64 { bool ok; union { IError err; i64 value; }; } __v_result_i64;
typedef struct __v_result_os__File { bool ok; union { IError err; os__File value; }; } __v_result_os__File;
typedef struct __v_result_string { bool ok; union { IError err; string value; }; } __v_result_string;
typedef struct __v_result_u32 { bool ok; union { IError err; u32 value; }; } __v_result_u32;

/* V3CACHE_SOURCE_DIRECTIVES_BEGIN */
/* V3CACHE_SOURCE_DIRECTIVES_END */
void GC_allow_register_threads(void);
i32* ___errno(void);
i32* __get_errno_ptr(void);
i32* _errnop(void);
i32 mprotect(void* addr_length, size_t len, i32 prot);

#if !defined(PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP) || defined(CUSTOM_DEFINE_musl) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
#define pthread_rwlockattr_setkind_np(attr, kind) (0)
#endif
array __new_array(i64 len, i64 cap, i64 elem_size);
static inline array __v3_internal_symbol_array_new(i64 elem_size, i64 len, i64 cap) { if (len == 0 && cap == 0) return (array){.element_size = elem_size, .flags = ArrayFlags__managed}; return __new_array(len, cap, elem_size); }
#define array_new(elem_size, len, cap) __v3_internal_symbol_array_new((elem_size), (len), (cap))
#define array_push array__push
void array__push_many(array* a, void* val, i64 size);
#define array_push_many_ptr(a, val, size) array__push_many((a), (void*)(val), (size))
#define array_get array__get
#define array_set(a, i, ...) array__set(&(a), (i), __VA_ARGS__)
array array__clone(array* a);
#define array_slice array__slice
#define array_delete array__delete
#define array_ensure_cap array__ensure_cap
#define map__get_or_set map__get_and_set
#ifndef V_COMMIT_HASH
#define V_COMMIT_HASH ""
#endif
#ifndef memory_order_relaxed
#define memory_order_relaxed 0
#define memory_order_acquire 2
#define memory_order_release 3
#define memory_order_acq_rel 4
#define memory_order_seq_cst 5
#endif
#if defined(_WIN32) && (defined(__TINYC__) || (defined(_MSC_VER) && !defined(__clang__)))
/* V atomic.h supplies atomic_thread_fence on Windows TCC and MSVC. */
#elif defined(__TINYC__) && (defined(__i386__) || defined(__arm__) || defined(__aarch64__) || defined(__riscv) || (defined(__x86_64__) && defined(__linux__)))
extern void _V_atomic_thread_fence(int order);
#define atomic_thread_fence(order) _V_atomic_thread_fence(order)
#define __atomic_thread_fence(order) _V_atomic_thread_fence(order)
#else
#define atomic_thread_fence(order) __atomic_thread_fence(order)
#endif
__attribute__((weak)) void vheap_alloc(void* p, u64 n) { (void)p; (void)n; }
__attribute__((weak)) void vheap_free(void* p) { (void)p; }

#ifdef __TINYC__
extern byte __atomic_exchange_1(byte* ptr, byte val, int order);
extern u16 __atomic_exchange_2(u16* ptr, u16 val, int order);
extern u32 __atomic_exchange_4(u32* ptr, u32 val, int order);
extern u64 __atomic_exchange_8(u64* ptr, u64 val, int order);
extern byte __atomic_load_1(byte* ptr, int order);
extern u16 __atomic_load_2(u16* ptr, int order);
extern u32 __atomic_load_4(u32* ptr, int order);
extern u64 __atomic_load_8(u64* ptr, int order);
extern void __atomic_store_1(byte* ptr, byte val, int order);
extern void __atomic_store_2(u16* ptr, u16 val, int order);
extern void __atomic_store_4(u32* ptr, u32 val, int order);
extern void __atomic_store_8(u64* ptr, u64 val, int order);
extern _Bool __atomic_compare_exchange_1(byte* ptr, byte* expected, byte desired, int success_order, int failure_order);
extern _Bool __atomic_compare_exchange_2(u16* ptr, u16* expected, u16 desired, int success_order, int failure_order);
extern _Bool __atomic_compare_exchange_4(u32* ptr, u32* expected, u32 desired, int success_order, int failure_order);
extern _Bool __atomic_compare_exchange_8(u64* ptr, u64* expected, u64 desired, int success_order, int failure_order);
#endif
#if defined(_MSC_VER) && !defined(__clang__)






#else


#ifdef __TINYC__




#else




#endif
#endif










#ifdef __TINYC__




#if UINTPTR_MAX == 0xFFFFFFFF

#else

#endif








#if UINTPTR_MAX == 0xFFFFFFFF


#else


#endif




#if UINTPTR_MAX == 0xFFFFFFFF

#else

#endif




#else
























#endif

#ifdef __TINYC__

#else

#endif


static const u64 _wyp[4] = {0x2d358dccaa6c78a5ull, 0x8bb84b93962eacc9ull, 0x4b33a62ed433d4a3ull, 0x4d5a2da51de1aa47ull};
#if defined(__SIZEOF_INT128__) && !defined(__TINYC__)

#else

#endif

#define V_WY_LOAD8(p) ((u64)(p)[0] | ((u64)(p)[1] << 8) | ((u64)(p)[2] << 16) | ((u64)(p)[3] << 24) | ((u64)(p)[4] << 32) | ((u64)(p)[5] << 40) | ((u64)(p)[6] << 48) | ((u64)(p)[7] << 56))

#define v_signal_with_handler_cast(sig, handler) signal((sig), ((void (*)(int))(handler)))
string string__clone(string a);
void string__free(string* s);
string string__plus(string s, string a);
string int__str(i64 n);
string i64__str(i64 n);
string u64__str(u64 nn);
string f64__str(double x);
string rune__str(u32 c);
u8* malloc_noscan(ptrdiff_t n);
void* memdup(void* src, ptrdiff_t sz);

static int v3_array_sort_int_cmp(const void* a, const void* b) { i64 av = *(const i64*)a; i64 bv = *(const i64*)b; return (av > bv) - (av < bv); }

static int v3_array_sort_i8_cmp(const void* a, const void* b) { signed char av = *(const signed char*)a; signed char bv = *(const signed char*)b; return (av > bv) - (av < bv); }

static int v3_array_sort_i16_cmp(const void* a, const void* b) { short av = *(const short*)a; short bv = *(const short*)b; return (av > bv) - (av < bv); }

static int v3_array_sort_i64_cmp(const void* a, const void* b) { long long av = *(const long long*)a; long long bv = *(const long long*)b; return (av > bv) - (av < bv); }

static int v3_array_sort_u8_cmp(const void* a, const void* b) { unsigned char av = *(const unsigned char*)a; unsigned char bv = *(const unsigned char*)b; return (av > bv) - (av < bv); }

static int v3_array_sort_u16_cmp(const void* a, const void* b) { unsigned short av = *(const unsigned short*)a; unsigned short bv = *(const unsigned short*)b; return (av > bv) - (av < bv); }

static int v3_array_sort_u32_cmp(const void* a, const void* b) { unsigned av = *(const unsigned*)a; unsigned bv = *(const unsigned*)b; return (av > bv) - (av < bv); }

static int v3_array_sort_u64_cmp(const void* a, const void* b) { unsigned long long av = *(const unsigned long long*)a; unsigned long long bv = *(const unsigned long long*)b; return (av > bv) - (av < bv); }

static int v3_array_sort_isize_cmp(const void* a, const void* b) { ptrdiff_t av = *(const ptrdiff_t*)a; ptrdiff_t bv = *(const ptrdiff_t*)b; return (av > bv) - (av < bv); }

static int v3_array_sort_usize_cmp(const void* a, const void* b) { size_t av = *(const size_t*)a; size_t bv = *(const size_t*)b; return (av > bv) - (av < bv); }

static int v3_array_sort_rune_cmp(const void* a, const void* b) { unsigned av = *(const unsigned*)a; unsigned bv = *(const unsigned*)b; return (av > bv) - (av < bv); }

static int v3_array_sort_char_cmp(const void* a, const void* b) { char av = *(const char*)a; char bv = *(const char*)b; return (av > bv) - (av < bv); }

#ifndef V_MANUAL_STDLIB_HEADERS
#ifdef _WIN32
void* _aligned_malloc(size_t size, size_t alignment);
void _aligned_free(void* memblock);
#else
int posix_memalign(void** memptr, size_t alignment, size_t size);
#endif
#endif
void* memdup_align(void* src, ptrdiff_t sz, ptrdiff_t alignment);
void v_free(void* p);










































void* map__get(map* m, void* key, void* zero);
bool map__exists(map* m, void* key);






#ifndef max_int
#define max_int max_i32
#endif
#ifndef min_int
#define min_int min_i32
#endif

static FILE* v3_eprint_begin(void) {
	fflush(stdout);
	fflush(stderr);
	return stderr;
}
static void v3_eprint_end(void) {
	fflush(stderr);
}
#define v3_eprintf(...) do { fprintf(v3_eprint_begin(), __VA_ARGS__); v3_eprint_end(); } while (0)
static void v3_eprint_lit(const char* s) {
	v3_eprintf("%s", s);
}
static void v3_eprintln_string(string s) {
	v3_eprintf("%.*s\n", s.len, (char*)s.str);
}

i64 g_autostr_type_stack[64] = {0};
i64 g_autostr_type_stack_len = 0;
#if defined(__TINYC__) && defined(_WIN32)
typedef DWORD (WINAPI *g_autostr_addr_state_fls_alloc_fn)(void (WINAPI *)(void*));
typedef void* (WINAPI *g_autostr_addr_state_fls_get_fn)(DWORD);
typedef BOOL (WINAPI *g_autostr_addr_state_fls_set_fn)(DWORD, void*);
static DWORD g_autostr_addr_state_key = 0xFFFFFFFF;
static g_autostr_addr_state_fls_get_fn g_autostr_addr_state_fls_get;
static g_autostr_addr_state_fls_set_fn g_autostr_addr_state_fls_set;
static void WINAPI g_autostr_addr_state_slot_free(void* p) { free(p); }
static unsigned int g_autostr_addr_state_key_claim;
static unsigned int g_autostr_addr_state_key_ready;
#if defined(__x86_64__) || defined(__i386__)
#define g_autostr_addr_state_key_is_ready() (*(volatile unsigned int*)&g_autostr_addr_state_key_ready)
#else
#define g_autostr_addr_state_key_is_ready() __atomic_add_fetch(&g_autostr_addr_state_key_ready, 0, 5)
#endif
static void g_autostr_addr_state_key_init(void) {
	if (g_autostr_addr_state_key_is_ready()) { return; }
	if (__atomic_add_fetch(&g_autostr_addr_state_key_claim, 1, 5) == 1) {
		void* kernel32 = GetModuleHandleA("kernel32.dll");
		g_autostr_addr_state_fls_alloc_fn fls_alloc = (g_autostr_addr_state_fls_alloc_fn)GetProcAddress(kernel32, "FlsAlloc");
		g_autostr_addr_state_fls_get = (g_autostr_addr_state_fls_get_fn)GetProcAddress(kernel32, "FlsGetValue");
		g_autostr_addr_state_fls_set = (g_autostr_addr_state_fls_set_fn)GetProcAddress(kernel32, "FlsSetValue");
		g_autostr_addr_state_key = fls_alloc && g_autostr_addr_state_fls_get && g_autostr_addr_state_fls_set ? fls_alloc(g_autostr_addr_state_slot_free) : TlsAlloc();
		__atomic_add_fetch(&g_autostr_addr_state_key_ready, 1, 5);
	} else {
		while (!g_autostr_addr_state_key_is_ready()) { Sleep(0); }
	}
}
#undef g_autostr_addr_state_key_is_ready
static AutostrAddrStackState* g_autostr_addr_state_slot(void) { g_autostr_addr_state_key_init(); void* p = g_autostr_addr_state_fls_get ? g_autostr_addr_state_fls_get(g_autostr_addr_state_key) : TlsGetValue(g_autostr_addr_state_key); if (!p) { p = calloc(1, sizeof(AutostrAddrStackState)); if (g_autostr_addr_state_fls_set) g_autostr_addr_state_fls_set(g_autostr_addr_state_key, p); else TlsSetValue(g_autostr_addr_state_key, p); } return (AutostrAddrStackState*)p; }
#define g_autostr_addr_state (*g_autostr_addr_state_slot())
#elif defined(__TINYC__)
static pthread_key_t g_autostr_addr_state_key;
static pthread_once_t g_autostr_addr_state_key_once = PTHREAD_ONCE_INIT;
static void g_autostr_addr_state_key_create(void) { pthread_key_create(&g_autostr_addr_state_key, free); }
static void g_autostr_addr_state_key_init(void) { pthread_once(&g_autostr_addr_state_key_once, g_autostr_addr_state_key_create); }
static AutostrAddrStackState* g_autostr_addr_state_slot(void) { g_autostr_addr_state_key_init(); void* p = pthread_getspecific(g_autostr_addr_state_key); if (!p) { p = calloc(1, sizeof(AutostrAddrStackState)); pthread_setspecific(g_autostr_addr_state_key, p); } return (AutostrAddrStackState*)p; }
#define g_autostr_addr_state (*g_autostr_addr_state_slot())
#elif defined(_MSC_VER)
__declspec(thread) AutostrAddrStackState g_autostr_addr_state = {0};
#elif defined(__cplusplus)
thread_local AutostrAddrStackState g_autostr_addr_state = {0};
#else
_Thread_local AutostrAddrStackState g_autostr_addr_state = {0};
#endif
Array as_cast_type_indexes = {0};
VMapData map_empty_data = {0};
bool v_memory_panic = false;
i64 total_m = ((i64)(0));
i64 g_main_argc = ((i64)(0));
void* g_main_argv = NULL;
void* g_live_reload_info;
void* gc_boehm_default_abort_func;
VMemoryBlock* g_memory_block;
i64 g_prealloc_allocation_count;
i64 g_prealloc_allocated_bytes;
#if defined(__TINYC__) && defined(_WIN32)
typedef DWORD (WINAPI *g_panic_state_fls_alloc_fn)(void (WINAPI *)(void*));
typedef void* (WINAPI *g_panic_state_fls_get_fn)(DWORD);
typedef BOOL (WINAPI *g_panic_state_fls_set_fn)(DWORD, void*);
static DWORD g_panic_state_key = 0xFFFFFFFF;
static g_panic_state_fls_get_fn g_panic_state_fls_get;
static g_panic_state_fls_set_fn g_panic_state_fls_set;
static void WINAPI g_panic_state_slot_free(void* p) { free(p); }
static unsigned int g_panic_state_key_claim;
static unsigned int g_panic_state_key_ready;
#if defined(__x86_64__) || defined(__i386__)
#define g_panic_state_key_is_ready() (*(volatile unsigned int*)&g_panic_state_key_ready)
#else
#define g_panic_state_key_is_ready() __atomic_add_fetch(&g_panic_state_key_ready, 0, 5)
#endif
static void g_panic_state_key_init(void) {
	if (g_panic_state_key_is_ready()) { return; }
	if (__atomic_add_fetch(&g_panic_state_key_claim, 1, 5) == 1) {
		void* kernel32 = GetModuleHandleA("kernel32.dll");
		g_panic_state_fls_alloc_fn fls_alloc = (g_panic_state_fls_alloc_fn)GetProcAddress(kernel32, "FlsAlloc");
		g_panic_state_fls_get = (g_panic_state_fls_get_fn)GetProcAddress(kernel32, "FlsGetValue");
		g_panic_state_fls_set = (g_panic_state_fls_set_fn)GetProcAddress(kernel32, "FlsSetValue");
		g_panic_state_key = fls_alloc && g_panic_state_fls_get && g_panic_state_fls_set ? fls_alloc(g_panic_state_slot_free) : TlsAlloc();
		__atomic_add_fetch(&g_panic_state_key_ready, 1, 5);
	} else {
		while (!g_panic_state_key_is_ready()) { Sleep(0); }
	}
}
#undef g_panic_state_key_is_ready
static PanicState* g_panic_state_slot(void) { g_panic_state_key_init(); void* p = g_panic_state_fls_get ? g_panic_state_fls_get(g_panic_state_key) : TlsGetValue(g_panic_state_key); if (!p) { p = calloc(1, sizeof(PanicState)); if (g_panic_state_fls_set) g_panic_state_fls_set(g_panic_state_key, p); else TlsSetValue(g_panic_state_key, p); } return (PanicState*)p; }
#define g_panic_state (*g_panic_state_slot())
#elif defined(__TINYC__)
static pthread_key_t g_panic_state_key;
static pthread_once_t g_panic_state_key_once = PTHREAD_ONCE_INIT;
static void g_panic_state_key_create(void) { pthread_key_create(&g_panic_state_key, free); }
static void g_panic_state_key_init(void) { pthread_once(&g_panic_state_key_once, g_panic_state_key_create); }
static PanicState* g_panic_state_slot(void) { g_panic_state_key_init(); void* p = pthread_getspecific(g_panic_state_key); if (!p) { p = calloc(1, sizeof(PanicState)); pthread_setspecific(g_panic_state_key, p); } return (PanicState*)p; }
#define g_panic_state (*g_panic_state_slot())
#elif defined(_MSC_VER)
__declspec(thread) PanicState g_panic_state = {0};
#elif defined(__cplusplus)
thread_local PanicState g_panic_state = {0};
#else
_Thread_local PanicState g_panic_state = {0};
#endif
u8 os__g_v_os_execute_mutex_storage[128] = {0};
u64 os__g_main_thread_id;
closure__Closure closure__g_closure = {0};
pthread_mutex_t closure__g_closure_once_mutex = PTHREAD_MUTEX_INITIALIZER;
bool closure__g_closure_once_done = false;

void __v3_cache_bits__init_consts(void);
void __v3_cache_bits__init_consts_defaults(void);
void __v3_cache_builtin__init_consts(void);
void __v3_cache_builtin__init_consts_defaults(void);
void __v3_cache_closure__init_consts(void);
void __v3_cache_closure__init_consts_defaults(void);
void __v3_cache_fnv1a__init_consts(void);
void __v3_cache_fnv1a__init_consts_defaults(void);
void __v3_cache_hash__init_consts(void);
void __v3_cache_hash__init_consts_defaults(void);
void __v3_cache_os__init_consts(void);
void __v3_cache_os__init_consts_defaults(void);
void __v3_cache_strconv__init_consts(void);
void __v3_cache_strconv__init_consts_defaults(void);
void __v3_cache_strings__init_consts(void);
void __v3_cache_strings__init_consts_defaults(void);
void __v3_cache_termios__init_consts(void);
void __v3_cache_termios__init_consts_defaults(void);
void __v3_cache_textscanner__init_consts(void);
void __v3_cache_textscanner__init_consts_defaults(void);
/* V3CACHE_LATE_DIRECTIVES_BEGIN */
/* V3CACHE_LATE_DIRECTIVES_END */
string Array_rune__string(Array ra);
void Array_string__free(Array* a);
string Array_string__join(Array a, string sep);
string Array_string__join_lines(Array s);
void Array_string__sort_by_len(Array* s);
void Array_string__sort_ignore_case(Array* s);
string Array_string__str(Array a);
__v_result_u32 Array_u8__byterune(Array b);
string Array_u8__bytestr(Array b);
string Array_u8__hex(Array b);
__v_result_u32 Array_u8__utf8_to_utf32(Array _bytes);
i64 Error__code(Error err);
string Error__msg(Error err);
string IError__str(IError err);
i64 MessageError__code(MessageError err);
string MessageError__msg(MessageError err);
string StrIntpType_str(int x);
void* __as_cast(void* obj, i64 obj_type, i64 expected_type, string obj_name, string expected_name);
array __new_array(i64 mylen, i64 cap, i64 elm_size);
array __new_array_noscan(i64 mylen, i64 cap, i64 elm_size);
array array__clone(array* a);
void array__delete(array* a, i64 i);
void array__delete_last(array* a);
void array__ensure_cap(array* a, i64 required);
void array__free(array* a);
void* array__get(array a, i64 i);
void array__insert(array* a, i64 i, void* val);
void array__insert_many(array* a, i64 i, void* val, i64 size);
void* array__pop_left(array* a);
void array__prepend(array* a, void* val);
void array__push(array* a, void* val);
void array__push_many(array* a, void* val, i64 size);
array array__reverse(array a);
void array__set(array* a, i64 i, void* val);
array array__slice(array a, i64 start, i64 _end);
array array__slice_ni(array a, i64 _start, i64 _end);
void array__sort_with_compare(array* a, _fn_ptr_ed95774d3a4e97ab callback);
void array_sort_move(void* dst, i64 di, void* src, i64 si, i64 count, size_t element_size);
void autostr_addr_pop(void);
bool autostr_addr_type_in_stack(void* addr, i64 typ);
void autostr_addr_type_push(void* addr, i64 typ);
string bool__str(bool b);
void builtin_init(void);
Array byteptr__vbytes(u8* data, i64 len);
string byteptr__vstring(u8* bp);
string byteptr__vstring_with_len(u8* bp, i64 len);
string charptr__vstring(char* cp);
string charptr__vstring_with_len(char* cp, i64 len);
void* closure__closure_create_with_data(void* func, void* data, bool owns_data);
void closure__closure_init(void);
void closure__closure_try_destroy(void* closure);
i64 compare_lower_strings(string* a, string* b);
i64 compare_strings_by_len(string* a, string* b);
string data_to_hex_string(u8* data, i64 len);
void drop_owned_interface_T_IError(IError value);
void drop_owned_result_error(IError err);
void drop_owned_result_error_interface(IError err);
void drop_owned_v3_interface_T_IError(IError value);
void eprintln(string s);
IError error(string message);
IError error_with_code(string message, i64 code);
string f32__str(float x);
string f64__str(double x);
__v_result_Array find_dupes(Array dirs);
u64 fnv1a__Fnv1a64__finish(fnv1a__Fnv1a64* h);
__v_result fnv1a__Fnv1a64__write(fnv1a__Fnv1a64* h, Array p);
fnv1a__Fnv1a64* fnv1a__new_fnv1a64(void);
bool gc_prepare_for_debugger_init(void);
void gc_restore_roots_after_debugger_init(bool use_manual_roots);
void gc_runtime_init(void);
map group_by_size(Array files);
__v_result_string hash_file(string path);
string i16__str(i16 n);
string i32__str(i32 n);
string i64__str(i64 nn);
string i8__str(i8 n);
u32 impl_utf8_to_utf32(u8* _bytes, i64 _bytes_len);
string int__str(i64 n);
u8* malloc_noscan(ptrdiff_t n);
void map__clear(map* m);
map map__clone(map* m);
void map__delete(map* m, void* key);
bool map__exists(map* m, void* key);
void map__free(map* m);
void* map__get(map* m, void* key, void* zero);
void* map__get_and_set(map* m, void* key, void* zero);
void* map__get_check(map* m, void* key);
array map__keys(map* m);
void map__reserve(map* m, u32 n);
void map__set(map* m, void* key, void* value);
array map__values(map* m);
void map_clone_int_1(void* dest, void* pkey);
void map_clone_int_16(void* dest, void* pkey);
void map_clone_int_2(void* dest, void* pkey);
void map_clone_int_4(void* dest, void* pkey);
void map_clone_int_8(void* dest, void* pkey);
void map_clone_string(void* dest, void* pkey);
bool map_eq_int_1(void* a, void* b);
bool map_eq_int_16(void* a, void* b);
bool map_eq_int_2(void* a, void* b);
bool map_eq_int_4(void* a, void* b);
bool map_eq_int_8(void* a, void* b);
bool map_eq_string(void* a, void* b);
void map_free_nop(void* _0);
void map_free_string(void* pkey);
u64 map_hash_int_1(void* pkey);
u64 map_hash_int_16(void* pkey);
u64 map_hash_int_2(void* pkey);
u64 map_hash_int_4(void* pkey);
u64 map_hash_int_8(void* pkey);
u64 map_hash_string(void* pkey);
bool map_map_eq(map a, map b);
void* memdup(void* src, ptrdiff_t sz);
void* memdup_align(void* src, ptrdiff_t sz, ptrdiff_t align);
array new_array_from_c_array(i64 len, i64 cap, i64 elm_size, void* c_array);
array new_array_from_c_array_noscan(i64 len, i64 cap, i64 elm_size, void* c_array);
map new_map(i64 key_bytes, i64 value_bytes, _fn_ptr_1e8d64a3d95a0da1 hash_fn, _fn_ptr_c95f092653bee64 key_eq_fn, _fn_ptr_1a3da2026b1489ea clone_fn, _fn_ptr_5373f7edc7b60e26 free_fn);
string os__ExecutableNotFoundError__msg(os__ExecutableNotFoundError err);
string os__FileNotOpenedError__msg(os__FileNotOpenedError err);
void os__File__close(os__File* f);
__v_result_i64 os__File__read(os__File* f, Array* buf);
i64 os__NotExpected__code(os__NotExpected err);
string os__NotExpected__msg(os__NotExpected err);
string os__SizeOfTypeIs0Error__msg(os__SizeOfTypeIs0Error err);
string os__dir(string path);
u64 os__file_size(string path);
void os__init(void);
bool os__is_dir(string path);
bool os__is_file(string path);
bool os__is_link(string path);
string os__join_path(string base, Array dirs);
string os__join_path_single(string base, string elem);
__v_result_Array os__ls(string path);
__v_result_os__File os__open(string path);
__v_result os__walk_dir(string root, _fn_ptr_24927a217aab3552 cb);
void panic_debug(i64 line_no, string file, string mod, string fn_name, string s);
void panic_frame_done(void* frame);
void panic_frame_pop(void* frame);
void panic_frame_push(void* frame);
void panic_frame_relink(void* frame);
void panic_frames_reset(void);
__v_option_string panic_recover_frame(void* frame);
void print_groups(Array groups);
void println(string s);
string ptr_str(void* ptr);
Array rune__bytes(u32 c);
string rune__str(u32 c);
u32 rune__to_lower(u32 c);
string strconv__Dec32__get_string_32(strconv__Dec32 d, bool neg, i64 i_n_digit, i64 i_pad_digit);
string strconv__Dec64__get_string_64(strconv__Dec64 d, bool neg, i64 i_n_digit, i64 i_pad_digit);
string strconv__f32_to_str_l(float f);
string strconv__format_int(i64 n, i64 radix);
string strconv__format_uint(u64 n, i64 radix);
string string__all_after(string s, string sub);
string string__all_after_last(string s, string sub);
string string__all_before(string s, string sub);
string string__all_before_last(string s, string sub);
u8 string__at(string s, i64 idx);
u8 string__at_i64(string s, i64 idx);
u8 string__at_ni(string s, i64 idx);
u8 string__at_u64(string s, u64 idx);
string string__clone(string a);
bool string__eq(string s, string a);
void string__free(string* s);
bool string__is_capital(string s);
bool string__lt(string s, string a);
string string__plus(string s, string a);
string string__substr(string s, i64 start, i64 _end);
string string__substr_ni(string s, i64 _start, i64 _end);
string string__to_lower_ascii(string s);
string string_plus_many(i64 data_len, string* input_base);
void strings__Builder__free(Array* b);
string strings__Builder__str(Array* b);
void strings__Builder__write_ptr(Array* b, u8* ptr, i64 len);
void strings__Builder__write_runes(Array* b, Array runes);
void strings__Builder__write_string(Array* b, string s);
void strings__Builder__write_u8(Array* b, u8 data);
Array strings__new_builder(i64 initial_size);
string tos(u8* s, i64 len);
string u64__str(u64 nn);
bool u8__is_capital(u8 c);
bool u8__is_letter(u8 c);
string u8__vstring(u8* bp);
string u8__vstring_with_len(u8* bp, i64 len);
void v_exit(i64 code);
i64 v_fixed_index(i64 i, i64 len);
i64 v_fixed_index_i64(i64 i, i64 len);
i64 v_fixed_index_ni(i64 i, i64 len);
i64 v_fixed_index_u64(u64 i, i64 len);
void v_free(void* ptr);
u8* v_malloc(ptrdiff_t n);
void v_panic(string s);
i64 v_slice_index_i64(i64 i);
i64 v_slice_index_u64(u64 i);
void* vmemcpy(void* dest, void* const_src, ptrdiff_t n);
Array voidptr__vbytes(void* data, i64 len);
void walk_dir(string dir, Array* out);
Array walk_files(Array dirs);

i64 Error__code(Error err);
string Error__msg(Error err);
string IError__str(IError err);
i64 MessageError__code(MessageError err);
string MessageError__msg(MessageError err);
string StrIntpType_str(int x);
void* __as_cast(void* obj, i64 obj_type, i64 expected_type, string obj_name, string expected_name);
array __new_array(i64 mylen, i64 cap, i64 elm_size);
array __new_array_noscan(i64 mylen, i64 cap, i64 elm_size);
array array__clone(array* a);
void array__delete(array* a, i64 i);
void array__delete_last(array* a);
void array__ensure_cap(array* a, i64 required);
void array__free(array* a);
void* array__get(array a, i64 i);
void array__insert(array* a, i64 i, void* val);
void array__insert_many(array* a, i64 i, void* val, i64 size);
void* array__pop_left(array* a);
void array__prepend(array* a, void* val);
void array__push(array* a, void* val);
void array__push_many(array* a, void* val, i64 size);
array array__reverse(array a);
void array__set(array* a, i64 i, void* val);
array array__slice(array a, i64 start, i64 _end);
array array__slice_ni(array a, i64 _start, i64 _end);
void array__sort_with_compare(array* a, _fn_ptr_ed95774d3a4e97ab callback);
void array_sort_move(void* dst, i64 di, void* src, i64 si, i64 count, size_t element_size);
void autostr_addr_pop(void);
bool autostr_addr_type_in_stack(void* addr, i64 typ);
void autostr_addr_type_push(void* addr, i64 typ);
string bool__str(bool b);
void builtin_init(void);
Array byteptr__vbytes(u8* data, i64 len);
string byteptr__vstring(u8* bp);
string byteptr__vstring_with_len(u8* bp, i64 len);
string charptr__vstring(char* cp);
string charptr__vstring_with_len(char* cp, i64 len);
void* closure__closure_create_with_data(void* func, void* data, bool owns_data);
void closure__closure_init(void);
void closure__closure_try_destroy(void* closure);
i64 compare_lower_strings(string* a, string* b);
i64 compare_strings_by_len(string* a, string* b);
string data_to_hex_string(u8* data, i64 len);
void drop_owned_interface_T_IError(IError value);
void drop_owned_result_error(IError err);
void drop_owned_result_error_interface(IError err);
void drop_owned_v3_interface_T_IError(IError value);
void eprintln(string s);
IError error(string message);
IError error_with_code(string message, i64 code);
string f32__str(float x);
string f64__str(double x);
u64 fnv1a__Fnv1a64__finish(fnv1a__Fnv1a64* h);
__v_result fnv1a__Fnv1a64__write(fnv1a__Fnv1a64* h, Array p);
fnv1a__Fnv1a64* fnv1a__new_fnv1a64(void);
bool gc_prepare_for_debugger_init(void);
void gc_restore_roots_after_debugger_init(bool use_manual_roots);
void gc_runtime_init(void);
string i16__str(i16 n);
string i32__str(i32 n);
string i64__str(i64 nn);
string i8__str(i8 n);
u32 impl_utf8_to_utf32(u8* _bytes, i64 _bytes_len);
string int__str(i64 n);
u8* malloc_noscan(ptrdiff_t n);
void map__clear(map* m);
map map__clone(map* m);
void map__delete(map* m, void* key);
bool map__exists(map* m, void* key);
void map__free(map* m);
void* map__get(map* m, void* key, void* zero);
void* map__get_and_set(map* m, void* key, void* zero);
void* map__get_check(map* m, void* key);
array map__keys(map* m);
void map__reserve(map* m, u32 n);
void map__set(map* m, void* key, void* value);
array map__values(map* m);
void map_clone_int_1(void* dest, void* pkey);
void map_clone_int_16(void* dest, void* pkey);
void map_clone_int_2(void* dest, void* pkey);
void map_clone_int_4(void* dest, void* pkey);
void map_clone_int_8(void* dest, void* pkey);
void map_clone_string(void* dest, void* pkey);
bool map_eq_int_1(void* a, void* b);
bool map_eq_int_16(void* a, void* b);
bool map_eq_int_2(void* a, void* b);
bool map_eq_int_4(void* a, void* b);
bool map_eq_int_8(void* a, void* b);
bool map_eq_string(void* a, void* b);
void map_free_nop(void* _0);
void map_free_string(void* pkey);
u64 map_hash_int_1(void* pkey);
u64 map_hash_int_16(void* pkey);
u64 map_hash_int_2(void* pkey);
u64 map_hash_int_4(void* pkey);
u64 map_hash_int_8(void* pkey);
u64 map_hash_string(void* pkey);
bool map_map_eq(map a, map b);
void* memdup(void* src, ptrdiff_t sz);
void* memdup_align(void* src, ptrdiff_t sz, ptrdiff_t align);
array new_array_from_c_array(i64 len, i64 cap, i64 elm_size, void* c_array);
array new_array_from_c_array_noscan(i64 len, i64 cap, i64 elm_size, void* c_array);
map new_map(i64 key_bytes, i64 value_bytes, _fn_ptr_1e8d64a3d95a0da1 hash_fn, _fn_ptr_c95f092653bee64 key_eq_fn, _fn_ptr_1a3da2026b1489ea clone_fn, _fn_ptr_5373f7edc7b60e26 free_fn);
string os__ExecutableNotFoundError__msg(os__ExecutableNotFoundError err);
string os__FileNotOpenedError__msg(os__FileNotOpenedError err);
void os__File__close(os__File* f);
__v_result_i64 os__File__read(os__File* f, Array* buf);
i64 os__NotExpected__code(os__NotExpected err);
string os__NotExpected__msg(os__NotExpected err);
string os__SizeOfTypeIs0Error__msg(os__SizeOfTypeIs0Error err);
string os__dir(string path);
u64 os__file_size(string path);
void os__init(void);
bool os__is_dir(string path);
bool os__is_file(string path);
bool os__is_link(string path);
string os__join_path(string base, Array dirs);
string os__join_path_single(string base, string elem);
__v_result_Array os__ls(string path);
__v_result_os__File os__open(string path);
__v_result os__walk_dir(string root, _fn_ptr_24927a217aab3552 cb);
void panic_debug(i64 line_no, string file, string mod, string fn_name, string s);
void panic_frame_done(void* frame);
void panic_frame_pop(void* frame);
void panic_frame_push(void* frame);
void panic_frame_relink(void* frame);
void panic_frames_reset(void);
__v_option_string panic_recover_frame(void* frame);
void println(string s);
string ptr_str(void* ptr);
Array rune__bytes(u32 c);
string rune__str(u32 c);
u32 rune__to_lower(u32 c);
string strconv__Dec32__get_string_32(strconv__Dec32 d, bool neg, i64 i_n_digit, i64 i_pad_digit);
string strconv__Dec64__get_string_64(strconv__Dec64 d, bool neg, i64 i_n_digit, i64 i_pad_digit);
string strconv__f32_to_str_l(float f);
string strconv__format_int(i64 n, i64 radix);
string strconv__format_uint(u64 n, i64 radix);
string string__all_after(string s, string sub);
string string__all_after_last(string s, string sub);
string string__all_before(string s, string sub);
string string__all_before_last(string s, string sub);
u8 string__at(string s, i64 idx);
u8 string__at_i64(string s, i64 idx);
u8 string__at_ni(string s, i64 idx);
u8 string__at_u64(string s, u64 idx);
string string__clone(string a);
bool string__eq(string s, string a);
void string__free(string* s);
bool string__is_capital(string s);
bool string__lt(string s, string a);
string string__plus(string s, string a);
string string__substr(string s, i64 start, i64 _end);
string string__substr_ni(string s, i64 _start, i64 _end);
string string__to_lower_ascii(string s);
string string_plus_many(i64 data_len, string* input_base);
void strings__Builder__free(Array* b);
string strings__Builder__str(Array* b);
void strings__Builder__write_ptr(Array* b, u8* ptr, i64 len);
void strings__Builder__write_runes(Array* b, Array runes);
void strings__Builder__write_string(Array* b, string s);
void strings__Builder__write_u8(Array* b, u8 data);
Array strings__new_builder(i64 initial_size);
string tos(u8* s, i64 len);
string u64__str(u64 nn);
bool u8__is_capital(u8 c);
bool u8__is_letter(u8 c);
string u8__vstring(u8* bp);
string u8__vstring_with_len(u8* bp, i64 len);
void v_exit(i64 code);
i64 v_fixed_index(i64 i, i64 len);
i64 v_fixed_index_i64(i64 i, i64 len);
i64 v_fixed_index_ni(i64 i, i64 len);
i64 v_fixed_index_u64(u64 i, i64 len);
void v_free(void* ptr);
u8* v_malloc(ptrdiff_t n);
void v_panic(string s);
i64 v_slice_index_i64(i64 i);
i64 v_slice_index_u64(u64 i);
void* vmemcpy(void* dest, void* const_src, ptrdiff_t n);
Array voidptr__vbytes(void* data, i64 len);

string IError__msg(IError* i);
string Error__msg(Error _recv);
string MessageError__msg(MessageError _recv);
string os__ExecutableNotFoundError__msg(os__ExecutableNotFoundError _recv);
string os__FileNotOpenedError__msg(os__FileNotOpenedError _recv);
string os__NotExpected__msg(os__NotExpected _recv);
string os__SizeOfTypeIs0Error__msg(os__SizeOfTypeIs0Error _recv);
i64 IError__code(IError* i);
i64 Error__code(Error _recv);
i64 MessageError__code(MessageError _recv);
i64 os__NotExpected__code(os__NotExpected _recv);
Array hash__Hash__sum(hash__Hash* i, Array _a0);
i64 hash__Hash__size(hash__Hash* i);
i64 hash__Hash__block_size(hash__Hash* i);
void hash__Hash__free(hash__Hash* i);
void hash__Hash__reset(hash__Hash* i);
__v_result_i64 hash__Hash__write(hash__Hash* i, Array _a0);
u32 hash__Hash32er__sum32(hash__Hash32er* i);
u64 hash__Hash64er__sum64(hash__Hash64er* i);
__v_result hash__Hasher__write(hash__Hasher* i, Array _a0);
u64 hash__Hasher__finish(hash__Hasher* i);

string ArrayFlags__autostr(ArrayFlags it);
string ChanState__autostr(ChanState it);
string GraphemeBreakProperty__autostr(GraphemeBreakProperty it);
string AttributeKind__autostr(AttributeKind it);
string MapMode__autostr(MapMode it);
string TrimMode__autostr(TrimMode it);
string strings__IndentState__autostr(strings__IndentState it);
string strconv__Align_text__autostr(strconv__Align_text it);
string strconv__ParserState__autostr(strconv__ParserState it);
string strconv__Char_parse_state__autostr(strconv__Char_parse_state it);
string os__MmapMode__autostr(os__MmapMode it);
string os__WalkDirAction__autostr(os__WalkDirAction it);
string os__ProcessState__autostr(os__ProcessState it);
string os__Signal__autostr(os__Signal it);
string os__SeekMode__autostr(os__SeekMode it);
string os__FileBufferMode__autostr(os__FileBufferMode it);
string os__FileType__autostr(os__FileType it);
string os__GlobMatch__autostr(os__GlobMatch it);
string os__ChildProcessPipeKind__autostr(os__ChildProcessPipeKind it);
string closure__MemoryProtectAtrr__autostr(closure__MemoryProtectAtrr it);

static const string _v3_lit_0_14650fb0739d0383 = {"", 0, 1};
static const string _v3_lit_1_44bd31d473cd01cb = {"\n", 1, 1};

static const string _v3_lit_4_1b0d87aaaffd5273 = {"    ", 4, 1};
static const string _v3_lit_8_86a8111759a98db0 = {" bytes  ", 8, 1};
static const string _v3_lit_18_a9c26cb051ae2e6c = {" bytes recoverable", 18, 1};
static const string _v3_lit_11_b9c2da042e7ff834 = {" group(s), ", 11, 1};
static const string _v3_lit_2_9afebb00c5c7fa67 = {", ", 2, 1};
























static const string _v3_lit_74_82fc39ccb1421152 = {"attempted to decode too many bytes, utf-8 is limited to four bytes maximum", 74, 1};
static const string _v3_lit_9_97d87a1106c21fc9 = {"dupfind: ", 9, 1};
static const string _v3_lit_44_7e766e4cc095bb70 = {"interface method IError.code not implemented", 44, 1};
static const string _v3_lit_43_9edf8799b50a549c = {"interface method IError.msg not implemented", 43, 1};
static const string _v3_lit_54_503bb76740bf2bb9 = {"interface method hash__Hash.block_size not implemented", 54, 1};
static const string _v3_lit_48_fb91f183b903b558 = {"interface method hash__Hash.free not implemented", 48, 1};
static const string _v3_lit_49_eb073e2877ead767 = {"interface method hash__Hash.reset not implemented", 49, 1};
static const string _v3_lit_48_e55a586fc0c6b73f = {"interface method hash__Hash.size not implemented", 48, 1};
static const string _v3_lit_47_67a5effad7253ea3 = {"interface method hash__Hash.sum not implemented", 47, 1};
static const string _v3_lit_49_2678ade7cd32896b = {"interface method hash__Hash.write not implemented", 49, 1};
static const string _v3_lit_53_95bddd17dfe45e44 = {"interface method hash__Hash32er.sum32 not implemented", 53, 1};
static const string _v3_lit_53_5f2d8f78123176b0 = {"interface method hash__Hash64er.sum64 not implemented", 53, 1};
static const string _v3_lit_52_81b5cee77879d238 = {"interface method hash__Hasher.finish not implemented", 52, 1};
static const string _v3_lit_51_dc22f65c21aeb98 = {"interface method hash__Hasher.write not implemented", 51, 1};
static const string _v3_lit_19_72be4e8eaa4a0d66 = {"no duplicates found", 19, 1};
static const string _v3_lit_29_290cde771a7bd19e = {"usage: dupfind <dir> [dir...]", 29, 1};

string ArrayFlags__autostr(ArrayFlags it) {
	int __fe_v = (int)it;
	string __fe_res = (string){.str = (u8*)"ArrayFlags{", .len = 11, .is_lit = 1};
	bool __fe_first = true;
	if (ArrayFlags__noslices != 0 && (__fe_v & (int)ArrayFlags__noslices) == (int)ArrayFlags__noslices) {
		if (!__fe_first) { __fe_res = string__plus(__fe_res, (string){.str = (u8*)" | ", .len = 3, .is_lit = 1}); }
		__fe_res = string__plus(__fe_res, (string){.str = (u8*)".noslices", .len = 9, .is_lit = 1});
		__fe_first = false;
	}
	if (ArrayFlags__noshrink != 0 && (__fe_v & (int)ArrayFlags__noshrink) == (int)ArrayFlags__noshrink) {
		if (!__fe_first) { __fe_res = string__plus(__fe_res, (string){.str = (u8*)" | ", .len = 3, .is_lit = 1}); }
		__fe_res = string__plus(__fe_res, (string){.str = (u8*)".noshrink", .len = 9, .is_lit = 1});
		__fe_first = false;
	}
	if (ArrayFlags__nogrow != 0 && (__fe_v & (int)ArrayFlags__nogrow) == (int)ArrayFlags__nogrow) {
		if (!__fe_first) { __fe_res = string__plus(__fe_res, (string){.str = (u8*)" | ", .len = 3, .is_lit = 1}); }
		__fe_res = string__plus(__fe_res, (string){.str = (u8*)".nogrow", .len = 7, .is_lit = 1});
		__fe_first = false;
	}
	if (ArrayFlags__nofree != 0 && (__fe_v & (int)ArrayFlags__nofree) == (int)ArrayFlags__nofree) {
		if (!__fe_first) { __fe_res = string__plus(__fe_res, (string){.str = (u8*)" | ", .len = 3, .is_lit = 1}); }
		__fe_res = string__plus(__fe_res, (string){.str = (u8*)".nofree", .len = 7, .is_lit = 1});
		__fe_first = false;
	}
	if (ArrayFlags__managed != 0 && (__fe_v & (int)ArrayFlags__managed) == (int)ArrayFlags__managed) {
		if (!__fe_first) { __fe_res = string__plus(__fe_res, (string){.str = (u8*)" | ", .len = 3, .is_lit = 1}); }
		__fe_res = string__plus(__fe_res, (string){.str = (u8*)".managed", .len = 8, .is_lit = 1});
		__fe_first = false;
	}
	if (ArrayFlags__noscan_data != 0 && (__fe_v & (int)ArrayFlags__noscan_data) == (int)ArrayFlags__noscan_data) {
		if (!__fe_first) { __fe_res = string__plus(__fe_res, (string){.str = (u8*)" | ", .len = 3, .is_lit = 1}); }
		__fe_res = string__plus(__fe_res, (string){.str = (u8*)".noscan_data", .len = 12, .is_lit = 1});
		__fe_first = false;
	}
	if (ArrayFlags__is_slice != 0 && (__fe_v & (int)ArrayFlags__is_slice) == (int)ArrayFlags__is_slice) {
		if (!__fe_first) { __fe_res = string__plus(__fe_res, (string){.str = (u8*)" | ", .len = 3, .is_lit = 1}); }
		__fe_res = string__plus(__fe_res, (string){.str = (u8*)".is_slice", .len = 9, .is_lit = 1});
		__fe_first = false;
	}
	__fe_res = string__plus(__fe_res, (string){.str = (u8*)"}", .len = 1, .is_lit = 1});
	return __fe_res;
}

string ChanState__autostr(ChanState it) {
	if (it == ChanState__success) return (string){.str = (u8*)"success", .len = 7, .is_lit = 1};
	if (it == ChanState__not_ready) return (string){.str = (u8*)"not_ready", .len = 9, .is_lit = 1};
	if (it == ChanState__closed) return (string){.str = (u8*)"closed", .len = 6, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string GraphemeBreakProperty__autostr(GraphemeBreakProperty it) {
	if (it == GraphemeBreakProperty__other) return (string){.str = (u8*)"other", .len = 5, .is_lit = 1};
	if (it == GraphemeBreakProperty__cr) return (string){.str = (u8*)"cr", .len = 2, .is_lit = 1};
	if (it == GraphemeBreakProperty__lf) return (string){.str = (u8*)"lf", .len = 2, .is_lit = 1};
	if (it == GraphemeBreakProperty__control) return (string){.str = (u8*)"control", .len = 7, .is_lit = 1};
	if (it == GraphemeBreakProperty__extend) return (string){.str = (u8*)"extend", .len = 6, .is_lit = 1};
	if (it == GraphemeBreakProperty__regional_indicator) return (string){.str = (u8*)"regional_indicator", .len = 18, .is_lit = 1};
	if (it == GraphemeBreakProperty__prepend) return (string){.str = (u8*)"prepend", .len = 7, .is_lit = 1};
	if (it == GraphemeBreakProperty__spacing_mark) return (string){.str = (u8*)"spacing_mark", .len = 12, .is_lit = 1};
	if (it == GraphemeBreakProperty__l) return (string){.str = (u8*)"l", .len = 1, .is_lit = 1};
	if (it == GraphemeBreakProperty__v) return (string){.str = (u8*)"v", .len = 1, .is_lit = 1};
	if (it == GraphemeBreakProperty__t) return (string){.str = (u8*)"t", .len = 1, .is_lit = 1};
	if (it == GraphemeBreakProperty__lv) return (string){.str = (u8*)"lv", .len = 2, .is_lit = 1};
	if (it == GraphemeBreakProperty__lvt) return (string){.str = (u8*)"lvt", .len = 3, .is_lit = 1};
	if (it == GraphemeBreakProperty__zwj) return (string){.str = (u8*)"zwj", .len = 3, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string AttributeKind__autostr(AttributeKind it) {
	if (it == AttributeKind__plain) return (string){.str = (u8*)"plain", .len = 5, .is_lit = 1};
	if (it == AttributeKind__string) return (string){.str = (u8*)"string", .len = 6, .is_lit = 1};
	if (it == AttributeKind__number) return (string){.str = (u8*)"number", .len = 6, .is_lit = 1};
	if (it == AttributeKind__bool) return (string){.str = (u8*)"bool", .len = 4, .is_lit = 1};
	if (it == AttributeKind__comptime_define) return (string){.str = (u8*)"comptime_define", .len = 15, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string MapMode__autostr(MapMode it) {
	if (it == MapMode__to_upper) return (string){.str = (u8*)"to_upper", .len = 8, .is_lit = 1};
	if (it == MapMode__to_lower) return (string){.str = (u8*)"to_lower", .len = 8, .is_lit = 1};
	if (it == MapMode__to_title) return (string){.str = (u8*)"to_title", .len = 8, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string TrimMode__autostr(TrimMode it) {
	if (it == TrimMode__trim_left) return (string){.str = (u8*)"trim_left", .len = 9, .is_lit = 1};
	if (it == TrimMode__trim_right) return (string){.str = (u8*)"trim_right", .len = 10, .is_lit = 1};
	if (it == TrimMode__trim_both) return (string){.str = (u8*)"trim_both", .len = 9, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string strings__IndentState__autostr(strings__IndentState it) {
	if (it == strings__IndentState__normal) return (string){.str = (u8*)"normal", .len = 6, .is_lit = 1};
	if (it == strings__IndentState__in_string) return (string){.str = (u8*)"in_string", .len = 9, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string strconv__Align_text__autostr(strconv__Align_text it) {
	if (it == strconv__Align_text__right) return (string){.str = (u8*)"right", .len = 5, .is_lit = 1};
	if (it == strconv__Align_text__left) return (string){.str = (u8*)"left", .len = 4, .is_lit = 1};
	if (it == strconv__Align_text__center) return (string){.str = (u8*)"center", .len = 6, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string strconv__ParserState__autostr(strconv__ParserState it) {
	if (it == strconv__ParserState__ok) return (string){.str = (u8*)"ok", .len = 2, .is_lit = 1};
	if (it == strconv__ParserState__pzero) return (string){.str = (u8*)"pzero", .len = 5, .is_lit = 1};
	if (it == strconv__ParserState__mzero) return (string){.str = (u8*)"mzero", .len = 5, .is_lit = 1};
	if (it == strconv__ParserState__pinf) return (string){.str = (u8*)"pinf", .len = 4, .is_lit = 1};
	if (it == strconv__ParserState__minf) return (string){.str = (u8*)"minf", .len = 4, .is_lit = 1};
	if (it == strconv__ParserState__invalid_number) return (string){.str = (u8*)"invalid_number", .len = 14, .is_lit = 1};
	if (it == strconv__ParserState__extra_char) return (string){.str = (u8*)"extra_char", .len = 10, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string strconv__Char_parse_state__autostr(strconv__Char_parse_state it) {
	if (it == strconv__Char_parse_state__start) return (string){.str = (u8*)"start", .len = 5, .is_lit = 1};
	if (it == strconv__Char_parse_state__norm_char) return (string){.str = (u8*)"norm_char", .len = 9, .is_lit = 1};
	if (it == strconv__Char_parse_state__field_char) return (string){.str = (u8*)"field_char", .len = 10, .is_lit = 1};
	if (it == strconv__Char_parse_state__pad_ch) return (string){.str = (u8*)"pad_ch", .len = 6, .is_lit = 1};
	if (it == strconv__Char_parse_state__len_set_start) return (string){.str = (u8*)"len_set_start", .len = 13, .is_lit = 1};
	if (it == strconv__Char_parse_state__len_set_in) return (string){.str = (u8*)"len_set_in", .len = 10, .is_lit = 1};
	if (it == strconv__Char_parse_state__check_type) return (string){.str = (u8*)"check_type", .len = 10, .is_lit = 1};
	if (it == strconv__Char_parse_state__check_float) return (string){.str = (u8*)"check_float", .len = 11, .is_lit = 1};
	if (it == strconv__Char_parse_state__check_float_in) return (string){.str = (u8*)"check_float_in", .len = 14, .is_lit = 1};
	if (it == strconv__Char_parse_state__reset_params) return (string){.str = (u8*)"reset_params", .len = 12, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string os__MmapMode__autostr(os__MmapMode it) {
	if (it == os__MmapMode__read_only) return (string){.str = (u8*)"read_only", .len = 9, .is_lit = 1};
	if (it == os__MmapMode__read_write) return (string){.str = (u8*)"read_write", .len = 10, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string os__WalkDirAction__autostr(os__WalkDirAction it) {
	if (it == os__WalkDirAction__proceed) return (string){.str = (u8*)"proceed", .len = 7, .is_lit = 1};
	if (it == os__WalkDirAction__skip_dir) return (string){.str = (u8*)"skip_dir", .len = 8, .is_lit = 1};
	if (it == os__WalkDirAction__stop) return (string){.str = (u8*)"stop", .len = 4, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string os__ProcessState__autostr(os__ProcessState it) {
	if (it == os__ProcessState__not_started) return (string){.str = (u8*)"not_started", .len = 11, .is_lit = 1};
	if (it == os__ProcessState__running) return (string){.str = (u8*)"running", .len = 7, .is_lit = 1};
	if (it == os__ProcessState__stopped) return (string){.str = (u8*)"stopped", .len = 7, .is_lit = 1};
	if (it == os__ProcessState__exited) return (string){.str = (u8*)"exited", .len = 6, .is_lit = 1};
	if (it == os__ProcessState__aborted) return (string){.str = (u8*)"aborted", .len = 7, .is_lit = 1};
	if (it == os__ProcessState__closed) return (string){.str = (u8*)"closed", .len = 6, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string os__Signal__autostr(os__Signal it) {
	if (it == os__Signal__hup) return (string){.str = (u8*)"hup", .len = 3, .is_lit = 1};
	if (it == os__Signal__v_int) return (string){.str = (u8*)"int", .len = 3, .is_lit = 1};
	if (it == os__Signal__quit) return (string){.str = (u8*)"quit", .len = 4, .is_lit = 1};
	if (it == os__Signal__ill) return (string){.str = (u8*)"ill", .len = 3, .is_lit = 1};
	if (it == os__Signal__trap) return (string){.str = (u8*)"trap", .len = 4, .is_lit = 1};
	if (it == os__Signal__abrt) return (string){.str = (u8*)"abrt", .len = 4, .is_lit = 1};
	if (it == os__Signal__bus) return (string){.str = (u8*)"bus", .len = 3, .is_lit = 1};
	if (it == os__Signal__fpe) return (string){.str = (u8*)"fpe", .len = 3, .is_lit = 1};
	if (it == os__Signal__kill) return (string){.str = (u8*)"kill", .len = 4, .is_lit = 1};
	if (it == os__Signal__usr1) return (string){.str = (u8*)"usr1", .len = 4, .is_lit = 1};
	if (it == os__Signal__segv) return (string){.str = (u8*)"segv", .len = 4, .is_lit = 1};
	if (it == os__Signal__usr2) return (string){.str = (u8*)"usr2", .len = 4, .is_lit = 1};
	if (it == os__Signal__v_pipe) return (string){.str = (u8*)"pipe", .len = 4, .is_lit = 1};
	if (it == os__Signal__alrm) return (string){.str = (u8*)"alrm", .len = 4, .is_lit = 1};
	if (it == os__Signal__term) return (string){.str = (u8*)"term", .len = 4, .is_lit = 1};
	if (it == os__Signal__stkflt) return (string){.str = (u8*)"stkflt", .len = 6, .is_lit = 1};
	if (it == os__Signal__chld) return (string){.str = (u8*)"chld", .len = 4, .is_lit = 1};
	if (it == os__Signal__cont) return (string){.str = (u8*)"cont", .len = 4, .is_lit = 1};
	if (it == os__Signal__stop) return (string){.str = (u8*)"stop", .len = 4, .is_lit = 1};
	if (it == os__Signal__tstp) return (string){.str = (u8*)"tstp", .len = 4, .is_lit = 1};
	if (it == os__Signal__ttin) return (string){.str = (u8*)"ttin", .len = 4, .is_lit = 1};
	if (it == os__Signal__ttou) return (string){.str = (u8*)"ttou", .len = 4, .is_lit = 1};
	if (it == os__Signal__urg) return (string){.str = (u8*)"urg", .len = 3, .is_lit = 1};
	if (it == os__Signal__xcpu) return (string){.str = (u8*)"xcpu", .len = 4, .is_lit = 1};
	if (it == os__Signal__xfsz) return (string){.str = (u8*)"xfsz", .len = 4, .is_lit = 1};
	if (it == os__Signal__vtalrm) return (string){.str = (u8*)"vtalrm", .len = 6, .is_lit = 1};
	if (it == os__Signal__prof) return (string){.str = (u8*)"prof", .len = 4, .is_lit = 1};
	if (it == os__Signal__winch) return (string){.str = (u8*)"winch", .len = 5, .is_lit = 1};
	if (it == os__Signal__poll) return (string){.str = (u8*)"poll", .len = 4, .is_lit = 1};
	if (it == os__Signal__pwr) return (string){.str = (u8*)"pwr", .len = 3, .is_lit = 1};
	if (it == os__Signal__sys) return (string){.str = (u8*)"sys", .len = 3, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string os__SeekMode__autostr(os__SeekMode it) {
	if (it == os__SeekMode__start) return (string){.str = (u8*)"start", .len = 5, .is_lit = 1};
	if (it == os__SeekMode__current) return (string){.str = (u8*)"current", .len = 7, .is_lit = 1};
	if (it == os__SeekMode__end) return (string){.str = (u8*)"end", .len = 3, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string os__FileBufferMode__autostr(os__FileBufferMode it) {
	if (it == os__FileBufferMode__fully_buffered) return (string){.str = (u8*)"fully_buffered", .len = 14, .is_lit = 1};
	if (it == os__FileBufferMode__line_buffered) return (string){.str = (u8*)"line_buffered", .len = 13, .is_lit = 1};
	if (it == os__FileBufferMode__not_buffered) return (string){.str = (u8*)"not_buffered", .len = 12, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string os__FileType__autostr(os__FileType it) {
	if (it == os__FileType__unknown) return (string){.str = (u8*)"unknown", .len = 7, .is_lit = 1};
	if (it == os__FileType__regular) return (string){.str = (u8*)"regular", .len = 7, .is_lit = 1};
	if (it == os__FileType__directory) return (string){.str = (u8*)"directory", .len = 9, .is_lit = 1};
	if (it == os__FileType__character_device) return (string){.str = (u8*)"character_device", .len = 16, .is_lit = 1};
	if (it == os__FileType__block_device) return (string){.str = (u8*)"block_device", .len = 12, .is_lit = 1};
	if (it == os__FileType__fifo) return (string){.str = (u8*)"fifo", .len = 4, .is_lit = 1};
	if (it == os__FileType__symbolic_link) return (string){.str = (u8*)"symbolic_link", .len = 13, .is_lit = 1};
	if (it == os__FileType__socket) return (string){.str = (u8*)"socket", .len = 6, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string os__GlobMatch__autostr(os__GlobMatch it) {
	if (it == os__GlobMatch__exact) return (string){.str = (u8*)"exact", .len = 5, .is_lit = 1};
	if (it == os__GlobMatch__ends_with) return (string){.str = (u8*)"ends_with", .len = 9, .is_lit = 1};
	if (it == os__GlobMatch__starts_with) return (string){.str = (u8*)"starts_with", .len = 11, .is_lit = 1};
	if (it == os__GlobMatch__start_and_ends_with) return (string){.str = (u8*)"start_and_ends_with", .len = 19, .is_lit = 1};
	if (it == os__GlobMatch__contains) return (string){.str = (u8*)"contains", .len = 8, .is_lit = 1};
	if (it == os__GlobMatch__any) return (string){.str = (u8*)"any", .len = 3, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string os__ChildProcessPipeKind__autostr(os__ChildProcessPipeKind it) {
	if (it == os__ChildProcessPipeKind__v_stdin) return (string){.str = (u8*)"stdin", .len = 5, .is_lit = 1};
	if (it == os__ChildProcessPipeKind__v_stdout) return (string){.str = (u8*)"stdout", .len = 6, .is_lit = 1};
	if (it == os__ChildProcessPipeKind__v_stderr) return (string){.str = (u8*)"stderr", .len = 6, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

string closure__MemoryProtectAtrr__autostr(closure__MemoryProtectAtrr it) {
	if (it == closure__MemoryProtectAtrr__read_exec) return (string){.str = (u8*)"read_exec", .len = 9, .is_lit = 1};
	if (it == closure__MemoryProtectAtrr__read_write) return (string){.str = (u8*)"read_write", .len = 10, .is_lit = 1};
	return strconv__format_int((i64)it, 10);
}

extern IError builtin__none__;
extern Array os__args;
#define bits__de_bruijn32 (((u32)(0x077CB531)))
#define bits__de_bruijn64 (((u64)(0x03f79d71b4ca8b09)))
#define bits__m0 (((u64)(0x5555555555555555)))
#define bits__m1 (((u64)(0x3333333333333333)))
#define bits__m2 (((u64)(0x0f0f0f0f0f0f0f0f)))
#define bits__m3 (((u64)(0x00ff00ff00ff00ff)))
#define bits__m4 (((u64)(0x0000ffff0000ffff)))
#define bits__n16 (((u16)(16)))
#define bits__n32 (((u32)(32)))
#define bits__n64 (((u64)(64)))
#define bits__two32 (((u64)(0x100000000)))
#define bits__mask32 ((((u64)(0x100000000))) - (1))
#define strconv__int_size ((((i64)(sizeof(i64)))) * (8))
#define strconv__i64_min_int32 ((((i64)(-(2147483647)))) - (1))
#define strconv__i64_max_int32 ((((i64)(2147483646))) + (1))
#define strconv__mantbits64 (((u32)(52)))
#define strconv__expbits64 (((u32)(11)))
#define strconv__bias64 (1023)
#define strconv__maxexp64 (((u64)(2047)))
#define strconv__rune_error (0xFFFD)
#define strconv__max_rune (0x10FFFF)
#define strconv__pow5_num_bits_32 (61)
#define strconv__pow5_inv_num_bits_32 (59)
#define strconv__pow5_num_bits_64 (121)
#define strconv__pow5_inv_num_bits_64 (122)
#define strconv__single_plus_zero (((u32)(0x00000000)))
#define strconv__single_minus_zero (((u32)(0x80000000)))
#define strconv__single_plus_infinity (((u32)(0x7F800000)))
#define strconv__single_minus_infinity (((u32)(0xFF800000)))
#define strconv__digits (18)
#define strconv__double_plus_zero (((u64)(0x0000000000000000)))
#define strconv__double_minus_zero (((u64)(0x8000000000000000)))
#define strconv__double_plus_infinity (((u64)(0x7FF0000000000000)))
#define strconv__double_minus_infinity (((u64)(0xFFF0000000000000)))
#define strconv__c_dpoint ('.')
#define strconv__c_plus ('+')
#define strconv__c_minus ('-')
#define strconv__c_zero ('0')
#define strconv__c_nine ('9')
#define strconv__c_ten (((u32)(10)))
#define strconv__mantbits32 (((u32)(23)))
#define strconv__expbits32 (((u32)(8)))
#define strconv__bias32 (127)
#define strconv__maxexp32 (255)
#define strconv__max_size_f64_char (512)
#define hash__wyp0 (((u64)(0x2d358dccaa6c78a5)))
#define hash__wyp1 (((u64)(0x8bb84b93962eacc9)))
#define hash__wyp2 (((u64)(0x4b33a62ed433d4a3)))
#define hash__wyp3 (((u64)(0x4d5a2da51de1aa47)))
#define builtin__array_flag_retained_aligned_fixed (((int)((((u32)(1))) << (31))))
#define builtin__autostr_type_stack_max_depth (64)
#define builtin__min_i8 (((i8)(-(128))))
#define builtin__max_i8 (((i8)(127)))
#define builtin__min_i16 (((i16)(-(32768))))
#define builtin__max_i16 (((i16)(32767)))
#define builtin__min_i32 (((i32)(-2147483648LL)))
#define builtin__max_i32 (((i32)(2147483647)))
#define builtin__min_i64 (((i64)((-9223372036854775807LL) - (1))))
#define builtin__max_i64 (((i64)(9223372036854775807)))
#define builtin__min_int (((i64)(((i64)((-9223372036854775807LL) - (1))))))
#define builtin__max_int (((i64)(((i64)(9223372036854775807)))))
#define builtin__min_u16 (((u16)(0)))
#define builtin__max_u16 (((u16)(65535)))
#define builtin__min_u32 (((u32)(0)))
#define builtin__max_u32 (((u32)(4294967295)))
#define builtin__min_u64 (((u64)(0)))
#define builtin__max_u64 (((u64)(18446744073709551615)))
#define builtin__hashbits (24)
#define builtin__max_cached_hashbits (16)
#define builtin__init_log_capicity (5)
#define builtin__init_capicity ((1) << (5))
#define builtin__max_load_factor (0.8)
#define builtin__init_even_index (((1) << (5)) - (2))
#define builtin__extra_metas_inc (4)
#define builtin__hash_mask (((u32)(0x00FFFFFF)))
#define builtin__probe_inc (((u32)(0x01000000)))
#define builtin__rune_maps_columns_in_row (4)
#define builtin__rune_maps_ul (-(3))
#define builtin__rune_maps_utl (-(2))
#define builtin__degree (6)
#define builtin__mid_index ((6) - (1))
#define builtin__max_len (((2) * (6)) - (1))
#define builtin__children_bytes ((sizeof(void*)) * (((((2) * (6)) - (1)) + (1))))
#define builtin__replace_stack_buffer_size (10)
#define builtin__max_direct_index_needle_len (16)
#define builtin__kmp_stack_buffer_size (20)
#define builtin__utf8_replacement_rune (((u32)(0xfffd)))
#define builtin__map_hash_k0 (((u64)(0x2d358dccaa6c78a5)))
#define builtin__map_hash_k1 (((u64)(0x8bb84b93962eacc9)))
#define builtin__map_hash_k2 (((u64)(0x4b33a62ed433d4a3)))
#define builtin__map_hash_k3 (((u64)(0x4d5a2da51de1aa47)))
#define builtin__prealloc_block_size (((16) * (1024)) * (1024))
#define builtin__prealloc_scope_block_size ((256) * (1024))
#define builtin__prealloc_recycle_cache_slots (8)
#define builtin__prealloc_default_align ((sizeof(void*)) * (2))
#define builtin__cp_acp (0)
#define builtin__cp_utf8 (65001)
MessageError builtin__error_sentinel__object = {.msg = {"error", 5, 1}};
IError builtin__error_sentinel = {._typ = 71273906, ._object = &builtin__error_sentinel__object};
#define fnv1a__fnv64_prime (((u64)(1099511628211)))
#define fnv1a__fnv64_offset_basis (((u64)(14695981039346656037)))
#define fnv1a__fnv32_offset_basis (((u32)(2166136261)))
#define fnv1a__fnv32_prime (((u32)(16777619)))
#define termios__cclen (32)
#define os__fslash ('/')
#define os__bslash ('\\')
#define os__dot ('.')
#define os__qmark ('?')
#define os__max_path_len (4096)
#define os__f_ok (0)
#define os__x_ok (1)
#define os__w_ok (2)
#define os__r_ok (4)
#define os__read_lines_chunk_size ((128) * (1024))
#define os__error_code_noent (((i64)(ENOENT)))
#define os__error_code_denied (((i64)(EACCES)))
#define os__error_code_perm (((i64)(EPERM)))
#define os__error_code_exist (((i64)(EEXIST)))
#define os__error_code_notdir (((i64)(ENOTDIR)))
#define os__max_path_buffer_size (4096)
#define os__o_binary (0)
#define os__o_rdonly (O_RDONLY)
#define os__o_wronly (O_WRONLY)
#define os__o_rdwr (O_RDWR)
#define os__o_create (O_CREAT)
#define os__o_excl (O_EXCL)
#define os__o_noctty (O_NOCTTY)
#define os__o_trunc (O_TRUNC)
#define os__o_append (O_APPEND)
#define os__o_nonblock (O_NONBLOCK)
#define os__o_sync (O_SYNC)
#define os__sysctl_ctl_kern (((i32)(1)))
#define os__freebsd_kern_proc (((i32)(14)))
#define os__freebsd_kern_proc_pathname (((i32)(12)))
#define os__openbsd_kern_proc_args (((i32)(55)))
#define os__openbsd_kern_proc_argv (((i32)(1)))
#define os__buf_size (4096)
#define os__error_code_not_set (((i64)(-(1))))
#define os__prot_read (1)
#define os__prot_write (2)
#define os__map_private (0x02)
#define os__map_anonymous (0x20)
#define os__sys_write (1)
#define os__sys_open (2)
#define os__sys_close (3)
#define os__sys_mkdir (83)
#define os__sys_creat (85)
#define os__stdin_value (0)
#define os__stdout_value (1)
#define os__stderr_value (2)
#define os__s_ifmt (((u32)(0xF000)))
#define os__s_ifdir (((u32)(0x4000)))
#define os__s_ifreg (((u32)(0x8000)))
#define os__s_iflnk (((u32)(0xa000)))
#define os__s_isuid (((u32)(04000)))
#define os__s_isgid (((u32)(02000)))
#define os__s_isvtx (((u32)(01000)))
#define os__s_irusr (((u32)(00400)))
#define os__s_iwusr (((u32)(00200)))
#define os__s_ixusr (((u32)(00100)))
#define os__s_irgrp (((u32)(00040)))
#define os__s_iwgrp (((u32)(00020)))
#define os__s_ixgrp (((u32)(00010)))
#define os__s_iroth (((u32)(00004)))
#define os__s_iwoth (((u32)(00002)))
#define os__s_ixoth (((u32)(00001)))
#define os__fd_stdout (STDOUT_FILENO)
#define os__fd_stderr (STDERR_FILENO)
#define closure__assumed_page_size (((i64)(0x4000)))
#define closure__ppc64_architecture (((i64)(11)))
#define main__hash_chunk_size ((64) * (1024))

/* V3CACHE_BODY_BEGIN */
/* V3CACHE_MODULE __v3_program_support */
void _vinit() {
	gc_runtime_init();
#if (defined(_VGCBOEHM) || defined(CUSTOM_DEFINE_gcboehm)) && defined(GC_THREADS)
	GC_allow_register_threads();
#endif
	__v3_cache_strings__init_consts_defaults();
	__v3_cache_bits__init_consts_defaults();
	__v3_cache_strconv__init_consts_defaults();
	__v3_cache_hash__init_consts_defaults();
	__v3_cache_builtin__init_consts_defaults();
	__v3_cache_fnv1a__init_consts_defaults();
	__v3_cache_textscanner__init_consts_defaults();
	__v3_cache_termios__init_consts_defaults();
	__v3_cache_os__init_consts_defaults();
	__v3_cache_closure__init_consts_defaults();
	__v3_cache_strings__init_consts();
	__v3_cache_bits__init_consts();
	__v3_cache_strconv__init_consts();
	__v3_cache_hash__init_consts();
	__v3_cache_builtin__init_consts();
	builtin_init();
	__v3_cache_fnv1a__init_consts();
	__v3_cache_textscanner__init_consts();
	__v3_cache_termios__init_consts();
	__v3_cache_os__init_consts();
	os__init();
	__v3_cache_closure__init_consts();
	closure__closure_init();
}

/* V3CACHE_MODULE main */
string IError__msg(IError* i) {
	if (i->_typ == 1938660593) return Error__msg(*(Error*)i->_object);
	if (i->_typ == 71273906) return MessageError__msg(*(MessageError*)i->_object);
	if (i->_typ == 2065246729) return Error__msg(((None__*)i->_object)->Error);
	if (i->_typ == 1743421611) return Error__msg(((os__Eof*)i->_object)->Error);
	if (i->_typ == 227373654) return os__ExecutableNotFoundError__msg(*(os__ExecutableNotFoundError*)i->_object);
	if (i->_typ == 1564013019) return os__FileNotOpenedError__msg(*(os__FileNotOpenedError*)i->_object);
	if (i->_typ == 310309972) return os__NotExpected__msg(*(os__NotExpected*)i->_object);
	if (i->_typ == 721233953) return os__SizeOfTypeIs0Error__msg(*(os__SizeOfTypeIs0Error*)i->_object);
	v_panic(_v3_lit_43_9edf8799b50a549c);
	return (string){0};
}
/* V3CACHE_MODULE main */
i64 IError__code(IError* i) {
	if (i->_typ == 1938660593) return Error__code(*(Error*)i->_object);
	if (i->_typ == 71273906) return MessageError__code(*(MessageError*)i->_object);
	if (i->_typ == 2065246729) return Error__code(((None__*)i->_object)->Error);
	if (i->_typ == 1743421611) return Error__code(((os__Eof*)i->_object)->Error);
	if (i->_typ == 227373654) return Error__code(((os__ExecutableNotFoundError*)i->_object)->Error);
	if (i->_typ == 1564013019) return Error__code(((os__FileNotOpenedError*)i->_object)->Error);
	if (i->_typ == 310309972) return os__NotExpected__code(*(os__NotExpected*)i->_object);
	if (i->_typ == 721233953) return Error__code(((os__SizeOfTypeIs0Error*)i->_object)->Error);
	v_panic(_v3_lit_44_7e766e4cc095bb70);
	return (i64){0};
}
/* V3CACHE_MODULE main */
Array hash__Hash__sum(hash__Hash* i, Array _a0) {
	v_panic(_v3_lit_47_67a5effad7253ea3);
	return (Array){0};
}
/* V3CACHE_MODULE main */
i64 hash__Hash__size(hash__Hash* i) {
	v_panic(_v3_lit_48_e55a586fc0c6b73f);
	return (i64){0};
}
/* V3CACHE_MODULE main */
i64 hash__Hash__block_size(hash__Hash* i) {
	v_panic(_v3_lit_54_503bb76740bf2bb9);
	return (i64){0};
}
/* V3CACHE_MODULE main */
void hash__Hash__free(hash__Hash* i) {
	v_panic(_v3_lit_48_fb91f183b903b558);
}
/* V3CACHE_MODULE main */
void hash__Hash__reset(hash__Hash* i) {
	v_panic(_v3_lit_49_eb073e2877ead767);
}
/* V3CACHE_MODULE main */
__v_result_i64 hash__Hash__write(hash__Hash* i, Array _a0) {
	v_panic(_v3_lit_49_2678ade7cd32896b);
	return (__v_result_i64){0};
}
/* V3CACHE_MODULE main */
u32 hash__Hash32er__sum32(hash__Hash32er* i) {
	v_panic(_v3_lit_53_95bddd17dfe45e44);
	return (u32){0};
}
/* V3CACHE_MODULE main */
u64 hash__Hash64er__sum64(hash__Hash64er* i) {
	v_panic(_v3_lit_53_5f2d8f78123176b0);
	return (u64){0};
}
/* V3CACHE_MODULE main */
__v_result hash__Hasher__write(hash__Hasher* i, Array _a0) {
	switch (i->_typ) {
		case 1413031071: return fnv1a__Fnv1a64__write((fnv1a__Fnv1a64*)i->_object, _a0);
		default: break;
	}
	v_panic(_v3_lit_51_dc22f65c21aeb98);
	return (__v_result){0};
}
/* V3CACHE_MODULE main */
u64 hash__Hasher__finish(hash__Hasher* i) {
	switch (i->_typ) {
		case 1413031071: return fnv1a__Fnv1a64__finish((fnv1a__Fnv1a64*)i->_object);
		default: break;
	}
	v_panic(_v3_lit_52_81b5cee77879d238);
	return (u64){0};
}

/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7e0ecdeaa64e5224 */
string Array_rune__string(Array ra) {
	Array __esc_0 = strings__new_builder(ra.len);
	Array* sb = (Array*)(memdup(&__esc_0, sizeof(Array)));
	strings__Builder__write_runes(sb, ra);
	string res = strings__Builder__str(sb);
	{
		strings__Builder__free(sb);
	}
	return res;
}

/* V3CACHE_FN_END 7e0ecdeaa64e5224 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 87f16ef66d22fe8c */
void Array_string__free(Array* a) {
	{
		i64 __for_idx_0 = 0;
		for (; __for_idx_0 < (*a).len; __for_idx_0++) {
			string* s = (string*)(array_get(*a, __for_idx_0));
			{
				string__free(s);
			}
		}
	}
	array* arr = (array*)(a);
	{
		array__free(arr);
	}
}

/* V3CACHE_FN_END 87f16ef66d22fe8c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN dde2772086485b92 */
string Array_string__join(Array a, string sep) {
	if (a.len == 0) {
		return _v3_lit_0_14650fb0739d0383;
	}
	i64 len = 0;
	{
		i64 __for_idx_0 = 0;
		for (; __for_idx_0 < a.len; __for_idx_0++) {
			string val = *(string*)(array_get(a, __for_idx_0));
			len += val.len + sep.len;
		}
	}
	len -= sep.len;
	string res = (string){.str = malloc_noscan(len + 1), .len = len};
	i64 idx = 0;
	{
		i64 i = 0;
		for (; i < a.len; i++) {
			string val = *(string*)(array_get(a, i));
			{
				vmemcpy((void*)(res.str + idx), (void*)(val.str), val.len);
				idx += val.len;
			}
			if (i != (a.len - 1)) {
				{
					vmemcpy((void*)(res.str + idx), (void*)(sep.str), sep.len);
					idx += sep.len;
				}
			}
		}
	}
	{
		(res.str)[res.len] = 0;
	}
	return res;
}

/* V3CACHE_FN_END dde2772086485b92 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 67c5de5973e76f02 */
inline string Array_string__join_lines(Array s) {
	return Array_string__join(s, _v3_lit_1_44bd31d473cd01cb);
}

/* V3CACHE_FN_END 67c5de5973e76f02 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 89ffb9763ff4275c */
inline void Array_string__sort_by_len(Array* s) {
	{
		i64 __sort_n_0 = s->len;
		Array __sort_buf_1 = array_new(		sizeof(string), __sort_n_0, __sort_n_0);
		Array __sort_src_2 = *s;
		Array __sort_dst_3 = __sort_buf_1;
		{
			i64 __sort_w_5 = 1;
			for (; __sort_w_5 < __sort_n_0; __sort_w_5 = (i64)(((i64)(			__sort_w_5)) << (1))) {
				{
					i64 __sort_lo_6 = 0;
					for (; __sort_lo_6 < __sort_n_0; ) {
						i64 __sort_mid_7 = __sort_lo_6 + __sort_w_5;
						if (__sort_mid_7 > __sort_n_0) {
							__sort_mid_7 = __sort_n_0;
						}
						i64 __sort_hi_8 = __sort_mid_7 + __sort_w_5;
						if (__sort_hi_8 > __sort_n_0) {
							__sort_hi_8 = __sort_n_0;
						}
						i64 __sort_i_9 = __sort_lo_6;
						i64 __sort_j_10 = __sort_mid_7;
						i64 __sort_k_11 = __sort_lo_6;
						for (; (__sort_i_9 < __sort_mid_7) && (__sort_j_10 < __sort_hi_8); __sort_k_11++) {
							if (compare_strings_by_len(&(*((string*)((__sort_src_2).data) + (__sort_j_10))), &(*((string*)((__sort_src_2).data) + (__sort_i_9)))) < 0) {
								array_sort_move(__sort_dst_3.data, __sort_k_11, __sort_src_2.data, __sort_j_10, 1, sizeof(string));
								__sort_j_10 = __sort_j_10 + 1;
							} else {
								array_sort_move(__sort_dst_3.data, __sort_k_11, __sort_src_2.data, __sort_i_9, 1, sizeof(string));
								__sort_i_9 = __sort_i_9 + 1;
							}
						}
						if (__sort_i_9 < __sort_mid_7) {
							array_sort_move(__sort_dst_3.data, __sort_k_11, __sort_src_2.data, __sort_i_9, __sort_mid_7 - __sort_i_9, sizeof(string));
						} else {
							if (__sort_j_10 < __sort_hi_8) {
								array_sort_move(__sort_dst_3.data, __sort_k_11, __sort_src_2.data, __sort_j_10, __sort_hi_8 - __sort_j_10, sizeof(string));
							}
						}
						__sort_lo_6 = __sort_hi_8;
					}
				}
				Array __sort_swap_4 = __sort_src_2;
				__sort_src_2 = __sort_dst_3;
				__sort_dst_3 = __sort_swap_4;
			}
		}
		if (__sort_src_2.data != s->data) {
			array_sort_move(s->data, 0, __sort_src_2.data, 0, __sort_n_0, sizeof(string));
		}
		array__free(&__sort_buf_1);
	}
	0;
}

/* V3CACHE_FN_END 89ffb9763ff4275c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6adcf649d7271df6 */
inline void Array_string__sort_ignore_case(Array* s) {
	{
		i64 __sort_n_0 = s->len;
		Array __sort_buf_1 = array_new(		sizeof(string), __sort_n_0, __sort_n_0);
		Array __sort_src_2 = *s;
		Array __sort_dst_3 = __sort_buf_1;
		{
			i64 __sort_w_5 = 1;
			for (; __sort_w_5 < __sort_n_0; __sort_w_5 = (i64)(((i64)(			__sort_w_5)) << (1))) {
				{
					i64 __sort_lo_6 = 0;
					for (; __sort_lo_6 < __sort_n_0; ) {
						i64 __sort_mid_7 = __sort_lo_6 + __sort_w_5;
						if (__sort_mid_7 > __sort_n_0) {
							__sort_mid_7 = __sort_n_0;
						}
						i64 __sort_hi_8 = __sort_mid_7 + __sort_w_5;
						if (__sort_hi_8 > __sort_n_0) {
							__sort_hi_8 = __sort_n_0;
						}
						i64 __sort_i_9 = __sort_lo_6;
						i64 __sort_j_10 = __sort_mid_7;
						i64 __sort_k_11 = __sort_lo_6;
						for (; (__sort_i_9 < __sort_mid_7) && (__sort_j_10 < __sort_hi_8); __sort_k_11++) {
							if (compare_lower_strings(&(*((string*)((__sort_src_2).data) + (__sort_j_10))), &(*((string*)((__sort_src_2).data) + (__sort_i_9)))) < 0) {
								array_sort_move(__sort_dst_3.data, __sort_k_11, __sort_src_2.data, __sort_j_10, 1, sizeof(string));
								__sort_j_10 = __sort_j_10 + 1;
							} else {
								array_sort_move(__sort_dst_3.data, __sort_k_11, __sort_src_2.data, __sort_i_9, 1, sizeof(string));
								__sort_i_9 = __sort_i_9 + 1;
							}
						}
						if (__sort_i_9 < __sort_mid_7) {
							array_sort_move(__sort_dst_3.data, __sort_k_11, __sort_src_2.data, __sort_i_9, __sort_mid_7 - __sort_i_9, sizeof(string));
						} else {
							if (__sort_j_10 < __sort_hi_8) {
								array_sort_move(__sort_dst_3.data, __sort_k_11, __sort_src_2.data, __sort_j_10, __sort_hi_8 - __sort_j_10, sizeof(string));
							}
						}
						__sort_lo_6 = __sort_hi_8;
					}
				}
				Array __sort_swap_4 = __sort_src_2;
				__sort_src_2 = __sort_dst_3;
				__sort_dst_3 = __sort_swap_4;
			}
		}
		if (__sort_src_2.data != s->data) {
			array_sort_move(s->data, 0, __sort_src_2.data, 0, __sort_n_0, sizeof(string));
		}
		array__free(&__sort_buf_1);
	}
	0;
}

/* V3CACHE_FN_END 6adcf649d7271df6 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f03e49c262b4881d */
string Array_string__str(Array a) {
	i64 sb_len = 4;
	if (a.len > 0) {
		sb_len += ((*((string*)((a).data) + (0)))).len;
		sb_len *= a.len;
	}
	sb_len += 2;
	Array __esc_0 = strings__new_builder(sb_len);
	Array* sb = (Array*)(memdup(&__esc_0, sizeof(Array)));
	strings__Builder__write_u8(sb, '[');
	{
		i64 i = 0;
		for (; i < a.len; i++) {
			string val = (*((string*)((a).data) + (i)));
			strings__Builder__write_u8(sb, '\'');
			strings__Builder__write_string(sb, val);
			strings__Builder__write_u8(sb, '\'');
			if (i < (a.len - 1)) {
				strings__Builder__write_string(sb, _v3_lit_2_9afebb00c5c7fa67);
			}
		}
	}
	strings__Builder__write_u8(sb, ']');
	string res = strings__Builder__str(sb);
	{
		strings__Builder__free(sb);
	}
	return res;
}

/* V3CACHE_FN_END f03e49c262b4881d */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 156cdac665885f2c */
__v_result_u32 Array_u8__byterune(Array b) {
	__v_result_u32 __or_opt_0 = Array_u8__utf8_to_utf32(b);
	u32 __or_val_1 = {0};
	if (__or_opt_0.ok) {
		__or_val_1 = __or_opt_0.value;
	} else {
		return (__v_result_u32){.ok = false, .err = __or_opt_0.err};
	}
	u32 r = __or_val_1;
	return (__v_result_u32){.ok = true, .value = (u32)(r)};
	return (__v_result_u32){.ok = true};
}

/* V3CACHE_FN_END 156cdac665885f2c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 75d01573379b2c67 */
string Array_u8__bytestr(Array b) {
	{
		u8* buf = malloc_noscan(b.len + 1);
		vmemcpy((void*)(buf), b.data, b.len);
		(buf)[b.len] = 0;
		return tos(buf, b.len);
	}
}

/* V3CACHE_FN_END 75d01573379b2c67 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 466e45423b681ceb */
string Array_u8__hex(Array b) {
	if (b.len == 0) {
		return _v3_lit_0_14650fb0739d0383;
	}
	return data_to_hex_string(b.data, b.len);
}

/* V3CACHE_FN_END 466e45423b681ceb */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1531a31d2461d60e */
__v_result_u32 Array_u8__utf8_to_utf32(Array _bytes) {
	if (_bytes.len > 4) {
		return (__v_result_u32){.ok = false, .err = (IError){._typ = 71273906, ._object = (MessageError*)memdup(&(MessageError){.msg = _v3_lit_74_82fc39ccb1421152, .code = 0}, sizeof(MessageError)), ._object_is_boxed = true}};
	}
	return (__v_result_u32){.ok = true, .value = impl_utf8_to_utf32(_bytes.data, _bytes.len)};
	return (__v_result_u32){.ok = true};
}

/* V3CACHE_FN_END 1531a31d2461d60e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 9fe8bc5b91ffb9aa */
i64 Error__code(Error err) {
}

/* V3CACHE_FN_END 9fe8bc5b91ffb9aa */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b240da78ab859486 */
string Error__msg(Error err) {
}

/* V3CACHE_FN_END b240da78ab859486 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 83f226ada7870307 */
string IError__str(IError err) {
}

/* V3CACHE_FN_END 83f226ada7870307 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 892f7fcca6334cb3 */
i64 MessageError__code(MessageError err) {
}

/* V3CACHE_FN_END 892f7fcca6334cb3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c71ebd4b905410c5 */
string MessageError__msg(MessageError err) {
}

/* V3CACHE_FN_END c71ebd4b905410c5 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN fca1adce0c1fb9b2 */
string StrIntpType_str(int x) {
}

/* V3CACHE_FN_END fca1adce0c1fb9b2 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6e108271464470b1 */
void* __as_cast(void* obj, i64 obj_type, i64 expected_type, string obj_name, string expected_name) {
}

/* V3CACHE_FN_END 6e108271464470b1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7d221081fa6887ff */
array __new_array(i64 mylen, i64 cap, i64 elm_size) {
}

/* V3CACHE_FN_END 7d221081fa6887ff */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 9c7e372c62a38a3e */
array __new_array_noscan(i64 mylen, i64 cap, i64 elm_size) {
}

/* V3CACHE_FN_END 9c7e372c62a38a3e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 9c36632961f94327 */
array array__clone(array* a) {
}

/* V3CACHE_FN_END 9c36632961f94327 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e926dd2f779f03af */
void array__delete(array* a, i64 i) {
}

/* V3CACHE_FN_END e926dd2f779f03af */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 526060422b37cb90 */
void array__delete_last(array* a) {
}

/* V3CACHE_FN_END 526060422b37cb90 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 745ee047b13d585d */
void array__ensure_cap(array* a, i64 required) {
}

/* V3CACHE_FN_END 745ee047b13d585d */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e6d047539692f0cc */
void array__free(array* a) {
}

/* V3CACHE_FN_END e6d047539692f0cc */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN fbbbbe8d1d1c578 */
void* array__get(array a, i64 i) {
}

/* V3CACHE_FN_END fbbbbe8d1d1c578 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN d2b9a34aa542cdb5 */
void array__insert(array* a, i64 i, void* val) {
}

/* V3CACHE_FN_END d2b9a34aa542cdb5 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 368d9f7c5c0cfff7 */
void array__insert_many(array* a, i64 i, void* val, i64 size) {
}

/* V3CACHE_FN_END 368d9f7c5c0cfff7 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 2e813a4ec3dfb7e5 */
void* array__pop_left(array* a) {
}

/* V3CACHE_FN_END 2e813a4ec3dfb7e5 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4e04df4af5223e70 */
void array__prepend(array* a, void* val) {
}

/* V3CACHE_FN_END 4e04df4af5223e70 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 53206d0f2cf910e6 */
inline void array__push(array* a, void* val) {
}

/* V3CACHE_FN_END 53206d0f2cf910e6 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN d50b76d93d40de32 */
void array__push_many(array* a, void* val, i64 size) {
}

/* V3CACHE_FN_END d50b76d93d40de32 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6d53cfaf757d288e */
array array__reverse(array a) {
}

/* V3CACHE_FN_END 6d53cfaf757d288e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN d5c7bc8fb641f6b4 */
void array__set(array* a, i64 i, void* val) {
}

/* V3CACHE_FN_END d5c7bc8fb641f6b4 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 481470f8777a6a */
array array__slice(array a, i64 start, i64 _end) {
}

/* V3CACHE_FN_END 481470f8777a6a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7f966d8177ba3a80 */
array array__slice_ni(array a, i64 _start, i64 _end) {
}

/* V3CACHE_FN_END 7f966d8177ba3a80 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c2de7a9dc859ebff */
void array__sort_with_compare(array* a, _fn_ptr_ed95774d3a4e97ab callback) {
}

/* V3CACHE_FN_END c2de7a9dc859ebff */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 9d45ccef722b32b3 */
inline void array_sort_move(void* dst, i64 di, void* src, i64 si, i64 count, size_t element_size) {
}

/* V3CACHE_FN_END 9d45ccef722b32b3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 303e640c3d5804ad */
void autostr_addr_pop(void) {
}

/* V3CACHE_FN_END 303e640c3d5804ad */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 24148acb588a7717 */
bool autostr_addr_type_in_stack(void* addr, i64 typ) {
}

/* V3CACHE_FN_END 24148acb588a7717 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN cb97f87e0f3c323 */
void autostr_addr_type_push(void* addr, i64 typ) {
}

/* V3CACHE_FN_END cb97f87e0f3c323 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 2a014151ff39b0e2 */
string bool__str(bool b) {
}

/* V3CACHE_FN_END 2a014151ff39b0e2 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f705e6ed510b1c83 */
void builtin_init(void) {
}

/* V3CACHE_FN_END f705e6ed510b1c83 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e6e9f9cd151f8ca0 */
Array byteptr__vbytes(u8* data, i64 len) {
}

/* V3CACHE_FN_END e6e9f9cd151f8ca0 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1b5d4ea6b67a1406 */
string byteptr__vstring(u8* bp) {
}

/* V3CACHE_FN_END 1b5d4ea6b67a1406 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 2822b22f4cc928ab */
string byteptr__vstring_with_len(u8* bp, i64 len) {
}

/* V3CACHE_FN_END 2822b22f4cc928ab */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN d02896b0fff57810 */
string charptr__vstring(char* cp) {
}

/* V3CACHE_FN_END d02896b0fff57810 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e32627f9295552b9 */
string charptr__vstring_with_len(char* cp, i64 len) {
}

/* V3CACHE_FN_END e32627f9295552b9 */
/* V3CACHE_MODULE closure */
/* V3CACHE_FN_BEGIN bcd99aeb82fd09fb */
void* closure__closure_create_with_data(void* func, void* data, bool owns_data) {
}

/* V3CACHE_FN_END bcd99aeb82fd09fb */
/* V3CACHE_MODULE closure */
/* V3CACHE_FN_BEGIN c2795548f211ecff */
void closure__closure_init(void) {
}

/* V3CACHE_FN_END c2795548f211ecff */
/* V3CACHE_MODULE closure */
/* V3CACHE_FN_BEGIN 15846f473bac9701 */
void closure__closure_try_destroy(void* closure) {
}

/* V3CACHE_FN_END 15846f473bac9701 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ed4d38079c262cfd */
i64 compare_lower_strings(string* a, string* b) {
}

/* V3CACHE_FN_END ed4d38079c262cfd */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 80d130ff837fcf5b */
i64 compare_strings_by_len(string* a, string* b) {
}

/* V3CACHE_FN_END 80d130ff837fcf5b */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7be9bd701f95a28f */
string data_to_hex_string(u8* data, i64 len) {
}

/* V3CACHE_FN_END 7be9bd701f95a28f */
/* V3CACHE_MODULE __v3_program_specializations */
/* V3CACHE_FN_BEGIN 31772e336ff0ebe3 */
void drop_owned_interface_T_IError(IError value) {
	({
		extern IError builtin__none__;
		extern IError builtin__error_sentinel;
		if ((		value)._object_is_boxed && ((		value)._object) != NULL && ((		value)._object) != builtin__none__._object && ((		value)._object) != builtin__error_sentinel._object) {
			switch ((		value)._typ) {
			case 71273906:
				string__free(&(((MessageError*)((		value)._object))->msg));
				break;
			case 310309972:
				string__free(&((*((os__NotExpected*)((		value)._object))).cause));
				break;
			default: break;
			}
			v_gc_free(((		value)._object));
			(		value)._object = NULL;
			(		value)._object_is_boxed = false;
		}
	});
}

/* V3CACHE_FN_END 31772e336ff0ebe3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 17784e4a114a578d */
void drop_owned_result_error(IError err) {
}

/* V3CACHE_FN_END 17784e4a114a578d */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ad55a9f448838df5 */
void drop_owned_result_error_interface(IError err) {
	drop_owned_interface_T_IError(err);
}

/* V3CACHE_FN_END ad55a9f448838df5 */
/* V3CACHE_MODULE __v3_program_specializations */
/* V3CACHE_FN_BEGIN f5e815758880a82f */
void drop_owned_v3_interface_T_IError(IError value) {
	{
		IError owned = value;
		OwnershipV3InterfacePayload* raw_interface = (OwnershipV3InterfacePayload*)((void*)(&owned));
		if (raw_interface->is_boxed) {
			({
				extern IError builtin__none__;
				extern IError builtin__error_sentinel;
				if ((				owned)._object_is_boxed && ((				owned)._object) != NULL && ((				owned)._object) != builtin__none__._object && ((				owned)._object) != builtin__error_sentinel._object) {
					switch ((				owned)._typ) {
					case 71273906:
						string__free(&(((MessageError*)((				owned)._object))->msg));
						break;
					case 310309972:
						string__free(&((*((os__NotExpected*)((				owned)._object))).cause));
						break;
					default: break;
					}
					v_gc_free(((				owned)._object));
					(				owned)._object = NULL;
					(				owned)._object_is_boxed = false;
				}
			});
		}
	}
}

/* V3CACHE_FN_END f5e815758880a82f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN a0f0ef814a5f4849 */
void eprintln(string s) {
}

/* V3CACHE_FN_END a0f0ef814a5f4849 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 521becd69263d987 */
inline IError error(string message) {
}

/* V3CACHE_FN_END 521becd69263d987 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 3c5514d29551cb6e */
inline IError error_with_code(string message, i64 code) {
}

/* V3CACHE_FN_END 3c5514d29551cb6e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4ac177dd6eb55c27 */
inline string f32__str(float x) {
}

/* V3CACHE_FN_END 4ac177dd6eb55c27 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6df00afac41b19f2 */
inline string f64__str(double x) {
}

/* V3CACHE_FN_END 6df00afac41b19f2 */
/* V3CACHE_MODULE main */
/* V3CACHE_FN_BEGIN 8acff25de61f7b8f */
__v_result_Array find_dupes(Array dirs) {
	Array files = walk_files(dirs);
	map size_groups = group_by_size(files);
	Array dupes = array_new(	sizeof(main__DupeGroup), 0, 0);
	for (int __mi_0 = 0; __mi_0 < (	size_groups).data->key_values.len; __mi_0++) {
		if ((	size_groups).data->key_values.all_deleted && (	size_groups).data->key_values.all_deleted[__mi_0]) continue;
		u64 size = *(u64*)((	size_groups).data->key_values.keys + __mi_0 * (	size_groups).data->key_values.key_bytes);
		Array bucket = *(Array*)((	size_groups).data->key_values.values + __mi_0 * (	size_groups).data->key_values.value_bytes);
		if (bucket.len < 2) {
			continue;
		}
		map by_hash = new_map(sizeof(string), sizeof(Array), map_hash_string, map_eq_string, map_clone_string, map_free_string);
		{
			i64 __for_idx_0 = 0;
			for (; __for_idx_0 < bucket.len; __for_idx_0++) {
				main__ScannedFile f = *(main__ScannedFile*)(array_get(bucket, __for_idx_0));
				__v_result_string __or_opt_1 = hash_file(f.path);
				string __or_val_2 = {0};
				if (__or_opt_1.ok) {
					__or_val_2 = __or_opt_1.value;
				} else {
					return (__v_result_Array){.ok = false, .err = __or_opt_1.err};
				}
				string digest = __or_val_2;
				string __map_key_3 = digest;
				Array __map_zero_5 = array_new(sizeof(string), 0, 0);
				Array __map_val_4 = *(Array*)(map__get(&by_hash, &__map_key_3, &__map_zero_5));
				string __arr_val_6 = string__clone(f.path);
				array_push(&__map_val_4, &__arr_val_6);
				map__set(&by_hash, &__map_key_3, &__map_val_4);
			}
		}
		for (int __mi_1 = 0; __mi_1 < (		by_hash).data->key_values.len; __mi_1++) {
			if ((		by_hash).data->key_values.all_deleted && (		by_hash).data->key_values.all_deleted[__mi_1]) continue;
			string hash = *(string*)((		by_hash).data->key_values.keys + __mi_1 * (		by_hash).data->key_values.key_bytes);
			hash = string__clone(hash);
			Array paths = *(Array*)((		by_hash).data->key_values.values + __mi_1 * (		by_hash).data->key_values.value_bytes);
			if (paths.len < 2) {
				continue;
			}
			Array sorted = array__clone(&paths);
			{
				i64 __sort_n_7 = sorted.len;
				Array __sort_buf_8 = array_new(				sizeof(string), __sort_n_7, __sort_n_7);
				Array __sort_src_9 = sorted;
				Array __sort_dst_10 = __sort_buf_8;
				{
					i64 __sort_w_12 = 1;
					for (; __sort_w_12 < __sort_n_7; __sort_w_12 = (i64)(((i64)(					__sort_w_12)) << (1))) {
						{
							i64 __sort_lo_13 = 0;
							for (; __sort_lo_13 < __sort_n_7; ) {
								i64 __sort_mid_14 = __sort_lo_13 + __sort_w_12;
								if (__sort_mid_14 > __sort_n_7) {
									__sort_mid_14 = __sort_n_7;
								}
								i64 __sort_hi_15 = __sort_mid_14 + __sort_w_12;
								if (__sort_hi_15 > __sort_n_7) {
									__sort_hi_15 = __sort_n_7;
								}
								i64 __sort_i_16 = __sort_lo_13;
								i64 __sort_j_17 = __sort_mid_14;
								i64 __sort_k_18 = __sort_lo_13;
								for (; (__sort_i_16 < __sort_mid_14) && (__sort_j_17 < __sort_hi_15); __sort_k_18++) {
									if (string__lt((*((string*)((__sort_src_9).data) + (__sort_j_17))), (*((string*)((__sort_src_9).data) + (__sort_i_16))))) {
										array_sort_move(__sort_dst_10.data, __sort_k_18, __sort_src_9.data, __sort_j_17, 1, sizeof(string));
										__sort_j_17 = __sort_j_17 + 1;
									} else {
										array_sort_move(__sort_dst_10.data, __sort_k_18, __sort_src_9.data, __sort_i_16, 1, sizeof(string));
										__sort_i_16 = __sort_i_16 + 1;
									}
								}
								if (__sort_i_16 < __sort_mid_14) {
									array_sort_move(__sort_dst_10.data, __sort_k_18, __sort_src_9.data, __sort_i_16, __sort_mid_14 - __sort_i_16, sizeof(string));
								} else {
									if (__sort_j_17 < __sort_hi_15) {
										array_sort_move(__sort_dst_10.data, __sort_k_18, __sort_src_9.data, __sort_j_17, __sort_hi_15 - __sort_j_17, sizeof(string));
									}
								}
								__sort_lo_13 = __sort_hi_15;
							}
						}
						Array __sort_swap_11 = __sort_src_9;
						__sort_src_9 = __sort_dst_10;
						__sort_dst_10 = __sort_swap_11;
					}
				}
				if (__sort_src_9.data != sorted.data) {
					array_sort_move(sorted.data, 0, __sort_src_9.data, 0, __sort_n_7, sizeof(string));
				}
				array__free(&__sort_buf_8);
			}
			0;
			main__DupeGroup __arr_val_19 = (main__DupeGroup){.size = size, .hash = hash, .files = sorted};
			array_push(&dupes, &__arr_val_19);
		}
	}
	{
		i64 __sort_n_20 = dupes.len;
		Array __sort_buf_21 = array_new(		sizeof(main__DupeGroup), __sort_n_20, __sort_n_20);
		Array __sort_src_22 = dupes;
		Array __sort_dst_23 = __sort_buf_21;
		{
			i64 __sort_w_25 = 1;
			for (; __sort_w_25 < __sort_n_20; __sort_w_25 = (i64)(((i64)(			__sort_w_25)) << (1))) {
				{
					i64 __sort_lo_26 = 0;
					for (; __sort_lo_26 < __sort_n_20; ) {
						i64 __sort_mid_27 = __sort_lo_26 + __sort_w_25;
						if (__sort_mid_27 > __sort_n_20) {
							__sort_mid_27 = __sort_n_20;
						}
						i64 __sort_hi_28 = __sort_mid_27 + __sort_w_25;
						if (__sort_hi_28 > __sort_n_20) {
							__sort_hi_28 = __sort_n_20;
						}
						i64 __sort_i_29 = __sort_lo_26;
						i64 __sort_j_30 = __sort_mid_27;
						i64 __sort_k_31 = __sort_lo_26;
						for (; (__sort_i_29 < __sort_mid_27) && (__sort_j_30 < __sort_hi_28); __sort_k_31++) {
							if (((*((main__DupeGroup*)((__sort_src_22).data) + (__sort_j_30)))).size > ((*((main__DupeGroup*)((__sort_src_22).data) + (__sort_i_29)))).size) {
								array_sort_move(__sort_dst_23.data, __sort_k_31, __sort_src_22.data, __sort_j_30, 1, sizeof(main__DupeGroup));
								__sort_j_30 = __sort_j_30 + 1;
							} else {
								array_sort_move(__sort_dst_23.data, __sort_k_31, __sort_src_22.data, __sort_i_29, 1, sizeof(main__DupeGroup));
								__sort_i_29 = __sort_i_29 + 1;
							}
						}
						if (__sort_i_29 < __sort_mid_27) {
							array_sort_move(__sort_dst_23.data, __sort_k_31, __sort_src_22.data, __sort_i_29, __sort_mid_27 - __sort_i_29, sizeof(main__DupeGroup));
						} else {
							if (__sort_j_30 < __sort_hi_28) {
								array_sort_move(__sort_dst_23.data, __sort_k_31, __sort_src_22.data, __sort_j_30, __sort_hi_28 - __sort_j_30, sizeof(main__DupeGroup));
							}
						}
						__sort_lo_26 = __sort_hi_28;
					}
				}
				Array __sort_swap_24 = __sort_src_22;
				__sort_src_22 = __sort_dst_23;
				__sort_dst_23 = __sort_swap_24;
			}
		}
		if (__sort_src_22.data != dupes.data) {
			array_sort_move(dupes.data, 0, __sort_src_22.data, 0, __sort_n_20, sizeof(main__DupeGroup));
		}
		array__free(&__sort_buf_21);
	}
	0;
	return (__v_result_Array){.ok = true, .value = dupes};
	return (__v_result_Array){.ok = true};
}

/* V3CACHE_FN_END 8acff25de61f7b8f */
/* V3CACHE_MODULE fnv1a */
/* V3CACHE_FN_BEGIN babe3247fbf6bb2f */
u64 fnv1a__Fnv1a64__finish(fnv1a__Fnv1a64* h) {
}

/* V3CACHE_FN_END babe3247fbf6bb2f */
/* V3CACHE_MODULE fnv1a */
/* V3CACHE_FN_BEGIN 2bcee02b5257c5d1 */
__v_result fnv1a__Fnv1a64__write(fnv1a__Fnv1a64* h, Array p) {
	return (__v_result){.ok = true};
}

/* V3CACHE_FN_END 2bcee02b5257c5d1 */
/* V3CACHE_MODULE fnv1a */
/* V3CACHE_FN_BEGIN d459ead96d8da689 */
fnv1a__Fnv1a64* fnv1a__new_fnv1a64(void) {
}

/* V3CACHE_FN_END d459ead96d8da689 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 2aefb7aac414a898 */
bool gc_prepare_for_debugger_init(void) {
}

/* V3CACHE_FN_END 2aefb7aac414a898 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 643e3cf9797ac852 */
void gc_restore_roots_after_debugger_init(bool use_manual_roots) {
}

/* V3CACHE_FN_END 643e3cf9797ac852 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 323d479d01f90901 */
inline void gc_runtime_init(void) {
}

/* V3CACHE_FN_END 323d479d01f90901 */
/* V3CACHE_MODULE main */
/* V3CACHE_FN_BEGIN 38754f26eb90a640 */
map group_by_size(Array files) {
	map groups = new_map(sizeof(u64), sizeof(Array), map_hash_int_8, map_eq_int_8, map_clone_int_8, map_free_nop);
	{
		i64 __for_idx_0 = 0;
		for (; __for_idx_0 < files.len; __for_idx_0++) {
			main__ScannedFile f = *(main__ScannedFile*)(array_get(files, __for_idx_0));
			u64 __map_key_1 = f.size;
			Array __map_zero_3 = array_new(sizeof(main__ScannedFile), 0, 0);
			Array __map_val_2 = *(Array*)(map__get(&groups, &__map_key_1, &__map_zero_3));
			main__ScannedFile __derived_clone_4 = f;
			__derived_clone_4.path = string__clone(__derived_clone_4.path);
			main__ScannedFile __arr_val_5 = __derived_clone_4;
			array_push(&__map_val_2, &__arr_val_5);
			map__set(&groups, &__map_key_1, &__map_val_2);
		}
	}
	return groups;
}

/* V3CACHE_FN_END 38754f26eb90a640 */
/* V3CACHE_MODULE main */
/* V3CACHE_FN_BEGIN 380cd82ef48432e9 */
__v_result_string hash_file(string path) {
	fnv1a__Fnv1a64* h = fnv1a__new_fnv1a64();
	__v_result_os__File __or_opt_0 = os__open(path);
	os__File __or_val_1 = {0};
	if (__or_opt_0.ok) {
		__or_val_1 = __or_opt_0.value;
	} else {
		return (__v_result_string){.ok = false, .err = __or_opt_0.err};
	}
	os__File f = __or_val_1;
	Array buf = __new_array_noscan(main__hash_chunk_size, 0, sizeof(u8));
	for (;;) {
		__v_result_i64 __or_opt_2 = os__File__read(&f, &buf);
		i64 __or_val_3 = {0};
		if (__or_opt_2.ok) {
			__or_val_3 = __or_opt_2.value;
		} else {
			__v_result_string _t1 = (__v_result_string){.ok = false, .err = __or_opt_2.err};
			{
				os__File__close(&f);
			}
			return _t1;
		}
		i64 n = __or_val_3;
		if (n == 0) {
			break;
		}
		__v_result __or_opt_4 = fnv1a__Fnv1a64__write(h, array_slice(		buf, 0, 		n));
		if (!__or_opt_4.ok) {
			__v_result_string _t2 = (__v_result_string){.ok = false, .err = __or_opt_4.err};
			{
				os__File__close(&f);
			}
			return _t2;
		}
	}
	__v_result_string _t3 = (__v_result_string){.ok = true, .value = 	strconv__format_uint(fnv1a__Fnv1a64__finish(h), 16)};
	{
		os__File__close(&f);
	}
	return _t3;
	{
		os__File__close(&f);
	}
	return (__v_result_string){.ok = true};
}

/* V3CACHE_FN_END 380cd82ef48432e9 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b5e4003a3c415792 */
string i16__str(i16 n) {
}

/* V3CACHE_FN_END b5e4003a3c415792 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 595ee04119dd653c */
string i32__str(i32 n) {
}

/* V3CACHE_FN_END 595ee04119dd653c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f34b0214224c03b9 */
inline string i64__str(i64 nn) {
}

/* V3CACHE_FN_END f34b0214224c03b9 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f7e9c221bfdac1e1 */
string i8__str(i8 n) {
}

/* V3CACHE_FN_END f7e9c221bfdac1e1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN fd46dfc7328792cc */
u32 impl_utf8_to_utf32(u8* _bytes, i64 _bytes_len) {
}

/* V3CACHE_FN_END fd46dfc7328792cc */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 373b16d1c007501 */
string int__str(i64 n) {
}

/* V3CACHE_FN_END 373b16d1c007501 */
/* V3CACHE_MODULE main */
/* V3CACHE_FN_BEGIN d45fa634b5ad904e */
int main(int argc, char** argv) {
	g_main_argc = argc;
	g_main_argv = argv;
	if (getenv("VEXE") == NULL || getenv("VEXE")[0] == 0) {
		const char* v3_vexe = "/home/gab/Projects/v/v";
		if (v3_vexe[0] != 0) {
#ifdef _WIN32
			_putenv_s("VEXE", v3_vexe);
#else
			setenv("VEXE", v3_vexe, 1);
#endif
		}
	}
	_vinit();
	Array args = array_slice(	os__args, 	1, (	os__args).len);
	if (args.len == 0) {
		eprintln(_v3_lit_29_290cde771a7bd19e);
		v_exit(1);
	}
	__v_result_Array __or_opt_0 = find_dupes(args);
	Array __or_val_1 = {0};
	if (__or_opt_0.ok) {
		__or_val_1 = __or_opt_0.value;
	} else {
		IError err = __or_opt_0.err;
		eprintln(string__plus(_v3_lit_9_97d87a1106c21fc9, IError__msg(&(err))));
		v_exit(1);
	}
	Array groups = __or_val_1;
	print_groups(groups);
	return 0;
}

/* V3CACHE_FN_END d45fa634b5ad904e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 93ce9db3d8e71e28 */
u8* malloc_noscan(ptrdiff_t n) {
}

/* V3CACHE_FN_END 93ce9db3d8e71e28 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 81ab48b177977f6a */
void map__clear(map* m) {
}

/* V3CACHE_FN_END 81ab48b177977f6a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4452d9e25cf1042a */
map map__clone(map* m) {
}

/* V3CACHE_FN_END 4452d9e25cf1042a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1d87169855cc3138 */
void map__delete(map* m, void* key) {
}

/* V3CACHE_FN_END 1d87169855cc3138 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f4e1976900ad5609 */
bool map__exists(map* m, void* key) {
}

/* V3CACHE_FN_END f4e1976900ad5609 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 119fdc98f50627f7 */
void map__free(map* m) {
}

/* V3CACHE_FN_END 119fdc98f50627f7 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 19f1b5223f85b15 */
void* map__get(map* m, void* key, void* zero) {
}

/* V3CACHE_FN_END 19f1b5223f85b15 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 5a05f4ff22ee6052 */
void* map__get_and_set(map* m, void* key, void* zero) {
}

/* V3CACHE_FN_END 5a05f4ff22ee6052 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN a92f840ce30176b8 */
void* map__get_check(map* m, void* key) {
}

/* V3CACHE_FN_END a92f840ce30176b8 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e59214908edb0375 */
array map__keys(map* m) {
}

/* V3CACHE_FN_END e59214908edb0375 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 464c4b6fa6768fd9 */
void map__reserve(map* m, u32 n) {
}

/* V3CACHE_FN_END 464c4b6fa6768fd9 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 3cafcaedf24d0bf1 */
void map__set(map* m, void* key, void* value) {
}

/* V3CACHE_FN_END 3cafcaedf24d0bf1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN df8fa410f98d8e77 */
array map__values(map* m) {
}

/* V3CACHE_FN_END df8fa410f98d8e77 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7c4f1f9dff454cdf */
inline void map_clone_int_1(void* dest, void* pkey) {
}

/* V3CACHE_FN_END 7c4f1f9dff454cdf */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 8264d978c501d781 */
inline void map_clone_int_16(void* dest, void* pkey) {
}

/* V3CACHE_FN_END 8264d978c501d781 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7c4d1f9dff44ca08 */
inline void map_clone_int_2(void* dest, void* pkey) {
}

/* V3CACHE_FN_END 7c4d1f9dff44ca08 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7c451f9dff3cf85a */
inline void map_clone_int_4(void* dest, void* pkey) {
}

/* V3CACHE_FN_END 7c451f9dff3cf85a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7c371f9dff30bafe */
inline void map_clone_int_8(void* dest, void* pkey) {
}

/* V3CACHE_FN_END 7c371f9dff30bafe */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN a045e7ba14b66cd1 */
inline void map_clone_string(void* dest, void* pkey) {
}

/* V3CACHE_FN_END a045e7ba14b66cd1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN bf435b39578a867c */
inline bool map_eq_int_1(void* a, void* b) {
}

/* V3CACHE_FN_END bf435b39578a867c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 8940856fbfc55068 */
inline bool map_eq_int_16(void* a, void* b) {
}

/* V3CACHE_FN_END 8940856fbfc55068 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN bf475b39578e6f53 */
inline bool map_eq_int_2(void* a, void* b) {
}

/* V3CACHE_FN_END bf475b39578e6f53 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN bf4d5b395792db01 */
inline bool map_eq_int_4(void* a, void* b) {
}

/* V3CACHE_FN_END bf4d5b395792db01 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN bf255b39577188ed */
inline bool map_eq_int_8(void* a, void* b) {
}

/* V3CACHE_FN_END bf255b39577188ed */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN fd9b25242970ed68 */
inline bool map_eq_string(void* a, void* b) {
}

/* V3CACHE_FN_END fd9b25242970ed68 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 531fa9d30a1fcf80 */
inline void map_free_nop(void* _0) {
}

/* V3CACHE_FN_END 531fa9d30a1fcf80 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7b17551b3d4fd218 */
inline void map_free_string(void* pkey) {
}

/* V3CACHE_FN_END 7b17551b3d4fd218 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ffe8e0b11b11338a */
u64 map_hash_int_1(void* pkey) {
}

/* V3CACHE_FN_END ffe8e0b11b11338a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN eaab41f0fedf81ae */
u64 map_hash_int_16(void* pkey) {
}

/* V3CACHE_FN_END eaab41f0fedf81ae */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ffdee0b11b08df05 */
u64 map_hash_int_2(void* pkey) {
}

/* V3CACHE_FN_END ffdee0b11b08df05 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN fff2e0b11b19880f */
u64 map_hash_int_4(void* pkey) {
}

/* V3CACHE_FN_END fff2e0b11b19880f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ffcae0b11af835fb */
u64 map_hash_int_8(void* pkey) {
}

/* V3CACHE_FN_END ffcae0b11af835fb */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 973207f7222ff3f2 */
u64 map_hash_string(void* pkey) {
}

/* V3CACHE_FN_END 973207f7222ff3f2 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN a31b06ba18b738ef */
bool map_map_eq(map a, map b) {
}

/* V3CACHE_FN_END a31b06ba18b738ef */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7eff9d679d128a4b */
void* memdup(void* src, ptrdiff_t sz) {
}

/* V3CACHE_FN_END 7eff9d679d128a4b */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4bc2e3e1b8f02add */
void* memdup_align(void* src, ptrdiff_t sz, ptrdiff_t align) {
}

/* V3CACHE_FN_END 4bc2e3e1b8f02add */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 37c3b21ab1001cf2 */
array new_array_from_c_array(i64 len, i64 cap, i64 elm_size, void* c_array) {
}

/* V3CACHE_FN_END 37c3b21ab1001cf2 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7feb25c5b56d7ee9 */
array new_array_from_c_array_noscan(i64 len, i64 cap, i64 elm_size, void* c_array) {
}

/* V3CACHE_FN_END 7feb25c5b56d7ee9 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN dae85c06883b27f8 */
map new_map(i64 key_bytes, i64 value_bytes, _fn_ptr_1e8d64a3d95a0da1 hash_fn, _fn_ptr_c95f092653bee64 key_eq_fn, _fn_ptr_1a3da2026b1489ea clone_fn, _fn_ptr_5373f7edc7b60e26 free_fn) {
}

/* V3CACHE_FN_END dae85c06883b27f8 */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN 2257447e5149c19d */
string os__ExecutableNotFoundError__msg(os__ExecutableNotFoundError err) {
}

/* V3CACHE_FN_END 2257447e5149c19d */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN e887a63ee45070c0 */
string os__FileNotOpenedError__msg(os__FileNotOpenedError err) {
}

/* V3CACHE_FN_END e887a63ee45070c0 */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN 597bafd50ec38321 */
void os__File__close(os__File* f) {
}

/* V3CACHE_FN_END 597bafd50ec38321 */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN c46e63352ba28851 */
__v_result_i64 os__File__read(os__File* f, Array* buf) {
	return (__v_result_i64){.ok = true};
}

/* V3CACHE_FN_END c46e63352ba28851 */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN 8e0b4813f8b714c5 */
i64 os__NotExpected__code(os__NotExpected err) {
}

/* V3CACHE_FN_END 8e0b4813f8b714c5 */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN ddd45dc1bee108fb */
string os__NotExpected__msg(os__NotExpected err) {
}

/* V3CACHE_FN_END ddd45dc1bee108fb */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN 708ce8a85b975fb6 */
string os__SizeOfTypeIs0Error__msg(os__SizeOfTypeIs0Error err) {
}

/* V3CACHE_FN_END 708ce8a85b975fb6 */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN 124adb54e1ae4670 */
string os__dir(string path) {
}

/* V3CACHE_FN_END 124adb54e1ae4670 */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN 8b18a730aa6b4e87 */
u64 os__file_size(string path) {
}

/* V3CACHE_FN_END 8b18a730aa6b4e87 */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN 1d63643351696d2f */
void os__init(void) {
}

/* V3CACHE_FN_END 1d63643351696d2f */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN ffce97741f33c869 */
bool os__is_dir(string path) {
}

/* V3CACHE_FN_END ffce97741f33c869 */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN 72d9112ba844e90c */
bool os__is_file(string path) {
}

/* V3CACHE_FN_END 72d9112ba844e90c */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN c71a2b83cb8a06da */
bool os__is_link(string path) {
}

/* V3CACHE_FN_END c71a2b83cb8a06da */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN 6f82e14a070929bb */
string os__join_path(string base, Array dirs) {
}

/* V3CACHE_FN_END 6f82e14a070929bb */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN f8be078e57d48154 */
string os__join_path_single(string base, string elem) {
}

/* V3CACHE_FN_END f8be078e57d48154 */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN 6b2ff3d0f3b00e66 */
__v_result_Array os__ls(string path) {
	return (__v_result_Array){.ok = true};
}

/* V3CACHE_FN_END 6b2ff3d0f3b00e66 */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN bc5bc899ebc555ad */
__v_result_os__File os__open(string path) {
	return (__v_result_os__File){.ok = true};
}

/* V3CACHE_FN_END bc5bc899ebc555ad */
/* V3CACHE_MODULE os */
/* V3CACHE_FN_BEGIN 46123f9cb798d592 */
__v_result os__walk_dir(string root, _fn_ptr_24927a217aab3552 cb) {
	return (__v_result){.ok = true};
}

/* V3CACHE_FN_END 46123f9cb798d592 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 18fa77825f0c6198 */
VNORETURN void panic_debug(i64 line_no, string file, string mod, string fn_name, string s) {
}

/* V3CACHE_FN_END 18fa77825f0c6198 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1dcf338e0af9d843 */
void panic_frame_done(void* frame) {
}

/* V3CACHE_FN_END 1dcf338e0af9d843 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c2599dfa302e9d8e */
void panic_frame_pop(void* frame) {
}

/* V3CACHE_FN_END c2599dfa302e9d8e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b893667344f55cc3 */
void panic_frame_push(void* frame) {
}

/* V3CACHE_FN_END b893667344f55cc3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 65f437e709eb3bc0 */
void panic_frame_relink(void* frame) {
}

/* V3CACHE_FN_END 65f437e709eb3bc0 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c81917daccc4a2f3 */
void panic_frames_reset(void) {
}

/* V3CACHE_FN_END c81917daccc4a2f3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 91c338ee2f84a9a7 */
__v_option_string panic_recover_frame(void* frame) {
	return (__v_option_string){.ok = true};
}

/* V3CACHE_FN_END 91c338ee2f84a9a7 */
/* V3CACHE_MODULE main */
/* V3CACHE_FN_BEGIN 6620d6d775eb38c4 */
void print_groups(Array groups) {
	if (groups.len == 0) {
		println(_v3_lit_19_72be4e8eaa4a0d66);
		return;
	}
	u64 wasted = (u64)(0);
	{
		i64 __for_idx_0 = 0;
		for (; __for_idx_0 < groups.len; __for_idx_0++) {
			main__DupeGroup g = *(main__DupeGroup*)(array_get(groups, __for_idx_0));
			println(({ string __v3_internal_symbol_join_0[3]; __v3_internal_symbol_join_0[0] = u64__str(g.size); __v3_internal_symbol_join_0[1] = _v3_lit_8_86a8111759a98db0; __v3_internal_symbol_join_0[2] = g.hash; string_plus_many(3, __v3_internal_symbol_join_0); }));
			{
				i64 __for_idx_1 = 0;
				for (; __for_idx_1 < g.files.len; __for_idx_1++) {
					string f = *(string*)(array_get(g.files, __for_idx_1));
					println(string__plus(_v3_lit_4_1b0d87aaaffd5273, f));
				}
			}
			wasted += g.size * (u64)(g.files.len - 1);
		}
	}
	println(({ string __v3_internal_symbol_join_1[4]; __v3_internal_symbol_join_1[0] = int__str(groups.len); __v3_internal_symbol_join_1[1] = _v3_lit_11_b9c2da042e7ff834; __v3_internal_symbol_join_1[2] = u64__str(wasted); __v3_internal_symbol_join_1[3] = _v3_lit_18_a9c26cb051ae2e6c; string_plus_many(4, __v3_internal_symbol_join_1); }));
}

/* V3CACHE_FN_END 6620d6d775eb38c4 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 2fdc425577a0b142 */
void println(string s) {
}

/* V3CACHE_FN_END 2fdc425577a0b142 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN cf139a8adca696bf */
string ptr_str(void* ptr) {
}

/* V3CACHE_FN_END cf139a8adca696bf */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1fc64375d08dbcc6 */
Array rune__bytes(u32 c) {
}

/* V3CACHE_FN_END 1fc64375d08dbcc6 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 157e0930549dcbb2 */
string rune__str(u32 c) {
}

/* V3CACHE_FN_END 157e0930549dcbb2 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4d595868eee5ec32 */
u32 rune__to_lower(u32 c) {
}

/* V3CACHE_FN_END 4d595868eee5ec32 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN eb69a9589f436d12 */
string strconv__Dec32__get_string_32(strconv__Dec32 d, bool neg, i64 i_n_digit, i64 i_pad_digit) {
}

/* V3CACHE_FN_END eb69a9589f436d12 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 1fbead87e9f7a3e6 */
string strconv__Dec64__get_string_64(strconv__Dec64 d, bool neg, i64 i_n_digit, i64 i_pad_digit) {
}

/* V3CACHE_FN_END 1fbead87e9f7a3e6 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN bc445feab02cd3f1 */
string strconv__f32_to_str_l(float f) {
}

/* V3CACHE_FN_END bc445feab02cd3f1 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN fc20de7039f70f30 */
string strconv__format_int(i64 n, i64 radix) {
}

/* V3CACHE_FN_END fc20de7039f70f30 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN aefd07a6fd399a57 */
string strconv__format_uint(u64 n, i64 radix) {
}

/* V3CACHE_FN_END aefd07a6fd399a57 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 12178b2c1cde1862 */
string string__all_after(string s, string sub) {
}

/* V3CACHE_FN_END 12178b2c1cde1862 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN cf266a1c6884a26b */
string string__all_after_last(string s, string sub) {
}

/* V3CACHE_FN_END cf266a1c6884a26b */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 442227c2c6f35373 */
string string__all_before(string s, string sub) {
}

/* V3CACHE_FN_END 442227c2c6f35373 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 83a5bf04b754f564 */
string string__all_before_last(string s, string sub) {
}

/* V3CACHE_FN_END 83a5bf04b754f564 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ca87241e049f0919 */
u8 string__at(string s, i64 idx) {
}

/* V3CACHE_FN_END ca87241e049f0919 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN d06e474ad7f82ad7 */
u8 string__at_i64(string s, i64 idx) {
}

/* V3CACHE_FN_END d06e474ad7f82ad7 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4d4ca37c7cc1a4f1 */
u8 string__at_ni(string s, i64 idx) {
}

/* V3CACHE_FN_END 4d4ca37c7cc1a4f1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 2126c729f585121b */
u8 string__at_u64(string s, u64 idx) {
}

/* V3CACHE_FN_END 2126c729f585121b */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 75f50d4a1b5888eb */
string string__clone(string a) {
}

/* V3CACHE_FN_END 75f50d4a1b5888eb */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e7dfe01fc85e7d5c */
bool string__eq(string s, string a) {
}

/* V3CACHE_FN_END e7dfe01fc85e7d5c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1fc94156f9757bb0 */
void string__free(string* s) {
}

/* V3CACHE_FN_END 1fc94156f9757bb0 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 71389f7059778c0f */
bool string__is_capital(string s) {
}

/* V3CACHE_FN_END 71389f7059778c0f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e9bb6da69ec84748 */
bool string__lt(string s, string a) {
}

/* V3CACHE_FN_END e9bb6da69ec84748 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e97b6da69e926353 */
string string__plus(string s, string a) {
}

/* V3CACHE_FN_END e97b6da69e926353 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6979dc6655c087d9 */
string string__substr(string s, i64 start, i64 _end) {
}

/* V3CACHE_FN_END 6979dc6655c087d9 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ce7a7780bbaf03b1 */
string string__substr_ni(string s, i64 _start, i64 _end) {
}

/* V3CACHE_FN_END ce7a7780bbaf03b1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ff8de8cbbd087d3b */
string string__to_lower_ascii(string s) {
}

/* V3CACHE_FN_END ff8de8cbbd087d3b */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 55e420860c56938d */
string string_plus_many(i64 data_len, string* input_base) {
}

/* V3CACHE_FN_END 55e420860c56938d */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN 6315072b2f458f3c */
void strings__Builder__free(Array* b) {
}

/* V3CACHE_FN_END 6315072b2f458f3c */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN 4cb298fd227638ed */
string strings__Builder__str(Array* b) {
}

/* V3CACHE_FN_END 4cb298fd227638ed */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN 62d7315343d94766 */
void strings__Builder__write_ptr(Array* b, u8* ptr, i64 len) {
}

/* V3CACHE_FN_END 62d7315343d94766 */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN d57552e50f1b7323 */
void strings__Builder__write_runes(Array* b, Array runes) {
}

/* V3CACHE_FN_END d57552e50f1b7323 */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN 7b3631204f470bc1 */
inline void strings__Builder__write_string(Array* b, string s) {
}

/* V3CACHE_FN_END 7b3631204f470bc1 */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN 926f5c2762c9c41 */
inline void strings__Builder__write_u8(Array* b, u8 data) {
}

/* V3CACHE_FN_END 926f5c2762c9c41 */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN 7766e7ae0e292c85 */
Array strings__new_builder(i64 initial_size) {
}

/* V3CACHE_FN_END 7766e7ae0e292c85 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 398fab20ecd6de6f */
string tos(u8* s, i64 len) {
}

/* V3CACHE_FN_END 398fab20ecd6de6f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 9c23ae5817afc995 */
inline string u64__str(u64 nn) {
}

/* V3CACHE_FN_END 9c23ae5817afc995 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ae906498b215a0f3 */
inline bool u8__is_capital(u8 c) {
}

/* V3CACHE_FN_END ae906498b215a0f3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN bf255c2e6a3f972f */
inline bool u8__is_letter(u8 c) {
}

/* V3CACHE_FN_END bf255c2e6a3f972f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 48ce9eb5f1b63e39 */
string u8__vstring(u8* bp) {
}

/* V3CACHE_FN_END 48ce9eb5f1b63e39 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c2a309e6f13cd896 */
string u8__vstring_with_len(u8* bp, i64 len) {
}

/* V3CACHE_FN_END c2a309e6f13cd896 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 5917b26ff1b85c1 */
VNORETURN void v_exit(i64 code) {
}

/* V3CACHE_FN_END 5917b26ff1b85c1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 313d167dfad375d1 */
inline i64 v_fixed_index(i64 i, i64 len) {
}

/* V3CACHE_FN_END 313d167dfad375d1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 78c8497c04d427ef */
inline i64 v_fixed_index_i64(i64 i, i64 len) {
}

/* V3CACHE_FN_END 78c8497c04d427ef */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e45140c9afd57269 */
inline i64 v_fixed_index_ni(i64 i, i64 len) {
}

/* V3CACHE_FN_END e45140c9afd57269 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b43848d521a648c3 */
inline i64 v_fixed_index_u64(u64 i, i64 len) {
}

/* V3CACHE_FN_END b43848d521a648c3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7fbc02dd9ab74c2f */
void v_free(void* ptr) {
}

/* V3CACHE_FN_END 7fbc02dd9ab74c2f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 392930a221e604d */
u8* v_malloc(ptrdiff_t n) {
}

/* V3CACHE_FN_END 392930a221e604d */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 888b7553102ad5d0 */
VNORETURN void v_panic(string s) {
}

/* V3CACHE_FN_END 888b7553102ad5d0 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6c7d461dc6a16b23 */
inline i64 v_slice_index_i64(i64 i) {
}

/* V3CACHE_FN_END 6c7d461dc6a16b23 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 310d46c4a9cf4a4f */
inline i64 v_slice_index_u64(u64 i) {
}

/* V3CACHE_FN_END 310d46c4a9cf4a4f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 95fc587be898cf3c */
inline void* vmemcpy(void* dest, void* const_src, ptrdiff_t n) {
}

/* V3CACHE_FN_END 95fc587be898cf3c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 670999719c676408 */
Array voidptr__vbytes(void* data, i64 len) {
}

/* V3CACHE_FN_END 670999719c676408 */
/* V3CACHE_MODULE main */
/* V3CACHE_FN_BEGIN 959136e94371b59e */
void walk_dir(string dir, Array* out) {
	__v_result_Array __or_opt_0 = os__ls(dir);
	Array __or_val_1 = {0};
	if (__or_opt_0.ok) {
		__or_val_1 = __or_opt_0.value;
	} else {
		IError err = __or_opt_0.err;
		return;
	}
	Array entries = __or_val_1;
	{
		i64 __for_idx_2 = 0;
		for (; __for_idx_2 < entries.len; __for_idx_2++) {
			string entry = *(string*)(array_get(entries, __for_idx_2));
			string full = os__join_path_single(dir, entry);
			if (os__is_dir(full)) {
				if (os__is_link(full)) {
					continue;
				}
				walk_dir(full, out);
			} else if (os__is_file(full)) {
				u64 size = (u64)(os__file_size(full));
				main__ScannedFile __arr_val_3 = (main__ScannedFile){.path = full, .size = size};
				array_push(out, &__arr_val_3);
			}
		}
	}
}

/* V3CACHE_FN_END 959136e94371b59e */
/* V3CACHE_MODULE main */
/* V3CACHE_FN_BEGIN 7d3fbf665dfc23ca */
Array walk_files(Array dirs) {
	Array out = array_new(	sizeof(main__ScannedFile), 0, 0);
	{
		i64 __for_idx_0 = 0;
		for (; __for_idx_0 < dirs.len; __for_idx_0++) {
			string dir = *(string*)(array_get(dirs, __for_idx_0));
			walk_dir(dir, &out);
		}
	}
	return out;
}

/* V3CACHE_FN_END 7d3fbf665dfc23ca */
// THE END.
/* V3CACHE_BODY_END */
