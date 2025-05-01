#!/usr/bin/env python3

__author__ = 'Arthur Astier - modified by Siddhant Baroth, 2025 (New York University)'

import rclpy
from rclpy.node import Node
import subprocess
import time


class SimulationScript(Node):
    def __init__(self):
        super().__init__('simulation_node')

        # Declare launch parameters
        self.declare_parameter('nb_vehicles', 0)
        self.declare_parameter('drone_model', '')
        self.declare_parameter('world', '')
        self.declare_parameter('script', '')
        self.declare_parameter('target', '')
        self.declare_parameter('label', '')
        self.declare_parameter('initial_pose', '')

        # Extract parameter values
        (n, m, w, s, t, l, p) = self.get_parameters(
            ['nb_vehicles', 'drone_model', 'world', 'script', 'target', 'label', 'initial_pose'])

        # Build query string for sitl_multiple_run.sh
        query_arguments = {
            ' -n ': n.value,
            ' -m ': m.value,
            ' -w ': w.value,
            ' -s ': s.value,
            ' -t ': t.value,
            ' -l ': l.value,
            ' -p ': p.value
        }

        query = ""
        for key, value in query_arguments.items():
            if value:
                query += key + (str(value) if not isinstance(value, str) else value)

        self.get_logger().info("Provided parameters" + query)

        # Gazebo environment paths
        plugin_path = "~/PX4-Autopilot/build/px4_sitl_default/build_gazebo-classic"
        model_path = "~/PX4-Autopilot/Tools/simulation/gazebo-classic/sitl_gazebo-classic/models"

        # List of commands to run in new terminals
        commands = [
            f"export GAZEBO_PLUGIN_PATH={plugin_path}:$GAZEBO_PLUGIN_PATH && "
            f"export GAZEBO_MODEL_PATH={model_path}:$GAZEBO_MODEL_PATH && "
            "MicroXRCEAgent udp4 -p 8888",

            f"cd ~/PX4-Autopilot && "
            f"export GAZEBO_PLUGIN_PATH={plugin_path}:$GAZEBO_PLUGIN_PATH && "
            f"export GAZEBO_MODEL_PATH={model_path}:$GAZEBO_MODEL_PATH && "
            f"/bin/bash ./Tools/simulation/gazebo-classic/sitl_multiple_run.sh{query}"
        ]

        # Launch each command in its own gnome-terminal tab
        for command in commands:
            subprocess.run(["gnome-terminal", "--tab", "--", "bash", "-c", command + "; exec bash"])
            time.sleep(1)  # Optional delay between launching tabs


def main(args=None):
    rclpy.init(args=args)
    node = SimulationScript()
    try:
        rclpy.spin(node)
    finally:
        subprocess.run("pkill gnome-terminal", shell=True)
        rclpy.shutdown()


if __name__ == "__main__":
    main()
