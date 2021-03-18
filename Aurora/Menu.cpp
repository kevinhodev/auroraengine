#include "Menu.h"
#include "Editor.h"
#include "QAcaoDeComando.h"

CMenu::CMenu(QWidget* pPai) : QMenu(pPai)
{
}

QAcaoDeComando* CMenu::AdicionarComando(const char* szComando)
{
	QAcaoDeComando* pAcao = ObterEditor()->ObterGerenciadorDeComandos()->ObterAcaoDeComando(szComando);
	if (pAcao)
	{
		addAction(pAcao);
	}

	return pAcao;
}