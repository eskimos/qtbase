/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWINDOW_QPA_P_H
#define QWINDOW_QPA_P_H

#include <QtGui/qwindow.h>

#include <QtCore/private/qobject_p.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

#define QWINDOWSIZE_MAX ((1<<24)-1)

class Q_GUI_EXPORT QWindowPrivate : public QObjectPrivate
{
public:
    QWindowPrivate()
        : QObjectPrivate()
        , windowFlags(Qt::Window)
        , surfaceType(QWindow::RasterSurface)
        , parentWindow(0)
        , platformWindow(0)
        , visible(false)
        , glContext(0)
        , surface(0)
        , windowState(Qt::WindowNoState)
        , maximumSize(QWINDOWSIZE_MAX, QWINDOWSIZE_MAX)
    {
        isWindow = true;
    }

    ~QWindowPrivate()
    {
    }

    Qt::WindowFlags windowFlags;
    QWindow::SurfaceType surfaceType;
    QWindow *parentWindow;
    QPlatformWindow *platformWindow;
    bool visible;
    QWindowFormat requestedFormat;
    QString windowTitle;
    QRect geometry;
    QWindowContext *glContext;
    QWindowSurface *surface;
    Qt::WindowState windowState;

    QSize minimumSize;
    QSize maximumSize;
    QSize baseSize;
    QSize sizeIncrement;
};


QT_END_NAMESPACE

QT_END_HEADER

#endif // QWINDOW_QPA_P_H
