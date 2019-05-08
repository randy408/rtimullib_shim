#include <RTIMULib.h>
#include "rtimulib_shim.h"

extern "C"
{

rtimu_settings_t rtimu_settings_new(const char *name)
{
    return new RTIMUSettings(name);
}

rtimu_t rtimu_create(rtimu_settings_t settings)
{
    return RTIMU::createIMU((RTIMUSettings*)settings);
}

int rtimu_init(rtimu_t imu, int flags)
{
    RTIMU *p = (RTIMU*)imu;
    p->IMUInit();

    p->setSlerpPower(0.02);
    p->setGyroEnable(true);
    p->setAccelEnable(true);
    p->setCompassEnable(true);

    return 0;
}

int rtimu_get_data(rtimu_t imu, struct rtimu_data *data)
{
    if(imu == NULL || data == NULL)  return 1;

    RTIMU *p = (RTIMU*)imu;
    p->IMURead();/* XXX: check error code */
    RTIMU_DATA imu_data = p->getIMUData();

    data->imu_timestamp = imu_data.timestamp;

    data->imu_flags = 0;
    data->imu_flags |= imu_data.fusionPoseValid ? RTIMU_FUSION_POSE_VALID : 0;
    data->imu_flags |= imu_data.fusionQPoseValid ? RTIMU_FUSION_QPOSE_VALID : 0;
    data->imu_flags |= imu_data.gyroValid ? RTIMU_GYRO_VALID : 0;
    data->imu_flags |= imu_data.accelValid ? RTIMU_ACCEL_VALID : 0;
    data->imu_flags |= imu_data.compassValid ? RTIMU_COMPASS_VALID : 0;
    data->imu_flags |= imu_data.temperatureValid ? RTIMU_TEMP_VALID : 0;

    data->fusion_pose_x = imu_data.fusionPose.x();
    data->fusion_pose_y = imu_data.fusionPose.y();
    data->fusion_pose_z = imu_data.fusionPose.z();

/*    printf("X: %f  Y: %f  Z: %f\n", imu_data.fusionPose.x(), imu_data.fusionPose.y(), imu_data.fusionPose.z());*/

    data->fusion_qpose_scalar = imu_data.fusionQPose.scalar();

    data->fusion_qpose_x = imu_data.fusionQPose.x();
    data->fusion_qpose_y = imu_data.fusionQPose.y();
    data->fusion_qpose_z = imu_data.fusionQPose.z();

    data->gyro_x = imu_data.gyro.x();
    data->gyro_y = imu_data.gyro.y();
    data->gyro_z = imu_data.gyro.z();

    data->accel_x = imu_data.accel.x();
    data->accel_y = imu_data.accel.y();
    data->accel_z = imu_data.accel.z();

    data->compass_x = imu_data.compass.x();
    data->compass_y = imu_data.compass.y();
    data->compass_z = imu_data.compass.z();

    data->imu_temp = imu_data.temperature;

    return 0;
}

void rtimu_delete(rtimu_t imu)
{
    RTIMU *p = (RTIMU*)imu;
    delete p;
}

void rtimu_settings_delete(rtimu_settings_t settings)
{
    RTIMUSettings *p = (RTIMUSettings*)settings;
    delete p;
}


}/* extern "C" */
