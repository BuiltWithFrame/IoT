// Forked from https://github.com/Makuna/NeoPixelBus/blob/master/examples/animations/NeoPixelFunLoop/NeoPixelFunLoop.ino

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>
const uint16_t PixelCount = 16;
const uint16_t PixelPin = 32;
const uint16_t AnimCount = PixelCount / 5 * 2 + 1;
const uint16_t PixelFadeDuration = 300;
const uint16_t NextPixelMoveDuration = 1000 / PixelCount;
NeoGamma<NeoGammaTableMethod> colorGamma;
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

struct MyAnimationState {
  RgbColor StartingColor;
  RgbColor EndingColor;
  uint16_t IndexPixel;
};

NeoPixelAnimator animations(AnimCount);
MyAnimationState animationState[AnimCount];
uint16_t frontPixel = 0;
RgbColor frontColor;

void setup() {
  strip.Begin();
  strip.Show();
  SetRandomSeed();
  animations.StartAnimation(0, NextPixelMoveDuration, LoopAnimUpdate);
}


void loop() {
  animations.UpdateAnimations();
  strip.Show();
}

void SetRandomSeed() {
  uint32_t seed;
  seed = analogRead(0);
  delay(1);
  for (int shifts = 3; shifts < 31; shifts += 3) {
    seed ^= analogRead(0) << shifts;
    delay(1);
  }
  randomSeed(seed);
}

void FadeOutAnimUpdate(const AnimationParam& param) {
  RgbColor updatedColor = RgbColor::LinearBlend(
    animationState[param.index].StartingColor,
    animationState[param.index].EndingColor,
    param.progress);
  strip.SetPixelColor(animationState[param.index].IndexPixel, 
     colorGamma.Correct(updatedColor));
}

void LoopAnimUpdate(const AnimationParam& param) {
  if (param.state == AnimationState_Completed) {
    animations.RestartAnimation(param.index);
    frontPixel = (frontPixel + 1) % PixelCount;
    if (frontPixel == 0) {
      frontColor = HslColor(random(360) / 360.0f, 1.0f, 0.25f);
    }
    uint16_t indexAnim;
    if (animations.NextAvailableAnimation(&indexAnim, 1)) {
      animationState[indexAnim].StartingColor = frontColor;
      animationState[indexAnim].EndingColor = RgbColor(0, 0, 0);
      animationState[indexAnim].IndexPixel = frontPixel;
      animations.StartAnimation(indexAnim, PixelFadeDuration, FadeOutAnimUpdate);
    }
  }
}
