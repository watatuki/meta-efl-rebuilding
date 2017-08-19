SUMMARY = "The software for Enlightenment"
DESCRIPTION = "A set of packages belong to Enlightenment"

LICENSE = "MIT"

inherit packagegroup

PACKAGES = "\
    packagegroup-enlightenment \
    "

ALLOW_EMPTY_${PN} = "1"

RDEPENDS_${PN} += "\
    "

RDEPENDS_${PN} += " enlightenment enlightenment-session \
                    enlightenment-config-default \
                    enlightenment-config-mobile \
                    enlightenment-config-standard \
                    enlightenment-config-tiling \
                    enlightenment-backgrounds \
                    elementary elementary-configs elementary-themes \
                  "
