#include "ui_view.h"
#include "view.h"

/**
 * @brief PhotoLaboratoryView::LabelHSLVColorChange
 * Function sets to label the HSL(V) color using sliders on view
 */
void PhotoLaboratoryView::LabelHSLVColorChange() {
  setStartBrightnessConstrast();
  QPalette p = ui->labelHSLVcolor->palette();
  if (ui->radioButtonHSL->isChecked()) {
    p.setColor(ui->labelHSLVcolor->backgroundRole(),
               QColor::fromHsl(ui->horizontalScrollBarHue->value(),
                               ui->horizontalScrollBarSaturation->value(),
                               ui->horizontalScrollBarValueLightness->value()));
  } else {
    p.setColor(ui->labelHSLVcolor->backgroundRole(),
               QColor::fromHsv(ui->horizontalScrollBarHue->value(),
                               ui->horizontalScrollBarSaturation->value(),
                               ui->horizontalScrollBarValueLightness->value()));
  }
  ui->labelHSLVcolor->setPalette(p);
}

/**
 * @brief PhotoLaboratoryView::RadioButtonControl
 * Function controles clickes on QRadioButton objects
 */
void PhotoLaboratoryView::RadioButtonControl() { LabelHSLVColorChange(); }

/**
 * @brief PhotoLaboratoryView::setToolTips
 * Function sets tooltips to all objects in view
 */
void PhotoLaboratoryView::setToolTips() {
  QString ctrl_command = "Ctrl";
#ifdef __APPLE__
  ctrl_command = "Command";
#endif
  ui->labelStartImage->setToolTip(
      "Current import image/Exporting image/Filter accepted image");
  ui->labelFilteredImage->setToolTip("Image for looking filters work");
  ui->pushButtonImport->setToolTip(
      "Import file with (*.png) (*.jpg) (*.jpeg) (*.bmp) extention.\nHotKey: " +
      ctrl_command + " + I");
  ui->pushButtonPeekStartImage->setToolTip("Show the original imported image.");
  ui->pushButtonAcceptFilters->setToolTip(
      "Accept current executed filter.\nHotKey: " + ctrl_command + " + S");
  ui->pushButtonResetFilters->setToolTip(
      "Reset all accepted filters.\nHotKey: " + ctrl_command + " + Z");
  ui->pushButtonGrayScaleFilter->setToolTip(
      "Convert image to gray scale.\nHotKey: SHIFT + 1");
  ui->pushButtonNegativeFilter->setToolTip(
      "Convert all image pixels color to negative colors.\nHotKey: SHIFT + N");
  ui->pushButtonToningFilter->setToolTip(
      "Convert image to gray scale and toning it with selected color.\nHotKey: "
      "SHIFT + T");
  ui->pushButtonEmbossFilter->setToolTip(
      "Making the image look three-dimensional.\nHotKey: SHIFT + E");
  ui->pushButtonSharpenFilter->setToolTip(
      "Gives you better image sharpness.\nHotKey: SHIFT + S");
  ui->pushButtonBoxBlurFilter->setToolTip(
      "Convert image to blur one.\nHotKey: SHIFT + B");
  ui->pushButtonGaussianBlurFilter->setToolTip(
      "Convert image to blur one.\nHotKey: SHIFT + 2");
  ui->pushButtonLaplacianFilter->setToolTip(
      "Highlight and enhance the edges of the image.\nHotKey: SHIFT + L");
  ui->pushButtonPrewittFilter->setToolTip(
      "Highlight and enhance the edges of the image.\nHotKey: SHIFT + P");
  ui->horizontalSliderBrightnessFilter->setToolTip("Changes image brightness.");
  ui->horizontalSliderContrastFilter->setToolTip("Changes image contrast.");
  ui->horizontalScrollBarHue->setToolTip("The basic color (hue).");
  ui->horizontalScrollBarSaturation->setToolTip(
      "The saturation of basic color (hue).");
  ui->horizontalScrollBarValueLightness->setToolTip("HSV value HSL lightness.");
  ui->spinBoxBrightness->setToolTip("Changes image brightness.");
  ui->spinBoxConstrast->setToolTip("Changes image contrast.");
  ui->spinBoxHue->setToolTip("The basic color (hue).");
  ui->spinBoxSaturation->setToolTip("The saturation of basic color (hue).");
  ui->spinBoxValueLightness->setToolTip("HSV value HSL lightness.");
  ui->labelHSLVcolor->setToolTip("HSL(V) model color preview.");
  ui->pushButtonConvertHSLV->setToolTip(
      "Convert current image from RGB to HSL(V), using hue, saturation, "
      "lightness(value)");
}

