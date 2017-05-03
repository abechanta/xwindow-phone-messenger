/*
// phone.h
*/

#ifndef PHONE_H
#define PHONE_H

void Destroy(int m);                                    /* destroy resources */
                                                    /* text scroll (forward) */
void TextPrint(int mode, int dot, int height, int len);
void TextBackPrint(int dot, int height);           /* text scroll (backward) */
void InfoPrint(int m, int mode, char *retc);            /* infomation output */

int Alias(char *alias, char *ret1, char *ret2);     /* user or display alias */

#endif
