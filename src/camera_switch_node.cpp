#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/msg/joy.hpp"

class CameraSwitch : public rclcpp::Node {
public:
  CameraSwitch() : Node("camera_switch"), active_camera_("front") {
    // Publisher für die aktive Kamera
    active_camera_pub_ = this->create_publisher<sensor_msgs::msg::Image>("active_camera/image_raw", 10);

    // Subscriber für die Frontkamera
    front_camera_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
      "front_camera/image_raw", 10,
      [this](sensor_msgs::msg::Image::SharedPtr msg) {
        if (active_camera_ == "front") {
          active_camera_pub_->publish(*msg);
        }
      });

    // Subscriber für die Rückkamera
    back_camera_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
      "back_camera/image_raw", 10,
      [this](sensor_msgs::msg::Image::SharedPtr msg) {
        if (active_camera_ == "back") {
          active_camera_pub_->publish(*msg);
        }
      });

    // Subscriber für Joystick-Eingaben (unabhängige Logik!)
    joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
      "joy", 10,
      [this](sensor_msgs::msg::Joy::SharedPtr msg) {
        if (msg->buttons[0] == 1) {  // Knopf 0: Vorwärts (Frontkamera)
          active_camera_ = "front";
          RCLCPP_INFO(this->get_logger(), "Aktive Kamera: FRONT (Vorwärts)");
        } else if (msg->buttons[1] == 1) {  // Knopf 1: Rückwärts (Rückkamera)
          active_camera_ = "back";
          RCLCPP_INFO(this->get_logger(), "Aktive Kamera: RÜCK (Rückwärts)");
        }
      });
  }

private:
  std::string active_camera_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr active_camera_pub_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr front_camera_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr back_camera_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CameraSwitch>());
  rclcpp::shutdown();
  return 0;
}