CC=gcc
CFLAGS=-fPIC -shared
LFLAGS=-ldl
FMODE=0644

libwrapper-sdbuscall.so: libwrapper-sdbuscall.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)
	#chown root $@
	#chmod ug+s $@
	chmod $(FMODE) $@

clean:
	rm -f *~ *.so

.PHONY: clean
