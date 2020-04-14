
// util.h

#ifndef UTIL_H
#define UTIL_H

// includes

#include <cstdio>

// constants

#undef FALSE
#define FALSE 0

#undef TRUE
#define TRUE 1

#ifdef DEBUG
#  undef DEBUG
#  define DEBUG TRUE
#else
#  define DEBUG FALSE
#endif

#ifdef _MSC_VER
#  define S64_FORMAT "%I64d"
#  define U64_FORMAT "%016I64X"
#else
#  define S64_FORMAT "%lld"
#  define U64_FORMAT "%016llX"
#endif

// macros

#if defined(_MSC_VER) && !defined(__MINGW32__)
#  define S64(u) (u##i64)
#  define U64(u) (u##ui64)
#else
#  define S64(u) (u##LL)
#  define U64(u) (u##ULL)
#endif

#undef ASSERT
#if DEBUG
#  define ASSERT(a) { if (!(a)) my_fatal("file \"%s\", line %d, assertion \"" #a "\" failed\n",__FILE__,__LINE__); }
#else
#  define ASSERT(a)
#endif

#if !defined(IS_32) && !defined(IS_64)
#  ifdef __GNUC__
#     define IS_UNIX TRUE
#     ifdef __x86_64__
#        define IS_64 TRUE
#     else
#        define IS_32 TRUE
#     endif
#  endif
#  if defined(_WIN32) || defined(_WIN64)
#     undef IS_UNIX
#     define IS_WINDOWS TRUE
#     ifdef _WIN64
#        define IS_64 TRUE
#     else
#        define IS_32 TRUE
#     endif
#  endif
#endif

// types

typedef signed char sint8;
typedef unsigned char uint8;

typedef signed short sint16;
typedef unsigned short uint16;

typedef signed int sint32;
typedef unsigned int uint32;

#ifdef _MSC_VER
  typedef signed __int64 sint64;
  typedef unsigned __int64 uint64;
#else
  typedef signed long long int sint64;
  typedef unsigned long long int uint64;
#endif

#ifndef _WIN32
#include <pthread.h>
typedef struct {
    int volatile value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} my_sem_t;
#endif

struct my_timer_t {
   double start_real;
   double start_cpu;
   double elapsed_real;
   double elapsed_cpu;
   bool running;
};

// functions

extern void   util_init             ();

extern void   my_random_init        ();
extern int    my_random             (int n);

extern sint64 my_atoll              (const char string[]);

extern int    my_round              (double x);

extern void * my_malloc             (uint64 size);
extern void   my_free               (void * address);

extern void   my_fatal              (const char format[], ...);

extern bool   my_file_read_line     (FILE * file, char string[], int size);

extern bool   my_string_empty       (const char string[]);
extern bool   my_string_equal       (const char string_1[], const char string_2[]);
extern char * my_strdup             (const char string[]);

extern void   my_string_clear       (const char * * variable);
extern void   my_string_set         (const char * * variable, const char string[]);

extern void   my_timer_reset        (my_timer_t * timer);
extern void   my_timer_start        (my_timer_t * timer);
extern void   my_timer_stop         (my_timer_t * timer);

extern double my_timer_elapsed_real (const my_timer_t * timer);
extern double my_timer_elapsed_cpu  (const my_timer_t * timer);
extern double my_timer_cpu_usage    (const my_timer_t * timer);

#ifndef _WIN32
extern void my_sem_init(my_sem_t *sem, int value);
extern void my_sem_post(my_sem_t *sem);
extern void my_sem_wait(my_sem_t *sem);
#endif

#endif // !defined UTIL_H

// end of util.h

