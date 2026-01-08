from launch import LaunchDescription
from launch_ros.actions import Node


# joint control check

def generate_launch_description():
    return LaunchDescription([
        Node (
            package='ur_task_controllers',
            executable='ur-joint-controller'
        )
])

'''
# cartesian reaching check
def generate_launch_description():
    return LaunchDescription([
        Node (
            package='ur_task_controllers',
            executable='static-target',
            output='screen'
        ),
        Node (
            package='ur_task_controllers',
            executable='ur-ik-controller',
            output='screen'
        )
])

'''


# avoidance-only check




