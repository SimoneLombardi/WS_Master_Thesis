#include "rclcpp/rclcpp.hpp"
#include "uc1_robot_perception/msg/contact.hpp"
#include "uc1_robot_perception/msg/contact_array.hpp"
#include <mutex>

// TODO build a control task generator out of this, that maybe could be done directly in the middleware. Here the 
// thing is easier, just need the set of forces and the link, then I build the control law directly in the robot 
// controller. I test here and then move this part on the control side, on threads that handle the subscription

using namespace std::chrono_literals;

class ContactSubscriber : public rclcpp::Node
{
public:
  ContactSubscriber()
  : Node("contact_subscriber")
  {
    // Subscription for single contact messages
    single_sub_ = this->create_subscription<tactile_contact_sim::msg::Contact>(
      "contact", 10,
      std::bind(&ContactSubscriber::single_callback, this, std::placeholders::_1));

    // Subscription for multi-contact messages
    multi_sub_ = this->create_subscription<tactile_contact_sim::msg::ContactArray>(
      "contacts", 10,
      std::bind(&ContactSubscriber::multi_callback, this, std::placeholders::_1));

    // Main loop timer running at 100Hz (i.e., every 10ms)
    main_timer_ = this->create_wall_timer(
      10ms, std::bind(&ContactSubscriber::main_loop, this));
  }

private:
  // Callback for the single contact topic
  void single_callback(const tactile_contact_sim::msg::Contact::SharedPtr msg)
  {
    std::lock_guard<std::mutex> lock(data_mutex_);
    latest_single_contact_ = *msg; // store a copy of the incoming message
    RCLCPP_INFO(this->get_logger(), "Received single contact: intensity=%.2f",
                latest_single_contact_.contact_intensity);
  }

  // Callback for the multi-contact topic
  void multi_callback(const tactile_contact_sim::msg::ContactArray::SharedPtr msg)
  {
    std::lock_guard<std::mutex> lock(data_mutex_);
    latest_contact_array_ = *msg; // store a copy of the incoming message array
    RCLCPP_INFO(this->get_logger(), "Received multi-contact array with %zu contacts",
                latest_contact_array_.contacts.size());
  }

  // Main loop running at 100Hz
  void main_loop()
  {
    // Lock the mutex to safely access the shared data
    {
      std::lock_guard<std::mutex> lock(data_mutex_);
      // Example processing: print out the intensity of the single contact and
      // the number of contacts in the array.
      double intensity = latest_single_contact_.contact_intensity;
      size_t num_contacts = latest_contact_array_.contacts.size();
      RCLCPP_DEBUG(this->get_logger(), "Main loop: single contact intensity=%.2f, contacts in array=%zu",
                   intensity, num_contacts);
      
      // Additional processing can be performed here without interfering with callbacks.
    }
    // The mutex is automatically released when the lock goes out of scope.
  }

  // Subscribers
  rclcpp::Subscription<tactile_contact_sim::msg::Contact>::SharedPtr single_sub_;
  rclcpp::Subscription<tactile_contact_sim::msg::ContactArray>::SharedPtr multi_sub_;
  // Timer for the main loop
  rclcpp::TimerBase::SharedPtr main_timer_;
  // Class variables to store the latest messages
  tactile_contact_sim::msg::Contact latest_single_contact_;
  tactile_contact_sim::msg::ContactArray latest_contact_array_;
  // Mutex to ensure thread-safe access to the data members
  std::mutex data_mutex_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ContactSubscriber>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
