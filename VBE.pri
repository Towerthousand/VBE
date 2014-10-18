INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

LIBS += -lVBE

# This is needed so the game is recompiled every time
# we change something in VBE
PRE_TARGETDEPS += ../VBE/libVBE.a

win32 {
        CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../VBE/release/
        CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../VBE/debug/

        CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../VBE/release/VBE.lib
        CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../VBE/debug/VBE.lib
}

unix {
        LIBS += -L$$OUT_PWD/../VBE/
        PRE_TARGETDEPS += $$OUT_PWD/../VBE/libVBE.a
}
