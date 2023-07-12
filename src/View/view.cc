#include "view.h"

#include <QColorDialog>
#include <QDebug>
#include <QDesktopServices>
#include <QFileDialog>

#include "ui_view.h"

PhotoLaboratoryView::PhotoLaboratoryView(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::PhotoLaboratoryView),
      import_export_filter_("(*.png);; (*.bmp);; (*.jpg);; (*.jpeg)") {
  ui->setupUi(this);

  setWindowTitle("PhotoLaboratory");
  setWindowIcon(QIcon(":/PhotoLaboratoryIcon.ico"));
  ui->stackedWidget->setCurrentIndex(MAIN);
  LockUi();
  Connect();
  setToolTips();
  setShortCuts();
}

PhotoLaboratoryView::~PhotoLaboratoryView() { delete ui; }

/**
 * @brief PhotoLaboratoryView::ImportImage
 * The main function (private slot) that importing image to view
 */
void PhotoLaboratoryView::ImportImage() {
  QString path = QFileDialog::getOpenFileName(
      this, QString("Import Image"), QDir::homePath(), import_export_filter_);
  if (path.isEmpty()) {
    return;
  }
  if (!QImage(path).isNull()) {
    image_start_ = QImage(path);
    tmp_start_image_ = image_start_;
    image_filtered_ = image_start_;
    image_is_imported_ = true;
    controller_.setBasicImage(image_start_);
    ui->stackedWidget->setCurrentIndex(EDIT);
    setImageToLabels();
    LabelHSLVColorChange();
    UnlockUi();
  } else {
    QMessageBox::information(this, windowTitle(), "Error image!");
  }
}

/**
 * @brief PhotoLaboratoryView::ExportImage
 * The main function (private slot) that exporting image from view
 */
void PhotoLaboratoryView::ExportImage() {
  if (image_is_imported_) {
    QString path = QFileDialog::getSaveFileName(
        this, QString("Export Image"), QDir::homePath(), import_export_filter_);
    if (path.isEmpty()) {
      return;
    }
    tmp_start_image_.save(path);
  }
}

/**
 * @brief PhotoLaboratoryView::ExecuteFilters
 * The main PhotoLaboratory function of using filter controller to execute
 * filters
 * @param Filter one of the most filters in namespace ng
 * @param constract_arguments constraction arguments of type Filter
 */
template <typename Filter, typename... Constract>
void PhotoLaboratoryView::ExecuteFilters(Constract &&...constract_arguments) {
  if (image_is_imported_) {
    controller_.setFilter<Filter>(constract_arguments...);
    controller_.ExecuteFilter();
    image_filtered_ = controller_.getFilteredImage();
    setImageToLabels();
  }
}

/**
 * @brief PhotoLaboratoryView::CustomKernel
 * The function that exists the new window with Matrix on it
 */
void PhotoLaboratoryView::CustomKernel() {
  if (!image_is_imported_) {
    return;
  }
  kernel_view_.setModal(true);
  kernel_view_.exec();
  if (kernel_view_.getKernel().empty()) {
    return;
  }
  ExecuteFilters<ng::CustomKernelFilter>(kernel_view_.getKernel());
}

/**
 * @brief PhotoLaboratoryView::Connect
 * The main function of connecting objects signals with slots(in most cases with
 * lambdas)
 */
void PhotoLaboratoryView::Connect() {
  ConnectActions();
  ConnectButtons();
  ConnectSliders();
  ConnectSpinBoxes();
  ConnectResetAcceptPeek();
}

/**
 * @brief PhotoLaboratoryView::ConnectActions
 * The function that connection all QAction objects in view
 */
