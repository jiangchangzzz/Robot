#include "Translate.h"

#include <QDir>
#include <QLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QList>
#include <QListView>
#include <QFileDialog>
#include <QApplication>
#include <QWidget>
#include <QStyleFactory>

#include <AIS_Shape.hxx>
#include <AIS_InteractiveObject.hxx>

#include <IGESControl_Reader.hxx>
#include <IGESControl_Writer.hxx>
#include <IGESControl_Controller.hxx>
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>
#include <STEPControl_StepModelType.hxx>
#include <Interface_Static.hxx>
//#include <Interface_TraceFile.hxx>

#include <StlAPI_Writer.hxx>
#include <VrmlAPI_Writer.hxx>

#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_HSequenceOfShape.hxx>

#include <Geom_Line.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Surface.hxx>


#include <Standard_ErrorHandler.hxx>
#include <Standard_CString.hxx>


Translate::Translate(QObject* parent)
	: QObject(parent)
{
}

Translate::~Translate()
{
}

QString Translate::info() const
{
	return myInfo;
}

bool Translate::importModel(const int format, const QString &fileName, const Handle(AIS_InteractiveContext)& ic)
{
	myInfo = QString();
	if (fileName.isEmpty())
		return true;

	if (!QFileInfo(fileName).exists())
	{
		myInfo = QObject::tr("INF_TRANSLATE_FILENOTFOUND").arg(fileName);
		return false;
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);
	Handle(TopTools_HSequenceOfShape) shapes = importModel(format, fileName);
	QApplication::restoreOverrideCursor();

	return displayShSequence(ic, shapes);
}

bool Translate::displayShSequence(const Handle(AIS_InteractiveContext)& ic,
	const Handle(TopTools_HSequenceOfShape)& shapes)
{
	if (shapes.IsNull() || !shapes->Length())
		return false;

	for (int i = 1; i <= shapes->Length(); i++)
		ic->Display(new AIS_Shape(shapes->Value(i)), false);
	ic->UpdateCurrentViewer();
	return true;
}

Handle(TopTools_HSequenceOfShape) Translate::importModel(const int format, const QString& file)
{
	Handle(TopTools_HSequenceOfShape) shapes;
	try {
		switch (format)
		{
		case FormatBREP:
			shapes = importBREP(file);
			break;
		case FormatIGES:
			shapes = importIGES(file);
			break;
		case FormatSTEP:
			shapes = importSTEP(file);
			break;
		}
	}
	catch (Standard_Failure) {
		shapes.Nullify();
	}
	return shapes;
}

Handle(TopTools_HSequenceOfShape) Translate::importModel(const QString & file)
{
	QFileInfo fileInfo(file);

	if (fileInfo.exists())
	{
		QString suffix = fileInfo.suffix();
		auto iter = FormatMap.find(suffix);
		if (iter != FormatMap.end())
		{
			FormatType format = iter->second;
			return importModel(format, file);
		}
	}
	return Handle(TopTools_HSequenceOfShape)();
}

bool Translate::exportModel(const int format, const QString fileName, const Handle(AIS_InteractiveContext)& ic)
{
	myInfo = QString();
	if (fileName.isEmpty())
		return true;

	Handle(TopTools_HSequenceOfShape) shapes = getShapes(ic);
	if (shapes.IsNull() || !shapes->Length())
		return false;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	bool stat = exportModel(format, fileName, shapes);
	QApplication::restoreOverrideCursor();

	return stat;
}

bool Translate::exportModel(const int format, const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes)
{
	try {
		switch (format)
		{
		case FormatBREP: return exportBREP(file, shapes);
		case FormatIGES: return exportIGES(file, shapes);
		case FormatSTEP: return exportSTEP(file, shapes);
		case FormatSTL:  return exportSTL(file, shapes);
		case FormatVRML: return exportVRML(file, shapes);
		}
	}
	catch (Standard_Failure) {
		//
	}
	return false;
}

