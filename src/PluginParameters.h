#pragma once

#include "JuceHeader.h"

class PluginParameters {
public:
  static juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
};
