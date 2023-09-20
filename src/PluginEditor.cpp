#include "PluginProcessor.h"
#include "PluginEditor.h"


AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p) {
  juce::ignoreUnused(processorRef);
  setResizable(true, true);
  setSize(400, 300);

  gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  gainSlider.setRange(0.0f, 1.0f);
  gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);

  gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
      processorRef.parameters,
      "GAIN",
      gainSlider);

  bypassButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
      processorRef.parameters,
      "BYPASS",
      bypassButton);

  addAndMakeVisible(gainSlider);
  addAndMakeVisible(bypassButton);
}


AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() = default;


void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}


void AudioPluginAudioProcessorEditor::resized() {
  gainSlider.setBounds(10, 10, 100, 100);
  bypassButton.setBounds(10, 110, 100, 50);
}
