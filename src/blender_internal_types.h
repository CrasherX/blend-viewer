#ifndef BLENDER_INTERNAL_TYPES_H
#define BLENDER_INTERNAL_TYPES_H

enum block_type_e {
    block_IDProperty = 24,
    block_PreviewImage = 32,
    block_Object = 35,
    block_Image = 48,
    block_Scene = 55,
    block_RenderSlot = 60,
    block_Stereo3dFormat = 64,
    block_CurveMapping = 70,
    block_bNodeTree = 71,
    block_Material = 77,
    block_Mesh = 95,
    block_MPoly = 98,
    block_MLoop = 99,
    block_MLoopUV = 100,
    block_MVert = 105,
    block_MEdge = 106,
    block_Collection = 229,
    block_World = 245,
    block_SceneRenderView = 251,
    block_PaintToolSlot = 260,
    block_Brush = 261,
    block_Sculpt = 267,
    block_GpPaint = 269,
    block_VPaint = 270,
    block_ToolSettings = 279,
    block_Base = 288,
    block_Editing = 290,
    block_RegionView3D = 294,
    block_View3D = 301,
    block_SpaceInfo = 305,
    block_SpaceButs = 306,
    block_SpaceOops = 307,
    block_TreeStoreElem = 309,
    block_FileSelectParams = 319,
    block_SpaceFile = 320,
    block_SpaceImage = 324,
    block_SpaceText = 327,
    block_bNodeTreePath = 330,
    block_SpaceNode = 332,
    block_ConsoleLine = 334,
    block_SpaceConsole = 335,
    block_bScreen = 362,
    block_ARegion = 363,
    block_ScrVert = 365,
    block_ScrEdge = 366,
    block_Panel = 368,
    block_bToolRef = 378,
    block_ScrArea = 379,
    block_FileGlobal = 386,
    block_ViewLayer = 387,
    block_TreeStore = 422,
    block_CollectionObject = 423,
    block_CollectionChild = 424,
    block_SpaceAction = 439,
    block_bNodeSocket = 477,
    block_bNodeLink = 479,
    block_bNode = 480,
    block_CurveMapPoint = 551,
    block_BrushGpencilSettings = 554,
    block_CustomDataLayer = 558,
    block_wmWindowManager = 620,
    block_wmWindow = 621,
    block_WorkSpaceInstanceHook = 625,
    block_FreestyleLineSet = 697,
    block_FreestyleLineStyle = 698,
    block_LineStyleGeometryModifier_Sampling = 725,
    block_LayerCollection = 745,
    block_WorkSpaceLayout = 748,
    block_WorkSpace = 750,
    block_WorkSpaceDataRelation = 751,
};

enum field_type_e {
    field_flag = 22,
    field_id = 52,
    field_totvert = 77,
    field_adt = 98,
    field_ipo = 103,
    field_runtime = 175,
    field_size = 234,
    field_loc = 360,
    field_mat = 476,
    field_totcol = 478,
    field_texflag = 479,
    field_key = 524,
    field_mselect = 590,
    field_mpoly = 591,
    field_mloop = 592,
    field_mloopuv = 593,
    field_mloopcol = 594,
    field_mface = 595,
    field_mtface = 596,
    field_tface = 597,
    field_mvert = 598,
    field_medge = 599,
    field_dvert = 600,
    field_mcol = 601,
    field_texcomesh = 602,
    field_edit_mesh = 603,
    field_vdata = 604,
    field_edata = 605,
    field_fdata = 606,
    field_pdata = 607,
    field_ldata = 608,
    field_totedge = 609,
    field_totface = 610,
    field_totselect = 611,
    field_totpoly = 612,
    field_totloop = 613,
    field_act_face = 614,
    field_smoothresh = 615,
    field_cd_flag = 616,
    field__pad = 617,
    field_subdiv = 618,
    field_subdivr = 619,
    field_subsurftype = 620,
    field_editflag = 621,
    field_remesh_voxel_size = 622,
    field_remesh_voxel_adaptivity = 623,
    field_remesh_mode = 624,
    field__pad1 = 625,
    field_mr = 626,
};

#endif // BLENDER_INTERNAL_TYPES_H
