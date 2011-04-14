GENDIR=../../client/c
TOCOPY=$(wildcard *.h *.cpp)
all: 
	make -C $(GENDIR) clean
	cp -r $(GENDIR)/* local/
	cp $(TOCOPY) local/
	make -C local
	cp local/client .

clean:
	make -C local clean
	rm -f client
extra_clean: clean
	rm -rf *~
	rm -rf *.gamelog
	
	
