#include "JsonReader.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

JsonReader::JsonReader()
{
}

JsonReader::~JsonReader()
{
}

bool JsonReader::parse(const std::string & content, Robot & robotModel)
{
	QJsonParseError jsonError;
	QJsonDocument document = QJsonDocument::fromJson(QString::fromStdString(content).toUtf8(), &jsonError);
	if (!document.isNull() && jsonError.error == QJsonParseError::NoError)
	{
		if (document.isObject())
		{
			QJsonObject root = document.object();
			if (root.contains("name"))
			{
				QJsonValue value = root.value("name");
				if (value.isString())
				{
					robotModel.name = value.toString().toStdString();
				}
			}

			if (root.contains("velocity"))
			{
				QJsonValue value = root.value("velocity");
				if (value.isDouble())
				{
					robotModel.velocity = value.toDouble();
				}
			}

			if (root.contains("acceleration"))
			{
				QJsonValue value = root.value("acceleration");
				if (value.isDouble())
				{
					robotModel.acceleration = value.toDouble();
				}
			}

			if (root.contains("jointVelocity"))
			{
				QJsonValue value = root.value("jointVelocity");
				if (value.isDouble())
				{
					robotModel.jointVelocity = value.toDouble();
				}
			}

			if (root.contains("jointAcceleration"))
			{
				QJsonValue value = root.value("jointAcceleration");
				if (value.isDouble())
				{
					robotModel.jointAcceleration = value.toDouble();
				}
			}

			if (root.contains("base"))
			{
				QJsonValue value = root.value("base");
				parseBase(value, robotModel.base);
			}

			if (root.contains("links"))
			{
				QJsonValue value = root.value("links");
				if (value.isArray())
				{
					QJsonArray arr = value.toArray();
					for (int i = 0; i < arr.size(); i++)
					{
						Link linkModel;
						parseLink(arr[i], linkModel);
						robotModel.links.push_back(linkModel);
					}
				}
			}

			return true;
		}
	}

	return false;
}

bool JsonReader::stringify(const Robot & robotModel, std::string & str)
{
	QJsonObject root;
	root.insert("name", QString::fromStdString(robotModel.name));
	root.insert("velocity", robotModel.velocity);
	root.insert("acceleration", robotModel.acceleration);
	root.insert("jointVelocity", robotModel.jointVelocity);
	root.insert("jointAcceleration", robotModel.jointAcceleration);

	QJsonObject baseNode;
	baseNode.insert("path", QString::fromStdString(robotModel.base.path));

	QJsonArray linksNode;
	for (const auto &link : robotModel.links)
	{
		QJsonObject linkNode;
		linkNode.insert("type", link.type);
		linkNode.insert("path", QString::fromStdString(link.path));
		linkNode.insert("alpha", link.alpha);
		linkNode.insert("a", link.a);
		linkNode.insert("theta", link.theta);
		linkNode.insert("d", link.d);
		linkNode.insert("jointMin", link.jointMin);
		linkNode.insert("jointMax", link.jointMax);

		linksNode.append(linkNode);
	}

	root.insert("base", baseNode);
	root.insert("links", linksNode);

	QJsonDocument document;
	document.setObject(root);
	str = document.toJson(QJsonDocument::Compact).toStdString();

	return true;
}

bool JsonReader::parseBase(const QJsonValue & value, Base & baseModel)
{
	if (value.isObject())
	{
		QJsonObject object = value.toObject();

		if (object.contains("path"))
		{
			QJsonValue pathValue = object.value("path");
			if (pathValue.isString())
			{
				baseModel.path = pathValue.toString().toStdString();
			}
		}

		return true;
	}
	return false;
}

bool JsonReader::parseLink(const QJsonValue & value, Link & linkModel)
{
	if (value.isObject())
	{
		QJsonObject object = value.toObject();

		if (object.contains("type"))
		{
			QJsonValue nodeValue = object.value("type");
			if (nodeValue.isDouble())
			{
				linkModel.type = (JointType)(nodeValue.toInt());
			}
		}

		if (object.contains("path"))
		{
			QJsonValue nodeValue = object.value("path");
			if (nodeValue.isString())
			{
				linkModel.path = nodeValue.toString().toStdString();
			}
		}

		if (object.contains("alpha"))
		{
			QJsonValue nodeValue = object.value("alpha");
			if (nodeValue.isDouble())
			{
				linkModel.alpha = nodeValue.toDouble();
			}
		}

		if (object.contains("a"))
		{
			QJsonValue nodeValue = object.value("a");
			if (nodeValue.isDouble())
			{
				linkModel.a = nodeValue.toDouble();
			}
		}

		if (object.contains("theta"))
		{
			QJsonValue nodeValue = object.value("theta");
			if (nodeValue.isDouble())
			{
				linkModel.theta = nodeValue.toDouble();
			}
		}

		if (object.contains("d"))
		{
			QJsonValue nodeValue = object.value("d");
			if (nodeValue.isDouble())
			{
				linkModel.d = nodeValue.toDouble();
			}
		}

		if (object.contains("jointMin"))
		{
			QJsonValue nodeValue = object.value("jointMin");
			if (nodeValue.isDouble())
			{
				linkModel.jointMin = nodeValue.toDouble();
			}
		}

		if (object.contains("joinMax"))
		{
			QJsonValue nodeValue = object.value("joinMax");
			if (nodeValue.isDouble())
			{
				linkModel.jointMax = nodeValue.toDouble();
			}
		}

		return true;
	}
	return false;
}

