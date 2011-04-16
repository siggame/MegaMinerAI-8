GENDIR=../../client/
TOCOPY=$(wildcard *.py)
all: local
	make -C $(GENDIR)/python clean
	cp -r $(GENDIR)/* local/
	cp $(TOCOPY) local/python
	make -C local/python

local:
	mkdir local

clean:
	make -C local clean
	rm -f client
extra_clean: clean
	rm -rf *~
	rm -rf *.gamelog

