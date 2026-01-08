# generated from rosidl_generator_py/resource/_idl.py.em
# with input from uc1_robot_perception:msg/ProximityTask.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ProximityTask(type):
    """Metaclass of message 'ProximityTask'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('uc1_robot_perception')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'uc1_robot_perception.msg.ProximityTask')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__proximity_task
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__proximity_task
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__proximity_task
            cls._TYPE_SUPPORT = module.type_support_msg__msg__proximity_task
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__proximity_task

            from geometry_msgs.msg import Vector3
            if Vector3.__class__._TYPE_SUPPORT is None:
                Vector3.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ProximityTask(metaclass=Metaclass_ProximityTask):
    """Message class 'ProximityTask'."""

    __slots__ = [
        '_min_point_robot',
        '_min_point_vector',
        '_distance',
        '_link_id',
    ]

    _fields_and_field_types = {
        'min_point_robot': 'geometry_msgs/Vector3',
        'min_point_vector': 'geometry_msgs/Vector3',
        'distance': 'float',
        'link_id': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from geometry_msgs.msg import Vector3
        self.min_point_robot = kwargs.get('min_point_robot', Vector3())
        from geometry_msgs.msg import Vector3
        self.min_point_vector = kwargs.get('min_point_vector', Vector3())
        self.distance = kwargs.get('distance', float())
        self.link_id = kwargs.get('link_id', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.min_point_robot != other.min_point_robot:
            return False
        if self.min_point_vector != other.min_point_vector:
            return False
        if self.distance != other.distance:
            return False
        if self.link_id != other.link_id:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def min_point_robot(self):
        """Message field 'min_point_robot'."""
        return self._min_point_robot

    @min_point_robot.setter
    def min_point_robot(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'min_point_robot' field must be a sub message of type 'Vector3'"
        self._min_point_robot = value

    @builtins.property
    def min_point_vector(self):
        """Message field 'min_point_vector'."""
        return self._min_point_vector

    @min_point_vector.setter
    def min_point_vector(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'min_point_vector' field must be a sub message of type 'Vector3'"
        self._min_point_vector = value

    @builtins.property
    def distance(self):
        """Message field 'distance'."""
        return self._distance

    @distance.setter
    def distance(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'distance' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'distance' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._distance = value

    @builtins.property
    def link_id(self):
        """Message field 'link_id'."""
        return self._link_id

    @link_id.setter
    def link_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'link_id' field must be of type 'str'"
        self._link_id = value
