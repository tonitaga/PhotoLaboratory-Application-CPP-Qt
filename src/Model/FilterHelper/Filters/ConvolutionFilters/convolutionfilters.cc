#include "convolutionfilters.h"

namespace ng {
void EmbossFilter::Execute(const QImage &start, QImage &filtered) {
  _kernel_width = 3;
  _kernel_height = 3;
  static std::vector<std::vector<float>> kernel{
      {-2.f, -1.f, 0.f}, {-1.f, 1.f, 1.f}, {0.f, 1.f, 2.f}};
  Convolution(kernel, start, filtered);
};

void SharpenFilter::Execute(const QImage &start, QImage &filtered) {
  _kernel_width = 3;
  _kernel_height = 3;
  static std::vector<std::vector<float>> kernel{
      {0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
  Convolution(kernel, start, filtered);
}

void BoxBlurFilter::Execute(const QImage &start, QImage &filtered) {
  _kernel_width = 3;
  _kernel_height = 3;
  float box = 1 / 9.f;
  static std::vector<std::vector<float>> kernel{
      {box, box, box}, {box, box, box}, {box, box, box}};
  Convolution(kernel, start, filtered);
}

void GaussianBlurFilter::Execute(const QImage &start, QImage &filtered) {
  // https://habr.com/ru/articles/142818/
  _kernel_width = 5;
  _kernel_height = 5;
  static std::vector<std::vector<float>> kernel{
      {0.000789f, 0.006581f, 0.013347f, 0.006581f, 0.000789f},
      {0.006581f, 0.054901f, 0.111345f, 0.054901f, 0.006581f},
      {0.013147f, 0.111345f, 0.225821f, 0.111345f, 0.013347f},
      {0.006581f, 0.054901f, 0.111345f, 0.054901f, 0.006581f},
      {0.000789f, 0.006581f, 0.013347f, 0.006581f, 0.000789f}};
  Convolution(kernel, start, filtered);
}

void LaplacianFilter::Execute(const QImage &start, QImage &filtered) {
  _kernel_width = 3;
  _kernel_height = 3;
  static std::vector<std::vector<float>> kernel{
      {-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
  Convolution(kernel, start, filtered);
}

void PrewittFilter::Execute(const QImage &start, QImage &filtered) {
  // https://ru.wikipedia.org/wiki/%D0%AF%D0%B4%D1%80%D0%BE_%D1%81%D0%B2%D0%B5%D1%80%D1%82%D0%BA%D0%B8
  _kernel_width = 3;
  _kernel_height = 3;
  static std::vector<std::vector<float>> kernel1{
      {1, 0, -1}, {1, 0, -1}, {1, 0, -1}};
  Convolution(kernel1, start, filtered);
}

void CustomKernelFilter::Execute(const QImage &start, QImage &filtered) {
  _kernel_width = kernel_[0].size();
  _kernel_height = kernel_.size();
  Convolution(kernel_, start, filtered);
}

}  // namespace ng
