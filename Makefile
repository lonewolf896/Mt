VERSION := $(shell git rev-parse --short HEAD)

CYAN := "\033[0;36m"
LIGHT_CYAN := "\033[1;36m"
LIGHT_GREEN := "\033[1;32m"
NO_COLOUR := "\033[0m"
WHITE := "\033[1;37m"

SRCDIR := src
OBJDIR := build
OUTDIR := bin

TARGET := $(OUTDIR)/$(shell basename `pwd`)

CXX := g++ -Werror -fno-builtin
CXX_DBG := clang++ -g -stdlib=libc++

CFLAGS := -std=c++11 -O3 -Wall -Wextra -Wformat=2 -Wpedantic -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-overflow=1 \
	-Wformat-nonliteral -Wuninitialized -fstack-protector -Wformat-security -I$(SRCDIR)/include

CFLAGS += `pkg-config --cflags ncurses`
CFLAGS += `pkg-config --cflags libzmq`
CFLAGS += -D'VERSION="$(VERSION)"'


LDFLAGS :=  -lc++abi -lpthread
LDFLAGS += `pkg-config --libs ncurses`
LDFLAGS += `pkg-config --libs libzmq`

SRCS := $(shell ls $(SRCDIR)/*.cc)
_OBJS := $(SRCS:.cc=.o)
OBJS := $(subst $(SRCDIR),$(OBJDIR),$(_OBJS))

all: debug

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

.PHONY: clean
clean:
	@echo -e Cleaning...
	@rm -f $(OBJS) $(TARGET)

.PHONY: directories
directories:
	if [ ! -d $(OBJDIR) -a ! -d $(OUTDIR) ]; then \
		mkdir -p $(OBJDIR) $(OUTDIR); \
	fi
