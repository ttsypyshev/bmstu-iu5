#ifndef ONB3_H
#define ONB3_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class onb3;
}

class onb3 : public QDialog
{
    Q_OBJECT

public:
    explicit onb3(QWidget *parent = nullptr);
    ~onb3();
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
    Ui::onb3 *ui;
    QString m_lastSearchQuery;
    int m_lastFoundIndex = -1;
};

#endif // ONB3_H
