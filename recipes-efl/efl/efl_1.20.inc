SUMMARY = "EFL"
LICENSE = "MIT & BSD & LGPL-2.1"
LIC_FILES_CHKSUM = "file://COPYING;md5=e5f6e713fdebf1237adf5c87de8255d8"

DEPENDS_class-native = "freetype-native libxext-native libpng-native jpeg-native tiff-native libfribidi-native glib-2.0-native dbus-native openssl-native"
DEPENDS = "virtual/libiconv curl glib-2.0 gnutls pkgconfig zlib jpeg openssl libsndfile1 dbus libexif librsvg freetype libpng tiff libxext \
           virtual/libx11 libxdamage libxrender fontconfig libfribidi giflib udev libxcursor libxcomposite libxinerama libxrandr libxtst \
           libxscrnsaver efl-native util-linux libunwind wayland wayland-protocols wayland-native libxkbcommon libinput libraw \
           poppler "

inherit efl gettext pkgconfig

BBCLASSEXTEND = "native"

PROVIDES += "ecore edje eet eeze efreet eina eio embryo emotion ethumb evas eldbus elementary "

EXTRA_OECONF = " \
    --disable-physics \
    --disable-spectre \
    --enable-i-really-know-what-i-am-doing-and-that-this-will-probably-break-things-and-i-will-fix-them-myself-and-send-patches-abb \
    WAYLAND_PROTOCOLS_SYSROOT_DIR=${RECIPE_SYSROOT} \
"

EXTRA_OECONF_append_class-target = " \
    --with-tests=none \
    --disable-always-build-examples \
    --with-x11=xlib \
    \
    --with-edje-cc=${STAGING_BINDIR_NATIVE}/edje_cc \
    --with-eolian-gen=${STAGING_BINDIR_NATIVE}/eolian_gen \
    --with-eolian-cxx=${STAGING_BINDIR_NATIVE}/eolian_cxx \
    --with-elua=${STAGING_BINDIR_NATIVE}/elua \
    --with-eet-eet=${STAGING_BINDIR_NATIVE}/eet \
    --with-eldbus_codegen=${STAGING_BINDIR_NATIVE}/eldbus-codegen \
    --with-elementary-codegen=${STAGING_BINDIR_NATIVE}/elementary_codegen \
    --with-elm-prefs-cc=${STAGING_BINDIR_NATIVE}/elm_prefs_cc \
"

EXTRA_OECONF_append_class-native = " \
    --disable-fontconfig \
    --disable-audio \
    --disable-physics \
    --disable-multisense \
    --disable-cserve \
    --disable-libeeze \
    --disable-poppler \
    --disable-librsvg \
    --disable-libraw  \
    --with-x11=none \
    --disable-image-loader-bmp \
    --disable-image-loader-eet \
    --disable-image-loader-generic \
    --disable-image-loader-gif \
    --disable-image-loader-ico \
    --disable-image-loader-jp2k \
    --disable-image-loader-pmaps \
    --disable-image-loader-psd \
    --disable-image-loader-tga \
    --disable-image-loader-wbmp \
    --disable-image-loader-webp \
    --disable-image-loader-xpm \
    --disable-image-loader-tgv \
    --disable-image-loader-dds \
"

PACKAGECONFIG ?= "egl opengl-es gstreamer1 pulseaudio luajit wayland "
PACKAGECONFIG_class-native = "luajit"

