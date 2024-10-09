// Copyright 2024 FUTU-RE Co. LTD.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "dummy_bms.hpp"

#include <chrono>

using namespace std::chrono_literals;

DummyBmsNode::DummyBmsNode()
  : Node("dummy_bms_node"),
    soc_value_(2)  // default value for soc_value_
{
  // Initialize EHMI Publisher
  battery_rsoc_pub_ = this->create_publisher<UIInt16>("/ui/battery/roc", 10);

  // Initialize the timer
  timer_ = this->create_wall_timer(10000ms, std::bind(&DummyBmsNode::main_loop, this));

  // Start a thread for user input
  std::thread(&DummyBmsNode::user_input_thread, this).detach();
}

//////// MAIN LOOP ////////
void DummyBmsNode::main_loop()
{
  UIInt16 soc_msg;

  {
    // Lock the mutex to safely access the shared soc_value_
    std::lock_guard<std::mutex> lock(soc_mutex_);
    soc_msg.data = soc_value_;
  }

  // Publish battery soc
  battery_rsoc_pub_->publish(soc_msg);

  RCLCPP_INFO(this->get_logger(), "Battery roc value published: %d", soc_msg.data);
}

//////// USER INPUT THREAD ////////
void DummyBmsNode::user_input_thread()
{
  while (rclcpp::ok()) {
    int16_t input_value;
    std::cout << "Enter new soc_value_: ";
    std::cin >> input_value;

    {
      // Lock the mutex to safely modify the shared soc_value_
      std::lock_guard<std::mutex> lock(soc_mutex_);
      soc_value_ = input_value;
    }

    RCLCPP_INFO(this->get_logger(), "User updated soc_value_ to: %d", soc_value_);
  }
}
