require ${BPN}.inc

S = "${WORKDIR}/${SRCNAME}-${PV}"

SRC_URI = "\
    ${E_RELEASES}/apps/${SRCNAME}/${SRCNAME}-${PV}.tar.gz \
    file://enlightenment_start.oe \
    file://applications.menu \
"

SRC_URI[md5sum] = "bf2a87f293e26467b5e5b3c1002c0021"
SRC_URI[sha256sum] = "44332443b39ac6f0563713c3d85acbbba0011dd7659e6b7d500ec09e05896197"

