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

SRC_URI[md5sum] = "bf2a87f293e26467b5e5b3c1002c0021"
SRC_URI[sha256sum] = "44332443b39ac6f0563713c3d85acbbba0011dd7659e6b7d500ec09e05896197"

