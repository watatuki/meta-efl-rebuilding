require ${BPN}_1.19.inc

SRC_URI = "\
   git://git.enlightenment.org/core/efl.git;branch=efl-1.19 \
   file://fix-configure-wayland-protocols-path.patch \
"

SRCREV = "85cd388b9669f339c133a0c02431d632408f5992"

S = "${WORKDIR}/git"
B = "${S}"