void PhotoLaboratoryView::ConnectActions() {
  connect(ui->actionImport, &QAction::triggered, this,
          &PhotoLaboratoryView::ImportImage);
  connect(ui->actionExport, &QAction::triggered, this,
          &PhotoLaboratoryView::ExportImage);
  connect(ui->action100, &QAction::triggered, this,
          &PhotoLaboratoryView::setTransparency);
  connect(ui->action95, &QAction::triggered, this,
          &PhotoLaboratoryView::setTransparency);
  connect(ui->action90, &QAction::triggered, this,
          &PhotoLaboratoryView::setTransparency);
  connect(ui->action80, &QAction::triggered, this,
          &PhotoLaboratoryView::setTransparency);
  connect(ui->actionMain, &QAction::triggered, this, [=]() {
    ui->stackedWidget->setCurrentIndex(MAIN);
    LockUi();
  });
  connect(ui->actionGrayScale, &QAction::triggered, this,
          [=]() { ExecuteFilters<ng::GrayScaleFilter>(); });
  connect(ui->actionNegative, &QAction::triggered, this,
          [=]() { ExecuteFilters<ng::NegativeFilter>(); });
  connect(ui->actionToning, &QAction::triggered, this, [=]() {
    if (!image_is_imported_) {
      return;
    }
    QColor toning_color = QColorDialog::getColor(Qt::green, this);
    if (toning_color.isValid()) {
      ExecuteFilters<ng::ToningFilter>(toning_color);
    }
  });
  connect(ui->actionEmboss, &QAction::triggered, this,
          [=]() { ExecuteFilters<ng::EmbossFilter>(); });
  connect(ui->actionSharpen, &QAction::triggered, this,
          [=]() { ExecuteFilters<ng::SharpenFilter>(); });
  connect(ui->actionBoxBlur, &QAction::triggered, this,
          [=]() { ExecuteFilters<ng::BoxBlurFilter>(); });
  connect(ui->actionGaussian, &QAction::triggered, this,
          [=]() { ExecuteFilters<ng::GaussianBlurFilter>(); });
  connect(ui->actionLaplacian, &QAction::triggered, this,
          [=]() { ExecuteFilters<ng::LaplacianFilter>(); });
  connect(ui->actionPrewitt, &QAction::triggered, this,
          [=]() { ExecuteFilters<ng::PrewittFilter>(); });
  connect(ui->actionCustom_Kernel, &QAction::triggered, this,
          &PhotoLaboratoryView::CustomKernel);
  connect(ui->actionReal, &QAction::triggered, this, [=]() {
    image_size_type_ = kReal;
    setImageToLabels();
  });
  connect(ui->actionScaled, &QAction::triggered, this, [=]() {
    image_size_type_ = kScaled;
    setImageToLabels();
  });
  connect(ui->actionStretched, &QAction::triggered, this, [=]() {
    image_size_type_ = kStretched;
    setImageToLabels();
  });
  connect(ui->actionEdit, &QAction::triggered, this, [=]() {
    ui->stackedWidget->setCurrentIndex(EDIT);
    UnlockUi();
  });
  connect(ui->actionAbout, &QAction::triggered, this, [=]() {
    QDesktopServices::openUrl(
        QUrl("https://github.com/tonitaga/PhotoLab_v1.0"));
  });
}

/**
 * @brief PhotoLaboratoryView::ConnectShortKeys
 * The function that connect all QShortCut objects (mostly use lambda functions
 * in slot place)
 */
