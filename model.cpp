#include "model.h"

model::model(QSqlDatabase* database)
{
	this->database = database;
}

model::~model() {
}
