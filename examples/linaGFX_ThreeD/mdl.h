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
  0, 1, 0xff,
  1, 2, 0xff,
  2, 3, 0xff,
  3, 0, 0xff,
  4, 5, 0xff,
  5, 6, 0xff,
  6, 7, 0xff,
  7, 4, 0xff,
  0, 4, 0xff,
  1, 5, 0xff,
  2, 6, 0xff,
  3, 7, 0xff,
  0, 6, 0xff,
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
