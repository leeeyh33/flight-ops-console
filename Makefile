# ===== Simple Makefile (clang only) =====

CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

TARGET   = flight_ops
BUILD    = build

# Find all .cpp files under src/
SRCS = $(shell find src -name "*.cpp")
OBJS = $(patsubst src/%.cpp,$(BUILD)/%.o,$(SRCS))

.PHONY: all clean

all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile each .cpp into build/ folder (mirror structure)
$(BUILD)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD) $(TARGET)