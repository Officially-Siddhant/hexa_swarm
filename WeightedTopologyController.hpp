/**
 * @brief Controller implementing distributed leader-follower formation control for multiple quadrotors with weighted topology.
 *
 * This controller is based on the paper:
 *
 * "Distributed leader-follower formation control for multiple quadrotors with weighted topology"
 * Zhicheng Hou, Isabelle Fantoni, hal-01180491
 *
 * It extends the SwarmController class to implement specific behavior for the weighted topology scenario.
 *
 * @author Arthur Astier
 */
#pragma once

#include <rclcpp/rclcpp.hpp>
#include <eigen3/Eigen/Eigen>
#include "SwarmController.hpp"
#include <custom_msgs/msg/weighted_topology_neighbors.hpp>
#include <limits>
#include <std_msgs/msg/float32_multi_array.hpp>
#include "PID.hpp"

namespace Controller {
    class WeightedTopologyController : public SwarmController<custom_msgs::msg::WeightedTopologyNeighbors> {
        using WeightedTopologyNeighbors = custom_msgs::msg::WeightedTopologyNeighbors;
        using SwarmControllerType = SwarmController<custom_msgs::msg::WeightedTopologyNeighbors>;
        using TrajectorySetpoint = SwarmControllerType::TrajectorySetpoint;
        using PoseTwist = Eigen::Matrix<float, 6, 1>;
        using Neighborhood = Eigen::Matrix<float, 6, Eigen::Dynamic>;
        using PID = PID::PID<float>;
    public:
        /**
         * @brief Constructs a new Weighted Topology Controller object.
         *
         * Initializes the controller by retrieving gains from parameters.
         */
        WeightedTopologyController();

    private:
        /**
         * @brief Convert neighbors data to matrix representation.
         *
         * @param neighbors The neighbors data received from the subscription.
         */
        void neighbors_to_matrix(const WeightedTopologyNeighbors &neighbors);

        /**
         * @brief Callback function for processing incoming neighbor data.
         *
         * @param neighbors Pointer to the received neighbor data.
         */
        void neighbors_callback(const WeightedTopologyNeighbors::SharedPtr &neighbors) override;

        /**
         * @brief Timer callback function for periodic control computations.
         */
        void timer_callback() override;

        /**
         * @brief Compute control command based on the current neighborhood information.
         *
         * @param setpoint Reference to the trajectory setpoint to be updated with the computed command.
         */
        void compute_command(TrajectorySetpoint &setpoint);

    private:
        Neighborhood neighborhood;   /**< Matrix representation of neighborhood information. */
        bool is_neighborhood_empty{true};  /**< Flag indicating whether the neighborhood is empty. */
        // TODO: Take it as a parameter
        std::vector<float> default_pose{0., 0., -5.};  /**< Default pose to be used if neighborhood is empty. */
        PID pid_ax{3.,2u}; /**<Acceleration PID Controller on X axis> */
        PID pid_ay{3.,2u}; /**<Acceleration PID Controller on Y axis> */
        PID pid_az{3.,2u}; /**<Acceleration PID Controller on Z axis> */
        float command_tp{0.0}; /** <Timepoint corresponding to last command computation> */
    };
}
