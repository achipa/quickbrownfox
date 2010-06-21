#-------------------------------------------------
#
# Project created by QtCreator 2010-01-09T02:48:23
#
#-------------------------------------------------


TARGET = quickbrownfox
TEMPLATE = app
#CONFIG += release

CONFIG += qdbus
#QT += dbus maemo5 xml
SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

maemo5 {
    message("Maemo5 build")
#    QT+= maemo5
}

unix {
    # VARIABLES
    isEmpty(PREFIX):PREFIX = /usr #/local ?
    BINDIR = $$PREFIX/bin
    DATADIR = $$PREFIX/share
    DEFINES += DATADIR=\"$$DATADIR\" \
        PKGDATADIR=\"$$PKGDATADIR\"

    contains(QT_CONFIG, hildon):{
          DEFINES += CHIMGDIR=\'\"$$DATADIR/$${TARGET}\"\'
    }
    # MAKE INSTALL
    INSTALLS += target \
        imagery \
        desktop \
        iconxpm \
        icon26 \
        icon40 \
        icon64
    target.path = $$BINDIR
    imagery.path = $$DATADIR/$${TARGET}/images
    imagery.files += ../src/images/*png
    desktop.path = $$DATADIR/applications/hildon
    desktop.files += $${TARGET}.desktop
    iconxpm.path = $$DATADIR/pixmap
    iconxpm.files += ../data/maemo/$${TARGET}.xpm
    icon26.path = $$DATADIR/icons/hicolor/26x26/apps
    icon26.files += ../data/26x26/$${TARGET}.png
    icon40.path = $$DATADIR/icons/hicolor/40x40/apps
    icon40.files += ../data/40x40/$${TARGET}.png
    icon64.path = $$DATADIR/icons/hicolor/64x64/apps
    icon64.files += ../data/64x64/$${TARGET}.png
}
