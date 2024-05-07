include ../../toolchain.mk
include ../common.mk

LDFLAGS += -Wl,--wrap=glutInit \
		   -Wl,--wrap=glutInitDisplayMode \
		   -Wl,--wrap=glutInitWindowSize \
		   -Wl,--wrap=glutInitWindowPosition \
		   -Wl,--wrap=glutCreateWindow \
		   -Wl,--wrap=glutDisplayFunc \
		   -Wl,--wrap=glClear \
		   -Wl,--wrap=glutSwapBuffers