PACKAGECONFIG[wayland] = "--enable-wayland --enable-wayland-ivi-shell,--disable-wayland --disable-wayland-ivi-shell,wayland"
PACKAGECONFIG[egl] = "--enable-egl,--disable-egl,virtual/egl"
# sort of tri-state
PACKAGECONFIG[opengl-full] = "--with-opengl=full,,virtual/libgl"
PACKAGECONFIG[opengl-es] = "--with-opengl=es,,virtual/libgles2"
PACKAGECONFIG[opengl-none] = "--with-opengl=none,,"
# be aware when enabling this for efl-native, we don't provide gcc-native so you need to make
# sure that all your builders have g++ which supports -std=gnu++11
PACKAGECONFIG[c++11] = "--enable-cxx-bindings,--disable-cxx-bindings"
PACKAGECONFIG[gstreamer] = "--enable-gstreamer,--disable-gstreamer,gstreamer"
PACKAGECONFIG[gstreamer1] = "--enable-gstreamer1,--disable-gstreamer1,gstreamer1.0 gstreamer1.0-plugins-base"
PACKAGECONFIG[pulseaudio] = "--enable-pulseaudio,--disable-pulseaudio,pulseaudio"
PACKAGECONFIG[systemd] = "--enable-systemd,--disable-systemd,systemd"
PACKAGECONFIG[luajit] = "--disable-lua-old,--enable-lua-old,luajit"
PACKAGECONFIG[lua-old] = "--enable-lua-old,--disable-lua-old,lua"
PACKAGECONFIG[avahi] = "--enable-avahi,--disable-avahi,avahi"
# currently we don't provide doxygen-native
PACKAGECONFIG[doc] = "--enable-doc,--disable-doc,doxygen-native"

