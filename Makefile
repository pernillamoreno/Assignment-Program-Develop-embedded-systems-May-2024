CC := g++
CFLAGS := -Wall -Wpedantic -Wextra -Werror -DDEVENV

MODULE := button

LIB_DIR := lib
TEST_DIR := test
TEST_EXE := test_program  # Change the output executable name
BUILD_DIR := build
UNITY_DIR := $(TEST_DIR)/unity
TEST_MODULE := $(TEST_DIR)_$(MODULE)

INCLUDES := $(sort $(dir $(wildcard $(LIB_DIR)/$(MODULE)/*.h) $(wildcard $(TEST_DIR)/*/*.h)))
INCLUDES := $(INCLUDES:%=-I./%)

# List all the source files in the module and test directories
SOURCES := $(wildcard $(LIB_DIR)/$(MODULE)/*.cpp) \
           $(wildcard $(TEST_DIR)/*/*.cpp)
OBJECTS := $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) $(BUILD_DIR)/$(TEST_EXE)
	@echo "=============== TARGETS ==================="
	@echo "==> clean: to clean the project"
	@echo "==> check: to build and run the test"
	@echo "==========================================="

$(BUILD_DIR)/$(TEST_EXE): $(OBJECTS)
	@$(CC) --coverage $^ -o $@ 

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) -c --coverage -MMD $(CFLAGS) $< $(INCLUDES) -o $@

-include $(OBJECTS:%.o=%.d)

check: $(BUILD_DIR) $(BUILD_DIR)/$(TEST_EXE)
	@echo "================================================="
	@echo "================ RUN TEST ======================="
	@echo "================================================="
	@./$(BUILD_DIR)/$(TEST_EXE); \
	gcovr -r . --filter $(LIB_DIR)/$(MODULE)/button.cpp --filter $(TEST_DIR)/*/test.cpp --html-details -o $(BUILD_DIR)/index.html

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: check all clean


