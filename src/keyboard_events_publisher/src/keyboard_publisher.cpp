#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32_multi_array.hpp>

#include <SDL2/SDL.h>
#include <unordered_set>

class KeyboardPublisher : public rclcpp::Node
{
public:
    KeyboardPublisher() : Node("keyboard_publisher")
    {
        publisher_ = create_publisher<std_msgs::msg::Int32MultiArray>("keys_pressed", 10);

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            RCLCPP_ERROR(get_logger(), "SDL could not initialize: %s", SDL_GetError());
            rclcpp::shutdown();
        }

        window_ = SDL_CreateWindow("ROS2 Keyboard Capture",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   100, 100,
                                   SDL_WINDOW_SHOWN);

        if (!window_) {
            RCLCPP_ERROR(get_logger(), "SDL window creation failed: %s", SDL_GetError());
            SDL_Quit();
            rclcpp::shutdown();
        }

        timer_ = create_wall_timer(
            std::chrono::milliseconds(20),
            std::bind(&KeyboardPublisher::pollKeyboard, this));
    }

    ~KeyboardPublisher()
    {
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }

private:
    void pollKeyboard()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                rclcpp::shutdown();
                return;
            }
            else if (event.type == SDL_KEYDOWN && !event.key.repeat) {
                keys_pressed_.insert(static_cast<int>(event.key.keysym.sym));
            }
            else if (event.type == SDL_KEYUP) {
                keys_pressed_.erase(static_cast<int>(event.key.keysym.sym));
            }
        }

        std_msgs::msg::Int32MultiArray msg;
        msg.data.assign(keys_pressed_.begin(), keys_pressed_.end());
        publisher_->publish(msg);
    }

private:
    rclcpp::Publisher<std_msgs::msg::Int32MultiArray>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    SDL_Window* window_;
    std::unordered_set<int> keys_pressed_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<KeyboardPublisher>());
    rclcpp::shutdown();
    return 0;
}
