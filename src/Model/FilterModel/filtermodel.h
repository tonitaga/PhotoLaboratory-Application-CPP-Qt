#ifndef FILTERENGINE_FILTERMODEL_H
#define FILTERENGINE_FILTERMODEL_H

#include "../FilterHelper/filterhelper.h"
#include "../Model/FilterHelper/filtertypetraits.h"

namespace ng {
/**
 * =============== FilterModel class ===============
 * Main information:
 * FilterModel is the class that controls all three filter managers
 * Can be constract from basic image
 * Can be initialized by new image using setBasicImage()
 * Have template function that controls setting filters to managers using
 * metafunctions Can return filtered image after filter been executed
 */
class FilterModel {
 public:
  FilterModel() = default;
  explicit FilterModel(const QImage &image) { setBasicImage(image); }
  ~FilterModel() = default;

  void ExecuteFilter() {
    switch (current_manager_) {
      case kConvolutionFilterManager:
        c_manager_.Execute(image_start_, image_filtered_);
        break;
      case kNonConvolutionFilterManager:
        n_manager_.Execute(image_start_, image_filtered_);
        break;
      case kColorCorrectionFilterManager:
        cc_manager_.Execute(image_start_, image_filtered_);
        break;
    }
  }

  void setBasicImage(const QImage &image) {
    image_start_ = image;
    image_filtered_ = image;
  }

  template <typename Filter, typename... Constract>
  void setFilter(Constract &&...constract_arguments) {
    if constexpr (is_convolution_v<Filter>) {
      c_manager_.setFilter<Filter>(constract_arguments...);
      current_manager_ = kConvolutionFilterManager;
    } else if constexpr (is_non_convolution_v<Filter>) {
      n_manager_.setFilter<Filter>(constract_arguments...);
      current_manager_ = kNonConvolutionFilterManager;
    } else if constexpr (is_color_correction_v<Filter>) {
      cc_manager_.setFilter<Filter>(constract_arguments...);
      current_manager_ = kColorCorrectionFilterManager;
    }
  }

  [[nodiscard]] QImage getFilteredImage() const { return image_filtered_; }

 private:
  ConvolutionFilterManager c_manager_;
  NonConvolutionFilterManager n_manager_;
  ColorCorrectionFilterManager cc_manager_;

  enum FilterManagers {
    kConvolutionFilterManager,
    kNonConvolutionFilterManager,
    kColorCorrectionFilterManager
  };

  FilterManagers current_manager_;

  QImage image_start_, image_filtered_;
};
}  // namespace ng
#endif  // FILTERENGINE_FILTERMODEL_H
