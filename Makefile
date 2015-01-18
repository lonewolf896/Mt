VERSION =  $(shell git rev-parse --short HEAD)

OUTPUT = Mt

SRCDIR = src
OBJDIR = build
ETCDIR = etc

CFLAGS += -I./src/include -fopenmp -Wall -std=c++11 -D 'VERSION="$(VERSION)"'


LDFLAGS += -lpthread -fopenmp

_OBJS = mt.o

OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

all: $(OUTPUT)

default: $(OUTPUT)

$(OBJDIR)/%.o: sml $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) $< -o $(OUTPUT)

sml:
	bison -d -o $(SRCDIR)/parser.cpp $(ETCDIR)/sml.y
	lex -o $(SRCDIR)/tokens.cpp $(ETCDIR)/sml.l

clean:
	rm -f $(OBJDIR)/*.o $(OUTPUT)
