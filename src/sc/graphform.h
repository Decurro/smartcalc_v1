#ifndef GRAPHFORM_H
#define GRAPHFORM_H
#include <QVector>
#include <QWidget>

namespace Ui {
class GraphForm;
}

class GraphForm : public QWidget {
  Q_OBJECT

 public:
  explicit GraphForm(QWidget *parent = nullptr, QString input1 = "here");
  ~GraphForm();

 public:
  GraphForm(QString str) { input = str; }

 private slots:
  void create_graph();
  void step(double x_start, double x_stop, double *stepik);
  int razriv(double x_1, double x_2);
  void closeEvent(QCloseEvent *event);

 private:
  QString input;
  QVector<double> x, y;

 signals:
  void close();

 private:
  Ui::GraphForm *ui;
};

#endif  // GRAPHFORM_H
