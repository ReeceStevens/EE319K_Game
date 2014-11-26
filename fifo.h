#include <stdint.h>

void fifo_Init(void);
int8_t fifo_Put(int32_t data);
int8_t fifo_Get(int32_t *dptr);