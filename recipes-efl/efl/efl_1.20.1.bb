require ${BPN}_${PV}.inc

SRC_URI = "\
   git://git.enlightenment.org/core/efl.git;branch=efl-1.20 \
   file://fix-configure-wayland-protocols-path.patch \
"

SRCREV = "dab6548dbe05ee8f58d8ffa9f1cc3269059d87e5"

S = "${WORKDIR}/git"
B = "${S}"

