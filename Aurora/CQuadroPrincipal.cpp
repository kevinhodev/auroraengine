#include "CQuadroPrincipal.h"

#include "IGerenciadorDeComando.h"
#include "ServicoDaBarraDeFerramentas.h"
#include "QAcaoDeComando.h"
#include "DialogoSobre.h"

#include <QDesktopWidget>
#include <QDialog>
#include <QToolBar>
#include <vector>

CQuadroPrincipal* CQuadroPrincipal::s_pIntancia = nullptr;

CQuadroPrincipal::CQuadroPrincipal(QWidget *pai) : QMainWindow(pai)
{
    s_pIntancia = this;
    m_pEditor = new CEditor();
    ConfigurarIU(this);
    PosCarregamento();

    //InicializarMenus();
}

CQuadroPrincipal::~CQuadroPrincipal()
{}

void CQuadroPrincipal::PosCarregamento()
{
    std::vector<QToolBar*> barrasDeFerramentas = ObterEditor()->ObterServicoDaBarraDeFerramentas()->CarregarBarrasDeFerramentas("QuadroPrincipal");
}

void CQuadroPrincipal::InicializarMenus()
{
    QMenu* const pMenuAjuda = menuBar()->findChild<QMenu*>("MenuAjuda");
    pMenuAjuda->addAction(ObterEditor()->ObterIGerenciadorDeComandos()->ObterAcao("Geral.Ajuda"));
    pMenuAjuda->addSeparator();

    const char* szNome = "Sobre o Aurora...";
    QAction* pAcao = new QAction(szNome, pMenuAjuda);
    pAcao->setProperty("PapelDoMenu", QVariant(QApplication::translate("janelaPrincipal", "PapelSobre", 0)));
    connect(pAcao, &QAction::triggered, [this]()
    {
            if (!m_pDialogoSobre)
            {
                //m_pDialogoSobre = new CDialogoSobre();
            }

            //m_pDialogoSobre->exec();
    });

    pMenuAjuda->addAction(pAcao);
}

CQuadroPrincipal* CQuadroPrincipal::ObterInstancia()
{
    return s_pIntancia;
}

