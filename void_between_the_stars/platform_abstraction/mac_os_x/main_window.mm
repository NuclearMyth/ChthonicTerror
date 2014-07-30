//
//  main_window.mm
//
//  MainWindow - The Mac OS X abstraction layer of the Void Between The Stars.
//
//  Written in 2014 by Vii 123qwe@gmail.com
//
//  To the extent possible under law, the author(s) have dedicated all copyright
//  and related and neighboring rights to this software to the public domain
//  worldwide. This software is distributed without any warranty.
//
//  You should have received a copy of the CC0 Public Domain Dedication along
//  with this software.
//
//  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//

#import <Cocoa/Cocoa.h>

#include "../input.h"
#include <OpenGL/gl.h>
#include <vector>

@interface MainWindow : NSWindow
{}
@end

@implementation MainWindow
  - (id) initWithContentRect: (NSRect)rect styleMask: (NSUInteger)wndStyle
      backing: (NSBackingStoreType)bufferingType defer: (BOOL)deferFlg {
    self = [super initWithContentRect: rect styleMask: wndStyle
      backing: bufferingType defer: deferFlg];
    [self setAcceptsMouseMovedEvents: YES];
    [[NSNotificationCenter defaultCenter] addObserver: self
      selector: @selector(windowWillClose:) name: NSWindowWillCloseNotification
      object: self];
    return self;
  }

  - (void) windowWillClose: (NSNotification *)notification {
    [NSApp terminate: nil];
  }
@end


@interface MainView : NSOpenGLView
{}
@end

@implementation MainView
static MainWindow *main_window_ = nil;
static MainView *main_view_ = nil;
static std::vector<Input> main_input_;
static NSUInteger prev_flags_ = 0;

void CreateMainWindow()
{
  ProcessSerialNumber psn = { 0, kCurrentProcess };
  TransformProcessType(&psn, kProcessTransformToForegroundApplication);
  
  [NSApplication sharedApplication];

  main_window_ = [[MainWindow alloc]
    initWithContentRect: [[NSScreen mainScreen] frame]
    styleMask: NSTitledWindowMask | NSClosableWindowMask |
               NSMiniaturizableWindowMask | NSResizableWindowMask
    backing: NSBackingStoreBuffered defer: NO];

  NSOpenGLPixelFormatAttribute attributes[] = { NSOpenGLPFAWindow,
    NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)32,
    NSOpenGLPFADoubleBuffer, 0
  };
  
  main_view_ = [[MainView alloc]
    initWithFrame: [[NSScreen mainScreen] frame]
    pixelFormat: [[NSOpenGLPixelFormat alloc] initWithAttributes: attributes]];
  
  [main_window_ setAcceptsMouseMovedEvents:YES];
  [main_window_ setContentView: main_view_];
  [main_window_ makeKeyAndOrderFront: main_view_];
  [main_window_ makeMainWindow];
  
  NSMenu* bar = [[NSMenu alloc] init];
  [NSApp setMainMenu:bar];
  NSMenuItem* app_menu_item = [bar addItemWithTitle:@"" action:NULL
    keyEquivalent:@""];
  NSMenu* app_menu = [[NSMenu alloc] init];
  [app_menu_item setSubmenu:app_menu];
  [app_menu addItemWithTitle:@"Quit" action:@selector(windowWillClose:)
    keyEquivalent:@"q"];

  [NSApp finishLaunching];
}

@end

void GetMainWindowDimensions(int *out_width, int *out_height)
{
  *out_width = main_view_.frame.size.width;
  *out_height = main_view_.frame.size.height;
}

void GetInput(std::vector<Input> *out_input)
{
  out_input->clear();
  
  while (true) {
    NSEvent *event = [NSApp nextEventMatchingMask: NSAnyEventMask
      untilDate: [NSDate distantPast] inMode: NSDefaultRunLoopMode
      dequeue: YES];
    if (event == nil) {
      return;
    }
    switch (event.type) {
      case NSOtherMouseDragged:
      case NSRightMouseDragged:
      case NSLeftMouseDragged:
      case NSMouseMoved:
      {
        Input mouse(Input::kMouseMove, Input::kNone,
                    [event locationInWindow].x,
                    [event locationInWindow].y);
        out_input->push_back(mouse);
        break;
      }
      case NSFlagsChanged:
      {
        NSUInteger flags = [event modifierFlags];
        if (NSShiftKeyMask & flags & ~prev_flags_) {
          Input key(Input::kKeyDown, Input::kShift, 0, 0);
          out_input->push_back(key);
        }
        if (NSControlKeyMask & flags & ~prev_flags_) {
          Input key(Input::kKeyDown, Input::kControl, 0, 0);
          out_input->push_back(key);
        }
        if (NSAlternateKeyMask & flags & ~prev_flags_) {
          Input key(Input::kKeyDown, Input::kAlt, 0, 0);
          out_input->push_back(key);
        }
        
        if (NSShiftKeyMask & ~flags & prev_flags_) {
          Input key(Input::kKeyUp, Input::kShift, 0, 0);
          out_input->push_back(key);
        }
        if (NSControlKeyMask & ~flags & prev_flags_) {
          Input key(Input::kKeyUp, Input::kControl, 0, 0);
          out_input->push_back(key);
        }
        if (NSAlternateKeyMask & ~flags & prev_flags_) {
          Input key(Input::kKeyUp, Input::kAlt, 0, 0);
          out_input->push_back(key);
        }
        
        prev_flags_ = flags;
        break;
      }
      case NSKeyDown:
      case NSKeyUp:
      {
        if ([event isARepeat]) {
          break;
        }
        Input key((event.type == NSKeyDown ? Input::kKeyDown : Input::kKeyUp),
                  Input::kNone, 0, 0);
        NSString *characters;
        
        bool is_ok = true;
        printf("keyCode = %d\n", (int)event.keyCode);
        switch (event.keyCode) {
          case 53:
            key.key = Input::kEsc;
            break;
          case 51:
            key.key = Input::kBackspace;
            break;
          case 36:
            key.key = Input::kReturn;
            break;
          default:
          {
            characters = [event characters];
            key.key = [characters characterAtIndex:0];
            switch (key.key) {
              case NSUpArrowFunctionKey:
                key.key = Input::kUpArrow;
                break;
              case NSDownArrowFunctionKey:
                key.key = Input::kDownArrow;
                break;
              case NSLeftArrowFunctionKey:
                key.key = Input::kLeftArrow;
                break;
              case NSRightArrowFunctionKey:
                key.key = Input::kRightArrow;
                break;
              default:
                if ([characters length] == 0) {
                  is_ok = false;
                }
                break;
            }
            break;
          }
        }
        if (is_ok) {
          out_input->push_back(key);
        }
        break;
      }
      case NSLeftMouseDown:
      {
        Input key(Input::kKeyDown, Input::kLeftMouse, 0, 0);
        out_input->push_back(key);
        break;
      }
      case NSOtherMouseDown:
      {
        Input key(Input::kKeyDown, Input::kMiddleMouse, 0, 0);
        out_input->push_back(key);
        break;
      }
      case NSRightMouseDown:
      {
        Input key(Input::kKeyDown, Input::kRightMouse, 0, 0);
        out_input->push_back(key);
        break;
      }
      default:
        break;
    } // switch (event.type)
    [NSApp sendEvent:event];
    [NSApp updateWindows];
  } // while (true)
}

void GlSwap() {
  glSwapAPPLE();
}
// SwapBuffers(hdc);  //For Windows