#include "colorcorrectionfilters.h"

namespace ng {
void BrightnessFilter::Execute(const QImage &start, QImage &filtered) {
  // https://esate.ru/uroki/OpenGL/image_processing/_p4106/
  for (int height = 0; height != start.height(); ++height) {
    for (int width = 0; width != start.width(); ++width) {
      QColor pixel_color = start.pixelColor(width, height);
      int red = Truncate(pixel_color.red() + brightness_);
      int green = Truncate(pixel_color.green() + brightness_);
      int blue = Truncate(pixel_color.blue() + brightness_);
      filtered.setPixelColor(width, height, QColor(red, green, blue));
    }
  }
}

void ContrastFilter::Execute(const QImage &start, QImage &filtered) {
  // https://esate.ru/uroki/OpenGL/image_processing/_p4106/
  contrast_ = 1.f + contrast_ / 10.f;
  contrast_ = contrast_ * contrast_;
  for (int height = 0; height != start.height(); ++height) {
    for (int width = 0; width != start.width(); ++width) {
      QColor pixel_color = start.pixelColor(width, height);
      float tmp_red = pixel_color.redF();
      tmp_red -= 0.5;
      tmp_red *= contrast_;
      tmp_red += 0.5;
      tmp_red *= 255;
      int red = Truncate(tmp_red);

      float tmp_green = pixel_color.greenF();
      tmp_green -= 0.5;
      tmp_green *= contrast_;
      tmp_green += 0.5;
      tmp_green *= 255;
      int green = Truncate(tmp_green);

      float tmp_blue = pixel_color.blueF();
      tmp_blue -= 0.5;
      tmp_blue *= contrast_;
      tmp_blue += 0.5;
      tmp_blue *= 255;
      int blue = Truncate(tmp_blue);

      filtered.setPixelColor(width, height, QColor(red, green, blue));
    }
  }
}

void HSLColorFilter::Execute(const QImage &start, QImage &filtered) {
  for (int height = 0; height != start.height(); ++height) {
    for (int width = 0; width != start.width(); ++width) {
      QColor color = start.pixelColor(width, height);
      color = RgbToHSLToRgb(color);
      filtered.setPixelColor(width, height, color.rgb());
    }
  }
}

void HSVColorFilter::Execute(const QImage &start, QImage &filtered) {
  for (int height = 0; height != start.height(); ++height) {
    for (int width = 0; width != start.width(); ++width) {
      QColor color = start.pixelColor(width, height);
      color = RgbToHSVToRgb(color);
      filtered.setPixelColor(width, height, color.rgb());
    }
  }
}
}  // namespace ng
