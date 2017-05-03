/*
// phone.c
*/

/* compile command */
/* % cc -Aa -I/usr/include/X11R5 -L/usr/lib/X11R5 phone.c ninput.c -o phone -lX11 */

/* ### Include Files ### */

#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include "phone.h"
#include "ninput.h"

/* ### Constant Define ### */

#define MAX          5                                 /* for maximum access */
#define FONT_X       24                                     /* for font_size */
#define FONT_Y       32                                     /* for font_size */
#define SPACE1       16                                   /* infomation line */

#define HEIGHT_1     SPACE1                                /* for infomation */
#define HEIGHT_2     FONT_Y+4*2                            /* for DrawString */
#define MES_HEIGHT   (HEIGHT_1+HEIGHT_2)
#define Y_1          0                                     /* for infomation */
#define INFO_HEIGHT  HEIGHT_1-4                            /* for infomation */
#define Y_2          HEIGHT_1                              /* for DrawString */
#define BASE_HEIGHT  HEIGHT_2-9                            /* for DrawString */

#define W0_WIDTH     FONT_X*36                       /* initial window width */
#define MIN_W0_WIDTH FONT_X*12                       /* minimum window width */
#define MAX_W0_WIDTH FONT_X*48        /* pixmap width & maximum window width */

/* ### Global Variables ### */

Display *dpy[MAX];
Window  w[MAX];
Pixmap  pix[MAX];
GC      gc_b[MAX], gc_w[MAX], gc_j[MAX];
unsigned int    width[MAX], height;
char    buf[64], dpy_name[MAX][32], user_name[MAX][32];
int     i, j, num, act[MAX];
int     n_flag[MAX];

static char     title[5][20] = {
  "a_phone send",
  "a_phone recieve1",
  "a_phone recieve2",
  "a_phone recieve3",
  "a_phone recieve4" };
static char     fontname0[] =
  "fg-16";
static char     fontname1[] =
  "-adobe-courier-medium-o-normal--34-240-100-100-m-200-iso8859-1";
static char     fontname2[] =
  "jpn.12x24";

