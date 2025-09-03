uint64 timestamp                         # [us] 시간 (uORB publish 시간)
uint64 timestamp_sample                  # [us] 실제 센서 수집 시간

uint8 pose_frame                         # 위치/자세 기준 좌표계 (e.g. NED, FRD 등)
float32[3] position                      # [m] x, y, z 위치
float32[4] q                             # 자세 (quaternion, [w, x, y, z] 또는 [x, y, z, w])
float32[3] velocity                      # [m/s] x, y, z 속도
float32[3] angular_velocity              # [rad/s] body frame 기준 각속도

float32[3] position_variance             # 위치 신뢰도 (분산 값)
float32[3] orientation_variance          # 자세 신뢰도 (분산 값)

float32[3] velocity_variance             # 속도 신뢰도 (분산 값)
float32[3] angular_velocity_variance     # 각속도 신뢰도 (분산 값)

uint8 reset_counter                      # EKF 리셋 횟수 추적용
bool quality_flag                        # 트래킹 품질 좋음/나쁨 여부

