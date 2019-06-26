DESCRIPTION = "Simple helloworld application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file:///home/leonardo/rpi/meta-tec/recipes-tec/myhello.c \
	   file:///home/leonardo/rpi/meta-tec/recipes-tec/intrinsics_results.pdf"

S = "${WORKDIR}"
FILES_${PN} += "/usr/share/tec/intrinsics_results.pdf"

do_compile() {
	${CC} /home/leonardo/rpi/meta-tec/recipes-tec/myhello.c ${LDFLAGS} -o myhello
}

# Install the converter code
do_install() {
	install -d ${D}${bindir}
	install -m 0755 myhello ${D}${bindir}
}

# Install the documentation (PDF)
do_install_append() {
	install -d ${D}/usr/share/tec
	install -m 0755 /home/leonardo/rpi/meta-tec/recipes-tec/intrinsics_results.pdf ${D}/usr/share/tec/intrinsics_results.pdf
}
