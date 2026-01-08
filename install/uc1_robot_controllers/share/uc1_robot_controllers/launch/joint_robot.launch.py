from launch import LaunchDescription
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.actions import Node
from launch.substitutions import Command
import os
from ament_index_python.packages import get_package_share_path
from launch.actions import (DeclareLaunchArgument, EmitEvent, ExecuteProcess,
                            LogInfo, RegisterEventHandler, TimerAction)

def generate_launch_description():
    
    interactive_targhet_node = Node(
        package="uc1_robot_controllers",
        executable="joint-robot-tp-test",
        parameters=[{
            "kuka_gain":0.0533,
            "ur10_gain":0.533
        }]
    )

    run_joint_robot = ExecuteProcess(
        cmd=[[
            'ros2',
            ' run',
            ' uc1_robot_controllers',
            ' joint-robot-tp-test',
            ' --ros-args',
            ' -p',
            ' kuka_gain:=0.066',
            ' -p',
            ' ur10_gain:=0.66',
        ]],
        shell=True
    )
    
    return LaunchDescription([
        run_joint_robot
    ])