void CQuadroPrincipal::ConfigurarIU(QMainWindow* janelaPrincipal)
{
    if (janelaPrincipal->objectName().isEmpty())
    {
        janelaPrincipal->setObjectName(QStringLiteral("janelaPrincipal"));
    }

    QRect rec = QApplication::desktop()->screenGeometry();
    janelaPrincipal->resize(rec.width(), rec.height());
    QWidget* widgetCentral = new QWidget(janelaPrincipal);
    janelaPrincipal->setCentralWidget(widgetCentral);
    janelaPrincipal->setWindowTitle(QApplication::translate("janelaPrincipal", "Aurora", 0));
    janelaPrincipal->setWindowIcon(QIcon(":/icones/IconeDoEditor"));
    janelaPrincipal->setMenuBar(m_pBarraDeMenus);

    m_pBarraDeMenus = new QMenuBar(janelaPrincipal);
    m_pBarraDeMenus->setGeometry(QRect(0, 0, janelaPrincipal->width(), 21));
    m_pBarraDeMenus->setObjectName(QStringLiteral("BarraDeMenus"));

    m_pMenuArquivo = new CMenu(m_pBarraDeMenus);
    m_pMenuArquivo->setTitle(QApplication::translate("janelaPrincipal", "&Arquivo", 0));
    m_pMenuArquivo->setObjectName(QStringLiteral("MenuArquivo"));
    m_pMenuNovoArquivo = new CMenu(m_pMenuArquivo);
    m_pMenuNovoArquivo->setTitle(QApplication::translate("janelaPrincipal", "&Novo", 0));
    m_pMenuNovoArquivo->setObjectName(QStringLiteral("MenuNovoArquivo"));
    m_pMenuNovoArquivo->AdicionarComando("Projeto.Novo");
    m_pMenuAbrirArquivo = new CMenu(m_pMenuArquivo);
    m_pMenuAbrirArquivo->setTitle(QApplication::translate("janelaPrincipal", "&Abrir", 0));
    m_pMenuAbrirArquivo->setObjectName(QStringLiteral("MenuAbrirArquivo"));
    m_pMenuArquivosRecentes = new QMenu(m_pMenuArquivo);
    m_pMenuArquivosRecentes->setTitle(QApplication::translate("janelaPrincipal", "&Arquivos Recentes", 0));
    m_pMenuArquivosRecentes->setObjectName(QStringLiteral("MenuArquivosRecentes"));
    m_pMenuArquivo->addAction(m_pMenuNovoArquivo->menuAction());
    m_pMenuArquivo->addAction(m_pMenuAbrirArquivo->menuAction());
    m_pMenuArquivo->AdicionarComando("Geral.Salvar");
    m_pMenuArquivo->AdicionarComando("Geral.SalvarComo");
    m_pMenuArquivo->addSeparator();
    m_pMenuArquivo->addAction(m_pMenuArquivosRecentes->menuAction());

    m_pMenuEditar = new QMenu(m_pBarraDeMenus);
    m_pMenuEditar->setTitle(QApplication::translate("janelaPrincipal", "&Editar", 0));
    m_pMenuEditar->setObjectName(QStringLiteral("MenuEditar"));
    m_pMenuAlinharSnap = new QMenu(m_pMenuEditar);
    m_pMenuAlinharSnap->setTitle(QApplication::translate("janelaPrincipal", "&Alinhar Snap", 0));
    m_pMenuAlinharSnap->setObjectName(QStringLiteral("MenuAlinharSnap"));
    m_pMenuModoDeEdicao = new QMenu(m_pMenuEditar);
    m_pMenuModoDeEdicao->setTitle(QStringLiteral("Modo de Edição"));
    m_pMenuModoDeEdicao->setObjectName(QStringLiteral("MenuModoDeEdicao"));
    m_pMenuConstranger = new QMenu(m_pMenuEditar);
    m_pMenuConstranger->setTitle(QApplication::translate("janelaPrincipal", "&Constranger", 0));
    m_pMenuConstranger->setObjectName(QStringLiteral("MenuConstranger"));
    m_pMenuRotacaoRapida = new QMenu(m_pMenuEditar);
    m_pMenuRotacaoRapida->setTitle(QStringLiteral("Rotação Rápida"));
    m_pMenuRotacaoRapida->setObjectName(QStringLiteral("MenuRotacaoRapida"));
    m_pMenuCoordenadas = new QMenu(m_pMenuEditar);
    m_pMenuCoordenadas->setTitle(QApplication::translate("janelaPrincipal", "&Coordenadas", 0));
    m_pMenuCoordenadas->setObjectName(QStringLiteral("MenuCoordenadas"));
    m_pMenuEditar->addAction(m_pMenuAlinharSnap->menuAction());
    m_pMenuEditar->addAction(m_pMenuModoDeEdicao->menuAction());
    m_pMenuEditar->addAction(m_pMenuConstranger->menuAction());
    m_pMenuEditar->addAction(m_pMenuRotacaoRapida->menuAction());
    m_pMenuEditar->addSeparator();
    m_pMenuEditar->addMenu(m_pMenuCoordenadas);

    m_pMenuNivel = new CMenu(m_pBarraDeMenus);
    m_pMenuNivel->setObjectName(QStringLiteral("MenuNivel"));
    m_pMenuNivel->setTitle(QStringLiteral("Nível"));
    m_pMenuFisicas = new CMenu(m_pMenuNivel);
    m_pMenuFisicas->setObjectName(QStringLiteral("MenuFisicas"));
    m_pMenuFisicas->setTitle(QStringLiteral("Física"));
    m_pMenuGrupo = new CMenu(m_pMenuNivel);
    m_pMenuGrupo->setObjectName(QStringLiteral("MenuGrupo"));
    m_pMenuGrupo->setTitle(QApplication::translate("janelaPrincipal", "Grupo", 0));
    m_pMenuVincular = new CMenu(m_pMenuNivel);
    m_pMenuVincular->setObjectName(QStringLiteral("MenuVincular"));
    m_pMenuVincular->setTitle(QApplication::translate("janelaPrincipal", "Vincular", 0));
    m_pMenuPrefabricados = new CMenu(m_pMenuNivel);
    m_pMenuPrefabricados->setObjectName(QStringLiteral("MenuPrefabricados"));
    m_pMenuPrefabricados->setTitle(QApplication::translate("janelaPrincipal", "Prefabricados", 0));
    m_pMenuSelecao = new CMenu(m_pMenuNivel);
    m_pMenuSelecao->setObjectName(QStringLiteral("MenuSelecao"));
    m_pMenuSelecao->setTitle(QStringLiteral("Seleção"));
    m_pMenuMascaraDeSelecao = new CMenu(m_pMenuSelecao);
    m_pMenuMascaraDeSelecao->setObjectName(QStringLiteral("MenuMascaraDeSelecao"));
    m_pMenuMascaraDeSelecao->setTitle(QStringLiteral("Máscara de Seleção"));
    m_pMenuIluminacao = new CMenu(m_pMenuNivel);
    m_pMenuIluminacao->setObjectName(QStringLiteral("MenuIluminacao"));
    m_pMenuIluminacao->setTitle(QStringLiteral("Iluminação"));
    m_pMenuMaterial = new CMenu(m_pMenuNivel);
    m_pMenuMaterial->setObjectName(QStringLiteral("MenuMaterial"));
    m_pMenuMaterial->setTitle(QApplication::translate("janelaPrincipal", "Material", 0));
    m_pMenuNivel->addAction(m_pMenuFisicas->menuAction());
    m_pMenuNivel->addAction(m_pMenuGrupo->menuAction());
    m_pMenuNivel->addAction(m_pMenuVincular->menuAction());
    m_pMenuNivel->addAction(m_pMenuPrefabricados->menuAction());
    m_pMenuNivel->addAction(m_pMenuSelecao->menuAction());
    m_pMenuNivel->addAction(m_pMenuMascaraDeSelecao->menuAction());
    m_pMenuNivel->addAction(m_pMenuIluminacao->menuAction());
    m_pMenuNivel->addAction(m_pMenuMaterial->menuAction());

    m_pMenuExibicao = new CMenu(m_pBarraDeMenus);
    m_pMenuExibicao->setObjectName(QStringLiteral("MenuExibicao"));
    m_pMenuExibicao->setTitle(QStringLiteral("Exibição"));
    m_pMenuGraficos = new CMenu(m_pMenuExibicao);
    m_pMenuGraficos->setObjectName(QStringLiteral("MenuGraficos"));
    m_pMenuGraficos->setTitle(QStringLiteral("Gráficos"));
    m_pMenuInformacoesDeExibicao = new CMenu(m_pMenuExibicao);
    m_pMenuInformacoesDeExibicao->setObjectName(QStringLiteral("MenuInformacoesDeExibicao"));
    m_pMenuInformacoesDeExibicao->setIcon(QIcon(":/janelaDeExibicao/InformacoesDeExibicao"));
    m_pMenuInformacoesDeExibicao->setTitle(QStringLiteral("Informações de Exibição"));
    m_pMenuLocalizacao = new CMenu(m_pMenuExibicao);
    m_pMenuLocalizacao->setObjectName(QStringLiteral("MenuLocalizacao"));
    m_pMenuLocalizacao->setTitle(QStringLiteral("Localização"));
    m_pMenuLembrarLocalizacao = new CMenu(m_pMenuLocalizacao);
    m_pMenuLembrarLocalizacao->setObjectName(QStringLiteral("MenuLembrarLocalizacao"));
    m_pMenuLembrarLocalizacao->setTitle(QStringLiteral("Lembrar Localização"));
    m_pMenuIrParaLocalizacao = new CMenu(m_pMenuLocalizacao);
    m_pMenuIrParaLocalizacao->setObjectName(QStringLiteral("MenuIrParaLocalizacao"));
    m_pMenuIrParaLocalizacao->setTitle(QStringLiteral("Ir Para Localização"));
    m_pMenuLocalizacao->addAction(m_pMenuLembrarLocalizacao->menuAction());
    m_pMenuLocalizacao->addAction(m_pMenuIrParaLocalizacao->menuAction());
    m_pMenuAlterarCamera = new CMenu(m_pMenuExibicao);
    m_pMenuAlterarCamera->setObjectName(QStringLiteral("MenuAlterarCamera"));
    m_pMenuAlterarCamera->setTitle(QStringLiteral("Alterar Câmera"));
    m_pMenuExibicao->addAction(m_pMenuGraficos->menuAction());
    m_pMenuExibicao->addAction(m_pMenuInformacoesDeExibicao->menuAction());
    m_pMenuExibicao->addAction(m_pMenuLocalizacao->menuAction());
    m_pMenuExibicao->addAction(m_pMenuAlterarCamera->menuAction());

    m_pMenuJogo = new CMenu(m_pBarraDeMenus);
    m_pMenuJogo->setObjectName(QStringLiteral("MenuJogo"));
    m_pMenuJogo->setTitle(QApplication::translate("janelaPrincipal", "Jogo", 0));
    m_pMenuAudio = new CMenu(m_pMenuJogo);
    m_pMenuAudio->setObjectName(QStringLiteral("MenuAudio"));
    m_pMenuAudio->setTitle(QApplication::translate("janelaPrincipal", "Audio", 0));
    m_pAcaoMutarAudio = new QAcaoDeComando(nullptr, nullptr, janelaPrincipal);
    m_pAcaoMutarAudio->setObjectName(QStringLiteral("AcaoMutarAudio"));
    m_pAcaoMutarAudio->setIcon(QIcon(":/icones/IconeMutarAudio"));
    m_pAcaoMutarAudio->setCheckable(true);
    m_pAcaoMutarAudio->setText(QApplication::translate("janelaPrincipal", "Mutar Audio", 0));
    m_pAcaoPararTodosOsSons = new QAcaoDeComando(nullptr, nullptr, janelaPrincipal);
    m_pAcaoPararTodosOsSons->setObjectName(QStringLiteral("AcaoPararTodosOsSons"));
    m_pAcaoPararTodosOsSons->setIcon(QIcon(":/icones/IconePararTodosOsSons"));
    m_pAcaoPararTodosOsSons->setText(QApplication::translate("janelaPrincipal", "Parar Todos os Sons", 0));
    m_pAcaoAtualizarAudio = new QAcaoDeComando(nullptr, nullptr, janelaPrincipal);
    m_pAcaoAtualizarAudio->setObjectName(QStringLiteral("AcaoAtualizarAudio"));
    m_pAcaoAtualizarAudio->setIcon(QIcon(":/icones/IconeAtualizarAudio"));
    m_pAcaoAtualizarAudio->setText(QApplication::translate("janelaPrincipal", "Atualizar Audio", 0));
    m_pMenuAudio->addAction(m_pAcaoMutarAudio);
    m_pMenuAudio->addAction(m_pAcaoPararTodosOsSons);
    m_pMenuAudio->addAction(m_pAcaoAtualizarAudio);
    m_pMenuIA = new CMenu(m_pMenuJogo);
    m_pMenuIA->setObjectName(QStringLiteral("MenuIA"));
    m_pMenuIA->setTitle(QApplication::translate("janelaPrincipal", "IA", 0));
    m_pMenuJogo->addAction(m_pMenuAudio->menuAction());
    m_pMenuJogo->addAction(m_pMenuIA->menuAction());

    m_pMenuDepurar = new CMenu(m_pBarraDeMenus);
    m_pMenuDepurar->setObjectName(QStringLiteral("MenuDepurar"));
    m_pMenuDepurar->setTitle(QApplication::translate("janelaPrincipal", "Depurar", 0));
    m_pAcaoMostrarArquivoDeLog = new QAcaoDeComando(nullptr, nullptr, janelaPrincipal);
    m_pAcaoMostrarArquivoDeLog->setObjectName(QStringLiteral("AcaoMostrarArquivoDeLog"));
    m_pAcaoMostrarArquivoDeLog->setText(QApplication::translate("janelaPrincipal", "Mostrar Arquivo de Log", 0));
    m_pMenuRecarregarScripts = new CMenu(m_pMenuDepurar);
    m_pMenuRecarregarScripts->setObjectName(QStringLiteral("MenuRecarregarScripts"));
    m_pMenuRecarregarScripts->setTitle(QApplication::translate("janelaPrincipal", "Recarregar Scripts", 0));
    m_pMenuAvancado = new CMenu(m_pMenuDepurar);
    m_pMenuAvancado->setObjectName(QStringLiteral("MenuAvancado"));
    m_pMenuAvancado->setTitle(QStringLiteral("Avançado"));
    m_pAcaoReduzirConjuntoDeTrabalho = new QAcaoDeComando(nullptr, nullptr, janelaPrincipal);
    m_pAcaoReduzirConjuntoDeTrabalho->setObjectName(QStringLiteral("AcaoReduzirConjuntoDeTrabalho"));
    m_pAcaoReduzirConjuntoDeTrabalho->setText(QApplication::translate("MainWindow", "Reduzir Conjunto de Trabalho", 0));
    m_pMenuAvancado->addAction(m_pAcaoReduzirConjuntoDeTrabalho);
    m_pMenuDepurar->addAction(m_pMenuRecarregarScripts->menuAction());
    m_pMenuDepurar->addSeparator();
    m_pMenuDepurar->addAction(m_pMenuAvancado->menuAction());
    m_pMenuDepurar->addAction(m_pAcaoMostrarArquivoDeLog);

    m_pMenuFerramentas = new CMenu(m_pBarraDeMenus);
    m_pMenuFerramentas->setObjectName(QStringLiteral("MenuFerramentas"));
    m_pMenuFerramentas->setTitle(QApplication::translate("janelaPrincipal", "Ferramentas", 0));

    m_pMenuLayout = new CMenu(m_pBarraDeMenus);
    m_pMenuLayout->setObjectName(QStringLiteral("MenuLayout"));
    m_pMenuLayout->setTitle(QApplication::translate("janelaPrincipal", "Layout", 0));

    m_pMenuAjuda = new CMenu(m_pBarraDeMenus);
    m_pMenuAjuda->setObjectName(QStringLiteral("MenuAjuda"));
    m_pMenuAjuda->setTitle(QApplication::translate("janelaPrincipal", "Ajuda", 0));
    m_pMenuAjuda->addAction(ObterEditor()->ObterIGerenciadorDeComandos()->ObterAcao("Geral.Ajuda"));
    m_pMenuAjuda->addSeparator();
    m_pMenuAjuda->addAction(ObterEditor()->ObterIGerenciadorDeComandos()->ObterAcao("Geral.Sobre"));

    m_pBarraDeMenus->addAction(m_pMenuArquivo->menuAction());
    m_pBarraDeMenus->addAction(m_pMenuEditar->menuAction());
    m_pBarraDeMenus->addAction(m_pMenuNivel->menuAction());
    m_pBarraDeMenus->addAction(m_pMenuExibicao->menuAction());
    m_pBarraDeMenus->addAction(m_pMenuJogo->menuAction());
    m_pBarraDeMenus->addAction(m_pMenuDepurar->menuAction());
    m_pBarraDeMenus->addAction(m_pMenuFerramentas->menuAction());
    m_pBarraDeMenus->addAction(m_pMenuLayout->menuAction());
    m_pBarraDeMenus->addAction(m_pMenuAjuda->menuAction());

    QMetaObject::connectSlotsByName(janelaPrincipal);
}
