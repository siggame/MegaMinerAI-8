GENDIR=../../client/c
TOCOPY=$(wildcard *.h *.cpp)
all: local
	make -C $(GENDIR) clean
	cp -r $(GENDIR)/* local/
	cp $(TOCOPY) local/
	make -C local
	cp local/client .

local:
	mkdir local
clean:
	make -C local clean
	rm -f client
extra_clean: clean
	rm -rf *~
	rm -rf *.gamelog
	
	
