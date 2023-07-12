#ifndef FILTERENGINE_FILTERCONTROLLER_H
#define FILTERENGINE_FILTERCONTROLLER_H

#include "../Model/FilterModel/filtermodel.h"

namespace ng {
/**
 * =============== FilterController class ===============
 * Main information:
 * FilterController is the class that controls the ng::FilterModel class
 */
class FilterController {
 public:
  FilterController() = default;
  ~FilterController() = default;

  void ExecuteFilter() { model_.ExecuteFilter(); }

  void setBasicImage(const QImage &image) { model_.setBasicImage(image); }

  template <typename Filter, typename... Constract>
  void setFilter(Constract &&...constract_arguments) {
    model_.setFilter<Filter>(constract_arguments...);
  }

  [[nodiscard]] QImage getFilteredImage() const {
    return model_.getFilteredImage();
  }

 private:
  FilterModel model_;
};
}  // namespace ng

#endif  // FILTERENGINE_FILTERCONTROLLER_H
