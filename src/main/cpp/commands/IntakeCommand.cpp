#include "commands/ShootingCommands.h"

#include "subsystems/SubFeeder.h"
#include "subsystems/SubShooter.h"
#include "subsystems/SubTurret.h"
#include "subsystems/SubIntake.h"

namespace icmd {
    using namespace frc2::cmd;
    frc2::CommandPtr IntakeSequence() {
        return Sequence(
            SubIntake::GetInstance().ExtendIntake(),
            SubIntake::GetInstance().SpinFlywheel(),
            SubIntake::GetInstance().RetractIntake()

        );
        
    }


}