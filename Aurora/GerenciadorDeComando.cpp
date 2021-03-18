#include "GerenciadorDeComando.h"
#include "QAcaoDeComando.h"

CGerenciadorDeComandosDoEditor::CGerenciadorDeComandosDoEditor()
{
}

CGerenciadorDeComandosDoEditor::~CGerenciadorDeComandosDoEditor()
{
}

QString CGerenciadorDeComandosDoEditor::ObterNomeCompletoDoComando(const QString& modulo, const QString& nome)
{
    QString nomeCompleto = modulo;
    nomeCompleto += ".";
    nomeCompleto += nome;
    return nomeCompleto;
}

bool CGerenciadorDeComandosDoEditor::AdicionarComando(CComando* pComando, TPfnDeletador deletador)
{
    assert(pComando);
    QString modulo = pComando->ObterModulo();
    QString nome = pComando->ObterNome();

    if (EstaRegistrado(modulo, nome))
    {
        return false;
    }

    if (pComando->PodeSerUmComandoDaIU())
    {
        CComandoDaIU* comandoDaIU = static_cast<CComandoDaIU*>(pComando);
        QAcaoDeComando* acao = nullptr;

        if (comandoDaIU->ObterInformacoesDaIU() == nullptr)
        {
            acao = new QAcaoDeComando(*comandoDaIU);
        }

        comandoDaIU->DefinirInformacoesDaIU(acao);
    }

    SEntradaDaTabelaDeComandos entrada;
    entrada.pComando = pComando;
    entrada.deletador = deletador;

    m_comandos.insert(TabelaDeComandos::value_type(ObterNomeCompletoDoComando(modulo, nome), entrada));

    return true;
}

void CGerenciadorDeComandosDoEditor::RegistrarDescricaoDaIU(const QString& modulo, const QString& nome, const QString& textoDoBotao, const CAtalhoDeTeclado& atalho, QString icone, bool checavel)
{
    CComandoDaIU::InformacoesDaIU informacoesDaIU(textoDoBotao, icone, atalho, checavel);
    DefinirDescricaoDaIU(modulo, nome, informacoesDaIU);
}

void CGerenciadorDeComandosDoEditor::ExecutarComando(const QString& linhaDeComando, ...)
{
    TabelaDeComandos::const_iterator iterador = m_comandos.find(linhaDeComando);

    if (iterador != m_comandos.end())
    {
        iterador->second.pComando->Executar();
    }
}

bool CGerenciadorDeComandosDoEditor::EstaRegistrado(const QString& modulo, const QString& nome) const
{
    QString nomeCompleto = ObterNomeCompletoDoComando(modulo, nome);
    TabelaDeComandos::const_iterator iterador = m_comandos.find(nomeCompleto);

    if (iterador != m_comandos.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

QAction* CGerenciadorDeComandosDoEditor::ObterAcao(const char* nomeCompletoDoComando, const char* texto) const
{
    return (QAction*)ObterAcaoDeComando(nomeCompletoDoComando, texto);
}

QAcaoDeComando* CGerenciadorDeComandosDoEditor::ObterAcaoDeComando(const char* comando, const char* texto) const
{
    TabelaDeComandos::const_iterator iterador;
    iterador = m_comandos.find(comando);
 
    if (iterador != m_comandos.end())
    {
        if (iterador->second.pComando->PodeSerUmComandoDaIU())
        {
            return static_cast<QAcaoDeComando*>(static_cast<CComandoDaIU*>(iterador->second.pComando)->ObterInformacoesDaIU());
        }
    }

    return new QAcaoDeComando(texto ? texto : "Comando Inexistente", nullptr, comando);
}

void CGerenciadorDeComandosDoEditor::DefinirDescricaoDaIU(const QString& modulo, const QString& nome, const CComandoDaIU::InformacoesDaIU& informacoes)
{
    QString nomeCompletoDoComando = ObterNomeCompletoDoComando(modulo, nome);

    if (!nomeCompletoDoComando.isEmpty())
    {
        QAcaoDeComando* pAcao = ObterAcaoDeComando(nomeCompletoDoComando.toStdString().c_str());

        if (pAcao)
        {
            *pAcao = informacoes;
        }
    }
}
