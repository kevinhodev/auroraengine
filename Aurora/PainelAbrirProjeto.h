#pragma once

#include <QWidget>

class CDialogoSelecionarProjeto;
class QButtonGroup;
class QVBoxLayout;
class QVisualizacaoEmArvoreAvancada;
class QVisualizacaoEmMiniatura;
class QSortFilterProxyModel;
class QPushButton;

class CPainelAbrirProjeto : public QWidget
{
	public:
		enum ModoDeVisualizacao
		{
			Arvore,
			Miniatura
		};
		
		CPainelAbrirProjeto(CDialogoSelecionarProjeto* pPai);
		~CPainelAbrirProjeto();

		void CriarPainelDePesquisa();
		void CriarVizualizacoes();
		void CriarBotaoVisualizacaoEmLista(QButtonGroup* pGrupo);
		void CriarBotaoVisualizacaoEmMiniatura(QButtonGroup* pGrupo);
		void CriarBotoesDoDialogo();

		void DefinirModoDeVisualizacao(ModoDeVisualizacao modo);

		CDialogoSelecionarProjeto* m_pPai;
		QVBoxLayout* m_pLayoutPrincipal;
		QVisualizacaoEmArvoreAvancada* m_pVisualizacaoEmArvore;
		QVisualizacaoEmMiniatura* m_pVisualizacaoEmMiniatura;
		QSortFilterProxyModel* m_pModeloClassificado;
		QPushButton* m_pBotaoAdicionarProjeto;
		QPushButton* m_pBotaoAbrirProjeto;
};

