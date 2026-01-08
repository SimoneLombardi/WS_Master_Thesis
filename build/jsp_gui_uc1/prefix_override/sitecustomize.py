import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/install/jsp_gui_uc1'
