#include <gtest/gtest.h>

#include <QImage>
#include <QLabel>

#include "filtercontroller.h"

ng::FilterController controller;

template <typename Filter, typename... Constraction>
QImage Execute(Constraction &&...constract_arguments) {
  controller.setBasicImage(QImage(":/test_original"));
  controller.template setFilter<Filter>(constract_arguments...);
  controller.ExecuteFilter();
  return controller.getFilteredImage();
}

void AssertEqual(const QImage &first, const QImage &second) {
  for (int i = 0; i != first.width(); ++i) {
    for (int j = 0; j != first.height(); ++j) {
      ASSERT_FLOAT_EQ(first.pixelColor(i, j).redF(),
                      second.pixelColor(i, j).redF());
      ASSERT_FLOAT_EQ(first.pixelColor(i, j).greenF(),
                      second.pixelColor(i, j).greenF());
      ASSERT_FLOAT_EQ(first.pixelColor(i, j).blueF(),
                      second.pixelColor(i, j).blueF());
    }
  }
}

TEST(Test, GrayScale) {
  QImage grayscale(":/test_grayscale");
  QImage filtered = Execute<ng::GrayScaleFilter>();
  AssertEqual(grayscale, filtered);
}

TEST(Test, Negative) {
  QImage negative(":/test_negative");
  QImage filtered = Execute<ng::NegativeFilter>();
  AssertEqual(negative, filtered);
}

TEST(Test, Toning) {
  QImage toning(":/test_toning");
  QImage filtered = Execute<ng::ToningFilter>(QColor(Qt::green));
  AssertEqual(toning, filtered);
}

TEST(Test, Emboss) {
  QImage emboss(":/test_emboss");
  QImage filtered = Execute<ng::EmbossFilter>();
  AssertEqual(emboss, filtered);
}

TEST(Test, Sharpen) {
  QImage sharpen(":/test_sharpen");
  QImage filtered = Execute<ng::SharpenFilter>();
  AssertEqual(sharpen, filtered);
}

TEST(Test, BoxBLur) {
  QImage boxblur(":/test_boxblur");
  QImage filtered = Execute<ng::BoxBlurFilter>();
  AssertEqual(boxblur, filtered);
}

TEST(Test, GaussianBlur) {
  QImage gaussian(":/test_gaussianblur");
  QImage filtered = Execute<ng::GaussianBlurFilter>();
  AssertEqual(gaussian, filtered);
}

TEST(Test, Laplacian) {
  QImage laplacian(":/test_laplacian");
  QImage filtered = Execute<ng::LaplacianFilter>();
  AssertEqual(laplacian, filtered);
}

TEST(Test, Prewitt) {
  QImage prewitt(":/test_prewitt");
  QImage filtered = Execute<ng::PrewittFilter>();
  AssertEqual(prewitt, filtered);
}

TEST(Test, CustomKernel) {
  QImage customkernel(":/test_kernel");
  std::vector<std::vector<float>> kernel{{0, 0, 0}, {0, 2, 0}, {0, 0, 0}};
  QImage filtered = Execute<ng::CustomKernelFilter>(kernel);
  AssertEqual(customkernel, filtered);
}

TEST(Test, Brightness) {
  QImage brightness(":/test_bright");
  QImage filtered = Execute<ng::BrightnessFilter>(100);
  AssertEqual(brightness, filtered);
}

TEST(Test, Contrast) {
  QImage contrast(":/test_contrast");
  QImage filtered = Execute<ng::ContrastFilter>(100);
  AssertEqual(contrast, filtered);
}

TEST(Test, HSL_HSV) {
  QImage hsl(":/test_hslv_0_255_130");
  QColor color = QColor::fromHsl(0, 255, 130);
  controller.setBasicImage(QImage(":/test_original2"));
  controller.setFilter<ng::HSLColorFilter>(color);
  QImage filtered = controller.getFilteredImage();
  AssertEqual(hsl, filtered);
  controller.setFilter<ng::HSVColorFilter>(color);
  AssertEqual(hsl, filtered);
}
