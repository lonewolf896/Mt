VERSION := $(shell git rev-parse --short HEAD)

CYAN := "\033[0;36m"
LIGHT_CYAN := "\033[1;36m"
LIGHT_GREEN := "\033[1;32m"
NO_COLOUR := "\033[0m"
WHITE := "\033[1;37m"

ETCDIR := etc
SRCDIR := src
OBJDIR := build
OUTDIR := bin

TARGET := $(OUTDIR)/$(shell basename `pwd`)

CXX := g++ -Werror -fno-builtin
CXX_DBG := clang++ -g -stdlib=libc++

CFLAGS := -std=c++11 -O3 -Wall -Wextra -Wformat=2 -Wpedantic -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-overflow=1 \
	-Wformat-nonliteral -Wuninitialized -fstack-protector -Wformat-security -I$(SRCDIR)/include

CFLAGS += -D'VERSION="$(VERSION)"'


LDFLAGS := -ltcmalloc -lc++abi -lpthread

SRCS := $(shell ls $(SRCDIR)/*.cc)
_OBJS := $(SRCS:.cc=.o)
OBJS := $(subst $(SRCDIR),$(OBJDIR),$(_OBJS))

all: debug

verbose: CFLAGS += -v
verbose: debug

perf: LDFLAGS += -lprofiler
perf: debug

debug: CFLAGS += -DDEBUG
debug: CXX=$(CXX_DBG)
debug: release

release: directories clean $(OBJS)
	@echo -e Linking $(LIGHT_GREEN)$(TARGET)$(NO_COLOUR)
	@$(CXX) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET)

$(OBJS): $(SRCS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@echo -e Building $(CYAN)$@$(WHITE) from $(CYAN)$<$(WHITE)
	@$(CXX) $(CFLAGS) -o $@ -c $<

bison:
	@echo -e Generating bison grammar
	@bison -t --defines=$(SRCDIR)/include/core/lang/Parser.hh -o $(SRCDIR)/Parser.cc $(ETCDIR)/sml.yy
	@echo -e Moving misplaced file
	@mv $(SRCDIR)/stack.hh $(SRCDIR)/include/core/lang/stack.hh

lex: bison
	@echo -e Generating lexical tokens
	@lex -o $(SRCDIR)/Tokens.cc $(ETCDIR)/sml.l

grammar: lex bison

.PHONY: clean
clean:
	@echo -e Cleaning...
	@rm -rf $(OBJS) $(TARGET) ./docs

.PHONY: directories
directories:
	if [ ! -d $(OBJDIR) -a ! -d $(OUTDIR) ]; then \
		mkdir -p $(OBJDIR) $(OUTDIR); \
	fi

.PHONY: docs
docs:
	@echo -e Generating documentation
	@(cat Doxyfile ; echo "PROJECT_NUMBER=$(VERSION)") | doxygen - 
	@(pushd ./docs/latex ; make ; popd)
