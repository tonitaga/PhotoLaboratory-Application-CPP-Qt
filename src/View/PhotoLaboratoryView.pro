QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Model/FilterHelper/Filters/ColorCorrectionFilters/colorcorrectionfilters.cc \
    ../Model/FilterHelper/Filters/ConvolutionFilters/convolutionfilters.cc \
    ../Model/FilterHelper/Filters/NonConvolutionFilters/nonconvolutionfilters.cc \
    ../Model/FilterHelper/basefilter.cc \
    customkernelview.cc \
    ../main.cc \
    view.cc \
    view_help.cc

HEADERS += \
    ../Controller/filtercontroller.h \
    ../Model/FilterHelper/FilterManagers/colorcorrectionfiltermanager.h \
    ../Model/FilterHelper/FilterManagers/convolutionfiltermanager.h \
    ../Model/FilterHelper/FilterManagers/nonconvolutionfiltermanager.h \
    ../Model/FilterHelper/basefilter.h \
    ../Model/FilterHelper/Filters/ColorCorrectionFilters/colorcorrectionfilters.h \
    ../Model/FilterHelper/Filters/ConvolutionFilters/convolutionfilters.h \
    ../Model/FilterHelper/Filters/NonConvolutionFilters/nonconvolutionfilters.h \
    ../Model/FilterHelper/filtertypetraits.h \
    ../Model/FilterHelper/filterhelper.h \
    ../Model/FilterModel/filtermodel.h \
    customkernelview.h \
    view.h

FORMS += \
    customkernelview.ui \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
