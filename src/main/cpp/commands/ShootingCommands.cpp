#include "commands/ShootingCommands.h"

#include "subsystems/SubFeeder.h"
#include "subsystems/SubShooter.h"
#include "subsystems/SubTurret.h"
#include "subsystems/SubIntake.h"



namespace cmd {
    using namespace frc2::cmd;
    frc2::CommandPtr ShootSequence() {
        return Parallel(
            SubShooter::GetInstance().SpinFlywheel(),
            SubTurret::GetInstance().TurnTo(30_deg),
            Sequence(
                WaitUntil([] {return SubShooter::GetInstance().AtTarget();}),
                WaitUntil([] {return SubTurret::GetInstance().AtTarget();}),
                SubFeeder::GetInstance().SpinFlywheel()
            )
        );
    }


}