HEADERS     = delegate.h
SOURCES     = delegate.cpp \
              main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/spinboxdelegate
INSTALLS += target

QT += widgets

simulator: warning(This example might not fully work on Simulator platform)
