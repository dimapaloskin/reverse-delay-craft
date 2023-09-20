#pragma once

#include "JuceHeader.h"

class DelayLine {
public:
  explicit DelayLine(int bufferSize);
  DelayLine(int bufferSize, float delayTime, float feedback);
  ~DelayLine();

  void setDelayTime(float delayTime);
  void setFeedback(float feedback);
  void setReverseFeedback(float reverseFeedback);
  float processSample(float sample);
  void setSampleRate(float sampleRate);
  void setDryWet(float dryWet);
  void setDelayReverse(float delayReverse);
  void setReverseTime(float reverseTime);
  void setAlpha(float alpha);
  void reset();
private:
  float* buffer;
  int bufferSize;

  float delayTime = 0.0f;
  float feedback = 0.0f;
  float reverseFeedback = 0.0f;
  float dryWet = 0.0f;
  float delayReverse = 0.5f;
  float reverseTime = 0.0f;


  int writeIndex = 0;
  int readPointer = 0;

  float targetDelayTime = 0.0f;
  float targetReverseTime = 0.0f;
  float delayTimeStep = 0.0f;
  float reverseTimeStep = 0.0f;

  float sampleRate = 0.0f;
  float alpha = 1.0f;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayLine)
};
