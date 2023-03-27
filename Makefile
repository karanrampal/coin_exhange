EXE := main
OBJS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
CLEAN_RM :=
MODE := debug

# Compiler/linker config and object/depfile directory:
CXX := g++
LD  := g++
OBJS_DIR := .objs

# Provide lots of helpful warning/errors:
DEPFILE_FLAGS := -MMD -MP
WARNINGS_AS_ERRORS := -Werror # Un-commenting this line makes compilation much more strict.
EXCLUSIVE_WARNING_OPTIONS :=  -Wno-unused-but-set-variable -Weffc++ -Wsign-conversion
ASANFLAGS := -fsanitize=address -fno-omit-frame-pointer # for debugging, if supported on the OS
WARNINGS := -pedantic -Wall $(WARNINGS_AS_ERRORS) -Wfatal-errors -Wextra $(EXCLUSIVE_WARNING_OPTIONS)

# Debugger flag
ifeq ($(MODE), debug)
DBG := -ggdb
else
DBG := -O2 -DNDEBUG
endif

# Flags for compile:
CXXFLAGS += -std=c++14 -O0 $(WARNINGS) $(DEPFILE_FLAGS) -g -c $(ASANFLAGS) $(DBG)

# Flags for linking:
LDFLAGS += -std=c++14 $(ASANFLAGS)

# Rule for `all` (first/default rule):
all: $(EXE)

# Rule for linking the final executable:
$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@

# Ensure .objs/ exists:
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for compiling source code.
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Standard C++ Makefile rules:
clean:
	rm -rf $(EXE) $(TEST) $(OBJS_DIR) $(CLEAN_RM) *.o

tidy: clean
	rm -rf doc

.PHONY: all tidy clean