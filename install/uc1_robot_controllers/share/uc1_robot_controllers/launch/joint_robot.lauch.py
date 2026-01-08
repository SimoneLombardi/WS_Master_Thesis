from launch import LaunchDescription
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.actions import Node
from launch.substitutions import Command
import os
from ament_index_python.packages import get_package_share_path

def generate_launch_description():
    
    interactive_targhet_node = Node(
        package="uc1_robot_controllers",
        executable="joint-robot-tp-test",
        name="joint_robot_tp_node",
        parameters=[{
            "kuka_gain":0.05,
            "ur10_gain":0.5
        }]
    )
    
    return LaunchDescription([
        interactive_targhet_node
    ])