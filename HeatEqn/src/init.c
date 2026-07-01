#include <math.h>
#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>
#include <stdio.h>

void HeatEqn_Initialize(CCTK_ARGUMENTS)
{
    DECLARE_CCTK_ARGUMENTS_HeatEqn_Initialize;
    DECLARE_CCTK_PARAMETERS;


    for (int k = 0; k < cctk_lsh[2]; k++) {
        for (int j = 0; j < cctk_lsh[1]; j++) {
            for (int i = 0; i < cctk_lsh[0]; i++) {
                const size_t ijk = CCTK_GFINDEX3D(cctkGH, i, j, k);
                U[ijk] = exp(0.1 * (-x[ijk] * x[ijk] - y[ijk] * y[ijk] - z[ijk] * z[ijk]));
            }
        }
    }
}
