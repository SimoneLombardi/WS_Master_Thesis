from launch import LaunchDescription
from launch_ros.actions import Node

'''
def generate_launch_description():
    return LaunchDescription([
        Node (
            package='ur_task_controllers',
            executable='ur-joint-controller',
            name='controller'
        ),
        Node (
            package='ur_task_controllers',
            executable='interactive-target',
            name='target',
            output='screen'
        ),
        Node (
            package='manage_pcl',
            executable='manage_pcl_stl_real',
            name='manage',
            output='screen'
        )
])
'''

def generate_launch_description():
    return LaunchDescription([
        Node (
            package='ur_task_controllers',
            executable='ur-joint-controller'
        ),
        Node (
            package='ur_task_controllers',
            executable='interactive-target',
            output='screen'
        ),
        Node (
            package='manage_pcl',
            executable='manage_pcl_stl_real',
            output='screen'
        ),
        Node (
            package='manage_pcl',
            executable='dummy_cloud_broadcaster',
            output='screen'
        ),
        Node (
            package='ur_task_controllers',
            executable='experiment-goals',
            output='screen'
        )
])
