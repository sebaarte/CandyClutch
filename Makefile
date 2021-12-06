FLAGS = -std=c++17 -masm=intel -pthread

#\ -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Winline\
-Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept\
-Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo\
-Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods\
-Wsuggest-override

LIBS_FLAGS= -lfltk

ODIR = obj/
SDIR = src/
IDIR = include/

BUILD = exec
CC = @g++
SRCS = $(wildcard $(SDIR)*.cpp)
OBJS = $(patsubst $(SDIR)%.cpp,$(ODIR)%.o,$(SRCS))


# Pre-build
$(shell mkdir -p obj/)

# Linkage
$(BUILD): $(OBJS)
	$(CC) $^ $(LIBS_FLAGS) -o $@
	@echo "[COMPILED]"

-include $(ODIR)*.d

# Compilation
$(ODIR)%.o: $(SDIR)%.cpp
	$(CC) $(FLAGS) -c -I$(IDIR) -MMD -o $@ $<

clean:
	rm -f $(ODIR)* $(BUILD)

run:
	./exec