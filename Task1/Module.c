/*
 * IOController.c
 *
 *  Created on: 2021¦~6¤ë30¤é
 *      Author: user
 */


#include <msp430.h>

unsigned char SET(unsigned char reg, unsigned char b){
    return reg | (b);
}

unsigned char CLR(unsigned char reg, unsigned char b){
    return reg & ~(b);
}

unsigned char TGL(unsigned char reg, unsigned char b){
    return reg ^ (b);
}

void delay_1ms(void){
    unsigned int i = 80;
    while(i!=0)
        i--;

}

void delay_1s(void){
    unsigned int i = 80000;
    while(i!=0)
        i--;

}
