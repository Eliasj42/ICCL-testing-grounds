#include "hip/hip_runtime.h"
#include "primitives.h"

int icclSend(const void* sendbuff, size_t count, int peer, struct icclComm_t* comm){

    int currentDevice;
    hipGetDevice(&currentDevice);

    if (currentDevice != peer) {
        hipSetDevice(peer);
    }

    hipMalloc(&sendbuff, count);

    comm->peer = peer;
    comm->count = count;
    comm->buff_access = &sendbuff;
    return 0;

}

int icclRecv(const void* recvbuff, size_t count, int peer, struct icclComm_t* comm){
    int currentDevice;
    hipGetDevice(&currentDevice);

    if (currentDevice != peer) {
        hipSetDevice(peer);
    }

    if (count != comm->count) {
        return 1;
    }

    hipMalloc(&recvbuff, count);
    hipMemcpy(recvbuff, comm->buff_access, count, hipMemcpyDeviceToDevice);

    hipError_t copyError = hipGetLastError();
    if (copyError != hipSuccess) {
        printf("Error copying data");
    } else {
        printf("Data copied Successfully");
    }

    return 0;

}