/**
 * @brief PhotoLaboratoryView::setImageToLabels
 * Function sets to image-view-labels current images, that was been calculated,
 * accepted, reseted
 */
void PhotoLaboratoryView::setImageToLabels() {
  if (!tmp_start_image_.isNull() && !image_filtered_.isNull()) {
    setImageToLabel(*ui->labelStartImage, tmp_start_image_);
    setImageToLabel(*ui->labelFilteredImage, image_filtered_);
  }
}

void PhotoLaboratoryView::setImageToLabel(QLabel &label, const QImage &image) {
  switch (image_size_type_) {
    case kScaled:
      label.setPixmap(QPixmap::fromImage(image).scaled(
          label.width(), label.height(), Qt::KeepAspectRatio,
          Qt::SmoothTransformation));
      break;
    case kStretched:
      label.setPixmap(
          QPixmap::fromImage(image).scaled(label.width(), label.height()));
      break;
    case kReal:
      label.setPixmap(QPixmap::fromImage(image));
      break;
  }
  label.setAlignment(Qt::AlignCenter);
}

/**
 * @brief PhotoLaboratoryView::setStartHSLV
 * Function resets sliders of HSL(V)
 */
void PhotoLaboratoryView::setStartHSLV() {
  ui->horizontalScrollBarHue->setValue(0);
  ui->horizontalScrollBarSaturation->setValue(0);
  ui->horizontalScrollBarValueLightness->setValue(0);
}

/**
 * @brief PhotoLaboratoryView::setStartBrightnessConstrast
 * Function resets sliders of contrast, brightness
 */
void PhotoLaboratoryView::setStartBrightnessConstrast() {
  ui->horizontalSliderBrightnessFilter->setValue(0);
  ui->horizontalSliderContrastFilter->setValue(0);
}

/**
 * @brief PhotoLaboratoryView::setShortCuts
 */
void PhotoLaboratoryView::setShortCuts() {
  short_cut_import_ = new QShortcut(Qt::CTRL | Qt::Key_I, this);
  short_cut_export_ = new QShortcut(Qt::CTRL | Qt::Key_E, this);
  short_cut_reset_ = new QShortcut(Qt::CTRL | Qt::Key_Z, this);
  short_cut_accept_ = new QShortcut(Qt::CTRL | Qt::Key_S, this);

  short_cut_gray_ = new QShortcut(Qt::SHIFT | Qt::Key_1, this);
  short_cut_negative_ = new QShortcut(Qt::SHIFT | Qt::Key_N, this);
  short_cut_toning_ = new QShortcut(Qt::SHIFT | Qt::Key_T, this);
  short_cut_emboss_ = new QShortcut(Qt::SHIFT | Qt::Key_E, this);
  short_cut_sharpen_ = new QShortcut(Qt::SHIFT | Qt::Key_S, this);
  short_cut_boxblur_ = new QShortcut(Qt::SHIFT | Qt::Key_B, this);
  short_cut_gaussianblur_ = new QShortcut(Qt::SHIFT | Qt::Key_2, this);
  short_cut_laplacian_ = new QShortcut(Qt::SHIFT | Qt::Key_L, this);
  short_cut_prewitt_ = new QShortcut(Qt::SHIFT | Qt::Key_P, this);
  short_cut_custom_ = new QShortcut(Qt::SHIFT | Qt::Key_C, this);
  short_cut_hslv = new QShortcut(Qt::SHIFT | Qt::Key_0, this);

  ConnectShortKeys();
}

