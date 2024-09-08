// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubElevator.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <utilities/ICSparkMax.h>
#include <frc/simulation/ElevatorSim.h>
#include <frc/RobotController.h>
#include <numbers>



SubElevator::SubElevator() {
    _elevatorMotor.SetConversionFactor(1.0/GEARING);
    _elevatorMotor.SetPIDFF(0, 0, 0, 0);
    frc::SmartDashboard::PutData("Elevator Motor", (wpi::Sendable*)&_elevatorMotor);
}

// This method will be called once per scheduler run
void SubElevator::Periodic() {
    frc::SmartDashboard::PutBoolean("Elevator on target", AtTarget());
}


frc2::CommandPtr SubElevator::GoTo(units::angle::turn_t rotations) {
    return RunOnce(
        [this, rotations]
        {
            _elevatorMotor.SetPositionTarget(rotations);
        }
    );
}

void SubElevator::SimulationPeriodic() {
    _elevatorSim.SetInputVoltage(_elevatorMotor.GetSimVoltage());


    _elevatorSim.Update(20_ms);

    _elevatorMotor.UpdateSimEncoder(converter(_elevatorSim.GetPosition()), convert2(_elevatorSim.GetVelocity(), radius));
      // this needs to be fixed !!
}

bool SubElevator::AtTarget() {
    return units::math::abs(_elevatorMotor.GetPosError()) < 1_tr;
}

units::angle::turn_t SubElevator::converter(units::meter_t height) {
    return (height/62.8318531).value()*1_tr;
}

units::radians_per_second_t SubElevator::convert2(units::meters_per_second_t mps, units::centimeter_t radius) {
    return mps/radius;
}
