DESCRIPTION = "A program to control LEDs based on button presses"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://led_control.cpp"

S = "${WORKDIR}"

do_compile() {
    ${CXX} ${CXXFLAGS} ${LDFLAGS} -o led_control led_control.cpp
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 led_control ${D}${bindir}/
}

FILES_${PN} += "${bindir}/led_control"

