// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/Commands.h>
#include <frc2/command/Command.h>
#include "subsystems/SubShooter.h"
#include "subsystems/SubFeeder.h"
#include "subsystems/SubTurret.h"

#include "commands/ShootingCommands.h"

RobotContainer::RobotContainer() {
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
  _controller.A().WhileTrue(cmd::ShootSequence());

  _controller.X().OnTrue(SubTurret::GetInstance().TurnTo(30_deg));
  _controller.Y().OnTrue(SubTurret::GetInstance().TurnTo(0_deg));
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return frc2::cmd::Print("No autonomous command configured");
}
