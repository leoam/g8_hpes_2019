converter: rgb2yuv_c.c
		g++ rgb2yuv_c.c -o converter

intrinsics: rgb2yuv_intrinsics.c
		arm-linux-gnueabihf-g++ -static -mfpu=neon rgb2yuv_intrinsics.c -o intrinsics
