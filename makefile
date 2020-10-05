CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/shell379

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -O2
LIB := -lncurses
INC := -I include

COMPRESSOR := zip
ARCHIVEFILES := *
ARCHIVEFLAGS := -r -x "$(BUILDDIR)/*" "$(TARGET)" "tags"
ARCHIVENAME := aabass_shell379
ARCHIVEEXT := zip


run: link
	$(TARGET)

link: $(TARGET)

compile: $(OBJECTS)

$(TARGET): $(OBJECTS)
	@echo "> Linking..."
	$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "> Compiling..."
	@echo "mkdir -p $(@D)"
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

compress: tester
	$(COMPRESSOR) $(ARCHIVENAME).$(ARCHIVEEXT) $(ARCHIVEFILES) $(ARCHIVEFLAGS)

tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

fix:
	vim -q build/errors.txt

clean:
	@echo " Cleaning..."
	$(RM) -rf $(BUILDDIR)/* $(TARGET)
