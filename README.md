This repository is based on [this](https://github.com/artastier/PX4_Swarm_Controller) package developed by Arthur Artasier. The changes made are that this is now compatible with ROS2 Foxy which thankfully still ships with Gazebo-Classic.

## Porting Notes for ROS 2 Foxy Compatibility

The `px4_swarm_controller` package was updated for compatibility with ROS 2 Foxy and Eigen 3.3. Below is a summary of code modifications made to eliminate build errors and modernize API usage:

| File | Change |
|------|--------|
| `ChangeWaypoint.cpp` | Added default values to `declare_parameter` calls (`wp_path`, `x_init`, `y_init`) |
| `NearestNeighbors.hpp` | Corrected vector default: `declare_parameter<std::vector<double>>("x_init", {0.0})` |
| `WeightedTopologyNeighbors.hpp` | Replaced invalid Eigen type with `Eigen::Matrix<std::size_t, Eigen::Dynamic, 1>` |
| `WeightedTopologyController.hpp` | Replaced `Eigen::Vector<float, 6>` with `Eigen::Matrix<float, 6, 1>` |
| `WeightedTopologyNeighbors.cpp` | Fixed logic error: replaced comma operator with `&&` for size comparison |
| `WeightedTopologyController.cpp` | Declared parameter `gains` with default `{1.0}`; replaced invalid Eigen initialization in lambda |
| `WeightedTopologyController.cpp` | Replaced `.reshaped(2, 3)` with manual reshaping using `Eigen::Matrix<float, 2, 3>` |

These changes ensure clean builds with `colcon build` and prevent API incompatibilities with the versions of rclcpp and Eigen provided in ROS 2 Foxy.
