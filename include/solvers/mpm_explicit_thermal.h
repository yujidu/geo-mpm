#ifndef MPM_MPM_EXPLICIT_THERMAL_H_
#define MPM_MPM_EXPLICIT_THERMAL_H_

#ifdef USE_GRAPH_PARTITIONING
#include "graph.h"
#endif

#include "mpm_base.h"

namespace mpm {

//! MPMExplicitThermal class
//! \brief A class that implements the fully explicit one phase thermal-mechanical mpm
//! \details A single-phase thermal-mechanical explicit MPM
//! \tparam Tdim Dimension
template <unsigned Tdim>
class MPMExplicitThermal : public MPMBase<Tdim> {
 public:
  //! Default constructor
  MPMExplicitThermal(const std::shared_ptr<IO>& io);

  //! Solve
  bool solve() override;

  //! Compute stress strain
  //! \param[in] phase Phase to smooth pressure
  void compute_stress_strain();

  // Compute time step size
  void compute_critical_timestep_size(double dt);

 protected:
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
  //! Interface scheme
  using mpm::MPMBase<Tdim>::contact_;

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
  //! Nonlocal cell neighbourhood
  using mpm::MPMBase<Tdim>::cell_neighbourhood_;
  //! Absorbing Boundary
  using mpm::MPMBase<Tdim>::absorbing_boundary_;
  
 private:
  //! Pressure smoothing
  bool pressure_smoothing_{false};
  //! Solver begin time
  std::chrono::time_point<std::chrono::steady_clock> solver_begin;

  // Current time
  double current_time_{0};
  // Output number
  int No_output{0};
  //! Compute free surface
  std::string free_surface_detection_;
  //! Volume tolerance for free surface
  double fs_vol_tolerance_{0.25};
  //! Virtual flux
  bool virtual_flux_{false};
  // Flux type
  std::string flux_type_{"convective"};
  // Heat transfer coeff
  double heat_transfer_coeff_{0};
  // Ambient temperature
  double ambient_temperature_{0};
  // Conductive flux
  double flux_{0};

};  // MPMExplicitThermal class
}  // namespace mpm

#include "mpm_explicit_thermal.tcc"

#endif  // MPM_MPM_EXPLICIT_THERMAL_H_
