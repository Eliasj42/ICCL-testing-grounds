#include "hip/hip_runtime.h"
#include "primitives.h"

int icclSend(void* sendbuff, size_t count, icclDatatype_t datatype, int peer, struct icclComm_t* comm){

    int currentDevice;
    hipGetDevice(&currentDevice);

    if (currentDevice != peer) {
        hipSetDevice(peer);
    }

    hipMalloc(&comm->buff_access, count);
    hipMemcpy(comm->buff_access, sendbuff, count, hipMemcpyDeviceToDevice);

    comm->peer = peer;
    comm->count = count;
    comm->datatype = datatype;
    return 0;

}

int icclRecv(void* recvbuff, size_t count, icclDatatype_t datatype, int peer, struct icclComm_t* comm){
    int currentDevice;
    hipGetDevice(&currentDevice);

    if (currentDevice != peer) {
        hipSetDevice(peer);
    }

    if (count != comm->count) {
        printf("ERROR: data buffers do not have matching sizes\n");
        return 1;
    }

    if (datatype != comm->datatype) {
        printf("ERROR: datatypes do not match\n");
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