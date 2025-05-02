This repository is based on [this](https://github.com/artastier/PX4_Swarm_Controller) package developed by Arthur Artasier. The changes made are that this is now compatible with ROS2 Foxy which thankfully still ships with Gazebo-Classic.

## How to Use this
Clone the repository provided in the link above. Then copy paste the contents of the files mentioned here. I will be uploading the complete repository soon.


## Porting Notes: ROS 2 Foxy + Gazebo Classic Compatibility

The `px4_swarm_controller` package was ported for ROS 2 Foxy using Gazebo Classic. Numerous C++ and ROS API changes were applied for compatibility with Foxy's rclcpp and Eigen 3.3 versions.


| File | Change |
|------|--------|
| `Arming.cpp` | Added default value to parameter: `declare_parameter<int>("nb_drones", 1)` |
| `ChangeWaypoint.cpp` | Added default values to parameters: `wp_path`, `x_init`, `y_init` |
| `NearestNeighbors.hpp` | Fixed vector default type: `x_init` now uses `{0.0}` |
| `WeightedTopologyNeighbors.hpp` | Replaced invalid Eigen type with `Eigen::Matrix<std::size_t, Eigen::Dynamic, 1>` |
| `WeightedTopologyController.hpp` | Replaced `Eigen::Vector<float, 6>` with `Eigen::Matrix<float, 6, 1>` for `PoseTwist` |
| `WeightedTopologyNeighbors.cpp` | Fixed broken size comparison using comma operator → replaced with logical `&&` |
| `simulation_node.py` | setting GAZEBO_PLUGIN_PATH and GAZEBO_MODEL_PATH within the gnome-terminal commands.|
- Added default value to `gains` parameter  
- Replaced invalid `PoseTwist` constructor with `<<` operator  
- Manually reshaped 6×1 vector into 2×3 matrix instead of using unsupported `.reshaped()`  
- Added defaults for: `leaders`, `x_formation`, `y_formation`, `z_formation` 


## Specific changes made in the second iteration for C++14 compatibility
As absurd as it may seem, I had to deprecate compatibility of syntax to function with ROS2 Foxy. In my defence, at the time of release, Ignition Gazebo migration is extremely code intensive. Hence, the downgrade was easier.

| File | Change |
|------|--------|
| `ChangeWaypoint.cpp` | Replaced `std::size(...)` → `.size()` and `std::hypot(...)` → `std::sqrt(std::pow(...))` |
| `WeightedTopologyController.cpp` | Replaced `std::size(...)` → `.size()` on `gains` and `neighbors_position` |
| `WeightedTopologyNeighbors.cpp` | Replaced `std::empty(...)` → `.empty()` on vectors |
| `NearestNeighbors.hpp` | Replaced 3D `std::hypot(...)` → manual Euclidean norm with `std::sqrt(...)` |
| `PID.hpp` | Replaced `std::is_floating_point_v<T>` with `std::is_floating_point<T>::value` + compatible `enable_if` |
