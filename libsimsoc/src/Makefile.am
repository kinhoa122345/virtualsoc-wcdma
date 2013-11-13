##
## SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
## LGPL license version 3
##

SUBDIRS =  processors/arm/ArmGen

ARMGEN_CPP_FILES = \
   armpi_dpi_int.cpp armpi_dpi_bool.cpp armpi_dpi_mov.cpp \
   armpi_mli_32.cpp armpi_mli_64_int.cpp armpi_mli_64_uint.cpp \
   armpi_loadstore_admode2_9.cpp \
   armpi_loadstore_admode2_9_zero.cpp \
   armpi_loadstore_admode2_3.cpp \
   armpi_loadstore_admode3_6.cpp \
   armpi_ldr_pc_admode2_9.cpp \
   armpi_swp.cpp \
   armpi_b_h.cpp armpi_b_l.cpp armpi_b_reg.cpp \
   armpi_clz.cpp \
   armpi_swi.cpp \
   armpi_ldmstm_pc.cpp armpi_ldmstm_nopc.cpp \
   armpi_mrs.cpp armpi_msr.cpp
ARMGEN_HPP_FILES = $(ARMGEN_CPP_FILES:%.cpp=%.hpp)

lib_LIBRARIES = libsimsoc.a

nodist_libsimsoc_a_SOURCES = \
    arm_decode.cpp thumb_decode.cpp $(ARMGEN_CPP_FILES)
BUILT_SOURCES = \
    arm_decode.cpp thumb_decode.cpp $(ARMGEN_CPP_FILES)
CLEANFILES = \
    arm_decode.cpp thumb_decode.cpp $(ARMGEN_CPP_FILES) $(ARMGEN_HPP_FILES) armgen_done
libsimsoc_a_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir) -I$(top_builddir) \
	               -DABS_TOP_SRCDIR="\"$(abs_top_srcdir)\"" \
                       -DABS_TOP_BUILDDIR="\"$(abs_top_builddir)\"" \
                       -DBINDIR="\"$(bindir)\""

