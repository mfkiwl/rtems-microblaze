rtems_tests_PROGRAMS = spmrsp01
spmrsp01_SOURCES = init.c

dist_rtems_tests_DATA = spmrsp01.scn spmrsp01.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spmrsp01_OBJECTS)
LINK_LIBS = $(spmrsp01_LDLIBS)

spmrsp01$(EXEEXT): $(spmrsp01_OBJECTS) $(spmrsp01_DEPENDENCIES)
	@rm -f spmrsp01$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
