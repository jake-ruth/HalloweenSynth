#pragma once
#include <JuceHeader.h>
#include "maximilian.h"
#include "SynthSound.h"
#include "maxiReverb.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:    
    bool canPlaySound (juce::SynthesiserSound* canPlaySound) override
    {
        return dynamic_cast<SynthSound*>(canPlaySound) != nullptr;
    }
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override
    {
        std::cout << midiNoteNumber << std::endl;
        
        //0 or 1 whether or not envelope is being triggered
        envelope.trigger = 1;
        level = velocity;
        frequency =  juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        envelope.trigger = 0;
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }
    
    void pitchWheelMoved(int newPitchWheelValue) override
    {
        
    }
    void controllerMoved (int controllerNumber, int newControllerValue) override
    {
        
    }
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override
    {
        //Appears all values for envelope must be set for it to work!
        envelope.setAttack(_attackValue);
        envelope.setDecay(_decayValue);
        envelope.setSustain(0.8);
        envelope.setRelease(5000);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double sine = oscillator.sinewave(frequency);
            
            double theSound = envelope.adsr(sine, envelope.trigger) * level;
            
            double filteredSound = filter.lores(theSound, 100, 0.5);
            
            //Glitchy sounding not sure why yet
            double chorus = maxiChorus1.chorus(filteredSound, 300, 0.5, 5, 1);
            
            double verb = reverb.play(filteredSound);
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, filteredSound);
            }
            
            ++startSample;
        }
    }
    
    void setAttackValue(std::atomic<float>* attackValue)
    {
        _attackValue = double(*attackValue);
    }
    
    void setDecayValue(std::atomic<float>* decayValue)
    {
        _decayValue = double(*decayValue);
    }
    
    void setSustainValue(std::atomic<float>* sustainValue)
    {
        _sustainValue = double(*sustainValue);
    }
    
    void setReleaseValue(std::atomic<float>* releaseValue)
    {
        _releaseValue = double(*releaseValue);
    }
    
private:
    double frequency;
    double level;
    
    double _attackValue = 100;
    double _decayValue = 100;
    double _sustainValue = 100;
    double _releaseValue = 100;
    
    maxiOsc oscillator;
    maxiChorus maxiChorus1;
    
    maxiEnv envelope;
    
    maxiFreeVerb reverb;
    maxiFilter filter;
};
