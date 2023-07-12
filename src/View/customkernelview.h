#ifndef CUSTOMKERNELVIEW_H
#define CUSTOMKERNELVIEW_H

#include <QDialog>

namespace Ui {
class CustomKernelView;
}

class CustomKernelView : public QDialog {
  Q_OBJECT

 public:
  explicit CustomKernelView(QWidget *parent = nullptr);
  ~CustomKernelView();

  std::vector<std::vector<float>> getKernel() const;

 signals:
  void CustomKernelSignal();

 private slots:
  void on_doubleSpinBoxRows_valueChanged(double arg1);
  void on_doubleSpinCols_valueChanged(double arg1);
  void on_pushButtonOK_clicked();
  void on_pushButtonReset_clicked();

 protected:
  void resizeEvent(QResizeEvent *) override;
  void closeEvent(QCloseEvent *) override;

 private:
  Ui::CustomKernelView *ui;

  std::vector<std::vector<float>> kernel_;

  bool ok_button_clicked_ = false;

  void UpdateKernelMatrix(int row, int col);
  void setToolTips();
};

#endif  // CUSTOMKERNELVIEW_H
