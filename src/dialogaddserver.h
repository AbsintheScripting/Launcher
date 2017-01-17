#pragma once

#include <QDialog>

namespace Ui {
    class DialogAddServer;
}

class DialogAddServer : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddServer(QWidget *parent = nullptr);
    virtual ~DialogAddServer() override;

private:
    Ui::DialogAddServer *m_pUi;

signals:
    void selected(const QString &url, const QString &name, quint16 port);
};