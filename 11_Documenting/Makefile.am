SUBDIRS = src po man
ACLOCAL_AMFLAGS = -I m4


if BUILD_DOXYGEN

DOC_SRC_DIR = $(top_srcdir)/doc
DOC_BUILD_DIR = $(top_srcdir)/doc_build

doc: $(DOC_SRC_DIR)/help_generated.txt $(DOC_SRC_DIR)/mainpage.dox
	doxygen $(top_srcdir)/Doxyfile

$(DOC_SRC_DIR)/help_generated.txt: src/guesser
	mkdir -p $(DOC_SRC_DIR)
	LANG=en_US.UTF-8 ./src/guesser --help > $(DOC_SRC_DIR)/help_generated.txt

$(DOC_SRC_DIR)/mainpage.dox: doc/mainpage.dox.in $(DOC_SRC_DIR)/help_generated.txt
	mkdir -p $(DOC_SRC_DIR)
	cp doc/mainpage.dox.in $(DOC_SRC_DIR)/mainpage.dox

endif

maintainer-clean-local:
	rm -rf ABOUT-NLS configure config.* autom4te.cache \
	Makefile Makefile.in aclocal.m4 ltmain.sh m4 \
	compile install-sh missing depcomp stamp-h1 *~ \
	src/guesser src/*.o src/Makefile src/Makefile.in src/.deps \
	po/*~ po/Makefile.in* po/Makefile po/*quot* po/POTFILES* po/*header* po/Makevars.template po/*pot* \
	doc_build Doxyfile doc/mainpage.dox doc/help_generated.txt doc/man man/Makefile man/Makefile.in

