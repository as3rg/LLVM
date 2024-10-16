build-gen-gen:
	mkdir build
	cd build && \
	clang++ -std=c++23 -o generator-generator.so ../generator-generator.cpp -fPIC -shared -I$$(llvm-config --includedir)

get-app:
	mkdir -p build/code
	cp -r ../'[2] Ray Marching & Float32'/* build/code/

get-gen: build-gen-gen get-app
	cd build && \
	clang code/app/app.c code/float32/*.c -O3 -S -emit-llvm && \
	llvm-link -o single.ll -S *.ll && \
	clang -Wno-unused-command-line-argument -fpass-plugin=./generator-generator.so -c single.ll > ../generator.cpp

build-gen: get-gen
	cd build && \
	clang++ -std=c++23 -Wno-implicitly-unsigned-literal $$(llvm-config --cppflags --ldflags --libs) -I./code code/app/sim.c ../generator.cpp -lSDL2 -o generator.out 

run: build-gen
	./build/generator.out run

ir: build-gen
	./build/generator.out print

clean:
	rm -rf build
	rm -rf **/*.pch
