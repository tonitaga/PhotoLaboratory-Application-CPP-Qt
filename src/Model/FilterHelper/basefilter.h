#ifndef FILTERENGINE_BASEFILTER_H
#define FILTERENGINE_BASEFILTER_H

#include <QImage>
#include <vector>

namespace ng {
/**
 * =============== BaseFilter class ===============
 * Main information:
 * BaseFilter class is the base of all filters (class is an interface)
 */
class BaseFilter {
 public:
  virtual ~BaseFilter() = default;
  virtual void Execute(const QImage &start, QImage &filtered) = 0;
};

/**
 * =============== BaseNonConvolutionFilter class ===============
 * Main information:
 * BaseConvolutionFilter class is the base of all convlolution filters (class is
 * an interface) ng::EmbossFilter, ng::SharpenFilter, ng::BoxBlueFilter,
 * ng::GaussianBlurFilter, ng::LaplacianFilter, ng::PrewittFilter,
 * ng::CustomKernelFilter
 */
class BaseConvolutionFilter : public BaseFilter {
 public:
  BaseConvolutionFilter() = default;
  ~BaseConvolutionFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override = 0;

 protected:
  void Convolution(std::vector<std::vector<float>> kernel, const QImage &start,
                   QImage &filtered) const;

  int _kernel_height = 0;
  int _kernel_width = 0;
};

/**
 * =============== BaseNonConvolutionFilter class ===============
 * Main information:
 * BaseNonConvolutionFilter class is the base of all non-convlolution filters
 * (class is an interface) ng::GrayScaleFilter, ng::NegativeFilter,
 * ng::ToningFilter
 */
class BaseNonConvolutionFilter : public BaseFilter {
 public:
  BaseNonConvolutionFilter() = default;
  ~BaseNonConvolutionFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override = 0;
};

/**
 * =============== BaseColorCorrectionFilter class ===============
 * Main information:
 * BaseColorCorrectionFilter class is the base of all color-correction filters
 * (class is an interface) ng::BrightnessFilter, ng::ContrastFilter,
 * ng::HSVColorFilter, ng::HSLColorFilter
 */
class BaseColorCorrectionFilter : public BaseFilter {
 public:
  BaseColorCorrectionFilter() = default;
  ~BaseColorCorrectionFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override = 0;

 protected:
  int _hue, _saturation, _lightness, _value;

  QColor RgbToHSLToRgb(const QColor &color);
  QColor HslToRgb(float hue, float saturation, float lightness);
  QColor RgbToHSVToRgb(const QColor &color);
  QColor HsvToRgb(float hue, float saturation, float value);

  static int Truncate(int value);

  float NormalizeHue(float hue);
  float NormalizeSaturation(float saturation);
  float NormalizeLightnessValue(float lv);

  float CalculateHue(const QColor &color);
  float CalculateSaturationHSV(const QColor &color);
  float CalculateSaturationHSL(const QColor &color);
  float CalculateValue(const QColor &color);
  float CalculateLightness(const QColor &color);
};
}  // namespace ng

#endif  // FILTERENGINE_BASEFILTER_H
