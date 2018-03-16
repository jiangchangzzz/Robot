#pragma once

#include <string>

#include <QJsonValue>

#include "../Model/Robot.h"

class JsonReader
{
public:
	JsonReader();

	~JsonReader();

	static bool parse(const std::string &content, Robot &robotModel);

	static bool stringify(const Robot &robotModel, std::string &str);

private:
	static bool parseBase(const QJsonValue &value, Base &baseModel);

	static bool parseLink(const QJsonValue &value, Link &linkModel);
};