void PhotoLaboratoryView::ConnectShortKeys() {
  connect(short_cut_import_, &QShortcut::activated, this,
          &PhotoLaboratoryView::ImportImage);
  connect(short_cut_export_, &QShortcut::activated, this,
          &PhotoLaboratoryView::ExportImage);
  connect(short_cut_gray_, &QShortcut::activated, this,
          [=]() { ExecuteFilters<ng::GrayScaleFilter>(); });
  connect(short_cut_negative_, &QShortcut::activated, this,
          [=]() { ExecuteFilters<ng::NegativeFilter>(); });
  connect(short_cut_toning_, &QShortcut::activated, this, [=]() {
    if (!image_is_imported_) {
      return;
    }
    QColor toning_color = QColorDialog::getColor(Qt::green, this);
    if (toning_color.isValid()) {
      ExecuteFilters<ng::ToningFilter>(toning_color);
    }
  });
  connect(short_cut_emboss_, &QShortcut::activated, this,
          [=]() { ExecuteFilters<ng::EmbossFilter>(); });
  connect(short_cut_sharpen_, &QShortcut::activated, this,
          [=]() { ExecuteFilters<ng::SharpenFilter>(); });
  connect(short_cut_boxblur_, &QShortcut::activated, this,
          [=]() { ExecuteFilters<ng::BoxBlurFilter>(); });
  connect(short_cut_gaussianblur_, &QShortcut::activated, this,
          [=]() { ExecuteFilters<ng::GaussianBlurFilter>(); });
  connect(short_cut_laplacian_, &QShortcut::activated, this,
          [=]() { ExecuteFilters<ng::LaplacianFilter>(); });
  connect(short_cut_prewitt_, &QShortcut::activated, this,
          [=]() { ExecuteFilters<ng::PrewittFilter>(); });
  connect(short_cut_custom_, &QShortcut::activated, this,
          &PhotoLaboratoryView::CustomKernel);
  connect(short_cut_reset_, &QShortcut::activated, this, [=]() { Reset(); });
  connect(short_cut_accept_, &QShortcut::activated, this, [=]() { Accept(); });
  connect(short_cut_hslv, &QShortcut::activated, this,
          &PhotoLaboratoryView::MakeImages);
}

/**
 * @brief PhotoLaboratoryView::ConnectSpinBoxes
 * The function that connect all QSpinBox objects in view (mostly use lambda
 * functions in slot place)
 */
void PhotoLaboratoryView::ConnectSpinBoxes() {
  connect(ui->spinBoxHue, &QSpinBox::valueChanged, this, [=]() {
    ui->horizontalScrollBarHue->setValue(ui->spinBoxHue->value());
  });
  connect(ui->spinBoxSaturation, &QSpinBox::valueChanged, this, [=]() {
    ui->horizontalScrollBarSaturation->setValue(ui->spinBoxSaturation->value());
  });
  connect(ui->spinBoxValueLightness, &QSpinBox::valueChanged, this, [=]() {
    ui->horizontalScrollBarValueLightness->setValue(
        ui->spinBoxValueLightness->value());
  });
  connect(ui->spinBoxBrightness, &QSpinBox::valueChanged, this, [=]() {
    ui->horizontalSliderBrightnessFilter->setValue(
        ui->spinBoxBrightness->value());
  });
  connect(ui->spinBoxConstrast, &QSpinBox::valueChanged, this, [=]() {
    ui->horizontalSliderContrastFilter->setValue(ui->spinBoxConstrast->value());
  });
}

/**
 * @brief PhotoLaboratoryView::ConnectButtons
 * The function that connect all QPushButton objects in view (mostly use lambda
 * functions in slot place)
 */
void PhotoLaboratoryView::ConnectButtons() {
  connect(ui->pushButtonImport, &QPushButton::clicked, this,
          &PhotoLaboratoryView::ImportImage);
  connect(ui->pushButtonGrayScaleFilter, &QPushButton::clicked, this,
          [=]() { ExecuteFilters<ng::GrayScaleFilter>(); });
  connect(ui->pushButtonNegativeFilter, &QPushButton::clicked, this,
          [=]() { ExecuteFilters<ng::NegativeFilter>(); });

  connect(ui->pushButtonToningFilter, &QPushButton::clicked, this, [=]() {
    if (!image_is_imported_) {
      return;
    }
    QColor toning_color = QColorDialog::getColor(Qt::green, this);
    if (toning_color.isValid()) {
      ExecuteFilters<ng::ToningFilter>(toning_color);
    }
  });
  connect(ui->pushButtonEmbossFilter, &QPushButton::clicked, this,
          [=]() { ExecuteFilters<ng::EmbossFilter>(); });
  connect(ui->pushButtonSharpenFilter, &QPushButton::clicked, this,
          [=]() { ExecuteFilters<ng::SharpenFilter>(); });
  connect(ui->pushButtonBoxBlurFilter, &QPushButton::clicked, this,
          [=]() { ExecuteFilters<ng::BoxBlurFilter>(); });
  connect(ui->pushButtonGaussianBlurFilter, &QPushButton::clicked, this,
          [=]() { ExecuteFilters<ng::GaussianBlurFilter>(); });
  connect(ui->pushButtonLaplacianFilter, &QPushButton::clicked, this,
          [=]() { ExecuteFilters<ng::LaplacianFilter>(); });
  connect(ui->pushButtonPrewittFilter, &QPushButton::clicked, this,
          [=]() { ExecuteFilters<ng::PrewittFilter>(); });
  connect(ui->pushButtonConvertHSLV, &QPushButton::clicked, this, [=]() {
    QColor color = ui->labelHSLVcolor->palette().color(
        ui->labelHSLVcolor->backgroundRole());
    if (ui->radioButtonHSL->isChecked()) {
      ExecuteFilters<ng::HSLColorFilter>(color.toHsl());
    } else {
      ExecuteFilters<ng::HSVColorFilter>(color.toHsv());
    }
  });
  connect(ui->radioButtonHSL, &QPushButton::clicked, this,
          &PhotoLaboratoryView::RadioButtonControl);
  connect(ui->radioButtonHSV, &QPushButton::clicked, this,
          &PhotoLaboratoryView::RadioButtonControl);
}

