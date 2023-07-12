#ifndef PHOTOLAB_GITHUB_FILTERTYPETRAITS_H
#define PHOTOLAB_GITHUB_FILTERTYPETRAITS_H

#include "filterhelper.h"

namespace ng {
/**
 * =============== is_convolution class ===============
 * Main information:
 * Structure defines that the passed pattern is an inheritor of
 * ng::BaseConvolutionFilter
 */
template <typename T>
struct is_convolution {
  static constexpr bool value = false;
};

/**
 * =============== is_convolution class ===============
 * Main information:
 * Structure defines that the passed pattern is an inheritor of
 * ng::BaseNonConvolutionFilter
 */
template <typename T>
struct is_non_convolution {
  static constexpr bool value = false;
};

/**
 * =============== is_color_correction class ===============
 * Main information:
 * Structure defines that the passed pattern is an inheritor of
 * ng::BaseColorCorrectionFilter
 */
template <typename T>
struct is_color_correction {
  static constexpr bool value = false;
};

template <typename T>
constexpr bool is_convolution_v = is_convolution<T>::value;

template <typename T>
constexpr bool is_non_convolution_v = is_non_convolution<T>::value;

template <typename T>
constexpr bool is_color_correction_v = is_color_correction<T>::value;

/*=============================================================*/

template <>
struct is_convolution<EmbossFilter> {
  static constexpr bool value = true;
};

template <>
struct is_convolution<SharpenFilter> {
  static constexpr bool value = true;
};

template <>
struct is_convolution<BoxBlurFilter> {
  static constexpr bool value = true;
};

template <>
struct is_convolution<GaussianBlurFilter> {
  static constexpr bool value = true;
};

template <>
struct is_convolution<LaplacianFilter> {
  static constexpr bool value = true;
};

template <>
struct is_convolution<PrewittFilter> {
  static constexpr bool value = true;
};

template <>
struct is_convolution<CustomKernelFilter> {
  static constexpr bool value = true;
};

template <>
struct is_non_convolution<GrayScaleFilter> {
  static constexpr bool value = true;
};

template <>
struct is_non_convolution<NegativeFilter> {
  static constexpr bool value = true;
};

template <>
struct is_non_convolution<ToningFilter> {
  static constexpr bool value = true;
};

template <>
struct is_color_correction<BrightnessFilter> {
  static constexpr bool value = true;
};

template <>
struct is_color_correction<ContrastFilter> {
  static constexpr bool value = true;
};

template <>
struct is_color_correction<HSLColorFilter> {
  static constexpr bool value = true;
};

template <>
struct is_color_correction<HSVColorFilter> {
  static constexpr bool value = true;
};
}  // namespace ng

#endif  // PHOTOLAB_GITHUB_FILTERTYPETRAITS_H
