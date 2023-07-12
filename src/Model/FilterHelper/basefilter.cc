#include "basefilter.h"

namespace ng {
void BaseConvolutionFilter::Convolution(std::vector<std::vector<float> > kernel,
                                        const QImage &start,
                                        QImage &filtered) const {
  float red, green, blue;
  for (int height = 0; height != start.height(); ++height) {
    for (int width = 0; width != start.width(); ++width) {
      red = green = blue = 0;
      for (int i = 0; i != _kernel_height; ++i) {
        for (int j = 0; j != _kernel_width; ++j) {
          if (width + j < start.width() && height + i < start.height()) {
            QColor color = start.pixelColor(width + j, height + i);
            red += color.redF() * kernel[i][j];
            green += color.greenF() * kernel[i][j];
            blue += color.blueF() * kernel[i][j];
          }
        }
      }
      red = qBound(0.f, red, 1.f);
      green = qBound(0.f, green, 1.f);
      blue = qBound(0.f, blue, 1.f);
      filtered.setPixelColor(width, height, QColor::fromRgbF(red, green, blue));
    }
  }
}

QColor BaseColorCorrectionFilter::RgbToHSLToRgb(const QColor &color) {
  // https://ru.wikipedia.org/wiki/HSL
  float hue = CalculateHue(color);
  float saturation = CalculateSaturationHSL(color);
  float lightness = CalculateLightness(color);
  return HslToRgb(hue, saturation, lightness);
}

QColor BaseColorCorrectionFilter::HslToRgb(float hue, float saturation,
                                           float lightness) {
  // https://en.wikipedia.org/wiki/HSL_and_HSV
  QColor rgb;
  float c = (1 - std::fabs(2 * lightness - 1)) * saturation;
  float x = c * (1 - std::fabs(std::fmod(hue, 2) - 1));
  float m = lightness - c / 2;

  if (hue >= 0 && hue < 1)
    rgb.setRgbF(c, x, 0);
  else if (hue >= 1 && hue < 2)
    rgb.setRgbF(x, c, 0);
  else if (hue >= 2 && hue < 3)
    rgb.setRgbF(0, c, x);
  else if (hue >= 3 && hue < 4)
    rgb.setRgbF(0, x, c);
  else if (hue >= 4 && hue < 5)
    rgb.setRgbF(x, 0, c);
  else if (hue >= 5)
    rgb.setRgbF(c, 0, x);
  rgb.setRgbF(rgb.redF() + m, rgb.greenF() + m, rgb.blueF() + m);
  return rgb;
}

QColor BaseColorCorrectionFilter::RgbToHSVToRgb(const QColor &color) {
  // https://ru.wikipedia.org/wiki/HSV_(%D1%86%D0%B2%D0%B5%D1%82%D0%BE%D0%B2%D0%B0%D1%8F_%D0%BC%D0%BE%D0%B4%D0%B5%D0%BB%D1%8C)#RGB_%E2%86%92_HSV
  float hue = CalculateHue(color);
  float saturation = CalculateSaturationHSV(color);
  float value = CalculateValue(color);
  return HsvToRgb(hue, saturation, value);
}

QColor BaseColorCorrectionFilter::HsvToRgb(float hue, float saturation,
                                           float value) {
  // https://en.wikipedia.org/wiki/HSL_and_HSV
  QColor rgb;
  float c = value + saturation;
  float x = c * (1 - std::fabs(std::fmod(hue, 2) - 1));
  float m = value - c;

  if (hue >= 0 && hue < 1)
    rgb.setRgbF(c, x, 0);
  else if (hue >= 1 && hue < 2)
    rgb.setRgbF(x, c, 0);
  else if (hue >= 2 && hue < 3)
    rgb.setRgbF(0, c, x);
  else if (hue >= 3 && hue < 4)
    rgb.setRgbF(0, x, c);
  else if (hue >= 4 && hue < 5)
    rgb.setRgbF(x, 0, c);
  else if (hue >= 5)
    rgb.setRgbF(c, 0, x);
  rgb.setRgbF(rgb.redF() + m, rgb.greenF() + m, rgb.blueF() + m);
  return rgb;
}

float BaseColorCorrectionFilter::NormalizeHue(float hue) {
  if (hue > 360) {
    hue -= 360;
  } else if (hue < 0) {
    hue += 360;
  }
  return hue;
}

float BaseColorCorrectionFilter::NormalizeSaturation(float saturation) {
  if (saturation > 1) {
    saturation = 1;
  } else if (saturation < 0) {
    saturation = 0;
  }
  return saturation;
}

float BaseColorCorrectionFilter::NormalizeLightnessValue(float lv) {
  if (lv > 1) {
    lv = 1;
  } else if (lv < 0) {
    lv = 0;
  }
  return lv;
}

float BaseColorCorrectionFilter::CalculateHue(const QColor &color) {
  float red = color.redF();
  float green = color.greenF();
  float blue = color.blueF();

  float min = std::min({red, green, blue});
  float max = std::max({red, green, blue});
  float delta = max - min;

  float hue = 0;
  if (delta == 0) {
    hue = 0;
  } else if (max == red) {
    hue = std::fmod((green - blue) / delta, 6);
  } else if (max == green) {
    hue = (blue - red) / delta + 2;
  } else if (max == blue) {
    hue = (red - green) / delta + 4;
  }
  hue *= 60;
  return NormalizeHue(hue + _hue) / 60;
}

float BaseColorCorrectionFilter::CalculateSaturationHSV(const QColor &color) {
  float max = std::max({color.redF(), color.greenF(), color.blueF()});
  float min = std::min({color.redF(), color.greenF(), color.blueF()});
  float delta = max - min;
  float value = max;
  float saturation = 0;
  if (value != 0) {
    saturation = delta / value;
  }

  if (value == 0 || value == 1) {
    saturation = 0;
  } else {
    saturation = (max - value) / std::min(value, 1 - value);
  }

  if (delta != 0) {
    saturation += _saturation / 255;
  }
  return NormalizeSaturation(saturation);
}

float BaseColorCorrectionFilter::CalculateSaturationHSL(const QColor &color) {
  float max = std::max({color.redF(), color.greenF(), color.blueF()});
  float min = std::min({color.redF(), color.greenF(), color.blueF()});
  float delta = max - min;
  float lightness = (max + min) / 2;
  float saturation = 0;
  if (lightness == 0 || lightness == 1) {
    saturation = 0;
  } else {
    saturation = (max - lightness) / std::min(lightness, 1 - lightness);
  }

  if (delta != 0) {
    saturation += _saturation / 255;
  }
  return NormalizeSaturation(saturation);
}

float BaseColorCorrectionFilter::CalculateValue(const QColor &color) {
  float value = std::max({color.redF(), color.greenF(), color.blueF()});
  value += _value / 255;
  return NormalizeLightnessValue(value);
}

float BaseColorCorrectionFilter::CalculateLightness(const QColor &color) {
  float max = std::max({color.redF(), color.greenF(), color.blueF()});
  float min = std::min({color.redF(), color.greenF(), color.blueF()});
  float lightness = (max + min) / 2;
  lightness += _lightness / 255;
  return NormalizeLightnessValue(lightness);
}

int BaseColorCorrectionFilter::Truncate(int value) {
  int result = value;
  if (value > 255) {
    result = 255;
  } else if (value < 0) {
    result = 0;
  }
  return result;
}
}  // namespace ng
