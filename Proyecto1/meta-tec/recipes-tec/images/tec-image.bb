DESCRIPTION = "Simple helloworld application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file:///home/leonardo/rpi/meta-tec/recipes-tec/rgb2yuv_c/rgb2yuv_c.c \
	   file:///home/leonardo/rpi/meta-tec/recipes-tec/rgb2yuv_c/image.rgb \
	   file:///home/leonardo/rpi/meta-tec/recipes-tec/rgb2yuv_intrinsics/rgb2yuv_intrinsics.c \
	   file:///home/leonardo/rpi/meta-tec/recipes-tec/rgb2yuv_intrinsics/image.rgb \
	   file:///home/leonardo/rpi/meta-tec/recipes-tec/rgb2yuv_intrinsics/intrinsics_results.pdf"

S = "${WORKDIR}"
FILES_${PN} += "/usr/share/tec/intrinsics_results.pdf"

do_compile() {
	${CXX} /home/leonardo/rpi/meta-tec/recipes-tec/rgb2yuv_c/rgb2yuv_c.c ${LDFLAGS} -o rgb2yuv_c
	${CXX} -static -mfpu=neon /home/leonardo/rpi/meta-tec/recipes-tec/rgb2yuv_intrinsics/rgb2yuv_intrinsics.c -o rgb2yuv_intrinsics
}

# Install the C converter code
do_install() {
	install -d ${D}${bindir}
	install -m 0755 rgb2yuv_c ${D}${bindir}
}

# Install the NEON intrinsics converter code
do_install_append() {
	install -d ${D}${bindir}
	install -m 0755 rgb2yuv_intrinsics ${D}${bindir}
}

# Install the documentation (PDF)
do_install_append() {
	install -d ${D}/usr/share/tec
	install -m 0755 /home/leonardo/rpi/meta-tec/recipes-tec/rgb2yuv_intrinsics/intrinsics_results.pdf ${D}/usr/share/tec/intrinsics_results.pdf
}