Handle(TopTools_HSequenceOfShape) Translate::getShapes(const Handle(AIS_InteractiveContext)& ic)
{
	Handle(TopTools_HSequenceOfShape) aSequence;
	Handle(AIS_InteractiveObject) picked;
	for (ic->InitSelected(); ic->MoreSelected(); ic->NextSelected())
	{
		Handle(AIS_InteractiveObject) obj = ic->SelectedInteractive();
		if (obj->IsKind(STANDARD_TYPE(AIS_Shape)))
		{
			TopoDS_Shape shape = Handle(AIS_Shape)::DownCast(obj)->Shape();
			if (aSequence.IsNull())
				aSequence = new TopTools_HSequenceOfShape();
			aSequence->Append(shape);
		}
	}
	return aSequence;
}

// ----------------------------- Import functionality -----------------------------

Handle(TopTools_HSequenceOfShape) Translate::importBREP(const QString& file)
{
	Handle(TopTools_HSequenceOfShape) aSequence;
	TopoDS_Shape aShape;
	BRep_Builder aBuilder;
	TCollection_AsciiString  aFilePath = file.toUtf8().data();
	Standard_Boolean result = BRepTools::Read(aShape, aFilePath.ToCString(), aBuilder);
	if (result)
	{
		aSequence = new TopTools_HSequenceOfShape();
		aSequence->Append(aShape);
	}
	return aSequence;
}

Handle(TopTools_HSequenceOfShape) Translate::importIGES(const QString& file)
{
	Handle(TopTools_HSequenceOfShape) aSequence;
	TCollection_AsciiString  aFilePath = file.toUtf8().data();

	IGESControl_Reader Reader;
	int status = Reader.ReadFile(aFilePath.ToCString());

	if (status == IFSelect_RetDone)
	{
		aSequence = new TopTools_HSequenceOfShape();
		Reader.TransferRoots();
		TopoDS_Shape aShape = Reader.OneShape();
		aSequence->Append(aShape);
	}
	return aSequence;
}

Handle(TopTools_HSequenceOfShape) Translate::importSTEP(const QString& file)
{
	Handle(TopTools_HSequenceOfShape) aSequence;
	TCollection_AsciiString  aFilePath = file.toUtf8().data();
	STEPControl_Reader aReader;
	IFSelect_ReturnStatus status = aReader.ReadFile(aFilePath.ToCString());
	if (status == IFSelect_RetDone)
	{
		//Interface_TraceFile::SetDefault();
		bool failsonly = false;
		aReader.PrintCheckLoad(failsonly, IFSelect_ItemsByEntity);

		int nbr = aReader.NbRootsForTransfer();
		aReader.PrintCheckTransfer(failsonly, IFSelect_ItemsByEntity);
		for (Standard_Integer n = 1; n <= nbr; n++)
		{
			bool ok = aReader.TransferRoot(n);
			int nbs = aReader.NbShapes();
			if (ok == true && nbs > 0)
			{
				aSequence = new TopTools_HSequenceOfShape();
				for (int i = 1; i <= nbs; i++)
				{
					TopoDS_Shape shape = aReader.Shape(i);
					aSequence->Append(shape);
				}
			}
		}
	}
	return aSequence;
}

// ----------------------------- Export functionality -----------------------------

bool Translate::exportBREP(const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes)
{
	if (shapes.IsNull() || shapes->IsEmpty())
		return false;

	TopoDS_Shape shape = shapes->Value(1);

	const TCollection_AsciiString anUtf8Path(file.toUtf8().data());

	return BRepTools::Write(shape, anUtf8Path.ToCString());
}

bool Translate::exportIGES(const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes)
{
	if (shapes.IsNull() || shapes->IsEmpty())
		return false;

	IGESControl_Controller::Init();
	IGESControl_Writer writer(Interface_Static::CVal("XSTEP.iges.unit"),
		Interface_Static::IVal("XSTEP.iges.writebrep.mode"));

	for (int i = 1; i <= shapes->Length(); i++)
		writer.AddShape(shapes->Value(i));
	writer.ComputeModel();

	const TCollection_AsciiString anUtf8Path(file.toUtf8().data());

	return writer.Write(anUtf8Path.ToCString());
}

