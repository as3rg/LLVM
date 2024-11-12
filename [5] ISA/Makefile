get-app:
	mkdir -p build/code
	cp -r ../'[2] Ray Marching & Float32'/* build/code/

build-isa-to-ir:
	mkdir -p build
	cd build && \
	clang++ -std=c++23 ../isa-parser.cpp ../isa.cpp ../sim.c ../isa-to-ir.cpp -lSDL2 $$(llvm-config --cppflags --ldflags --libs)

run-isa: FORCE
	./build/a.out run-isa < app.s

run-ir: FORCE
	./build/a.out run-ir < app.s

print-isa: FORCE
	./build/a.out print-isa < app.s

print-ir: FORCE
	./build/a.out print-ir < app.s

build-ir: FORCE
	cd build && \
	./a.out print-ir < ../app.s > app.ll && \
	clang -O3 -o app.out -lSDL2 $$(llvm-config --cppflags --ldflags --libs) app.ll ../start.c ../sim.c

clean:
	rm -rf build
	rm -rf **/*.pch

FORCE: ;
