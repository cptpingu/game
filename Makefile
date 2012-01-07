include Makefile.rules

all:
	cd src && $(MAKE) && cd ..

clean:
	rm -f *.o *.~ *.core *.Dstore *.log *.ml *.err *\#*
	cd src && $(MAKE) clean && cd ..
	cd bonus && $(MAKE) clean && cd ..

distclean: clean
	cd src && $(MAKE) distclean && cd ..
	rm -f $(EXE) Makefile.rules Makefile.deps $(EXE)_bonus


rights:
	chmod 640 AUTHORS
	chmod 750 configure
	chmod 640 README
	chmod 640 TODO
	chmod 640 ChangeLog
	find . -type d -print -exec chmod 750 {} \;
	find . -name "*.[ch]" -print -exec chmod 640 {} \;
	find . -name "*.cc" -print -exec chmod 640 {} \;
	find . -name "*.hh" -print -exec chmod 640 {} \;
	find . -name "*.sh" -print -exec chmod 750 {} \;
	find . -name "Makefile" -print -exec chmod 750 {} \;

dist: distclean rights
	rm -f *.tar.bz2 && \
	tar pcjvf $(LOGIN)-$(PROJ).tar.bz2 * && \
	chmod 640 $(LOGIN)-$(PROJ).tar.bz2 &&
	rm -Rf $(LOGIN)-$(PROJ) && mkdir $(LOGIN)-$(PROJ) &&
	chmod 750 $(LOGIN)-$(PROJ) &&
	mv $(LOGIN)-$(PROJ).tar.bz2 $(LOGIN)-$(PROJ) && \
	cd $(LOGIN)-$(PROJ) && tar pxjvf $(LOGIN)-$(PROJ).tar.bz2 && \
	rm -f *.tar.bz2 && cd .. && \
	tar pcjvf $(LOGIN)-$(PROJ).tar.bz2  $(LOGIN)-$(PROJ) &&
	chmod 640 $(LOGIN)-$(PROJ).tar.bz2 &&
	rm -Rf  $(LOGIN)-$(PROJ)

tar: dist
