// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubElevator.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <utilities/ICSparkMax.h>

SubElevator::SubElevator() {
    _elevatorMotor.SetConversionFactor(1.0/GEARING);
    _elevatorMotor.SetPIDFF(0, 0, 0, 0);
    frc::SmartDashboard::PutData("Elevator Motor", (wpi::Sendable*)&_elevatorMotor);
}

// This method will be called once per scheduler run
void SubElevator::Periodic() {
    frc::SmartDashboard::PutBoolean("Elevator on target", AtTarget());
}


frc2::CommandPtr SubElevator::UpTo(units::degree_t angle) {
    return RunOnce(
        [this, angle]
        {
            _elevatorMotor.SetPositionTarget(angle);
        }
    );
}

void SubElevator::SimulationPeriodic() {
    _elevatorSim.SetInputVoltage(_elevatorMotor.GetSimVoltage());


    _elevatorSim.Update(20_ms);

    _elevatorSim.(_elevatorSim.GetAngularPosition(), _elevatorSim.GetAngularVelocity());
      // this needs to be fixed !!
}

bool SubElevator::AtTarget() {
    return units::math::abs(_elevatorMotor.GetPosError()) < 1_deg;
}
