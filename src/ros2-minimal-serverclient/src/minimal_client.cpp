#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#include <random>

/* Minimal Client Class Definition */
class MinimalClient : public rclcpp:Node {
    private:
        rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_; // Shared pointer to a client object of type AddTwoInts from example_interfaces
        rclcpp::TimerBase::SharedPtr timer_;
        void timer_callback() { // Fill out the request message
            auto req = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
            req->a = std::rand() % 11;
            req->b = std::rand() % 11;
            client_->async_send_request(req, std::bind(&MinimalClient::response_callback, this, std::placeholders::_1));    // Send the request to the server and set callback
        }
        void response_callback(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture future) {  // Log result when received fromserver
            auto resp = future.get();
            RCLCPP_INFO(this->get_logger(), "Result: %d", (int)resp->sum);
        }
    public:
        MinimalClient() : Node("minimal_client") {
            client_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_ints"); // Creates our client object by using the create_client method from Node.
                                                                                            // <Type>(name_of_the_service_to_interact_with)
            while (!client_->wait_for_service(std::chrono::seconds(2))) {   // Wait until service its available. If its not, then print a warning message
                RCLCPP_WARN(this->get_logger, "Waiting for service...");
            }
            std::srand(std::time(nullptr)); // Seed random number generator with current time
            timer_ = this->create_wall_timer(std::chrono::milliseconds(2000), std::bind(&MinimalClient::timer_callback, this));
        }
}

/* Main Entrypoint*/
int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);                       // Initualizes the ROS2 communication system
    auto node = std::make_shared<MinimalClient>();  // Creates the node object using a shared pointer
    rclcpp::spin(node);                             // Keeps the node alive and processing callbacks
    rclcpp::shutdown();                             // Properly shuts down ROS2 before exiting
    return 0;
}