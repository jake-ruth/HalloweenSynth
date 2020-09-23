#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SynthPracticeAudioProcessorEditor  : public juce::AudioProcessorEditor

{
public:
    SynthPracticeAudioProcessorEditor (SynthPracticeAudioProcessor&);
    ~SynthPracticeAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider _attackSlider;
    juce::Slider _decaySlider;
    juce::Slider _sustainSlider;
    juce::Slider _releaseSlider;
    
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> _attackSliderValueTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> _decaySliderValueTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> _sustainSliderValueTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> _releaseSliderValueTree;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthPracticeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthPracticeAudioProcessorEditor)
};
