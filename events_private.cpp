#include "hpp-files/Events.hpp"

void Events::UpdateVariables()
{
	PlayerPointer = entitiesOBJ->ReturnPlayerPointer();
	InfoPlayer = entitiesOBJ->ReturnPlayerOBJ();
}

void Events::mvright(int Force)
{
	if (PlayerPointer->xForce <= MaxForce)
		PlayerPointer->xForce += Force;
}

void Events::mvleft(int Force)
{
	if (PlayerPointer->xForce >= MaxForce * -1)
		PlayerPointer->xForce -= Force;
}

void Events::JumpStraight()
{
	if (!InfoPlayer->inJump)
	{
		if (PlayerPointer->yForce == 0)
			PlayerPointer->yForce -= JUMPHEIGHT;
	}
}

void Events::Jump()
{
	if (!InfoPlayer->inJump)
	{
		if (PlayerPointer->yForce == 0)
			PlayerPointer->yForce -= JUMPHEIGHT;

		if (InfoPlayer->LastMovement == 'd')
			mvright(JUMPHEIGHT);
		else
			mvleft(JUMPHEIGHT);
	}
}

void Events::HandleHitTarget(ens shooter, ens target)
{
	if (shooter->type == player)
	{
		InfoPlayer->colpi--;
	}

	entitiesOBJ->KillEntity(target);
}

bool Events::checkIfValidShoot(char obstacle, ens shooter)
{
	return obstacle != HORIZONTAL_WALL &&
		   obstacle != VERTICAL_WALL &&
		   obstacle != FULLFILL_POINT &&
		   (InfoPlayer->colpi > 0 || shooter->type == enemy);
}

void Events::HandleValidShot(ens shooter, int x, int y, char lastMovement)
{
	ens shot = entitiesOBJ->Insert(shoot, x, y, shooter->mappa, shooter->livello);

	if (shooter->type == player)
	{
		shot->xForce = (lastMovement == 'd') ? InfoPlayer->bulletRange : (-1 * InfoPlayer->bulletRange);
		InfoPlayer->colpi--;
	}
	else
	{
		shot->xForce = (lastMovement == 'd') ? MAX_BULLET_RANGE : -MAX_BULLET_RANGE;
	}
}
