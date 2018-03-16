#pragma once

#include <unordered_map>

#include <QObject>

#include <AIS_InteractiveContext.hxx>
#include <TopTools_HSequenceOfShape.hxx>

class Translate : public QObject
{
	Q_OBJECT

public:
	enum FormatType{ FormatBREP, FormatIGES, FormatSTEP, FormatVRML, FormatSTL };

	//根据文件后缀名判断文件类型
	const std::map < QString, FormatType > FormatMap= { 
		{ "STEP", FormatSTEP } };

	Translate(QObject*);
	~Translate();

	QString                               info() const;

	bool importModel(const int format, const QString &path, const Handle(AIS_InteractiveContext)& ic);

	Handle(TopTools_HSequenceOfShape) importModel(const int format, const QString & file);

	Handle(TopTools_HSequenceOfShape) importModel(const QString & file);

	bool exportModel(const int format, const QString fileName, const Handle(AIS_InteractiveContext)& ic);

	bool exportModel(const int format, const QString & file, const Handle(TopTools_HSequenceOfShape)& shapes);

	bool displayShSequence(const Handle(AIS_InteractiveContext)& ic, const Handle(TopTools_HSequenceOfShape)& shapes);

	Handle(TopTools_HSequenceOfShape) getShapes(const Handle(AIS_InteractiveContext)& ic);

private:
	Handle(TopTools_HSequenceOfShape)         importBREP(const QString&);

	Handle(TopTools_HSequenceOfShape)         importIGES(const QString&);

	Handle(TopTools_HSequenceOfShape)         importSTEP(const QString&);

	bool exportBREP(const QString & file, const Handle(TopTools_HSequenceOfShape)& shapes);

	bool exportIGES(const QString & file, const Handle(TopTools_HSequenceOfShape)& shapes);

	bool exportSTEP(const QString & file, const Handle(TopTools_HSequenceOfShape)& shapes);

	bool exportSTL(const QString & file, const Handle(TopTools_HSequenceOfShape)& shapes);

	bool exportVRML(const QString & file, const Handle(TopTools_HSequenceOfShape)& shapes);

	bool checkFacetedBrep(const Handle(TopTools_HSequenceOfShape)& shapes);

protected:
	QString                           myInfo;
};