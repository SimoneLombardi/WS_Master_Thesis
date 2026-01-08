#include "JointRobot.hpp"
#include "KukaRobot.hpp"
#include "UR10eRobot.hpp"
#include "TfGoalBroadcaster.hpp"


#include <csignal>
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
//#include <tf2_eigen/tf2_eigen.h>

Eigen::MatrixXd skewSymmetric(const Eigen::VectorXd& v){
    Eigen::MatrixXd skew_mat(3, 3);
    skew_mat <<     0, -v(2),  v(1),
                 v(2),     0, -v(0),
                -v(1),  v(0),     0;
    return skew_mat;
}

using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    
    auto kuka_node = std::make_shared<rclcpp::Node>("kuka_robot_node");
    auto kuka_robot = std::make_shared<KukaRobot>();
    kuka_robot->initialize(kuka_node);

    auto ur10_node = std::make_shared<rclcpp::Node>("ur10_robotnode");
    auto ur10_robot = std::make_shared<UR10eRobot>();
    ur10_robot->initialize(ur10_node);

    auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor->add_node(kuka_node);
    executor->add_node(ur10_node);
    std::thread spin_thread([executor](){ executor->spin(); });

    // print space to separate my output from the initialization one
    std::cout << "\n\n\n\n";
    // initial position reaching -------------------------------------------------------------------------- initial position reaching //
    Eigen::VectorXd q_des = Eigen::VectorXd::Zero(6);
    Eigen::VectorXd q_err = Eigen::VectorXd::Zero(6);

    q_des << 0.0, -2.1, 2.4, 0.0, -1.57, 0.0;
    
    kuka_robot->runJointControlLoop(q_des, q_err);
    RCLCPP_INFO(kuka_node->get_logger(), "joint loop kuka finished");
    
    q_des << 0.0, -1.57, 0.0, -1.57, 0.0, 0.0;
    ur10_robot->runJointControlLoop(q_des, q_err);
    RCLCPP_INFO(ur10_node->get_logger(), "joint loop kuka finished");
    // initial position reaching -------------------------------------------------------------------------- initial position reaching //

    
    // debug print data ----------------------------------------------------------------------------------- debug print data //
    /*
    std::cout << "\nPROJECTION MATRIX DEBUG:" << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "kuka, gen tf, (kuka_base_link, tool0):\n" << kuka_robot->getGenericTransformation("kuka_base_link", "tool0").matrix() << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "kuka, gen tf, (tool0, kuka_base_link):\n" << kuka_robot->getGenericTransformation("tool0", "kuka_base_link").matrix() << std::endl;
    
    std::cout << "\n" << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "ur10, gen tf, (kuka_base_link, tool0):\n" << ur10_robot->getGenericTransformation("kuka_base_link", "tool0").matrix() << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "ur10, gen tf, (tool0, kuka_base_link):\n" << ur10_robot->getGenericTransformation("tool0", "kuka_base_link").matrix() << std::endl;

    std::cout << "\nDEBUG FUNZIONE 'getTransformations':" << std::endl;
    std::cout << "\ncontrol for trasnf type:" << std::endl;
    //std::cout << std::fixed << std::setprecision(1) << "ur10, gen tf, (base_link, shoulder_link):\n" << ur10_robot->getGenericTransformation("base_link", "shoulder_link").matrix() << std::endl;
    //std::cout << std::fixed << std::setprecision(1) << "ur10, gen tf, (base_link, upper_arm_link):\n" << ur10_robot->getGenericTransformation("base_link", "upper_arm_link").matrix() << std::endl;
    //std::cout << std::fixed << std::setprecision(1) << "ur10, gen tf, (shoulder_link, upper_arm_link):\n" << ur10_robot->getGenericTransformation("shoulder_link", "upper_arm_link").matrix() << std::endl;
    auto ur10_tfs = ur10_robot->getTransformations();
    std::cout << "\n -- START FCN --" << std::endl;
    for (int i = 0; i < 1; i++)
    {
        std::cout << std::fixed << std::setprecision(1) << ur10_tfs[i].matrix() << "\n - - - " << std::endl;
    }

    std::cout << "\nDEBUG JACOBIANE:" << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "kuka, jacobian:\n" << kuka_robot->computeJacobian("kuka_link_6") << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "ur10, jacobian:\n" << ur10_robot->computeJacobian("tool0") << std::endl;

    std::cout << "\nDEBUG COLLEGAMENTO ROBOT STATICO:" << std::endl;
    int prec = 6;
    std::cout << std::fixed << std::setprecision(prec) << "kuka, gen tf, (kuka_link_6, base_link):\n" << kuka_robot->getGenericTransformation("kuka_link_6", "base_link").matrix() << std::endl;
    std::cout << std::fixed << std::setprecision(prec) << "ur10, gen tf, (kuka_link_6, base_link):\n" << ur10_robot->getGenericTransformation("kuka_link_6", "base_link").matrix() << std::endl;
    */
    std::vector frame_names = {"kuka_link_1", "kuka_link_2", "kuka_link_3", "kuka_link_4", "kuka_link_5", "kuka_link_6",
                     "shoulder_link", "upper_arm_link", "forearm_link", "wrist_1_link", "wrist_2_link", "wrist_3_link"};


    std::cout << "\n\n\nDEBUG CALCOLO JACOBIANO:" << std::endl;
    Eigen::MatrixXd J_kuka = kuka_robot->computeJacobian("kuka_link_6");
    Eigen::MatrixXd J_ur10 = ur10_robot->computeJacobian("tool0");

    // provo a compilare la JACOBIANA con il metodo classico
    Eigen::Affine3d cur_lnk_tf;
    Eigen::Affine3d ee_tf = kuka_robot->getGenericTransformation("kuka_base_link", "kuka_link_6");
    Eigen::MatrixXd J_kuka_ANA = Eigen::MatrixXd::Zero(6,6);
    Eigen::Vector3d ax_vtc;
    for(int i=0;i<6;++i){
        cur_lnk_tf = kuka_robot->getGenericTransformation("kuka_base_link", frame_names[i]);
        switch(i){
            case 0: ax_vtc <<0,0,-1; break;
            case 1: ax_vtc <<0,1,0; break;
            case 2: ax_vtc <<0,1,0; break;
            case 3: ax_vtc <<-1,0,0; break;
            case 4: ax_vtc <<0,1,0; break;
            case 5: ax_vtc <<-1,0,0; break;
            case 6: ax_vtc <<0,0,1; break;
            case 7: ax_vtc <<0,0,1; break;
            case 8: ax_vtc <<0,0,1; break;
            case 9: ax_vtc <<0,0,1; break;
            case 10: ax_vtc <<0,0,1; break;
            case 11: ax_vtc <<0,0,1; break;
            default: break;
        }
        //std::cout << frame_names_[i] << " -- " << ax_vtc.transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        Eigen::Vector3d AX_vtc = cur_lnk_tf.linear()*ax_vtc;
        J_kuka_ANA.block(0,i,3,1) = AX_vtc.cross((ee_tf.translation()-cur_lnk_tf.translation()));
        J_kuka_ANA.block(3,i,3,1) = AX_vtc;
    }

    ee_tf = kuka_robot->getGenericTransformation("base_link", "tool0");
    Eigen::MatrixXd J_ur10_ANA = Eigen::MatrixXd::Zero(6,6);
    for(int i=6;i<12;++i){
        cur_lnk_tf = kuka_robot->getGenericTransformation("base_link", frame_names[i]);
        switch(i){
            case 0: ax_vtc <<0,0,-1; break;
            case 1: ax_vtc <<0,1,0; break;
            case 2: ax_vtc <<0,1,0; break;
            case 3: ax_vtc <<-1,0,0; break;
            case 4: ax_vtc <<0,1,0; break;
            case 5: ax_vtc <<-1,0,0; break;
            case 6: ax_vtc <<0,0,1; break;
            case 7: ax_vtc <<0,0,1; break;
            case 8: ax_vtc <<0,0,1; break;
            case 9: ax_vtc <<0,0,1; break;
            case 10: ax_vtc <<0,0,1; break;
            case 11: ax_vtc <<0,0,1; break;
            default: break;
        }
        //std::cout << frame_names[i] << " -- " << ax_vtc.transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        //std::cout << cur_lnk_tf.linear() << std::endl;
        Eigen::Vector3d AX_vtc = cur_lnk_tf.linear()*ax_vtc;
        J_ur10_ANA.block(0,i-6,3,1) = AX_vtc.cross((ee_tf.translation()-cur_lnk_tf.translation()));
        J_ur10_ANA.block(3,i-6,3,1) = AX_vtc;
    }
    
    std::cout << J_kuka << std::endl;
    std::cout << J_kuka_ANA << std::endl;
    std::cout << "\n\n" << std::endl;
    std::cout << J_ur10 << std::endl;
    std::cout << J_ur10_ANA << std::endl;
    
    
    // debug print data ----------------------------------------------------------------------------------- debug print data //


    // closing 
    executor->cancel();
    if(spin_thread.joinable()){
        spin_thread.join();
    }

    std::cout << "\n\n\n\n";
    rclcpp::shutdown();
    RCLCPP_INFO(kuka_node->get_logger(), "KUKA ROBOT TEST SHUTDOWN");
    RCLCPP_INFO(ur10_node->get_logger(), "UR10 ROBOT TEST SHUTDOWN");
    //RCLCPP_INFO(joint_jacobian_publisher->get_logger(), "kuka node shut down");
    return 0;
}