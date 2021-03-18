#pragma once

#include <QEvent>
#include <QString>

class CEventoDoAquara : public QEvent
{
	public:
		enum TipoDeEvento
		{
			Comando
		};

		CEventoDoAquara(TipoDeEvento tipoDeEvento);
		void EnvieParaOFocoDoTeclado();
};

class CEventoDeComando: public CEventoDoAquara
{
	public:
		CEventoDeComando(const char* szComando);

	private:
		QString m_comando;
};
