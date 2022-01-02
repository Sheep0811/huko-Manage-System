#ifndef REASON_H
#define REASON_H

#include <QWidget>

namespace Ui {
class reason;
}

class reason : public QWidget
{
    Q_OBJECT

public:
    explicit reason(QWidget *parent = nullptr);
    ~reason();
    void set(QString tmp);

private slots:
    void on_pushButton_clicked();

private:
    Ui::reason *ui;
     QString hno;
};

#endif // REASON_H
