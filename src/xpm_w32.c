/* vi:set ts=8 sts=4 sw=4:
 *
 * Load XPM image.
 *
 * This function is placed in separate file because Xpm headers conflict with
 * Vim ones :(
 *
 * Written by Sergey Khorev.
 * http://iamphet.nm.ru/vim/index.html
 */

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

/* reduced def from Vim.h */
#ifndef __ARGS
# if defined(__STDC__) || defined(__GNUC__) || defined(WIN3264)
#  define __ARGS(x) x
# else
#  define __ARGS(x) ()
# endif
#endif

#include "xpm_w32.h"

/* Engage Windows support in libXpm */
#define FOR_MSW

#include "xpm/x86/../include/xpm.h"

/*
 * Tries to load an Xpm image from the file "filename".
 * Returns -1 on failure.
 * Returns 0 on success and stores image and mask BITMAPS in "hImage" and
 * "hShape".
 */
    int
LoadXpmImage(filename, hImage, hShape)
    char    *filename;
    HBITMAP *hImage;
    HBITMAP *hShape;
{
    XImage	    *img;  /* loaded image */
    XImage	    *shp;  /* shapeimage */
    XpmAttributes   attr;
    int		    res;
    HDC		    hdc = CreateCompatibleDC(NULL);

    attr.valuemask = 0;
    res = XpmReadFileToImage(&hdc, filename, &img, &shp, &attr);
    DeleteDC(hdc);
    if (res < 0)
	return -1;
    if (shp == NULL)
    {
	if (img)
	    XDestroyImage(img);
	return -1;
    }
    *hImage = img->bitmap;
    *hShape = shp->bitmap;
    return 0;
}
