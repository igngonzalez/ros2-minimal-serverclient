#include "rclcpp/rclcpp.hpp"                            // Main ROS2 library for C++
#include "example_interfaces/srv/add_two_ints.hpp"      // For using the interface AddTwoInts

/* Minimal Server Class Definition */
class MinimalServer : public rclcpp::Node { // Inherits from class Node from rclcpp
    private:
        rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;    // Shared pointer to a service object of type AddTwoInts from example_interfaces
        void server_callback(const example_interfaces::srv::AddTwoInts::Request::SharedPtr req, const example_interfaces::srv::AddTwoInts::Response::SharedPtr resp) { // Callback function. As we declared in the server constructor, it has 2 parameters (placeholders), the request and the response
            resp->sum = req->a + req->b;
            RCLCPP_INFO(this->get_logger(), "Received request: a=%d, b=%d", (int)req->a, (int)req->b);  // Prints an informational message in the ROS2 console log.
        }

    public:
        MinimalServer() : Node("minimal_server") {
            server_ = this -> create_service<example_interfaces::srv::AddTwoInts>("add_ints", std::bind(&MinimalServer::server_callback, this, std::placeholders::_1, std::placeholders::_2));    // Create a service object. This is what creates our node into a server.
                                                                                                                                                                                                // We do this by calling the function create_service from Node.
                                                                                                                                                                                                // <Type_for_the_template>(name_of_our_service, which_callback_should_be_used)
    
        }
};

/* Main Entrypoint*/
int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);                       // Initualizes the ROS2 communication system
    auto node = std::make_shared<MinimalServer>();  // Creates the node object using a shared pointer
    rclcpp::spin(node);                             // Keeps the node alive and processing callbacks
    rclcpp::shutdown();                             // Properly shuts down ROS2 before exiting
    return 0;
}