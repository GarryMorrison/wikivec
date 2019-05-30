CXX = g++
CXXFLAGS = -std=c++11 -O3
INCS = -Iinclude
BUILDDIR = build
OUTDIR = bin
SRCDIR = src
OBJS = $(addprefix ${BUILDDIR}/, \
	vectors.o \
        sets.o \
	main.o \
	)

all: directories $(OUTDIR)/wikivec

$(OUTDIR)/wikivec: $(OBJS)
	@echo "LD $@"
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(INCS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

.PHONY: directories clean

directories: $(OUTDIR)/ $(BUILDDIR)/

%/:
	@echo "MKDIR $<"
	@mkdir -p $@

clean:
	@echo "RMDIR ${BUILDDIR} ${OUTDIR}"
	@rm $(BUILDDIR)/* $(OUTDIR)/* 2> /dev/null