do_install_append() {
    # don't ship precompiled lua files
    rm -f ${datadir}/elua/*/*.luac
}

PACKAGES =+ "edje-utils embryo-utils embryo-tests efreet-trash efreet-mime libeet libefreet \
             ecore-audio ecore-input-evas ecore-input ecore-imf-evas ecore-imf ecore-file ecore-con ecore-ipc ecore-x ecore-evas \
             libemotion eo ecore edje eet eeze efreet eina eio embryo emotion ethumb evas eldbus elua \
             elementary elementary-themes elementary-configs elementary-tests elementary-accessibility \
             evas-image-loader evas-generic-pdf-loader "

# upgrade path from 1.7
DEBIAN_NOAUTONAME_ecore-audio = "1"
DEBIAN_NOAUTONAME_ecore-input-evas = "1"
DEBIAN_NOAUTONAME_ecore-input = "1"
DEBIAN_NOAUTONAME_ecore-imf-evas = "1"
DEBIAN_NOAUTONAME_ecore-imf = "1"
DEBIAN_NOAUTONAME_ecore-file = "1"
DEBIAN_NOAUTONAME_ecore-con = "1"
DEBIAN_NOAUTONAME_ecore-ipc = "1"
DEBIAN_NOAUTONAME_ecore-x = "1"
DEBIAN_NOAUTONAME_ecore-evas = "1"
DEBIAN_NOAUTONAME_embryo = "1"

ALLOW_EMPTY_ecore = "1"
RDEPENDS_ecore = "ecore-audio ecore-input-evas ecore-input ecore-imf-evas ecore-imf ecore-file ecore-con ecore-ipc ecore-x ecore-evas"

python populate_packages_prepend () {
    for plugin_type in "engines loaders savers".split():
        bb.note( "splitting packages for evas %s..." % plugin_type )
        basedir = d.expand( '${libdir}/evas/modules/%s' % plugin_type)

        do_split_packages(d, basedir, '^(.*)',
        output_pattern = 'evas-' + plugin_type[:-1] + "-%s",
        description = 'Evas module %s',
        allow_dirs=True, recursive=False, extra_depends="" )

        plugin_type = "cserve2"
        bb.note( "splitting packages for evas %s..." % plugin_type )
        basedir = d.expand( '${libdir}/evas/%s/loaders' % plugin_type)

        do_split_packages(d, basedir, '^(.*)',
        output_pattern = 'evas-' + plugin_type + "-%s",
        description = 'Evas csever2 loader module %s',
        allow_dirs=True, recursive=False, extra_depends="" )
}

PACKAGES += "evas-loader-png evas-engine-software-generic evas-engine-fb"
PACKAGES_DYNAMIC += "^evas-engine-.* ^evas-loader-.* ^evas-saver-.* ^evas-cserve2-.*"

# PACKAGES_DYNAMIC + do_split_packages isn't used for all libe libs,
# because PACKAGES_DYNAMIC would be catching too many patterns
# (or need to list all possible prefixes) and not all original packages
# were splitted like that, so it would need RCONFLICTS/RPROVIDES/RREPLACES
# combos at least in few places for upgrade path.

FILES_efreet-trash = " \
    ${libdir}/libefreet_trash${SOLIBS} \
"
FILES_efreet-mime = " \
    ${libdir}/libefreet_mime${SOLIBS} \
"
FILES_libeet = " \
    ${libdir}/libeet${SOLIBS} \
"
FILES_libefreet = " \
    ${libdir}/libefreet${SOLIBS} \
"
FILES_ecore-audio = "\
    ${libdir}/libecore_audio${SOLIBS} \
"
FILES_ecore-input-evas = "\
    ${libdir}/libecore_input_evas${SOLIBS} \
"
FILES_ecore-input = "\
    ${libdir}/libecore_input${SOLIBS} \
"
FILES_ecore-imf-evas = "\
    ${libdir}/libecore_imf_evas${SOLIBS} \
    ${libdir}/ecore-imf/modules/*/*/module.so \
"
FILES_ecore-imf = "\
    ${libdir}/libecore_imf${SOLIBS} \
"

FILES_ecore-file = "\
    ${libdir}/libecore_file${SOLIBS} \
"
FILES_ecore-con = "\
    ${libdir}/libecore_con${SOLIBS} \
    ${libdir}/ecore_con/*/*/* \
"
FILES_ecore-ipc = "\
    ${libdir}/libecore_ipc${SOLIBS} \
"
FILES_ecore-x = "\
    ${libdir}/libecore_x${SOLIBS} \
    ${libdir}/ecore_x/bin/v-*/ecore_x_vsync \
"
FILES_ecore-evas = "\
    ${libdir}/libecore_evas${SOLIBS} \
    ${libdir}/ecore-evas/engines/*/*/module.so \
"
FILES_eio = "\
    ${libdir}/libeio${SOLIBS} \
"
FILES_eina = "\
    ${libdir}/libeina${SOLIBS} \
    ${bindir}/eina-bench-cmp \
    ${bindir}/eina_modinfo \
"
FILES_edje-utils = "\
    ${bindir}/edje_* \
    ${datadir}/edje/include/edje.inc \
"
FILES_eldbus = "\
    ${libdir}/libeldbus${SOLIBS} \
"
FILES_eo = "\
    ${libdir}/libeo${SOLIBS} \
"
FILES_libemotion = "\
    ${libdir}/libemotion${SOLIBS} \
"
FILES_efreet = " \
    ${datadir}/dbus-1/services/*Efreet* \
    ${libdir}/efreet/*/efreet*create \
    ${bindir}/efreetd \
    ${datadir}/efreet \
"
FILES_eet = " \
    ${bindir}/eet \
    ${bindir}/eetpack \
    ${bindir}/vieet \
    ${bindir}/diffeet \
    ${libdir}/libeet${SOLIBS} \
"
FILES_emotion = " \
    ${datadir}/emotion \
    ${libdir}/emotion/modules/gstreamer1/*/module.so \
"
FILES_embryo-tests = " \
    ${datadir}/embryo/ \
"
FILES_embryo-utils = " \
    ${binddir}/embryo_* \
"
FILES_embryo = " \
    ${libdir}/libembryo${SOLIBS} \
"
FILES_ethumb = " \
    ${datadir}/dbus-1/services/*Ethumb* \
    ${libdir}/libethumb${SOLIBS} \
    ${libdir}/libethumb_client${SOLIBS} \
    ${bindir}/ethumbd \
    ${bindir}/ethumbd_client \
    ${bindir}/ethumb \
    ${libdir}/ethumb/*/*/*/module.so \
    ${libdir}/ethumb/*/*/*/*.edj \
    ${libdir}/ethumb_client/utils/*/ethumbd_slave \
    ${datadir}/ethumb* \
"
FILES_ecore = " \
    ${libdir}/libecore${SOLIBS} \
    ${libdir}/ecore*/*/*/*/module.so \
    ${datadir}/ecore* \
"

RDEPENDS_evas = "\
    evas-image-loader \
    evas-generic-pdf-loader \
"

FILES_evas = " \
    ${libdir}/libevas${SOLIBS} \
    ${libdir}/evas*/*/*/*/*/module.so \
    ${libdir}/evas*/*/*/*/*/*.edj \
    ${libdir}/evas/cserve2/bin/*/evas_cserve2* \
    ${datadir}/evas* \
    ${bindir}/evas_cserve2_* \
"

FILES_evas-image-loader = " \
    ${libdir}/evas/utils/evas_image_loader*.* \
"

FILES_evas-generic-pdf-loader = " \
    ${libdir}/evas/utils/evas_generic_pdf_loader*.* \
"

FILES_eeze = " \
    ${libdir}/libeeze${SOLIBS} \
    ${libdir}/eeze*/*/*/*/*/module.so \
    ${datadir}/eeze \
    ${bindir}/eeze_* \
"
FILES_edje = " \
    ${libdir}/libedje${SOLIBS} \
    ${libdir}/edje*/*/*/*/module.so \
    ${libdir}/edje/utils/*/epp \
    ${datadir}/edje \
    ${datadir}/mime \
"
FILES_elua = " \
    ${bindir}/elua \
    ${datadir}/elua \
"

RDEPENDS_elementary = "\
    elementary-themes \
    elementary-configs \
"

FILES_elementary = "\
    ${libdir}/edje/modules/elm \
    ${libdir}/elementary/modules/*/*/module.so \
    ${libdir}/elementary/modules/*/*/*/module.so \
    ${libdir}/elementary/modules/*/*/*.edj \
"

FILES_elementary-themes = "\
    ${datadir}/elementary/themes \
"

FILES_elementary-configs = "\
    ${datadir}/elementary/config \
"

FILES_${PN}-tests = "\
    ${bindir}/elementary* \
    ${bindir}/efl_wl_test** \
    ${datadir}/elementary/images \
    ${datadir}/elementary/objects \
    ${datadir}/elementary/examples \
    ${datadir}/elementary/edje_externals \
    ${datadir}/elementary/test* \
    ${datadir}/applications/* \
    ${datadir}/icons/* \
    ${libdir}/elementary/modules/test_entry/* \
    ${libdir}/elementary/modules/test_map/* \
"

FILES_${PN}-accessibility = "\
    ${libdir}/elementary/modules/access_output/* \
"

FILES_${PN}-dbg += " \
    ${libdir}/efreet/*/.debug \
    ${libdir}/ecore*/*/*/*/.debug \
    ${libdir}/ecore*/*/*/.debug \
    ${libdir}/evas*/*/*/*/*/.debug \
    ${libdir}/evas/cserve2/bin/*/.debug \
    ${libdir}/eeze*/*/*/*/*/.debug \
    ${libdir}/edje*/*/*/*/.debug \
    ${libdir}/edje/utils/*/.debug \
    ${libdir}/ethumb/*/*/*/.debug \
    ${libdir}/ethumb_client/utils/*/.debug \
    ${libdir}/emotion/modules/gstreamer1/*/.debug \
"
FILES_${PN}-dev += " \
    ${libdir}/cmake \
    ${libdir}/ecore*/*/*/*/module.la \
    ${libdir}/evas*/*/*/*/*/module.la \
    ${libdir}/ethumb*/*/*/*/module.la \
    ${libdir}/eeze*/*/*/*/*/module.la \
    ${libdir}/edje*/*/*/*/module.la \
    ${libdir}/elementary*/*/*/*/module.la \
    ${libdir}/elementary*/*/*/*/*/module.la \
    ${libdir}/emotion/modules/gstreamer1/*/module.la \
    ${datadir}/gdb/auto-load \
    ${datadir}/eo/gdb \
    ${bindir}/eldbus-codegen \
    ${bindir}/eina_btlog \
    ${bindir}/eolian_gen \
    ${bindir}/embryo_cc \
    ${bindir}/elm_prefs_cc \
    ${bindir}/efl_debugd \
    ${bindir}/efl_debug \
    ${bindir}/ecore_evas_convert \
    ${bindir}/eo_debug \
"
