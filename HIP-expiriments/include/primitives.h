#include "hip/hip_runtime.h"
#include <stddef.h>

struct icclComm_t {
    void* buff_access;
    size_t count;
    int peer;

};

int icclSend(void* sendbuff, size_t count, int peer, struct icclComm_t* comm);

int icclRecv(void* recvbuff, size_t count, int peer, struct icclComm_t* comm);
