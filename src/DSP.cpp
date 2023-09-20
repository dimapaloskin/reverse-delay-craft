#include "DSP.h"


JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wshadow-field-in-constructor")

DSP::DSP(juce::AudioProcessorValueTreeState &parameters)
    : parameters(parameters) {

  for (auto param : parameters.processor.getParameters()) {
    auto p = dynamic_cast<juce::AudioProcessorParameterWithID *>(param);
    parameters.addParameterListener(p->paramID, this);
  }
}

JUCE_END_IGNORE_WARNINGS_GCC_LIKE


DSP::~DSP() noexcept {
  for (auto param : parameters.processor.getParameters()) {
    auto p = dynamic_cast<juce::AudioProcessorParameterWithID *>(param);
    parameters.removeParameterListener(p->paramID, this);
  }
}


void DSP::parameterChanged(const juce::String &parameterID, float value) {
  std::cout << "Parameter changed: " << parameterID << " " << value << std::endl;
  if (parameterID == "DELAY_TIME") {
    float delayTime = value * 0.001f * sampleRate;
    delays[0]->setDelayTime(delayTime);
    delays[1]->setDelayTime(delayTime);
  }

  if (parameterID == "REVERSE_TIME") {
    float reverseTime = value * 0.001f * sampleRate;
    delays[0]->setReverseTime(reverseTime);
    delays[1]->setReverseTime(reverseTime);
  }
}


void DSP::prepareToPlay(double _sampleRate, int _samplesPerBlock) {
  sampleRate = static_cast<float>(_sampleRate);
  samplesPerBlock = static_cast<float>(_samplesPerBlock);

  delays[0] = std::make_unique<DelayLine>(static_cast<int>(sampleRate * 20.0f));
  delays[1] = std::make_unique<DelayLine>(static_cast<int>(sampleRate * 20.0f));

  delays[0]->setSampleRate(sampleRate);
  delays[1]->setSampleRate(sampleRate);

  float delayTime = parameters.getRawParameterValue("DELAY_TIME")->load() * 0.001f * sampleRate;
  delays[0]->setDelayTime(delayTime);
  delays[1]->setDelayTime(delayTime);

  float reverseTime = parameters.getRawParameterValue("REVERSE_TIME")->load() * 0.001f * sampleRate;
  delays[0]->setReverseTime(reverseTime);
  delays[1]->setReverseTime(reverseTime);
}


void DSP::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
  juce::ignoreUnused(midiMessages);

  juce::dsp::AudioBlock<float> block(buffer);

  for (size_t channel = 0; channel < block.getNumChannels(); ++channel) {
    auto channelBlock = block.getChannelPointer(channel);

    for (size_t n = 0; n < block.getNumSamples(); ++n) {
      channelBlock[n] = processSample(static_cast<int>(channel), channelBlock[n]);
    }
  }
}


float DSP::processSample(int channel, float sample) {
  float gainParam = parameters.getRawParameterValue("GAIN")->load();
  float dryWet = parameters.getRawParameterValue("DRY_WET")->load();
  float bypass = (1.0f - parameters.getRawParameterValue("BYPASS")->load());
  float feedback = parameters.getRawParameterValue("FEEDBACK")->load();
  float reverseFeedback = parameters.getRawParameterValue("FEEDBACK_REV")->load();
  float delayReverse = parameters.getRawParameterValue("DYL_REV")->load();
  float alpha = parameters.getRawParameterValue("ALPHA")->load();

  float gain = gainParam * bypass;

  delays[channel]->setFeedback(feedback);
  delays[channel]->setDryWet(dryWet);
  delays[channel]->setReverseFeedback(reverseFeedback);
  delays[channel]->setDelayReverse(delayReverse);
  delays[channel]->setAlpha(alpha);

  float y = gain * delays[channel]->processSample(sample);
  return y;
}
