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

int icclReduce(void* sendbuff, void* recvbuff, size_t count, icclDatatype_t datatype, icclRedOp_t op, int root, struct icclComm_t* comm){

    int currentDevice;
    hipGetDevice(&currentDevice);

    if (currentDevice != root) {
        hipSetDevice(root);
    }

    //TODO: add checks

    void* cpyrecvbuff;

    if (datatype == icclInt){
        void* cpyrecvbuff = malloc(count * sizeof(int));
        int* cpyrecvbuffcasted = (int*)cpyrecvbuff;
        hipFree(cpyrecvbuff);
        hipMemcpy(cpyrecvbuffcasted, sendbuff, count, hipMemcpyDeviceToDevice);
        op(cpyrecvbuffcasted, recvbuff, count);
        hipFree(cpyrecvbuffcasted);
        
    } else {
        return -1;
    }


    op(sendbuff, recvbuff, count);

    return 0;

}

int icclDummy(void* inbuffer, void* outbuffer, size_t count){
    return 0;
}

int icclAdd(void* inbuffer, void* outbuffer, size_t count) {
    if (inbuffer == NULL || outbuffer == NULL) {
        return -1;
    }
    int* inData = (int*)inbuffer;
    int* outData = (int*)outbuffer;

    int sum = 0;
    for (size_t i = 0; i < count; i++) {
        sum += inData[i];
    }
    
    outData[0] = sum;
    
    return 0;
}

int icclProd(void* inbuffer, void* outbuffer, size_t count) {
    if (inbuffer == NULL || outbuffer == NULL) {
        return -1;
    }
    int* inData = (int*)inbuffer;
    int* outData = (int*)outbuffer;

    int prod = 1;
    for (size_t i = 0; i < count; i++) {
        prod *= inData[i];
    }
    
    outData[0] = prod;
    
    return 0;
}

int icclMin(void* inbuffer, void* outbuffer, size_t count) {
    if (inbuffer == NULL || outbuffer == NULL) {
        return -1;
    }
    int* inData = (int*)inbuffer;
    int* outData = (int*)outbuffer;

    int min = 0;
    bool started = false;
    for (size_t i = 0; i < count; i++) {
        if(!started) {
            started = true;
            min = inData[i];
        } else {
            if(inData < min) {
                min = inData[i];
            }
        }
    }
    
    outData[0] = min;
    
    return 0;
}

int icclMax(void* inbuffer, void* outbuffer, size_t count) {
    if (inbuffer == NULL || outbuffer == NULL) {
        return -1;
    }
    int* inData = (int*)inbuffer;
    int* outData = (int*)outbuffer;

    int max = 0;
    bool started = false;
    for (size_t i = 0; i < count; i++) {
        if(!started) {
            started = true;
            max = inData[i];
        } else {
            if(inData > max) {
                max = inData[i];
            }
        }
    }
    
    outData[0] = max;
    
    return 0;
}