/* =-=-=-=-=-=-=-=-= */
main(int argc, char *argv[])
{
  XEvent  event;
  Font    font[MAX][3];
  KeySym  key;
  XSizeHints      hint;
  int     black[MAX], white[MAX];

  Window  dummy0;
  int     dummy1;
  unsigned int    dummy2;
  int     str;
  char    *out;

                                             /* user_name & display_name set */
  if ((2 <= argc)&&(argc <= MAX)) {
    sprintf(dpy_name[0], "%s", getenv("DISPLAY"));
    sprintf(user_name[0], "%s", getenv("USER"));
    for (i = 1; i < argc; i++) {
                                                         /* alias user check */
      Alias(argv[i], user_name[i], dpy_name[i]);
                                                       /* display_name check */
      if (!strchr(dpy_name[i], ':')) {
	sprintf(dpy_name[i], "%s:0", dpy_name[i]);
      }
    }
  } else {                                                    /* print usage */
    fprintf(stderr,
	    "Usage : %s hostname [hostname] [hostname] [hostname]\n", argv[0]);
    exit(0);
  }
  fprintf(stderr, "\n");

                                                        /* display open loop */
  num = 0;
  for (i = 0; i < MAX; i++) {
    if (argc <= i) {
      act[i] = -1;
    } else if ((dpy[i] = XOpenDisplay(dpy_name[i]) ) == NULL) {
      fprintf(stderr,
	      "Can't open display ! [%s@%s]\n", user_name[i], dpy_name[i]);
      act[i] = -1;
    } else {
      act[i] = num++;
    }
  }

                                                        /* abort (no member) */
  if (num <= 1) {
    fprintf(stderr, "No members to call !\n");
    for (i = 0; i < MAX; i++) {
      if (act[i] >= 0) {
	XCloseDisplay(dpy[i]);
      }
    }
    exit(0);
  }

                                                   /* window initialize loop */
  for (i = 0; i < MAX; i++) {
    if (act[i] >= 0) {
                                                                /* get pixel */
      black[i] = BlackPixel(dpy[i], 0);
      white[i] = WhitePixel(dpy[i], 0);

                                                              /* window open */
      height = MES_HEIGHT*num;
      w[i] = XCreateSimpleWindow(dpy[i], RootWindow(dpy[i], 0),
				 0, 0, W0_WIDTH, height,
				 1, black[i], white[i]);

                                                              /* pixmap open */
      pix[i] = XCreatePixmap(dpy[i], w[i],
			     MAX_W0_WIDTH, height,
			     DefaultDepth(dpy[i], 0));

                                                             /* select input */
      XSelectInput(dpy[i], w[i],
		   ExposureMask | StructureNotifyMask |
		   KeyPressMask | ButtonPressMask);

                                                                /* create gc */
      gc_b[i] = XCreateGC(dpy[i], w[i], 0, NULL);
      gc_w[i] = XCreateGC(dpy[i], w[i], 0, NULL);
      gc_j[i] = XCreateGC(dpy[i], w[i], 0, NULL);
      XSetForeground(dpy[i], gc_b[i], black[i]);
      XSetForeground(dpy[i], gc_w[i], white[i]);
      XSetForeground(dpy[i], gc_j[i], black[i]);

                                                                 /* set hint */
      hint.flags = PMaxSize | PMinSize;
      hint.min_width  = MIN_W0_WIDTH;
      hint.max_width  = MAX_W0_WIDTH;
      hint.min_height = height;
      hint.max_height = height;
      XSetStandardProperties(dpy[i], w[i], title[i], title[i],
			     None, NULL, 0, &hint);

                                                  /* set font for infomation */
      font[i][0] = XLoadFont(dpy[i], fontname0);
      XSetFont(dpy[i], gc_w[i], font[i][0]);
                                                  /* set font for DrawString */
      font[i][1] = XLoadFont(dpy[i], fontname1);
      XSetFont(dpy[i], gc_b[i], font[i][1]);
                                                     /* set font for DrawJPN */
      font[i][2] = XLoadFont(dpy[i], fontname2);
      XSetFont(dpy[i], gc_j[i], font[i][2]);

                                                               /* window map */
      XMapWindow(dpy[i], w[i]);

                                                              /* width check */
      XGetGeometry(dpy[i], w[i], &dummy0,
		   &dummy1, &dummy1, &width[i], &dummy2, &dummy2, &dummy2);
      XFlush(dpy[i]);

                                               /* window & pixmap initialize */
      XFillRectangle(dpy[i], pix[i], gc_w[i], 0, 0, MAX_W0_WIDTH, height);
      NumSet(i, 0);
      n_flag[i] = 0;
      BufferCheck(i, &out, &str);
      InfoPrint(i, n_flag[i], out);
      XFlush(dpy[i]);
    }
  }

                                                                /* main loop */
  while (1) {
    for (i = 0; i < MAX; i++) {
                                                     /* event loop (no wait) */
      if (act[i] >= 0) {
	if (XPending(dpy[i])) {
	  XNextEvent(dpy[i], &event);
                                                         /* Expose -> redraw */
	  if (event.type == Expose) {
	    XCopyArea(dpy[i], pix[i], w[i], gc_w[i],
		      MAX_W0_WIDTH-width[i], 0, width[i], height, 0, 0);
	  }

                                        /* ConfigureNotify -> partial redraw */
	  else if (event.type == ConfigureNotify) {
	    XGetGeometry(dpy[i], w[i], &dummy0,
			 &dummy1, &dummy1, &width[i], &dummy2,
			 &dummy2, &dummy2);
	    XFlush(dpy[i]);
	    BufferCheck(i, &out, &str);
	    InfoPrint(i, n_flag[i], out);
	    XCopyArea(dpy[i], pix[i], w[i], gc_w[i],
		      MAX_W0_WIDTH-width[i], 0, width[i], height, 0, 0);
	  }

                                                   /* KeyPress -> print text */
	  else if (event.type == KeyPress) {
	    XLookupString((XKeyEvent*)&event, buf, 2, &key, NULL);
	    buf[1] = '\0';
	    if ((!IsCursorKey(key))&&
		(!IsFunctionKey(key))&&
		(!IsMiscFunctionKey(key))&&
		(!IsModifierKey(key))&&
		(!IsPFKey(key))) {
	      switch (key) {
                                                       /* BS or Del -> erase */
	      case XK_BackSpace:
	      case XK_Delete:
                                            /* jpn buf != empty -> buf clear */
		if (n_flag[i] == 1) {
		  BufferCheck(i, &out, &str);
		  if (str > 0) {
		    NumSet(i, 0);
		    InfoPrint(i, n_flag[i], out);
		    break;
		  }
		}
                                                               /* else erase */
		TextBackPrint(FONT_X, MES_HEIGHT*act[i]+Y_2);
		break;
	      default:
                                                           /* print 8bit chr */
		if (n_flag[i] == 0) {
		  TextPrint(n_flag[i],
			    FONT_X, MES_HEIGHT*act[i]+Y_2,
			    1);
		} else {
                                                          /* print 16bit chr */
		  Word(i, buf[0], &out, &str);
		  if (str > 0) {
		    strcpy(buf, out);
		    TextPrint(n_flag[i],
			      FONT_X*str/2, MES_HEIGHT*act[i]+Y_2,
			      str);
		  }
		  BufferCheck(i, &out, &str);
		  InfoPrint(i, n_flag[i], out);
		}
	      }
	    }
	  }

	  else if (event.type == ButtonPress) {
                                         /* ButtonPress1 -> jpn_input on/off */
	    if (event.xbutton.button == Button1) {
	      n_flag[i] = !n_flag[i];
	      NumSet(i, 0);
	      BufferCheck(i, &out, &str);
	      InfoPrint(i, n_flag[i], out);
	    }
                                            /* ButtonPress3 -> program abort */
	    if (event.xbutton.button == Button3) {
	      fprintf(stderr, "Exit. [%s@%s]\n", user_name[i], dpy_name[i]);

	      for (j = 0; j < MAX; j++) {
		if (j != i) {
		  if (act[j] >= 0) {
                                                            /* reflesh act[] */
		    if (act[j] > act[i]) {
		      act[j] -= 1;
		    }
                                                           /* reflesh pixmap */
		    XCopyArea(dpy[j], pix[j], pix[j], gc_b[j],
			      0, MES_HEIGHT*(act[i]+1),
			      MAX_W0_WIDTH, height-MES_HEIGHT*(act[i]+1),
			      0, MES_HEIGHT*act[i]);
                                                             /* reflesh hint */
		    hint.flags = PMaxSize | PMinSize;
		    hint.min_width  = MIN_W0_WIDTH;
		    hint.max_width  = MAX_W0_WIDTH;
		    hint.min_height = height-MES_HEIGHT;
		    hint.max_height = height-MES_HEIGHT;
		    XSetStandardProperties(dpy[j], w[j], title[j], title[j],
					   None, NULL, 0, &hint);
                                                           /* reflesh window */
		    XResizeWindow(dpy[j], w[j], width[j], height-MES_HEIGHT);
		    XFlush(dpy[j]);
		  }
		}
	      }
                                                   /* reflesh some variables */
	      height -= MES_HEIGHT;
	      act[i] = -1;
	      num--;
	      Destroy(i);
	    }
	  }

	}

      }

    }
                                                        /* abort (no member) */
    if (num <= 1) {
      for (i = 0; i < MAX; i++) {
	if (act[i] >= 0) {
	  Destroy(i);
	}
      }
      exit(0);
    }
  }

}


