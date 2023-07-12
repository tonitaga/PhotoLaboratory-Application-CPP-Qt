#ifndef PHOTOLAB_V1_0_COLORCORRECTIONFILTERS_H
#define PHOTOLAB_V1_0_COLORCORRECTIONFILTERS_H

#include "../../basefilter.h"

namespace ng {
/**
 * =============== BrightnessFilter class ===============
 * Main information:
 * Class is an inheritor of BaseColorCorrectionFilter class
 */
class BrightnessFilter : public BaseColorCorrectionFilter {
 public:
  BrightnessFilter(int brightness = int()) : brightness_(brightness) {}
  ~BrightnessFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;

 private:
  int brightness_ = 0;
};

/**
 * =============== ContrastFilter class ===============
 * Main information:
 * Class is an inheritor of BaseColorCorrectionFilter class
 */
class ContrastFilter : public BaseColorCorrectionFilter {
 public:
  ContrastFilter(int contrast = int()) : contrast_(contrast) {}
  ~ContrastFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;

 private:
  int contrast_ = 0;
};

/**
 * =============== HSLColorFilter class ===============
 * Main information:
 * Class is an inheritor of BaseColorCorrectionFilter class
 */
class HSLColorFilter : public BaseColorCorrectionFilter {
 public:
  HSLColorFilter(int hue, int saturation, int lightness) {
    _hue = hue;
    _saturation = saturation;
    _value = lightness;
  }

  explicit HSLColorFilter(QColor hsl_color) {
    _hue = hsl_color.hue();
    _saturation = hsl_color.saturation();
    _lightness = hsl_color.lightness();
  }
  ~HSLColorFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;
};

/**
 * =============== HSVColorFilter class ===============
 * Main information:
 * Class is an inheritor of BaseColorCorrectionFilter class
 */
class HSVColorFilter : public BaseColorCorrectionFilter {
 public:
  HSVColorFilter(int hue, int saturation, int value) {
    _hue = hue;
    _saturation = saturation;
    _value = value;
  }

  explicit HSVColorFilter(QColor hsv_color) {
    _hue = hsv_color.hue();
    _saturation = hsv_color.saturation();
    _value = hsv_color.value();
  }

  ~HSVColorFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;
};
}  // namespace ng

#endif  // PHOTOLAB_V1_0_COLORCORRECTIONFILTERS_H
