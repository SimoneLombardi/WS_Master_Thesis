#include "rclcpp/rclcpp.hpp"
#include "message_filters/subscriber.h"
#include "message_filters/synchronizer.h"
#include "message_filters/sync_policies/approximate_time.h"
#include <sensor_msgs/msg/joint_state.hpp>

#include <chrono>
#include <functional>
#include <memory>

using namespace std::chrono_literals;

using std::placeholders::_1;
using std::placeholders::_2;
using JointStateMsg = sensor_msgs::msg::JointState;

class JointStatesSynchronizer : public rclcpp::Node
{
    public:
        JointStatesSynchronizer() : Node("joint_states_synchronizer")
        {
            // define QoS window
            rclcpp::QoS qos = rclcpp::QoS(10);
            uint32_t queque_size = 10;

            // define the merged topic
            merged_pub = this->create_publisher<JointStateMsg>("/joint_states", qos);

            // define sub to kuka and ur joint state topic
            kuka_sub.subscribe(this, "/joint_states_kuka", qos.get_rmw_qos_profile());
            ur10_sub.subscribe(this, "/joint_states_ur10", qos.get_rmw_qos_profile());
            
            sync = std::make_shared<message_filters::Synchronizer<message_filters::sync_policies::ApproximateTime<JointStateMsg, JointStateMsg>>>(
                message_filters::sync_policies::ApproximateTime<JointStateMsg, JointStateMsg>(queque_size), kuka_sub, ur10_sub);

            sync->setAgePenalty(0.005);
            sync->registerCallback(std::bind(&JointStatesSynchronizer::SyncCallback, this, _1, _2));

            ordered_joint_names_ = {"kuka_joint_a1",      "kuka_joint_a2",       "kuka_joint_a3", "kuka_joint_a4", "kuka_joint_a5", "kuka_joint_a6",
                                    "shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint",   "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"};    
            joint_state_zero_ = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
        }

        JointStateMsg getZero_message(){
            JointStateMsg msg;

            msg.header.stamp = this->get_clock()->now();
            msg.header.frame_id = "merged_zero_msg";

            msg.name = ordered_joint_names_;
            msg.position = {joint_state_zero_[0], joint_state_zero_[1], joint_state_zero_[2],joint_state_zero_[3],joint_state_zero_[4], joint_state_zero_[5],
                            joint_state_zero_[6], joint_state_zero_[7], joint_state_zero_[8],joint_state_zero_[9],joint_state_zero_[10],joint_state_zero_[11]};

            msg.velocity = {joint_state_zero_[0], joint_state_zero_[1], joint_state_zero_[2],joint_state_zero_[3],joint_state_zero_[4], joint_state_zero_[5],
                            joint_state_zero_[6], joint_state_zero_[7], joint_state_zero_[8],joint_state_zero_[9],joint_state_zero_[10],joint_state_zero_[11]};

            msg.effort = {joint_state_zero_[0], joint_state_zero_[1], joint_state_zero_[2],joint_state_zero_[3],joint_state_zero_[4], joint_state_zero_[5],
                            joint_state_zero_[6], joint_state_zero_[7], joint_state_zero_[8],joint_state_zero_[9],joint_state_zero_[10],joint_state_zero_[11]};

            return msg;
        }

        void mergeJoint_message(JointStateMsg & merged_msg, const JointStateMsg::ConstSharedPtr & msg){
            if(msg->header.frame_id == "base_link"){
                // position
                merged_msg.position[6] = msg->position[5];
                merged_msg.position[7] = msg->position[0];
                merged_msg.position[8] = msg->position[1];
                merged_msg.position[9] = msg->position[2];
                merged_msg.position[10] = msg->position[3];
                merged_msg.position[11] = msg->position[4];
                
                /*
                // velocity
                merged_msg.velocity[6] = msg->velocity[0];
                merged_msg.velocity[7] = msg->velocity[1];
                merged_msg.velocity[8] = msg->velocity[2];
                merged_msg.velocity[9] = msg->velocity[3];
                merged_msg.velocity[10] = msg->velocity[4];
                merged_msg.velocity[11] = msg->velocity[5];

                // effort
                merged_msg.effort[6] = msg->effort[0];
                merged_msg.effort[7] = msg->effort[1];
                merged_msg.effort[8] = msg->effort[2];
                merged_msg.effort[9] = msg->effort[3];
                merged_msg.effort[10] = msg->effort[4];
                merged_msg.effort[11] = msg->effort[5];
                */

            }else if(msg->header.frame_id == "kuka_base_link"){
                merged_msg.position[0] = msg->position[0];
                merged_msg.position[1] = msg->position[1];
                merged_msg.position[2] = msg->position[2];
                merged_msg.position[3] = msg->position[3];
                merged_msg.position[4] = msg->position[4];
                merged_msg.position[5] = msg->position[5];
            }
        }

    private:
        rclcpp::Publisher<JointStateMsg>::SharedPtr merged_pub;
 
        message_filters::Subscriber<JointStateMsg> kuka_sub;
        message_filters::Subscriber<JointStateMsg> ur10_sub;

        std::shared_ptr<message_filters::Synchronizer<message_filters::sync_policies::ApproximateTime<JointStateMsg, JointStateMsg>>> sync;

        void SyncCallback(const JointStateMsg::ConstSharedPtr & kuka_js, const JointStateMsg::ConstSharedPtr & ur10_js){
            //RCLCPP_INFO(this->get_logger(), "publishing merged /joint_state at zero");
            JointStateMsg msg = getZero_message();

            mergeJoint_message(msg, kuka_js);
            mergeJoint_message(msg, ur10_js);

            merged_pub->publish(msg);
        }

        std::vector<std::string> ordered_joint_names_;
        std::vector<double> joint_state_zero_;

};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<JointStatesSynchronizer>();
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}