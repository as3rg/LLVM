build:
	mkdir build
	cd build && \
	clang++ -o customPass.so ../pass.cpp -fPIC -shared -I$(llvm-config --includedir)

get-app:
	mkdir -p build/code
	cp -r ../'[2] Ray Marching & Float32'/* build/code/

opt: build get-app
	cd build && \
	clang code/app/*.c code/float32/*.c -fpass-plugin=./customPass.so -lSDL2 -O3

run: opt
	cd build && \
	./a.out | head -n 5000000 > log.txt && \
	wc -l log.txt && \
	du -h log.txt

analize: run
	python analize.py 1
	python analize.py 2
	python analize.py 3
	python analize.py 4
	python analize.py 5

clean:
	rm -rf build
	rm -rf **/*.pch
