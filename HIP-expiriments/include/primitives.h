#include "hip/hip_runtime.h"
#include <stddef.h>

struct icclComm_t {
    const void** buff_access;
    size_t count;
    int peer;

};

int icclSend(const void* sendbuff, size_t count, int peer, struct icclComm_t* comm);

int icclRecv(const void* recvbuff, size_t count, int peer, struct icclComm_t* comm);

int compiletest();