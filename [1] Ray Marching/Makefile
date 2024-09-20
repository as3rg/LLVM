build:
	mkdir build
	cd build && \
	clang ../app/*.c ../app/*.h ../float32/*.c ../float32/*.h -lSDL2 -lm

llvm:
	mkdir llvm
	cd llvm && \
	clang ../app/*.c ../app/*.h ../float32/*.c ../float32/*.h -S -emit-llvm

run: build
	./build/a.out

clean:
	rm -rf llvm build
	rm -rf **/*.pch