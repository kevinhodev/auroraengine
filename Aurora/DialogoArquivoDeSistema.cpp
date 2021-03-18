#include "DialogoArquivoDeSistema.h"

CDialogoArquivoDeSistema::CDialogoArquivoDeSistema(const ParametrosDeAbertura& parametrosDeAbertura, QWidget* pPai)
	: m_dialogo(pPai)
{
	m_dialogo.setOption(QFileDialog::DontUseCustomDirectoryIcons);
	m_dialogo.setFileMode(QFileDialog::Directory);

	m_dialogo.setWindowTitle(parametrosDeAbertura.titulo);
	m_dialogo.setDirectory(parametrosDeAbertura.diretorioInicial);

	m_dialogo.directory();
}

std::vector<QString> CDialogoArquivoDeSistema::ObterArquivosSelecionados() const
{
	return m_dialogo.selectedFiles().toVector().toStdVector();
}
