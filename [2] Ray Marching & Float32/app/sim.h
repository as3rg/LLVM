#define SIM_X_SIZE 500
#define SIM_Y_SIZE 500

void simFlush();
void simPutPixel(int x, int y, int argb);
void simInit();
void simExit();

extern void app();
