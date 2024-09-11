// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubTurret.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubTurret::SubTurret() {
    _turretMotor.SetConversionFactor(1.0/GEARING);
    _turretMotor.SetPIDFF(10, 0.0, 0.1, 0.0);
    frc::SmartDashboard::PutData("Turret Motor", (wpi::Sendable*)&_turretMotor);
}

// This method will be called once per scheduler run
void SubTurret::Periodic() {
    frc::SmartDashboard::PutBoolean("Turret on target", AtTarget());
}

frc2::CommandPtr SubTurret::TurnTo(units::degree_t angle) {
    return RunOnce(
        [this, angle]
        {
            _turretMotor.SetPositionTarget(angle);
        });
}


void SubTurret::SimulationPeriodic() {

    _turretSim.SetInputVoltage(_turretMotor.GetSimVoltage());


    _turretSim.Update(20_ms);

    _turretMotor.UpdateSimEncoder(_turretSim.GetAngularPosition(), _turretSim.GetAngularVelocity());

}

bool SubTurret::AtTarget() {
    return units::math::abs(_turretMotor.GetPosError()) < 1_deg;
}
