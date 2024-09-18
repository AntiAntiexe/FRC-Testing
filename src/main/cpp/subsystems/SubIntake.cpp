// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIntake.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DoubleSolenoid.h>

SubIntake::SubIntake() = default;

// This method will be called once per scheduler run
void SubIntake::Periodic() {
    frc::SmartDashboard::PutNumber("roller speed", _intakeMotor.Get());
    frc::SmartDashboard::PutBoolean("Intake Arm Down", solIntake.Get());
}

frc2::CommandPtr SubIntake::SpinFlywheel(){
    return StartEnd(
        [this]
        {
            _intakeMotor.Set(1);
        },
        [this]
        {
            _intakeMotor.Set(0);
        }
    ).Until(
        [this]
        {
            return _intakeSensor.Get();
        }

    );
}

// Extend Intake
frc2::CommandPtr SubIntake::ExtendIntake() {
  return RunOnce([this] { solIntake.Set(frc::DoubleSolenoid::kForward); });
}

frc2::CommandPtr SubIntake::RetractIntake() {
    return RunOnce([this] { solIntake.Set(frc::DoubleSolenoid::kOff); });
  
}




