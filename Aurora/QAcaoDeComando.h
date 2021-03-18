#pragma once

#include <QAction>
#include <QList>
#include <QKeySequence>

#include "Comando.h"

class QAcaoDeComando : public QAction, public CComandoDaIU::InformacoesDaIU
{
	Q_OBJECT
	public:
		QAcaoDeComando(const QString& nomeDaAcao, const QString& textoDaAcao, QObject* pai, const char* comando = 0);
		QAcaoDeComando(const QString& nomeDaAcao, QObject* pai, const char* comando);
		QAcaoDeComando(const QAcaoDeComando& comando);
		QAcaoDeComando(const CComandoDaIU& comando);
		~QAcaoDeComando() {}
		void DefinirAtalhosPadroes(const QList<QKeySequence>& atalhos) { m_padroes = atalhos; }

		virtual void operator=(const InformacoesDaIU& informacoes) override;

	protected:
		void AoAcionar();

	private:
		QList<QKeySequence> m_padroes;
};

