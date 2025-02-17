#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QRegExp>

#include "dialogaddserver.h"
#include "ui_dialogaddserver.h"

const char* invalidStyle = "background-color: #B22222; color: white;";
// FIXME: incorporate ipv6 later if you want
const QRegularExpression ip4Match = QRegularExpression(R"(^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)");
// domain rules: http://stackoverflow.com/a/7933253/433790
const QRegularExpression domainMatch = QRegularExpression(R"(^(?!.{256})(?:[a-z0-9](?:[a-z0-9-]{0,61}[a-z0-9])?\.)+(?:[a-z]{1,63}|xn--[a-z0-9]{1,59})$)");

DialogAddServer::DialogAddServer(QWidget *parent) :
    QDialog(parent),
    m_pUi(new Ui::DialogAddServer) {

    m_pUi->setupUi(this);

	m_pUi->editUrl->setStyleSheet(invalidStyle);

	connect(m_pUi->editUrl, &QLineEdit::editingFinished, [this]() {

		QLineEdit* addressLine = this->m_pUi->editUrl;

		// check url for regex match and set validity
		if (!ip4Match.match(addressLine->text()).hasMatch() && !domainMatch.match(addressLine->text()).hasMatch())
		{
			addressLine->setStyleSheet(invalidStyle);
			return;
		}

		this->hasValidInput = true;

	});
	connect(m_pUi->editUrl, &QLineEdit::textChanged, [this]() {

		// we start changing the text: reset style and validity
		QLineEdit* addressLine = this->m_pUi->editUrl;
		addressLine->setStyleSheet(0);
		this->hasValidInput = false;

	});
    connect(m_pUi->buttonCancel, &QPushButton::clicked, [this]() {

        close();

    });
	connect(m_pUi->buttonAddServer, &QPushButton::clicked, [this]() {

		QLineEdit* serverNameLine = this->m_pUi->editServerName;
		QLineEdit* addressLine = this->m_pUi->editUrl;
		quint16 port = this->m_pUi->editPort->value();

		// check validation again and send the data to the main form
		if (addressLine->text().size() > 0 && this->hasValidInput)
		{
			emit selected(serverNameLine->text(), addressLine->text(), port);
		}

		close();

	});
}

DialogAddServer::~DialogAddServer() {

    delete m_pUi;

}