void PhotoLaboratoryView::LockUi() {
  ui->menuFilters->setDisabled(true);
  ui->menuSize->setDisabled(true);
  if (!image_is_imported_) ui->actionEdit->setDisabled(true);
  ui->actionExport->setDisabled(true);
}

void PhotoLaboratoryView::UnlockUi() {
  ui->menuFilters->setDisabled(false);
  ui->menuSize->setDisabled(false);
  ui->actionEdit->setDisabled(false);
  ui->actionExport->setDisabled(false);
}

void PhotoLaboratoryView::Reset() {
  controller_.setBasicImage(image_start_);
  tmp_start_image_ = image_filtered_ = image_start_;
  ui->horizontalSliderBrightnessFilter->setValue(0);
  ui->horizontalSliderContrastFilter->setValue(0);
  ui->horizontalScrollBarHue->setValue(0);
  ui->horizontalScrollBarSaturation->setValue(255);
  ui->horizontalScrollBarValueLightness->setValue(130);
  setImageToLabel(*ui->labelStartImage, image_start_);
  setImageToLabel(*ui->labelFilteredImage, image_start_);
}

void PhotoLaboratoryView::Accept() {
  controller_.setBasicImage(image_filtered_);
  tmp_start_image_ = image_filtered_;
  ui->horizontalSliderBrightnessFilter->setValue(0);
  ui->horizontalSliderContrastFilter->setValue(0);
  ui->horizontalScrollBarHue->setValue(0);
  ui->horizontalScrollBarSaturation->setValue(255);
  ui->horizontalScrollBarValueLightness->setValue(130);
  setImageToLabel(*ui->labelStartImage, tmp_start_image_);
  setImageToLabel(*ui->labelFilteredImage, tmp_start_image_);
}

void PhotoLaboratoryView::setTransparency() {
  QAction *action = (QAction *)sender();
  QString transparency = action->text();
  transparency.chop(1);
  setWindowOpacity(transparency.toFloat() / 100);
}

void PhotoLaboratoryView::MakeImages() {
  if (!image_is_imported_) {
    return;
  }

  static int i = 0;
  QString message =
      "You find EarterEgg of PhotoLaboratory!\n"
      "You can choose HSL or HSV color model\n"
      "using radio-buttons!\n"
      "Also, you should wait some time <3";
  if (i != 0) message = "Again? Really? OK...";
  QMessageBox::information(this, "PhotoLaboratory", message);

  QString path;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef _WIN64
  path = QDir::homePath() + "/Desktop/";
#else
  return;
#endif
#elif __APPLE__
  path = QDir::homePath() + "/goinfre/";
#else
  return;
#endif
  QDir dir(path);
  QString directory_name = "PhotoLaboratory";
  QString hslv;
  if (ui->radioButtonHSL->isChecked()) {
    hslv = "HSL_";
    directory_name += "HSL_No." + QString::number(i++);
  } else {
    hslv = "HSV_";
    directory_name += "HSV_No." + QString::number(i++);
  }
  dir.mkdir(directory_name);
  QImage saved_image = image_start_;
  image_start_ = tmp_start_image_;
  controller_.setBasicImage(image_start_);

  QString full_path = path + directory_name;

  for (int hue = 0; hue < 360; hue += 3) {
    ui->horizontalScrollBarHue->setValue(hue);
    ui->pushButtonConvertHSLV->click();
    Accept();
    tmp_start_image_.save(full_path + "/" + hslv + QString::number(hue) +
                          "_255_130.jpg");
    Reset();
  }
  image_start_ = saved_image;
  Reset();

  QMessageBox::information(
      this, "PhotoLaboratory",
      "Process finished successfully!\nSaved path: " + full_path);
}
