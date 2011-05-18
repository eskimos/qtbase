/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
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

#ifndef QNSWINDOWDELEGATE_H
#define QNSWINDOWDELEGATE_H

#include <Cocoa/Cocoa.h>

#include "qcocoawindow.h"

#if MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_5
@protocol NSWindowDelegate <NSObject>
//- (NSSize)windowWillResize:(NSWindow *)window toSize:(NSSize)proposedFrameSize;
//- (void)windowDidMiniaturize:(NSNotification*)notification;
- (void)windowDidResize:(NSNotification *)notification;
- (void)windowWillClose:(NSNotification *)notification;
//- (NSRect)windowWillUseStandardFrame:(NSWindow *)window defaultFrame:(NSRect)defaultFrame;
//- (void)windowDidMove:(NSNotification *)notification;
//- (BOOL)windowShouldClose:(id)window;
//- (void)windowDidDeminiaturize:(NSNotification *)notification;
//- (void)windowDidBecomeMain:(NSNotification*)notification;
//- (void)windowDidResignMain:(NSNotification*)notification;
//- (void)windowDidBecomeKey:(NSNotification*)notification;
//- (void)windowDidResignKey:(NSNotification*)notification;
//- (BOOL)window:(NSWindow *)window shouldPopUpDocumentPathMenu:(NSMenu *)menu;
//- (BOOL)window:(NSWindow *)window shouldDragDocumentWithEvent:(NSEvent *)event from:(NSPoint)dragImageLocation withPasteboard:(NSPasteboard *)pasteboard;
//- (BOOL)windowShouldZoom:(NSWindow *)window toFrame:(NSRect)newFrame;
@end
#endif

@interface QNSWindowDelegate : NSObject <NSWindowDelegate>
{
    QCocoaWindow *m_cocoaWindow;
}

- (id)initWithQCocoaWindow: (QCocoaWindow *) cocoaWindow;

- (void)windowDidResize:(NSNotification *)notification;
- (void)windowWillClose:(NSNotification *)notification;

@end

#endif // QNSWINDOWDELEGATE_H
