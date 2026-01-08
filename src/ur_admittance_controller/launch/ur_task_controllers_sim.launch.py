from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node (
            package='ur_task_controllers',
            executable='ur-joint-controller'
        ),
        Node (
            package='ur_task_controllers',
            executable='mindist-dummy-broadcaster'
        ),
        Node (
            package='ur_task_controllers',
            executable='interactive-target',
            output='screen'
        ),
        Node (
            package='manage_pcl',
            executable='manage_pcl_stl_ursim',
            output='screen'
        ),
        Node (
            package='manage_pcl',
            executable='dummy_cloud_broadcaster',
            output='screen'
        )
])


'''
Node(
    package='ur_task_controllers',
    executable='static-target',
    output='screen'
)
'''
