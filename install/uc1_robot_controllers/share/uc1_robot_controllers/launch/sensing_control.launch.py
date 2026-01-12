from launch import LaunchDescription
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.actions import Node
from launch.substitutions import Command
import os
from ament_index_python.packages import get_package_share_path

def generate_launch_description():
    
    interactive_targhet_node = Node(
        package="pointcloud_interactive_markers",
        executable="interactive-target",
        name="ik_target_body_marker",
        parameters=[{
            "position":[3.0, 0.0, 0.05],
            "orientation":[0.0, 0.0, 0.0]
        }]
    )
    
    # cylinder-cloud-broadcaster -- SINGOLO OSTACOLO CILINDRO
    # cylinder-cloud-broadcaster-multi -- DOPPIO CILINDRO
    # chassis-cloud -- CHASSIS MACCHINA
    obstacle_node = Node(
        package="pointcloud_interactive_markers",
        executable="cylinder-cloud-broadcaster"
    )
    
    proximity_task_gen_node = Node(
        package="uc1_robot_perception",
        executable="proximity_task_generator"
    )
    
    return LaunchDescription([
        interactive_targhet_node,
        obstacle_node,
        proximity_task_gen_node
    ])