#ifndef MPM_MPM_IMPLICIT_THERMAL_H_
#define MPM_MPM_IMPLICIT_THERMAL_H_

#ifdef USE_GRAPH_PARTITIONING
#include "graph.h"
#endif

#include "mpm_base.h"

#include "assembler_base.h"
#include "convergence_criterion_base.h"
#include "convergence_criterion_residual.h"
#include "convergence_criterion_solution.h"
#include "solver_base.h"

namespace mpm {

//! MPMImplicitThermal class
//! \brief A class that implements the fully implicit one phase mpm
//! \details A single-phase implicit MPM
//! \tparam Tdim Dimension
template <unsigned Tdim>
class MPMImplicitThermal : public MPMBase<Tdim> {
 public:
  //! Default constructor
  MPMImplicitThermal(const std::shared_ptr<IO>& io);

  //! Solve
  bool solve() override;

  //! Class private functions
 private:
  /**
   * \defgroup Implicit Functions dealing with implicit MPM
   */
  /**@{*/
  //! Initialise matrix
  //! \ingroup Implicit
  bool initialise_matrix();

  //! Initialise matrix
  //! \ingroup Implicit
  bool reinitialise_matrix();

  //! Reinitialise equilibrium equation
  //! \ingroup Implicit
  void reinitialise_system_equation();

  //! Assemble equilibrium equation
  //! \ingroup Implicit
  bool assemble_system_equation();

  //! Solve equilibrium equation
  //! \ingroup Implicit
  bool solve_system_equation();

  //! Initialisation of Newton-Raphson iteration
  //! \ingroup Implicit
  void initialise_newton_raphson_iteration();

  //! Check convergence of Newton-Raphson iteration
  //! \ingroup Implicit
  bool check_newton_raphson_convergence();

  //! Finalisation of Newton-Raphson iteration
  //! \ingroup Implicit
  void finalise_newton_raphson_iteration();
  /**@}*/

  //! Class private variables
 private:
  // Generate a unique id for the analysis
  using mpm::MPMBase<Tdim>::uuid_;
  //! Time step size
  using mpm::MPMBase<Tdim>::dt_;
  //! Current step
  using mpm::MPMBase<Tdim>::step_;
  //! Number of steps
  using mpm::MPMBase<Tdim>::nsteps_;
  //! Number of steps
  using mpm::MPMBase<Tdim>::nload_balance_steps_;
  //! Output steps
  using mpm::MPMBase<Tdim>::output_steps_;
  //! A unique ptr to IO object
  using mpm::MPMBase<Tdim>::io_;
  //! JSON analysis object
  using mpm::MPMBase<Tdim>::analysis_;
  //! JSON post-process object
  using mpm::MPMBase<Tdim>::post_process_;
  //! Logger
  using mpm::MPMBase<Tdim>::console_;
  //! MPM Scheme
  using mpm::MPMBase<Tdim>::mpm_scheme_;
  //! Stress update method
  using mpm::MPMBase<Tdim>::stress_update_;

#ifdef USE_GRAPH_PARTITIONING
  //! Graph
  using mpm::MPMBase<Tdim>::graph_;
#endif

  //! velocity update
  using mpm::MPMBase<Tdim>::velocity_update_;
  //! FLIP-PIC blending ratio
  using mpm::MPMBase<Tdim>::blending_ratio_;
  //! Gravity
  using mpm::MPMBase<Tdim>::gravity_;
  //! Mesh object
  using mpm::MPMBase<Tdim>::mesh_;
  //! Materials
  using mpm::MPMBase<Tdim>::materials_;
  //! Node concentrated force
  using mpm::MPMBase<Tdim>::set_node_concentrated_force_;
  //! Damping type
  using mpm::MPMBase<Tdim>::damping_type_;
  //! Damping factor
  using mpm::MPMBase<Tdim>::damping_factor_;
  //! Locate particles
  using mpm::MPMBase<Tdim>::locate_particles_;
  //! Nonlocal node neighbourhood
  using mpm::MPMBase<Tdim>::node_neighbourhood_;
  //! Nonlocal cell neighbourhood
  using mpm::MPMBase<Tdim>::cell_neighbourhood_;  
  //! Pressure smoothing
  bool pressure_smoothing_{false};

  /**
   * \defgroup ImplicitVariables Variables dealing with implicit MPM
   */
  /**@{*/
  //! Phase
  const unsigned phase_{mpm::ParticlePhase::SinglePhase};
  //! Boolean of nonlinear analysis
  bool nonlinear_{true};
  //! Boolean of quasi-static analysis
  bool quasi_static_{false};
  //! Parameter beta of Newmark scheme
  double newmark_beta_{0.25};
  //! Parameter gamma of Newmark scheme
  double newmark_gamma_{0.5};
  //! Current number of Newton-Raphson iteration
  unsigned current_iteration_;
  //! Max number of Newton-Raphson iteration
  unsigned max_iteration_{20};
  //! Verbosity for Newton-Raphson iteration
  unsigned verbosity_{0};
  //! Assembler object
  std::shared_ptr<mpm::AssemblerBase<Tdim>> assembler_;
  //! Linear solver object
  tsl::robin_map<std::string,
                 std::shared_ptr<mpm::SolverBase<Eigen::SparseMatrix<double>>>>
      linear_solver_;
  //! Newton-Raphson solution increment convergence
  std::shared_ptr<mpm::ConvergenceCriterionBase> displacement_criterion_{nullptr};
  //! Newton-Raphson solution increment convergence
  std::shared_ptr<mpm::ConvergenceCriterionBase> temperature_criterion_{nullptr};  
  //! Newton-Raphson residual convergence
  std::shared_ptr<mpm::ConvergenceCriterionBase> residual_criterion_{nullptr};
  // Current time
  double current_time_{0};
  //! Compute free surface
  std::string free_surface_detection_;
  //! Volume tolerance for free surface
  double fs_vol_tolerance_{0.25};
  //! Virtual flux
  bool virtual_flux_{false};
  // Flux type
  std::string flux_type_{"convective"};
  // Heat transfer coeff
  double vfm_param1_{0};
  // Ambient temperature
  double vfm_param2_{0};
  /**@}*/

};  // MPMImplicitThermal class
}  // namespace mpm

#include "mpm_implicit_thermal.tcc"

#endif  // MPM_MPM_IMPLICIT_H_
