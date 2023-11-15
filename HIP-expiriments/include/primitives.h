#include "hip/hip_runtime.h"
#include <stddef.h>

typedef enum {
    icclChar,
    icclInt,
    icclFloat,
    icclHalf,
    icclDouble,
} icclDatatype_t;


typedef int (*icclRedOp_t)(void*, void*, size_t);

int icclAdd(void* inbuffer, void* outbuffer, size_t count);

int icclProd(void* inbuffer, void* outbuffer, size_t count);

int icclMax(void* inbuffer, void* outbuffer, size_t count);

int icclMin(void* inbuffer, void* outbuffer, size_t count);

int icclDummy(void* inbuffer, void* outbuffer, size_t count);

struct icclComm_t {
    void* buff_access;
    size_t count;
    int peer;
    icclDatatype_t datatype;

};

int icclSend(void* sendbuff, size_t count, icclDatatype_t datatype, int peer, struct icclComm_t* comm);

int icclRecv(void* recvbuff, size_t count, icclDatatype_t datatype, int peer, struct icclComm_t* comm);

int icclReduce(void* sendbuff, void* recvbuff, size_t count, icclDatatype_t datatype, icclRedOp_t op, int root, struct icclComm_t* comm);

int icclRecvReduceSend(void* sendbuff, void* recvbuff, size_t count, icclDatatype_t datatype, icclRedOp_t op, int root, struct icclComm_t* comm);

int icclRecvReduceCopy(void* sendbuff, void* recvbuff, size_t count, icclDatatype_t datatype, icclRedOp_t op, int root, struct icclComm_t* comm);

int icclCopySend(void* sendbuff, size_t count, icclDatatype_t datatype, int peer, struct icclComm_t* comm);

int icclRecvCopySend(void* sendbuff, void* recvbuff, size_t count, icclDatatype_t datatype, icclRedOp_t op, int root, struct icclComm_t* comm);

int icclRecvReduceCopySend(void* sendbuff, void* recvbuff, size_t count, icclDatatype_t datatype, icclRedOp_t op, int root, struct icclComm_t* comm);


