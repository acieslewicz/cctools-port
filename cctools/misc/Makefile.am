bin_PROGRAMS =  \
	lipo

LDADD =  \
    $(top_builddir)/libmacho/libmacho.la \
	$(top_builddir)/libstuff/libstuff.la \
	$(MATH_LIB) \
	$(REALLOCF_LIB)

AM_CFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/include/foreign -I$(top_srcdir)/libstuff $(WARNINGS) $(LTO_DEF) -D__DARWIN_UNIX03 $(ENDIAN_FLAG)

lipo_SOURCES = lipo.c

