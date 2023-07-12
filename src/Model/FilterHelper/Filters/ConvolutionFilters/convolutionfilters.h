#ifndef FILTERENGINE_CONVOLUTIONFILTERS_H
#define FILTERENGINE_CONVOLUTIONFILTERS_H

#include "../../basefilter.h"

// https://en.wikipedia.org/wiki/Kernel_(image_processing)

namespace ng {
/**
 * =============== EmbossFilter class ===============
 * Main information:
 * Class is an inheritor of BaseConvolutionFilter class
 */
class EmbossFilter : public BaseConvolutionFilter {
 public:
  EmbossFilter() = default;
  ~EmbossFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;
};

/**
 * =============== SharpenFilter class ===============
 * Main information:
 * Class is an inheritor of BaseConvolutionFilter class
 */
class SharpenFilter : public BaseConvolutionFilter {
 public:
  SharpenFilter() = default;
  ~SharpenFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;
};

/**
 * =============== BoxBlurFilter class ===============
 * Main information:
 * Class is an inheritor of BaseConvolutionFilter class
 */
class BoxBlurFilter : public BaseConvolutionFilter {
 public:
  BoxBlurFilter() = default;
  ~BoxBlurFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;
};

/**
 * =============== GaussianBlurFilter class ===============
 * Main information:
 * Class is an inheritor of BaseConvolutionFilter class
 */
class GaussianBlurFilter : public BaseConvolutionFilter {
 public:
  GaussianBlurFilter() = default;
  ~GaussianBlurFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;
};

/**
 * =============== LaplacianFilter class ===============
 * Main information:
 * Class is an inheritor of BaseConvolutionFilter class
 */
class LaplacianFilter : public BaseConvolutionFilter {
 public:
  LaplacianFilter() = default;
  ~LaplacianFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;
};

/**
 * =============== PrewittFilter class ===============
 * Main information:
 * Class is an inheritor of BaseConvolutionFilter class
 */
class PrewittFilter : public BaseConvolutionFilter {
 public:
  PrewittFilter() = default;
  ~PrewittFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;
};

/**
 * =============== CustomKernelFilter class ===============
 * Main information:
 * Class is an inheritor of BaseConvolutionFilter class
 */
class CustomKernelFilter : public BaseConvolutionFilter {
 public:
  CustomKernelFilter(const std::vector<std::vector<float>> &kernel)
      : kernel_(kernel){};
  ~CustomKernelFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;

 private:
  std::vector<std::vector<float>> kernel_;
};
}  // namespace ng

#endif  // FILTERENGINE_CONVOLUTIONFILTERS_H
