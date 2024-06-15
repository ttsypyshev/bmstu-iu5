#ifndef ONB2_H
#define ONB2_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class onb2;
}

class onb2 : public QDialog
{
    Q_OBJECT

public:
    explicit onb2(QWidget *parent = nullptr);
    ~onb2();
private slots:
    void selectAll();
    void on_btnExit_clicked();
    void add();
    void remove();
    void clean();
    void edit();
    void on_tw_itemSelectionChanged();
    void search();
    void generateReportRequest();
private:
    Ui::onb2 *ui;
    QString m_lastSearchQuery;
    int m_lastFoundIndex = -1;
};

#endif // onb2_H
