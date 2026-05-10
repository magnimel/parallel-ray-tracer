.PHONY: compile rebuild clean run quick_render benchmark_suite profile tracy_profiler

# Renderer compiler
CC := /opt/homebrew/bin/gcc-15
CXX := /opt/homebrew/bin/g++-15

BUILD_TYPE ?= Release
TRACY ?= OFF

BUILD_DIR := build

# Tracy profiler build
TRACY_PROFILER_BUILD := external/tracy/profiler/build
TRACY_PROFILER := $(TRACY_PROFILER_BUILD)/tracy-profiler

$(BUILD_DIR)/.configured: CMakeLists.txt
	@CC=$(CC) CXX=$(CXX) cmake \
		-S . \
		-B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DTRACY_ENABLE=$(TRACY)

	@touch $(BUILD_DIR)/.configured

compile: $(BUILD_DIR)/.configured
	@cmake --build $(BUILD_DIR)

rebuild: clean compile

run:
	./$(BUILD_DIR)/ray-tracing

quick_render:
	./scripts/quick_render.sh

benchmark_suite:
	./scripts/benchmark_suite.sh

tracy_profiler:
	@CC=/usr/bin/clang CXX=/usr/bin/clang++ \
	cmake \
		-S external/tracy/profiler \
		-B $(TRACY_PROFILER_BUILD) \
		-DCMAKE_BUILD_TYPE=Release

	@cmake --build $(TRACY_PROFILER_BUILD)

profile: tracy_profiler
	$(TRACY_PROFILER)

clean:
	rm -rf $(BUILD_DIR)