/**/

void Destroy(int m)
{
  XFreeGC(dpy[m], gc_b[m]);
  XFreeGC(dpy[m], gc_w[m]);
  XFreeGC(dpy[m], gc_j[m]);
  XDestroyWindow(dpy[m], w[m]);
  XCloseDisplay(dpy[m]);

} /* end of Destroy */


void TextPrint(int mode, int dot, int height, int len)
{
  int  p;

  for (p = 0; p < MAX; p++) {
    if (act[p] >= 0) {
      XCopyArea(dpy[p], pix[p], pix[p], gc_b[p],
		dot, height, MAX_W0_WIDTH-dot, HEIGHT_2,
		0, height);
      XFillRectangle(dpy[p], pix[p], gc_w[p],
		     MAX_W0_WIDTH-dot, height, dot, HEIGHT_2);
      if (mode == 0) {
	XDrawString(dpy[p], pix[p], gc_b[p],
		    MAX_W0_WIDTH-dot, height+BASE_HEIGHT, buf, len);
      } else {
	XDrawString(dpy[p], pix[p], gc_j[p],
		    MAX_W0_WIDTH-dot, height+BASE_HEIGHT, buf, len);
      }
      XCopyArea(dpy[p], pix[p], w[p], gc_b[p],
		MAX_W0_WIDTH-width[p], height, width[p], HEIGHT_2, 0, height);
    }
  }

} /* end of TextPrint */


