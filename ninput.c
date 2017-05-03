/*
// ninput.c
*/

/* ### Include Files ### */

#include <stdio.h>
#include <string.h>
#include "ninput.h"

/* ### Constant Define ### */

#define MAX          5                                 /* for maximum access */
#define MAX_CHR1   207
#define MAX_CHR2    26
#define MAX_CHR3    26
#define MAX_CHR4    45
#define MAX_KEY1    41
#define MAX_KEY4    45

/* ### Global Variables ### */

char buffer[MAX][3];
int  number[MAX];

char *table1[MAX_CHR1] = {
  "Ç†",  "Ç¢",  "Ç§",  "Ç¶",  "Ç®",  "Ç©",  "Ç´",  "Ç≠",  "ÇØ",  "Ç±",
  "Ç≥",  "Çµ",  "Ç∑",  "Çπ",  "Çª",  "ÇΩ",  "Çø",  "Ç¬",  "Çƒ",  "Ç∆",
  "Ç»",  "Ç…",  "Ç ",  "ÇÀ",  "ÇÃ",  "ÇÕ",  "Ç–",  "Ç”",  "Ç÷",  "ÇŸ",
  "Ç‹",  "Ç›",  "Çﬁ",  "Çﬂ",  "Ç‡",  "Ç‚",  "Ç¢",  "Ç‰",  "Ç¢Ç•","ÇÊ",
  "ÇÁ",  "ÇË",  "ÇÈ",  "ÇÍ",  "ÇÎ",  "ÇÌ",  "Ç§Ç°","Ç§",  "Ç§Ç•","Ç",
  "Ç™",  "Ç¨",  "ÇÆ",  "Ç∞",  "Ç≤",  "Ç¥",  "Ç∂",  "Ç∏",  "Ç∫",  "Çº",
  "Çæ",  "Ç¿",  "Ç√",  "Ç≈",  "Ç«",  "ÇŒ",  "Ç—",  "Ç‘",  "Ç◊",  "Ç⁄",
  "Çœ",  "Ç“",  "Ç’",  "Çÿ",  "Ç€", "Ç§ÅJÇü","Ç§ÅJÇ°","Ç§ÅJ","Ç§ÅJÇ•","Ç§ÅJÇß",
  "Ç∂Ç·","Ç∂",  "Ç∂Ç„","Ç∂Ç•","Ç∂ÇÂ","Ç”Çü","Ç”Ç°","Ç”",  "Ç”Ç•","Ç”Çß",
  "Çü",  "Ç°",  "Ç£",  "Ç•",  "Çß",  "Ç´Ç·","Ç´Ç°","Ç´Ç„","Ç´Ç•","Ç´ÇÂ",
  "ÇµÇ·","ÇµÇ°","ÇµÇ„","ÇµÇ•","ÇµÇÂ","ÇøÇ·","ÇøÇ°","ÇøÇ„","ÇøÇ•","ÇøÇÂ",
  "Ç…Ç·","Ç…Ç°","Ç…Ç„","Ç…Ç•","Ç…ÇÂ","Ç–Ç·","Ç–Ç°","Ç–Ç„","Ç–Ç•","Ç–ÇÂ",
  "Ç›Ç·","Ç›Ç°","Ç›Ç„","Ç›Ç•","Ç›ÇÂ","ÇËÇ·","ÇËÇ°","ÇËÇ„","ÇËÇ•","ÇËÇÂ",
  "Ç¨Ç·","Ç¨Ç°","Ç¨Ç„","Ç¨Ç•","Ç¨ÇÂ","Ç∂Ç·","Ç∂Ç°","Ç∂Ç„","Ç∂Ç•","Ç∂ÇÂ",
  "Ç¿Ç·","Ç¿Ç°","Ç¿Ç„","Ç¿Ç•","Ç¿ÇÂ","Ç—Ç·","Ç—Ç°","Ç—Ç„","Ç—Ç•","Ç—ÇÂ",
  "Ç“Ç·","Ç“Ç°","Ç“Ç„","Ç“Ç•","Ç“ÇÂ","Ç∂Ç·","Ç∂Ç°","Ç∂Ç„","Ç∂Ç•","Ç∂ÇÂ",
  "Ç”Ç·","Ç”Ç°","Ç”Ç„","Ç”Ç•","Ç”ÇÂ","ÇµÇ·","Çµ",  "ÇµÇ„","ÇµÇ•","ÇµÇÂ",
  "ÇøÇ·","Çø",  "ÇøÇ„","ÇøÇ•","ÇøÇÂ","ÇøÇ·","ÇøÇ°","ÇøÇ„","ÇøÇ•","ÇøÇÂ",
  "Ç¬Çü","Ç¬Ç°","Ç¬",  "Ç¬Ç•","Ç¬Çß","Ç≈Ç·","Ç≈Ç°","Ç≈Ç„","Ç≈Ç•","Ç≈ÇÂ",
  "ÇƒÇ·","ÇƒÇ°","ÇƒÇ„","ÇƒÇ•","ÇƒÇÂ","Ç·",  "Ç°",  "Ç„",  "Ç•",  "ÇÂ",
  "Ç¡",  "Ç¡",  "Ç¡",  "Ç¡",  "Ç¡",
  "ÇÒ",  "Ç¡"
  };

