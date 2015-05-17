
#import "AudioUnitSynthView_ViewFactory.h"
#import "AudioUnitSynthView_UIView.h"

@implementation AudioUnitSynthView_ViewFactory

- (unsigned) interfaceVersion {
	return 0;
}

- (NSString *) description {
	return @"AudioUnit Synth";
}

- (NSView *)uiViewForAudioUnit:(AudioUnit)inAU withSize:(NSSize)inPreferredSize {

    if (![[NSBundle bundleForClass:[self class]] loadNibNamed:@"AudioUnitSynthView" owner:self topLevelObjects:nil]) {
        NSLog (@"Unable to load nib for view.");
		return nil;
	}
    
    [uiFreshlyLoadedView setAU:inAU];
    
    NSView *returnView = uiFreshlyLoadedView;
    uiFreshlyLoadedView = nil;
    
    return returnView;
}

@end