bool Translate::exportSTEP(const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes)
{
	if (shapes.IsNull() || shapes->IsEmpty())
		return false;

	STEPControl_StepModelType type = STEPControl_ManifoldSolidBrep;
	if (type < 0)
		return false;

	IFSelect_ReturnStatus status;

	if (type == STEPControl_FacetedBrep && !checkFacetedBrep(shapes))
	{
		myInfo = QObject::tr("INF_FACET_ERROR");
		return false;
	}

	STEPControl_Writer writer;
	for (int i = 1; i <= shapes->Length(); i++)
	{
		status = writer.Transfer(shapes->Value(i), type);
		if (status != IFSelect_RetDone)
			return false;
	}

	const TCollection_AsciiString anUtf8Path(file.toUtf8().data());

	status = writer.Write(anUtf8Path.ToCString());

	switch (status)
	{
	case IFSelect_RetError:
		myInfo = QObject::tr("INF_DATA_ERROR");
		break;
	case IFSelect_RetFail:
		myInfo = QObject::tr("INF_WRITING_ERROR");
		break;
	case IFSelect_RetVoid:
		myInfo = QObject::tr("INF_NOTHING_ERROR");
		break;
	case IFSelect_RetStop:
	case IFSelect_RetDone:
		break;
	}
	return status == IFSelect_RetDone;
}

bool Translate::exportSTL(const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes)
{
	if (shapes.IsNull() || shapes->IsEmpty())
		return false;

	TopoDS_Compound res;
	BRep_Builder builder;
	builder.MakeCompound(res);

	for (int i = 1; i <= shapes->Length(); i++)
	{
		TopoDS_Shape shape = shapes->Value(i);
		if (shape.IsNull())
		{
			myInfo = QObject::tr("INF_TRANSLATE_ERROR_INVALIDSHAPE");
			return false;
		}
		builder.Add(res, shape);
	}

	StlAPI_Writer writer;

	const TCollection_AsciiString anUtf8Path(file.toUtf8().data());

	writer.Write(res, anUtf8Path.ToCString());

	return true;
}

bool Translate::exportVRML(const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes)
{
	if (shapes.IsNull() || shapes->IsEmpty())
		return false;

	TopoDS_Compound res;
	BRep_Builder builder;
	builder.MakeCompound(res);

	for (int i = 1; i <= shapes->Length(); i++)
	{
		TopoDS_Shape shape = shapes->Value(i);
		if (shape.IsNull())
		{
			myInfo = QObject::tr("INF_TRANSLATE_ERROR_INVALIDSHAPE");
			return false;
		}
		builder.Add(res, shape);
	}

	VrmlAPI_Writer writer;

	const TCollection_AsciiString anUtf8Path(file.toUtf8().data());

	writer.Write(res, anUtf8Path.ToCString());

	return true;
}

bool Translate::checkFacetedBrep(const Handle(TopTools_HSequenceOfShape)& shapes)
{
	bool err = false;
	for (int i = 1; i <= shapes->Length(); i++)
	{
		TopoDS_Shape shape = shapes->Value(i);
		for (TopExp_Explorer fexp(shape, TopAbs_FACE); fexp.More() && !err; fexp.Next())
		{
			Handle(Geom_Surface) surface = BRep_Tool::Surface(TopoDS::Face(fexp.Current()));
			if (!surface->IsKind(STANDARD_TYPE(Geom_Plane)))
				err = true;
		}
		for (TopExp_Explorer eexp(shape, TopAbs_EDGE); eexp.More() && !err; eexp.Next())
		{
			Standard_Real fd, ld;
			Handle(Geom_Curve) curve = BRep_Tool::Curve(TopoDS::Edge(eexp.Current()), fd, ld);
			if (!curve->IsKind(STANDARD_TYPE(Geom_Line)))
				err = true;
		}
	}
	return !err;
}



