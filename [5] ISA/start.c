#include "sim.h"

extern void app();

int main(void)
{
    simInit();
    app();
    simExit();
    return 0;
}