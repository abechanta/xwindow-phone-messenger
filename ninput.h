/*
// ninput.h
*/

#ifndef NINPUT_H
#define NINPUT_H

void NumSet(int m, int n);                              /* number initialize */
void BufferCheck(int m, char **retc, int *reti);    /* current buffer output */
void Word(int m, char ch, char **retc, int *reti);   /* return 16bit strings */
int Code(char ch0, char ch1, char ch2);          /* return 16bit table index */
int Isboin(char ch);                        /* check 'a', 'i', 'u', 'e', 'o' */

#endif
