#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>

// Register variables with MoL
void WaveEqn_MoLRegister(CCTK_ARGUMENTS)
{
  DECLARE_CCTK_ARGUMENTS_WaveEqn_MoLRegister;  // Declare all grid functions from interface.ccl
  CCTK_INT ierr = 0, group, rhs;

  // Look up the group index of the evol_group
  group = CCTK_GroupIndex ("WaveEqn::evol_group");
  
  // Look up the group index of the rhs_group
  rhs = CCTK_GroupIndex ("WaveEqn::rhs_group");

  if (CCTK_IsFunctionAliased ("MoLRegisterEvolvedGroup"))
  {
    // *** KEY STEP! *** Tell MoL what we variables
    // we are evolving and what the rhs variables are.
    ierr += MoLRegisterEvolvedGroup(group, rhs);
  }
  else
  {
    CCTK_WARN (0, "MoL function not aliased !");
    ierr++;
  }

  if (ierr)
  {
    CCTK_WARN(CCTK_WARN_ABORT, "Problems registering with MoL !");
  }
}