from launch import LaunchDescription
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.actions import Node
from launch.substitutions import Command
import os
from ament_index_python.packages import get_package_share_path

def generate_launch_description():
    # cylinder-cloud-broadcaster -- SINGOLO OSTACOLO CILINDRO 
        #"position"   :[3.0, 0.0, 0.05],
        #"orientation":[0.0, 0.0, 0.0]
    # cylinder-cloud-broadcaster-multi -- DOPPIO CILINDRO
        # IN-LINE
        #"position"   :[3.0, 0.0, 0.05],
        #"orientation":[0.0, 0.0, 0.0]
        # GATE
        #"position"   :[3.0, 0.0, 0.05],
        #"orientation":[0.0, 0.0, -1.57]
    # chassis-cloud -- CHASSIS MACCHINA
        # SIDE
        #"position"   :[3.5, 0.0, 0.05],
        #"orientation":[0.0, 0.0, -1.57]
        # BACK
        #"position"   :[4.0, 0.0, 0.05],
        #"orientation":[0.0, 0.0, -3.14]

    
    interactive_targhet_node = Node(
        package="pointcloud_interactive_markers",
        executable="interactive-target",
        name="ik_target_body_marker",
        parameters=[{
            "position":[2.3, -1.7, 0.05],
            "orientation":[0.0, 0.0, -1.57]
        }]
    )
    
    
    obstacle_node = Node(
        package="pointcloud_interactive_markers",
        executable="cylinder-cloud-broadcaster-multi"
    )

    obstacle_node_v2 = Node(
        package="pointcloud_interactive_markers",
        executable="obstacle-cloud-broadcaster",
        parameters=[{
            "ptc_filename":"/resources/chassis_downsampled_cloud_scaled_centered.pcd",
            "ptc_pkgname":"environment_pointcloud_processing"
        }]
    )

    #chassis_downsampled_cloud_scaled_centered.pcd
    #multi_cylinder_colud.pcd
    #single_cylinder_colud.pcd
    
    proximity_task_gen_node = Node(
        package="uc1_robot_perception",
        executable="proximity_task_generator"
    )
    
    return LaunchDescription([
        interactive_targhet_node,
        obstacle_node_v2,
        proximity_task_gen_node
    ])