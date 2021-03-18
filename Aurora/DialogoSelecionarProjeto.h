#pragma once

#include <QDialog>

class CDialogoSelecionarProjeto : public QDialog
{
	Q_OBJECT
	public:
		enum class Tab
		{
			Abrir,
			Criar
		};

		CDialogoSelecionarProjeto(QWidget* pPai, Tab tabParaMostrar);
		~CDialogoSelecionarProjeto();
};

