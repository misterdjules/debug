.PHONY: all clean test

SOURCES 		:= debug.c
OBJECTS			:= $(subst .c,.o,$(SOURCES))
HEADERS			:= $(subst .c,.h,$(SOURCES))

CFLAGS += -fPIC
CFLAGS += -Wall -pedantic

LDFLAGS += -shared

RANLIB := ranlib

DYN_SHARED_LIB 	:= libdebug.so
STATIC_LIB 		:= libdebug.a

all: $(DYN_SHARED_LIB) $(STATIC_LIB)

$(DYN_SHARED_LIB): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

$(STATIC_LIB): $(OBJECTS)
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) *.o *.so *.a

test: