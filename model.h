#ifndef MODEL_H
#define MODEL_H
#include <QString>

class model
{
	private:
		QString login;
		QString password;
	public:
		model();
		void checkUser(QString login, QString password);
};

#endif // MODEL_H
