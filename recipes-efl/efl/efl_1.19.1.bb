require ${BPN}.inc

SRC_URI = "\
    ${E_RELEASES}/libs/${SRCNAME}/${SRCNAME}-${SRCVER}.tar.gz \
   file://fix-configure-wayland-protocols-path.patch \
"

SRC_URI[md5sum] = "9e66987ad9a44eb9117341a3efa9ee0b"
SRC_URI[sha256sum] = "15181fc29ed9b856b5abf3a6b4a0a0a431e29d64382259e2da699acd643488ca"

# Temporary disable until error like the one following are fixed
# efl-native/2_1.8.4-r0/efl-1.8.4/src/lib/eet/.libs/libeet.so: file not recognized: File truncated
# collect2: error: ld returned 1 exit status
# x86_64-linux-libtool: install: error: relink `modules/evas/savers/tiff/module.la' with the above command before installing it
# Makefile:11031: recipe for target 'install-savertiffpkgLTLIBRARIES' failed
PARALLEL_MAKE_class-native = ""

B = "${S}"

