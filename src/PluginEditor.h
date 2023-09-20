#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>

class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
 public  :
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
  ~AudioPluginAudioProcessorEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;

 private:
  AudioPluginAudioProcessor &processorRef;

  juce::Slider gainSlider;
  juce::ToggleButton bypassButton{"Bypass"};

  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassButtonAttachment;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
