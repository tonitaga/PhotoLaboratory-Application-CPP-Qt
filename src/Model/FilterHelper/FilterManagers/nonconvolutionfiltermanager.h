#ifndef FILTERENGINE_NONCONVOLUTIONFILTERMANAGER_H
#define FILTERENGINE_NONCONVOLUTIONFILTERMANAGER_H

#include "../Model/FilterHelper/Filters/NonConvolutionFilters/nonconvolutionfilters.h"

namespace ng {
/**
 * =============== NonConvolutionFilterManager class ===============
 * Main information:
 * Class is a manager of classes that was inherited from
 * ng::BaseNonConvolutionFilter class ng::GrayScaleFilter,
 * ng::NegativeFilter, ng::ToningFilter
 */
class NonConvolutionFilterManager {
 public:
  NonConvolutionFilterManager() = default;
  ~NonConvolutionFilterManager() noexcept { delete filter_; }

  void Execute(const QImage &start, QImage &filtered) {
    filter_->Execute(start, filtered);
  }

  template <typename Filter, typename... Constract>
  void setFilter(Constract &&...constract_arguments) {
    delete filter_;
    filter_ = new Filter(constract_arguments...);
  }

 private:
  BaseNonConvolutionFilter *filter_ = nullptr;
};
}  // namespace ng

#endif  // FILTERENGINE_NONCONVOLUTIONFILTERMANAGER_H
