#include "QVisualizacaoDeArvoreAvancada.h"

#include <QModelIndex>
#include <QPersistentModelIndex>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QAbstractProxyModel>

CIndiceDeModeloPersistenteAvançado::CIndiceDeModeloPersistenteAvançado(const QModelIndex& indice)
	: m_coluna(indice.column())
	, m_modelo(indice.model())
	, m_indicePersistente(indice)
{
	QModelIndex indiceLocal = indice;

	while (indiceLocal.isValid())
	{
		m_identificadores.push_front(indiceLocal.internalId());
		indiceLocal = indiceLocal.parent();
	}
}

QModelIndex CIndiceDeModeloPersistenteAvançado::ConverterParaIndice() const
{
	if (m_indicePersistente.isValid())
	{
		return m_indicePersistente;
	}

	QModelIndex indice;

	std::deque<quintptr> identificadores = m_identificadores;

	while (!identificadores.empty())
	{
		const int contagemDeLinhas = m_modelo->rowCount(indice);
		bool bEncontrado = false;

		for (int i = 0; i < contagemDeLinhas; i++)
		{
			QModelIndex indiceDaLinha = m_modelo->index(i, m_coluna, indice);
			if (indiceDaLinha.internalId() == identificadores.front())
			{
				indice = indiceDaLinha;
				identificadores.pop_front();
				bEncontrado = true;
				break;
			}
		}

		if (!bEncontrado)
		{
			return QModelIndex();
		}

	}

	return indice;
}

QVisualizacaoEmArvoreAvancada::QVisualizacaoEmArvoreAvancada()
{}

QVisualizacaoEmArvoreAvancada::~QVisualizacaoEmArvoreAvancada()
{}

QModelIndex QVisualizacaoEmArvoreAvancada::ConverterParaOriginal(QModelIndex& indice, QAbstractItemModel* pModeloDeVisualizacao)
{
	QAbstractItemModel* modelo = pModeloDeVisualizacao;
	QModelIndex original = indice;

	while (QAbstractProxyModel* proxy = qobject_cast<QAbstractProxyModel*>(modelo))
	{
		original = proxy->mapToSource(original);
		modelo = proxy->sourceModel();
	}

	return original;
}

QModelIndex QVisualizacaoEmArvoreAvancada::ConverterDoOriginal(QModelIndex& indice, QAbstractItemModel* pModeloDeVisualizacao)
{
	std::vector<QAbstractProxyModel*> proxys;

	QAbstractItemModel* modelo = pModeloDeVisualizacao;

	while (QAbstractProxyModel* proxy = qobject_cast<QAbstractProxyModel*>(modelo))
	{
		proxys.push_back(proxy);
		modelo = proxy->sourceModel();
	}

	QModelIndex localIndex = indice;

	for (auto iterador = proxys.rbegin(); iterador != proxys.rend(); ++iterador)
	{
		localIndex = (*iterador)->mapFromSource(localIndex);
	}

	return localIndex;
}

void QVisualizacaoEmArvoreAvancada::SalvarSelecao(std::vector<CIndiceDeModeloPersistenteAvançado>& armazenamentoDeBackupSelecionado, QAbstractItemModel * pModeloDeVisualizacao, QItemSelectionModel * pModeloDeSelecaoDeVisualizacao)
{
	armazenamentoDeBackupSelecionado.clear();

	QModelIndexList lista = pModeloDeSelecaoDeVisualizacao->selectedRows();

	for (QModelIndex indice : lista)
	{
		armazenamentoDeBackupSelecionado.push_back(CIndiceDeModeloPersistenteAvançado(ConverterParaOriginal(indice, pModeloDeVisualizacao)));
	}

	armazenamentoDeBackupSelecionado.push_back(CIndiceDeModeloPersistenteAvançado(ConverterParaOriginal(pModeloDeSelecaoDeVisualizacao->currentIndex(), pModeloDeVisualizacao)));
}

void QVisualizacaoEmArvoreAvancada::RestaurarSelecao(std::vector<CIndiceDeModeloPersistenteAvançado>& armazenamentoDeBackupSelecionado, QAbstractItemModel* pModeloDeVisualizacao, QItemSelectionModel* pModeloDeSelecaoDeVisualizacao)
{
	if (armazenamentoDeBackupSelecionado.size() == 0)
	{
		return;
	}

	QModelIndex atual = ConverterDoOriginal(armazenamentoDeBackupSelecionado[armazenamentoDeBackupSelecionado.size() - 1].ConverterParaIndice(), pModeloDeVisualizacao);
	armazenamentoDeBackupSelecionado.pop_back();

	for (CIndiceDeModeloPersistenteAvançado indicePersisente : armazenamentoDeBackupSelecionado)
	{
		QModelIndex indice = indicePersisente.ConverterParaIndice();
		if (indice.isValid())
		{
			QModelIndex indiceLocal = ConverterDoOriginal(indice, pModeloDeVisualizacao);
			pModeloDeSelecaoDeVisualizacao->select(indiceLocal, QItemSelectionModel::Select | QItemSelectionModel::Rows);
		}
	}

	if (atual.isValid())
	{
		pModeloDeSelecaoDeVisualizacao->setCurrentIndex(atual, QItemSelectionModel::Select | QItemSelectionModel::Rows);
	}

	armazenamentoDeBackupSelecionado.clear();
}
