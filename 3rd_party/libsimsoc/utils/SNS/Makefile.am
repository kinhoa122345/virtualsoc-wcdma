##
## SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
## LGPL license version 3
##

bin_PROGRAMS = simsoc_sns

simsoc_sns_SOURCES = \
	../../libsimsoc/network/poll.cpp \
	../../libsimsoc/network/pcaplog.cpp \
	../../libsimsoc/network/ethernet/ether-address.cpp \
	../../libsimsoc/network/ethernet/ether-buffer.cpp \
	../../libsimsoc/network/ethernet/arch/ethtr-mcast.cpp \
	../../libsimsoc/network/ethernet/arch/ethtr-null.cpp \
	../../libsimsoc/network/ethernet/ether-transport.cpp \
	simsoc_sns.cpp

if LINUXTAP
simsoc_sns_SOURCES += ../../libsimsoc/network/ethernet/arch/ethtr-linuxtap.cpp
endif

if PCAP
simsoc_sns_SOURCES += ../../libsimsoc/network/ethernet/arch/ethtr-pcap.cpp
endif

simsoc_sns_CPPFLAGS = -I$(top_srcdir) $(PCAP_CFLAGS)
simsoc_sns_LDFLAGS  = $(PCAP_LIBS)
