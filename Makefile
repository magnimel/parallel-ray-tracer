.PHONY: compile rebuild clean

compile: 
	@cmake --build build --config release

rebuild:
	@cmake -S . -B build

clean:
	rm -rf build