.PHONY: compile rebuild clean

compile: 
	@cmake --build build --config release --target render

rebuild:
	@cmake -S . -B build

clean:
	rm -rf build out