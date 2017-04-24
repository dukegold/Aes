IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -fpermissive

ODIR=obj


_DEPS = AesEncryptor.h AesDecryptor.h sbox.h AesKeygen.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o AesEncryptor.o AesDecryptor.o AesKeygen.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

aes: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 