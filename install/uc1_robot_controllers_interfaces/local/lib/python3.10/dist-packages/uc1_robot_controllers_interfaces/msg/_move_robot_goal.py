# generated from rosidl_generator_py/resource/_idl.py.em
# with input from uc1_robot_controllers_interfaces:msg/MoveRobotGoal.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MoveRobotGoal(type):
    """Metaclass of message 'MoveRobotGoal'."""

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
            module = import_type_support('uc1_robot_controllers_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'uc1_robot_controllers_interfaces.msg.MoveRobotGoal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__move_robot_goal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__move_robot_goal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__move_robot_goal
            cls._TYPE_SUPPORT = module.type_support_msg__msg__move_robot_goal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__move_robot_goal

            from uc1_robot_controllers_interfaces.msg import MoveRobotOrient
            if MoveRobotOrient.__class__._TYPE_SUPPORT is None:
                MoveRobotOrient.__class__.__import_type_support__()

            from uc1_robot_controllers_interfaces.msg import MoveRobotPoint
            if MoveRobotPoint.__class__._TYPE_SUPPORT is None:
                MoveRobotPoint.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MoveRobotGoal(metaclass=Metaclass_MoveRobotGoal):
    """Message class 'MoveRobotGoal'."""

    __slots__ = [
        '_translation',
        '_orientation',
    ]

    _fields_and_field_types = {
        'translation': 'uc1_robot_controllers_interfaces/MoveRobotPoint',
        'orientation': 'uc1_robot_controllers_interfaces/MoveRobotOrient',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['uc1_robot_controllers_interfaces', 'msg'], 'MoveRobotPoint'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['uc1_robot_controllers_interfaces', 'msg'], 'MoveRobotOrient'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from uc1_robot_controllers_interfaces.msg import MoveRobotPoint
        self.translation = kwargs.get('translation', MoveRobotPoint())
        from uc1_robot_controllers_interfaces.msg import MoveRobotOrient
        self.orientation = kwargs.get('orientation', MoveRobotOrient())

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
        if self.translation != other.translation:
            return False
        if self.orientation != other.orientation:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def translation(self):
        """Message field 'translation'."""
        return self._translation

    @translation.setter
    def translation(self, value):
        if __debug__:
            from uc1_robot_controllers_interfaces.msg import MoveRobotPoint
            assert \
                isinstance(value, MoveRobotPoint), \
                "The 'translation' field must be a sub message of type 'MoveRobotPoint'"
        self._translation = value

    @builtins.property
    def orientation(self):
        """Message field 'orientation'."""
        return self._orientation

    @orientation.setter
    def orientation(self, value):
        if __debug__:
            from uc1_robot_controllers_interfaces.msg import MoveRobotOrient
            assert \
                isinstance(value, MoveRobotOrient), \
                "The 'orientation' field must be a sub message of type 'MoveRobotOrient'"
        self._orientation = value
