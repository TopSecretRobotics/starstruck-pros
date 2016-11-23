#include "main.h"

/*
 * Basic X-Drive Declarations
 */

typedef struct basicDrive_s {
  drivemotor_t frontRight;
  drivemotor_t frontLeft;
  drivemotor_t backRight;
  drivemotor_t backLeft;
} basicDrive_t;

static void basicDriveTick(void *data);

static basicDrive_t basicDriveData = {
  {3, DRIVEMOTOR_SIDE_RIGHT, true }, // frontRight
  {5, DRIVEMOTOR_SIDE_LEFT,  false}, // frontLeft
  {2, DRIVEMOTOR_SIDE_RIGHT, true }, // backRight
  {4, DRIVEMOTOR_SIDE_LEFT,  false}, // backLeft
};

/*
 * Holonomic X-Drive Declarations
 */

#define PI 3.14159265358979

#define HOLONOMIC_DEADBAND 20

typedef struct holonomicDrive_s {
  drivemotor_t frontRight;
  drivemotor_t frontLeft;
  drivemotor_t rearRight;
  drivemotor_t rearLeft;
} holonomicDrive_t;

static void holonomicDriveTick(void *data);
static void holonomicDriveSet(void *data, double radians, double speed, int rotation);

static holonomicDrive_t holonomicDriveData = {
  {3, DRIVEMOTOR_SIDE_RIGHT, true }, // frontRight
  {5, DRIVEMOTOR_SIDE_LEFT,  false}, // frontLeft
  {2, DRIVEMOTOR_SIDE_RIGHT, true }, // rearRight
  {4, DRIVEMOTOR_SIDE_LEFT,  false}, // rearLeft
};

/*
 * Public API
 */

static drivetrain_t drivetrains[3] = {
  {DRIVETRAIN_TYPE_BASIC_XDRIVE, &basicDriveTick, &basicDriveData},
  {DRIVETRAIN_TYPE_HOLONOMIC_XDRIVE, &holonomicDriveTick, &holonomicDriveData},
  {NULL}
};

static drivetrain_t *drivetrain = drivetrains;

drivetrain_t *drivetrainGet(void) {
  return drivetrain;
}

bool drivetrainSet(uint8_t type) {
  drivetrain_t *p = drivetrains;
  while (p != NULL) {
    if (p->type == type) {
      drivetrain = p;
      break;
    }
    p++;
  }
  return (p == drivetrain);
}

void drivetrainTick(void) {
  if (drivetrain->tick != NULL) {
    drivetrain->tick(drivetrain->data);
  }
}

/*
 * Basic X-Drive Functions
 */

static void basicDriveTick(void *data) {
  basicDrive_t *drive = (basicDrive_t *) data;
  int xRight = joystickGetAnalog(1, 1);
  // int yRight = joystickGetAnalog(1, 2);
  int xLeft  = joystickGetAnalog(1, 4);
  int yLeft  = joystickGetAnalog(1, 3);
  drivemotorSet(&drive->frontRight, yLeft - xRight - xLeft);
  drivemotorSet(&drive->frontLeft,  yLeft + xRight + xLeft);
  drivemotorSet(&drive->backRight,  yLeft + xRight - xLeft);
  drivemotorSet(&drive->backLeft,   yLeft - xRight + xLeft);
}

/*
 * Holonomic X-Drive Functions
 */

static void holonomicDriveTick(void *data) {
  double radians = (PI / 2) - joystickGetPolarRadians(1, 1, 2);
  double speed = joystickGetPolarSpeed(1, 1, 2);
  int rotation = joystickGetAnalog(1, 4);
  holonomicDriveSet(data, radians, speed, rotation);
}

static void holonomicDriveSet(void *data, double radians, double speed, int rotation) {
  holonomicDrive_t *drive = (holonomicDrive_t *) data;
  if (speed > 0) {
    double frontLeftOutput  = -DRIVEMOTOR_MAX_SPEED * cos((PI / 4) - radians);
    double frontRightOutput =  DRIVEMOTOR_MAX_SPEED * cos((PI / 4) + radians);
    double rearRightOutput  =  DRIVEMOTOR_MAX_SPEED * cos((PI / 4) - radians);
    double rearLeftOutput   = -DRIVEMOTOR_MAX_SPEED * cos((PI / 4) + radians);

    frontLeftOutput  += rotation;
    frontRightOutput += rotation;
    rearRightOutput  += rotation;
    rearLeftOutput   += rotation;

    double maxOutput = fabsmax(4, frontLeftOutput, frontRightOutput, rearLeftOutput, rearRightOutput);
    speed *= (DRIVEMOTOR_MAX_SPEED / maxOutput);

    frontLeftOutput  *= speed;
    frontRightOutput *= speed;
    rearLeftOutput   *= speed;
    rearRightOutput  *= speed;

    drivemotorSet(&drive->frontLeft,  frontLeftOutput);
    drivemotorSet(&drive->frontRight, frontRightOutput);
    drivemotorSet(&drive->rearLeft,   rearLeftOutput);
    drivemotorSet(&drive->rearRight,  rearRightOutput);
  } else if (rotation > HOLONOMIC_DEADBAND || rotation < -HOLONOMIC_DEADBAND) {
    drivemotorSet(&drive->frontLeft,  rotation);
    drivemotorSet(&drive->frontRight, rotation);
    drivemotorSet(&drive->rearLeft,   rotation);
    drivemotorSet(&drive->rearRight,  rotation);
  } else {
    drivemotorStop(&drive->frontLeft);
    drivemotorStop(&drive->frontRight);
    drivemotorStop(&drive->rearLeft);
    drivemotorStop(&drive->rearRight);
  }
}
