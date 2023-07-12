#ifndef FILTERENGINE_CONVOLUTIONFILTERMANAGER_H
#define FILTERENGINE_CONVOLUTIONFILTERMANAGER_H

#include "../Model/FilterHelper/Filters/ConvolutionFilters/convolutionfilters.h"

namespace ng {
/**
 * =============== ConvolutionFilterManager class ===============
 * Main information:
 * Class is a manager of classes that was inherited from
 * ng::BaseConvolutionFilter class ng::EmbossFilter, ng::SharpenFilter,
 * ng::BoxBlueFilter, ng::GaussianBlurFilter, ng::LaplacianFilter,
 * ng::PrewittFilter, ng::CustomKernelFilter
 */
class ConvolutionFilterManager {
 public:
  ConvolutionFilterManager() = default;
  ~ConvolutionFilterManager() noexcept { delete filter_; }

  void Execute(const QImage &start, QImage &filtered) {
    filter_->Execute(start, filtered);
  }

  template <typename Filter, typename... Constract>
  void setFilter(Constract &&...constract_arguments) {
    delete filter_;
    filter_ = new Filter(constract_arguments...);
  }

 private:
  BaseConvolutionFilter *filter_ = nullptr;
};
}  // namespace ng

#endif  // FILTERENGINE_CONVOLUTIONFILTERMANAGER_H
