/* libsimsoc/config.h.  Generated from config.h.in by configure.  */
/* libsimsoc/config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Log GDB dialog with client debugger */
/* #undef DEBUG_GDB_PROTOCOL */

/* Define to 1 if you have the <byteswap.h> header file. */
#define HAVE_BYTESWAP_H 1

/* Define to 1 if you have the <CoreFoundation/CoreFoundation.h> header file.
   */
/* #undef HAVE_COREFOUNDATION_COREFOUNDATION_H */

/* Define to 1 if you have the <elf.h> header file. */
#define HAVE_ELF_H 1

/* Define to 1 if you have the `fls' function. */
/* #undef HAVE_FLS */

/* Define to 1 if mmap() accepts __attribute__ ((hot)). */
#define HAVE_HOT_COLD_ATTR 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define 1 if Linux TUN/TAP interface is available */
#define HAVE_LINUXTAP 1

/* Define to 1 if LLVM 2.7 and llvm-g++ are available. */
/* #undef HAVE_LLVM */

/* Define to 1 whether LLVM defines llvm::DwarfExceptionHandling. */
/* #undef HAVE_LLVM_DWARFEXCEPTIONHANDLING */

/* Define to 1 if you have the loff_t type. */
#define HAVE_LOFF_T 1

/* Define to 1 if mmap() accepts MAP_ANON. */
#define HAVE_MAP_ANON 1

/* Define to 1 if mmap() accepts MAP_ANONYMOUS. */
#define HAVE_MAP_ANONYMOUS 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define if you have the mpfr library */
/* #undef HAVE_MPFR */

/* Define 1 if libpcap is available */
/* #undef HAVE_PCAP */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <systemc> header file. */
#define HAVE_SYSTEMC 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <tlm.h> header file. */
#define HAVE_TLM_H 1

/* Define to 1 if you have the <tlm_h/tlm_sockets/tlm_initiator_socket.h>
   header file. */
#define HAVE_TLM_H_TLM_SOCKETS_TLM_INITIATOR_SOCKET_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Name of package */
#define PACKAGE "simsoc"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "simsoc@formes.asia"

/* Define to the full name of this package. */
#define PACKAGE_NAME "simsoc"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "simsoc 0.7.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "simsoc"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.7.1"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.7.1"

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
