#include "hip/hip_runtime.h"
#include <stddef.h>

typedef enum {
    icclChar,
    icclInt,
    icclFloat,
    icclHalf,
    icclDouble,
} icclDatatype_t;

struct icclComm_t {
    void* buff_access;
    size_t count;
    int peer;
    icclDatatype_t datatype;

};

int icclSend(void* sendbuff, size_t count, icclDatatype_t datatype, int peer, struct icclComm_t* comm);

int icclRecv(void* recvbuff, size_t count, icclDatatype_t datatype, int peer, struct icclComm_t* comm);
