#pragma once

namespace canid {
    constexpr int shooterMotor = 1;
    constexpr int feederMotor = 2;
    constexpr int turretMotor = 3;
    constexpr int rollerMotor = 4;
}

namespace doi {
    constexpr int intakeDOI = 0;
}

namespace pcm1 {
     //Intake
    constexpr int IntakeExtend = 0;
    constexpr int IntakeRetract = 1;

    constexpr int Pcm1Id = 22; //same ID as ClimberRightLaserCan

}