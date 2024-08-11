#ifndef ONB7_H
#define ONB7_H

#include <QDialog>

namespace Ui {
class onb7;
}

class onb7 : public QDialog
{
    Q_OBJECT

public:
    explicit onb7(QWidget *parent = nullptr);
    ~onb7();
private slots:
    void on_btnExit_clicked();
    void selectAll();
    void add();
    void remove();
    void search();

private:
    Ui::onb7 *ui;
    void populate1ComboBox();
    void populate2ComboBox();
void populate3ComboBox();
    QString m_lastSearchQuery;
    int m_lastFoundIndex = -1;
};

#endif // ONB7_H
