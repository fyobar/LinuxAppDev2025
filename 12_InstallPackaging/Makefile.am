SUBDIRS = src po tests man docs

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = docs/Doxyfile docs/titlepage.dox

.PHONY: docs

if ENABLE_DOCS
SUBDIRS += docs
docs:
	@echo "=== Generating Doxygen documentation ==="
	@echo "DOXYGEN = $(DOXYGEN)"
	@$(DOXYGEN) $(top_srcdir)/docs/Doxyfile
else
docs:
	@echo "Documentation generation is disabled. Run './configure --enable-docs' to enable it."
endif


maintainer-clean-local:
	rm -rf ABOUT-NLS configure config.* autom4te.cache \
	Makefile Makefile.in aclocal.m4 ltmain.sh m4 \
	compile install-sh missing depcomp stamp-h1 *~ \
	src/slot_machine src/*.o src/Makefile src/Makefile.in src/.deps \
	po/*~ po/Makefile.in* po/Makefile po/*quot* po/POTFILES* po/*header* po/Makevars.template po/*pot* \
	test-driver libtool \
    tests/Makefile tests/Makefile.in tests/.deps tests/*.o /tests/*.log tests/*trs tests/test_slot
	docs/Doxyfile dos/mainpage.dox docs/html  docs/man man/Makefile man/Makefile.in 