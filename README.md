# ROS 2 Minimal Server/Client (C++)

This repository contains a minimal example of a **Server** and **Client** in ROS 2 using C++ and the `rclcpp` library.

## 📌 Overview
The project demonstrates how two nodes communicate through a *service*:
- The **Server** offers a service that processes requests.
- The **Client** sends a request to the server and waits for a response.

This is intended as an introductory example for learning ROS 2 services.

## 🚀 Requirements
- ROS 2 Jazzy.
- CMake ≥ 3.8.
- A C++17-compatible compiler.

## 📂 Project Structure
```text
ros2-minimal-serverclient/
├── src/
│   └── ros2-minimal-serverclient/
│       ├── include/
│		├── src/
│		│   ├── minimal_server.cpp
│		│   └── minimal_client.cpp
│		├── CMakeLists.txt
│		└── package.xml
└── README.md
```

## ⚙️ Build Instructions
Clone the repository inside your workspace:

```bash
cd ~/ros2_ws
git clone https://github.com/igngonzalez/ros2-minimal-serverclient.git
cd ros2-minimal-serverclient
colcon build --packages-select ros2-minimal-serverclient
```

## ▶️ Run the Example
```bash
# Terminal 1: run the publisher
. install/setup.bash
ros2 run ros2-minimal-pubsub minimal_publisher

# Terminal 2: run the subscriber
. install/setup.bash
ros2 run ros2-minimal-pubsub minimal_subscriber
```

# 📖 References
- [ROS2 Tutorials](https://docs.ros.org/en/jazzy/Tutorials)
- [rclcpp API Documentation](https://docs.ros.org/en/jazzy/p/rclcpp/generated/index.html)
