build:
	mkdir build
	cd build && \
	clang ../app/*.c ../app/*.h ../float32/*.c ../float32/*.h -lSDL2

llvm:
	mkdir llvm
	cd llvm && \
	clang ../app/app.c ../float32/*.c ../float32/*.h -S -emit-llvm && \
	llvm-link -S -v -o result.ll *.ll

run: build
	./build/a.out

clean:
	rm -rf llvm build
	rm -rf **/*.pch
