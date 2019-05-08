#ifndef RTIMULIB_SHIM_H
#define RTIMULIB_SHIM_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* rtimu_settings_t;
typedef void* rtimu_t;

#define RTIMU_FUSION_POSE_VALID 1
#define RTIMU_FUSION_QPOSE_VALID 2
#define RTIMU_GYRO_VALID 4
#define RTIMU_ACCEL_VALID 8
#define RTIMU_COMPASS_VALID 16
#define RTIMU_TEMP_VALID 32

struct rtimu_data
{
    uint64_t imu_timestamp;
    uint8_t imu_flags; 
    float fusion_pose_x, fusion_pose_y, fusion_pose_z;
    float fusion_qpose_scalar;
    float fusion_qpose_x, fusion_qpose_y, fusion_qpose_z;
    float gyro_x, gyro_y, gyro_z;
    float accel_x, accel_y, accel_z;
    float compass_x, compass_y, compass_z;
    uint8_t imu_temp;
};

uint64_t rtimu_epoch_usec(void);

rtimu_settings_t rtimu_settings_new(const char *name);
rtimu_t rtimu_create(rtimu_settings_t settings);
int rtimu_init(rtimu_t imu, int flags);
int rtimu_get_data(rtimu_t imu, struct rtimu_data *data);

void rtimu_delete(rtimu_t imu);
void rtimu_settings_delete(rtimu_settings_t settings);


#ifdef __cplusplus
}
#endif
#endif /* RTIMULIB_SHIM_H */
