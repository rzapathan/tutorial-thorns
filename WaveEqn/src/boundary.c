#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>

// Update grid functions at boundary points
void WaveEqn_Boundary(CCTK_ARGUMENTS)
{
  DECLARE_CCTK_ARGUMENTS_WaveEqn_Boundary;  // Declare all grid functions from interface.ccl
  DECLARE_CCTK_PARAMETERS; // Declare all parameters from param.ccl

  const int gz = cctk_nghostzones[2];
  const int gy = cctk_nghostzones[1];
  const int gx = cctk_nghostzones[0];

  const CCTK_REAL dt = CCTK_DELTA_TIME;

  // Lower X Boundary
  if (cctk_bbox[0])
  {
    for (int k = 0; k < cctk_lsh[2]; k++) // loop over the z direction
    {
      for (int j = 0; j < cctk_lsh[1]; j++) // loop over the y direction
      {
        for (int i = 0; i < gx; i++) // loop over the x direction
        {
          const size_t ijk = CCTK_GFINDEX3D(cctkGH, i, j, k);
          U_rhs[ijk] = K[ijk];
          K_rhs[ijk] = 0.0;
        }
      }
    }
  }

  // Upper X Boundary
  if (cctk_bbox[1])
  {
    for (int k = 0; k < cctk_lsh[2]; k++) // loop over the z direction
    {
      for (int j = 0; j < cctk_lsh[1]; j++) // loop over the y direction
      {
        for (int i = cctk_lsh[0] - gx; i < cctk_lsh[0]; i++) // loop over the x direction
        {
          const size_t ijk = CCTK_GFINDEX3D(cctkGH, i, j, k);
          U_rhs[ijk] = K[ijk];
          K_rhs[ijk] = 0.0;
        }
      }
    }
  }

  // Lower Y Boundary
  if (cctk_bbox[2])
  {
    for (int k = 0; k < cctk_lsh[2]; k++) // loop over the z direction
    {
      for (int j = 0; j < gy; j++) // loop over the y direction
      {
        for (int i = 0; i < cctk_lsh[0]; i++) // loop over the x direction
        {
          const size_t ijk = CCTK_GFINDEX3D(cctkGH, i, j, k);
          U_rhs[ijk] = K[ijk];
          K_rhs[ijk] = 0.0;
        }
      }
    }
  }

  // Upper Y Boundary
  if (cctk_bbox[3])
  {
    for (int k = 0; k < cctk_lsh[2]; k++) // loop over the z direction
    {
      for (int j = cctk_lsh[1] - gy; j < cctk_lsh[1]; j++) // loop over the y direction
      {
        for (int i = 0; i < cctk_lsh[0]; i++) // loop over the x direction
        {
          const size_t ijk = CCTK_GFINDEX3D(cctkGH, i, j, k);
          U_rhs[ijk] = K[ijk];
          K_rhs[ijk] = 0.0;
        }
      }
    }
  }

  // Lower Z Boundary
  if (cctk_bbox[4])
  {
    for (int k = 0; k < gz; k++) // loop over the z direction
    {
      for (int j = 0; j < cctk_lsh[1]; j++) // loop over the y direction
      {
        for (int i = 0; i < cctk_lsh[0]; i++) // loop over the x direction
        {
          const size_t ijk = CCTK_GFINDEX3D(cctkGH, i, j, k);
          U_rhs[ijk] = K[ijk];
          K_rhs[ijk] = 0.0;
        }
      }
    }
  }
    
  // Upper Z Boundary
  if (cctk_bbox[5])
  {
    for (int k = cctk_lsh[2] - gz; k < cctk_lsh[2]; k++) // loop over the z direction
    {
      for (int j = 0; j < cctk_lsh[1]; j++) // loop over the y direction
      {
        for (int i = 0; i < cctk_lsh[0]; i++) // loop over the x direction
        {
          const size_t ijk = CCTK_GFINDEX3D(cctkGH, i, j, k);
          U_rhs[ijk] = K[ijk];
          K_rhs[ijk] = 0.0;
        }
      }
    }
  }
}