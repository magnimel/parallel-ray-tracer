.PHONY: compile rebuild

compile: 
	@cmake --build build --config release --target render

rebuild:
	rm -rf build out
	@cmake -S . -B build