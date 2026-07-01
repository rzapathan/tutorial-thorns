#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>

// Initialize grid functions

void WaveEqn_Initialize(CCTK_ARGUMENTS)
{
    DECLARE_CCTK_ARUGMENTS_WaveEqn_Initialize; // declare all grid fns from interface.ccl

    for (int k = 0; k < cctk_lsh[2]; k++) // loop over the z dir
    {
        for (int j = 0; j < cctk_lsh[1]; j++) // y dir
        {
            for (int i = 0; i < cctk_lsh[1]; i++) // x dir
            {
                const size_t ijk = CCTK_GFINDEX3D(cctkGH, i, j, k);
                U[ijk] = exp( -x[ijk] * x[ijk] - y[ijk] * y[ijk])
                k[ijk] = -0.0;
            }
        }
    }
}