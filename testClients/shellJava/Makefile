GENDIR=../../client/
TOCOPY=$(wildcard *.java)
all: local
	make -C $(GENDIR)/java clean
	cp -r $(GENDIR)/* local/
	cp $(TOCOPY) local/java
	make -C local/java

local:
	mkdir local

clean:
	make -C local clean
	rm -f client
extra_clean: clean
	rm -rf *~
	rm -rf *.gamelog

