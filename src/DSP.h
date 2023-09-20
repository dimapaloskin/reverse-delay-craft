#pragma once

#include "JuceHeader.h"
#include "PluginParameters.h"
#include "dsp/DelayLine.h"

class DSP : public juce::AudioProcessorValueTreeState::Listener {
public:
  explicit DSP(juce::AudioProcessorValueTreeState &parameters);

  ~DSP() noexcept override;

  void prepareToPlay(double sampleRate, int samplesPerBlock);

  float processSample(int channel, float sample);

  void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages);
private:
  juce::AudioProcessorValueTreeState &parameters;

  float sampleRate = 0.0f;
  float samplesPerBlock = 0.0f;

  std::unique_ptr<DelayLine> delays[2];

  void parameterChanged(const juce::String &parameterID, float newValue) override;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DSP)
};
