#pragma once

#include <QWidget>
#include <QButtonGroup>
#include <QAbstractItemView>
#include <QListView>

#include "QVisualizacaoDeArvoreAvancada.h"
//#include "AtributoDeModeloDeItem.h"

class QSize;
class QModelIndex;

class QVisualizacaoEmMiniatura : public QWidget
{
	Q_OBJECT
	public:
		QVisualizacaoEmMiniatura(QListView* pVisualizacaoInterna, bool mostrarBotoesDeTamanho = true, QWidget* pPai = nullptr);
		~QVisualizacaoEmMiniatura();

		bool DefinirTamanhoDoItem(const QSize& tamanho);
		inline QSize ObterTamanhoDoItem() const { return m_tamanhoDoItem; }
		void DefinirLimitesDeTamanhoDeItem(const QSize& minimo, const QSize& maximo);
		void DefinirIndiceRaiz(const QModelIndex& indice);
		QModelIndex  ObterIndiceRaiz() const;
		void DefinirColunaDeDados(int coluna);
		//bool DefinirAtributoDeDados(const CAtributoDeModeloDeItem* atributo = &Atributos::s_atributoDeMiniatura, int funcaoDeAtributo = Atributos::s_obterFuncaoDeAributo);
		void DefinirModelo(QAbstractItemModel* pModelo);
		void RolarParaLinha(const QModelIndex& indiceNaLinha, QAbstractItemView::ScrollHint dicaDeRolagem = QAbstractItemView::EnsureVisible);
		inline QAbstractItemView* ObterVisualizacaoInterna() { return m_pVisualizacaoDeLista; }

	private:
		void AoModeloPrestesASerReiniciado();
		void AoReiniciarOModelo();
		void AdicionarBotãoDeDimensionamento(int tamanho, int numeroDoIcone);

		class Delegado;
		Delegado* m_pDelegado;
		QListView* m_pVisualizacaoDeLista;
		QSize m_tamanhoMinimoDoItem;
		QSize m_tamanhoMaximoDoItem;
		QSize m_tamanhoDoItem;
		const QSize m_tamanhoPadrao;
		bool m_bTemporizadorIniciou;
		bool m_bRestaurarSelecao;
		QButtonGroup* m_pBotoesDeTamanhoDeVisualizacao;
		const int m_numeroDeTamanhosDeVisualização = 4;
		std::vector<CIndiceDeModeloPersistenteAvançado> m_backupSelecionado;
};

