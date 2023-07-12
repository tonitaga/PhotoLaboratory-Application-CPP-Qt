#ifndef PHOTOLABORATORYVIEW_H
#define PHOTOLABORATORYVIEW_H

#include <QDir>
#include <QMainWindow>
#include <QMessageBox>
#include <QShortcut>

#include "../Controller/filtercontroller.h"
#include "customkernelview.h"

#define MAIN 0
#define EDIT 1

class QLabel;

QT_BEGIN_NAMESPACE
namespace Ui {
class PhotoLaboratoryView;
}
QT_END_NAMESPACE

class PhotoLaboratoryView : public QMainWindow {
  Q_OBJECT

 public:
  PhotoLaboratoryView(QWidget *parent = nullptr);
  ~PhotoLaboratoryView();

 private slots:
  void ImportImage();
  void ExportImage();
  void setTransparency();
  void CustomKernel();
  void LabelHSLVColorChange();
  void RadioButtonControl();
  void MakeImages();

 protected:
  void resizeEvent(QResizeEvent *) override;

 private:
  Ui::PhotoLaboratoryView *ui;

  void Connect();
  void ConnectActions();
  void ConnectShortKeys();
  void ConnectSpinBoxes();
  void ConnectButtons();
  void ConnectSliders();
  void ConnectResetAcceptPeek();
  void setToolTips();
  void setShortCuts();
  void setImageToLabels();
  void setImageToLabel(QLabel &label, const QImage &image);
  void setStartHSLV();
  void setStartBrightnessConstrast();
  void LockUi();
  void UnlockUi();
  void Reset();
  void Accept();

  template <typename Filter, typename... Constract>
  void ExecuteFilters(Constract &&...constract_arguments);

  CustomKernelView kernel_view_;
  ng::FilterController controller_;

  const QString import_export_filter_;
  QImage image_start_, image_filtered_, tmp_start_image_;

  bool image_is_imported_ = false;

  enum ImageSizeType { kReal, kScaled, kStretched };

  ImageSizeType image_size_type_ = kScaled;

  QShortcut *short_cut_import_;
  QShortcut *short_cut_export_;
  QShortcut *short_cut_accept_;
  QShortcut *short_cut_reset_;
  QShortcut *short_cut_gray_;
  QShortcut *short_cut_negative_;
  QShortcut *short_cut_toning_;
  QShortcut *short_cut_emboss_;
  QShortcut *short_cut_sharpen_;
  QShortcut *short_cut_boxblur_;
  QShortcut *short_cut_gaussianblur_;
  QShortcut *short_cut_laplacian_;
  QShortcut *short_cut_prewitt_;
  QShortcut *short_cut_custom_;
  QShortcut *short_cut_hslv;
};

#endif  // PHOTOLABORATORYVIEW_H
