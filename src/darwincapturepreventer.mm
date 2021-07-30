#include "darwincapturepreventer.h"
#import <Appkit/NSWindow.h>

#if defined(INCLUDE_PRIVATE_API) && INCLUDE_PRIVATE_API

#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>

//define the private CGS methods we need to exclude a window from being captured.
// ------ PRIVATE API ------
typedef int CGSConnectionID;
typedef int CGSWindowID;
typedef CFTypeRef CGSRegionRef;

CG_EXTERN CGSConnectionID CGSMainConnectionID(void);

CG_EXTERN CGError CGSGetWindowBounds(CGSConnectionID cid, CGSWindowID wid, CGRect *rectOut);

CG_EXTERN CGError CGSNewRegionWithRect(const CGRect *rect, CGSRegionRef *regionOut);
CG_EXTERN BOOL CGSRegionIsEmpty(CGSRegionRef region);
CG_EXTERN CGError CGSReleaseRegion(CGSRegionRef region);

CG_EXTERN CGError CGSSetWindowCaptureExcludeShape(CGSConnectionID cid, CGSWindowID wid, CGSRegionRef region);
// ------ END PRIVATE API ------


//implementation

BOOL preventWindowCaptureForWindow(NSWindow *window)
{
#ifndef DEV_VERSION
    CGSConnectionID cid = CGSMainConnectionID();
    CGSWindowID wid = (int)window.windowNumber;

    CGRect windowRectOut;

    CGError err = CGSGetWindowBounds(cid, wid, &windowRectOut);
    if(err != kCGErrorSuccess)
    {
#ifdef EXTENSIVE_LOGGING
        NSLog(@"Error: failed to get windows bounds with error %i", err);
#endif
        return NO;
    }
    windowRectOut.origin = CGPointZero;

    CGSRegionRef regionOut;
    err = CGSNewRegionWithRect(&windowRectOut, &regionOut);
    if(err != kCGErrorSuccess)
    {
#ifdef EXTENSIVE_LOGGING
        NSLog(@"Error: failed to get create CGSRegion with error %i", err);
#endif
        return NO;
    }

    err = CGSSetWindowCaptureExcludeShape(cid, wid, regionOut);
    if(err != kCGErrorSuccess)
    {
#ifdef EXTENSIVE_LOGGING
        NSLog(@"Error: failed to set capture exclude shape for window with error %i", err);
#endif
        CGSReleaseRegion(regionOut);
        return NO;
    }
    //qDebug() << windowRectOut.size.height;
    //qDebug() << windowRectOut.size.width;
    CGSReleaseRegion(regionOut);
#endif
    return YES;
}
DarwinCapturePreventer::DarwinCapturePreventer(QGuiApplication &_app, QObject *parent) : QObject(parent),
    app(_app)
{
    NSWindow * window	= reinterpret_cast<NSView *>(app.allWindows().at(0)->winId()).window;
    window.sharingType = NSWindowSharingType::NSWindowSharingNone;
    preventWindowCaptureForWindow(window);

}

void DarwinCapturePreventer::update()
{
    NSWindow * window	= reinterpret_cast<NSView *>(app.allWindows().at(0)->winId()).window;
    window.sharingType = NSWindowSharingType::NSWindowSharingNone;
    preventWindowCaptureForWindow(window);
}
#endif
