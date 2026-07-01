#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>
#include <stdio.h>

// Update grid functions at interior points
void HeatEqn_Update(CCTK_ARGUMENTS)
{
  DECLARE_CCTK_ARGUMENTS_HeatEqn_Update;  // Declare all grid functions from interface.ccl
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

        // U_p is the value of U at the previous time step. We have access to this because we declared
        // evol_group to have TIMELEVELS=2.

        const CCTK_REAL laplacian_U = (U_p[ip1jk] + U_p[im1jk] - 2 * U_p[ijk]) / (dx * dx)
                                    + (U_p[ijp1k] + U_p[ijm1k] - 2 * U_p[ijk]) / (dy * dy)
                                    + (U_p[ijkp1] + U_p[ijkm1] - 2 * U_p[ijk]) / (dz * dz);

        U[ijk] = U_p[ijk] + dt * laplacian_U;
      }
    }
  }
}
