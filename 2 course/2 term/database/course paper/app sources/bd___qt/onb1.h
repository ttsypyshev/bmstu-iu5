#ifndef ONB1_H
#define ONB1_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class onb1;
}

class onb1 : public QDialog
{
    Q_OBJECT

public:
    explicit onb1(QWidget *parent = nullptr);
    ~onb1();
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
    Ui::onb1 *ui;
    QString m_lastSearchQuery;
    int m_lastFoundIndex = -1;
};

#endif // ONB1_H
