GENDIR=../../client/java
TOCOPY=$(wildcard *.java)
all:
	cp $(TOCOPY) $(GENDIR)
	make -C $(GENDIR)

clean:
	rm -f client
	make -C $(GENDIR) clean
extra_clean: clean
	rm -rf *~
	rm -rf *.gamelog
	
	
