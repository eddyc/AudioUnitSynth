#import <Cocoa/Cocoa.h>
#import <AudioUnit/AudioUnit.h>
#import <AudioToolbox/AudioToolbox.h>

@interface AudioUnitSynthView_UIView : NSView
{	
    AudioUnit mAU;
}

- (void)setAU:(AudioUnit)inAU;

@end
