noinst_LTLIBRARIES = libstuff.la

libstuff_la_CFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/include/foreign -D__DARWIN_UNIX03 $(WARNINGS) $(LTO_DEF) -DPROGRAM_PREFIX="\"$(PROGRAM_PREFIX)\"" $(ENDIAN_FLAG)

libstuff_la_LDFLAGS = $(FTS_LIB)

libstuff_la_SOURCES =  \
	allocate.c  \
	apple_version.c  \
	arch.c  \
	arch_usage.c  \
	bytesex.c  \
	port.c  \
	errors.c  \
	fatals.c  \
	diagnostics.c \
	rnd.c  \
	seg_addr_table.c  \
	align.c \
	write64.c
