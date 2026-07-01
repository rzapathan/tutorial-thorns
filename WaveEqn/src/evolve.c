#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>

// Update RHS functions
void WaveEqn_RHS(CCTK_ARGUMENTS)
{
  DECLARE_CCTK_ARGUMENTS_WaveEqn_RHS;  // Declare all grid functions from interface.ccl
  DECLARE_CCTK_PARAMETERS; // Declare all parameters from param.ccl

  const int gz = cctk_nghostzones[2];
  const int gy = cctk_nghostzones[1];
  const int gx = cctk_nghostzones[0];

  const CCTK_REAL dt = CCTK_DELTA_TIME;

  const CCTK_REAL dx = CCTK_DELTA_SPACE(0);
  const CCTK_REAL dy = CCTK_DELTA_SPACE(1);
  const CCTK_REAL dz = CCTK_DELTA_SPACE(2);

  for (int k = gz; k < cctk_lsh[2] - gz; k++) // loop over the z direction
  {
    for (int j = gy; j < cctk_lsh[1] - gy; j++) // loop over the y direction
    {
      for (int i = gx; i < cctk_lsh[0] - gx; i++) // loop over the x direction
      {
        const size_t ijk = CCTK_GFINDEX3D(cctkGH, i, j, k);
        const size_t ip1jk = CCTK_GFINDEX3D(cctkGH, i + 1, j, k);
        const size_t im1jk = CCTK_GFINDEX3D(cctkGH, i - 1, j, k);
        const size_t ijp1k = CCTK_GFINDEX3D(cctkGH, i, j + 1, k);
        const size_t ijm1k = CCTK_GFINDEX3D(cctkGH, i, j - 1, k);
        const size_t ijkp1 = CCTK_GFINDEX3D(cctkGH, i, j, k + 1);
        const size_t ijkm1 = CCTK_GFINDEX3D(cctkGH, i, j, k - 1);

        const CCTK_REAL laplacian_U = (U[ip1jk] + U[im1jk] - 2 * U[ijk]) / (dx * dx)
                                    + (U[ijp1k] + U[ijm1k] - 2 * U[ijk]) / (dy * dy)
                                    + (U[ijkp1] + U[ijkm1] - 2 * U[ijk]) / (dz * dz);

        U_rhs[ijk] = K[ijk];
        K_rhs[ijk] = laplacian_U;
      }
    }
  }
}