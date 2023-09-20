#include "PluginParameters.h"


juce::AudioProcessorValueTreeState::ParameterLayout PluginParameters::createParameters() {
  juce::AudioProcessorValueTreeState::ParameterLayout params;

  params.add(std::make_unique<juce::AudioParameterFloat>(
      "GAIN",
      "Gain",
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f, 0.5f),
      0.5f));

  params.add(std::make_unique<juce::AudioParameterBool>(
      "BYPASS",
      "Bypass",
      false));

  params.add(std::make_unique<juce::AudioParameterFloat>(
      "DELAY_TIME",
      "DelayLine Time",
      juce::NormalisableRange<float>(0.1f, 4000.0f, 0.1f, 1.0f),
      500.0f));

  params.add(std::make_unique<juce::AudioParameterFloat>(
      "REVERSE_TIME",
      "Reverse Time",
      juce::NormalisableRange<float>(0.1f, 4000.0f, 0.1f, 1.0f),
      500.0f));

  params.add(std::make_unique<juce::AudioParameterFloat>(
      "FEEDBACK",
      "Feedback",
      juce::NormalisableRange<float>(0.0f, 0.9f, 0.001f, 2.0f),
      0.5f));

  params.add(std::make_unique<juce::AudioParameterFloat>(
      "FEEDBACK_REV",
      "Feedback delay/reverse ",
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f, 1.0f),
      0.5f));

  params.add(std::make_unique<juce::AudioParameterFloat>(
      "DYL_REV",
      "Delay/Reverse",
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f, 1.0f),
      0.5f));

  params.add(std::make_unique<juce::AudioParameterFloat>(
      "ALPHA",
      "Alpha",
      juce::NormalisableRange<float>(0.05f, 10.0f, 0.001f, 0.5f),
      2.0f));

  params.add(std::make_unique<juce::AudioParameterFloat>(
      "DRY_WET",
      "Dry/Wet",
      juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f, 1.0f),
      0.5f));

  return params;
}
