.PHONY: compile rebuild

compile: 
	@cmake --build build --target render

rebuild:
	rm -rf build out
	@cmake -S . -B build