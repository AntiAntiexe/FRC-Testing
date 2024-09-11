// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubShooter.h"
#include <frc/smartdashboard/SmartDashboard.h>


SubShooter::SubShooter() {
    frc::SmartDashboard::PutData("shooter motor", (wpi::Sendable*)&_shooterMotor);
    _shooterMotor.SetPIDFF(10.0, 0, 0, 0.13);
}

// This method will be called once per scheduler run
void SubShooter::Periodic() {
    frc::SmartDashboard::PutBoolean("Shooter on target", AtTarget());
}

frc2::CommandPtr SubShooter::SpinFlywheel(){
    return StartEnd(
        [this]
        {
            _shooterMotor.SetVelocityTarget(100_rpm);
        },
        [this]
        {
            _shooterMotor.Set(0);
        }
    );

}

bool SubShooter::AtTarget() {
    /*if (units::math::abs(_shooterMotor.GetVelError()) < 20_rpm) {
        return true;
    }
    else {
        return false;
    } is the same as what is below: */
    return units::math::abs(_shooterMotor.GetVelError()) < 20_rpm;
}

void SubShooter::SimulationPeriodic(){
    auto volts = _shooterMotor.GetSimVoltage();

    _flywheelSim.SetInputVoltage(volts);
    _flywheelSim.Update(20_ms);

    auto velocity = _flywheelSim.GetAngularVelocity();

    _shooterMotor.UpdateSimEncoder(0_deg, velocity);
}