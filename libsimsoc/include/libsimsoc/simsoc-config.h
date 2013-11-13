#ifndef _LIBSIMSOC_SIMSOC_CONFIG_H
#define _LIBSIMSOC_SIMSOC_CONFIG_H 1
 
/* libsimsoc/simsoc-config.h. Generated automatically at end of configure. */
/* libsimsoc/config.h.  Generated from config.h.in by configure.  */
/* libsimsoc/config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Log GDB dialog with client debugger */
/* #undef DEBUG_GDB_PROTOCOL */

/* Define to 1 if you have the <byteswap.h> header file. */
#ifndef SIMSOC_HAVE_BYTESWAP_H
#define SIMSOC_HAVE_BYTESWAP_H 1
#endif

/* Define to 1 if you have the <CoreFoundation/CoreFoundation.h> header file.
   */
/* #undef HAVE_COREFOUNDATION_COREFOUNDATION_H */

/* Define to 1 if you have the <elf.h> header file. */
#ifndef SIMSOC_HAVE_ELF_H
#define SIMSOC_HAVE_ELF_H 1
#endif

/* Define to 1 if you have the `fls' function. */
/* #undef HAVE_FLS */

/* Define to 1 if mmap() accepts __attribute__ ((hot)). */
#ifndef SIMSOC_HAVE_HOT_COLD_ATTR
#define SIMSOC_HAVE_HOT_COLD_ATTR 1
#endif

/* Define to 1 if you have the <inttypes.h> header file. */
#ifndef SIMSOC_HAVE_INTTYPES_H
#define SIMSOC_HAVE_INTTYPES_H 1
#endif

/* Define 1 if Linux TUN/TAP interface is available */
#ifndef SIMSOC_HAVE_LINUXTAP
#define SIMSOC_HAVE_LINUXTAP 1
#endif

/* Define to 1 if LLVM 2.7 and llvm-g++ are available. */
/* #undef HAVE_LLVM */

/* Define to 1 whether LLVM defines llvm::DwarfExceptionHandling. */
/* #undef HAVE_LLVM_DWARFEXCEPTIONHANDLING */

/* Define to 1 if you have the loff_t type. */
#ifndef SIMSOC_HAVE_LOFF_T
#define SIMSOC_HAVE_LOFF_T 1
#endif

/* Define to 1 if mmap() accepts MAP_ANON. */
#ifndef SIMSOC_HAVE_MAP_ANON
#define SIMSOC_HAVE_MAP_ANON 1
#endif

/* Define to 1 if mmap() accepts MAP_ANONYMOUS. */
#ifndef SIMSOC_HAVE_MAP_ANONYMOUS
#define SIMSOC_HAVE_MAP_ANONYMOUS 1
#endif

/* Define to 1 if you have the <memory.h> header file. */
#ifndef SIMSOC_HAVE_MEMORY_H
#define SIMSOC_HAVE_MEMORY_H 1
#endif

/* Define if you have the mpfr library */
/* #undef HAVE_MPFR */

/* Define 1 if libpcap is available */
/* #undef HAVE_PCAP */

/* Define to 1 if you have the <stdint.h> header file. */
#ifndef SIMSOC_HAVE_STDINT_H
#define SIMSOC_HAVE_STDINT_H 1
#endif

/* Define to 1 if you have the <stdlib.h> header file. */
#ifndef SIMSOC_HAVE_STDLIB_H
#define SIMSOC_HAVE_STDLIB_H 1
#endif

/* Define to 1 if you have the <strings.h> header file. */
#ifndef SIMSOC_HAVE_STRINGS_H
#define SIMSOC_HAVE_STRINGS_H 1
#endif

/* Define to 1 if you have the <string.h> header file. */
#ifndef SIMSOC_HAVE_STRING_H
#define SIMSOC_HAVE_STRING_H 1
#endif

/* Define to 1 if you have the <systemc> header file. */
#ifndef SIMSOC_HAVE_SYSTEMC
#define SIMSOC_HAVE_SYSTEMC 1
#endif

/* Define to 1 if you have the <sys/stat.h> header file. */
#ifndef SIMSOC_HAVE_SYS_STAT_H
#define SIMSOC_HAVE_SYS_STAT_H 1
#endif

/* Define to 1 if you have the <sys/types.h> header file. */
#ifndef SIMSOC_HAVE_SYS_TYPES_H
#define SIMSOC_HAVE_SYS_TYPES_H 1
#endif

/* Define to 1 if you have the <tlm.h> header file. */
#ifndef SIMSOC_HAVE_TLM_H
#define SIMSOC_HAVE_TLM_H 1
#endif

/* Define to 1 if you have the <tlm_h/tlm_sockets/tlm_initiator_socket.h>
   header file. */
#ifndef SIMSOC_HAVE_TLM_H_TLM_SOCKETS_TLM_INITIATOR_SOCKET_H
#define SIMSOC_HAVE_TLM_H_TLM_SOCKETS_TLM_INITIATOR_SOCKET_H 1
#endif

/* Define to 1 if you have the <unistd.h> header file. */
#ifndef SIMSOC_HAVE_UNISTD_H
#define SIMSOC_HAVE_UNISTD_H 1
#endif

/* Name of package */
#ifndef SIMSOC_PACKAGE
#define SIMSOC_PACKAGE "simsoc"
#endif

/* Define to the address where bug reports for this package should be sent. */
#ifndef SIMSOC_PACKAGE_BUGREPORT
#define SIMSOC_PACKAGE_BUGREPORT "simsoc@formes.asia"
#endif

/* Define to the full name of this package. */
#ifndef SIMSOC_PACKAGE_NAME
#define SIMSOC_PACKAGE_NAME "simsoc"
#endif

/* Define to the full name and version of this package. */
#ifndef SIMSOC_PACKAGE_STRING
#define SIMSOC_PACKAGE_STRING "simsoc 0.7.1"
#endif

/* Define to the one symbol short name of this package. */
#ifndef SIMSOC_PACKAGE_TARNAME
#define SIMSOC_PACKAGE_TARNAME "simsoc"
#endif

/* Define to the home page for this package. */
#ifndef SIMSOC_PACKAGE_URL
#define SIMSOC_PACKAGE_URL ""
#endif

/* Define to the version of this package. */
#ifndef SIMSOC_PACKAGE_VERSION
#define SIMSOC_PACKAGE_VERSION "0.7.1"
#endif

/* Define to 1 if you have the ANSI C header files. */
#ifndef SIMSOC_STDC_HEADERS
#define SIMSOC_STDC_HEADERS 1
#endif

/* Version number of package */
#ifndef SIMSOC_VERSION
#define SIMSOC_VERSION "0.7.1"
#endif

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif
 
/* once: _LIBSIMSOC_SIMSOC_CONFIG_H */
#endif
