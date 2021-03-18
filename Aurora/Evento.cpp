#include "Evento.h"

#include <QApplication>
#include <QWidget>
#include <QObject>

CEventoDoAquara::CEventoDoAquara(TipoDeEvento tipoDeEvento)
	: QEvent(static_cast<QEvent::Type>(tipoDeEvento))
{}

void CEventoDoAquara::EnvieParaOFocoDoTeclado()
{
	QObject* const pFocado = QApplication::focusWidget();

	if (pFocado)
	{
		QApplication::sendEvent(pFocado, this);
	}
}

CEventoDeComando::CEventoDeComando(const char* szComando)
	: CEventoDoAquara(TipoDeEvento::Comando)
	, m_comando(szComando)
{}
