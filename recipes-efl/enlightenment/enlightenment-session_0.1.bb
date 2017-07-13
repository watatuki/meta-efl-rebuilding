DESCRIPTION = "Mini X session files for enlightenment"

LICENSE = "MIT"

SECTION = "x11"

LIC_FILES_CHKSUM = "file://COPYING;md5=1b71f681713d1256e1c23b0890920874"

SRC_URI = "file://session \
           file://COPYING \
           "

S = "${WORKDIR}"

do_install() {
	install -d ${D}${sysconfdir}/mini_x
	install -m 0755 ${WORKDIR}/session ${D}${sysconfdir}/mini_x/session
}
