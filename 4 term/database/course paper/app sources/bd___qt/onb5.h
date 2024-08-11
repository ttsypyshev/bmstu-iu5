#ifndef ONB5_H
#define ONB5_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class onb5;
}

class onb5 : public QDialog
{
    Q_OBJECT

public:
    explicit onb5(QWidget *parent = nullptr);
    ~onb5();
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
    Ui::onb5 *ui;
    QString m_lastSearchQuery;
    int m_lastFoundIndex = -1;
};

#endif // ONB5_H
