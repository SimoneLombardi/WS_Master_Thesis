// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from uc1_robot_perception:msg/ProximityTaskArray.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "uc1_robot_perception/msg/detail/proximity_task_array__struct.h"
#include "uc1_robot_perception/msg/detail/proximity_task_array__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes
#include "uc1_robot_perception/msg/detail/proximity_task__functions.h"
// end nested array functions include
bool uc1_robot_perception__msg__proximity_task__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * uc1_robot_perception__msg__proximity_task__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool uc1_robot_perception__msg__proximity_task_array__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[66];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("uc1_robot_perception.msg._proximity_task_array.ProximityTaskArray", full_classname_dest, 65) == 0);
  }
  uc1_robot_perception__msg__ProximityTaskArray * ros_message = _ros_message;
  {  // proximity_tasks
    PyObject * field = PyObject_GetAttrString(_pymsg, "proximity_tasks");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'proximity_tasks'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!uc1_robot_perception__msg__ProximityTask__Sequence__init(&(ros_message->proximity_tasks), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create uc1_robot_perception__msg__ProximityTask__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    uc1_robot_perception__msg__ProximityTask * dest = ros_message->proximity_tasks.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!uc1_robot_perception__msg__proximity_task__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * uc1_robot_perception__msg__proximity_task_array__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ProximityTaskArray */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("uc1_robot_perception.msg._proximity_task_array");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ProximityTaskArray");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  uc1_robot_perception__msg__ProximityTaskArray * ros_message = (uc1_robot_perception__msg__ProximityTaskArray *)raw_ros_message;
  {  // proximity_tasks
    PyObject * field = NULL;
    size_t size = ros_message->proximity_tasks.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    uc1_robot_perception__msg__ProximityTask * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->proximity_tasks.data[i]);
      PyObject * pyitem = uc1_robot_perception__msg__proximity_task__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "proximity_tasks", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
