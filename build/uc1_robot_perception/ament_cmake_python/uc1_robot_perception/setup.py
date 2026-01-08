from setuptools import find_packages
from setuptools import setup

setup(
    name='uc1_robot_perception',
    version='0.0.0',
    packages=find_packages(
        include=('uc1_robot_perception', 'uc1_robot_perception.*')),
)