/**
 * @brief PhotoLaboratoryView::ConnectSliders
 * The function that connect all QSlider objects in view (mostly use lambda
 * functions in slot place)
 */
void PhotoLaboratoryView::ConnectSliders() {
  connect(ui->horizontalScrollBarHue, &QSlider::valueChanged, this, [=]() {
    LabelHSLVColorChange();
    ui->spinBoxHue->setValue(ui->horizontalScrollBarHue->value());
  });
  connect(ui->horizontalScrollBarSaturation, &QSlider::valueChanged, this,
          [=]() {
            LabelHSLVColorChange();
            ui->spinBoxSaturation->setValue(
                ui->horizontalScrollBarSaturation->value());
          });
  connect(ui->horizontalScrollBarValueLightness, &QSlider::valueChanged, this,
          [=]() {
            LabelHSLVColorChange();
            ui->spinBoxValueLightness->setValue(
                ui->horizontalScrollBarValueLightness->value());
          });
  connect(ui->horizontalSliderContrastFilter, &QSlider::valueChanged, this,
          [=]() {
            setStartHSLV();
            ui->horizontalSliderBrightnessFilter->setValue(0);
            ui->spinBoxBrightness->setValue(0);
            if (ui->horizontalSliderContrastFilter->value() % 10 == 0) {
              ExecuteFilters<ng::ContrastFilter>(
                  ui->horizontalSliderContrastFilter->value());
            }
            ui->spinBoxConstrast->setValue(
                ui->horizontalSliderContrastFilter->value());
          });
  connect(ui->horizontalSliderBrightnessFilter, &QSlider::valueChanged, this,
          [=]() {
            setStartHSLV();
            ui->horizontalSliderContrastFilter->setValue(0);
            ui->spinBoxConstrast->setValue(0);
            if (ui->horizontalSliderBrightnessFilter->value() % 2 == 0) {
              ExecuteFilters<ng::BrightnessFilter>(
                  ui->horizontalSliderBrightnessFilter->value());
            }
            ui->spinBoxBrightness->setValue(
                ui->horizontalSliderBrightnessFilter->value());
          });
}

/**
 * @brief PhotoLaboratoryView::ConnectResetAcceptPeek
 * Connect settings buttons of view (mostly use lambda functions in slot place)
 */
void PhotoLaboratoryView::ConnectResetAcceptPeek() {
  connect(ui->pushButtonAcceptFilters, &QPushButton::clicked, this,
          [=]() { Accept(); });
  connect(ui->pushButtonResetFilters, &QPushButton::clicked, this,
          [=]() { Reset(); });
  connect(ui->pushButtonPeekStartImage, &QPushButton::pressed, this,
          [=]() { setImageToLabel(*ui->labelStartImage, image_start_); });
  connect(ui->pushButtonPeekStartImage, &QPushButton::released, this,
          [=]() { setImageToLabel(*ui->labelStartImage, tmp_start_image_); });
}

void PhotoLaboratoryView::resizeEvent(QResizeEvent *) { setImageToLabels(); }
