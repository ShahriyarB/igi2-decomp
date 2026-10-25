// source: e/3/pc/pc_direct3drender.c  [override: the original skins bone vertices with SSE
// intrinsics the decompiler cannot express; the x87 path computes the same transform]
long __cdecl Direct3DRender_ProcessVerticesBone_SSE(struct Direct3DRender_BoneMesh_t *ptSource,
                                                    struct LODVirModel_s *ptLODVirModel,
                                                    struct BoneDynCubeObj_s *ptBoneObj, long iLOD)
{
  return Direct3DRender_ProcessVerticesBone(ptSource, ptLODVirModel, ptBoneObj, iLOD);
}