char *table2[MAX_CHR2] = {
  "ÇÅ",  "ÇÇ",  "ÇÉ",  "ÇÑ",  "ÇÖ",  "ÇÜ",  "Çá",  "Çà",  "Çâ",  "Çä",
  "Çã",  "Çå",  "Çç",  "Çé",  "Çè",  "Çê",  "Çë",  "Çí",  "Çì",  "Çî",
  "Çï",  "Çñ",  "Çó",  "Çò",  "Çô",  "Çö"
  };

char *table3[MAX_CHR3] = {
  "Ç`",  "Ça",  "Çb",  "Çc",  "Çd",  "Çe",  "Çf",  "Çg",  "Çh",  "Çi",
  "Çj",  "Çk",  "Çl",  "Çm",  "Çn",  "Ço",  "Çp",  "Çq",  "Çr",  "Çs",
  "Çt",  "Çu",  "Çv",  "Çw",  "Çx",  "Çy"
  };

char *table4[MAX_CHR4] = {
  "  ",  "  ",  "ÇP",  "ÇQ",  "ÇR",  "ÇS",  "ÇT",  "ÇU",  "ÇV",  "ÇW",
  "ÇX",  "ÇO",  "ÅI",  "Åç",  "Åî",  "Åê",  "Åì",  "Åï",  "Åå",  "Åi",
  "Åj",  "Å|",  "ÅO",  "Åè",  "Åó",  "Åm",  "ÅG",  "ÅF",  "Ån",  "ÅC",
  "ÅD",  "Å^",  "Åè",  "ÅÅ",  "Å`",  "Åb",  "ÅM",  "Åo",  "Å{",  "Åñ",
  "Åp",  "ÅÉ",  "ÅÑ",  "ÅH",  "ÅQ"
  };

char *key1[MAX_KEY1] = {
  "\0", "k",  "s",  "t",  "n",  "h",  "m",  "y",  "r",  "w",
  "g",  "z",  "d",  "b",  "p",  "v",  "j",  "f",  "x",  "ky",
  "sy", "ty", "ny", "hy", "my", "ry", "gy", "zy", "dy", "by",
  "py", "jy", "fy", "sh", "ch", "cy", "ts", "dh", "th", "xy",
  "xt"
  };

char *key4[MAX_KEY4] = {
  "\n", " ",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",
  "9",  "0",  "!",  "\"", "#",  "$",  "%",  "&",  "'",  "(",
  ")",  "-",  "^",  "\\", "@",  "[",  ";",  ":",  "]",  ",",
  ".",  "/",  "\\", "=",  "~",  "|",  "`",  "{",  "+",  "*",
  "}",  "<",  ">",  "?",  "_"
  };

/* =-=-=-=-=-=-=-=-= */

void NumSet(int m, int n)
{
  number[m] = ((0 <= n)&&(n <= 2)) ? n : number[m];
  buffer[m][number[m]] = '\0';

} /* end of NumSet */


void BufferCheck(int m, char **retc, int *reti)
{
  *retc = buffer[m];
  *reti = strlen(*retc);

} /* end of BufferCheck */


