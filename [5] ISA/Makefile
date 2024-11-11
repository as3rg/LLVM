get-app:
	mkdir -p build/code
	cp -r ../'[2] Ray Marching & Float32'/* build/code/

get-ir: get-app
	cd build && \
	clang code/app/app.c code/float32/*.c -Os -S -emit-llvm

build-isa-to-ir:
	mkdir -p build
	cd build && \
	clang++ -g -std=c++23 ../isa-parser.cpp ../isa.cpp ../sim.c ../isa-to-ir.cpp -lSDL2 $$(llvm-config --cppflags --ldflags --libs)

run-isa: FORCE
	./build/a.out run-isa < app.s

run-ir: FORCE
	./build/a.out run-ir < app.s

print-isa: FORCE
	./build/a.out print-isa < app.s

print-ir: FORCE
	./build/a.out print-ir < app.s

clean:
	rm -rf build
	rm -rf **/*.pch

FORCE: ;
