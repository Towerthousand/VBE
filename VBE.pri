INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

LIBS += -lVBE

# This is needed so the game is recompiled every time
# we change something in VBE

win32 {
		CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../VBE/release/
		CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../VBE/debug/

		CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../VBE/release/libVBE.a
		CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../VBE/debug/libVBE.a
}


unix {
        LIBS += -L$$OUT_PWD/../VBE/
        PRE_TARGETDEPS += $$OUT_PWD/../VBE/libVBE.a
}
