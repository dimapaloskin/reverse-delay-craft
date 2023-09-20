#include "DelayLine.h"


DelayLine::DelayLine(int _bufferSize) {
  bufferSize = _bufferSize;
  buffer = new float[static_cast<unsigned long>(_bufferSize)];
  reset();
}


DelayLine::DelayLine(int _bufferSize, float _delayTime, float _feedback) {
  bufferSize = _bufferSize;
  buffer = new float[static_cast<unsigned long>(_bufferSize)];
  reset();
  delayTime = _delayTime;
  feedback = _feedback;
}


DelayLine::~DelayLine() {
  delete[] this->buffer;
}


void DelayLine::reset() {
  for (int i = 0; i < bufferSize; ++i) {
    buffer[i] = 0.0f;
  }
}


void DelayLine::setSampleRate(float _sampleRate) {
  sampleRate = _sampleRate;
}



void DelayLine::setDryWet(float _dryWet) {
  dryWet = std::clamp(_dryWet, 0.0f, 1.0f);
}


void DelayLine::setFeedback(float _feedback) {
  feedback = std::clamp(_feedback, 0.0f, 0.99f);
}

void DelayLine::setReverseFeedback(float _reverseFeedback) {
  reverseFeedback = std::clamp(_reverseFeedback, 0.0f, 0.99f);
}

void DelayLine::setDelayReverse(float _delayReverse) {
  delayReverse = std::clamp(_delayReverse, 0.0f, 1.0f);
}



void DelayLine::setDelayTime(float _delayTime) {
  targetDelayTime = std::clamp(_delayTime, 1.0f, static_cast<float>(bufferSize));
  delayTimeStep = (targetDelayTime - delayTime) / (sampleRate * 0.01f);
  std::cout << delayTime << std::endl;
  std::cout << "Target delay time: " << targetDelayTime << std::endl;
}

void DelayLine::setReverseTime(float _reverseTime) {
  targetReverseTime = std::clamp(_reverseTime, 1.0f, static_cast<float>(bufferSize));
  reverseTimeStep = (targetReverseTime - reverseTime) / (sampleRate * 0.01f);

  std::cout << reverseTime << std::endl;
  std::cout << "Target reverse time: " << targetReverseTime << std::endl;
}

void DelayLine::setAlpha(float _alpha) {
  alpha = _alpha;
}


float DelayLine::processSample(float sample) {
  if (abs(delayTime - targetDelayTime) >= abs(delayTimeStep)) {
    delayTime += delayTimeStep;
  } else {
    delayTime = targetDelayTime;
  }

  if (abs(reverseTime - targetReverseTime) >= abs(reverseTimeStep)) {
    reverseTime += reverseTimeStep;
  } else {
    reverseTime = targetReverseTime;
  }

  if (delayTime < 1.0f) {
    return sample;
  }

  if (reverseTime < 1.0f) {
    return sample;
  }

  int dl = static_cast<int>(reverseTime); // reverse
  int left = (dl - readPointer);

  int readIndex = (((writeIndex - dl + bufferSize) % bufferSize - readPointer + left) + bufferSize) % bufferSize;
  int readIndexNext = (readIndex - 1 + bufferSize) % bufferSize;
  float fraction = reverseTime - round(reverseTime);
  float delayedSample = buffer[readIndex] + fraction * (buffer[readIndexNext] - buffer[readIndex]); // linear interpolation

  int readIndexDel = (writeIndex - static_cast<int>(delayTime) + bufferSize) % bufferSize;
  int readIndexNextDel = (readIndexDel + 1) % bufferSize;

  float fractionDel = delayTime - round(delayTime);
  float delayedSampleDel = buffer[readIndexDel] + fractionDel * (buffer[readIndexNextDel] - buffer[readIndexDel]);

  // window for delayedSample
  // 0.5 - 0.5 * (np.cos((2 * np.pi * x) / (dl - 1)))
//  float cosArg = (2.0f * juce::MathConstants<float>::twoPi * static_cast<float>(readPointer)) / (reverseTime - 1.0f);
//  float hann_coef = 0.5f - 0.5f * std::cosf(cosArg);

  float sinArg = (juce::MathConstants<float>::pi * static_cast<float>(readPointer)) / (reverseTime - 1.0f);
  float sin = std::sinf(sinArg);
  if (sin < 0.0f) {
    sin = 0.0f;
  }

  float hann_coef = std::powf(sin, alpha);
//  if ( !(hann_coef >= 0.0f && hann_coef <= 1.0f)) {
//    juce::Logger::writeToLog("sinArg: " + std::to_string(sinArg));
//    juce::Logger::writeToLog("hann_coef: " + std::to_string(hann_coef));
//    juce::Logger::writeToLog("readPointer: " + std::to_string(readPointer));
//    juce::Logger::writeToLog("alpha: " + std::to_string(alpha));
//  }
//

  float y = (1.0f - dryWet) * sample + dryWet * (delayReverse * hann_coef * delayedSample + (1.0f - delayReverse) * delayedSampleDel);
//  buffer[writeIndex] = y;
  buffer[writeIndex] = sample + feedback * ((1.0f - reverseFeedback) * delayedSampleDel + reverseFeedback * (delayedSample * hann_coef));
  writeIndex = (writeIndex + 1) % bufferSize;

  readPointer = (readPointer + 1) % static_cast<int>(reverseTime);
  return y;
}
