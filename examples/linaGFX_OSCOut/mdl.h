static const uint16_t mdlpt = 8;
static const uint16_t lnkpt = 13;

MDL3D_T mdl[mdlpt] = {
  -1.0, -1.0,  1.0,
  1.0, -1.0,  1.0,
  1.0,  1.0,  1.0,
  -1.0,  1.0,  1.0,
  -1.0, -1.0, -1.0,
  1.0, -1.0, -1.0,
  1.0,  1.0, -1.0,
  -1.0,  1.0, -1.0,
};
LNK_T lnk[lnkpt] = {
  0, 1, 1,
  1, 2, 1,
  2, 3, 1,
  3, 0, 1,
  4, 5, 2,
  5, 6, 2,
  6, 7, 2,
  7, 4, 2,
  0, 4, 3,
  1, 5, 3,
  2, 6, 3,
  3, 7, 3,
  0, 6, 4,
};
MDL3D_T dst3d[mdlpt];
MDL2D_T dst2d[mdlpt];
MDL3D_T mv = {
  0.0,
  0.0,
  0.0
};
MDL3D_T view = {
  0.0,
  0.0,
 -5.0
};
