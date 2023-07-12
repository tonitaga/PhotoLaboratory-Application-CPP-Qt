#include "customkernelview.h"

#include "ui_customkernelview.h"

CustomKernelView::CustomKernelView(QWidget *parent)
    : QDialog(parent), ui(new Ui::CustomKernelView) {
  ui->setupUi(this);
  setToolTips();
}

CustomKernelView::~CustomKernelView() { delete ui; }

std::vector<std::vector<float> > CustomKernelView::getKernel() const {
  return kernel_;
}

/**
 * @brief CustomKernelView::UpdateKernelMatrix
 * Dynamically update count of rows and cols in matrix
 */
void CustomKernelView::UpdateKernelMatrix(int row, int col) {
  ui->tableWidget->clear();
  ui->tableWidget->setRowCount(row);
  ui->tableWidget->setColumnCount(col);

  for (int i = 0; i != row; ++i) {
    for (int j = 0; j != col; ++j) {
      QDoubleSpinBox *spin_box = new QDoubleSpinBox(this);
      spin_box->setStyleSheet(
          "QDoubleSpinBox {\n"
          "background-color: #18122B;\n"
          "color: white;\n}\n"
          "\nQDoubleSpinBox::hover {\n"
          "background-color: #393053;\n"
          "}");
      spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
      spin_box->setAlignment(Qt::AlignHCenter);
      spin_box->setDecimals(0);
      spin_box->setValue(0);
      spin_box->setRange(-50, 50);
      ui->tableWidget->setColumnWidth(j, ui->tableWidget->width() / col);
      ui->tableWidget->setCellWidget(i, j, spin_box);
    }
    ui->tableWidget->setRowHeight(i, ui->tableWidget->height() / row);
  }
}

void CustomKernelView::on_pushButtonOK_clicked() {
  kernel_.clear();
  kernel_.resize(ui->doubleSpinBoxRows->value());

  for (int i = 0; i != ui->doubleSpinBoxRows->value(); ++i) {
    for (int j = 0; j != ui->doubleSpinCols->value(); ++j) {
      kernel_[i].push_back(
          qobject_cast<QDoubleSpinBox *>(ui->tableWidget->cellWidget(i, j))
              ->value());
    }
  }

  this->close();
}

void CustomKernelView::on_pushButtonReset_clicked() {
  UpdateKernelMatrix(ui->doubleSpinBoxRows->value(),
                     ui->doubleSpinCols->value());
}

void CustomKernelView::on_doubleSpinBoxRows_valueChanged(double arg1) {
  UpdateKernelMatrix(arg1, ui->doubleSpinCols->value());
}

void CustomKernelView::on_doubleSpinCols_valueChanged(double arg1) {
  UpdateKernelMatrix(ui->doubleSpinBoxRows->value(), arg1);
}

void CustomKernelView::resizeEvent(QResizeEvent *) {
  UpdateKernelMatrix(ui->doubleSpinBoxRows->value(),
                     ui->doubleSpinCols->value());
}

void CustomKernelView::closeEvent(QCloseEvent *) {
  if (ok_button_clicked_) {
    kernel_.clear();
    ok_button_clicked_ = false;
  } else {
    ok_button_clicked_ = true;
  }
}

void CustomKernelView::setToolTips() {
  ui->doubleSpinBoxRows->setToolTip("Change kernel matrix rows count.");
  ui->doubleSpinCols->setToolTip("Change kernel matrix cols count.");
  ui->pushButtonReset->setToolTip(
      "Reset kernel matrix, make zero all elements.");
  ui->pushButtonOK->setToolTip(
      "Confirm the kernel matrix and close the window.");
}
