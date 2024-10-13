build-gen-gen:
	mkdir build
	cd build && \
	clang++ -std=c++23 -o generator-generator.so ../generator-generator.cpp -fPIC -shared -I$$(llvm-config --includedir)

get-app:
	mkdir -p build/code
	cp -r ../'[2] Ray Marching & Float32'/* build/code/

get-gen: build-gen-gen get-app
	cd build && \
	clang -D__sim__ code/**/*.c -O3 -S -emit-llvm && \
	llvm-link -o single.ll -S *.ll && \
	clang -Wno-unused-command-line-argument -fpass-plugin=./generator-generator.so -c single.ll > ../generator.cpp

build-gen: get-gen
	cd build && \
	clang++ -std=c++23 -Wno-implicitly-unsigned-literal $$(llvm-config --cppflags --ldflags --libs) code/app/sim.c ../generator.cpp -lSDL2 -o generator.out 

run-gen: build-gen
	./build/generator.out run

run-raw: build-gen
	cd build && \
	./generator.out print > generated.ll && \
	clang generated.ll code/app/sim.c -lSDL2 -o app.out && \
	./app.out

clean:
	rm -rf build
	rm -rf **/*.pch
