#include "primitives.h"
#include <stdio.h>

#include "hip/hip_runtime.h"

int main(){
    struct icclComm_t comm;

    int* sourceData;
    int* destData;

    size_t countsrc = sizeof(sourceData);
    size_t countdest = sizeof(destData);

    icclSend(&sourceData, countsrc, 0, &comm);
    icclRecv(&destData, countdest, 1, &comm);

    return 0;

}
