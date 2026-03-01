/******************************************************
**
** Copyright 2022 SMIT. All rights reserved.
**
** This file of part of the unified DB project
**
******************************************************/

#include <iostream>
#include <exception>
#include <QtGlobal>
#include <QByteArray>

#include "liblm_token.h"

extern void peInitAllServices();
extern void peRunApp(int argc, char **argv);

extern void plEval(const char *line);
extern void peBuildArgs(int argc, char** argv);
extern void pePrintArgsHelp();
extern bool peCheckIsClient();

/*********************************************************
 *
 * list all the form needed form the application
 *
 *********************************************************/
extern void pmCreateTabForm();
extern void edCreateFlattenShapeForm();
extern void edCreateFlattenInstanceForm();
extern void edCreateLayerBorderForm();
extern void pmCreatePropertyForm();
extern void pmCreateSearchForm();
extern void edCreateClipDesignForm();
extern void edCreateFlattenInstForm();
extern void edCreateBoolForm();
extern void ctCreateTraceForm();
extern void gmCreateMarkerForm();
extern void gmCreateDecodeForm();
extern void gmCreateRulerForm();
extern void xoCreateLVLForm();
extern void mdCreateMetalDensityForm();
extern void gmCreateRectForm();
extern void gmCreatePolyForm();
extern void gmCreateCircleForm();
extern void gmCreatePathForm();
extern void gmCreateTextForm();
extern void gmCreateInstForm();
extern void gmCreateMoveForm();
extern void gmCreatePartialForm();
extern void sqCreateSQLForm();
extern void gmCreatePrintScreenForm();
extern void gmCreateCheckBoundaryForm();
extern void xoCreateViewportLVLForm();
//extern void dcCreateDeviceCheckForm();
extern void bpCreateBooleanForm();
extern void edCreateMakeCellForm();
extern void edCreateSplitForm();
extern void edCreateCutShapeForm();
extern void edCreateRotateShapeForm();
extern void edCreateScaleShapeForm();
extern void edCreateCutCopyPasteForm();
extern void edCreateSnapForm();
extern void xoCreateBooleanXORForm();
extern void edCreateLayerChangeForm();
extern void edCreateMakeArrayForm();
extern void xoCreateSimpleBooleanForm();
extern void ctCreatePGTraceForm();
extern void edCreateStatisticsForm();
extern void edCreateIpScanForm();
extern void edCreateDeleteCellForm();
extern void edCreateOpenCellForm();
extern void edCreateCalculateAreaForm();
extern void edCreateImportForm();
extern void edCreateReplaceTextForm();
extern void edCreateSaveHierarchyForm();
extern void edCreateCharShapesForm();
extern void edCreateLoadImageForm();
extern void fraCreateFractureForm();
extern void ptmCreateCaptureForm();
extern void ptmCreateMatchForm();
extern void cntCreateImageForm();
#ifdef OPC
extern void opcCreateSimulationForm();
#endif
extern void mdCreateMaskForm();
extern void edCreatePadReportForm();
extern void edCreateSramForm();
extern void ptmCreateExtractFormZKFC();
extern void ptmCreateMatchFormZKFC();
#ifdef SZFC
extern void szfcCreateSramForm();
#endif
extern void jdvCreateTransformForm();
extern void jdvCreateAxisForm();
extern void ptmCreateSearchForm();

static void createForms()
{
    pmCreateTabForm();
    edCreateFlattenShapeForm();
    edCreateFlattenInstanceForm();
    edCreateLayerBorderForm();
    pmCreatePropertyForm();
    pmCreateSearchForm();
    edCreateClipDesignForm();
    edCreateFlattenInstForm();
    ctCreateTraceForm();
    gmCreateMarkerForm();
    gmCreateRulerForm();
    gmCreateDecodeForm();
    xoCreateLVLForm();
    mdCreateMetalDensityForm();
    gmCreateRectForm();
    gmCreatePolyForm();
    gmCreateCircleForm();
    gmCreatePathForm();
    gmCreateTextForm();
    gmCreateInstForm();
    gmCreatePartialForm();
    gmCreateMoveForm();
    gmCreateCheckBoundaryForm();
    sqCreateSQLForm();
    gmCreatePrintScreenForm();
    xoCreateViewportLVLForm();
//    dcCreateDeviceCheckForm();
    bpCreateBooleanForm();
    edCreateMakeCellForm();
    edCreateSplitForm();
    edCreateCutShapeForm();
    edCreateRotateShapeForm();
    edCreateScaleShapeForm();
    edCreateCutCopyPasteForm();
    edCreateSnapForm();
    xoCreateBooleanXORForm();
    edCreateLayerChangeForm();
    edCreateMakeArrayForm();
    xoCreateSimpleBooleanForm();
    ctCreatePGTraceForm();
    edCreateStatisticsForm();
    edCreateIpScanForm();
    edCreateDeleteCellForm();
    edCreateOpenCellForm();
    edCreateCalculateAreaForm();
    edCreateImportForm();
    edCreateReplaceTextForm();
    edCreateSaveHierarchyForm();
    edCreateCharShapesForm();
    edCreateLoadImageForm();
    fraCreateFractureForm();
    ptmCreateCaptureForm();
    ptmCreateMatchForm();
    cntCreateImageForm();
#ifdef OPC
    opcCreateSimulationForm();
#endif
    mdCreateMaskForm();
    edCreatePadReportForm();
    edCreateSramForm();
    ptmCreateExtractFormZKFC();
    ptmCreateMatchFormZKFC();
#ifdef SZFC
    szfcCreateSramForm();
#endif
    jdvCreateTransformForm();
    jdvCreateAxisForm();
    ptmCreateSearchForm();

    //in UserForm.pm
    #ifdef TCL
    #else
        plEval("smCreateAllUserForm();");
    #endif
} 

// load product only pm
static void loadPM()
{
    #ifdef TCL
    #else
        plEval("use smDB");
        plEval("use smBase");
        plEval("use Form");
        plEval("use saveAs");
        plEval("use dmDump");
        plEval("use dmLibExpand");
        plEval("use DRC");
        plEval("use hashFunc");
        plEval("use UserForm");
    #endif
}

int main(int argc, char **argv)
{
    // qputenv("LC_ALL", "en_US.UTF-8");

    try
    {
        peBuildArgs(argc, argv);
    }
    catch (const std::string &errStr)
    {
        if (errStr != "Error") {
            std::cout << "Error: " << errStr << std::endl;
            std::cout << std::endl;
        }
        pePrintArgsHelp();
    }

    if(peCheckIsClient())
        return 0;

    {
#if 1
        // "lic::init()" call only once within the program
        if(static_cast<lic::eStatus>(lic::init()) != lic::ELIC_SUCCESS) {
            printf("init license server failed.\n");
            return 0;
        }

        lmToken lmt("GWX_EDITOR");
        if (!lmt.checkOut())
            return 0;
#endif
        peInitAllServices();
        loadPM();
        createForms();
        peRunApp(argc, argv);
    }
    // "lic::quit()" call only once within the program
    lic::quit();
}
