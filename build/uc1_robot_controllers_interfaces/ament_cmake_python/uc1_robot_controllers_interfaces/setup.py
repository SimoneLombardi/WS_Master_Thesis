from setuptools import find_packages
from setuptools import setup

setup(
    name='uc1_robot_controllers_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('uc1_robot_controllers_interfaces', 'uc1_robot_controllers_interfaces.*')),
)
