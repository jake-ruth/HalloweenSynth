#pragma once
#include <JuceHeader.h>

//A synthesiser can contain one or more sounds, and a sound can choose which midi notes and channels can trigger it.

class SynthSound : public juce::SynthesiserSound //Describes one of the sounds that a Synthesiser can play
{
public:
    
    //The Synthesiser will use this information when deciding which sounds to trigger for a given note.
    bool appliesToNote(int midiNoteNumber) override
    {
        return true;
    }
    
    bool appliesToChannel (int midiChannel) override
    {
        return true;
    }
};
