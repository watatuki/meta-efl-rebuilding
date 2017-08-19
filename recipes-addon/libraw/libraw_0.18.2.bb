SUMMARY = "Library for reading and processing of RAW digicam images"
SECTION = "libs"
LICENSE = "LGPL-2.1"
LIC_FILES_CHKSUM = "file://LICENSE.LGPL;md5=68ad62c64cc6c620126241fd429e68fe"

SRC_URI = "git://github.com/LibRaw/LibRaw.git;branch=0.18-stable"
SRCREV = "4d2aec21dc76bdf04e66b9dfce0a8442bb3fb375"

DEPENDS = " lcms "

S = "${WORKDIR}/git"

inherit autotools pkgconfig

EXTRA_OECONF = " \
                --enable-lcms \
                --disable-demosaic-pack-gpl2 \
                --disable-demosaic-pack-gpl3 \
                --disable-examples \
               "

