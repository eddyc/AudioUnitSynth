# AudioUnitSynth
Barebones AudioUnit project for a synthesiser

Create new Xcode project: Bundle, set bundle extension: component
 
To Info.plist add Array named: AudioComponents

To Array add Dictionary named: Item 0, it's the default name

To Dictionary add keys:

  manufacturer    NAME              String  The AudioUnit name
  
  sandboxSafe     YES               Boolean
  
  subtype         SUBT              String  The AudioUnit subtype
  
  version         65536             Number
  
  type            aumu/aufx         String  Either depending on type Instrument or Effect
  
  description     The AU            String  Description of AudioUnit
  
  name            The Name          String  Name of the AudioUnit
  
  factoryFunction AudioUnitFactory  String  AudioUnit main class name with Factory suffix
 
Create .exp file and add the factoryFunction variable prefixed with underscore: _AudioUnitFactory
 
In Build settings

Add the .exp file path to Exported Symbols File e.g. $(SRCROOT)/src/ExportFile.exp

Add -bundle to Other Linker Flags

For Deployment set Installation Directory to $(HOME)/Library/Audio/Plug-Ins/Components/

Set Installation Build Products Location to /

Set Deployment Location to Yes

Set Skip Install to No

Set Force Package Info Generation to Yes
 
In Link Binary With Libraries add

AudioToolbox.framework

AudioUnit.framework

CoreMIDI.framework if its a synth

CoreServices.framework
 
For GUI
 
Add new target bundle

Set Other Linker Flags -framework Foundation -framework AppKit

In Info.plist

Set Main nib file base name AudioUnitView

Set Principle class AudioUnitView_ViewFactory

Add xib file to GUI target

Set xib files ownder to AudioUnitView_ViewFactory

Add UIView and set Custom Class to AudioUnitView_UIView
 
In AudioUnit target add Target Dependencies Build Phase

Add AudioUnitView as Target Dependencie

Add Copy Files phase and set Destination Resources and add AudioUnitView.bundle 
