# stages
uint8 STAGE_POSITION=0
uint8 STAGE_VELOCITY=1
uint8 STAGE_ATTITUDE=2
uint8 STAGE_RATE=3
uint8 STAGE_ALLOCATION=4
uint8 STAGE_DOB=5
uint8 STAGE_COM=6

uint64 timestamp   # hrt_absolute_time() (us)
uint8  stage       # 위 enum 중 하나
float32 dt         # seconds
