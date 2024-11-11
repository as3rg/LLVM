#define SIM_X_SIZE 500
#define SIM_Y_SIZE 500

unsigned long long simAlloc(unsigned long long x);
unsigned long long simFree(unsigned long long x);
unsigned long long simFlush();
unsigned long long simPutPixel(unsigned long long x, unsigned long long y, unsigned long long argb);
unsigned long long simInit();
unsigned long long simExit();
