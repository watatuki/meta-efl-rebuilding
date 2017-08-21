require ${BPN}_1.20.inc

SRC_URI = "\
   git://git.enlightenment.org/core/efl.git;branch=efl-1.20 \
   file://fix-configure-wayland-protocols-path.patch \
"

SRCREV = "4dee485ddd03452d51d0e27d5d4d4fa15a138783"

S = "${WORKDIR}/git"
B = "${S}"

