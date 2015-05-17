

#include "AUInstrumentBase.h"

#define kCsoundAudioUnitVersion 0x00010000

class AudioUnitSynth : public AUInstrumentBase
{
public:
    AudioUnitSynth(AudioUnit inComponentInstance);
    virtual ~AudioUnitSynth();
    
    virtual OSStatus Initialize();
    virtual void Cleanup();
    
    virtual OSStatus Version() {
        return kCsoundAudioUnitVersion;
    }
    
    virtual OSStatus GetProperty(AudioUnitPropertyID inID,
                                 AudioUnitScope      inScope,
                                 AudioUnitElement    inElement,
                                 void *              outData);
    virtual OSStatus GetPropertyInfo(AudioUnitPropertyID inID,
                                     AudioUnitScope      inScope,
                                     AudioUnitElement    inElement,
                                     UInt32 &            outDataSize,
                                     Boolean &           outWritable);
    
    virtual OSStatus Render(AudioUnitRenderActionFlags &ioActionFlags,
                            const AudioTimeStamp &inTimeStamp,
                            UInt32 inNumberFrames);
};


AUDIOCOMPONENT_ENTRY(AUMusicDeviceFactory, AudioUnitSynth)

AudioUnitSynth::AudioUnitSynth(AudioUnit inComponentInstance)
: AUInstrumentBase(inComponentInstance, 0, 1) {
    CreateElements();
    
}

AudioUnitSynth::~AudioUnitSynth() {
    
}

void AudioUnitSynth::Cleanup() {
    
    AUInstrumentBase::Cleanup();
}

OSStatus AudioUnitSynth::Initialize() {
    
    AUInstrumentBase::Initialize();
    
    return noErr;
}


OSStatus AudioUnitSynth::GetProperty(AudioUnitPropertyID inID,
                               AudioUnitScope      inScope,
                               AudioUnitElement    inElement,
                               void *              outData) {
    
    if (inScope == kAudioUnitScope_Global) {
        
        switch (inID) {
                
            case kAudioUnitProperty_CocoaUI: {
                
                CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFSTR("com.eddyc.AudioUnitSynth"));
                
                if (bundle == NULL) return fnfErr;
                
                CFURLRef bundleURL = CFBundleCopyResourceURL(bundle,
                                                             CFSTR("AudioUnitSynthView"),
                                                             CFSTR("bundle"),
                                                             NULL);
                
                if (bundleURL == NULL) return fnfErr;
                
                CFStringRef className = CFSTR("AudioUnitSynthView_ViewFactory");
                
                AudioUnitCocoaViewInfo cocoaInfo = {bundleURL, {className}};
                *((AudioUnitCocoaViewInfo *)outData) = cocoaInfo;
                
                return noErr;
            }
        }
    }
    
    return AUInstrumentBase::GetProperty(inID, inScope, inElement, outData);
}

OSStatus AudioUnitSynth::GetPropertyInfo(AudioUnitPropertyID inID,
                                   AudioUnitScope      inScope,
                                   AudioUnitElement    inElement,
                                   UInt32 &            outDataSize,
                                   Boolean &           outWritable) {
    
    if (inScope == kAudioUnitScope_Global) {
        
        switch (inID) {
                
            case kAudioUnitProperty_CocoaUI: {
                
                outWritable = false;
                outDataSize = sizeof(AudioUnitCocoaViewInfo);
                return noErr;
            }
        }
    }
    
    return AUInstrumentBase::GetPropertyInfo(inID, inScope, inElement, outDataSize, outWritable);
}

OSStatus AudioUnitSynth::Render(AudioUnitRenderActionFlags &ioActionFlags,
                          const AudioTimeStamp &inTimeStamp,
                          UInt32 inNumberFrames)
{
    
    AUScope &outputs = Outputs();
    UInt32 numOutputs = outputs.GetNumberOfElements();
    for (UInt32 j = 0; j < numOutputs; ++j)
    {
        GetOutput(j)->PrepareBuffer(inNumberFrames);	// AUBase::DoRenderBus() only does this for the first output element
        AudioBufferList& bufferList = GetOutput(j)->GetBufferList();
        for (UInt32 k = 0; k < bufferList.mNumberBuffers; ++k)
        {
            memset(bufferList.mBuffers[k].mData, 0, bufferList.mBuffers[k].mDataByteSize);
        }
    }
    UInt32 numGroups = Groups().GetNumberOfElements();
    for (UInt32 j = 0; j < numGroups; ++j)
    {
        SynthGroupElement *group = (SynthGroupElement*)Groups().GetElement(j);
        OSStatus err = group->Render((SInt64)inTimeStamp.mSampleTime, inNumberFrames, outputs);
        if (err) return err;
    }
    
    mAbsoluteSampleFrame += inNumberFrames;
    return noErr;
}