EXTRA_DIST = $(srcdir)/processors/arm_v6/simlight/slv6_iss_arm_decode_store.c\
			 $(srcdir)/processors/arm_v6/simlight/slv6_iss_thumb_decode_store.c \
			 $(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.cold.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.hot.c \
			 $(srcdir)/processors/arm_v6/simlight/slv6_iss_grouped.cold.c \
			 $(srcdir)/processors/arm_v6/simlight/slv6_iss_grouped.hot.c \
			$(srcdir)/processors/arm_v6/arm_v6_llvm_lib.cpp \
			$(srcdir)/processors/ppc/ppc_llvm_lib.cpp \
			 $(srcdir)/processors/arm_v6/simlight/slv6_iss.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_condition.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_math.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_mode.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_processor.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_status_register.c

#=====================================================================
# Tools
#=====================================================================

libsimsoc_a_SOURCES = \
    module.cpp \
    context.cpp \
    command_line.cpp \
    display.cpp \
    io.cpp \
    random.cpp \
    \
    components/elf_loader.cpp \
    \
    processors/common.cpp \
    processors/iss.cpp \
    processors/iss.tpp \
    processors/mmu.cpp \
    processors/mmu.tpp \
    processors/tlb.cpp \
    processors/tlb.tpp \
    processors/processor.cpp \
    processors/processor_base.cpp \
    processors/processor_base.hpp \
    processors/llvm_gen_parameters.hpp \
    processors/llvm_gen_parameters.cpp \
    \
    processors/arm/arm_condition.cpp \
    processors/arm/arm_coproc.cpp \
    processors/arm/arm_cpu.cpp \
    processors/arm/arm_debugger.hpp \
    processors/arm/arm_debugger.cpp \
    processors/arm/arm_decode.isc \
    processors/arm/arm_dpi.cpp \
    processors/arm/arm_loadstore.cpp \
    processors/arm/arm_mmu.cpp \
    processors/arm/arm_processor.cpp \
    processors/arm/arm_shift.cpp \
    processors/arm/arm_status_register.cpp \
    processors/arm/arm_systemcontrol_coproc.cpp \
    processors/arm/arm_thumb_pi.hpp \
    processors/arm/arm_thumb_pi.cpp \
    processors/arm/arm_tlb.cpp \
    processors/arm/arm_translation_page.cpp \
    processors/arm/armis.cpp \
    processors/arm/armis_visitor.hpp \
    processors/arm/armis_visitor.cpp \
    processors/arm/armis_dyntrans.hpp \
    processors/arm/armis_dyntrans.cpp \
    processors/arm/armis_arithmetic.hpp \
    processors/arm/armis_arithmetic.cpp \
    processors/arm/armis_arithmetic.tpp \
    processors/arm/armis_control.hpp \
    processors/arm/armis_control.cpp \
    processors/arm/armis_coproc.hpp \
    processors/arm/armis_coproc.cpp \
    processors/arm/armis_loadstore.hpp \
    processors/arm/armis_loadstore.cpp \
    processors/arm/armis_loadstore.tpp \
    processors/arm/armis_edsp.hpp \
    processors/arm/armis_edsp.cpp \
    processors/arm/armpi.cpp \
    processors/arm/arm_translate.hpp \
    processors/arm/arm_translate.cpp \
    processors/arm/thumb_decode.isc \
    processors/arm/thumbis_arithmetic.hpp \
    processors/arm/thumbis_arithmetic.cpp \
    processors/arm/thumbis_control.hpp \
    processors/arm/thumbis_control.cpp \
    processors/arm/thumbis_loadstore.hpp \
    processors/arm/thumbis_loadstore.cpp \
    processors/arm/thumb_translate.hpp \
    processors/arm/thumb_translate.cpp \
    \
    processors/arm_v6/arm_v6_processor.cpp \
    processors/arm_v6/arm_v6_debugger.hpp \
    processors/arm_v6/arm_v6_debugger.cpp \
    processors/arm_v6/arm_v6_coproc.cpp \
    processors/arm_v6/arm_v5_systemcontrol_coproc.cpp \
    processors/arm_v6/arm_v5_mmu.cpp \
    processors/arm_v6/arm_v5_tlb.cpp \
    processors/arm_v6/arm_v6_translation_page.cpp \
    processors/arm_v6/arm_v6_dyntrans.hpp \
    processors/arm_v6/arm_v6_dyntrans.cpp \
    processors/arm_v6/simlight/slv6_condition.cpp \
    processors/arm_v6/simlight/slv6_iss.cpp \
    processors/arm_v6/simlight/slv6_iss_expanded.h \
    processors/arm_v6/simlight/slv6_iss_grouped.h \
    processors/arm_v6/simlight/slv6_iss_grouped.hot.cpp \
    processors/arm_v6/simlight/slv6_iss_grouped.cold.cpp \
    processors/arm_v6/simlight/slv6_iss_arm_decode_store.cpp \
    processors/arm_v6/simlight/slv6_iss_thumb_decode_store.cpp \
    processors/arm_v6/simlight/slv6_iss_c_prelude.h \
    processors/arm_v6/simlight/slv6_iss_h_prelude.h \
    processors/arm_v6/simlight/slv6_math.h \
    processors/arm_v6/simlight/slv6_math.cpp \
    processors/arm_v6/simlight/slv6_mode.cpp \
    processors/arm_v6/simlight/slv6_processor.cpp \
    processors/arm_v6/simlight/slv6_status_register.cpp \
    processors/arm_v6/simlight/slv6_iss_printers.cpp \
    processors/arm_v6/arm_v6_printers.cpp \
    \
    tools/debugger/debugger.cpp \
    \
    translation_table.cpp \
    interfaces/RS232.cpp \
    interfaces/tlm.cpp \
    interfaces/float_point_unit.cpp \
    interfaces/endian.cc \
    \
    network/pcaplog.cpp \
    network/poll.cpp \
    network/ethernet/ether-address.cpp \
    network/ethernet/ether-buffer.cpp \
    network/ethernet/ether-transport.cpp \
    network/ethernet/arch/ethtr-mcast.cpp \
    network/ethernet/arch/ethtr-null.cpp

if LINUXTAP
libsimsoc_a_SOURCES += network/ethernet/arch/ethtr-linuxtap.cpp
endif

if PCAP
libsimsoc_a_SOURCES += network/ethernet/arch/ethtr-pcap.cpp
endif

arm_decode.cpp: processors/arm/arm_decode.isc Makefile ../utils/ISC/isc
	../utils/ISC/isc $(srcdir)/processors/arm/arm_decode.isc -o $@

thumb_decode.cpp: processors/arm/thumb_decode.isc Makefile ../utils/ISC/isc
	../utils/ISC/isc $(srcdir)/processors/arm/thumb_decode.isc -o $@

$(ARMGEN_CPP_FILES): Makefile armgen_done

armgen_done: Makefile processors/arm/ArmGen/armgen
	processors/arm/ArmGen/armgen -o armgen_done

processors/arm/ArmGen/armgen: Makefile
	cd processors/arm/ArmGen && $(MAKE)

components/elf_loader.hpp: config.h

################################################################################
if LLVM_COND
libsimsoc_adir=$(datadir)
libsimsoc_a_DATA=ppc_llvm_lib.bc arm_v6_llvm_lib.bc

ppc_llvm_lib.bc: $(srcdir)/processors/ppc/ppc_llvm_lib.cpp libsimsoc_a-ppc_pi.o Makefile
	$(LLVMGXX) -c -emit-llvm $< $(libsimsoc_a_CPPFLAGS) -I $(top_builddir)/libsimsoc -DNDEBUG -O3 -o $@

arm_v6_llvm_lib.hot.bc: $(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.hot.c \
 $(srcdir)/processors/arm_v6/arm_v6_llvm_lib.cpp \
 $(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.h \
 libsimsoc_a-slv6_iss_grouped.hot.o Makefile
	$(LLVMGXX) -c -emit-llvm -I $(top_builddir)/libsimsoc -DNDEBUG \
                   $(libsimsoc_a_CPPFLAGS) -DSLV6_ISS_grouped_H \
                   --include $< $(srcdir)/processors/arm_v6/arm_v6_llvm_lib.cpp \
                   -O3 -o $@

arm_v6_llvm_lib.cold.bc: $(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.cold.c \
 $(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.h \
 libsimsoc_a-slv6_iss_grouped.cold.o Makefile
	$(LLVMGXX) -c -emit-llvm $< $(libsimsoc_a_CPPFLAGS) -DSLV6_ISS_grouped_H \
                   -I $(top_builddir)/libsimsoc -DNDEBUG -O1 -o $@

arm_v6_llvm_lib.bc: arm_v6_llvm_lib.hot.bc arm_v6_llvm_lib.cold.bc
	$(LLVMLINK) $^ -o=$@

CLEANFILES += ppc_llvm_lib.bc arm_v6_llvm_lib.bc \
	arm_v6_llvm_lib.hot.bc arm_v6_llvm_lib.cold.bc

libsimsoc_a_SOURCES+= \
    processors/compil_server.hpp \
    processors/compil_server.tpp \
    processors/ppc/ppc_llvm_generator.hpp \
    processors/ppc/ppc_llvm_generator.cpp \
    processors/arm_v6/arm_v6_llvm_generator.hpp \
    processors/arm_v6/arm_v6_llvm_generator.cpp \
    processors/arm_v6/arm_v6_llvm_server.hpp \
    processors/arm_v6/arm_v6_llvm_server.cpp \
    processors/arm_v6/simlight/slv6_iss-llvm_generator.hpp

endif
