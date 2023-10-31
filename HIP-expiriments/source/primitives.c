#include "hip/hip_runtime.h"
#include "primitives.h"

int icclSend(void* sendbuff, size_t count, int peer, struct icclComm_t* comm){

    int currentDevice;
    hipGetDevice(&currentDevice);

    if (currentDevice != peer) {
        hipSetDevice(peer);
    }

    hipMalloc(&comm->buff_access, count);
    hipMemcpy(comm->buff_access, sendbuff, count, hipMemcpyDeviceToDevice);

    comm->peer = peer;
    comm->count = count;
    return 0;

}

int icclRecv(void* recvbuff, size_t count, int peer, struct icclComm_t* comm){
    int currentDevice;
    hipGetDevice(&currentDevice);

    if (currentDevice != peer) {
        hipSetDevice(peer);
    }

    if (count != comm->count) {
        return 1;
    }

    hipMemcpy(recvbuff, comm->buff_access, count, hipMemcpyDeviceToDevice);
    hipFree(comm->buff_access);

    hipError_t copyError = hipGetLastError();
    if (copyError != hipSuccess) {
        printf("Error copying data ");
        printf(hipGetErrorString(copyError));
        return 1;
    }

    return 0;

}