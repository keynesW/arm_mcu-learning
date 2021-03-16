###############################################################
#
# Purpose: Makefile for "M-JPEG Streamer"
# Author.: Tom Stoeveken (TST)
# Version: 0.3
# License: GPL
#
###############################################################

CC = arm-none-linux-gnueabi-gcc

OTHER_HEADERS = ../../mjpg_streamer.h ../../utils.h ../output.h ../input.h

CFLAGS += -O2 -DLINUX -D_GNU_SOURCE  -Wall -shared -fPIC -I /home/linux/workdir/fs4412/camera/jpeg-install/include
#CFLAGS += -DDEBUG
LFLAGS += -lpthread -ldl -L /home/linux/workdir/fs4412/camera/jpeg-install/lib -ljpeg

all: input_uvc.so

clean:
	rm -f *.a *.o core *~ *.so *.lo

input_uvc.so: $(OTHER_HEADERS) input_uvc.c v4l2uvc.lo jpeg_utils.lo dynctrl.lo
	$(CC) $(CFLAGS)  -o $@ input_uvc.c v4l2uvc.lo jpeg_utils.lo dynctrl.lo $(LFLAGS)

v4l2uvc.lo: huffman.h uvc_compat.h uvcvideo.h v4l2uvc.c v4l2uvc.h
	$(CC) -c $(CFLAGS) -o $@ v4l2uvc.c

jpeg_utils.lo: jpeg_utils.c jpeg_utils.h
	$(CC) -c $(CFLAGS) -o $@ jpeg_utils.c

dynctrl.lo: dynctrl.c dynctrl.h uvcvideo.h
	$(CC) -c $(CFLAGS) -o $@ dynctrl.c
