require ${BPN}.inc

S = "${WORKDIR}/${SRCNAME}-${PV}"

SRC_URI = "\
    ${E_RELEASES}/apps/${SRCNAME}/${SRCNAME}-${PV}.tar.gz \
    file://enlightenment_start.oe \
    file://applications.menu \
"

SRC_URI[md5sum] = "800bd736dcea5d7a5851836af0e298ff"
SRC_URI[sha256sum] = "6b328eec14c5b658b8b3f448d9b65dfc189d98db7b92610e56c438f1232f4973"

