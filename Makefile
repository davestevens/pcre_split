CC = gcc
CFLAGS = -c -Wall -pedantic -Wextra
LDFLAGS = -lpcre

INCDIR =  inc
SRCDIR = src
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGET = PCRE_SPLIT

debug:		CFLAGS += -g
release:	CFLAGS += -O3 -fno-strict-aliasing

all: $(SRC) $(TARGET)

debug:	$(SRC) $(TARGET)
release: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	   $(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@ -I$(INCDIR)

clean:
		rm -f $(OBJ) $(TARGET)

distclean:
		rm -f *~ \#* $(OBJDIR)/*.o $(SRCDIR)/*~ $(INCDIR)/*~ $(TARGET)
