

#import <Cocoa/Cocoa.h>
#import <AudioUnit/AUCocoaUIView.h>

@class AudioUnitSynthView_UIView;

@interface AudioUnitSynthView_ViewFactory : NSObject <AUCocoaUIBase>
{
    IBOutlet AudioUnitSynthView_UIView *uiFreshlyLoadedView;
}
- (NSString *) description;

@end