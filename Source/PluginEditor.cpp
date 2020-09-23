#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthPracticeAudioProcessorEditor::SynthPracticeAudioProcessorEditor (SynthPracticeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (500, 500);
    
    //Attack Slider
    addAndMakeVisible(_attackSlider);
    _attackSlider.setRange(100.0f, 10000.0f);
    _attackSlider.setSliderStyle(juce::Slider::LinearVertical);
    _attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    _attackSliderValueTree = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor._valueTreeState, "attack", _attackSlider);
    
    //Decay Slider
    addAndMakeVisible(_decaySlider);
    _decaySlider.setRange(100.0f, 10000.0f);
    _decaySlider.setSliderStyle(juce::Slider::LinearVertical);
    _decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    _decaySliderValueTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor._valueTreeState, "decay", _decaySlider);
    
    
    //Sustain Slider
    addAndMakeVisible(_sustainSlider);
    _sustainSlider.setRange(100.0f, 10000.0f);
    _sustainSlider.setSliderStyle(juce::Slider::LinearVertical);
    _sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    _sustainSliderValueTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor._valueTreeState, "sustain", _sustainSlider);
    
    //Release Slider
    addAndMakeVisible(_releaseSlider);
    _releaseSlider.setRange(100.0f, 10000.0f);
    _releaseSlider.setSliderStyle(juce::Slider::LinearVertical);
    _releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    _releaseSliderValueTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor._valueTreeState, "release", _releaseSlider);
    
}

SynthPracticeAudioProcessorEditor::~SynthPracticeAudioProcessorEditor()
{
}

//==============================================================================
void SynthPracticeAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

    g.setColour (juce::Colours::coral);
    g.setFont (30.0f);
    g.drawRect(100, 100, 100, 300);
    g.drawFittedText ("Jake's Halloween Synth", getLocalBounds(), juce::Justification::centredTop, 3);
    
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::teal);
}

void SynthPracticeAudioProcessorEditor::resized()
{
    _attackSlider.setBounds(10, 30, 200, 250);
    _decaySlider.setBounds(110, 30, 200, 250);
    _sustainSlider.setBounds(210, 30, 200, 250);
    _releaseSlider.setBounds(310, 30, 200, 250);
}
