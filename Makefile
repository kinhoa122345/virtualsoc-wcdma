RM        = rm -frv
MKDIR     = mkdir -p
CMAKE     = cmake

ifeq ("$(shell which ninja 2> /dev/null)", "")
MAKEPGR   = make
GENERATOR = "Unix Makefiles"
else
MAKEPGR   = ninja
GENERATOR = "Ninja"
endif

BUILDDIR  = build
BINDIR    = bin
LIBDIR    = lib
EXEC      = $(wildcard $(BINDIR)/*)
WAVE      = $(wildcard $(WAVEDIR)/*)

all: $(BUILDDIR)
	@[ -d $< ] && cd $< && $(MAKEPGR)

$(BINDIR) $(LIBDIR):
	@$(MKDIR) $@

$(BUILDDIR):
	@$(MKDIR) $@
	@cd $@ && $(CMAKE) -G $(GENERATOR) .. || (cd .. && $(RM) $@)

run: $(EXEC)
	@sh -c '$(addsuffix ;, $(EXEC))'

clean:
	@[ -d $(BUILDDIR) ] && cd $(BUILDDIR) && $(MAKEPGR) clean

distclean:
	@$(RM) $(BUILDDIR) $(BINDIR) $(WAVEDIR) $(LIBDIR)

.PHONY: run clean distclean all
