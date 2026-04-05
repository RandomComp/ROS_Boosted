#ifndef _R_OS_ASYNC_FWD_H
#define _R_OS_ASYNC_FWD_H

#define MAX_QUEUE_SIZE 128

typedef ErrorCode (*AsyncIO_Method)(struct Awaiter* this);

typedef struct Awaiter Awaiter;

#endif