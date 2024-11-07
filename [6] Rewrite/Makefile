run-app:
	mkdir -p build
	cd build && \
	../isa-to-ir.out "print-ir" < ../app.s > app2.ll && \
	clang ../sim.c app2.ll ../start.c -lSDL2 -O3 && \
	./a.out

clean:
	rm -rf build
	rm -rf **/*.pch

FORCE: ;
