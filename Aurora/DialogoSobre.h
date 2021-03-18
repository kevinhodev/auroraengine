#pragma once

#include "CQuadroPrincipal.h"

#include <QDialog>

class QLabel;

class CDialogoSobre : public QDialog
{
	public:
		CDialogoSobre(CQuadroPrincipal* pPai);
		~CDialogoSobre();

	protected:
		QLabel* m_pRotuloVersao;
		QLabel* m_pRotuloInformacoesMista;
};