void Word(int m, char ch, char **retc, int *reti)
{
  char dummy[16];
  int  i;

  *retc = NULL;
                                                               /* ch == BION */
  if (Isboin(ch) >= 0) {
    switch (number[m]) {
    case 1:
      i = Code(buffer[m][0], '\0', ch);
      if (i < MAX_CHR1) {
	*retc = table1[i];
	break;
      } else {
	*retc = table2[buffer[m][0]-'a'];
      }
    case 0:
      sprintf(dummy, "%s%s", *retc, table1[Code('\0', '\0', ch)]);
      *retc = dummy;
      break;
    case 2:
      *retc = table1[Code(buffer[m][0], buffer[m][1], ch)];
      break;
    }
    number[m] = 0;

                                                               /* ch == SIIN */
  } else if (islower(ch)) {
    switch (number[m]) {
    case 0:
      buffer[m][number[m]++] = ch;
      *retc = NULL;
      break;
    case 2:
      *retc = table2[buffer[m][0]-'a'];
      buffer[m][0] = buffer[m][1];
    case 1:
      buffer[m][1] = ch;
      buffer[m][2] = '\0';
      if (buffer[m][0] == buffer[m][1]) {
	number[m] = (buffer[m][0] == 'n') ? 0 : 1;
	sprintf(dummy, "%s%s", *retc, table1[Code(buffer[m][0], buffer[m][0],'\0')]);
	*retc = dummy;
      } else {
	for (i = 0; i < MAX_KEY1; i++) {
	  if (!strcmp(key1[i], buffer[m])) {
	    break;
	  }
	}
	if (i >= MAX_KEY1) {
	  sprintf(dummy, "%s%s", *retc, table2[buffer[m][0]-'a']);
	  *retc = dummy;
	  buffer[m][0] = ch;
	  number[m] = 1;
	} else {
	  number[m] = 2;
	}
      }
      break;
    }

                                                    /* ch == UPPER or SYMBOL */
  } else {
    for (i = 0; i < number[m]; i++) {
      sprintf(dummy, "%s%s", *retc, table2[buffer[m][i]-'a']);
      *retc = dummy;
    }
    if (isupper(ch)) {
      sprintf(dummy, "%s%s", *retc, table3[ch-'A']);
    } else {
      buffer[m][0] = ch;
      buffer[m][1] = '\0';
      for (i = 0; i < MAX_KEY4; i++) {
	if (!strcmp(key4[i], buffer[m])) {
	  break;
	}
      }
      if (i < MAX_KEY4) {
	sprintf(dummy, "%s%s", *retc, table4[i]);
      }
    }
    number[m] = 0;
    *retc = dummy;

  }
  buffer[m][number[m]] = '\0';
  *reti = strlen(*retc);

} /* end of Word */


int Code(char ch0, char ch1, char ch2)
{
  char str[3];
  int  i, reti;

  if ((ch0 == ch1)&&(ch2 == '\0')) {
    if (ch0 == 'n') {
      reti = MAX_CHR1-2;
    } else {
      reti = MAX_CHR1-1;
    }
  } else {
    str[0] = ch0;
    str[1] = ch1;
    str[2] = '\0';
    for (i = 0; i < MAX_KEY1; i++) {
      if (!strcmp(key1[i], str)) {
	break;
      }
    }
    if (i < MAX_KEY1) {
      switch (ch2) {
      case 'a':
	reti = i*5 + 0;
	break;
      case 'i':
	reti = i*5 + 1;
	break;
      case 'u':
	reti = i*5 + 2;
	break;
      case 'e':
	reti = i*5 + 3;
	break;
      case 'o':
	reti = i*5 + 4;
	break;
      case '\0':
	reti = i*5 + 0;
	break;
      default:
	reti = MAX_CHR1;
      }
    } else {
      reti = MAX_CHR1;
    }
  }
  return reti;

} /* end of Code */


int Isboin(char ch)
{
  int  reti;

  switch (ch) {
  case 'a':
    reti = 0;
    break;
  case 'i':
    reti = 1;
    break;
  case 'u':
    reti = 2;
    break;
  case 'e':
    reti = 3;
    break;
  case 'o':
    reti = 4;
    break;
  default:
    reti = -1;
  }

  return reti;

} /* end of Isboin */
