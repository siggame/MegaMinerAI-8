GENDIR=../../codegen/output/c
TOCOPY=$(wildcard *.h *.cpp)
all:
	cp $(TOCOPY) $(GENDIR)
	make -C $(GENDIR)
	cp $(GENDIR)/client .

clean:
	rm -f client
	make -C $(GENDIR) clean
extra_clean: clean
	rm -rf *~
	rm -rf *.gamelog
	
	
