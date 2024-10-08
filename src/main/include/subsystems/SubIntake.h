// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc2/command/Commands.h>
#include "Constants.h"
#include <frc/DigitalInput.h>

#include <frc/DoubleSolenoid.h>
#include <frc/simulation/DIOSim.h>
#include <frc/DigitalInput.h>

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc2/command/commands.h>
#include <frc/DoubleSolenoid.h>
#include <frc/DigitalInput.h>
#include <frc/simulation/DIOSim.h>

class SubIntake : public frc2::SubsystemBase {
 public:
 static SubIntake& GetInstance() {static SubIntake inst; return inst;}
  SubIntake();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  frc2::CommandPtr SpinFlywheel();
  frc2::CommandPtr ExtendIntake();
  frc2::CommandPtr RetractIntake();

  
  


 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax _intakeMotor{canid::rollerMotor, rev::CANSparkLowLevel::MotorType::kBrushless};
  frc::DigitalInput _intakeSensor{doi::intakeDOI};
  
  frc::DoubleSolenoid solIntake{pcm1::Pcm1Id, frc::PneumaticsModuleType::REVPH,
                                pcm1::IntakeExtend, pcm1::IntakeRetract};
};
