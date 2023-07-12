#ifndef PHOTOLAB_V1_0_COLORCORRECTIONFILTERMANAGER_H
#define PHOTOLAB_V1_0_COLORCORRECTIONFILTERMANAGER_H

#include "../Model/FilterHelper/Filters/ColorCorrectionFilters/colorcorrectionfilters.h"

namespace ng {
/**
 * =============== ColorCorrectionFilterManager class ===============
 * Main information:
 * Class is a manager of classes that was inherited from
 * ng::BaseColorCorrectionFilter class ng::BrightnessFilter,
 * ng::ContrastFilter, ng::HSVColorFilter, ng::HSLColorFilter
 */
class ColorCorrectionFilterManager {
 public:
  ColorCorrectionFilterManager() = default;
  ~ColorCorrectionFilterManager() noexcept { delete filter_; }

  void Execute(const QImage &start, QImage &filtered) {
    filter_->Execute(start, filtered);
  }

  template <typename Filter, typename... Constract>
  void setFilter(Constract &&...constract_arguments) {
    delete filter_;
    filter_ = new Filter(constract_arguments...);
  }

 private:
  BaseColorCorrectionFilter *filter_ = nullptr;
};
}  // namespace ng

#endif  // PHOTOLAB_V1_0_COLORCORRECTIONFILTERMANAGER_H
