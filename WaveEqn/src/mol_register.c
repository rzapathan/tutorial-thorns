#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>


// Register variables w MoL
void WaveEqn_MolRegister(CCTK_ARGUMENTS)
{
    DECLARE_CCTK_ARGUMENTS_WaveEqn_MolRegister; //declaring grid fns from interface
    CCTK_INT ierr = 0, group, rhs;

    // Look up at the group index of the evol_group
    rhs = CCTK_GroupIndex ("WaveEqn::rhs_group");

    if (CCTK_IsFunctionAliased ("MoLRegisterEvolvedGroup"))
    {
        // *** key step *** tell MoL what vars we're evolving & what rhs vars are
        ierr += MolRegisterEvolvedGroup(group,rhs);
    }
    else 
    {
        CCTK_WARN (0, "MoL function not aliased !");
        ierr++
    }

    if (ierr) {
        CCTK_WARN(CCTK_WARN_ABORT, "Problems registering with MoL")
    }

}