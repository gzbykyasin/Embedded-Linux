/*
 * @brief User Space (/dev/mem) Example for Embedded Linux
 *      MPU Cortex A7 is imx6ull.
 * 
 *  Created on: 15 Mar 2020
 *      Author: YASIN GOZUBUYUK
 */

#include "padConfig.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

/********************
*****GPIO DEFINE*****
*********************/
#define GPIO1_DR                                    0x209C000   // Data Register
#define GPIO1_GDIR                                  0x209C004   // Direction Register
#define GPIO1_PSR                                   0x209C008   // Pad Status Register 
#define GPIO5_DR                                    0x20AC000   // Data Register   
#define GPIO5_GDIR                                  0x20AC004   // Direction Register
#define GPIO5_PSR                                   0x20AC008   // Pad Status Register


/******************************************
*****PIN INPUT, OUTPUT DIRECTION STATE*****
*******************************************/
#define GPIO1_D0_IN                                 (~(uint32_t)(1<<0)) // D0 Input
#define GPIO1_D1_IN                                 (~(uint32_t)(1<<1)) // D1 Input
#define GPIO5_D0_OUT                                ((uint32_t)(1<<0))  // D0 Output
#define GPIO5_D1_OUT                                ((uint32_t)(1<<1))  // D1 Output


/**********************
*****PIN SETTINGS*****
***********************/
#define GPIO1_D0_READ                               ((uint32_t)(1<<0))  // D0 Read
#define GPIO1_D1_READ                               ((uint32_t)(1<<1))  // D1 Read
#define GPIO5_D0_HIGH                               ((uint32_t)(1<<0))  // D0 High
#define GPIO5_D0_LOW                                (~(uint32_t)(1<<0)) // D0 Low
#define GPIO5_D1_HIGH                               ((uint32_t)(1<<1))  // D1 High
#define GPIO5_D1_LOW                                (~(uint32_t)(1<<1)) // D1 Low

/*****************************
*****MEMORY MUX MAP SIZES*****
******************************/
#define MUX_SIZE                                    ((uint32_t)(4096))
#define GPIO1_MUX_SIZE                              MUX_SIZE
#define GPIO5_MUX_SIZE                              MUX_SIZE

/*************************
******GPIO MAP SIZES******
**************************/
#define GPIO_DATA_SIZE                              MUX_SIZE

/********************************* 
 *******GPIO INIT FUNCTIONS******* 
 *********************************/
void gpio1Init(void);
void gpio5Init(void);


/***********************
 *******VERIABLES******* 
 ***********************/
static int devMem;
static volatile int *gpio1;
static volatile int *gpio5;
static volatile int *iomux1;
static volatile int *iomux5;

int main(int argc,char **argv){   

    printf("/dev/mem opening\n");
    if ((devMem = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0) {
        printf("Unable to open /dev/mem: %s\n", strerror(errno));
        close(devMem);
        exit(EXIT_FAILURE);
    } 

    gpio1Init();
    printf("gpio1 init finish\n");    
    gpio5Init();
    printf("gpio5 init finish\n");
    
    while(1){
        if(*gpio1 & GPIO1_D0_READ){
            *gpio5 |= GPIO5_D0_HIGH;
            usleep(250000);
            *gpio5 &= GPIO5_D0_LOW;
        }

        if(*gpio1 & GPIO1_D1_READ){
            *gpio5 |= GPIO5_D1_HIGH;
            usleep(250000);
            *gpio5 &= GPIO5_D1_LOW;
        }
    }

    close(devMem);
    return 0;
}

//GPIO1 INIT
void gpio1Init(void){
    printf("gpio1 mux open\n");
    iomux1 = (uint_t *)mmap(0, GPIO1_MUX_SIZE , PROT_READ|PROT_WRITE, MAP_SHARED, devMem, IOMUXC_GPIO1);
    if((int) iomux1 <0){
      printf("gpio1 mux open failed:%s",strerror(errno));
      close(devMem);
      exit(EXIT_FAILURE);
    }    
    printf("gpio1 mux set\n"); 
    *(iomux1 + ((D0_MUX - IOMUXC_GPIO1) ) / 4) = 0x5;   
    *(iomux1 + ((D0_PAD - IOMUXC_GPIO1) ) / 4) = 0x0000B0B0;
    *(iomux1 + ((D1_MUX - IOMUXC_GPIO1) ) / 4) = 0x5;   
    *(iomux1 + ((D1_PAD - IOMUXC_GPIO1) ) / 4) = 0x0000B0B0;    
    if((munmap((void *)iomux1, GPIO1_MUX_SIZE)) < 0){
        printf("gpio1 mux set failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("gpio1 pad open\n"); 
    gpio1 = (int *)mmap(0,  GPIO_DATA_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, devMem, GPIO1_DR);
    if((int) gpio1 <0){
      printf("gpio1 pad open failed:%s",strerror(errno));
      exit(EXIT_FAILURE);
    }
    printf("gpio1 D0 and D1 direction set\n");
    *(gpio1 + ((GPIO1_GDIR - GPIO1_DR) / 4)) &= ( GPIO1_D0_IN );
    *(gpio1 + ((GPIO1_GDIR - GPIO1_DR) / 4)) &= ( GPIO1_D1_IN );
}

//GPIO5 INIT
void gpio5Init(void){
    printf("gpio5 mux open\n");
    iomux5 = (uint_t *)mmap(0, GPIO1_MUX_SIZE , PROT_READ|PROT_WRITE, MAP_SHARED, devMem, IOMUXC_GPIO5);
    if((int) iomux5 <0){
      printf("gpio5 mux open failed:%s",strerror(errno));
      close(devMem);
      exit(EXIT_FAILURE);
    }    
    printf("gpio5 mux set\n"); 
    *(iomux5 + ((D0_MUX - IOMUXC_GPIO5) ) / 4) = 0x5;   
    *(iomux5 + ((D0_PAD - IOMUXC_GPIO5) ) / 4) = 0x0000B0B0;
    *(iomux5 + ((D1_MUX - IOMUXC_GPIO5) ) / 4) = 0x5;   
    *(iomux5 + ((D1_PAD - IOMUXC_GPIO5) ) / 4) = 0x0000B0B0;    
    if((munmap((void *)iomux5, GPIO1_MUX_SIZE)) < 0){
        printf("gpio5 mux set failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("gpio5 pad open\n"); 
    gpio5 = (int *)mmap(0,  GPIO_DATA_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, devMem, GPIO5_DR);
    if((int) gpio5 <0){
      printf("gpio5 pad open failed:%s",strerror(errno));
      exit(EXIT_FAILURE);
    }
    printf("gpio5 D0 and D1 direction set\n");
    *(gpio5 + ((GPIO5_GDIR - GPIO5_DR) / 4)) |= ( GPIO5_D0_OUT );
    *(gpio5 + ((GPIO5_GDIR - GPIO5_DR) / 4)) |= ( GPIO5_D0_OUT );
}
