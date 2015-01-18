VERSION =  $(shell git rev-parse --short HEAD)

OUTPUT = Mt

SRCDIR = src
OBJDIR = build

CFLAGS += -I./src/include -fopenmp -Wall -std=c++11 -D 'VERSION="$(VERSION)"'


LDFLAGS += -lpthread -fopenmp

_OBJS = mt.o

OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

all: $(OUTPUT)

default: $(OUTPUT)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) $< -o $(OUTPUT)

clean:
	rm -f $(OBJDIR)/*.o $(OUTPUT)
