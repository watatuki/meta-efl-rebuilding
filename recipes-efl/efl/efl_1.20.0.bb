require ${BPN}_${PV}.inc

SRC_URI = "\
   git://git.enlightenment.org/core/efl.git \
   file://fix-configure-wayland-protocols-path.patch \
"

SRCREV = "0bd8259da885c7cc81293c9d9e4fe0fa87dfd855"

# Temporary disable until error like the one following are fixed
# efl-native/2_1.8.4-r0/efl-1.8.4/src/lib/eet/.libs/libeet.so: file not recognized: File truncated
# collect2: error: ld returned 1 exit status
# x86_64-linux-libtool: install: error: relink `modules/evas/savers/tiff/module.la' with the above command before installing it
# Makefile:11031: recipe for target 'install-savertiffpkgLTLIBRARIES' failed
PARALLEL_MAKE_class-native = ""

S = "${WORKDIR}/git"
B = "${S}"

