DESCRIPTION = "Simple helloworld application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file:///home/leonardo/rpi/meta-tec/recipes-tec/myhello.c"

S = "${WORKDIR}"

do_compile() {
	${CC} /home/leonardo/rpi/meta-tec/recipes-tec/myhello.c ${LDFLAGS} -o myhello
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 myhello ${D}${bindir}
}
