#include "primitives.h"
#include <stdio.h>

#include "hip/hip_runtime.h"

int main(){
    struct icclComm_t comm;

    int sourceData[5];
    int destData[5];

    for (int i = 0; i < 5; i++) {
        sourceData[i] = i + 1;
    }

    printf("\n SOURCE DATA \n", destData);
    for (int i = 0; i < 5; i++) {
        printf("%d\n", sourceData[i]);
    }

    size_t countsrc = sizeof(sourceData);
    size_t countdest = sizeof(destData);

    icclSend(sourceData, countsrc, icclInt, 0, &comm);
    icclRecv(&destData, countdest, icclInt, 1, &comm);

    printf("\n DEST DATA \n", destData);
    for (int i = 0; i < 5; i++) {
        printf("%d\n", destData[i]);
    }

    hipFree(sourceData);
    hipFree(destData);

    return 0;

}
