#include <QMenu.h>

class QAcaoDeComando;

class CMenu : public QMenu
{
	public:
		CMenu(QWidget* pPai = nullptr);

		QAcaoDeComando* AdicionarComando(const char* szComando);
};
