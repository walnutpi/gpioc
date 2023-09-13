#ifndef _COMMON_H
#define _COMMON_H


#define	INPUT			 0
#define	OUTPUT			 1

#define	PUD_OFF			 0
#define	PUD_DOWN		 1
#define	PUD_UP			 2

#define	CHIP_H616       1

static char *chips_compatible[]={
    "占位符",
    "sun50i-h616"
};

int detect();

#endif