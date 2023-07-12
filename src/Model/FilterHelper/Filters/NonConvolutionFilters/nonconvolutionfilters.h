#ifndef FILTERENGINE_NONCONVOLUTIONFILTERS_H
#define FILTERENGINE_NONCONVOLUTIONFILTERS_H

#include "../../basefilter.h"

namespace ng {
/**
 * =============== GrayScaleFilter class ===============
 * Main information:
 * Class is an inheritor of BaseNonConvolutionFilter class
 */
class GrayScaleFilter : public BaseNonConvolutionFilter {
 public:
  GrayScaleFilter() = default;
  ~GrayScaleFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;
};

/**
 * =============== NegativeFilter class ===============
 * Main information:
 * Class is an inheritor of BaseNonConvolutionFilter class
 */
class NegativeFilter : public BaseNonConvolutionFilter {
 public:
  NegativeFilter() = default;
  ~NegativeFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;
};

/**
 * =============== ToningFilter class ===============
 * Main information:
 * Class is an inheritor of BaseNonConvolutionFilter class
 */
class ToningFilter : public BaseNonConvolutionFilter {
 public:
  explicit ToningFilter(int = int()){};
  explicit ToningFilter(const QColor &color) : toning_color_(color) {}
  ~ToningFilter() override = default;

  void Execute(const QImage &start, QImage &filtered) override;

 private:
  QColor toning_color_;
};
}  // namespace ng

#endif  // FILTERENGINE_NONCONVOLUTIONFILTERS_H
