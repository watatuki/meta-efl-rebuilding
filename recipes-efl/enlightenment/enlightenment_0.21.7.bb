require ${BPN}.inc

SRCNAME = "enlightenment"

S = "${WORKDIR}/${SRCNAME}-${PV}"

# couple of modules needed for illume2 (mobile) profile were removed in
# http://git.enlightenment.org/core/enlightenment.git/commit/src/modules/Makefile.mk?id=1be76d599ca27f820b58b8186c5f73d9844c67ca
# and replacements aren't included yet, if you want to use e-wm on device with small screen, better stay with 0.18 release
DEFAULT_PREFERENCE = "-1"

SRC_URI = "\
    ${E_RELEASES}/apps/${SRCNAME}/${SRCNAME}-${PV}.tar.gz \
    file://enlightenment_start.oe \
    file://applications.menu \
"

SRC_URI[md5sum] = "27fa063b9fee37347fc84a8e259a4362"
SRC_URI[sha256sum] = "914a305d1d1d8f51f2ae0c6a6b5a69f7cb783f701ed4d5d49efb2d57c6807df6"

