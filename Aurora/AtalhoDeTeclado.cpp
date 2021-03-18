#include "AtalhoDeTeclado.h"

#include <QString>

CAtalhoDeTeclado::CAtalhoDeTeclado() 
	: m_tecla(TeclaPadrao::Contagem)
{}

CAtalhoDeTeclado::CAtalhoDeTeclado(TeclaPadrao tecla)
	: m_tecla(tecla)
{}

CAtalhoDeTeclado::CAtalhoDeTeclado(const char* string)
	: m_tecla(TeclaPadrao::Contagem)
	, m_string(string)
{}

QList<QKeySequence> CAtalhoDeTeclado::ConverterParaSequenciaDeTecla() const
{
	if (EUmaTeclaPadrao())
	{
		switch (ObterTecla())
		{
			case CAtalhoDeTeclado::TeclaPadrao::WikiDeAjuda:
				return QKeySequence::keyBindings(QKeySequence::HelpContents);
			case CAtalhoDeTeclado::TeclaPadrao::Salvar:
				return QKeySequence::keyBindings(QKeySequence::Save);
			case CAtalhoDeTeclado::TeclaPadrao::SalvarComo:
				return QKeySequence::keyBindings(QKeySequence::SaveAs);
			default:
				break;
		}
	}
	else if (!ObterSring().isEmpty())
	{
		return QKeySequence::listFromString(ObterSring());
	}

	return QList<QKeySequence>();
}

