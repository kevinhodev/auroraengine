#include "DialogoSelecionarProjeto.h"
#include "PainelAbrirProjeto.h"
#include "PainelCriarProjeto.h"

#include <QTabWidget>
#include <QVBoxLayout>

CDialogoSelecionarProjeto::CDialogoSelecionarProjeto(QWidget* pPai, Tab tabParaMostrar)
	: QDialog(pPai)
{
	setWindowTitle("Navegador de Projetos");
	setWindowIcon(QIcon(":/icones/IconeDoEditor"));

	QTabWidget* pTabs = new QTabWidget(this);
	pTabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	pTabs->setTabsClosable(false);

	pTabs->addTab(new CPainelAbrirProjeto(this), "Projetos");
	pTabs->addTab(new CPainelCriarProjeto(this), "Novo Projeto");

	switch (tabParaMostrar)
	{
		case CDialogoSelecionarProjeto::Tab::Abrir:
			pTabs->setCurrentIndex(0);
			break;
		case CDialogoSelecionarProjeto::Tab::Criar:
			pTabs->setCurrentIndex(1);
			break;
		default:
			break;
	}

	QVBoxLayout* pLayoutPrincipal = new QVBoxLayout();
	pLayoutPrincipal->setContentsMargins(0, 0, 0, 0);
	pLayoutPrincipal->setSpacing(0);
	pLayoutPrincipal->setMargin(0);
	pLayoutPrincipal->addWidget(pTabs);
	setLayout(pLayoutPrincipal);
}

CDialogoSelecionarProjeto::~CDialogoSelecionarProjeto()
{}
