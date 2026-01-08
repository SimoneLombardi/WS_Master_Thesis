from launch import LaunchDescription
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.actions import Node
from launch.substitutions import Command
import os
from ament_index_python.packages import get_package_share_path


def generate_launch_description():

    urdf_path = os.path.join(get_package_share_path("kuka_150_3100_description"), 'urdf', 'kuka.urdf.xacro')
    rviz_cfg_path = os.path.join(get_package_share_path("kuka_150_3100_description"), 'rviz', 'kuka_demo.rviz')
    
    robot_description = ParameterValue(Command(['xacro ', urdf_path]), value_type=str)
    tf_prefix_ = ParameterValue('kuka_', value_type=str)
    #robot_description = ParameterValue(urdf_path, value_type=str)

    # custom robot state publisher (TODO maybe change namespace for running joint with UR10e)
    robot_state_publisher_node = Node(
        package="rsp_uc1",
        executable="rsp_uc1",
        parameters=[{'robot_description_kuka': robot_description}]
    )
    kuka_controller_node = Node(
        package="ur_prioritized_controller",
        executable="kuka-test-controller"
    )

    rviz2_node = Node(
        package="rviz2",
        executable="rviz2",
        name='rviz2',
        arguments=['-d', rviz_cfg_path]
    )

    return LaunchDescription([
        robot_state_publisher_node,
        kuka_controller_node,
        rviz2_node
    ])
