#ifndef PORTABILITY_H_
#define PORTABILITY_H_

#ifdef __FreeBSD__
#define fdatasync fsync
#define ftruncate64 ftruncate
#define pread64 pread
#define pwrite64 pwrite
#endif

#endif
