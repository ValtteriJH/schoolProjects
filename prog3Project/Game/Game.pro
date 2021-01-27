TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    Actors/teekkari.cpp \
    Core/creategame.cpp \
    Core/maincity.cpp \
    Core/initialization.cpp\
    Graphics/UFOGraphics.cpp \
    Graphics/mainwindow.cpp \
    Graphics/nyssegraphics.cpp \
    Graphics/stopgraphics.cpp \
    Graphics/dialog.cpp \
    Graphics/endingdialog.cpp \
    Graphics/loredialog.cpp \
    main.cc \
    Graphics/passengergraphics.cpp \
    Core/tilasto.cpp

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib \
    $$PWD/../Game/

DEPENDPATH += \
    $$PWD/../Course/CourseLib
    $$PWD/../Game/

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

HEADERS += \
    Actors/teekkari.h \
    Core/initialization.h\
    Core/creategame.hh \
    Core/maincity.hh \
    Graphics/UFOGraphics.h \
    Graphics/mainwindow.hh \
    Graphics/nyssegraphics.hh \
    Graphics/stopgraphics.hh \
    Graphics/passengergraphics.hh \
    Graphics/dialog.hh \
    Graphics/endingdialog.hh \
    Graphics/loredialog.hh \
    Core/tilasto.hh

DISTFILES

RESOURCES += \
    Resources/Resources.qrc

FORMS += \
    mainwindow.ui \
    dialog.ui \
    endingdialog.ui \
    loredialog.ui
