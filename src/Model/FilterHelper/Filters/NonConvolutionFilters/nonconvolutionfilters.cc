#include "nonconvolutionfilters.h"

namespace ng {
void GrayScaleFilter::Execute(const QImage &start, QImage &filtered) {
  // https://fototips.ru/obrabotka/metody-preobrazovaniya-cvetnogo-izobrazheniya-v-chyorno-beloe/
  for (int height = 0; height < start.height(); ++height) {
    for (int width = 0; width < start.width(); ++width) {
      QColor pixel_color = start.pixelColor(width, height);
      float color_aspect = pixel_color.redF() * 0.3f +
                           pixel_color.greenF() * 0.59f +
                           pixel_color.blueF() * 0.11f;
      color_aspect = std::max(0.f, std::min(color_aspect, 1.f));
      filtered.setPixelColor(
          width, height,
          QColor::fromRgbF(color_aspect, color_aspect, color_aspect));
    }
  }
}

void NegativeFilter::Execute(const QImage &start, QImage &filtered) {
  QColor negative;
  for (int height = 0; height < start.height(); ++height) {
    for (int width = 0; width < start.width(); ++width) {
      QColor pixel_color = start.pixelColor(width, height);
      negative.setRgb(255 - pixel_color.red(), 255 - pixel_color.green(),
                      255 - pixel_color.blue());
      filtered.setPixelColor(width, height, negative);
    }
  }
}

void ToningFilter::Execute(const QImage &start, QImage &filtered) {
  for (int height = 0; height < start.height(); ++height) {
    for (int width = 0; width < start.width(); ++width) {
      QColor pixel_color = start.pixelColor(width, height);
      float color_aspect = pixel_color.redF() * 0.3f +
                           pixel_color.greenF() * 0.59f +
                           pixel_color.blueF() * 0.11f;
      color_aspect = std::max(0.f, std::min(color_aspect, 1.f));
      filtered.setPixelColor(
          width, height,
          QColor::fromRgbF(color_aspect * toning_color_.redF(),
                           color_aspect * toning_color_.greenF(),
                           color_aspect * toning_color_.blueF()));
    }
  }
}
}  // namespace ng
