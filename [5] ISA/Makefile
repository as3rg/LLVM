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
	./build/a.out run-isa

run-ir: FORCE
	./build/a.out run-ir

print-isa: FORCE
	./build/a.out print-isa

print-ir: FORCE
	./build/a.out print-ir

run:
	cd build && \
	clang++ ../single.ll ../sim.c ../start.c -lSDL2

clean:
	rm -rf build
	rm -rf **/*.pch

FORCE: ;
