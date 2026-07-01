#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>

// Initialize grid functions
void WaveEqn_Initialize(CCTK_ARGUMENTS)
{
  DECLARE_CCTK_ARGUMENTS_WaveEqn_Initialize;  // Declare all grid functions from interface.ccl
  DECLARE_CCTK_PARAMETERS; // Declare all parameters from param.ccl

  for (int k = 0; k < cctk_lsh[2]; k++) // loop over the z direction
  {
    for (int j = 0; j < cctk_lsh[1]; j++) // loop over the y direction
    {
      for (int i = 0; i < cctk_lsh[0]; i++) // loop over the x direction
      {
        const size_t ijk = CCTK_GFINDEX3D(cctkGH, i, j, k);
        U[ijk] = exp(-x[ijk] * x[ijk] - y[ijk] * y[ijk]);
        K[ijk] = 0.0;
      }
    }
  }
}