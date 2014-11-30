#include <stdio.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"

#include "fifo.h"

#define fsize 20

     static int32_t fifo[fsize]; //(static prevents any other file from accessing this fifo; global only to this file)
     int32_t getI, putI;

     void fifo_Init(void){
        getI = 0;
        putI = 0;
                         
     }
                    
     // Returns a success or failure if buffer is full 
     int8_t fifo_Put(int32_t data){
        if (((putI + 1) % fsize) == getI){
             return 0;
        }
        fifo[putI] = data;
        putI  = (putI + 1) % fsize;
				return 1;
		 }

     // Returns a success or failure if buffer empty
     int8_t fifo_Get(int32_t *dptr){
        if (getI == putI){
            return (0); //empty buffer
        }
        *dptr = fifo[getI];
        getI = (getI + 1) % fsize;
        return 1; 
     }