#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthPracticeAudioProcessor::SynthPracticeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
_valueTreeState(*this, nullptr)
#endif
{
    
    _valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>("attack", "Attack", 0.1f, 10000.0f, 5000.0f));
    _valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>("decay", "Decay", 0.1f, 10000.0f, 5000.0f));
    _valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", 0.1f, 10000.0f, 5000.0f));
    _valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>("release", "Release", 0.1f, 10000.0f, 5000.0f));
    
    mySynth.clearVoices();
    const int maxNumVoices = 5;
    
    
    for (int i = 0; i < maxNumVoices; i++)
    {
        mySynth.addVoice(new SynthVoice);
    }
    
    mySynth.clearSounds();

    mySynth.addSound(new SynthSound);
}

SynthPracticeAudioProcessor::~SynthPracticeAudioProcessor()
{
}

//==============================================================================
const juce::String SynthPracticeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthPracticeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthPracticeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthPracticeAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthPracticeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthPracticeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthPracticeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthPracticeAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthPracticeAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthPracticeAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthPracticeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    juce::ignoreUnused(samplesPerBlock);
    
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void SynthPracticeAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthPracticeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthPracticeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->setAttackValue(_valueTreeState.getRawParameterValue("attack"));
            myVoice->setDecayValue(_valueTreeState.getRawParameterValue("decay"));
            myVoice->setSustainValue(_valueTreeState.getRawParameterValue("sustain"));
            myVoice->setReleaseValue(_valueTreeState.getRawParameterValue("release"));
        }
    }
    
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SynthPracticeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthPracticeAudioProcessor::createEditor()
{
    return new SynthPracticeAudioProcessorEditor (*this);
}

//==============================================================================
void SynthPracticeAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthPracticeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthPracticeAudioProcessor();
}