void TextBackPrint(int dot, int height)
{
  int  p;

  for (p = 0; p < MAX; p++) {
    if (act[p] >= 0) {
      XCopyArea(dpy[p], pix[p], pix[p], gc_b[p],
		0, height, MAX_W0_WIDTH-dot, HEIGHT_2,
		dot, height);
      XFillRectangle(dpy[p], pix[p], gc_w[p],
		     0, height, dot, HEIGHT_2);
      XCopyArea(dpy[p], pix[p], w[p], gc_b[p],
		MAX_W0_WIDTH-width[p], height, width[p], HEIGHT_2, 0, height);
    }
  }

} /* end of TextBackPrint */


void InfoPrint(int m, int mode, char *retc)
{
  int  p;

  for (p = 0; p < MAX; p++) {
    if (act[p] >= 0) {
      XFillRectangle(dpy[m], pix[m], gc_b[m],
		     0, MES_HEIGHT*act[p]+Y_1,
		     MAX_W0_WIDTH, HEIGHT_1);
      sprintf(buf, " %s [ %s ]", user_name[p], dpy_name[p]);
      XDrawString(dpy[m], pix[m], gc_w[m],
		  MAX_W0_WIDTH-width[m], MES_HEIGHT*act[p]+INFO_HEIGHT,
		  buf, strlen(buf));
    }
  }
  if (mode == 1) {
    sprintf(buf, "[%s]", retc);
    XDrawString(dpy[m], pix[m], gc_w[m],
		MAX_W0_WIDTH-FONT_X*3, MES_HEIGHT*act[m]+INFO_HEIGHT,
		buf, strlen(buf));
  }
  XCopyArea(dpy[m], pix[m], w[m], gc_b[m],
	    MAX_W0_WIDTH-width[m], 0, width[m], height, 0, 0);

} /* end of InfoPrint */


int Alias(char *alias, char *ret1, char *ret2)
{
  FILE *fp;
  char buf1[32], buf2[32];
  int  flag;

  flag = 0;
  sprintf(buf1, "%s/.phone", getenv("HOME"));
  if ((fp = fopen(buf1, "r")) != NULL) {

    while (1) {
      fscanf(fp, "%s", buf1);
      if (!strcmp(buf1, "NAME")) {
	fscanf(fp, "%s %s %s", buf2, ret1, ret2);
	if (!strcmp(buf2, alias)) {
	  flag = 1;
	  break;
	}
      } else if (!strcmp(buf1, "REM")) {
	while (fgetc(fp) != '\n')
	  ;
      } else if (!strcmp(buf1, "END")) {
	break;
      }
    }

  }

  if (flag == 0) {
    strcpy(ret1, "???");
    strcpy(ret2, alias);
  }

  fclose(fp);

  return flag;

} /* end of Alias */
