#define SIM_X_SIZE 500
#define SIM_Y_SIZE 500

#ifndef __sim__
void simFlush();
void simPutPixel(int x, int y, int argb);
int simRand();
#endif

extern void simInit();
extern void app();
extern void simExit();
