#pragma once

#include <QWidget>

class CDialogoSelecionarProjeto;
class QVBoxLayout;
class QButtonGroup;
class QToolButton;
class QLineEdit;
class QTreeView;
class QVisualizacaoEmMiniatura;
class QSortFilterProxyModel;

class CPainelCriarProjeto : public QWidget
{
	public:
		enum ModoDeVisualizacao
		{
			Arvore,
			Miniatura
		};

		CPainelCriarProjeto(CDialogoSelecionarProjeto* pPai);
		~CPainelCriarProjeto();

	private:
		void CriarPainelDePesquisa();
		void CriarVizualizacoes();
		void CriarBotaoVizualizacaoDeLista(QButtonGroup* pGrupo);
		void CriarBotaoMiniatura(QButtonGroup* pGrupo);
		void CriarCaixaDeEdicaoPastaRaizDeSaida();
		void CriarCaixaDeEdicaoNomeDoProjeto();
		void CriarBotoesDoDialogo();

		void DefinirModoDeVisualizacao(ModoDeVisualizacao modo);
		void AoAlterarAPastaDeSaida();

		CDialogoSelecionarProjeto* m_pPai;
		QVBoxLayout* m_pLayoutPrincipal;
		QLineEdit* m_pLinhaDeEdicaoDiretorioDeSaida;
		QTreeView* m_pVisualizacaoDeArvore;
		QVisualizacaoEmMiniatura* m_pVisualizacaoDeMiniatura;
		QSortFilterProxyModel* m_pModeloClassificado;
};

