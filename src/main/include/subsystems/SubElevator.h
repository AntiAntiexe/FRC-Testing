// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/SubsystemBase.h>
#include <frc2/command/Commands.h>
#include "utilities/ICSparkMax.h"
#include "Constants.h"
#include <frc/simulation/ElevatorSim.h>
#include <frc/system/plant/DCMotor.h>
#include <units/angle.h>
#include <units/moment_of_inertia.h>
#include <frc/simulation/ElevatorSim.h>


class SubElevator : public frc2::SubsystemBase {
 public:
  SubElevator();
  static SubElevator& GetInstance() {static SubElevator inst; return inst;}

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void SimulationPeriodic() override;
  bool AtTarget();
  units::angle::turn_t converter(units::meter_t height);
  units::radians_per_second_t convert2(units::meters_per_second_t mps, units::centimeter_t radius);
  frc2::CommandPtr GoTo(units::angle::turn_t rotations);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  ICSparkMax _elevatorMotor{canid::elevatorMotor};

  // constants
  static constexpr double GEARING = 20;
  static constexpr units::meter_t circumference = 62.831531_m;
  static constexpr units::centimeter_t radius = 10_cm;
  static constexpr units::meter_t maxHeight = 1_m;
  static constexpr units::meter_t minHeight = 0_m;

  // Simulation

  frc::sim::ElevatorSim _elevatorSim{frc::DCMotor::NEO(), GEARING, 5_kg, radius, minHeight, maxHeight, false, 0.5_m};
  // this needs to be fixed !!
};
