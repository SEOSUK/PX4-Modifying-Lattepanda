from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch_ros.actions import Node
from launch.actions import TimerAction

def generate_launch_description():
    return LaunchDescription([

        # listen_and_speak 노드 실행 (예시, 실제 실행파일 이름 필요)
        Node(
            package='px4_ros_com',
            executable='listen_and_speak_ros',  
            name='listen_and_speak_ros',
            output='screen'
        ),
        # custom_trajectory_generation SEUK
        Node(
            package='px4_ros_com',
            executable='custom_trajectory_generation',  
            name='custom_trajectory_generation',
            output='screen'
        ),        
TimerAction(
    period=3.0,
    actions=[
        # ros2 bag record 프로세스
        ExecuteProcess(
            cmd=[
                'ros2', 'bag', 'record',
                '/data_logging_msg',
            ],
            output='screen'
        )])
    ])

